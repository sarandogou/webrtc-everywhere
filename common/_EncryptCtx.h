/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_ENCRYPTCTX_H_
#define _WEBRTC_EVERYWHERE_COMMON_ENCRYPTCTX_H_

#include "_Config.h"
#include "_Buffer.h"

class WEBRTC_EVERYWHERE_API _EncryptCtx
{
protected:
	_EncryptCtx() {}
public:
	virtual ~_EncryptCtx() {}

	virtual WeError Encrypt(const cpp11::shared_ptr<_Buffer> &in, cpp11::shared_ptr<_Buffer> &out) = 0;
	virtual WeError Decrypt(const cpp11::shared_ptr<_Buffer> &in, cpp11::shared_ptr<_Buffer> &out) = 0;

	static _EncryptCtx* New();
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_ENCRYPTCTX_H_ */
