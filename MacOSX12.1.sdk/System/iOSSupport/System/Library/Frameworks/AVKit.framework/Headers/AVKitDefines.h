#if !__has_include(<AVKitCore/AVKitDefines.h>)
/*
	File:  AVKitDefines.h
	
	Framework:  AVKit
	
	Copyright © 2014-2016 Apple Inc. All rights reserved.
	
 */

#import <Availability.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define AVKIT_EXTERN	extern "C" __attribute__((visibility ("default")))
#else
#define AVKIT_EXTERN	extern __attribute__((visibility ("default")))
#endif

#if !TARGET_IS_AVKITMACHELPER
#define AVKIT_ONLY_EXTERN AVKIT_EXTERN
#define AVKIT_ONLY_API_AVAILABLE(...) API_AVAILABLE(__VA_ARGS__)
#else
#define AVKIT_ONLY_EXTERN extern __attribute__((visibility ("hidden")))
#define AVKIT_ONLY_API_AVAILABLE(...)
#endif

#define PLATFORM_SUPPORTS_AVKITCORE (TARGET_OS_OSX || TARGET_OS_MACCATALYST)

#else
#import <AVKitCore/AVKitDefines.h>
#endif
