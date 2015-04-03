

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Apr 01 17:04:38 2015
 */
/* Compiler settings for webrtceverywhere.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "webrtceverywhere_i.h"

#define TYPE_FORMAT_STRING_SIZE   1051                              
#define PROC_FORMAT_STRING_SIZE   3945                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _webrtceverywhere_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } webrtceverywhere_MIDL_TYPE_FORMAT_STRING;

typedef struct _webrtceverywhere_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } webrtceverywhere_MIDL_PROC_FORMAT_STRING;

typedef struct _webrtceverywhere_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } webrtceverywhere_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const webrtceverywhere_MIDL_TYPE_FORMAT_STRING webrtceverywhere__MIDL_TypeFormatString;
extern const webrtceverywhere_MIDL_PROC_FORMAT_STRING webrtceverywhere__MIDL_ProcFormatString;
extern const webrtceverywhere_MIDL_EXPR_FORMAT_STRING webrtceverywhere__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IWebRTC_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IWebRTC_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISessionDescription_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISessionDescription_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDictOptions_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDictOptions_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPeerConnection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPeerConnection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMediaStream_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMediaStream_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCIceCandidate_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCIceCandidate_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMediaStreamTrack_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMediaStreamTrack_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISourceInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISourceInfo_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMediaSourceStates_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMediaSourceStates_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMediaStreamEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMediaStreamEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPeerConnectionIceEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPeerConnectionIceEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCStatsReport_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCStatsReport_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCStats_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCStats_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCDTMFSender_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCDTMFSender_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCDTMFToneChangeEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCDTMFToneChangeEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCDataChannel_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCDataChannel_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMessageEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMessageEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCDataChannelEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCDataChannelEvent_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const webrtceverywhere_MIDL_PROC_FORMAT_STRING webrtceverywhere__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_label */


	/* Procedure get_tone */


	/* Procedure get_sourceType */


	/* Procedure get_sourceId */


	/* Procedure get_kind */


	/* Procedure get_candidate */


	/* Procedure get_id */


	/* Procedure get_type */


	/* Procedure get_versionName */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 26 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createAnswer */


	/* Procedure getUserMedia */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x8 ),	/* 8 */
/* 46 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 54 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x1 ),	/* 1 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter successCallback */


	/* Parameter constraints */

/* 64 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 66 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 68 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter failureCallback */


	/* Parameter successCallback */

/* 70 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 72 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 74 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter MediaConstraints */


	/* Parameter errorCallback */

/* 76 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 78 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 80 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */

/* 82 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 84 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 86 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createDisplay */

/* 88 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 90 */	NdrFcLong( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x9 ),	/* 9 */
/* 96 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x8 ),	/* 8 */
/* 102 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 104 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDisplay */

/* 114 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 116 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 118 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */

	/* Return value */

/* 120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 122 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createSessionDescription */

/* 126 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0xa ),	/* 10 */
/* 134 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 140 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 142 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0x1 ),	/* 1 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCSessionDescriptionInit */

/* 152 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 154 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 156 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter ppSdp */

/* 158 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 160 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 162 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */

	/* Return value */

/* 164 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 166 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createDictOptions */

/* 170 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0xb ),	/* 11 */
/* 178 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x8 ),	/* 8 */
/* 184 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 186 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x0 ),	/* 0 */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDictOptions */

/* 196 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 198 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 200 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */

	/* Return value */

/* 202 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 204 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 206 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createPeerConnection */

/* 208 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 210 */	NdrFcLong( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0xc ),	/* 12 */
/* 216 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 220 */	NdrFcShort( 0x8 ),	/* 8 */
/* 222 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 224 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 228 */	NdrFcShort( 0x1 ),	/* 1 */
/* 230 */	NdrFcShort( 0x0 ),	/* 0 */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCConfiguration */

/* 234 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 236 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 238 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter MediaConstraints */

/* 240 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 242 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 244 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter ppPeerConnection */

/* 246 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 248 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 250 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */

	/* Return value */

/* 252 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 254 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createIceCandidate */

/* 258 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 260 */	NdrFcLong( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0xd ),	/* 13 */
/* 266 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x8 ),	/* 8 */
/* 272 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 274 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x1 ),	/* 1 */
/* 280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 282 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCIceCandidateInit */

/* 284 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 286 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 288 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter ppIceCandidate */

/* 290 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 292 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 294 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */

	/* Return value */

/* 296 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 298 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createMediaStreamTrack */

/* 302 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 304 */	NdrFcLong( 0x0 ),	/* 0 */
/* 308 */	NdrFcShort( 0xe ),	/* 14 */
/* 310 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x8 ),	/* 8 */
/* 316 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 318 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppMediaStreamTrack */

/* 328 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 330 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 332 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */

	/* Return value */

/* 334 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 336 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 338 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure bindEventListener */

/* 340 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 342 */	NdrFcLong( 0x0 ),	/* 0 */
/* 346 */	NdrFcShort( 0xf ),	/* 15 */
/* 348 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x8 ),	/* 8 */
/* 354 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 356 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x1 ),	/* 1 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter type */

/* 366 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 368 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 370 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter listenerCallback */

/* 372 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 374 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 376 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter useCapture */

/* 378 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 380 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 382 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 384 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 386 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onunmute */


	/* Procedure put_onended */


	/* Procedure getSources */

/* 390 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 392 */	NdrFcLong( 0x0 ),	/* 0 */
/* 396 */	NdrFcShort( 0x10 ),	/* 16 */
/* 398 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 402 */	NdrFcShort( 0x8 ),	/* 8 */
/* 404 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 406 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 410 */	NdrFcShort( 0x1 ),	/* 1 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter successCallback */

/* 416 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 418 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 420 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 422 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 424 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 426 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_src */

/* 428 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 430 */	NdrFcLong( 0x0 ),	/* 0 */
/* 434 */	NdrFcShort( 0x11 ),	/* 17 */
/* 436 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 440 */	NdrFcShort( 0x8 ),	/* 8 */
/* 442 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 444 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 448 */	NdrFcShort( 0x1 ),	/* 1 */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 454 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 456 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 458 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 460 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 462 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 464 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_videoWidth */

/* 466 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 468 */	NdrFcLong( 0x0 ),	/* 0 */
/* 472 */	NdrFcShort( 0x12 ),	/* 18 */
/* 474 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0x24 ),	/* 36 */
/* 480 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 482 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 492 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 494 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 498 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 500 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 502 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_videoHeight */

/* 504 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 506 */	NdrFcLong( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0x13 ),	/* 19 */
/* 512 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x24 ),	/* 36 */
/* 518 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 520 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 528 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 530 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 532 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 534 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 536 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 538 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 540 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onremovetrack */


	/* Procedure fillImageData */

/* 542 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 544 */	NdrFcLong( 0x0 ),	/* 0 */
/* 548 */	NdrFcShort( 0x14 ),	/* 20 */
/* 550 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x8 ),	/* 8 */
/* 556 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 558 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 562 */	NdrFcShort( 0x1 ),	/* 1 */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter imageData */

/* 568 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 570 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 572 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */

/* 574 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 576 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 578 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getScreenShot */

/* 580 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 582 */	NdrFcLong( 0x0 ),	/* 0 */
/* 586 */	NdrFcShort( 0x15 ),	/* 21 */
/* 588 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x8 ),	/* 8 */
/* 594 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 596 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 598 */	NdrFcShort( 0x1 ),	/* 1 */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter base64BitmapData */

/* 606 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 608 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 610 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 612 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 614 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 616 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_isWebRtcPlugin */

/* 618 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 620 */	NdrFcLong( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x16 ),	/* 22 */
/* 626 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x22 ),	/* 34 */
/* 632 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 634 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 644 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 646 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 648 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 650 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 652 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 654 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_type */

/* 656 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 658 */	NdrFcLong( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0x8 ),	/* 8 */
/* 664 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x8 ),	/* 8 */
/* 670 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 672 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x1 ),	/* 1 */
/* 678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 682 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 684 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 686 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Return value */

/* 688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 690 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_id */


	/* Procedure get_kind */


	/* Procedure get_label */


	/* Procedure get_sdp */

/* 694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x9 ),	/* 9 */
/* 702 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 708 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 710 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 712 */	NdrFcShort( 0x1 ),	/* 1 */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 718 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 720 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 722 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 724 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 726 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 728 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 730 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_sdp */

