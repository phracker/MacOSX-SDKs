//
//  MEMessageSecurityInformation.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MEMessageSigner;

NS_ASSUME_NONNULL_BEGIN

/// @brief Contains security information about a decoded message
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@interface MEMessageSecurityInformation : NSObject <NSSecureCoding>

/// @brief The signers of the message
@property (nonatomic, readonly, strong) NSArray<MEMessageSigner *> *signers;

/// @brief Whether or not the message was encrypted.
@property (nonatomic, readonly, assign) BOOL isEncrypted;

/// @brief Any signing error that occured when decoding the message.
@property (nonatomic, nullable, readonly, strong) NSError *signingError;

/// @brief Any encryption error that occured when decoding the message.
@property (nonatomic, nullable, readonly, strong) NSError *encryptionError;

/// @brief Whether or not Mail should block loading remote content for the message by default. The user will have the option to load remote content manually.
@property (nonatomic, readonly, assign) BOOL shouldBlockRemoteContent;

/// @brief A localized string containing the reason for blocking remote content.
@property (nonatomic, nullable, readonly, strong) NSString * localizedRemoteContentBlockingReason;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithSigners:(NSArray<MEMessageSigner *> *)signers isEncrypted:(BOOL)isEncrypted signingError:(nullable NSError *)signingError encryptionError:(nullable NSError *)encryptionError;
- (instancetype)initWithSigners:(NSArray<MEMessageSigner *> *)signers isEncrypted:(BOOL)isEncrypted signingError:(nullable NSError *)signingError encryptionError:(nullable NSError *)encryptionError shouldBlockRemoteContent:(BOOL)shouldBlockRemoteContent localizedRemoteContentBlockingReason:(nullable NSString *)localizedRemoteContentBlockingReason;
@end

NS_ASSUME_NONNULL_END
