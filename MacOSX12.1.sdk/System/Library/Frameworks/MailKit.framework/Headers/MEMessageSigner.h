//
//  MEMessageSigner.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MEEmailAddress;

NS_ASSUME_NONNULL_BEGIN

/// @brief Contains information about a message signer
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@interface MEMessageSigner : NSObject <NSSecureCoding>

/// @brief Email addresses associated with the signature.
@property (nonatomic, readonly, copy) NSArray<MEEmailAddress *> *emailAddresses;

/// @brief The message signers label. Shown in the message header view. For instance, "John Smith".
@property (nonatomic, readonly, copy) NSString *label;

/// @brief The context for the message signature. This might include the signing certificate. This will be passed back to the extension for
/// either verifying the signature or if the user wishes to view signature information.
@property (nonatomic, readonly) NSData *context;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithEmailAddresses:(NSArray<MEEmailAddress *> *)emailAddresses signatureLabel:(NSString *)label context:(nullable NSData *)context;
@end

NS_ASSUME_NONNULL_END
