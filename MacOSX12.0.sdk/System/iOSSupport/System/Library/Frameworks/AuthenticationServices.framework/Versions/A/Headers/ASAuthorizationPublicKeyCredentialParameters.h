// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASCOSEConstants.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPublicKeyCredentialParameters: NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithAlgorithm:(ASCOSEAlgorithmIdentifier)algorithm;

/*! @abstract A COSE algorithm indentifier. */
@property (nonatomic, readonly) ASCOSEAlgorithmIdentifier algorithm;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
