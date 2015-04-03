#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <assert.h>

#if 1
// http://www.w3.org/TR/mediacapture-streams/
// http://www.w3.org/TR/webrtc/

#include "_PeerConnection.h"
#include "_NavigatorUserMedia.h"
#include "_MediaStream.h"
#include "_MediaStreamTrack.h"
#include "_MediaTrackConstraints.h"
#include "_MediaStreamConstraints.h"
#include "_EncryptCtx.h"
#include "_Utils.h"
#include "_Buffer.h"
#include "_Debug.h"

#ifdef WIN32
#include <Windows.h>
#endif

static std::shared_ptr<_MediaStream> mediaStream = nullptr;
static std::shared_ptr<_SessionDescription>sdpOffer = nullptr;
static std::shared_ptr<_PeerConnection>peerConnection = nullptr;

static std::shared_ptr<_Sequence<_MediaStream> > localStreams;
static std::shared_ptr<_Sequence<_MediaStream> > remoteStreams;

// http://www.w3.org/TR/webrtc/#idl-def-RTCSessionDescriptionCallback
static void CreateOfferSuccessCb(std::shared_ptr<_SessionDescription> sdp)
{
	sdpOffer = sdp;
}

// http://www.w3.org/TR/webrtc/#idl-def-RTCPeerConnectionErrorCallback
static void CreateOfferErrorCb(std::shared_ptr<std::string> error)
{

}

// http://www.w3.org/TR/mediacapture-streams/#idl-def-NavigatorUserMediaSuccessCallback
static void NavigatorUserMediaSuccessCb(std::shared_ptr<_MediaStream> stream)
{
	mediaStream = stream;
}

// http://www.w3.org/TR/mediacapture-streams/#idl-def-NavigatorUserMediaErrorCallback
static void NavigatorUserMediaErrorCb(std::shared_ptr<_NavigatorUserMediaError>e)
{
	WE_DEBUG_ERROR("%s", e->constraintName.c_str());
}

// http://www.w3.org/TR/webrtc/#event-negotiation
static void onnegotiationneededCallback()
{

}
// http://www.w3.org/TR/webrtc/#event-icecandidate
static void onicecandidateCallback(std::shared_ptr<_RTCPeerConnectionIceEvent> e)
{
	if (e->candidate) {
		peerConnection->AddIceCandidate(e->candidate.get());
	}
}
// http://www.w3.org/TR/webrtc/#event-signalingstatechange
static void onsignalingstatechangeCallback()
{
	if (peerConnection) {
		WE_DEBUG_INFO("New signaling state: %s", peerConnection->SignalingState());
	}
}
// http://www.w3.org/TR/webrtc/#event-mediastream-addstream
static void onaddstreamCallback(std::shared_ptr<_MediaStreamEvent> stream)
{

}

// http://www.w3.org/TR/webrtc/#event-mediastream-removestream
static void onremovestreamCallback(std::shared_ptr<_MediaStreamEvent> stream)
{

}
// http://www.w3.org/TR/webrtc/#event-iceconnectionstatechange
static void oniceconnectionstatechangeCallback()
{

}

// http://www.w3.org/TR/webrtc/#idl-def-RTCStatsCallback
static void onRTCStatsCallback(std::shared_ptr<_RTCStatsReport> report)
{

}

