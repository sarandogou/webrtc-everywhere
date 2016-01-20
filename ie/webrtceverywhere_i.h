

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jan 15 16:29:46 2016
 */
/* Compiler settings for webrtceverywhere.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __webrtceverywhere_i_h__
#define __webrtceverywhere_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWebRTC_FWD_DEFINED__
#define __IWebRTC_FWD_DEFINED__
typedef interface IWebRTC IWebRTC;

#endif 	/* __IWebRTC_FWD_DEFINED__ */


#ifndef __ISessionDescription_FWD_DEFINED__
#define __ISessionDescription_FWD_DEFINED__
typedef interface ISessionDescription ISessionDescription;

#endif 	/* __ISessionDescription_FWD_DEFINED__ */


#ifndef __IDictOptions_FWD_DEFINED__
#define __IDictOptions_FWD_DEFINED__
typedef interface IDictOptions IDictOptions;

#endif 	/* __IDictOptions_FWD_DEFINED__ */


#ifndef __IPeerConnection_FWD_DEFINED__
#define __IPeerConnection_FWD_DEFINED__
typedef interface IPeerConnection IPeerConnection;

#endif 	/* __IPeerConnection_FWD_DEFINED__ */


#ifndef __IMediaStream_FWD_DEFINED__
#define __IMediaStream_FWD_DEFINED__
typedef interface IMediaStream IMediaStream;

#endif 	/* __IMediaStream_FWD_DEFINED__ */


#ifndef __IRTCIceCandidate_FWD_DEFINED__
#define __IRTCIceCandidate_FWD_DEFINED__
typedef interface IRTCIceCandidate IRTCIceCandidate;

#endif 	/* __IRTCIceCandidate_FWD_DEFINED__ */


#ifndef __IMediaStreamTrack_FWD_DEFINED__
#define __IMediaStreamTrack_FWD_DEFINED__
typedef interface IMediaStreamTrack IMediaStreamTrack;

#endif 	/* __IMediaStreamTrack_FWD_DEFINED__ */


#ifndef __ISourceInfo_FWD_DEFINED__
#define __ISourceInfo_FWD_DEFINED__
typedef interface ISourceInfo ISourceInfo;

#endif 	/* __ISourceInfo_FWD_DEFINED__ */


#ifndef __IMediaSourceStates_FWD_DEFINED__
#define __IMediaSourceStates_FWD_DEFINED__
typedef interface IMediaSourceStates IMediaSourceStates;

#endif 	/* __IMediaSourceStates_FWD_DEFINED__ */


#ifndef __IMediaStreamEvent_FWD_DEFINED__
#define __IMediaStreamEvent_FWD_DEFINED__
typedef interface IMediaStreamEvent IMediaStreamEvent;

#endif 	/* __IMediaStreamEvent_FWD_DEFINED__ */


#ifndef __IRTCPeerConnectionIceEvent_FWD_DEFINED__
#define __IRTCPeerConnectionIceEvent_FWD_DEFINED__
typedef interface IRTCPeerConnectionIceEvent IRTCPeerConnectionIceEvent;

#endif 	/* __IRTCPeerConnectionIceEvent_FWD_DEFINED__ */


#ifndef __IRTCStatsReport_FWD_DEFINED__
#define __IRTCStatsReport_FWD_DEFINED__
typedef interface IRTCStatsReport IRTCStatsReport;

#endif 	/* __IRTCStatsReport_FWD_DEFINED__ */


#ifndef __IRTCStats_FWD_DEFINED__
#define __IRTCStats_FWD_DEFINED__
typedef interface IRTCStats IRTCStats;

#endif 	/* __IRTCStats_FWD_DEFINED__ */


#ifndef __IRTCDTMFSender_FWD_DEFINED__
#define __IRTCDTMFSender_FWD_DEFINED__
typedef interface IRTCDTMFSender IRTCDTMFSender;

#endif 	/* __IRTCDTMFSender_FWD_DEFINED__ */


#ifndef __IRTCDTMFToneChangeEvent_FWD_DEFINED__
#define __IRTCDTMFToneChangeEvent_FWD_DEFINED__
typedef interface IRTCDTMFToneChangeEvent IRTCDTMFToneChangeEvent;

#endif 	/* __IRTCDTMFToneChangeEvent_FWD_DEFINED__ */


#ifndef __IRTCDataChannel_FWD_DEFINED__
#define __IRTCDataChannel_FWD_DEFINED__
typedef interface IRTCDataChannel IRTCDataChannel;

#endif 	/* __IRTCDataChannel_FWD_DEFINED__ */


#ifndef __IMessageEvent_FWD_DEFINED__
#define __IMessageEvent_FWD_DEFINED__
typedef interface IMessageEvent IMessageEvent;

#endif 	/* __IMessageEvent_FWD_DEFINED__ */


#ifndef __IRTCDataChannelEvent_FWD_DEFINED__
#define __IRTCDataChannelEvent_FWD_DEFINED__
typedef interface IRTCDataChannelEvent IRTCDataChannelEvent;

#endif 	/* __IRTCDataChannelEvent_FWD_DEFINED__ */


#ifndef ___IWebRTCEvents_FWD_DEFINED__
#define ___IWebRTCEvents_FWD_DEFINED__
typedef interface _IWebRTCEvents _IWebRTCEvents;

#endif 	/* ___IWebRTCEvents_FWD_DEFINED__ */


#ifndef __WebRTC_FWD_DEFINED__
#define __WebRTC_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebRTC WebRTC;
#else
typedef struct WebRTC WebRTC;
#endif /* __cplusplus */

#endif 	/* __WebRTC_FWD_DEFINED__ */


#ifndef __SessionDescription_FWD_DEFINED__
#define __SessionDescription_FWD_DEFINED__

#ifdef __cplusplus
typedef class SessionDescription SessionDescription;
#else
typedef struct SessionDescription SessionDescription;
#endif /* __cplusplus */

#endif 	/* __SessionDescription_FWD_DEFINED__ */


#ifndef __DictOptions_FWD_DEFINED__
#define __DictOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DictOptions DictOptions;
#else
typedef struct DictOptions DictOptions;
#endif /* __cplusplus */

#endif 	/* __DictOptions_FWD_DEFINED__ */


#ifndef __PeerConnection_FWD_DEFINED__
#define __PeerConnection_FWD_DEFINED__

#ifdef __cplusplus
typedef class PeerConnection PeerConnection;
#else
typedef struct PeerConnection PeerConnection;
#endif /* __cplusplus */

#endif 	/* __PeerConnection_FWD_DEFINED__ */


#ifndef __MediaStream_FWD_DEFINED__
#define __MediaStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class MediaStream MediaStream;
#else
typedef struct MediaStream MediaStream;
#endif /* __cplusplus */

#endif 	/* __MediaStream_FWD_DEFINED__ */


#ifndef __RTCIceCandidate_FWD_DEFINED__
#define __RTCIceCandidate_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCIceCandidate RTCIceCandidate;
#else
typedef struct RTCIceCandidate RTCIceCandidate;
#endif /* __cplusplus */

#endif 	/* __RTCIceCandidate_FWD_DEFINED__ */


#ifndef __MediaStreamTrack_FWD_DEFINED__
#define __MediaStreamTrack_FWD_DEFINED__

#ifdef __cplusplus
typedef class MediaStreamTrack MediaStreamTrack;
#else
typedef struct MediaStreamTrack MediaStreamTrack;
#endif /* __cplusplus */

#endif 	/* __MediaStreamTrack_FWD_DEFINED__ */


#ifndef __SourceInfo_FWD_DEFINED__
#define __SourceInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class SourceInfo SourceInfo;
#else
typedef struct SourceInfo SourceInfo;
#endif /* __cplusplus */

#endif 	/* __SourceInfo_FWD_DEFINED__ */


#ifndef __MediaSourceStates_FWD_DEFINED__
#define __MediaSourceStates_FWD_DEFINED__

#ifdef __cplusplus
typedef class MediaSourceStates MediaSourceStates;
#else
typedef struct MediaSourceStates MediaSourceStates;
#endif /* __cplusplus */

#endif 	/* __MediaSourceStates_FWD_DEFINED__ */


#ifndef __MediaStreamEvent_FWD_DEFINED__
#define __MediaStreamEvent_FWD_DEFINED__

#ifdef __cplusplus
typedef class MediaStreamEvent MediaStreamEvent;
#else
typedef struct MediaStreamEvent MediaStreamEvent;
#endif /* __cplusplus */

#endif 	/* __MediaStreamEvent_FWD_DEFINED__ */


