//
//  ASCredentialServiceIdentifier.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum ASCredentialServiceIdentifierType
 @abstract The type of value represented by the service identifier.
 @constant ASCredentialServiceIdentifierTypeDomain The service identifier represents a domain name that conforms to RFC 1035.
 @constant ASCredentialServiceIdentifierTypeURL The service identifier represents a URL that conforms to RFC 1738.
 */
typedef NS_ENUM(NSInteger, ASCredentialServiceIdentifierType) {
    ASCredentialServiceIdentifierTypeDomain,
    ASCredentialServiceIdentifierTypeURL,
    /// The service identifier represents an App ID. When a service identifier of this type is provided to your extension for saving a password,
    /// the ASCredentialServiceIdentifier object will have a non-nil `displayName` property that contains a user friendly name for the app.
    ASCredentialServiceIdentifierTypeApp API_AVAILABLE(ios(26.2), macos(26.2), visionos(26.2)) API_UNAVAILABLE(tvos, watchos),
} API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NAME(ASCredentialServiceIdentifier.IdentifierType);

AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASCredentialServiceIdentifier : NSObject <NSCopying, NSSecureCoding>

/*! @abstract Initializes an ASCredentialServiceIdentifier object.
 @param identifier string value for the service identifier.
 @param type the type that the service identifier string represents.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier type:(ASCredentialServiceIdentifierType)type;

/// Initializes an ASCredentialServiceIdentifier object.
///
/// - Parameters:
///   - identifier: The string value for the service identifier.
///   - type: The type that the service identifier string represents.
///   - displayName: A user visible name that describes the service.
- (instancetype)initWithIdentifier:(NSString *)identifier type:(ASCredentialServiceIdentifierType)type displayName:(NSString *)displayName API_AVAILABLE(ios(26.2), macos(26.2), visionos(26.2)) API_UNAVAILABLE(tvos, watchos);

/// A user visible name for the identifier. For `app` types it will contain the localized name of the app. For `URL` types it will contain the host name of the URL if it contains a valid host.
/// For `URL` type identifiers that do not contain a valid host and for `domain` type identifiers, this will be equal to `identifier`.
/// This property is meant only as a best effort suggestion for display purposes. It is not used by the system to identify the service or suggest a credential for AutoFill.
@property (nonatomic, nullable, readonly, copy) NSString *displayName API_AVAILABLE(ios(26.2), macos(26.2), visionos(26.2)) API_UNAVAILABLE(tvos, watchos);

/*! @abstract Get the identifier.
 @result The service identifier.
 */
@property (nonatomic, readonly, copy) NSString *identifier;

/*! @abstract Get the service identifier type.
 @result The service identifier type.
 */
@property (nonatomic, readonly) ASCredentialServiceIdentifierType type;

@end

NS_ASSUME_NONNULL_END
