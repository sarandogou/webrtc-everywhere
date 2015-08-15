/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Common.h"
#include "_Utils.h"
#include "_Buffer.h"
#include "_MediaStream.h"
#include "_Debug.h"

#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"
#include "talk/app/webrtc/portallocatorfactory.h"
#include "webrtc/base/proxydetect.h"
#include "webrtc/p2p/client/basicportallocator.h"

#include <sys/stat.h>

#if !defined(PEERCONN_MODE)
#define PEERCONN_MODE 1
#endif

#if PEERCONN_MODE == 1
static rtc::Thread* _worker_thread = NULL;
static rtc::scoped_refptr<webrtc::PortAllocatorFactoryInterface> _port_allocator_factory = NULL;
static rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _fake_peer_connection = NULL; // TODO: "getUserMedia" fails if no PeerconnectionFactory instance exists. Why?
static webrtc::CriticalSectionWrapper* _fake_peer_connection_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
#else
rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _fake_peer_connection(webrtc::CreatePeerConnectionFactory());
#endif

#if 0
static const char kFirefoxPattern[] = "Firefox";
static const char kInternetExplorerPattern[] = "MSIE";
#endif
static const char kAutoDetectPattern[] = "";
#if 1
#	define kAgentHoldingProxyInfo		kAutoDetectPattern
#else
#	if WE_UNDER_WINDOWS
#		define kAgentHoldingProxyInfo	kInternetExplorerPattern
#	else
#		define kAgentHoldingProxyInfo	""
#	endif
#endif

// TODO(mdi): On OSX We have to include "portallocatorfactory.cc" because it seems like "portallocatorfactory.o" is missing in libjingle_peerconnection
// This could cause duplicated symbols if the bug get fixed by Google
//
//	_RTCPortAllocatorFactory
//
class _RTCPortAllocatorFactory : public webrtc::PortAllocatorFactory
{
public:
	_RTCPortAllocatorFactory(rtc::Thread* worker_thread)
		: webrtc::PortAllocatorFactory(worker_thread)
	{

	}
	virtual ~_RTCPortAllocatorFactory()
	{
	}

	virtual cricket::PortAllocator* CreatePortAllocator(
		const std::vector<StunConfiguration>& stun,
		const std::vector<TurnConfiguration>& turn)
	{
		cricket::PortAllocator* allocator_ = webrtc::PortAllocatorFactory::CreatePortAllocator(stun, turn);
		if (allocator_) {
			cricket::ProtocolType protocol;
			rtc::ProxyInfo proxyInfo;
			static const struct {
				std::string scheme;
				rtc::ProxyType proxy_type;
			} PROXIES[] = {
				{ "http", rtc::ProxyType::PROXY_HTTPS },
				{ "https", rtc::ProxyType::PROXY_HTTPS },
				{ "socks5", rtc::ProxyType::PROXY_SOCKS5 }
			};
			for (size_t i = 0; i < turn.size(); ++i) {
				if (cricket::StringToProto(turn[i].transport_type.c_str(), &protocol)) {
					if (protocol == cricket::ProtocolType::PROTO_TCP || protocol == cricket::ProtocolType::PROTO_SSLTCP) {
						for (size_t j = 0; j < sizeof(PROXIES) / sizeof(PROXIES[0]); ++j) {
							std::string url = PROXIES[j].scheme + "://" + turn[i].server.hostname();
							if (rtc::GetProxySettingsForUrl(kAgentHoldingProxyInfo, url.c_str(), &proxyInfo, false)) {
								if (proxyInfo.type != rtc::ProxyType::PROXY_NONE && !proxyInfo.address.IsAnyIP() && !proxyInfo.address.IsLoopbackIP() && proxyInfo.address.hostname() != "localhost") {
									if (proxyInfo.type == rtc::ProxyType::PROXY_UNKNOWN) {
										proxyInfo.type = PROXIES[j].proxy_type;
									}
									allocator_->set_proxy(kAgentHoldingProxyInfo, proxyInfo);
									goto proxy_done;
								}
							}
						}
					}
				}
			}
		}
proxy_done:
		return allocator_;
	}
private:

};

WEBRTC_EVERYWHERE_API rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> GetPeerConnectionFactory()
{
#if PEERCONN_MODE == 1
	_fake_peer_connection_cs->Enter();
	rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _peer = _fake_peer_connection;
	_fake_peer_connection_cs->Leave();
	return _peer;
#else
	return _fake_peer_connection;
#endif
}

