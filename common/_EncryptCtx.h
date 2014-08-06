/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_ENCRYPTCTX_H_
#define _WEBRTC_EVERYWHERE_COMMON_ENCRYPTCTX_H_

#include "_Config.h"
#include "_Buffer.h"

class WEBRTC_EVERYWHERE_API _EncryptCtx
{
public:
	_EncryptCtx();
	virtual ~_EncryptCtx();

	WeError Encrypt(const cpp11::shared_ptr<_Buffer> &in, cpp11::shared_ptr<_Buffer> &out);
	WeError Decrypt(const cpp11::shared_ptr<_Buffer> &in, cpp11::shared_ptr<_Buffer> &out);

private:
	WeError Op(const cpp11::shared_ptr<_Buffer> &in, cpp11::shared_ptr<_Buffer> &out, bool encrypt);

private:
	struct PK11SymKeyStr* m_SymKey;
	struct SECItemStr* m_SecParam;
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_ENCRYPTCTX_H_ */
