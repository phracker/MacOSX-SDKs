#if !__has_include(<PassKitCore/PKIdentityRequest.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityRequest.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <PassKit/PKIdentityDocumentDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

/// Request for information from an identity document stored as a Wallet pass.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKIdentityRequest: NSObject

/// A descriptor describing the identity document to request.
@property (nonatomic, nullable, strong) id<PKIdentityDocumentDescriptor> descriptor;

/// A caller-specified nonce that will be included in the signed response payload.
/// This is treated as opaque by the PKIdentityAuthorizationController, and has a
/// maximum allowed size of 64 bytes.
@property (nonatomic, nullable, copy) NSData *nonce;

/// Identifies the merchant making the request, as previously agreed with Apple.
/// This must match one of the merchant identifiers in the application's entitlement.
/// This property must be set when requestDocument is invoked.
@property (nonatomic, nullable, copy) NSString *merchantIdentifier;

/// A key in the NSIdentityUsageDescriptionDictionary field of the app's
/// Info.plist file.
///
/// The value for this key is an app-provided string that describes the
/// reason for requesting identity information.
@property (nonatomic, nullable, copy) NSString *usageDescriptionKey API_AVAILABLE(ios(26.2), visionos(26.2));

@end

NS_ASSUME_NONNULL_END


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIdentityRequest.h>
#endif