/*
 *  CTCallCenter.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

@class CTCall;

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(4_0)
@interface CTCallCenter : NSObject

/*
 * currentCalls
 *
 * Discussion:
 *   An array containing CTCall objects for all calls that are currently
 *   in progress. If no calls are active, this will be nil.
 *
 */
@property(readonly, retain, nullable) NSSet<CTCall*> *currentCalls __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCallObserver.h>");

/*
 * callEventHandler
 *
 * Discussion:
 *   A block that will be dispatched on the default priority global dispatch
 *   queue when a new call event occurs. Set this property to a block
 *   that is defined in your application to handle call events.
 */
@property(nonatomic, copy, nullable) void (^callEventHandler)(CTCall*) __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCallObserver.h>");

@end

NS_ASSUME_NONNULL_END
