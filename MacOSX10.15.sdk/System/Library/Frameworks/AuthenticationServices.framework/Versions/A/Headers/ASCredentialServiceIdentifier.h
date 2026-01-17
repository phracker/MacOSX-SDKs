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
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macCatalyst, macos, tvos, watchos) NS_SWIFT_NAME(ASCredentialServiceIdentifier.IdentifierType);

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macCatalyst, macos, tvos, watchos)
@interface ASCredentialServiceIdentifier : NSObject <NSCopying, NSSecureCoding>

/*! @abstract Initializes an ASCredentialServiceIdentifier object.
 @param identifier string value for the service identifier.
 @param type the type that the service identifier string represents.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier type:(ASCredentialServiceIdentifierType)type;

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
