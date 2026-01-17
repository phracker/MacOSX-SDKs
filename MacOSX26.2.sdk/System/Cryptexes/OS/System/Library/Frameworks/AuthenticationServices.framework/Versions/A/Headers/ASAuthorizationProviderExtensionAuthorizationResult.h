//
//  ASAuthorizationProviderExtensionAuthorizationResult.h
//  AuthenticationServices Framework
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASAuthorizationProviderExtensionAuthorizationResult : NSObject

/*! @abstract Authorization succeeded with an authorization tokens stored in HTTP headers.
 */
- (instancetype)initWithHTTPAuthorizationHeaders:(NSDictionary<NSString *, NSString *> *)httpAuthorizationHeaders  NS_SWIFT_NAME(init(httpAuthorizationHeaders:)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Authorization succeeded with a HTTP response.
 */
- (instancetype)initWithHTTPResponse:(NSHTTPURLResponse *)httpResponse httpBody:(nullable NSData *)httpBody NS_SWIFT_NAME(init(httpResponse:httpBody:)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract HTTP extra headers for addition with credentials.
 */
@property (nonatomic, nullable) NSDictionary<NSString *, NSString *> *httpAuthorizationHeaders;

/*! @abstract HTTP response for OAUth and SAML based authentications.
 */
@property (copy, nonatomic, nullable) NSHTTPURLResponse *httpResponse;

/*! @abstract HTTP response body for OAUth and SAML based authentications.
 */
@property (nonatomic, nullable) NSData *httpBody;

/*! @abstract Private SecKeys.
 */
@property (nonatomic) NSArray *privateKeys NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
