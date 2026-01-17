/*
     File:       DiscRecordingUI/DiscRecordingUI.h
 
     Contains:   DiscRecordingUI interfaces.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifdef __OBJC__

#import <DiscRecordingUI/DRSetupPanel.h>
#import <DiscRecordingUI/DRBurnSetupPanel.h>
#import <DiscRecordingUI/DREraseSetupPanel.h>

#import <DiscRecordingUI/DRBurnProgressPanel.h>
#import <DiscRecordingUI/DREraseProgressPanel.h>

#import <DiscRecordingUI/DiscRecordingUIResources.h>

#else

#ifndef _H_DiscRecordingUI
#define _H_DiscRecordingUI

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef _H_DRBurnSession
#include <DiscRecordingUI/DRBurnSession.h>
#endif

#ifndef _H_DREraseSession
#include <DiscRecordingUI/DREraseSession.h>
#endif

#endif

#endif /* _H_DiscRecordingUI */