static DWORD WINAPI CreatePeerConnection(LPVOID lpParam)
{
	std::shared_ptr<_MediaConstraints> optional = std::make_shared<_MediaConstraints>();
	std::shared_ptr<_MediaConstraints> mandatory = std::make_shared<_MediaConstraints>();
	_MediaConstraintsObj peerConnectionConstraints(optional, mandatory);

	peerConnection = std::make_shared<_PeerConnection>();
	static _RTCIceServer iceServers[] = {
		{ "stun:stun.l.google.com:19302" },
		{ "turn:numb.viagenie.ca:3478", "user", "password" },
	};
	static size_t iceServersCount = sizeof(iceServers) / sizeof(iceServers[0]);

	_RTCConfiguration peerConnectionConfiguration;
	peerConnectionConfiguration.iceServers.push_back(_RTCIceServer(iceServers[0].uri, iceServers[0].username, iceServers[0].password));
	peerConnectionConfiguration.iceServers.push_back(_RTCIceServer(iceServers[1].uri, iceServers[1].username, iceServers[1].password));

	peerConnection->SetCallback_onnegotiationneeded(onnegotiationneededCallback);
	peerConnection->SetCallback_onicecandidate(onicecandidateCallback);
	peerConnection->SetCallback_onsignalingstatechange(onsignalingstatechangeCallback);
	peerConnection->SetCallback_onaddstream(onaddstreamCallback);
	peerConnection->SetCallback_onremovestream(onremovestreamCallback);
	peerConnection->SetCallback_oniceconnectionstatechange(oniceconnectionstatechangeCallback);

	mandatory->insert(std::pair<std::string, std::string>("DtlsSrtpKeyAgreement", "true"));
	if (!peerConnection->Init(&peerConnectionConfiguration, &peerConnectionConstraints)) {
		goto bail;
	}

	if (!peerConnection->AddStream(mediaStream.get())) {
		goto bail;
	}

	if (!peerConnection->CreateOffer(CreateOfferSuccessCb, CreateOfferErrorCb)) {
		goto bail;
	}

	// FIXME: AssertBreak() at the end because not all streams are destroyed
	localStreams = peerConnection->GetLocalStreams();
	remoteStreams = peerConnection->GetRemoteStreams();

	if (localStreams->values.size() > 0) {
		std::shared_ptr<_MediaStream>localStream = localStreams->values[0]->clone();

		std::shared_ptr<_Sequence<_MediaStreamTrack> > audioTracks = localStream->getAudioTracks();
		std::shared_ptr<_Sequence<_MediaStreamTrack> > videoTracks = localStream->getVideoTracks();

		WE_DEBUG_INFO("audioTracks.size() = %ld", audioTracks->values.size());
		WE_DEBUG_INFO("videoTracks.size() = %ld", videoTracks->values.size());

		for (size_t i = 0; i < audioTracks->values.size(); ++i) {
			WE_DEBUG_INFO("AudioTrack: %s, %s, %s", audioTracks->values[i]->id(), audioTracks->values[i]->kind(), audioTracks->values[i]->label());
		}
		for (size_t i = 0; i < videoTracks->values.size(); ++i) {
			WE_DEBUG_INFO("VideoTrack: %s, %s, %s", videoTracks->values[i]->id(), videoTracks->values[i]->kind(), videoTracks->values[i]->label());
		}
	}

bail:
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	_Utils::Initialize();
	TakeFakePeerConnectionFactory();

	WeError err = WeError_Success;
	HANDLE thread = NULL;

	std::shared_ptr<_MediaTrackConstraints> audio = std::make_shared<_MediaTrackConstraints>(true);
	std::shared_ptr<_MediaTrackConstraints> video = std::make_shared<_MediaTrackConstraints>(true);
	_MediaStreamConstraints mediaStreamConstraints(audio, video);

	_NavigatorUserMedia::getUserMedia(&mediaStreamConstraints, NavigatorUserMediaSuccessCb, NavigatorUserMediaErrorCb);

	if (!mediaStream) {
		goto bail;
	}

	thread = CreateThread(NULL, 0, CreatePeerConnection, NULL, 0, NULL);

	// getchar();
	MSG msg;
	BOOL gm;
	while ((gm = ::GetMessage(&msg, NULL, 0, 0)) != 0 && gm != -1) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	localStreams = nullptr;
	remoteStreams = nullptr;
	peerConnection = nullptr;
	mediaStream = nullptr;
	_Utils::DeInitialize();
	ReleaseFakePeerConnectionFactory();
	if (thread) {
		CloseHandle(thread);
	}

	return 0;

bail:
	assert(0);
	return -1;
}

#elif 0
#include <windows.h>
#include <winhttp.h>