WEBRTC_EVERYWHERE_API void TakeFakePeerConnectionFactory()
{
#if PEERCONN_MODE == 1
	_fake_peer_connection_cs->Enter();
	if (!_worker_thread) {
		_worker_thread = new rtc::Thread;
		if (_worker_thread) {
			_worker_thread->Start();
		}
	}
	if (!_fake_peer_connection) {
		_fake_peer_connection = webrtc::CreatePeerConnectionFactory(_worker_thread, _worker_thread, NULL, NULL, NULL);
	}
	else {
		_fake_peer_connection->AddRef();
	}
	_fake_peer_connection_cs->Leave();
#endif
}

WEBRTC_EVERYWHERE_API void ReleaseFakePeerConnectionFactory()
{
#if PEERCONN_MODE == 1
	_fake_peer_connection_cs->Enter();
	if (_fake_peer_connection) {
		// hack because no function to retrieve the refCount value;
		webrtc::PeerConnectionFactoryInterface* tmp = _fake_peer_connection.get();
		tmp->AddRef();
		if (tmp->Release() == 1) {
			_fake_peer_connection = NULL;
			_port_allocator_factory = NULL;
			if (_worker_thread) {
				delete _worker_thread, _worker_thread = NULL;
			}
		}
		else {
			_fake_peer_connection->Release();
		}
	}
	_fake_peer_connection_cs->Leave();
#endif
}

WEBRTC_EVERYWHERE_API rtc::Thread* GetWorkerThread()
{
	return _worker_thread;
}

WEBRTC_EVERYWHERE_API rtc::scoped_refptr<webrtc::PortAllocatorFactoryInterface> GetPortAllocatorFactory()
{
	if (!_port_allocator_factory) {
        _port_allocator_factory =  new rtc::RefCountedObject<_RTCPortAllocatorFactory>(GetWorkerThread());
	}
	return _port_allocator_factory;
}

rtc::scoped_refptr<_RTCMediaConstraints> BuildConstraints(const _MediaConstraintsObj* _constraints)
{
	rtc::scoped_refptr<_RTCMediaConstraints> contraints = new rtc::RefCountedObject<_RTCMediaConstraints>();

	_MediaConstraints::const_iterator it;

	if (_constraints) {
		if (_constraints->optional) {
			for (it = _constraints->optional->begin(); it != _constraints->optional->end(); ++it) {
				contraints->AddOptional(it->first, it->second);
			}
		}
		if (_constraints->mandatory) {
			for (it = _constraints->mandatory->begin(); it != _constraints->mandatory->end(); ++it) {
				contraints->AddMandatory(it->first, it->second);
			}
		}
	}

	return contraints;
}

webrtc::MediaStreamInterface* BuildMediaStream(const _MediaStream* stream)
{
	if (!stream) {
		return NULL;
	}
	return dynamic_cast<webrtc::MediaStreamInterface*>((webrtc::MediaStreamInterface*)stream->GetWrappedStream());
}

_UniqueObject::_UniqueObject()
: m_id(_Utils::UniqueId())
{
    _Utils::UniqueObjAdd(this);
}

_UniqueObject::~_UniqueObject()
{
    _Utils::UniqueObjRemove(this->UniqueId());
}



#if WE_UNDER_WINDOWS

_File::_File(const TCHAR* path, bool write /*= false*/)
	: m_write(write)

{
	if ((m_file = CreateFile(path,
		GENERIC_READ | (write ? GENERIC_WRITE : 0),
		FILE_SHARE_READ | (write ? FILE_SHARE_WRITE : 0),
		NULL,
		(write ? OPEN_ALWAYS : OPEN_EXISTING),
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS /*| FILE_FLAG_NO_BUFFERING*/,
		NULL)) == INVALID_HANDLE_VALUE) {
		m_file = NULL;
	}
}

_File::~_File()
{
	if (IsValid()) {
		CloseHandle(m_file);
		m_file = NULL;
	}
}

bool _File::IsValid()const
{
	return (m_file && m_file != INVALID_HANDLE_VALUE);
}

bool _File::LockInterProcess(bool exclusive /*= false*/)
{
	if (IsValid()) {
		DWORD flags = exclusive ? LOCKFILE_EXCLUSIVE_LOCK : 0;
		static const DWORD len = 0xffffffff;
		OVERLAPPED offset;
		ZeroMemory(&offset, sizeof(offset));
		if (LockFileEx(m_file, flags, 0, len, len, &offset)) {
			return true;
		}
	}
	return false;
}

bool _File::UnlockInterProcess()
{
	if (IsValid()) {
		static const DWORD len = 0xffffffff;
		OVERLAPPED offset;
		ZeroMemory(&offset, sizeof(offset));
		if (UnlockFileEx(m_file, 0, len, len, &offset)) {
			return true;
		}
	}
	return false;
}