#ifndef __RTCPeerConnectionIceEvent_FWD_DEFINED__
#define __RTCPeerConnectionIceEvent_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCPeerConnectionIceEvent RTCPeerConnectionIceEvent;
#else
typedef struct RTCPeerConnectionIceEvent RTCPeerConnectionIceEvent;
#endif /* __cplusplus */

#endif 	/* __RTCPeerConnectionIceEvent_FWD_DEFINED__ */


#ifndef __RTCStatsReport_FWD_DEFINED__
#define __RTCStatsReport_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCStatsReport RTCStatsReport;
#else
typedef struct RTCStatsReport RTCStatsReport;
#endif /* __cplusplus */

#endif 	/* __RTCStatsReport_FWD_DEFINED__ */


#ifndef __RTCStats_FWD_DEFINED__
#define __RTCStats_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCStats RTCStats;
#else
typedef struct RTCStats RTCStats;
#endif /* __cplusplus */

#endif 	/* __RTCStats_FWD_DEFINED__ */


#ifndef __RTCDTMFSender_FWD_DEFINED__
#define __RTCDTMFSender_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCDTMFSender RTCDTMFSender;
#else
typedef struct RTCDTMFSender RTCDTMFSender;
#endif /* __cplusplus */

#endif 	/* __RTCDTMFSender_FWD_DEFINED__ */


#ifndef __RTCDTMFToneChangeEvent_FWD_DEFINED__
#define __RTCDTMFToneChangeEvent_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCDTMFToneChangeEvent RTCDTMFToneChangeEvent;
#else
typedef struct RTCDTMFToneChangeEvent RTCDTMFToneChangeEvent;
#endif /* __cplusplus */

#endif 	/* __RTCDTMFToneChangeEvent_FWD_DEFINED__ */


#ifndef __RTCDataChannel_FWD_DEFINED__
#define __RTCDataChannel_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCDataChannel RTCDataChannel;
#else
typedef struct RTCDataChannel RTCDataChannel;
#endif /* __cplusplus */

#endif 	/* __RTCDataChannel_FWD_DEFINED__ */


#ifndef __MessageEvent_FWD_DEFINED__
#define __MessageEvent_FWD_DEFINED__

#ifdef __cplusplus
typedef class MessageEvent MessageEvent;
#else
typedef struct MessageEvent MessageEvent;
#endif /* __cplusplus */

#endif 	/* __MessageEvent_FWD_DEFINED__ */


#ifndef __RTCDataChannelEvent_FWD_DEFINED__
#define __RTCDataChannelEvent_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTCDataChannelEvent RTCDataChannelEvent;
#else
typedef struct RTCDataChannelEvent RTCDataChannelEvent;
#endif /* __cplusplus */

#endif 	/* __RTCDataChannelEvent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWebRTC_INTERFACE_DEFINED__
#define __IWebRTC_INTERFACE_DEFINED__

