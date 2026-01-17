#if !__has_include(<PassKitCore/PKIdentityDocument.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityDocument.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents the response of a request for an identity document.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKIdentityDocument: NSObject

/// An encrypted data blob containing the requested document information and associated metadata.
/// This is encrypted to the public key on-file with the Developer portal for the calling app, and should
/// be passed to the server holding the corresponding private key for decryption.
/// This data is not intended to be read on-device.
@property (nonatomic, readonly) NSData *encryptedData;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIdentityDocument.h>
#endif