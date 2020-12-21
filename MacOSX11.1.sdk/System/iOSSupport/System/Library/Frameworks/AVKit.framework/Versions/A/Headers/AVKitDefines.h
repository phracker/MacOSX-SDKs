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
