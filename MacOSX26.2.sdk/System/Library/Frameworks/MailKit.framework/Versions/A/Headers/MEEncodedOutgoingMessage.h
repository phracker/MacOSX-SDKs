//
//  MEEncodedOutgoingMessage.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <MailKit/MEMessageEncoder.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@interface MEEncodedOutgoingMessage : NSObject <NSSecureCoding>

- (instancetype)initWithRawData:(NSData *)rawData isSigned:(BOOL)isSigned isEncrypted:(BOOL)isEncrypted;

/// @brief The full encoded RFC822 message including headers and body.
@property (nonatomic, readonly, copy) NSData *rawData;

/// @brief Whether or not the encoded message is signed
@property (nonatomic, readonly, assign) BOOL isSigned;

/// @brief Whether or not the encoded message is encrypted
@property (nonatomic, readonly, assign) BOOL isEncrypted;

@end

NS_ASSUME_NONNULL_END