extern "C" {
	typedef HINTERNET(WINAPI *pfWinHttpOpen)
		(
		_In_opt_z_ LPCWSTR pszAgentW,
		_In_ DWORD dwAccessType,
		_In_opt_z_ LPCWSTR pszProxyW,
		_In_opt_z_ LPCWSTR pszProxyBypassW,
		_In_ DWORD dwFlags
		);

	typedef WINHTTPAPI HINTERNET (WINAPI *pfWinHttpConnect)
		(
		IN HINTERNET hSession,
		IN LPCWSTR pswzServerName,
		IN INTERNET_PORT nServerPort,
		IN DWORD dwReserved
		);
	typedef WINHTTPAPI HINTERNET (WINAPI *pfWinHttpOpenRequest)
		(
		IN HINTERNET hConnect,
		IN LPCWSTR pwszVerb,
		IN LPCWSTR pwszObjectName,
		IN LPCWSTR pwszVersion,
		IN LPCWSTR pwszReferrer OPTIONAL,
		IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL,
		IN DWORD dwFlags
		);
	typedef WINHTTPAPI BOOL(WINAPI *pfWinHttpSetOption)
		(
		_In_opt_ HINTERNET hInternet,
		_In_ DWORD dwOption,
		_When_((dwOption == WINHTTP_OPTION_USERNAME ||
		dwOption == WINHTTP_OPTION_PASSWORD ||
		dwOption == WINHTTP_OPTION_PROXY_USERNAME ||
		dwOption == WINHTTP_OPTION_PROXY_PASSWORD ||
		dwOption == WINHTTP_OPTION_USER_AGENT),
		_At_((LPCWSTR)lpBuffer, _In_reads_(dwBufferLength)))
		_When_((dwOption != WINHTTP_OPTION_USERNAME &&
		dwOption != WINHTTP_OPTION_PASSWORD &&
		dwOption != WINHTTP_OPTION_PROXY_USERNAME &&
		dwOption != WINHTTP_OPTION_PROXY_PASSWORD &&
		dwOption != WINHTTP_OPTION_USER_AGENT),
		_In_reads_bytes_(dwBufferLength))
		LPVOID lpBuffer,
		_In_ DWORD dwBufferLength
		);

	typedef WINHTTPAPI BOOL (WINAPI *pfWinHttpGetProxyForUrl)
		(
		IN  HINTERNET                   hSession,
		IN  LPCWSTR                     lpcwszUrl,
		IN  WINHTTP_AUTOPROXY_OPTIONS * pAutoProxyOptions,
		OUT WINHTTP_PROXY_INFO *        pProxyInfo
		);
	typedef WINHTTPAPI BOOL(WINAPI *pfWinHttpSendRequest)
		(
		IN HINTERNET hRequest,
		_In_reads_opt_(dwHeadersLength) LPCWSTR lpszHeaders,
		IN DWORD dwHeadersLength,
		_In_reads_bytes_opt_(dwOptionalLength) LPVOID lpOptional,
		IN DWORD dwOptionalLength,
		IN DWORD dwTotalLength,
		IN DWORD_PTR dwContext
		);
	typedef WINHTTPAPI BOOL(WINAPI *pfWinHttpReceiveResponse)
		(
		IN HINTERNET hRequest,
		IN LPVOID lpReserved
		);
	typedef WINHTTPAPI BOOL(WINAPI *pfWinHttpCloseHandle)
		(
		IN HINTERNET hInternet
		);

} // extern "C"

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	HMODULE hLibrary = NULL;
	HINTERNET hHttpSession = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hRequest = NULL;

	WINHTTP_AUTOPROXY_OPTIONS  AutoProxyOptions;
	WINHTTP_PROXY_INFO         ProxyInfo;
	DWORD                      cbProxyInfoSize = sizeof(ProxyInfo);

	const _TCHAR* Url_ = L"http://www.microsoft.com/ms.htm";
	if (argc > 0 && argv[1] && wcslen(argv[1]) > 0) {
		Url_ = argv[1];
	}