/* 732 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 734 */	NdrFcLong( 0x0 ),	/* 0 */
/* 738 */	NdrFcShort( 0xa ),	/* 10 */
/* 740 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x8 ),	/* 8 */
/* 746 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 748 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 752 */	NdrFcShort( 0x1 ),	/* 1 */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 758 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 760 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 762 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Return value */

/* 764 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 766 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 768 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createOffer */

/* 770 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 772 */	NdrFcLong( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x7 ),	/* 7 */
/* 778 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 784 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 786 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 790 */	NdrFcShort( 0x1 ),	/* 1 */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter successCallback */

/* 796 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 798 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 800 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter failureCallback */

/* 802 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 804 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 806 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter MediaConstraints */

/* 808 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 810 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 812 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 814 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 816 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setLocalDescription */

/* 820 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 822 */	NdrFcLong( 0x0 ),	/* 0 */
/* 826 */	NdrFcShort( 0x9 ),	/* 9 */
/* 828 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x8 ),	/* 8 */
/* 834 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 836 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x1 ),	/* 1 */
/* 842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCSessionDescription */

/* 846 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 848 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 850 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter successCallback */

/* 852 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 854 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 856 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter failureCallback */

/* 858 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 860 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 862 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 866 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_maxRetransmits */


	/* Procedure get_ontonechange */


	/* Procedure names */


	/* Procedure get_height */


	/* Procedure get_localDescription */

/* 870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0xa ),	/* 10 */
/* 878 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x8 ),	/* 8 */
/* 884 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 886 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 888 */	NdrFcShort( 0x1 ),	/* 1 */
/* 890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 894 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter Names */


	/* Parameter pVal */


	/* Parameter pVal */

/* 896 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 898 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 900 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 902 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 904 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 906 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setRemoteDescription */

/* 908 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 910 */	NdrFcLong( 0x0 ),	/* 0 */
/* 914 */	NdrFcShort( 0xb ),	/* 11 */
/* 916 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x8 ),	/* 8 */
/* 922 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 924 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 928 */	NdrFcShort( 0x1 ),	/* 1 */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCSessionDescription */

/* 934 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 936 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 938 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter successCallback */

/* 940 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 942 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 944 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter failureCallback */

/* 946 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 948 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 950 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 954 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_aspectRatio */


	/* Procedure get_remoteDescription */

/* 958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0xc ),	/* 12 */
/* 966 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 972 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 974 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 976 */	NdrFcShort( 0x1 ),	/* 1 */
/* 978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 984 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 986 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 988 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 990 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 992 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 994 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_signalingState */

/* 996 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 998 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1002 */	NdrFcShort( 0xd ),	/* 13 */
/* 1004 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1008 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1010 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1012 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1014 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1022 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1024 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1026 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1030 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure updateIce */

/* 1034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0xe ),	/* 14 */
/* 1042 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1048 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1050 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1054 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1058 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCConfiguration */

/* 1060 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1062 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1064 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter MediaConstraints */

/* 1066 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1068 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1070 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1072 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1074 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1076 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addIceCandidate */

/* 1078 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1080 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1084 */	NdrFcShort( 0xf ),	/* 15 */
/* 1086 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 1088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1090 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1092 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1094 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1098 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1102 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCIceCandidate */

/* 1104 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1106 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1108 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter successCallback */

/* 1110 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1112 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1114 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter failureCallback */

/* 1116 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1118 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1120 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1122 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1124 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_binaryType */


	/* Procedure get_iceGatheringState */

/* 1128 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1130 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1136 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1142 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1144 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1146 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1152 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1154 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1156 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1158 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */

/* 1160 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1162 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1164 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_iceConnectionState */

/* 1166 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1168 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1172 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1174 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1178 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1180 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1182 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1184 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1192 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1194 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1196 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1198 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1200 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onopen */


	/* Procedure getLocalStreams */

/* 1204 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1206 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1210 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1212 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1216 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1218 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1220 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1222 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1228 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter MediaStreams */

/* 1230 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1232 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1234 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 1236 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1238 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onremovetrack */


	/* Procedure getRemoteStreams */

/* 1242 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1244 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1248 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1250 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1254 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1256 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1258 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1260 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1262 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1266 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter MediaStreams */

/* 1268 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1270 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1272 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 1274 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1276 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getStreamById */

/* 1280 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1282 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1286 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1288 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1294 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1296 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1298 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1300 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1304 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter streamId */

/* 1306 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1308 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1310 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter MediaStream */

/* 1312 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1314 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1316 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 1318 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1320 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addStream */

/* 1324 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1326 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1330 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1332 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1334 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1336 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1338 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1340 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1344 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1348 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter stream */

/* 1350 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1352 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1354 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter MediaConstraints */

/* 1356 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1358 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1360 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1362 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1364 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure removeStream */

/* 1368 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1374 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1376 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1382 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1384 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1388 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1392 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter stream */

/* 1394 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1396 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1398 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1400 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1402 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1404 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure close */

/* 1406 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1408 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1412 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1414 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1416 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1418 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1420 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1422 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1424 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1430 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1432 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1434 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getStats */

/* 1438 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1440 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1444 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1446 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 1448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1450 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1452 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1454 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1456 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1458 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1462 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter selector */

/* 1464 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1466 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1468 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter successCallback */

/* 1470 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1472 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1474 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter failureCallback */

/* 1476 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1478 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1480 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1482 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1484 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createDTMFSender */

/* 1488 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1496 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1502 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1504 */	0xa,		/* 10 */
			0x87,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has big amd64 byval param */
/* 1506 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1508 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1512 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MediaStreamTrack */

/* 1514 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1516 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1518 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter RTCDTMFSender */

/* 1520 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1522 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1524 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 1526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1528 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure createDataChannel */

/* 1532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1538 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1540 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 1542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1546 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1548 */	0xa,		/* 10 */
			0x87,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has big amd64 byval param */
/* 1550 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1552 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1556 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter label */

/* 1558 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1560 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1562 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter dataChannelDict */

/* 1564 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1566 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1568 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter DataChannel */

/* 1570 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1572 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1574 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 1576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1578 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure capabilities */


	/* Procedure get_onnegotiationneeded */

/* 1582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1588 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1590 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1594 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1596 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1598 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1600 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1606 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter AllCapabilities */


	/* Parameter pVal */

/* 1608 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1610 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1612 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 1614 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1616 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1618 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure applyConstraints */


	/* Procedure put_onnegotiationneeded */

/* 1620 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1622 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1626 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1628 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1632 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1634 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1636 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1640 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1644 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MediaTrackConstraints */


	/* Parameter newVal */

/* 1646 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1648 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1650 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */

/* 1652 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1654 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1656 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onoverconstrained */


	/* Procedure get_onicecandidate */

/* 1658 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1660 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1664 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1666 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1670 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1672 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1674 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1676 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1682 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1684 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1686 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1688 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 1690 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1692 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1694 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onoverconstrained */


	/* Procedure put_onicecandidate */

/* 1696 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1698 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1702 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1704 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1708 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1710 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1712 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1716 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1720 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1722 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1724 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1726 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */

/* 1728 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1730 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1732 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure clone */


	/* Procedure get_onsignalingstatechange */

/* 1734 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1736 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1740 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1742 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1748 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1750 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1752 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1758 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MediaStreamTrack */


	/* Parameter pVal */

/* 1760 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1762 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1764 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 1766 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1768 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1770 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onsignalingstatechange */

/* 1772 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1774 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1778 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1780 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1786 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1788 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1792 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1796 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1798 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1800 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1802 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1804 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1806 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1808 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onaddstream */

/* 1810 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1812 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1816 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1818 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1822 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1824 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1826 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1828 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1834 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1836 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1838 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1840 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 1842 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1844 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1846 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onaddstream */

/* 1848 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1850 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1854 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1856 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1862 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1864 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1868 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1870 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1872 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1874 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1876 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1878 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1880 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1882 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1884 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onremovestream */

/* 1886 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1888 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1892 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1894 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1896 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1898 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1900 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1902 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1904 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1910 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1912 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1914 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1916 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 1918 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1920 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1922 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onremovestream */

