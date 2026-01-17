//
//  CSBase.h
//  CoreSpotlight
//
//  Copyright © 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#if !defined(CORESPOTLIGHT_EXPORT)
#define CORESPOTLIGHT_EXPORT extern
#endif

#ifndef CS_AVAILABLE
#define CS_AVAILABLE(mac, ios) NS_AVAILABLE(10_11, ios)
#endif

#ifndef CS_CLASS_AVAILABLE
#define CS_CLASS_AVAILABLE(mac, ios) NS_CLASS_AVAILABLE(10_11, ios)
#endif

#ifndef CS_DEPRECATED
#define CS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) NS_DEPRECATED(10_11, 10_11, _iosIntro, _iosDep, __VA_ARGS__)
#endif

#ifndef CS_TVOS_UNAVAILABLE
#define CS_TVOS_UNAVAILABLE __TVOS_PROHIBITED
#endif
