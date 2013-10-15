/*
     File:       DiscRecordingEngine/DiscRecordingEngine.h
 
     Contains:   DiscRecordingEngine interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DiscRecordingEngine
#define _H_DiscRecordingEngine

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef _H_DRCoreBurn
#include <DiscRecordingEngine/DRCoreBurn.h>
#endif

#ifndef _H_DRCoreCDText
#include <DiscRecordingEngine/DRCoreCDText.h>
#endif

#ifndef _H_DRCoreDevice
#include <DiscRecordingEngine/DRCoreDevice.h>
#endif

#ifndef _H_DRCoreErase
#include <DiscRecordingEngine/DRCoreErase.h>
#endif

#ifndef _H_DRCoreStatus
#include <DiscRecordingEngine/DRCoreStatus.h>
#endif

#ifndef _H_DRCoreErrors
#include <DiscRecordingEngine/DRCoreErrors.h>
#endif

#ifndef _H_DRCoreNotifications
#include <DiscRecordingEngine/DRCoreNotifications.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecordingEngine/DRCoreObject.h>
#endif

#ifndef _H_DRCoreTrack
#include <DiscRecordingEngine/DRCoreTrack.h>
#endif

#ifdef __OBJC__
#import <DiscRecordingEngine/DRBurn.h>
#import <DiscRecordingEngine/DRCDText.h>
#import <DiscRecordingEngine/DRDevice.h>
#import <DiscRecordingEngine/DRMSF.h>
#import <DiscRecordingEngine/DRMSFFormatter.h>
#import <DiscRecordingEngine/DRErase.h>
#import <DiscRecordingEngine/DRNotificationCenter.h>
#import <DiscRecordingEngine/DRStatus.h>
#import <DiscRecordingEngine/DRTrack.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


NumVersion DRGetVersion(void);


#ifdef __cplusplus
}
#endif

#endif /* _H_DiscRecordingEngine */
