/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaStreamConstraints
#ifndef _WEBRTC_EVERYWHERE_COMMON_MEDIATRACKCONSTRAINT_H_
#define _WEBRTC_EVERYWHERE_COMMON_MEDIATRACKCONSTRAINT_H_

#include "_Config.h"
#include "_Common.h"

#include <map>

class _Buffer;

typedef enum __MediaTrackConstraintsType
{
	_MediaTrackConstraintsTypeUnknown,
	_MediaTrackConstraintsTypeBoolean,
	_MediaTrackConstraintsTypeComposite
} _MediaTrackConstraintsType;

class WEBRTC_EVERYWHERE_API _MediaTrackConstraints
{
public:
	_MediaTrackConstraints(bool bVal);
	_MediaTrackConstraints(cpp11::shared_ptr<_MediaConstraints> mandatory = nullPtr, cpp11::shared_ptr<_MediaConstraints> optional = nullPtr);
	virtual ~_MediaTrackConstraints();

	WE_INLINE _MediaTrackConstraintsType type()const { return m_eType; }
	WE_INLINE bool isBool()const { return type() == _MediaTrackConstraintsTypeBoolean; }
	WE_INLINE bool boolVal()const { return m_bValue; }
	WE_INLINE const cpp11::shared_ptr<_MediaConstraints> mandatory()const { return m_mandatory; }
	WE_INLINE const cpp11::shared_ptr<_MediaConstraints> optional()const { return m_optional; }

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	_MediaTrackConstraintsType m_eType;
	bool m_bValue; // only if type is _MediaTrackConstraintsTypeBoolean
	cpp11::shared_ptr<_MediaConstraints> m_mandatory; // only if type is _MediaTrackConstraintsTypeComposite
	cpp11::shared_ptr<_MediaConstraints> m_optional; // only if type is _MediaTrackConstraintsTypeComposite
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_MEDIATRACKCONSTRAINT_H_ */
