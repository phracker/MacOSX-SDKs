/*
  GLKitBase.h
  GLKit

  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
*/

#import <TargetConditionals.h>

#define GLK_INLINE	static __inline__

#ifdef __cplusplus
	#define GLK_EXTERN extern "C"
#else
	#define GLK_EXTERN extern 
#endif