/* 1924 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1926 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1930 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1932 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1934 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1936 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1938 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1940 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 1942 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1944 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1948 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1950 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1952 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1954 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 1956 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1958 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1960 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_oniceconnectionstatechange */

/* 1962 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1964 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1968 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1970 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1974 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1976 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1978 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1980 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1986 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1988 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 1990 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1992 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 1994 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1996 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1998 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_oniceconnectionstatechange */

/* 2000 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2002 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2006 */	NdrFcShort( 0x26 ),	/* 38 */
/* 2008 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2012 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2014 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2016 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 2018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2020 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2022 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2024 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2026 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2028 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2030 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 2032 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2034 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2036 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ondatachannel */

/* 2038 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2040 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2044 */	NdrFcShort( 0x27 ),	/* 39 */
/* 2046 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2050 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2052 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2054 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2056 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2062 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2064 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2066 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2068 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 2070 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2072 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2074 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ondatachannel */

/* 2076 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2078 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2082 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2084 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2088 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2090 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2092 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 2094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2096 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2102 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2104 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2106 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 2108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2110 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getAudioTracks */

/* 2114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2122 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2128 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2130 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2132 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Tracks */

/* 2140 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2142 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2144 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 2146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2148 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_maxRetransmitTime */


	/* Procedure get_track */


	/* Procedure get_width */


	/* Procedure getVideoTracks */

/* 2152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2158 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2160 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2166 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2168 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2170 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pMediaStreamTrack */


	/* Parameter pVal */


	/* Parameter Tracks */

/* 2178 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2180 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2182 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 2184 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2186 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getTrackById */

/* 2190 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2192 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2196 */	NdrFcShort( 0xa ),	/* 10 */
/* 2198 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 2200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2204 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2206 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2208 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2210 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2214 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter trackId */

/* 2216 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2218 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2220 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter MediaStreamTrack */

/* 2222 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2224 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2226 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 2228 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2230 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ontonechange */


	/* Procedure addTrack */

/* 2234 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2236 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2240 */	NdrFcShort( 0xb ),	/* 11 */
/* 2242 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2248 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2250 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 2252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2254 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2258 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter MediaStreamTrack */

/* 2260 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2262 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2264 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */

/* 2266 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2268 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2270 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure removeTrack */

/* 2272 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2274 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2278 */	NdrFcShort( 0xc ),	/* 12 */
/* 2280 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2284 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2286 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2288 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 2290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2292 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2296 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MediaStreamTrack */

/* 2298 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2300 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2302 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 2304 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2306 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2308 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_id */


	/* Procedure get_facingMode */


	/* Procedure get_onmute */


	/* Procedure clone */

/* 2310 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2312 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2316 */	NdrFcShort( 0xd ),	/* 13 */
/* 2318 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2322 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2324 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2326 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2328 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2334 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter MediaStream */

/* 2336 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2338 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2340 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 2342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2344 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ended */

/* 2348 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2354 */	NdrFcShort( 0xe ),	/* 14 */
/* 2356 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2360 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2362 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2364 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2372 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2374 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2376 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2378 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2380 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2382 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onunmute */


	/* Procedure get_onended */

/* 2386 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2392 */	NdrFcShort( 0xf ),	/* 15 */
/* 2394 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2398 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2400 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2402 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2404 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2410 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 2412 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2414 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2416 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 2418 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2420 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2422 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onaddtrack */

/* 2424 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2426 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2430 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2432 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2436 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2438 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2440 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2442 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2448 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2450 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2452 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2454 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 2456 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2458 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onaddtrack */

/* 2462 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2464 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2468 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2470 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2474 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2476 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2478 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 2480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2482 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2486 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2488 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2490 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2492 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 2494 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2496 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2498 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure stop */

/* 2500 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2502 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2506 */	NdrFcShort( 0x15 ),	/* 21 */
/* 2508 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2512 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2514 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2516 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2524 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2528 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_type */


	/* Procedure get_sourceId */


	/* Procedure get_id */


	/* Procedure get_id */


	/* Procedure get_sdpMid */

/* 2532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2538 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2540 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2546 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2548 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2550 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2556 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 2558 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2560 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2562 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 2564 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2566 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_sdpMLineIndex */

/* 2570 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2572 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2576 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2578 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2582 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2584 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2586 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2594 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2596 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2598 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2600 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2602 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2604 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_enabled */

/* 2608 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2610 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2614 */	NdrFcShort( 0xa ),	/* 10 */
/* 2616 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2620 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2622 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2624 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2632 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2634 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2636 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2638 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2640 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2642 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2644 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_enabled */

/* 2646 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2648 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2652 */	NdrFcShort( 0xb ),	/* 11 */
/* 2654 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2656 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2658 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2660 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2662 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2670 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2672 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2674 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2676 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2680 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_negotiated */


	/* Procedure get_muted */

/* 2684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2690 */	NdrFcShort( 0xc ),	/* 12 */
/* 2692 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2696 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2698 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2700 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2708 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 2710 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2712 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2714 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 2716 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2718 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2720 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onmute */

/* 2722 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2724 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2728 */	NdrFcShort( 0xe ),	/* 14 */
/* 2730 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2734 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2736 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2738 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 2740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2742 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2746 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2748 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2750 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2752 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 2754 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2756 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_readonly */

/* 2760 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2762 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2766 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2768 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2772 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2774 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2776 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2784 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2786 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2788 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2790 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2794 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_remote */

/* 2798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2804 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2806 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2810 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2812 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2814 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2822 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2824 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2826 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2828 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2830 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2832 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2834 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_readyState */

/* 2836 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2838 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2842 */	NdrFcShort( 0x13 ),	/* 19 */
/* 2844 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2850 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2852 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2854 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2860 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2862 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2864 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2866 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2868 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2870 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2872 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onerror */


	/* Procedure get_onstarted */

/* 2874 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2876 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2880 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2882 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2886 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2888 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2890 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2892 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2896 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2898 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 2900 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2902 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2904 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 2906 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2908 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2910 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onerror */


	/* Procedure put_onstarted */

/* 2912 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2914 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2918 */	NdrFcShort( 0x15 ),	/* 21 */
/* 2920 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2926 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2928 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 2930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2932 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2934 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2936 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 2938 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2940 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2942 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */

/* 2944 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2946 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2948 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onclose */


	/* Procedure get_onended */

/* 2950 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2952 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2956 */	NdrFcShort( 0x16 ),	/* 22 */
/* 2958 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2962 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2964 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2966 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2968 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2974 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 2976 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 2978 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2980 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 2982 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2984 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2986 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onclose */


	/* Procedure put_onended */

/* 2988 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2990 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2994 */	NdrFcShort( 0x17 ),	/* 23 */
/* 2996 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3000 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3002 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3004 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 3006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3008 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3012 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 3014 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3016 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3018 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */


	/* Return value */

/* 3020 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3022 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3024 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_onmessage */


	/* Procedure getSourceInfos */

/* 3026 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3028 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3032 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3034 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3038 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3040 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3042 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3044 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3050 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter Infos */

/* 3052 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 3054 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3056 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */

/* 3058 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3060 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure constraints */

/* 3064 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3070 */	NdrFcShort( 0x19 ),	/* 25 */
/* 3072 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3076 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3078 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3080 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3082 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3088 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MediaTrackConstraints */

/* 3090 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 3092 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3094 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 3096 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3098 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure states */

/* 3102 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3104 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3108 */	NdrFcShort( 0x1a ),	/* 26 */
/* 3110 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3114 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3116 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3118 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3120 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3126 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MediaSourceStates */

/* 3128 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 3130 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3132 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 3134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3136 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure stop */

/* 3140 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3142 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3146 */	NdrFcShort( 0x20 ),	/* 32 */
/* 3148 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3154 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 3156 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3164 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 3166 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3168 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3170 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_label */

/* 3172 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3174 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3178 */	NdrFcShort( 0xa ),	/* 10 */
/* 3180 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3184 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3186 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3188 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3190 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3192 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3196 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3198 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3200 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3202 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3204 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3206 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_protocol */


	/* Procedure get_facing */

/* 3210 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3212 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3216 */	NdrFcShort( 0xb ),	/* 11 */
/* 3218 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3222 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3224 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3226 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3228 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3230 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3234 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 3236 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3238 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3240 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */

/* 3242 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3244 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3246 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_frameRate */