/* interface IWebRTC */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebRTC;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4994FB92-A5F5-4292-AB60-472AA4937C9E")
    IWebRTC : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_versionName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getUserMedia( 
            /* [optional][in] */ VARIANT constraints,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT errorCallback) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getWindowList( 
            /* [retval][out] */ BSTR *winList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createDisplay( 
            /* [retval][out] */ IDispatch **ppDisplay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createSessionDescription( 
            /* [in] */ VARIANT RTCSessionDescriptionInit,
            /* [retval][out] */ IDispatch **ppSdp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createDictOptions( 
            /* [retval][out] */ IDispatch **ppDictOptions) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createPeerConnection( 
            /* [optional][in] */ VARIANT RTCConfiguration,
            /* [optional][in] */ VARIANT MediaConstraints,
            /* [retval][out] */ IDispatch **ppPeerConnection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createIceCandidate( 
            /* [in] */ VARIANT RTCIceCandidateInit,
            /* [retval][out] */ IDispatch **ppIceCandidate) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createMediaStreamTrack( 
            /* [retval][out] */ IDispatch **ppMediaStreamTrack) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE bindEventListener( 
            /* [in] */ BSTR type,
            /* [optional][in] */ VARIANT listenerCallback,
            /* [optional][in] */ VARIANT useCapture) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSources( 
            /* [optional][in] */ VARIANT successCallback) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_src( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_videoWidth( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_videoHeight( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fillImageData( 
            /* [in] */ VARIANT imageData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getScreenShot( 
            /* [retval][out] */ BSTR *base64BitmapData) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_isWebRtcPlugin( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWebRTCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebRTC * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebRTC * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebRTC * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebRTC * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebRTC * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebRTC * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebRTC * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_versionName )( 
            IWebRTC * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getUserMedia )( 
            IWebRTC * This,
            /* [optional][in] */ VARIANT constraints,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT errorCallback);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getWindowList )( 
            IWebRTC * This,
            /* [retval][out] */ BSTR *winList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createDisplay )( 
            IWebRTC * This,
            /* [retval][out] */ IDispatch **ppDisplay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createSessionDescription )( 
            IWebRTC * This,
            /* [in] */ VARIANT RTCSessionDescriptionInit,
            /* [retval][out] */ IDispatch **ppSdp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createDictOptions )( 
            IWebRTC * This,
            /* [retval][out] */ IDispatch **ppDictOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createPeerConnection )( 
            IWebRTC * This,
            /* [optional][in] */ VARIANT RTCConfiguration,
            /* [optional][in] */ VARIANT MediaConstraints,
            /* [retval][out] */ IDispatch **ppPeerConnection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createIceCandidate )( 
            IWebRTC * This,
            /* [in] */ VARIANT RTCIceCandidateInit,
            /* [retval][out] */ IDispatch **ppIceCandidate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createMediaStreamTrack )( 
            IWebRTC * This,
            /* [retval][out] */ IDispatch **ppMediaStreamTrack);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *bindEventListener )( 
            IWebRTC * This,
            /* [in] */ BSTR type,
            /* [optional][in] */ VARIANT listenerCallback,
            /* [optional][in] */ VARIANT useCapture);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getSources )( 
            IWebRTC * This,
            /* [optional][in] */ VARIANT successCallback);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_src )( 
            IWebRTC * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_videoWidth )( 
            IWebRTC * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_videoHeight )( 
            IWebRTC * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fillImageData )( 
            IWebRTC * This,
            /* [in] */ VARIANT imageData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getScreenShot )( 
            IWebRTC * This,
            /* [retval][out] */ BSTR *base64BitmapData);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_isWebRtcPlugin )( 
            IWebRTC * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IWebRTCVtbl;

    interface IWebRTC
    {
        CONST_VTBL struct IWebRTCVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebRTC_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWebRTC_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWebRTC_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWebRTC_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWebRTC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWebRTC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWebRTC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWebRTC_get_versionName(This,pVal)	\
    ( (This)->lpVtbl -> get_versionName(This,pVal) ) 

#define IWebRTC_getUserMedia(This,constraints,successCallback,errorCallback)	\
    ( (This)->lpVtbl -> getUserMedia(This,constraints,successCallback,errorCallback) ) 

#define IWebRTC_getWindowList(This,winList)	\
    ( (This)->lpVtbl -> getWindowList(This,winList) ) 

#define IWebRTC_createDisplay(This,ppDisplay)	\
    ( (This)->lpVtbl -> createDisplay(This,ppDisplay) ) 

#define IWebRTC_createSessionDescription(This,RTCSessionDescriptionInit,ppSdp)	\
    ( (This)->lpVtbl -> createSessionDescription(This,RTCSessionDescriptionInit,ppSdp) ) 

#define IWebRTC_createDictOptions(This,ppDictOptions)	\
    ( (This)->lpVtbl -> createDictOptions(This,ppDictOptions) ) 

#define IWebRTC_createPeerConnection(This,RTCConfiguration,MediaConstraints,ppPeerConnection)	\
    ( (This)->lpVtbl -> createPeerConnection(This,RTCConfiguration,MediaConstraints,ppPeerConnection) ) 

#define IWebRTC_createIceCandidate(This,RTCIceCandidateInit,ppIceCandidate)	\
    ( (This)->lpVtbl -> createIceCandidate(This,RTCIceCandidateInit,ppIceCandidate) ) 

#define IWebRTC_createMediaStreamTrack(This,ppMediaStreamTrack)	\
    ( (This)->lpVtbl -> createMediaStreamTrack(This,ppMediaStreamTrack) ) 

#define IWebRTC_bindEventListener(This,type,listenerCallback,useCapture)	\
    ( (This)->lpVtbl -> bindEventListener(This,type,listenerCallback,useCapture) ) 

#define IWebRTC_getSources(This,successCallback)	\
    ( (This)->lpVtbl -> getSources(This,successCallback) ) 

#define IWebRTC_put_src(This,newVal)	\
    ( (This)->lpVtbl -> put_src(This,newVal) ) 

#define IWebRTC_get_videoWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_videoWidth(This,pVal) ) 

#define IWebRTC_get_videoHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_videoHeight(This,pVal) ) 

#define IWebRTC_fillImageData(This,imageData)	\
    ( (This)->lpVtbl -> fillImageData(This,imageData) ) 

#define IWebRTC_getScreenShot(This,base64BitmapData)	\
    ( (This)->lpVtbl -> getScreenShot(This,base64BitmapData) ) 

#define IWebRTC_get_isWebRtcPlugin(This,pVal)	\
    ( (This)->lpVtbl -> get_isWebRtcPlugin(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWebRTC_INTERFACE_DEFINED__ */


#ifndef __ISessionDescription_INTERFACE_DEFINED__
#define __ISessionDescription_INTERFACE_DEFINED__

/* interface ISessionDescription */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISessionDescription;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7CFEF92-42B8-40FB-BCA9-E79D39ABCF72")
    ISessionDescription : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_type( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sdp( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sdp( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISessionDescriptionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISessionDescription * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISessionDescription * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISessionDescription * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISessionDescription * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISessionDescription * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISessionDescription * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISessionDescription * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_type )( 
            ISessionDescription * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_type )( 
            ISessionDescription * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sdp )( 
            ISessionDescription * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_sdp )( 
            ISessionDescription * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ISessionDescriptionVtbl;

    interface ISessionDescription
    {
        CONST_VTBL struct ISessionDescriptionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISessionDescription_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISessionDescription_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISessionDescription_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISessionDescription_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISessionDescription_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISessionDescription_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISessionDescription_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISessionDescription_get_type(This,pVal)	\
    ( (This)->lpVtbl -> get_type(This,pVal) ) 

#define ISessionDescription_put_type(This,newVal)	\
    ( (This)->lpVtbl -> put_type(This,newVal) ) 

#define ISessionDescription_get_sdp(This,pVal)	\
    ( (This)->lpVtbl -> get_sdp(This,pVal) ) 

#define ISessionDescription_put_sdp(This,newVal)	\
    ( (This)->lpVtbl -> put_sdp(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISessionDescription_INTERFACE_DEFINED__ */


#ifndef __IDictOptions_INTERFACE_DEFINED__
#define __IDictOptions_INTERFACE_DEFINED__

/* interface IDictOptions */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDictOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FA4B099C-3A15-4659-B288-565AD5258D4B")
    IDictOptions : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IDictOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDictOptions * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDictOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDictOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDictOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDictOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDictOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDictOptions * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IDictOptionsVtbl;

    interface IDictOptions
    {
        CONST_VTBL struct IDictOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDictOptions_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDictOptions_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDictOptions_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDictOptions_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDictOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDictOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDictOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDictOptions_INTERFACE_DEFINED__ */


#ifndef __IPeerConnection_INTERFACE_DEFINED__
#define __IPeerConnection_INTERFACE_DEFINED__

/* interface IPeerConnection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPeerConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("462E3805-373B-46EE-9BEE-43E6110CB751")
    IPeerConnection : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createOffer( 
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback,
            /* [optional][in] */ VARIANT MediaConstraints) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createAnswer( 
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback,
            /* [optional][in] */ VARIANT MediaConstraints) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setLocalDescription( 
            /* [in] */ VARIANT RTCSessionDescription,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_localDescription( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setRemoteDescription( 
            /* [in] */ VARIANT RTCSessionDescription,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_remoteDescription( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_signalingState( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE updateIce( 
            /* [in] */ VARIANT RTCConfiguration,
            /* [optional][in] */ VARIANT MediaConstraints) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addIceCandidate( 
            /* [in] */ VARIANT RTCIceCandidate,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_iceGatheringState( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_iceConnectionState( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLocalStreams( 
            /* [retval][out] */ VARIANT *MediaStreams) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getRemoteStreams( 
            /* [retval][out] */ VARIANT *MediaStreams) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getStreamById( 
            /* [in] */ BSTR streamId,
            /* [retval][out] */ VARIANT *MediaStream) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addStream( 
            /* [in] */ VARIANT stream,
            /* [optional][in] */ VARIANT MediaConstraints) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeStream( 
            /* [in] */ VARIANT stream) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getStats( 
            /* [in] */ VARIANT selector,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createDTMFSender( 
            /* [in] */ VARIANT MediaStreamTrack,
            /* [retval][out] */ VARIANT *RTCDTMFSender) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createDataChannel( 
            /* [in] */ BSTR label,
            /* [optional][in] */ VARIANT dataChannelDict,
            /* [retval][out] */ VARIANT *DataChannel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onnegotiationneeded( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onnegotiationneeded( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onicecandidate( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onicecandidate( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onsignalingstatechange( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onsignalingstatechange( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onaddstream( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onaddstream( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onremovestream( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onremovestream( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_oniceconnectionstatechange( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_oniceconnectionstatechange( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ondatachannel( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ondatachannel( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPeerConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPeerConnection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPeerConnection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPeerConnection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPeerConnection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPeerConnection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPeerConnection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPeerConnection * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createOffer )( 
            IPeerConnection * This,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback,
            /* [optional][in] */ VARIANT MediaConstraints);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createAnswer )( 
            IPeerConnection * This,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback,
            /* [optional][in] */ VARIANT MediaConstraints);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setLocalDescription )( 
            IPeerConnection * This,
            /* [in] */ VARIANT RTCSessionDescription,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_localDescription )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setRemoteDescription )( 
            IPeerConnection * This,
            /* [in] */ VARIANT RTCSessionDescription,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_remoteDescription )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_signalingState )( 
            IPeerConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *updateIce )( 
            IPeerConnection * This,
            /* [in] */ VARIANT RTCConfiguration,
            /* [optional][in] */ VARIANT MediaConstraints);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addIceCandidate )( 
            IPeerConnection * This,
            /* [in] */ VARIANT RTCIceCandidate,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_iceGatheringState )( 
            IPeerConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_iceConnectionState )( 
            IPeerConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLocalStreams )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *MediaStreams);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getRemoteStreams )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *MediaStreams);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getStreamById )( 
            IPeerConnection * This,
            /* [in] */ BSTR streamId,
            /* [retval][out] */ VARIANT *MediaStream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addStream )( 
            IPeerConnection * This,
            /* [in] */ VARIANT stream,
            /* [optional][in] */ VARIANT MediaConstraints);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeStream )( 
            IPeerConnection * This,
            /* [in] */ VARIANT stream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *close )( 
            IPeerConnection * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getStats )( 
            IPeerConnection * This,
            /* [in] */ VARIANT selector,
            /* [optional][in] */ VARIANT successCallback,
            /* [optional][in] */ VARIANT failureCallback);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createDTMFSender )( 
            IPeerConnection * This,
            /* [in] */ VARIANT MediaStreamTrack,
            /* [retval][out] */ VARIANT *RTCDTMFSender);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *createDataChannel )( 
            IPeerConnection * This,
            /* [in] */ BSTR label,
            /* [optional][in] */ VARIANT dataChannelDict,
            /* [retval][out] */ VARIANT *DataChannel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onnegotiationneeded )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onnegotiationneeded )( 
            IPeerConnection * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onicecandidate )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onicecandidate )( 
            IPeerConnection * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onsignalingstatechange )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onsignalingstatechange )( 
            IPeerConnection * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onaddstream )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onaddstream )( 
            IPeerConnection * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onremovestream )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onremovestream )( 
            IPeerConnection * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_oniceconnectionstatechange )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_oniceconnectionstatechange )( 
            IPeerConnection * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ondatachannel )( 
            IPeerConnection * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ondatachannel )( 
            IPeerConnection * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IPeerConnectionVtbl;

    interface IPeerConnection
    {
        CONST_VTBL struct IPeerConnectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPeerConnection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPeerConnection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPeerConnection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPeerConnection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPeerConnection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPeerConnection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPeerConnection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPeerConnection_createOffer(This,successCallback,failureCallback,MediaConstraints)	\
    ( (This)->lpVtbl -> createOffer(This,successCallback,failureCallback,MediaConstraints) ) 

#define IPeerConnection_createAnswer(This,successCallback,failureCallback,MediaConstraints)	\
    ( (This)->lpVtbl -> createAnswer(This,successCallback,failureCallback,MediaConstraints) ) 

#define IPeerConnection_setLocalDescription(This,RTCSessionDescription,successCallback,failureCallback)	\
    ( (This)->lpVtbl -> setLocalDescription(This,RTCSessionDescription,successCallback,failureCallback) ) 

#define IPeerConnection_get_localDescription(This,pVal)	\
    ( (This)->lpVtbl -> get_localDescription(This,pVal) ) 

#define IPeerConnection_setRemoteDescription(This,RTCSessionDescription,successCallback,failureCallback)	\
    ( (This)->lpVtbl -> setRemoteDescription(This,RTCSessionDescription,successCallback,failureCallback) ) 

#define IPeerConnection_get_remoteDescription(This,pVal)	\
    ( (This)->lpVtbl -> get_remoteDescription(This,pVal) ) 

#define IPeerConnection_get_signalingState(This,pVal)	\
    ( (This)->lpVtbl -> get_signalingState(This,pVal) ) 

#define IPeerConnection_updateIce(This,RTCConfiguration,MediaConstraints)	\
    ( (This)->lpVtbl -> updateIce(This,RTCConfiguration,MediaConstraints) ) 

#define IPeerConnection_addIceCandidate(This,RTCIceCandidate,successCallback,failureCallback)	\
    ( (This)->lpVtbl -> addIceCandidate(This,RTCIceCandidate,successCallback,failureCallback) ) 

#define IPeerConnection_get_iceGatheringState(This,pVal)	\
    ( (This)->lpVtbl -> get_iceGatheringState(This,pVal) ) 

#define IPeerConnection_get_iceConnectionState(This,pVal)	\
    ( (This)->lpVtbl -> get_iceConnectionState(This,pVal) ) 

#define IPeerConnection_getLocalStreams(This,MediaStreams)	\
    ( (This)->lpVtbl -> getLocalStreams(This,MediaStreams) ) 

#define IPeerConnection_getRemoteStreams(This,MediaStreams)	\
    ( (This)->lpVtbl -> getRemoteStreams(This,MediaStreams) ) 

#define IPeerConnection_getStreamById(This,streamId,MediaStream)	\
    ( (This)->lpVtbl -> getStreamById(This,streamId,MediaStream) ) 

#define IPeerConnection_addStream(This,stream,MediaConstraints)	\
    ( (This)->lpVtbl -> addStream(This,stream,MediaConstraints) ) 

#define IPeerConnection_removeStream(This,stream)	\
    ( (This)->lpVtbl -> removeStream(This,stream) ) 

#define IPeerConnection_close(This)	\
    ( (This)->lpVtbl -> close(This) ) 

#define IPeerConnection_getStats(This,selector,successCallback,failureCallback)	\
    ( (This)->lpVtbl -> getStats(This,selector,successCallback,failureCallback) ) 

#define IPeerConnection_createDTMFSender(This,MediaStreamTrack,RTCDTMFSender)	\
    ( (This)->lpVtbl -> createDTMFSender(This,MediaStreamTrack,RTCDTMFSender) ) 

#define IPeerConnection_createDataChannel(This,label,dataChannelDict,DataChannel)	\
    ( (This)->lpVtbl -> createDataChannel(This,label,dataChannelDict,DataChannel) ) 

#define IPeerConnection_get_onnegotiationneeded(This,pVal)	\
    ( (This)->lpVtbl -> get_onnegotiationneeded(This,pVal) ) 

#define IPeerConnection_put_onnegotiationneeded(This,newVal)	\
    ( (This)->lpVtbl -> put_onnegotiationneeded(This,newVal) ) 

#define IPeerConnection_get_onicecandidate(This,pVal)	\
    ( (This)->lpVtbl -> get_onicecandidate(This,pVal) ) 

#define IPeerConnection_put_onicecandidate(This,newVal)	\
    ( (This)->lpVtbl -> put_onicecandidate(This,newVal) ) 

#define IPeerConnection_get_onsignalingstatechange(This,pVal)	\
    ( (This)->lpVtbl -> get_onsignalingstatechange(This,pVal) ) 

#define IPeerConnection_put_onsignalingstatechange(This,newVal)	\
    ( (This)->lpVtbl -> put_onsignalingstatechange(This,newVal) ) 

#define IPeerConnection_get_onaddstream(This,pVal)	\
    ( (This)->lpVtbl -> get_onaddstream(This,pVal) ) 

#define IPeerConnection_put_onaddstream(This,newVal)	\
    ( (This)->lpVtbl -> put_onaddstream(This,newVal) ) 

#define IPeerConnection_get_onremovestream(This,pVal)	\
    ( (This)->lpVtbl -> get_onremovestream(This,pVal) ) 

#define IPeerConnection_put_onremovestream(This,newVal)	\
    ( (This)->lpVtbl -> put_onremovestream(This,newVal) ) 

#define IPeerConnection_get_oniceconnectionstatechange(This,pVal)	\
    ( (This)->lpVtbl -> get_oniceconnectionstatechange(This,pVal) ) 

#define IPeerConnection_put_oniceconnectionstatechange(This,newVal)	\
    ( (This)->lpVtbl -> put_oniceconnectionstatechange(This,newVal) ) 

#define IPeerConnection_get_ondatachannel(This,pVal)	\
    ( (This)->lpVtbl -> get_ondatachannel(This,pVal) ) 

#define IPeerConnection_put_ondatachannel(This,newVal)	\
    ( (This)->lpVtbl -> put_ondatachannel(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPeerConnection_INTERFACE_DEFINED__ */


#ifndef __IMediaStream_INTERFACE_DEFINED__
#define __IMediaStream_INTERFACE_DEFINED__

/* interface IMediaStream */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21745AC4-2C31-481C-AB07-834C4D0E287A")
    IMediaStream : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_id( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getAudioTracks( 
            /* [retval][out] */ VARIANT *Tracks) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVideoTracks( 
            /* [retval][out] */ VARIANT *Tracks) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTracks( 
            /* [retval][out] */ VARIANT *Tracks) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTrackById( 
            /* [in] */ BSTR trackId,
            /* [retval][out] */ VARIANT *MediaStreamTrack) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addTrack( 
            /* [in] */ VARIANT MediaStreamTrack) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeTrack( 
            /* [in] */ VARIANT MediaStreamTrack) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ VARIANT *MediaStream) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ended( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onended( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onended( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onaddtrack( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onaddtrack( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onremovetrack( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onremovetrack( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stop( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaStream * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaStream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMediaStream * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMediaStream * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMediaStream * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMediaStream * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_id )( 
            IMediaStream * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getAudioTracks )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT *Tracks);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getVideoTracks )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT *Tracks);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTracks )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT *Tracks);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTrackById )( 
            IMediaStream * This,
            /* [in] */ BSTR trackId,
            /* [retval][out] */ VARIANT *MediaStreamTrack);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addTrack )( 
            IMediaStream * This,
            /* [in] */ VARIANT MediaStreamTrack);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeTrack )( 
            IMediaStream * This,
            /* [in] */ VARIANT MediaStreamTrack);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *clone )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT *MediaStream);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ended )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onended )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onended )( 
            IMediaStream * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onaddtrack )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onaddtrack )( 
            IMediaStream * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onremovetrack )( 
            IMediaStream * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onremovetrack )( 
            IMediaStream * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stop )( 
            IMediaStream * This);
        
        END_INTERFACE
    } IMediaStreamVtbl;

    interface IMediaStream
    {
        CONST_VTBL struct IMediaStreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaStream_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMediaStream_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMediaStream_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMediaStream_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMediaStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMediaStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMediaStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMediaStream_get_id(This,pVal)	\
    ( (This)->lpVtbl -> get_id(This,pVal) ) 

#define IMediaStream_getAudioTracks(This,Tracks)	\
    ( (This)->lpVtbl -> getAudioTracks(This,Tracks) ) 

#define IMediaStream_getVideoTracks(This,Tracks)	\
    ( (This)->lpVtbl -> getVideoTracks(This,Tracks) ) 

#define IMediaStream_getTracks(This,Tracks)	\
    ( (This)->lpVtbl -> getTracks(This,Tracks) ) 

#define IMediaStream_getTrackById(This,trackId,MediaStreamTrack)	\
    ( (This)->lpVtbl -> getTrackById(This,trackId,MediaStreamTrack) ) 

#define IMediaStream_addTrack(This,MediaStreamTrack)	\
    ( (This)->lpVtbl -> addTrack(This,MediaStreamTrack) ) 

#define IMediaStream_removeTrack(This,MediaStreamTrack)	\
    ( (This)->lpVtbl -> removeTrack(This,MediaStreamTrack) ) 

#define IMediaStream_clone(This,MediaStream)	\
    ( (This)->lpVtbl -> clone(This,MediaStream) ) 

#define IMediaStream_get_ended(This,pVal)	\
    ( (This)->lpVtbl -> get_ended(This,pVal) ) 

#define IMediaStream_get_onended(This,pVal)	\
    ( (This)->lpVtbl -> get_onended(This,pVal) ) 

#define IMediaStream_put_onended(This,newVal)	\
    ( (This)->lpVtbl -> put_onended(This,newVal) ) 

#define IMediaStream_get_onaddtrack(This,pVal)	\
    ( (This)->lpVtbl -> get_onaddtrack(This,pVal) ) 

#define IMediaStream_put_onaddtrack(This,newVal)	\
    ( (This)->lpVtbl -> put_onaddtrack(This,newVal) ) 

#define IMediaStream_get_onremovetrack(This,pVal)	\
    ( (This)->lpVtbl -> get_onremovetrack(This,pVal) ) 

#define IMediaStream_put_onremovetrack(This,newVal)	\
    ( (This)->lpVtbl -> put_onremovetrack(This,newVal) ) 

#define IMediaStream_stop(This)	\
    ( (This)->lpVtbl -> stop(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMediaStream_INTERFACE_DEFINED__ */


#ifndef __IRTCIceCandidate_INTERFACE_DEFINED__
#define __IRTCIceCandidate_INTERFACE_DEFINED__

/* interface IRTCIceCandidate */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCIceCandidate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FBE8F87D-BD47-4325-9196-7A36F339EE2A")
    IRTCIceCandidate : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_candidate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_sdpMid( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_sdpMLineIndex( 
            /* [retval][out] */ USHORT *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCIceCandidateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCIceCandidate * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCIceCandidate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCIceCandidate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCIceCandidate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCIceCandidate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCIceCandidate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCIceCandidate * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_candidate )( 
            IRTCIceCandidate * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sdpMid )( 
            IRTCIceCandidate * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sdpMLineIndex )( 
            IRTCIceCandidate * This,
            /* [retval][out] */ USHORT *pVal);
        
        END_INTERFACE
    } IRTCIceCandidateVtbl;

    interface IRTCIceCandidate
    {
        CONST_VTBL struct IRTCIceCandidateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCIceCandidate_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCIceCandidate_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCIceCandidate_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCIceCandidate_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCIceCandidate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCIceCandidate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCIceCandidate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCIceCandidate_get_candidate(This,pVal)	\
    ( (This)->lpVtbl -> get_candidate(This,pVal) ) 

#define IRTCIceCandidate_get_sdpMid(This,pVal)	\
    ( (This)->lpVtbl -> get_sdpMid(This,pVal) ) 

#define IRTCIceCandidate_get_sdpMLineIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_sdpMLineIndex(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCIceCandidate_INTERFACE_DEFINED__ */


#ifndef __IMediaStreamTrack_INTERFACE_DEFINED__
#define __IMediaStreamTrack_INTERFACE_DEFINED__

/* interface IMediaStreamTrack */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMediaStreamTrack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDD26AE0-B068-4918-826D-E75BBE844B71")
    IMediaStreamTrack : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_kind( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_id( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_label( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_enabled( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_enabled( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_muted( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onmute( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onmute( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onunmute( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onunmute( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_readonly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_remote( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_readyState( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onstarted( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onstarted( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onended( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onended( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSourceInfos( 
            /* [retval][out] */ VARIANT *Infos) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE constraints( 
            /* [retval][out] */ VARIANT *MediaTrackConstraints) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE states( 
            /* [retval][out] */ VARIANT *MediaSourceStates) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE capabilities( 
            /* [retval][out] */ VARIANT *AllCapabilities) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE applyConstraints( 
            /* [in] */ VARIANT MediaTrackConstraints) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onoverconstrained( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onoverconstrained( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ VARIANT *MediaStreamTrack) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stop( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMediaStreamTrackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaStreamTrack * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaStreamTrack * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaStreamTrack * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMediaStreamTrack * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMediaStreamTrack * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMediaStreamTrack * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMediaStreamTrack * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_kind )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_id )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_label )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_enabled )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_enabled )( 
            IMediaStreamTrack * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_muted )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onmute )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onmute )( 
            IMediaStreamTrack * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onunmute )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onunmute )( 
            IMediaStreamTrack * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_readonly )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_remote )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_readyState )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onstarted )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onstarted )( 
            IMediaStreamTrack * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onended )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onended )( 
            IMediaStreamTrack * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getSourceInfos )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *Infos);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *constraints )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *MediaTrackConstraints);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *states )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *MediaSourceStates);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *capabilities )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *AllCapabilities);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *applyConstraints )( 
            IMediaStreamTrack * This,
            /* [in] */ VARIANT MediaTrackConstraints);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onoverconstrained )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onoverconstrained )( 
            IMediaStreamTrack * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *clone )( 
            IMediaStreamTrack * This,
            /* [retval][out] */ VARIANT *MediaStreamTrack);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stop )( 
            IMediaStreamTrack * This);
        
        END_INTERFACE
    } IMediaStreamTrackVtbl;

    interface IMediaStreamTrack
    {
        CONST_VTBL struct IMediaStreamTrackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaStreamTrack_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMediaStreamTrack_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMediaStreamTrack_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMediaStreamTrack_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMediaStreamTrack_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMediaStreamTrack_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMediaStreamTrack_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMediaStreamTrack_get_kind(This,pVal)	\
    ( (This)->lpVtbl -> get_kind(This,pVal) ) 

#define IMediaStreamTrack_get_id(This,pVal)	\
    ( (This)->lpVtbl -> get_id(This,pVal) ) 

#define IMediaStreamTrack_get_label(This,pVal)	\
    ( (This)->lpVtbl -> get_label(This,pVal) ) 

#define IMediaStreamTrack_get_enabled(This,pVal)	\
    ( (This)->lpVtbl -> get_enabled(This,pVal) ) 

#define IMediaStreamTrack_put_enabled(This,newVal)	\
    ( (This)->lpVtbl -> put_enabled(This,newVal) ) 

#define IMediaStreamTrack_get_muted(This,pVal)	\
    ( (This)->lpVtbl -> get_muted(This,pVal) ) 

#define IMediaStreamTrack_get_onmute(This,pVal)	\
    ( (This)->lpVtbl -> get_onmute(This,pVal) ) 

#define IMediaStreamTrack_put_onmute(This,newVal)	\
    ( (This)->lpVtbl -> put_onmute(This,newVal) ) 

#define IMediaStreamTrack_get_onunmute(This,pVal)	\
    ( (This)->lpVtbl -> get_onunmute(This,pVal) ) 

#define IMediaStreamTrack_put_onunmute(This,newVal)	\
    ( (This)->lpVtbl -> put_onunmute(This,newVal) ) 

#define IMediaStreamTrack_get_readonly(This,pVal)	\
    ( (This)->lpVtbl -> get_readonly(This,pVal) ) 

#define IMediaStreamTrack_get_remote(This,pVal)	\
    ( (This)->lpVtbl -> get_remote(This,pVal) ) 

#define IMediaStreamTrack_get_readyState(This,pVal)	\
    ( (This)->lpVtbl -> get_readyState(This,pVal) ) 

#define IMediaStreamTrack_get_onstarted(This,pVal)	\
    ( (This)->lpVtbl -> get_onstarted(This,pVal) ) 

#define IMediaStreamTrack_put_onstarted(This,newVal)	\
    ( (This)->lpVtbl -> put_onstarted(This,newVal) ) 

#define IMediaStreamTrack_get_onended(This,pVal)	\
    ( (This)->lpVtbl -> get_onended(This,pVal) ) 

#define IMediaStreamTrack_put_onended(This,newVal)	\
    ( (This)->lpVtbl -> put_onended(This,newVal) ) 

#define IMediaStreamTrack_getSourceInfos(This,Infos)	\
    ( (This)->lpVtbl -> getSourceInfos(This,Infos) ) 

#define IMediaStreamTrack_constraints(This,MediaTrackConstraints)	\
    ( (This)->lpVtbl -> constraints(This,MediaTrackConstraints) ) 

#define IMediaStreamTrack_states(This,MediaSourceStates)	\
    ( (This)->lpVtbl -> states(This,MediaSourceStates) ) 

#define IMediaStreamTrack_capabilities(This,AllCapabilities)	\
    ( (This)->lpVtbl -> capabilities(This,AllCapabilities) ) 

#define IMediaStreamTrack_applyConstraints(This,MediaTrackConstraints)	\
    ( (This)->lpVtbl -> applyConstraints(This,MediaTrackConstraints) ) 

#define IMediaStreamTrack_get_onoverconstrained(This,pVal)	\
    ( (This)->lpVtbl -> get_onoverconstrained(This,pVal) ) 

#define IMediaStreamTrack_put_onoverconstrained(This,newVal)	\
    ( (This)->lpVtbl -> put_onoverconstrained(This,newVal) ) 

#define IMediaStreamTrack_clone(This,MediaStreamTrack)	\
    ( (This)->lpVtbl -> clone(This,MediaStreamTrack) ) 

#define IMediaStreamTrack_stop(This)	\
    ( (This)->lpVtbl -> stop(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMediaStreamTrack_INTERFACE_DEFINED__ */


#ifndef __ISourceInfo_INTERFACE_DEFINED__
#define __ISourceInfo_INTERFACE_DEFINED__

/* interface ISourceInfo */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISourceInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BCD116DA-B4BC-472E-A6AE-363D13B78667")
    ISourceInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sourceId( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_id( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_kind( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_label( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_facing( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISourceInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISourceInfo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISourceInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISourceInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISourceInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISourceInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISourceInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISourceInfo * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sourceId )( 
            ISourceInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_id )( 
            ISourceInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_kind )( 
            ISourceInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_label )( 
            ISourceInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_facing )( 
            ISourceInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ISourceInfoVtbl;

    interface ISourceInfo
    {
        CONST_VTBL struct ISourceInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISourceInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISourceInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISourceInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISourceInfo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISourceInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISourceInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISourceInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISourceInfo_get_sourceId(This,pVal)	\
    ( (This)->lpVtbl -> get_sourceId(This,pVal) ) 

#define ISourceInfo_get_id(This,pVal)	\
    ( (This)->lpVtbl -> get_id(This,pVal) ) 

#define ISourceInfo_get_kind(This,pVal)	\
    ( (This)->lpVtbl -> get_kind(This,pVal) ) 

#define ISourceInfo_get_label(This,pVal)	\
    ( (This)->lpVtbl -> get_label(This,pVal) ) 

#define ISourceInfo_get_facing(This,pVal)	\
    ( (This)->lpVtbl -> get_facing(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISourceInfo_INTERFACE_DEFINED__ */


#ifndef __IMediaSourceStates_INTERFACE_DEFINED__
#define __IMediaSourceStates_INTERFACE_DEFINED__

/* interface IMediaSourceStates */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMediaSourceStates;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A2B697F-688A-4CBE-B36F-4820D12BAE61")
    IMediaSourceStates : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sourceType( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sourceId( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_width( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_height( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_frameRate( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_aspectRatio( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_facingMode( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_volume( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMediaSourceStatesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaSourceStates * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaSourceStates * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaSourceStates * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMediaSourceStates * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMediaSourceStates * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMediaSourceStates * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMediaSourceStates * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sourceType )( 
            IMediaSourceStates * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sourceId )( 
            IMediaSourceStates * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_width )( 
            IMediaSourceStates * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_height )( 
            IMediaSourceStates * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_frameRate )( 
            IMediaSourceStates * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_aspectRatio )( 
            IMediaSourceStates * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_facingMode )( 
            IMediaSourceStates * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_volume )( 
            IMediaSourceStates * This,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IMediaSourceStatesVtbl;

    interface IMediaSourceStates
    {
        CONST_VTBL struct IMediaSourceStatesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaSourceStates_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMediaSourceStates_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMediaSourceStates_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMediaSourceStates_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMediaSourceStates_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMediaSourceStates_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMediaSourceStates_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMediaSourceStates_get_sourceType(This,pVal)	\
    ( (This)->lpVtbl -> get_sourceType(This,pVal) ) 

#define IMediaSourceStates_get_sourceId(This,pVal)	\
    ( (This)->lpVtbl -> get_sourceId(This,pVal) ) 

#define IMediaSourceStates_get_width(This,pVal)	\
    ( (This)->lpVtbl -> get_width(This,pVal) ) 

#define IMediaSourceStates_get_height(This,pVal)	\
    ( (This)->lpVtbl -> get_height(This,pVal) ) 

#define IMediaSourceStates_get_frameRate(This,pVal)	\
    ( (This)->lpVtbl -> get_frameRate(This,pVal) ) 

#define IMediaSourceStates_get_aspectRatio(This,pVal)	\
    ( (This)->lpVtbl -> get_aspectRatio(This,pVal) ) 

#define IMediaSourceStates_get_facingMode(This,pVal)	\
    ( (This)->lpVtbl -> get_facingMode(This,pVal) ) 

#define IMediaSourceStates_get_volume(This,pVal)	\
    ( (This)->lpVtbl -> get_volume(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMediaSourceStates_INTERFACE_DEFINED__ */


#ifndef __IMediaStreamEvent_INTERFACE_DEFINED__
#define __IMediaStreamEvent_INTERFACE_DEFINED__

/* interface IMediaStreamEvent */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMediaStreamEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EAB6AB59-5B8E-4096-AA67-0D557AA6BB32")
    IMediaStreamEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stream( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMediaStreamEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaStreamEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaStreamEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaStreamEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMediaStreamEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMediaStreamEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMediaStreamEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMediaStreamEvent * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_stream )( 
            IMediaStreamEvent * This,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IMediaStreamEventVtbl;

    interface IMediaStreamEvent
    {
        CONST_VTBL struct IMediaStreamEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaStreamEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMediaStreamEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMediaStreamEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMediaStreamEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMediaStreamEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMediaStreamEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMediaStreamEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMediaStreamEvent_get_stream(This,pVal)	\
    ( (This)->lpVtbl -> get_stream(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMediaStreamEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCPeerConnectionIceEvent_INTERFACE_DEFINED__
#define __IRTCPeerConnectionIceEvent_INTERFACE_DEFINED__

/* interface IRTCPeerConnectionIceEvent */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCPeerConnectionIceEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("354C2E39-380F-4F24-AEEA-687EB67F759D")
    IRTCPeerConnectionIceEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_candidate( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCPeerConnectionIceEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCPeerConnectionIceEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCPeerConnectionIceEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCPeerConnectionIceEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCPeerConnectionIceEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCPeerConnectionIceEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCPeerConnectionIceEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCPeerConnectionIceEvent * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_candidate )( 
            IRTCPeerConnectionIceEvent * This,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IRTCPeerConnectionIceEventVtbl;

    interface IRTCPeerConnectionIceEvent
    {
        CONST_VTBL struct IRTCPeerConnectionIceEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCPeerConnectionIceEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCPeerConnectionIceEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCPeerConnectionIceEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCPeerConnectionIceEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCPeerConnectionIceEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCPeerConnectionIceEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCPeerConnectionIceEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCPeerConnectionIceEvent_get_candidate(This,pVal)	\
    ( (This)->lpVtbl -> get_candidate(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCPeerConnectionIceEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCStatsReport_INTERFACE_DEFINED__
#define __IRTCStatsReport_INTERFACE_DEFINED__

/* interface IRTCStatsReport */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCStatsReport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("455118D0-A29F-44DB-ACF7-FE22BFAE2167")
    IRTCStatsReport : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE result( 
            /* [retval][out] */ VARIANT *RTCStatsList) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCStatsReportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCStatsReport * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCStatsReport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCStatsReport * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCStatsReport * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCStatsReport * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCStatsReport * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCStatsReport * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *result )( 
            IRTCStatsReport * This,
            /* [retval][out] */ VARIANT *RTCStatsList);
        
        END_INTERFACE
    } IRTCStatsReportVtbl;

    interface IRTCStatsReport
    {
        CONST_VTBL struct IRTCStatsReportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCStatsReport_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCStatsReport_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCStatsReport_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCStatsReport_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCStatsReport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCStatsReport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCStatsReport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCStatsReport_result(This,RTCStatsList)	\
    ( (This)->lpVtbl -> result(This,RTCStatsList) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCStatsReport_INTERFACE_DEFINED__ */


#ifndef __IRTCStats_INTERFACE_DEFINED__
#define __IRTCStats_INTERFACE_DEFINED__

/* interface IRTCStats */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CEFEB782-AFEC-4D0D-8C62-F1E255A73841")
    IRTCStats : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_timestamp( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_id( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE names( 
            /* [retval][out] */ VARIANT *Names) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stat( 
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCStats * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCStats * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCStats * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCStats * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCStats * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_timestamp )( 
            IRTCStats * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_type )( 
            IRTCStats * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_id )( 
            IRTCStats * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *names )( 
            IRTCStats * This,
            /* [retval][out] */ VARIANT *Names);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stat )( 
            IRTCStats * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IRTCStatsVtbl;

    interface IRTCStats
    {
        CONST_VTBL struct IRTCStatsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCStats_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCStats_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCStats_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCStats_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCStats_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCStats_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCStats_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCStats_get_timestamp(This,pVal)	\
    ( (This)->lpVtbl -> get_timestamp(This,pVal) ) 

#define IRTCStats_get_type(This,pVal)	\
    ( (This)->lpVtbl -> get_type(This,pVal) ) 

#define IRTCStats_get_id(This,pVal)	\
    ( (This)->lpVtbl -> get_id(This,pVal) ) 

#define IRTCStats_names(This,Names)	\
    ( (This)->lpVtbl -> names(This,Names) ) 

#define IRTCStats_stat(This,name,pVal)	\
    ( (This)->lpVtbl -> stat(This,name,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCStats_INTERFACE_DEFINED__ */


#ifndef __IRTCDTMFSender_INTERFACE_DEFINED__
#define __IRTCDTMFSender_INTERFACE_DEFINED__

/* interface IRTCDTMFSender */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCDTMFSender;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3FA7AEBF-DD1D-4F4A-B7AE-8BD878AF7809")
    IRTCDTMFSender : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_canInsertDTMF( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE insertDTMF( 
            BSTR tones,
            /* [optional][in] */ VARIANT duration,
            /* [optional][in] */ VARIANT interToneGap) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_track( 
            /* [retval][out] */ VARIANT *pMediaStreamTrack) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ontonechange( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ontonechange( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_toneBuffer( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_duration( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_interToneGap( 
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCDTMFSenderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCDTMFSender * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCDTMFSender * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCDTMFSender * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCDTMFSender * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCDTMFSender * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCDTMFSender * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCDTMFSender * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_canInsertDTMF )( 
            IRTCDTMFSender * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *insertDTMF )( 
            IRTCDTMFSender * This,
            BSTR tones,
            /* [optional][in] */ VARIANT duration,
            /* [optional][in] */ VARIANT interToneGap);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_track )( 
            IRTCDTMFSender * This,
            /* [retval][out] */ VARIANT *pMediaStreamTrack);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ontonechange )( 
            IRTCDTMFSender * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ontonechange )( 
            IRTCDTMFSender * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_toneBuffer )( 
            IRTCDTMFSender * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_duration )( 
            IRTCDTMFSender * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_interToneGap )( 
            IRTCDTMFSender * This,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } IRTCDTMFSenderVtbl;

    interface IRTCDTMFSender
    {
        CONST_VTBL struct IRTCDTMFSenderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCDTMFSender_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCDTMFSender_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCDTMFSender_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCDTMFSender_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCDTMFSender_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCDTMFSender_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCDTMFSender_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCDTMFSender_get_canInsertDTMF(This,pVal)	\
    ( (This)->lpVtbl -> get_canInsertDTMF(This,pVal) ) 

#define IRTCDTMFSender_insertDTMF(This,tones,duration,interToneGap)	\
    ( (This)->lpVtbl -> insertDTMF(This,tones,duration,interToneGap) ) 

#define IRTCDTMFSender_get_track(This,pMediaStreamTrack)	\
    ( (This)->lpVtbl -> get_track(This,pMediaStreamTrack) ) 

#define IRTCDTMFSender_get_ontonechange(This,pVal)	\
    ( (This)->lpVtbl -> get_ontonechange(This,pVal) ) 

#define IRTCDTMFSender_put_ontonechange(This,newVal)	\
    ( (This)->lpVtbl -> put_ontonechange(This,newVal) ) 

#define IRTCDTMFSender_get_toneBuffer(This,pVal)	\
    ( (This)->lpVtbl -> get_toneBuffer(This,pVal) ) 

#define IRTCDTMFSender_get_duration(This,pVal)	\
    ( (This)->lpVtbl -> get_duration(This,pVal) ) 

#define IRTCDTMFSender_get_interToneGap(This,pVal)	\
    ( (This)->lpVtbl -> get_interToneGap(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCDTMFSender_INTERFACE_DEFINED__ */


#ifndef __IRTCDTMFToneChangeEvent_INTERFACE_DEFINED__
#define __IRTCDTMFToneChangeEvent_INTERFACE_DEFINED__

/* interface IRTCDTMFToneChangeEvent */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCDTMFToneChangeEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E01CBEE1-8442-40FF-81CC-20714A49CC39")
    IRTCDTMFToneChangeEvent : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_tone( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCDTMFToneChangeEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCDTMFToneChangeEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCDTMFToneChangeEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCDTMFToneChangeEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCDTMFToneChangeEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCDTMFToneChangeEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCDTMFToneChangeEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCDTMFToneChangeEvent * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_tone )( 
            IRTCDTMFToneChangeEvent * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IRTCDTMFToneChangeEventVtbl;

    interface IRTCDTMFToneChangeEvent
    {
        CONST_VTBL struct IRTCDTMFToneChangeEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCDTMFToneChangeEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCDTMFToneChangeEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCDTMFToneChangeEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCDTMFToneChangeEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCDTMFToneChangeEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCDTMFToneChangeEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCDTMFToneChangeEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCDTMFToneChangeEvent_get_tone(This,pVal)	\
    ( (This)->lpVtbl -> get_tone(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCDTMFToneChangeEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCDataChannel_INTERFACE_DEFINED__
#define __IRTCDataChannel_INTERFACE_DEFINED__

/* interface IRTCDataChannel */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCDataChannel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("453AFDA0-2936-48C3-BE41-D059302217C2")
    IRTCDataChannel : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_label( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ordered( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_maxRetransmitTime( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_maxRetransmits( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_protocol( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_negotiated( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_id( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_readyState( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_bufferedAmount( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_binaryType( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_binaryType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onopen( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onopen( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onerror( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onerror( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onclose( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onclose( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_onmessage( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_onmessage( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE send( 
            /* [in] */ VARIANT data) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCDataChannelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCDataChannel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCDataChannel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCDataChannel * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCDataChannel * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCDataChannel * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCDataChannel * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCDataChannel * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_label )( 
            IRTCDataChannel * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ordered )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_maxRetransmitTime )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_maxRetransmits )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_protocol )( 
            IRTCDataChannel * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_negotiated )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_id )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_readyState )( 
            IRTCDataChannel * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_bufferedAmount )( 
            IRTCDataChannel * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_binaryType )( 
            IRTCDataChannel * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_binaryType )( 
            IRTCDataChannel * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onopen )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onopen )( 
            IRTCDataChannel * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onerror )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onerror )( 
            IRTCDataChannel * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onclose )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onclose )( 
            IRTCDataChannel * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_onmessage )( 
            IRTCDataChannel * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_onmessage )( 
            IRTCDataChannel * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *close )( 
            IRTCDataChannel * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *send )( 
            IRTCDataChannel * This,
            /* [in] */ VARIANT data);
        
        END_INTERFACE
    } IRTCDataChannelVtbl;

    interface IRTCDataChannel
    {
        CONST_VTBL struct IRTCDataChannelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCDataChannel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCDataChannel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCDataChannel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCDataChannel_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCDataChannel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCDataChannel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCDataChannel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCDataChannel_get_label(This,pVal)	\
    ( (This)->lpVtbl -> get_label(This,pVal) ) 

#define IRTCDataChannel_get_ordered(This,pVal)	\
    ( (This)->lpVtbl -> get_ordered(This,pVal) ) 

#define IRTCDataChannel_get_maxRetransmitTime(This,pVal)	\
    ( (This)->lpVtbl -> get_maxRetransmitTime(This,pVal) ) 

#define IRTCDataChannel_get_maxRetransmits(This,pVal)	\
    ( (This)->lpVtbl -> get_maxRetransmits(This,pVal) ) 

#define IRTCDataChannel_get_protocol(This,pVal)	\
    ( (This)->lpVtbl -> get_protocol(This,pVal) ) 

#define IRTCDataChannel_get_negotiated(This,pVal)	\
    ( (This)->lpVtbl -> get_negotiated(This,pVal) ) 

#define IRTCDataChannel_get_id(This,pVal)	\
    ( (This)->lpVtbl -> get_id(This,pVal) ) 

#define IRTCDataChannel_get_readyState(This,pVal)	\
    ( (This)->lpVtbl -> get_readyState(This,pVal) ) 

#define IRTCDataChannel_get_bufferedAmount(This,pVal)	\
    ( (This)->lpVtbl -> get_bufferedAmount(This,pVal) ) 

#define IRTCDataChannel_get_binaryType(This,pVal)	\
    ( (This)->lpVtbl -> get_binaryType(This,pVal) ) 

#define IRTCDataChannel_put_binaryType(This,newVal)	\
    ( (This)->lpVtbl -> put_binaryType(This,newVal) ) 

#define IRTCDataChannel_get_onopen(This,pVal)	\
    ( (This)->lpVtbl -> get_onopen(This,pVal) ) 

#define IRTCDataChannel_put_onopen(This,newVal)	\
    ( (This)->lpVtbl -> put_onopen(This,newVal) ) 

#define IRTCDataChannel_get_onerror(This,pVal)	\
    ( (This)->lpVtbl -> get_onerror(This,pVal) ) 

#define IRTCDataChannel_put_onerror(This,newVal)	\
    ( (This)->lpVtbl -> put_onerror(This,newVal) ) 

#define IRTCDataChannel_get_onclose(This,pVal)	\
    ( (This)->lpVtbl -> get_onclose(This,pVal) ) 

#define IRTCDataChannel_put_onclose(This,newVal)	\
    ( (This)->lpVtbl -> put_onclose(This,newVal) ) 

#define IRTCDataChannel_get_onmessage(This,pVal)	\
    ( (This)->lpVtbl -> get_onmessage(This,pVal) ) 

#define IRTCDataChannel_put_onmessage(This,newVal)	\
    ( (This)->lpVtbl -> put_onmessage(This,newVal) ) 

#define IRTCDataChannel_close(This)	\
    ( (This)->lpVtbl -> close(This) ) 

#define IRTCDataChannel_send(This,data)	\
    ( (This)->lpVtbl -> send(This,data) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCDataChannel_INTERFACE_DEFINED__ */


#ifndef __IMessageEvent_INTERFACE_DEFINED__
#define __IMessageEvent_INTERFACE_DEFINED__

/* interface IMessageEvent */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMessageEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2C5FD5A1-29F3-4CFF-94B6-711A77F0CB61")
    IMessageEvent : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_data( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMessageEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMessageEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMessageEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMessageEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMessageEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMessageEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMessageEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMessageEvent * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_data )( 
            IMessageEvent * This,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IMessageEventVtbl;

    interface IMessageEvent
    {
        CONST_VTBL struct IMessageEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMessageEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMessageEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMessageEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMessageEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMessageEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMessageEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMessageEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMessageEvent_get_data(This,pVal)	\
    ( (This)->lpVtbl -> get_data(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMessageEvent_INTERFACE_DEFINED__ */


#ifndef __IRTCDataChannelEvent_INTERFACE_DEFINED__
#define __IRTCDataChannelEvent_INTERFACE_DEFINED__

/* interface IRTCDataChannelEvent */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTCDataChannelEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51E8910B-881C-43DE-B211-28C43107C6A1")
    IRTCDataChannelEvent : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_channel( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRTCDataChannelEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTCDataChannelEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTCDataChannelEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTCDataChannelEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTCDataChannelEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTCDataChannelEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTCDataChannelEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTCDataChannelEvent * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_channel )( 
            IRTCDataChannelEvent * This,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IRTCDataChannelEventVtbl;

    interface IRTCDataChannelEvent
    {
        CONST_VTBL struct IRTCDataChannelEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTCDataChannelEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTCDataChannelEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTCDataChannelEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTCDataChannelEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTCDataChannelEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTCDataChannelEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTCDataChannelEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTCDataChannelEvent_get_channel(This,pVal)	\
    ( (This)->lpVtbl -> get_channel(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTCDataChannelEvent_INTERFACE_DEFINED__ */



#ifndef __webrtceverywhereLib_LIBRARY_DEFINED__
#define __webrtceverywhereLib_LIBRARY_DEFINED__

/* library webrtceverywhereLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_webrtceverywhereLib;

#ifndef ___IWebRTCEvents_DISPINTERFACE_DEFINED__
#define ___IWebRTCEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWebRTCEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWebRTCEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("20B33168-3B94-49C3-9E55-A60B9EA0E886")
    _IWebRTCEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWebRTCEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWebRTCEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWebRTCEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWebRTCEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWebRTCEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWebRTCEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWebRTCEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWebRTCEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IWebRTCEventsVtbl;

    interface _IWebRTCEvents
    {
        CONST_VTBL struct _IWebRTCEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWebRTCEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWebRTCEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWebRTCEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWebRTCEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWebRTCEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWebRTCEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWebRTCEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWebRTCEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebRTC;

#ifdef __cplusplus

class DECLSPEC_UUID("7FD49E23-C8D7-4C4F-93A1-F7EACFA1EC53")
WebRTC;
#endif

EXTERN_C const CLSID CLSID_SessionDescription;

#ifdef __cplusplus

class DECLSPEC_UUID("3F7C50A7-7B5C-4631-8988-17B43A938667")
SessionDescription;
#endif

EXTERN_C const CLSID CLSID_DictOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("D6B8C652-7A2A-47B6-8C38-3BD5BB0E2872")
DictOptions;
#endif

EXTERN_C const CLSID CLSID_PeerConnection;

#ifdef __cplusplus

class DECLSPEC_UUID("017D6D0A-BDBC-45DC-9368-A7ED657DAC4D")
PeerConnection;
#endif

EXTERN_C const CLSID CLSID_MediaStream;

#ifdef __cplusplus

class DECLSPEC_UUID("BA5835A2-D1F8-466D-BB5E-8093E3E2EE0E")
MediaStream;
#endif

EXTERN_C const CLSID CLSID_RTCIceCandidate;

#ifdef __cplusplus

class DECLSPEC_UUID("31074FC8-A7D4-4281-9C90-B7D20C53A023")
RTCIceCandidate;
#endif

EXTERN_C const CLSID CLSID_MediaStreamTrack;

#ifdef __cplusplus

class DECLSPEC_UUID("DA1D1412-BC34-4288-8047-6FFE131C647F")
MediaStreamTrack;
#endif

EXTERN_C const CLSID CLSID_SourceInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("E66A3288-4BFB-41E2-850D-61C63208DD80")
SourceInfo;
#endif

EXTERN_C const CLSID CLSID_MediaSourceStates;

#ifdef __cplusplus

class DECLSPEC_UUID("7F64ACB6-F21C-44C2-8EEA-EFCBEED5AEB7")
MediaSourceStates;
#endif

EXTERN_C const CLSID CLSID_MediaStreamEvent;

#ifdef __cplusplus

class DECLSPEC_UUID("C744BE59-7004-4B7E-BD9D-C83F594A1B69")
MediaStreamEvent;
#endif

EXTERN_C const CLSID CLSID_RTCPeerConnectionIceEvent;

#ifdef __cplusplus

class DECLSPEC_UUID("1A225B63-CA8F-466E-A848-44A16A19706E")
RTCPeerConnectionIceEvent;
#endif

EXTERN_C const CLSID CLSID_RTCStatsReport;

#ifdef __cplusplus

class DECLSPEC_UUID("419C32C7-EF29-42C3-9A02-7C64FF869FD6")
RTCStatsReport;
#endif

EXTERN_C const CLSID CLSID_RTCStats;

#ifdef __cplusplus

class DECLSPEC_UUID("F752E29B-45CB-4753-AA0C-51D1A021143C")
RTCStats;
#endif

EXTERN_C const CLSID CLSID_RTCDTMFSender;

#ifdef __cplusplus

class DECLSPEC_UUID("FDFDCAED-5FE4-4B75-A492-5E1837CDC84C")
RTCDTMFSender;
#endif

EXTERN_C const CLSID CLSID_RTCDTMFToneChangeEvent;

#ifdef __cplusplus

class DECLSPEC_UUID("C01163AE-3E5E-4224-B708-74933D83E81E")
RTCDTMFToneChangeEvent;
#endif

EXTERN_C const CLSID CLSID_RTCDataChannel;

#ifdef __cplusplus

class DECLSPEC_UUID("815D3DD5-8BFD-40DC-ABCC-382C94A57445")
RTCDataChannel;
#endif

EXTERN_C const CLSID CLSID_MessageEvent;

#ifdef __cplusplus

class DECLSPEC_UUID("F62F0206-F6F8-4FD8-8F63-0C6BCE7C904F")
MessageEvent;
#endif

EXTERN_C const CLSID CLSID_RTCDataChannelEvent;

#ifdef __cplusplus

class DECLSPEC_UUID("C40ED871-D195-4EFD-9E60-F0911449A404")
RTCDataChannelEvent;
#endif
#endif /* __webrtceverywhereLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


