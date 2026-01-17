/*
     File:       DiscRecordingContent/DiscRecordingContent.h
 
     Contains:   DiscRecordingContent interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DiscRecordingContent
#define _H_DiscRecordingContent

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef _H_DRContentFolder
#include <DiscRecordingContent/DRContentFolder.h>
#endif

#ifndef _H_DRContentFile
#include <DiscRecordingContent/DRContentFile.h>
#endif

#ifndef _H_DRContentProperties
#include <DiscRecordingContent/DRContentProperties.h>
#endif

#ifndef _H_DRContentTrack
#include <DiscRecordingContent/DRContentTrack.h>
#endif

#ifdef __OBJC__
#import <DiscRecordingContent/DRFile.h>
#import <DiscRecordingContent/DRFolder.h>
#import <DiscRecordingContent/DRFSObject.h>
#import <DiscRecordingContent/DRBurn_ContentSupport.h>
#import <DiscRecordingContent/DRTrack_ContentSupport.h>
#endif

#endif /* _H_DiscRecordingContent */
