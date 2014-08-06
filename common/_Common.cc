/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Common.h"
#include "_Utils.h"
#include "_Buffer.h"
#include "_MediaStream.h"

#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"

#include <sys/stat.h>

#if !defined(PEERCONN_MODE)
#define PEERCONN_MODE 1
#endif

#if PEERCONN_MODE == 1
static talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _fake_peer_connection = NULL; // TODO: "getUserMedia" fails if no PeerconnectionFactory instance exists. Why?
static webrtc::CriticalSectionWrapper* _fake_peer_connection_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
#else
talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _fake_peer_connection(webrtc::CreatePeerConnectionFactory());
#endif

WEBRTC_EVERYWHERE_API talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> GetPeerConnectionFactory()
{
#if PEERCONN_MODE == 1
	_fake_peer_connection_cs->Enter();
	talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _peer = _fake_peer_connection;
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
	if (!_fake_peer_connection) {
		_fake_peer_connection = webrtc::CreatePeerConnectionFactory();
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
		}
		else {
			_fake_peer_connection->Release();
		}
	}
	_fake_peer_connection_cs->Leave();
#endif
}

talk_base::scoped_refptr<_RTCMediaConstraints> BuildConstraints(const _MediaConstraintsObj* _constraints)
{
	talk_base::scoped_refptr<_RTCMediaConstraints> contraints = new talk_base::RefCountedObject<_RTCMediaConstraints>();

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
		if (WriteFile(m_file, buffer->getPtr(), buffer->getSize(), &dwBytesWritten, &offset)) {
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
#error "Not implemented"
#endif


