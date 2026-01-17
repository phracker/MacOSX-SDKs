//
//  ImageKit.h
//  ImageKit
//
//  Copyright 2006-2018 Apple. All rights reserved.
//
#ifndef __IMAGEKITBASE__
#define __IMAGEKITBASE__

#include <os/availability.h>
#include <TargetConditionals.h>

#if IMAGEKIT_BUILDING_IMAGEKIT

#	define IK_API_DEPRECATED(...)
#	define IK_AVAILABLE(_macIntro)
#	define IK_CLASS_AVAILABLE(_macIntro)
#	define IK_ENUM_AVAILABLE(_macIntro)

#else

#	define IK_API_DEPRECATED API_DEPRECATED
#	define IK_AVAILABLE(_macIntro)  NS_AVAILABLE_MAC(_macIntro)
#	define IK_CLASS_AVAILABLE(_macIntro) NS_CLASS_AVAILABLE_MAC(_macIntro)
#	define IK_ENUM_AVAILABLE(_macIntro) NS_ENUM_AVAILABLE_MAC(_macIntro)

#endif

#endif // __IMAGEKITBASE__


