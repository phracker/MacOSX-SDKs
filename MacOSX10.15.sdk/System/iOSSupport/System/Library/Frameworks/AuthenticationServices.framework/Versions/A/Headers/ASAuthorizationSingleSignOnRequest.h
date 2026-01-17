//
//  ASAuthorizationSingleSignOnRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationOpenIDRequest.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), macCatalyst(13.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationSingleSignOnRequest : ASAuthorizationOpenIDRequest

/*! @abstract Parameters required by the specific Authorization Server which should be used by the selected Authorization Services extension for authorization.
 */
@property(nonatomic, copy) NSArray<NSURLQueryItem *> *authorizationOptions;

@end

NS_ASSUME_NONNULL_END
