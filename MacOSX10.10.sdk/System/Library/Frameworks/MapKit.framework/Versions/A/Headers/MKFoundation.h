//
//  MKFoundation.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Availability.h>

#ifdef __cplusplus
#define MK_EXTERN       extern "C" __attribute__((visibility ("default")))
#else
#define MK_EXTERN       extern __attribute__((visibility ("default")))
#endif

#define MK_CLASS_AVAILABLE(_macIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_macIntro, _iphoneIntro)
#define MK_CLASS_DEPRECATED(_macIntro, _macDep, _iphoneIntro, _iphoneDep) __attribute__((visibility("default"))) NS_DEPRECATED(_macIntro, macDep, _iphoneIntro,_iphoneDep)
