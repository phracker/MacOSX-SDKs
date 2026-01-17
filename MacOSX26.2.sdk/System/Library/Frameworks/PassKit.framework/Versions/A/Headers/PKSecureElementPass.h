#if !__has_include(<PassKitCore/PKSecureElementPass.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKSecureElementPass.h
//    PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#ifndef __PKSECUREELEMENTPASS_H
#define __PKSECUREELEMENTPASS_H

#import <PassKit/PKPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKSecureElementPassActivationState) {
    PKSecureElementPassActivationStateActivated,
    PKSecureElementPassActivationStateRequiresActivation,
    PKSecureElementPassActivationStateActivating,
    PKSecureElementPassActivationStateSuspended,
    PKSecureElementPassActivationStateDeactivated,
} NS_SWIFT_NAME(PKSecureElementPass.PassActivationState) API_AVAILABLE(macos(11.0), ios(13.4), watchos(6.2));

API_AVAILABLE(macos(11.0), ios(13.4), watchos(6.2))
@interface PKSecureElementPass : PKPass

@property (nonatomic, copy, readonly) NSString *primaryAccountIdentifier;
@property (nonatomic, copy, readonly) NSString *primaryAccountNumberSuffix;
@property (strong, readonly) NSString *deviceAccountIdentifier;
@property (strong, readonly) NSString *deviceAccountNumberSuffix;
@property (nonatomic, readonly) PKSecureElementPassActivationState passActivationState;

@property (nonatomic, copy, readonly, nullable) NSString *devicePassIdentifier;
@property (nonatomic, copy, readonly, nullable) NSString *pairedTerminalIdentifier;

@end

NS_ASSUME_NONNULL_END

#endif // __PKSECUREELEMENTPASS_H

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKSecureElementPass.h>
#endif