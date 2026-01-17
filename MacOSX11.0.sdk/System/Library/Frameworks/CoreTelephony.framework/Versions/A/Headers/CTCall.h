/*
 *  CTCall.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_EXTERN NSString * const CTCallStateDialing  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCall.h> properties");
CORETELEPHONY_EXTERN NSString * const CTCallStateIncoming  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCall.h> properties");
CORETELEPHONY_EXTERN NSString * const CTCallStateConnected  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCall.h> properties");
CORETELEPHONY_EXTERN NSString * const CTCallStateDisconnected  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCall.h> properties");

CORETELEPHONY_CLASS_AVAILABLE(4_0)
@interface CTCall : NSObject
{
@private
    NSString *_callState;
    NSString *_callID;
}

/*
 * callState
 *
 * Description:
 *     An NSString constant that describes the state of this call. The initial state
 *     will be either CTCallStateDialing or CTCallStateIncoming, will transition
 *     to CTCallStateConnected when the call is established with all parties 
 *     involved and will move to CTCallStateDisconnected when this call is terminated.
 */
@property(nonatomic, readonly, copy) NSString *callState  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCall.h> properties");

/*
 * callID
 *
 * Description:
 *     A unique identifier for this call to be used by clients to differentiate
 *     multiple active calls.
 */
@property(nonatomic, readonly, copy) NSString *callID  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_4_0, __IPHONE_10_0, "Replaced by <CallKit/CXCall.h> properties");

@end

NS_ASSUME_NONNULL_END
