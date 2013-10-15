/*!
 * @header CoreWLAN.h
 * @copyright 2009 Apple Inc. All rights reserved.
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_H_
#define _CORE_WLAN_H_

#define COREWLAN_VERSION_1_0	1.0

#ifdef __OBJC__

#import <CoreWLAN/CWGlobals.h>
#import <CoreWLAN/CWInterface.h>
#import <CoreWLAN/CWNetwork.h>
#import <CoreWLAN/CWConfiguration.h>
#import <CoreWLAN/CWWirelessProfile.h>
#import <CoreWLAN/CW8021XProfile.h>

#endif

/*!
 * @framework CoreWLAN API
 * @abstract CoreWLAN Objective-C Public API
 * @discussion Provides developers with a means to query and change parameters of an CoreWLAN interface,
 * scan for networks, access configuration parameters, associate to networks, and create computer-to-computer networks.
 * This framework supports Objective-C garbage collection.  This framework is not daemon-safe.
 */

#endif /* _CORE_WLAN_H_ */