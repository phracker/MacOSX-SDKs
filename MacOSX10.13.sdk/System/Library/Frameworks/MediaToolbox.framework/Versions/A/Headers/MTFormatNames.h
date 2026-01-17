/*
	File:  MTFormatNames.h
 
	Framework:  MediaToolbox
 
	Copyright 2015 Apple Inc. All rights reserved.
 
*/

#ifndef MTFORMATNAME_H
#define MTFORMATNAME_H

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMFormatDescription.h>

#ifdef __cplusplus
extern "C"  {
#endif

#pragma pack(push, 4)

MT_EXPORT CFStringRef CM_NULLABLE MTCopyLocalizedNameForMediaType( CMMediaType mediaType );

MT_EXPORT CFStringRef CM_NULLABLE MTCopyLocalizedNameForMediaSubType( CMMediaType mediaType, FourCharCode mediaSubType );

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif	// MTFORMATNAME_H
