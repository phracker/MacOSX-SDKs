/*
 *  CTTelephonyNetworkInfo.h
 *  CoreTelephony
 *
 *  Copyright 2009 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CTRadioAccessTechnologyDataTechnologyDidChangeNotification
 *
 * Description:
 *     A NSNotification broadcast when radio access technology changes
 */
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyDidChangeNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 * Radio Access Technology values
 */
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyGPRS          __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyEdge          __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyWCDMA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyHSDPA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyHSUPA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMA1x        __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORev0  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORevA  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORevB  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyeHRPD         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyLTE           __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@class CTCarrier;

/*
 *  CTTelephonyNetworkInfo
 *  
 *  Discussion:
 *    The CTTelephonyNetworkInfo object is your entry point to the telephony service.
 */
CORETELEPHONY_CLASS_AVAILABLE(4_0)
@interface CTTelephonyNetworkInfo : NSObject

/*
 * subscriberCellularProvider
 *
 * Discussion:
 *   A CTCarrier object that contains information about the subscriber's
 *   home cellular service provider.
 */
@property(readonly, retain, nullable) CTCarrier *subscriberCellularProvider __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * subscriberCellularProviderDidUpdateNotifier
 *
 * Discussion:
 *   A block that will be dispatched on the default priority global dispatch
 *   queue when the subscriber's cellular provider information updates. Set
 *   this property to a block that is defined in your application to
 *   receive the newly updated information.
 */
@property(nonatomic, copy, nullable) void (^subscriberCellularProviderDidUpdateNotifier)(CTCarrier*) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * currentRadioAccessTechnology
 *
 * Discussion:
 *   The current radio access technology the device is registered with. May be NULL
 *   if device is not registered on any network.
 */
@property (nonatomic, readonly, retain, nullable) NSString* currentRadioAccessTechnology __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@end

NS_ASSUME_NONNULL_END

