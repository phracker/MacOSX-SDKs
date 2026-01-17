/*
     File:       DiscRecording/DiscRecording.h
 
     Contains:   DiscRecording interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2007 Apple Inc.  All Rights Reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DiscRecording
#define _H_DiscRecording

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#import <CoreServices/CoreServices.h>
#endif

#ifndef _H_DRCoreBurn
#import <DiscRecording/DRCoreBurn.h>
#endif

#ifndef _H_DRCoreCDText
#import <DiscRecording/DRCoreCDText.h>
#endif

#ifndef _H_DRCoreDevice
#import <DiscRecording/DRCoreDevice.h>
#endif

#ifndef _H_DRCoreErase
#import <DiscRecording/DRCoreErase.h>
#endif

#ifndef _H_DRCoreErrors
#import <DiscRecording/DRCoreErrors.h>
#endif

#ifndef _H_DRCoreNotifications
#import <DiscRecording/DRCoreNotifications.h>
#endif

#ifndef _H_DRCoreObject
#import <DiscRecording/DRCoreObject.h>
#endif

#ifndef _H_DRCoreStatus
#import <DiscRecording/DRCoreStatus.h>
#endif

#ifndef _H_DRCoreTrack
#import <DiscRecording/DRCoreTrack.h>
#endif

#ifndef _H_DRContentFolder
#import <DiscRecording/DRContentFolder.h>
#endif

#ifndef _H_DRContentFile
#import <DiscRecording/DRContentFile.h>
#endif

#ifndef _H_DRContentProperties
#import <DiscRecording/DRContentProperties.h>
#endif

#ifndef _H_DRContentTrack
#import <DiscRecording/DRContentTrack.h>
#endif

#ifdef __OBJC__
#import <DiscRecording/DRBurn.h>
#import <DiscRecording/DRBurn_ContentSupport.h>
#import <DiscRecording/DRCDText.h>
#import <DiscRecording/DRDevice.h>
#import <DiscRecording/DRErase.h>
#import <DiscRecording/DRFile.h>
#import <DiscRecording/DRFolder.h>
#import <DiscRecording/DRFSObject.h>
#import <DiscRecording/DRMSF.h>
#import <DiscRecording/DRMSFFormatter.h>
#import <DiscRecording/DRNotificationCenter.h>
#import <DiscRecording/DRStatus.h>
#import <DiscRecording/DRTrack.h>
#import <DiscRecording/DRTrack_ContentSupport.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
	
NumVersion DRGetVersion(void);
	
	
#ifdef __cplusplus
}
#endif
#endif /* _H_DiscRecording */