#define WINHTTP_DEBUG_INFO(FMT, ...) fprintf(stderr, "*INFO: " FMT "\n", ##__VA_ARGS__)
#define WINHTTP_DEBUG_ERROR(FMT, ...)  fprintf(stderr, "***ERROR: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nMSG: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__)

	
	WINHTTP_DEBUG_INFO("Testing auto-detect proxy for URL= %ls", Url_);

	hLibrary = LoadLibrary(L"winhttp.dll");
	if (!hLibrary) {
		WINHTTP_DEBUG_ERROR("LoadLibrary('winhttp.dll') failed: %ld", GetLastError());
		goto Exit;
	}
	WINHTTP_DEBUG_INFO("LoadLibrary('winhttp.dll') ok");

	ZeroMemory(&AutoProxyOptions, sizeof(AutoProxyOptions));
	ZeroMemory(&ProxyInfo, sizeof(ProxyInfo));

	pfWinHttpOpen WinHttpOpen_ = reinterpret_cast<pfWinHttpOpen>(GetProcAddress(hLibrary, "WinHttpOpen"));
	pfWinHttpConnect WinHttpConnect_ = reinterpret_cast<pfWinHttpConnect>(GetProcAddress(hLibrary, "WinHttpConnect"));
	pfWinHttpSetOption WinHttpSetOption_ = reinterpret_cast<pfWinHttpSetOption>(GetProcAddress(hLibrary, "WinHttpSetOption"));
	pfWinHttpOpenRequest WinHttpOpenRequest_ = reinterpret_cast<pfWinHttpOpenRequest>(GetProcAddress(hLibrary, "WinHttpOpenRequest"));
	pfWinHttpGetProxyForUrl WinHttpGetProxyForUrl_ = reinterpret_cast<pfWinHttpGetProxyForUrl>(GetProcAddress(hLibrary, "WinHttpGetProxyForUrl"));
	pfWinHttpSendRequest WinHttpSendRequest_ = reinterpret_cast<pfWinHttpSendRequest>(GetProcAddress(hLibrary, "WinHttpSendRequest"));
	pfWinHttpReceiveResponse WinHttpReceiveResponse_ = reinterpret_cast<pfWinHttpReceiveResponse>(GetProcAddress(hLibrary, "WinHttpReceiveResponse"));
	pfWinHttpCloseHandle WinHttpCloseHandle_ = reinterpret_cast<pfWinHttpCloseHandle>(GetProcAddress(hLibrary, "WinHttpCloseHandle"));
	
	//
	// Create the WinHTTP session.
	//
	hHttpSession = WinHttpOpen_(L"WinHTTP AutoProxy Sample/1.0",
		WINHTTP_ACCESS_TYPE_NO_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		0);

	// Exit if WinHttpOpen failed.
	if (!hHttpSession) {
		WINHTTP_DEBUG_ERROR("WinHttpOpen() failed: %ld", GetLastError());
		goto Exit;
	}

	//
	// Create the WinHTTP connect handle.
	//
	hConnect = WinHttpConnect_(hHttpSession,
		Url_,
		INTERNET_DEFAULT_HTTP_PORT,
		0);

	// Exit if WinHttpConnect failed.
	if (!hConnect) {
		WINHTTP_DEBUG_ERROR("WinHttpConnect() failed: %ld", GetLastError());
		goto Exit;
	}

	//
	// Create the HTTP request handle.
	//
	hRequest = WinHttpOpenRequest_(hConnect,
		L"GET",
		L"ms.htm",
		L"HTTP/1.1",
		WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES,
		0);

	// Exit if WinHttpOpenRequest failed.
	if (!hRequest) {
		WINHTTP_DEBUG_ERROR("WinHttpOpenRequest() failed: %ld", GetLastError());
		goto Exit;
	}

	//
	// Set up the autoproxy call.
	//

	// Use auto-detection because the Proxy 
	// Auto-Config URL is not known.
	AutoProxyOptions.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;

	// Use DHCP and DNS-based auto-detection.
	AutoProxyOptions.dwAutoDetectFlags =
		WINHTTP_AUTO_DETECT_TYPE_DHCP |
		WINHTTP_AUTO_DETECT_TYPE_DNS_A;

	// If obtaining the PAC script requires NTLM/Negotiate
	// authentication, then automatically supply the client
	// domain credentials.
	AutoProxyOptions.fAutoLogonIfChallenged = TRUE;

	//
	// Call WinHttpGetProxyForUrl with our target URL. If 
	// auto-proxy succeeds, then set the proxy info on the 
	// request handle. If auto-proxy fails, ignore the error 
	// and attempt to send the HTTP request directly to the 
	// target server (using the default WINHTTP_ACCESS_TYPE_NO_PROXY 
	// configuration, which the requesthandle will inherit 
	// from the session).
	//
	if (WinHttpGetProxyForUrl_(hHttpSession,
		L"http://www.microsoft.com/ms.htm",
		&AutoProxyOptions,
		&ProxyInfo))
	{
		// A proxy configuration was found, set it on the
		// request handle.
		WINHTTP_DEBUG_INFO("WinHttpGetProxyForUrl() returned TRUE");

		if (!WinHttpSetOption_(hRequest,
			WINHTTP_OPTION_PROXY,
			&ProxyInfo,
			cbProxyInfoSize))
		{
			// Exit if setting the proxy info failed.
			WINHTTP_DEBUG_ERROR("WinHttpSetOption() failed: %ld", GetLastError());
			goto Exit;
		}
	}
	else {
		WINHTTP_DEBUG_INFO("WinHttpGetProxyForUrl() returned FALSE");
	}

	//
	// Send the request.
	//
	if (!WinHttpSendRequest_(hRequest,
		WINHTTP_NO_ADDITIONAL_HEADERS,
		0,
		WINHTTP_NO_REQUEST_DATA,
		0,
		0,
		NULL))
	{
		// Exit if WinHttpSendRequest failed.
		WINHTTP_DEBUG_ERROR("WinHttpSendRequest() failed: %ld", GetLastError());
		goto Exit;
	}

	//
	// Wait for the response.
	//

	if (!WinHttpReceiveResponse_(hRequest, NULL)) {
		WINHTTP_DEBUG_ERROR("WinHttpReceiveResponse() failed: %ld", GetLastError());
		goto Exit;
	}

	//
	// A response has been received, then process it.
	// (omitted)
	//

	WINHTTP_DEBUG_INFO("///ProxyInfo/// lpszProxy=%ls, dwAccessType=%ld, lpszProxyBypass=%ls", ProxyInfo.lpszProxy, ProxyInfo.dwAccessType, ProxyInfo.lpszProxyBypass);