// No safe: up to the caller to lock the file
cpp11::shared_ptr<_Buffer> _File::Read()
{
	if (IsValid()) {
		DWORD nNumberOfBytesToRead = GetFileSize(m_file, NULL);
		if (nNumberOfBytesToRead != INVALID_FILE_SIZE && nNumberOfBytesToRead) {
			cpp11::shared_ptr<_Buffer> buffer(new _Buffer(NULL, nNumberOfBytesToRead));
			if (buffer && buffer->getPtr()) {
				DWORD nNumberOfBytesRead;
				OVERLAPPED offset;
				ZeroMemory(&offset, sizeof(offset));
				if (ReadFile(m_file, (LPVOID)buffer->getPtr(), nNumberOfBytesToRead, &nNumberOfBytesRead, &offset)) {
					if (buffer->getSize() == nNumberOfBytesRead) {
						return buffer;
					}
				}
			}
		}
	}
	return nullPtr;
}

bool _File::Write(cpp11::shared_ptr<_Buffer>& buffer, bool append /*= false*/)
{
	if (IsValid() && buffer && buffer->getPtr() && buffer->getSize()) {
		DWORD dwBytesWritten = 0;
		OVERLAPPED offset;
		ZeroMemory(&offset, sizeof(offset));
		if (!append) {
			static LARGE_INTEGER li_zero = { 0 };
			if (!SetFilePointerEx(m_file, li_zero, NULL, FILE_BEGIN)) {
				return false;
			}
		}
		if (WriteFile(m_file, buffer->getPtr(), (DWORD)buffer->getSize(), &dwBytesWritten, &offset)) {
			if (dwBytesWritten == buffer->getSize()) {
				return (SetEndOfFile(m_file) == TRUE);
			}
		}
	}
	return false; 
}

bool _File::GetModificationTime(_FTIME *time)
{
	if (IsValid()) {
		if (GetFileTime(m_file, NULL, NULL, time)) {
			return true;
		}
	}
	return false;
}

#else // !WE_UNDER_WINDOWS


_File::_File(const char* path, bool write /*= false*/)
: m_write(write)

{
    m_file = fopen(path, write ? "w" : "r");
}

_File::~_File()
{
	if (IsValid()) {
		fclose(m_file);
		m_file = 0;
	}
}

bool _File::IsValid()const
{
	return !!m_file;
}

bool _File::LockInterProcess(bool exclusive /*= false*/)
{
	if (IsValid()) {
        if (flock(fileno(m_file), exclusive ? LOCK_EX : LOCK_SH) == 0) {
            return true;
        }
	}
	return false;
}

bool _File::UnlockInterProcess()
{
	if (IsValid()) {
        if (flock(fileno(m_file), LOCK_UN) == 0) {
            return true;
        }
	}
	return false;
}

// No safe: up to the caller to lock the file
cpp11::shared_ptr<_Buffer> _File::Read()
{
	if (IsValid()) {
        struct stat _stat;
        if (fstat(fileno(m_file), &_stat) == 0 && _stat.st_size) {
            cpp11::shared_ptr<_Buffer> buffer(new _Buffer(NULL, (size_t)_stat.st_size));
            if (buffer && buffer->getPtr()) {
                if (read(fileno(m_file), (void*)buffer->getPtr(), buffer->getSize()) == buffer->getSize()) {
                    return buffer;
                }
            }
        }
	}
	return nullPtr;
}

bool _File::Write(cpp11::shared_ptr<_Buffer>& buffer, bool append /*= false*/)
{
	if (IsValid() && buffer && buffer->getPtr() && buffer->getSize()) {
        if (!append) {
            FILE* fp = fdopen(fileno(m_file), "w"); // will be closed when close() is called
            if (!fp) {
                return false;
            }
            rewind(fp);
        }
        if (write(fileno(m_file), buffer->getPtr(), buffer->getSize()) == buffer->getSize()) {
            if (!append) {
                if (ftruncate(fileno(m_file), buffer->getSize()) != 0) {
                    return false;
                }
            }
            return true;
        }
	}
	return false;
}

bool _File::GetModificationTime(_FTIME *time)
{
    #define Int32x32To64(a, b) ((LONGLONG)((LONG)(a)) * (LONGLONG)((LONG)(b)))
    #define LONG long
	if (IsValid()) {
		struct stat _stat;
        if (fstat(fileno(m_file), &_stat) == 0) {
            time_t tt = (time_t)_stat.st_mtimespec.tv_sec;
            LONGLONG ll = Int32x32To64(tt, 10000000) + 116444736000000000;
            time->dwLowDateTime = (unsigned long) ll;
            time->dwHighDateTime = ll >>32;
            return true;
        }
	}
	return false;
}

#endif /* !WE_UNDER_WINDOWS */


