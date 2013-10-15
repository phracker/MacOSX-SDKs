/*------------------------------------------------------------------------------------------------------------------------------
 *
 *  ICADevices/ICADevices.h
 *
 *  Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 *  For bug reports, consult the following page onthe World Wide Web:
 *  http://developer.apple.com/bugreporter/
 *
 *----------------------------------------------------------------------------------------------------------------------------*/

#pragma once

#ifndef __ICADEVICES__
#define __ICADEVICES__

//------------------------------------------------------------------------------------------------------------------------------

#import <Carbon/Carbon.h>
#import <ICADevices/ICD_CameraCalls.h>
#import <ICADevices/ICD_ScannerCalls.h>

//------------------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------------------------------------------------------

ICAError        ICDAddImageInfoToNotificationDictionary( CFMutableDictionaryRef dict, UInt32 width, UInt32 height, UInt32 bytesPerRow, UInt32 dataStartRow, UInt32 dataNumberOfRows, UInt32 dataSize, void* dataBuffer );

ICAError        ICDSendNotification( ICASendNotificationPB* pb );

ICAError        ICDSendNotificationAndWaitForReply( ICASendNotificationPB* pb );

//------------------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------------------------------------------------------

#endif /* __ICADEVICES__ */

//------------------------------------------------------------------------------------------------------------------------------