Exit:
	//
	// Clean up the WINHTTP_PROXY_INFO structure.
	//
	if (ProxyInfo.lpszProxy != NULL)
		GlobalFree(ProxyInfo.lpszProxy);

	if (ProxyInfo.lpszProxyBypass != NULL)
		GlobalFree(ProxyInfo.lpszProxyBypass);

	//
	// Close the WinHTTP handles.
	//
	if (hRequest != NULL)
		WinHttpCloseHandle_(hRequest);

	if (hConnect != NULL)
		WinHttpCloseHandle_(hConnect);

	if (hHttpSession != NULL)
		WinHttpCloseHandle_(hHttpSession);

	if (hLibrary != NULL)
		FreeLibrary(hLibrary);

	//WINHTTP_DEBUG_INFO("\n\n\n ***PRESS ANY KEY TO EXIT*** \n\n\n");
	//getchar();

	return ret;
}

#else

#if defined(_MSC_VER)
#	pragma comment(lib, "wininet.lib")
#	pragma comment(lib, "dnsapi.lib")
#	pragma comment(lib, "version.lib")
#	pragma comment(lib, "msimg32.lib")
#	pragma comment(lib, "ws2_32.lib")
#	pragma comment(lib, "usp10.lib")
#	pragma comment(lib, "psapi.lib")
#	pragma comment(lib, "dbghelp.lib")
#	pragma comment(lib, "winmm.lib")
#	pragma comment(lib, "shlwapi.lib")
#	pragma comment(lib, "kernel32.lib")
#	pragma comment(lib, "gdi32.lib")
#	pragma comment(lib, "winspool.lib")
#	pragma comment(lib, "comdlg32.lib")
#	pragma comment(lib, "advapi32.lib")
#	pragma comment(lib, "shell32.lib")
#	pragma comment(lib, "ole32.lib")
#	pragma comment(lib, "oleaut32.lib")
#	pragma comment(lib, "user32.lib")
#	pragma comment(lib, "uuid.lib")
#	pragma comment(lib, "odbc32.lib")
#	pragma comment(lib, "odbccp32.lib")
#	pragma comment(lib, "delayimp.lib")
#	pragma comment(lib, "credui.lib")
#	pragma comment(lib, "netapi32.lib")
#	pragma comment(lib, "Strmiids.lib")
#	pragma comment(lib, "crypt32.lib")
#	pragma comment(lib, "iphlpapi.lib")
#	pragma comment(lib, "secur32.lib")
#	pragma comment(lib, "dmoguids.lib")
#	pragma comment(lib, "wmcodecdspuuid.lib")
#	pragma comment(lib, "amstrmid.lib")
#	pragma comment(lib, "msdmo.lib")

