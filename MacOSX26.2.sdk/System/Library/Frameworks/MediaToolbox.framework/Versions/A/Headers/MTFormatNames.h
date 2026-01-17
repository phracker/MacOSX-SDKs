/*
	File:  MTFormatNames.h
 
	Framework:  MediaToolbox
 
	Copyright © 2015-2018 Apple Inc. All rights reserved.
 
*/

#ifndef MTFORMATNAME_H
#define MTFORMATNAME_H

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMFormatDescription.h>

#ifdef __cplusplus
extern "C"  {
#endif

#pragma pack(push, 4)

MT_EXPORT CFStringRef CM_RETURNS_RETAINED CM_NULLABLE MTCopyLocalizedNameForMediaType( CMMediaType mediaType ) API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

MT_EXPORT CFStringRef CM_RETURNS_RETAINED CM_NULLABLE MTCopyLocalizedNameForMediaSubType( CMMediaType mediaType, FourCharCode mediaSubType ) API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif	// MTFORMATNAME_H