/* 3248 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3250 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3254 */	NdrFcShort( 0xb ),	/* 11 */
/* 3256 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3260 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3262 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3264 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3266 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3272 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3274 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 3276 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3278 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 3280 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3282 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_volume */

/* 3286 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3288 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3292 */	NdrFcShort( 0xe ),	/* 14 */
/* 3294 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3296 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3300 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3302 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3304 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3308 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3310 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3312 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 3314 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3316 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 3318 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3320 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_channel */


	/* Procedure get_data */


	/* Procedure result */


	/* Procedure get_candidate */


	/* Procedure get_stream */

/* 3324 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3326 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3330 */	NdrFcShort( 0x7 ),	/* 7 */
/* 3332 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3334 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3336 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3338 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3340 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3342 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3348 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter RTCStatsList */


	/* Parameter pVal */


	/* Parameter pVal */

/* 3350 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 3352 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3354 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 3356 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3358 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3360 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_timestamp */

/* 3362 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3364 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3368 */	NdrFcShort( 0x7 ),	/* 7 */
/* 3370 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3374 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3376 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3378 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3386 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3388 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3390 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3392 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 3394 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3396 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3398 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure stat */

/* 3400 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3402 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3406 */	NdrFcShort( 0xb ),	/* 11 */
/* 3408 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 3410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3412 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3414 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3416 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 3418 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3420 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3424 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 3426 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3428 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3430 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter pVal */

/* 3432 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3434 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3436 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3438 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3440 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3442 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_canInsertDTMF */

/* 3444 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3446 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3450 */	NdrFcShort( 0x7 ),	/* 7 */
/* 3452 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3456 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3458 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3460 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3468 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3470 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3472 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3474 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 3476 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3478 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3480 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure insertDTMF */

/* 3482 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3484 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3490 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 3492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3494 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3496 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3498 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 3500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3502 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3506 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter tones */

/* 3508 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3510 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3512 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter duration */

/* 3514 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3516 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3518 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Parameter interToneGap */

/* 3520 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3522 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3524 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 3526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3528 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 3530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_toneBuffer */

/* 3532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3538 */	NdrFcShort( 0xc ),	/* 12 */
/* 3540 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3546 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3548 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3550 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3556 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3558 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3560 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3562 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3564 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3566 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_duration */

/* 3570 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3572 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3576 */	NdrFcShort( 0xd ),	/* 13 */
/* 3578 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3582 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3584 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3586 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3594 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3596 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3598 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3600 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3602 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3604 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_interToneGap */

/* 3608 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3610 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3614 */	NdrFcShort( 0xe ),	/* 14 */
/* 3616 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3620 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3622 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3624 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3632 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3634 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3636 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3640 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3642 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3644 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ordered */

/* 3646 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3648 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3652 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3654 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3658 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3660 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3662 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3670 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3672 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3674 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3676 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 3678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3680 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_readyState */

/* 3684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3690 */	NdrFcShort( 0xe ),	/* 14 */
/* 3692 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3698 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3700 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3702 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3708 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3710 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3712 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3714 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3716 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3718 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3720 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_bufferedAmount */

/* 3722 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3724 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3728 */	NdrFcShort( 0xf ),	/* 15 */
/* 3730 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3734 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3736 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3738 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3746 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3748 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3750 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3752 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3754 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3756 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_binaryType */

/* 3760 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3762 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3766 */	NdrFcShort( 0x11 ),	/* 17 */
/* 3768 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3772 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3774 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3776 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3780 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3784 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3786 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3788 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3790 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Return value */

/* 3792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3794 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onopen */

/* 3798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3804 */	NdrFcShort( 0x13 ),	/* 19 */
/* 3806 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3812 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3814 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 3816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3818 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3822 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3824 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3826 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3828 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 3830 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3832 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3834 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_onmessage */

/* 3836 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3838 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3842 */	NdrFcShort( 0x19 ),	/* 25 */
/* 3844 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3850 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3852 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 3854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3856 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3860 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3862 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3864 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3866 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 3868 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3870 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3872 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure close */

/* 3874 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3876 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3880 */	NdrFcShort( 0x1a ),	/* 26 */
/* 3882 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3886 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3888 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 3890 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3896 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3898 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 3900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3902 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure send */

/* 3906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3912 */	NdrFcShort( 0x1b ),	/* 27 */
/* 3914 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3920 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3922 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 3924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3926 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3928 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3930 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter data */

/* 3932 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3934 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3936 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */

	/* Return value */

/* 3938 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3940 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3942 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const webrtceverywhere_MIDL_TYPE_FORMAT_STRING webrtceverywhere__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x8 ),	/* 8 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x11, 0x0,	/* FC_RP */
/* 44 */	NdrFcShort( 0x3b8 ),	/* Offset= 952 (996) */
/* 46 */	
			0x12, 0x0,	/* FC_UP */
/* 48 */	NdrFcShort( 0x3a0 ),	/* Offset= 928 (976) */
/* 50 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 52 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 54 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 56 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 58 */	NdrFcShort( 0x2 ),	/* Offset= 2 (60) */
/* 60 */	NdrFcShort( 0x10 ),	/* 16 */
/* 62 */	NdrFcShort( 0x2f ),	/* 47 */
/* 64 */	NdrFcLong( 0x14 ),	/* 20 */
/* 68 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 70 */	NdrFcLong( 0x3 ),	/* 3 */
/* 74 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 76 */	NdrFcLong( 0x11 ),	/* 17 */
/* 80 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 82 */	NdrFcLong( 0x2 ),	/* 2 */
/* 86 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 88 */	NdrFcLong( 0x4 ),	/* 4 */
/* 92 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 94 */	NdrFcLong( 0x5 ),	/* 5 */
/* 98 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 100 */	NdrFcLong( 0xb ),	/* 11 */
/* 104 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 106 */	NdrFcLong( 0xa ),	/* 10 */
/* 110 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 112 */	NdrFcLong( 0x6 ),	/* 6 */
/* 116 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (348) */
/* 118 */	NdrFcLong( 0x7 ),	/* 7 */
/* 122 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 124 */	NdrFcLong( 0x8 ),	/* 8 */
/* 128 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (354) */
/* 130 */	NdrFcLong( 0xd ),	/* 13 */
/* 134 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (358) */
/* 136 */	NdrFcLong( 0x9 ),	/* 9 */
/* 140 */	NdrFcShort( 0xec ),	/* Offset= 236 (376) */
/* 142 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 146 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (394) */
/* 148 */	NdrFcLong( 0x24 ),	/* 36 */
/* 152 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (902) */
/* 154 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 158 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (902) */
/* 160 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 164 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (906) */
/* 166 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 170 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (910) */
/* 172 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 176 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (914) */
/* 178 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 182 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (918) */
/* 184 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 188 */	NdrFcShort( 0x2de ),	/* Offset= 734 (922) */
/* 190 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 194 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (926) */
/* 196 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 200 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (910) */
/* 202 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 206 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (914) */
/* 208 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 212 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (930) */
/* 214 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 218 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (926) */
/* 220 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 224 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (934) */
/* 226 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 230 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (938) */
/* 232 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 236 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (942) */
/* 238 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 242 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (946) */
/* 244 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 248 */	NdrFcShort( 0x2be ),	/* Offset= 702 (950) */
/* 250 */	NdrFcLong( 0x10 ),	/* 16 */
/* 254 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 256 */	NdrFcLong( 0x12 ),	/* 18 */
/* 260 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 262 */	NdrFcLong( 0x13 ),	/* 19 */
/* 266 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 268 */	NdrFcLong( 0x15 ),	/* 21 */
/* 272 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 274 */	NdrFcLong( 0x16 ),	/* 22 */
/* 278 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 280 */	NdrFcLong( 0x17 ),	/* 23 */
/* 284 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 286 */	NdrFcLong( 0xe ),	/* 14 */
/* 290 */	NdrFcShort( 0x29c ),	/* Offset= 668 (958) */
/* 292 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 296 */	NdrFcShort( 0x2a0 ),	/* Offset= 672 (968) */
/* 298 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 302 */	NdrFcShort( 0x29e ),	/* Offset= 670 (972) */
/* 304 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 308 */	NdrFcShort( 0x25a ),	/* Offset= 602 (910) */
/* 310 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 314 */	NdrFcShort( 0x258 ),	/* Offset= 600 (914) */
/* 316 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 320 */	NdrFcShort( 0x256 ),	/* Offset= 598 (918) */
/* 322 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 326 */	NdrFcShort( 0x24c ),	/* Offset= 588 (914) */
/* 328 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 332 */	NdrFcShort( 0x246 ),	/* Offset= 582 (914) */
/* 334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x0 ),	/* Offset= 0 (338) */
/* 340 */	NdrFcLong( 0x1 ),	/* 1 */
/* 344 */	NdrFcShort( 0x0 ),	/* Offset= 0 (344) */
/* 346 */	NdrFcShort( 0xffff ),	/* Offset= -1 (345) */
/* 348 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 352 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 354 */	
			0x12, 0x0,	/* FC_UP */