#	pragma comment(lib, "obj\\third_party\\jsoncpp\\jsoncpp.lib")
#	pragma comment(lib, "obj\\talk\\libjingle_peerconnection.lib")
#	pragma comment(lib, "obj\\third_party\\expat\\expat.lib")
#	pragma comment(lib, "obj\\webrtc\\base\\rtc_base.lib")
#	pragma comment(lib, "obj\\webrtc\\webrtc_common.lib")
#	pragma comment(lib, "obj\\webrtc\\base\\rtc_base_approved.lib")
#	pragma comment(lib, "obj\\third_party\\boringssl\\boringssl.lib")
#	pragma comment(lib, "obj\\talk\\libjingle_media.lib")
#	pragma comment(lib, "libyuv.lib")
#	pragma comment(lib, "obj\\third_party\\libjpeg_turbo\\libjpeg.lib")
#	pragma comment(lib, "obj\\third_party\\usrsctp\\usrsctplib.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_render_module.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\webrtc_utility.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audio_coding_module.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\CNG.lib")
#	pragma comment(lib, "obj\\webrtc\\common_audio\\common_audio.lib")
#	pragma comment(lib, "obj\\webrtc\\system_wrappers\\system_wrappers.lib")
#	pragma comment(lib, "obj\\third_party\\openmax_dl\\dl\\openmax_dl.lib")
#	pragma comment(lib, "obj\\webrtc\\common_audio\\common_audio_sse2.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audio_encoder_interface.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\G711.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\G722.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\iLBC.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\iSAC.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audio_decoder_interface.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\iSACFix.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\PCM16B.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\red.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\webrtc_opus.lib")
#	pragma comment(lib, "obj\\third_party\\opus\\opus.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\neteq.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\media_file.lib")
#	pragma comment(lib, "obj\\webrtc\\common_video\\common_video.lib")
#	pragma comment(lib, "obj\\webrtc\\webrtc.lib")
#	pragma comment(lib, "obj\\webrtc\\video_engine\\video_engine_core.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\rtp_rtcp.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\paced_sender.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\remote_bitrate_estimator.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\bitrate_controller.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_capture_module.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\webrtc_video_coding.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\webrtc_i420.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_coding\\utility\\video_coding_utility.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_coding\\codecs\\vp8\\webrtc_vp8.lib")
#	pragma comment(lib, "obj\\third_party\\libvpx\\libvpx.lib")
#	pragma comment(lib, "obj\\third_party\\libvpx\\libvpx_intrinsics_mmx.lib")
#	pragma comment(lib, "obj\\third_party\\libvpx\\libvpx_intrinsics_sse2.lib")
#	pragma comment(lib, "obj\\third_party\\libvpx\\libvpx_intrinsics_ssse3.lib")
#	pragma comment(lib, "obj\\third_party\\libvpx\\libvpx_intrinsics_sse4_1.lib")
#	pragma comment(lib, "obj\\third_party\\libvpx\\libvpx_intrinsics_avx2.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_coding\\codecs\\vp9\\webrtc_vp9.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_processing.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_processing_sse2.lib")
#	pragma comment(lib, "obj\\webrtc\\voice_engine\\voice_engine.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audio_conference_mixer.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audio_processing.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audioproc_debug_proto.lib")
#	pragma comment(lib, "obj\\third_party\\protobuf\\protobuf_lite.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audio_processing_sse2.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\audio_device.lib")
#	pragma comment(lib, "obj\\webrtc\\sound\\rtc_sound.lib")
#	pragma comment(lib, "obj\\webrtc\\system_wrappers\\field_trial_default.lib")
#	pragma comment(lib, "obj\\webrtc\\system_wrappers\\metrics_default.lib")
#	pragma comment(lib, "obj\\webrtc\\libjingle\\xmllite\\rtc_xmllite.lib")
#	pragma comment(lib, "obj\\webrtc\\libjingle\\xmpp\\rtc_xmpp.lib")
#	pragma comment(lib, "obj\\webrtc\\p2p\\rtc_p2p.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_capture_module_internal_impl.lib")
#	pragma comment(lib, "obj\\third_party\\winsdk_samples\\directshow_baseclasses.lib")
#	pragma comment(lib, "obj\\webrtc\\modules\\video_render_module_internal_impl.lib")
#	pragma comment(lib, "obj\\talk\\libjingle_p2p.lib")
#	pragma comment(lib, "obj\\third_party\\libsrtp\\libsrtp.lib")

