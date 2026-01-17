/*!
 * @header CoreWLAN.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

// For more information and/or to provide feedback, contact CoreWLAN-Feedback@group.apple.com

#ifndef _CORE_WLAN_H_
#define _CORE_WLAN_H_

// CoreWLAN Framework Version
extern double CoreWLANFrameworkVersionNumber;
#define CoreWLANFrameworkVersionNumber2_0 200

#ifdef __OBJC__

#import <CoreWLAN/CoreWLANTypes.h>
#import <CoreWLAN/CoreWLANConstants.h>
#import <CoreWLAN/CoreWLANUtil.h>
#import <CoreWLAN/CWInterface.h>
#import <CoreWLAN/CWNetwork.h>
#import <CoreWLAN/CWConfiguration.h>
#import <CoreWLAN/CWNetworkProfile.h>
#import <CoreWLAN/CWChannel.h>

// Legacy
#import <CoreWLAN/CWGlobals.h>
#import <CoreWLAN/CWWirelessProfile.h>
#import <CoreWLAN/CW8021XProfile.h>

#endif

/*!
 * @framework CoreWLAN
 * @abstract CoreWLAN Objective-C public application programming interface
 * @discussion This framework supports Objective-C garbage collection.  This framework is daemon-safe.
 */

#endif /* _CORE_WLAN_H_ */