/* 356 */	NdrFcShort( 0xfeb2 ),	/* Offset= -334 (22) */
/* 358 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 360 */	NdrFcLong( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 368 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 370 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 372 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 374 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 376 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 378 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 386 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 388 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 390 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 392 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 394 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 396 */	NdrFcShort( 0x2 ),	/* Offset= 2 (398) */
/* 398 */	
			0x12, 0x0,	/* FC_UP */
/* 400 */	NdrFcShort( 0x1e4 ),	/* Offset= 484 (884) */
/* 402 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 404 */	NdrFcShort( 0x20 ),	/* 32 */
/* 406 */	NdrFcShort( 0xa ),	/* 10 */
/* 408 */	NdrFcLong( 0x8 ),	/* 8 */
/* 412 */	NdrFcShort( 0x50 ),	/* Offset= 80 (492) */
/* 414 */	NdrFcLong( 0xd ),	/* 13 */
/* 418 */	NdrFcShort( 0x70 ),	/* Offset= 112 (530) */
/* 420 */	NdrFcLong( 0x9 ),	/* 9 */
/* 424 */	NdrFcShort( 0x90 ),	/* Offset= 144 (568) */
/* 426 */	NdrFcLong( 0xc ),	/* 12 */
/* 430 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (606) */
/* 432 */	NdrFcLong( 0x24 ),	/* 36 */
/* 436 */	NdrFcShort( 0x102 ),	/* Offset= 258 (694) */
/* 438 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 442 */	NdrFcShort( 0x11e ),	/* Offset= 286 (728) */
/* 444 */	NdrFcLong( 0x10 ),	/* 16 */
/* 448 */	NdrFcShort( 0x138 ),	/* Offset= 312 (760) */
/* 450 */	NdrFcLong( 0x2 ),	/* 2 */
/* 454 */	NdrFcShort( 0x14e ),	/* Offset= 334 (788) */
/* 456 */	NdrFcLong( 0x3 ),	/* 3 */
/* 460 */	NdrFcShort( 0x164 ),	/* Offset= 356 (816) */
/* 462 */	NdrFcLong( 0x14 ),	/* 20 */
/* 466 */	NdrFcShort( 0x17a ),	/* Offset= 378 (844) */
/* 468 */	NdrFcShort( 0xffff ),	/* Offset= -1 (467) */
/* 470 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 474 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 480 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 484 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 486 */	
			0x12, 0x0,	/* FC_UP */
/* 488 */	NdrFcShort( 0xfe2e ),	/* Offset= -466 (22) */
/* 490 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 492 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 494 */	NdrFcShort( 0x10 ),	/* 16 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 498 */	NdrFcShort( 0x6 ),	/* Offset= 6 (504) */
/* 500 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 502 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 504 */	
			0x11, 0x0,	/* FC_RP */
/* 506 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (470) */
/* 508 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 512 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 518 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 522 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 524 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 526 */	NdrFcShort( 0xff58 ),	/* Offset= -168 (358) */
/* 528 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 530 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 532 */	NdrFcShort( 0x10 ),	/* 16 */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x6 ),	/* Offset= 6 (542) */
/* 538 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 540 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 542 */	
			0x11, 0x0,	/* FC_RP */
/* 544 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (508) */
/* 546 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 556 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 560 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 562 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 564 */	NdrFcShort( 0xff44 ),	/* Offset= -188 (376) */
/* 566 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 568 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 570 */	NdrFcShort( 0x10 ),	/* 16 */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x6 ),	/* Offset= 6 (580) */
/* 576 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 578 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 580 */	
			0x11, 0x0,	/* FC_RP */
/* 582 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (546) */
/* 584 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 588 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 594 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 598 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 600 */	
			0x12, 0x0,	/* FC_UP */
/* 602 */	NdrFcShort( 0x176 ),	/* Offset= 374 (976) */
/* 604 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 606 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 608 */	NdrFcShort( 0x10 ),	/* 16 */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x6 ),	/* Offset= 6 (618) */
/* 614 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 616 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 618 */	
			0x11, 0x0,	/* FC_RP */
/* 620 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (584) */
/* 622 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 624 */	NdrFcLong( 0x2f ),	/* 47 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 634 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 636 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 638 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 640 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 642 */	NdrFcShort( 0x1 ),	/* 1 */
/* 644 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 646 */	NdrFcShort( 0x4 ),	/* 4 */
/* 648 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 650 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 652 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 654 */	NdrFcShort( 0x18 ),	/* 24 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcShort( 0xa ),	/* Offset= 10 (668) */
/* 660 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 662 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 664 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (622) */
/* 666 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 668 */	
			0x12, 0x0,	/* FC_UP */
/* 670 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (640) */
/* 672 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 680 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 682 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 686 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 688 */	
			0x12, 0x0,	/* FC_UP */
/* 690 */	NdrFcShort( 0xffda ),	/* Offset= -38 (652) */
/* 692 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 694 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 696 */	NdrFcShort( 0x10 ),	/* 16 */
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x6 ),	/* Offset= 6 (706) */
/* 702 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 704 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 706 */	
			0x11, 0x0,	/* FC_RP */
/* 708 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (672) */
/* 710 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 712 */	NdrFcShort( 0x8 ),	/* 8 */
/* 714 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 716 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 718 */	NdrFcShort( 0x10 ),	/* 16 */
/* 720 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 722 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 724 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (710) */
			0x5b,		/* FC_END */
/* 728 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 730 */	NdrFcShort( 0x20 ),	/* 32 */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0xa ),	/* Offset= 10 (744) */
/* 736 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 738 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 740 */	0x0,		/* 0 */
			NdrFcShort( 0xffe7 ),	/* Offset= -25 (716) */
			0x5b,		/* FC_END */
/* 744 */	
			0x11, 0x0,	/* FC_RP */
/* 746 */	NdrFcShort( 0xff12 ),	/* Offset= -238 (508) */
/* 748 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 750 */	NdrFcShort( 0x1 ),	/* 1 */
/* 752 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 758 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 760 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 762 */	NdrFcShort( 0x10 ),	/* 16 */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x6 ),	/* Offset= 6 (772) */
/* 768 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 770 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 772 */	
			0x12, 0x0,	/* FC_UP */
/* 774 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (748) */
/* 776 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 778 */	NdrFcShort( 0x2 ),	/* 2 */
/* 780 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 784 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 786 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 788 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 790 */	NdrFcShort( 0x10 ),	/* 16 */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x6 ),	/* Offset= 6 (800) */
/* 796 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 798 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 800 */	
			0x12, 0x0,	/* FC_UP */
/* 802 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (776) */
/* 804 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 806 */	NdrFcShort( 0x4 ),	/* 4 */
/* 808 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 814 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 816 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 818 */	NdrFcShort( 0x10 ),	/* 16 */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	NdrFcShort( 0x6 ),	/* Offset= 6 (828) */
/* 824 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 826 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 828 */	
			0x12, 0x0,	/* FC_UP */
/* 830 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (804) */
/* 832 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 836 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 842 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 844 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 846 */	NdrFcShort( 0x10 ),	/* 16 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x6 ),	/* Offset= 6 (856) */
/* 852 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 854 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 856 */	
			0x12, 0x0,	/* FC_UP */
/* 858 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (832) */
/* 860 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 864 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 866 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 868 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 874 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 876 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 878 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 880 */	NdrFcShort( 0xffec ),	/* Offset= -20 (860) */
/* 882 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 884 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 886 */	NdrFcShort( 0x38 ),	/* 56 */
/* 888 */	NdrFcShort( 0xffec ),	/* Offset= -20 (868) */
/* 890 */	NdrFcShort( 0x0 ),	/* Offset= 0 (890) */
/* 892 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 894 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 896 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 898 */	0x0,		/* 0 */
			NdrFcShort( 0xfe0f ),	/* Offset= -497 (402) */
			0x5b,		/* FC_END */