#endif

#include "webrtc/base/proxydetect.h"
#include "webrtc/base/logging.h"
#include "webrtc/base/ssladapter.h"
#include "webrtc/base/thread.h"
#include "webrtc/base/json.h"

#ifdef WIN32
#	include "webrtc/base/win32socketinit.h"
#	include "webrtc/base/win32socketserver.h"
#endif

#include <stdlib.h>

//
//	Proxy detection
//
int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;

	rtc::LogMessage::LogToDebug(rtc::LoggingSeverity::LS_INFO);
	rtc::LogMessage::LogContext(rtc::LoggingSeverity::LS_INFO);
	rtc::LogMessage::LogThreads(true);


#ifdef WIN32
	rtc::EnsureWinsockInit();
	static rtc::Win32Thread w32_thread;
	rtc::ThreadManager::Instance()->SetCurrentThread(&w32_thread);
#endif

#if WE_UNDER_MAC
#if 0 // NOT_USING_MAC_SERVER
	static rtc::MacCocoaSocketServer ss;
	static rtc::SocketServerScope ss_scope(&ss);
#endif
#endif

	rtc::InitializeSSL();
	rtc::InitializeSSLThread();

	std::string strUrl = "http://www.microsoft.com/ms.htm"; // "stun.inspectionworks.com";

	if (argc > 0 && argv[1] && wcslen(argv[1]) > 0) {
		int len = (int)wcslen(argv[1]);
		char* tmp = (char*)malloc(len + 1);
		tmp[len] = '\0';
		len = (int)wcstombs(tmp, argv[1], len);
		if (len > 0) {
			strUrl = std::string(tmp, len);
		}
		free(tmp);
	}
	
	rtc::ProxyInfo proxyInfo;

	if (rtc::GetProxySettingsForUrl("IE", strUrl.c_str(), &proxyInfo, false)) {
		LOG(LS_INFO) << "GetProxySettingsForUrl(" << strUrl << ") ok";
		LOG(LS_INFO) << "proxyInfo, toString() = " << proxyInfo.address.ToString() << ", type() = " << proxyInfo.type;
	}
	else {
		LOG(LS_ERROR) << "GetProxySettingsForUrl(" << strUrl << ") failed";
		goto bail;
	}

bail:
#ifdef WIN32
#endif
	rtc::CleanupSSL();

	//LOG(LS_INFO) << "\n\n\n ***PRESS ANY KEY TO EXIT*** \n\n\n";
	//getchar();

	LOG(LS_INFO) << "\n ----------------------------- \n";
	return ret;
}


#endif