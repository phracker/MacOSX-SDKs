//
//  SCNBase.h
//
//  Copyright (c) 2012-2014 Apple Inc. All rights reserved.
//

/*! @header SCNBase
    @abstract Various defines used throughout SceneKit
 */

#define SCN_EXTERN FOUNDATION_EXTERN

#ifndef __has_feature      // Optional.
#define __has_feature(x) 0 // Compatibility with non-clang compilers.
#endif

#define SCENEKIT_CLASS_AVAILABLE(_mac, _ios)                             NS_CLASS_AVAILABLE(_mac, _ios)
#define SCENEKIT_AVAILABLE(_mac, _ios)                                   NS_AVAILABLE(_mac, _ios)
#define SCENEKIT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) NS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, __VA_ARGS__)
#define SCENEKIT_ENUM_AVAILABLE(_mac, _ios)                              NS_ENUM_AVAILABLE(_mac, _ios)