/* 902 */	
			0x12, 0x0,	/* FC_UP */
/* 904 */	NdrFcShort( 0xff04 ),	/* Offset= -252 (652) */
/* 906 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 908 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 912 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 914 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 916 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 918 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 920 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 922 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 924 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 926 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 928 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 930 */	
			0x12, 0x0,	/* FC_UP */
/* 932 */	NdrFcShort( 0xfdb8 ),	/* Offset= -584 (348) */
/* 934 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 936 */	NdrFcShort( 0xfdba ),	/* Offset= -582 (354) */
/* 938 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 940 */	NdrFcShort( 0xfdba ),	/* Offset= -582 (358) */
/* 942 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 944 */	NdrFcShort( 0xfdc8 ),	/* Offset= -568 (376) */
/* 946 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 948 */	NdrFcShort( 0xfdd6 ),	/* Offset= -554 (394) */
/* 950 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 952 */	NdrFcShort( 0x2 ),	/* Offset= 2 (954) */
/* 954 */	
			0x12, 0x0,	/* FC_UP */
/* 956 */	NdrFcShort( 0x14 ),	/* Offset= 20 (976) */
/* 958 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 960 */	NdrFcShort( 0x10 ),	/* 16 */
/* 962 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 964 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 966 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 968 */	
			0x12, 0x0,	/* FC_UP */
/* 970 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (958) */
/* 972 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 974 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 976 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 978 */	NdrFcShort( 0x20 ),	/* 32 */
/* 980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0x0 ),	/* Offset= 0 (982) */
/* 984 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 986 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 988 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 990 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 992 */	NdrFcShort( 0xfc52 ),	/* Offset= -942 (50) */
/* 994 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 996 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 998 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1000 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0xfc42 ),	/* Offset= -958 (46) */
/* 1006 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1008 */	NdrFcShort( 0xfd88 ),	/* Offset= -632 (376) */
/* 1010 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1012 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1014 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1018 */	NdrFcShort( 0xfd68 ),	/* Offset= -664 (354) */
/* 1020 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1022 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1024 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1026 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1028 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1030 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1036) */
/* 1032 */	
			0x13, 0x0,	/* FC_OP */
/* 1034 */	NdrFcShort( 0xffc6 ),	/* Offset= -58 (976) */
/* 1036 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1038 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1040 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1032) */
/* 1046 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1048 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IWebRTC, ver. 0.0,
   GUID={0x4994FB92,0xA5F5,0x4292,{0xAB,0x60,0x47,0x2A,0xA4,0x93,0x7C,0x9E}} */

#pragma code_seg(".orpc")
static const unsigned short IWebRTC_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    38,
    88,
    126,
    170,
    208,
    258,
    302,
    340,
    390,
    428,
    466,
    504,
    542,
    580,
    618
    };

static const MIDL_STUBLESS_PROXY_INFO IWebRTC_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IWebRTC_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IWebRTC_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IWebRTC_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(23) _IWebRTCProxyVtbl = 
{
    &IWebRTC_ProxyInfo,
    &IID_IWebRTC,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::get_versionName */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::getUserMedia */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::createDisplay */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::createSessionDescription */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::createDictOptions */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::createPeerConnection */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::createIceCandidate */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::createMediaStreamTrack */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::bindEventListener */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::getSources */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::put_src */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::get_videoWidth */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::get_videoHeight */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::fillImageData */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::getScreenShot */ ,
    (void *) (INT_PTR) -1 /* IWebRTC::get_isWebRtcPlugin */
};


static const PRPC_STUB_FUNCTION IWebRTC_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IWebRTCStubVtbl =
{
    &IID_IWebRTC,
    &IWebRTC_ServerInfo,
    23,
    &IWebRTC_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: ISessionDescription, ver. 0.0,
   GUID={0xE7CFEF92,0x42B8,0x40FB,{0xBC,0xA9,0xE7,0x9D,0x39,0xAB,0xCF,0x72}} */

#pragma code_seg(".orpc")
static const unsigned short ISessionDescription_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    656,
    694,
    732
    };

static const MIDL_STUBLESS_PROXY_INFO ISessionDescription_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &ISessionDescription_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISessionDescription_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &ISessionDescription_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _ISessionDescriptionProxyVtbl = 
{
    &ISessionDescription_ProxyInfo,
    &IID_ISessionDescription,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ISessionDescription::get_type */ ,
    (void *) (INT_PTR) -1 /* ISessionDescription::put_type */ ,
    (void *) (INT_PTR) -1 /* ISessionDescription::get_sdp */ ,
    (void *) (INT_PTR) -1 /* ISessionDescription::put_sdp */
};


