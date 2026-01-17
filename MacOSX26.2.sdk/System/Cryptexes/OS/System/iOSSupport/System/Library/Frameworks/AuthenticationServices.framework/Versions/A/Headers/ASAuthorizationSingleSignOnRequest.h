//
//  ASAuthorizationSingleSignOnRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationOpenIDRequest.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), macCatalyst(13.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationSingleSignOnRequest : ASAuthorizationOpenIDRequest

/*! @abstract Parameters required by the specific Authorization Server which should be used by the selected Authorization Services extension for authorization.
 */
@property(nonatomic, copy) NSArray<NSURLQueryItem *> *authorizationOptions;

/*! @abstract Enables or disables the authorization user interface.
 @discussion The default values is YES. If user interface is not enabled, then the authorization will fail with @see ASAuthorizationErrorNotInteractive if it attempts to display the authorization user interface.
*/
@property (nonatomic, getter=isUserInterfaceEnabled) BOOL userInterfaceEnabled API_AVAILABLE(ios(15.0), macos(12.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
