/*
  GLKitBase.h
  GLKit

  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
*/

#import <TargetConditionals.h>
#import <os/availability.h>
#if TARGET_OS_IPHONE && (!defined(TARGET_OS_MACCATALYST) || !TARGET_OS_MACCATALYST)
#import <OpenGLES/gltypes.h>
#else // !TARGET_OS_IPHONE
#import <OpenGL/gltypes.h>
#endif // !TARGET_OS_IPHONE
#define GLK_INLINE	static __inline__

#ifdef __cplusplus
	#define GLK_EXTERN extern "C"
#else
	#define GLK_EXTERN extern 
#endif

#if TARGET_OS_IPHONE && (!defined(TARGET_OS_MACCATALYST) || !TARGET_OS_MACCATALYST)
#import <OpenGLES/OpenGLESAvailability.h>
#define OPENGL_DEPRECATED(...)
#else
#import <OpenGL/OpenGLAvailability.h>
#define OPENGLES_DEPRECATED(...)
#endif

