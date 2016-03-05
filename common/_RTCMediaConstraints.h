/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_RTCMEDIACONSTRAINTS_H_
#define _WEBRTC_EVERYWHERE_COMMON_RTCMEDIACONSTRAINTS_H_

#include "_Config.h"

#include "talk/app/webrtc/mediaconstraintsinterface.h"
#include "webrtc/base/refcount.h"

class _RTCMediaConstraints 
	: public webrtc::MediaConstraintsInterface
	, public rtc::RefCountInterface
{
public:
	_RTCMediaConstraints();
	_RTCMediaConstraints(const Constraints& mandatory, const Constraints& optional);
	virtual ~_RTCMediaConstraints();

	// MediaConstraintsInterface
	virtual const Constraints& GetMandatory() const { return m_mandatory; }
	virtual const Constraints& GetOptional() const { return m_optional; };

	void AddOptional(const std::string& key, const std::string& value);
	bool AddMandatory(const std::string& key, const std::string& value, bool override_if_exists = true);

private:
	Constraints m_mandatory;
	Constraints m_optional;
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_RTCMEDIACONSTRAINTS_H_ */
