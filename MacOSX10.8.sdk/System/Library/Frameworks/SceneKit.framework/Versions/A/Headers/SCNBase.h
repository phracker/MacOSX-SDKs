//
//  SCNBase.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

/*! @header SCNBase
    @abstract Various defines used throughout SceneKit
 */

#ifdef __cplusplus
#define SCENEKIT_EXTERN		extern "C"
#else
#define SCENEKIT_EXTERN		extern
#endif



#define SCENEKIT_INLINE static inline
#define SCENEKIT_DEPRECATED __attribute__((deprecated))

#ifndef __has_feature      // Optional.
#define __has_feature(x) 0 // Compatibility with non-clang compilers.
#endif

#if __has_feature(attribute_objc_ivar_unused)
#define SCENEKIT_UNUSED __attribute__((unused))
#else
#define SCENEKIT_UNUSED
#endif

#ifdef NS_CLASS_AVAILABLE

#if TARGET_OS_IPHONE
#define SCENEKIT_AVAILABLE(x,y)
#else
#define SCENEKIT_AVAILABLE NS_CLASS_AVAILABLE
#endif

#else
#define SCENEKIT_AVAILABLE(x,y)
#endif