static const PRPC_STUB_FUNCTION ISessionDescription_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ISessionDescriptionStubVtbl =
{
    &IID_ISessionDescription,
    &ISessionDescription_ServerInfo,
    11,
    &ISessionDescription_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IDictOptions, ver. 0.0,
   GUID={0xFA4B099C,0x3A15,0x4659,{0xB2,0x88,0x56,0x5A,0xD5,0x25,0x8D,0x4B}} */

#pragma code_seg(".orpc")
static const unsigned short IDictOptions_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IDictOptions_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IDictOptions_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDictOptions_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IDictOptions_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IDictOptionsProxyVtbl = 
{
    0,
    &IID_IDictOptions,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IDictOptions_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IDictOptionsStubVtbl =
{
    &IID_IDictOptions,
    &IDictOptions_ServerInfo,
    7,
    &IDictOptions_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IPeerConnection, ver. 0.0,
   GUID={0x462E3805,0x373B,0x46EE,{0x9B,0xEE,0x43,0xE6,0x11,0x0C,0xB7,0x51}} */

#pragma code_seg(".orpc")
static const unsigned short IPeerConnection_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    770,
    38,
    820,
    870,
    908,
    958,
    996,
    1034,
    1078,
    1128,
    1166,
    1204,
    1242,
    1280,
    1324,
    1368,
    1406,
    1438,
    1488,
    1532,
    1582,
    1620,
    1658,
    1696,
    1734,
    1772,
    1810,
    1848,
    1886,
    1924,
    1962,
    2000,
    2038,
    2076
    };

static const MIDL_STUBLESS_PROXY_INFO IPeerConnection_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IPeerConnection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPeerConnection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IPeerConnection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(41) _IPeerConnectionProxyVtbl = 
{
    &IPeerConnection_ProxyInfo,
    &IID_IPeerConnection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::createOffer */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::createAnswer */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::setLocalDescription */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_localDescription */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::setRemoteDescription */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_remoteDescription */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_signalingState */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::updateIce */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::addIceCandidate */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_iceGatheringState */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_iceConnectionState */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::getLocalStreams */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::getRemoteStreams */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::getStreamById */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::addStream */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::removeStream */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::close */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::getStats */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::createDTMFSender */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::createDataChannel */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_onnegotiationneeded */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::put_onnegotiationneeded */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_onicecandidate */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::put_onicecandidate */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_onsignalingstatechange */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::put_onsignalingstatechange */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_onaddstream */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::put_onaddstream */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_onremovestream */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::put_onremovestream */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_oniceconnectionstatechange */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::put_oniceconnectionstatechange */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::get_ondatachannel */ ,
    (void *) (INT_PTR) -1 /* IPeerConnection::put_ondatachannel */
};


static const PRPC_STUB_FUNCTION IPeerConnection_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IPeerConnectionStubVtbl =
{
    &IID_IPeerConnection,
    &IPeerConnection_ServerInfo,
    41,
    &IPeerConnection_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMediaStream, ver. 0.0,
   GUID={0x21745AC4,0x2C31,0x481C,{0xAB,0x07,0x83,0x4C,0x4D,0x0E,0x28,0x7A}} */

#pragma code_seg(".orpc")
static const unsigned short IMediaStream_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    2114,
    2152,
    2190,
    2234,
    2272,
    2310,
    2348,
    2386,
    390,
    2424,
    2462,
    1242,
    542,
    2500
    };

static const MIDL_STUBLESS_PROXY_INFO IMediaStream_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaStream_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMediaStream_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaStream_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(22) _IMediaStreamProxyVtbl = 
{
    &IMediaStream_ProxyInfo,
    &IID_IMediaStream,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::get_id */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::getAudioTracks */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::getVideoTracks */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::getTrackById */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::addTrack */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::removeTrack */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::clone */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::get_ended */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::get_onended */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::put_onended */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::get_onaddtrack */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::put_onaddtrack */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::get_onremovetrack */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::put_onremovetrack */ ,
    (void *) (INT_PTR) -1 /* IMediaStream::stop */
};


static const PRPC_STUB_FUNCTION IMediaStream_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMediaStreamStubVtbl =
{
    &IID_IMediaStream,
    &IMediaStream_ServerInfo,
    22,
    &IMediaStream_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCIceCandidate, ver. 0.0,
   GUID={0xFBE8F87D,0xBD47,0x4325,{0x91,0x96,0x7A,0x36,0xF3,0x39,0xEE,0x2A}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCIceCandidate_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    2532,
    2570
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCIceCandidate_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCIceCandidate_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCIceCandidate_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCIceCandidate_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCIceCandidateProxyVtbl = 
{
    &IRTCIceCandidate_ProxyInfo,
    &IID_IRTCIceCandidate,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCIceCandidate::get_candidate */ ,
    (void *) (INT_PTR) -1 /* IRTCIceCandidate::get_sdpMid */ ,
    (void *) (INT_PTR) -1 /* IRTCIceCandidate::get_sdpMLineIndex */
};


static const PRPC_STUB_FUNCTION IRTCIceCandidate_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCIceCandidateStubVtbl =
{
    &IID_IRTCIceCandidate,
    &IRTCIceCandidate_ServerInfo,
    10,
    &IRTCIceCandidate_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMediaStreamTrack, ver. 0.0,
   GUID={0xEDD26AE0,0xB068,0x4918,{0x82,0x6D,0xE7,0x5B,0xBE,0x84,0x4B,0x71}} */

#pragma code_seg(".orpc")
static const unsigned short IMediaStreamTrack_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    2532,
    694,
    2608,
    2646,
    2684,
    2310,
    2722,
    2386,
    390,
    2760,
    2798,
    2836,
    2874,
    2912,
    2950,
    2988,
    3026,
    3064,
    3102,
    1582,
    1620,
    1658,
    1696,
    1734,
    3140
    };

static const MIDL_STUBLESS_PROXY_INFO IMediaStreamTrack_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaStreamTrack_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMediaStreamTrack_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaStreamTrack_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(33) _IMediaStreamTrackProxyVtbl = 
{
    &IMediaStreamTrack_ProxyInfo,
    &IID_IMediaStreamTrack,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_kind */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_id */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_label */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_enabled */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::put_enabled */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_muted */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_onmute */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::put_onmute */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_onunmute */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::put_onunmute */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_readonly */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_remote */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_readyState */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_onstarted */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::put_onstarted */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_onended */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::put_onended */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::getSourceInfos */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::constraints */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::states */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::capabilities */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::applyConstraints */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::get_onoverconstrained */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::put_onoverconstrained */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::clone */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamTrack::stop */
};


static const PRPC_STUB_FUNCTION IMediaStreamTrack_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMediaStreamTrackStubVtbl =
{
    &IID_IMediaStreamTrack,
    &IMediaStreamTrack_ServerInfo,
    33,
    &IMediaStreamTrack_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: ISourceInfo, ver. 0.0,
   GUID={0xBCD116DA,0xB4BC,0x472E,{0xA6,0xAE,0x36,0x3D,0x13,0xB7,0x86,0x67}} */

#pragma code_seg(".orpc")
static const unsigned short ISourceInfo_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    2532,
    694,
    3172,
    3210
    };

static const MIDL_STUBLESS_PROXY_INFO ISourceInfo_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &ISourceInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISourceInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &ISourceInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _ISourceInfoProxyVtbl = 
{
    &ISourceInfo_ProxyInfo,
    &IID_ISourceInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ISourceInfo::get_sourceId */ ,
    (void *) (INT_PTR) -1 /* ISourceInfo::get_id */ ,
    (void *) (INT_PTR) -1 /* ISourceInfo::get_kind */ ,
    (void *) (INT_PTR) -1 /* ISourceInfo::get_label */ ,
    (void *) (INT_PTR) -1 /* ISourceInfo::get_facing */
};


static const PRPC_STUB_FUNCTION ISourceInfo_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ISourceInfoStubVtbl =
{
    &IID_ISourceInfo,
    &ISourceInfo_ServerInfo,
    12,
    &ISourceInfo_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMediaSourceStates, ver. 0.0,
   GUID={0x7A2B697F,0x688A,0x4CBE,{0xB3,0x6F,0x48,0x20,0xD1,0x2B,0xAE,0x61}} */

#pragma code_seg(".orpc")
static const unsigned short IMediaSourceStates_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    2532,
    2152,
    870,
    3248,
    958,
    2310,
    3286
    };

static const MIDL_STUBLESS_PROXY_INFO IMediaSourceStates_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaSourceStates_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMediaSourceStates_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaSourceStates_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _IMediaSourceStatesProxyVtbl = 
{
    &IMediaSourceStates_ProxyInfo,
    &IID_IMediaSourceStates,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_sourceType */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_sourceId */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_width */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_height */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_frameRate */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_aspectRatio */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_facingMode */ ,
    (void *) (INT_PTR) -1 /* IMediaSourceStates::get_volume */
};


static const PRPC_STUB_FUNCTION IMediaSourceStates_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IMediaSourceStatesStubVtbl =
{
    &IID_IMediaSourceStates,
    &IMediaSourceStates_ServerInfo,
    15,
    &IMediaSourceStates_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMediaStreamEvent, ver. 0.0,
   GUID={0xEAB6AB59,0x5B8E,0x4096,{0xAA,0x67,0x0D,0x55,0x7A,0xA6,0xBB,0x32}} */

#pragma code_seg(".orpc")
static const unsigned short IMediaStreamEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3324
    };

static const MIDL_STUBLESS_PROXY_INFO IMediaStreamEvent_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaStreamEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMediaStreamEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMediaStreamEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IMediaStreamEventProxyVtbl = 
{
    &IMediaStreamEvent_ProxyInfo,
    &IID_IMediaStreamEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMediaStreamEvent::get_stream */
};


static const PRPC_STUB_FUNCTION IMediaStreamEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IMediaStreamEventStubVtbl =
{
    &IID_IMediaStreamEvent,
    &IMediaStreamEvent_ServerInfo,
    8,
    &IMediaStreamEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCPeerConnectionIceEvent, ver. 0.0,
   GUID={0x354C2E39,0x380F,0x4F24,{0xAE,0xEA,0x68,0x7E,0xB6,0x7F,0x75,0x9D}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPeerConnectionIceEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3324
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPeerConnectionIceEvent_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCPeerConnectionIceEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPeerConnectionIceEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCPeerConnectionIceEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCPeerConnectionIceEventProxyVtbl = 
{
    &IRTCPeerConnectionIceEvent_ProxyInfo,
    &IID_IRTCPeerConnectionIceEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCPeerConnectionIceEvent::get_candidate */
};


static const PRPC_STUB_FUNCTION IRTCPeerConnectionIceEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCPeerConnectionIceEventStubVtbl =
{
    &IID_IRTCPeerConnectionIceEvent,
    &IRTCPeerConnectionIceEvent_ServerInfo,
    8,
    &IRTCPeerConnectionIceEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCStatsReport, ver. 0.0,
   GUID={0x455118D0,0xA29F,0x44DB,{0xAC,0xF7,0xFE,0x22,0xBF,0xAE,0x21,0x67}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCStatsReport_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3324
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCStatsReport_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCStatsReport_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCStatsReport_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCStatsReport_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCStatsReportProxyVtbl = 
{
    &IRTCStatsReport_ProxyInfo,
    &IID_IRTCStatsReport,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCStatsReport::result */
};


static const PRPC_STUB_FUNCTION IRTCStatsReport_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCStatsReportStubVtbl =
{
    &IID_IRTCStatsReport,
    &IRTCStatsReport_ServerInfo,
    8,
    &IRTCStatsReport_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCStats, ver. 0.0,
   GUID={0xCEFEB782,0xAFEC,0x4D0D,{0x8C,0x62,0xF1,0xE2,0x55,0xA7,0x38,0x41}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCStats_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3362,
    2532,
    694,
    870,
    3400
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCStats_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCStats_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCStats_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCStats_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IRTCStatsProxyVtbl = 
{
    &IRTCStats_ProxyInfo,
    &IID_IRTCStats,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCStats::get_timestamp */ ,
    (void *) (INT_PTR) -1 /* IRTCStats::get_type */ ,
    (void *) (INT_PTR) -1 /* IRTCStats::get_id */ ,
    (void *) (INT_PTR) -1 /* IRTCStats::names */ ,
    (void *) (INT_PTR) -1 /* IRTCStats::stat */
};


static const PRPC_STUB_FUNCTION IRTCStats_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCStatsStubVtbl =
{
    &IID_IRTCStats,
    &IRTCStats_ServerInfo,
    12,
    &IRTCStats_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCDTMFSender, ver. 0.0,
   GUID={0x3FA7AEBF,0xDD1D,0x4F4A,{0xB7,0xAE,0x8B,0xD8,0x78,0xAF,0x78,0x09}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCDTMFSender_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3444,
    3482,
    2152,
    870,
    2234,
    3532,
    3570,
    3608
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCDTMFSender_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDTMFSender_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCDTMFSender_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDTMFSender_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _IRTCDTMFSenderProxyVtbl = 
{
    &IRTCDTMFSender_ProxyInfo,
    &IID_IRTCDTMFSender,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::get_canInsertDTMF */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::insertDTMF */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::get_track */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::get_ontonechange */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::put_ontonechange */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::get_toneBuffer */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::get_duration */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFSender::get_interToneGap */
};


static const PRPC_STUB_FUNCTION IRTCDTMFSender_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCDTMFSenderStubVtbl =
{
    &IID_IRTCDTMFSender,
    &IRTCDTMFSender_ServerInfo,
    15,
    &IRTCDTMFSender_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCDTMFToneChangeEvent, ver. 0.0,
   GUID={0xE01CBEE1,0x8442,0x40FF,{0x81,0xCC,0x20,0x71,0x4A,0x49,0xCC,0x39}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCDTMFToneChangeEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCDTMFToneChangeEvent_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDTMFToneChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCDTMFToneChangeEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDTMFToneChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCDTMFToneChangeEventProxyVtbl = 
{
    &IRTCDTMFToneChangeEvent_ProxyInfo,
    &IID_IRTCDTMFToneChangeEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCDTMFToneChangeEvent::get_tone */
};


static const PRPC_STUB_FUNCTION IRTCDTMFToneChangeEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCDTMFToneChangeEventStubVtbl =
{
    &IID_IRTCDTMFToneChangeEvent,
    &IRTCDTMFToneChangeEvent_ServerInfo,
    8,
    &IRTCDTMFToneChangeEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCDataChannel, ver. 0.0,
   GUID={0x453AFDA0,0x2936,0x48C3,{0xBE,0x41,0xD0,0x59,0x30,0x22,0x17,0xC2}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCDataChannel_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    3646,
    2152,
    870,
    3210,
    2684,
    2310,
    3684,
    3722,
    1128,
    3760,
    1204,
    3798,
    2874,
    2912,
    2950,
    2988,
    3026,
    3836,
    3874,
    3906
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCDataChannel_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDataChannel_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCDataChannel_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDataChannel_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(28) _IRTCDataChannelProxyVtbl = 
{
    &IRTCDataChannel_ProxyInfo,
    &IID_IRTCDataChannel,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_label */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_ordered */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_maxRetransmitTime */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_maxRetransmits */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_protocol */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_negotiated */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_id */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_readyState */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_bufferedAmount */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_binaryType */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::put_binaryType */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_onopen */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::put_onopen */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_onerror */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::put_onerror */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_onclose */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::put_onclose */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::get_onmessage */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::put_onmessage */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::close */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannel::send */
};


static const PRPC_STUB_FUNCTION IRTCDataChannel_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCDataChannelStubVtbl =
{
    &IID_IRTCDataChannel,
    &IRTCDataChannel_ServerInfo,
    28,
    &IRTCDataChannel_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMessageEvent, ver. 0.0,
   GUID={0x2C5FD5A1,0x29F3,0x4CFF,{0x94,0xB6,0x71,0x1A,0x77,0xF0,0xCB,0x61}} */

#pragma code_seg(".orpc")
static const unsigned short IMessageEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3324
    };

static const MIDL_STUBLESS_PROXY_INFO IMessageEvent_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMessageEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMessageEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IMessageEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IMessageEventProxyVtbl = 
{
    &IMessageEvent_ProxyInfo,
    &IID_IMessageEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMessageEvent::get_data */
};


static const PRPC_STUB_FUNCTION IMessageEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IMessageEventStubVtbl =
{
    &IID_IMessageEvent,
    &IMessageEvent_ServerInfo,
    8,
    &IMessageEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCDataChannelEvent, ver. 0.0,
   GUID={0x51E8910B,0x881C,0x43DE,{0xB2,0x11,0x28,0xC4,0x31,0x07,0xC6,0xA1}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCDataChannelEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    3324
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCDataChannelEvent_ProxyInfo =
    {
    &Object_StubDesc,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDataChannelEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCDataChannelEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    webrtceverywhere__MIDL_ProcFormatString.Format,
    &IRTCDataChannelEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCDataChannelEventProxyVtbl = 
{
    &IRTCDataChannelEvent_ProxyInfo,
    &IID_IRTCDataChannelEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCDataChannelEvent::get_channel */
};


static const PRPC_STUB_FUNCTION IRTCDataChannelEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCDataChannelEventStubVtbl =
{
    &IID_IRTCDataChannelEvent,
    &IRTCDataChannelEvent_ServerInfo,
    8,
    &IRTCDataChannelEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    webrtceverywhere__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _webrtceverywhere_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IPeerConnectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCDataChannelEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPeerConnectionIceEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMediaStreamEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCIceCandidateProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMediaSourceStatesProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCStatsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISessionDescriptionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IWebRTCProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDictOptionsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCDataChannelProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMessageEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCDTMFSenderProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMediaStreamProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCStatsReportProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISourceInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMediaStreamTrackProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCDTMFToneChangeEventProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _webrtceverywhere_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IPeerConnectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCDataChannelEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPeerConnectionIceEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IMediaStreamEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCIceCandidateStubVtbl,
    ( CInterfaceStubVtbl *) &_IMediaSourceStatesStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCStatsStubVtbl,
    ( CInterfaceStubVtbl *) &_ISessionDescriptionStubVtbl,
    ( CInterfaceStubVtbl *) &_IWebRTCStubVtbl,
    ( CInterfaceStubVtbl *) &_IDictOptionsStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCDataChannelStubVtbl,
    ( CInterfaceStubVtbl *) &_IMessageEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCDTMFSenderStubVtbl,
    ( CInterfaceStubVtbl *) &_IMediaStreamStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCStatsReportStubVtbl,
    ( CInterfaceStubVtbl *) &_ISourceInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_IMediaStreamTrackStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCDTMFToneChangeEventStubVtbl,
    0
};

PCInterfaceName const _webrtceverywhere_InterfaceNamesList[] = 
{
    "IPeerConnection",
    "IRTCDataChannelEvent",
    "IRTCPeerConnectionIceEvent",
    "IMediaStreamEvent",
    "IRTCIceCandidate",
    "IMediaSourceStates",
    "IRTCStats",
    "ISessionDescription",
    "IWebRTC",
    "IDictOptions",
    "IRTCDataChannel",
    "IMessageEvent",
    "IRTCDTMFSender",
    "IMediaStream",
    "IRTCStatsReport",
    "ISourceInfo",
    "IMediaStreamTrack",
    "IRTCDTMFToneChangeEvent",
    0
};

const IID *  const _webrtceverywhere_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _webrtceverywhere_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _webrtceverywhere, pIID, n)

int __stdcall _webrtceverywhere_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _webrtceverywhere, 18, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _webrtceverywhere, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _webrtceverywhere, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _webrtceverywhere, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _webrtceverywhere, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _webrtceverywhere, 18, *pIndex )
    
}

const ExtendedProxyFileInfo webrtceverywhere_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _webrtceverywhere_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _webrtceverywhere_StubVtblList,
    (const PCInterfaceName * ) & _webrtceverywhere_InterfaceNamesList,
    (const IID ** ) & _webrtceverywhere_BaseIIDList,
    & _webrtceverywhere_IID_Lookup, 
    18,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

