//
//  VSAutoSignInAuthorization.h
//  VideoSubscriberAccount
//
//  Created by Felipe (fcy) Cypriano on 2/26/25.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>
#import <Foundation/Foundation.h>


/// Auto sign in authorization state.
typedef NS_ENUM(NSInteger, VSAutoSignInAuthorization) {
    /// Consent to auto sign in hasn't been granted nor denied.
    VSAutoSignInAuthorizationNotDetermined = 0,
    /// Authorized to store and use auto sign in tokens.
    VSAutoSignInAuthorizationGranted,
    /// Consent to use auto sign in has been denied.
    VSAutoSignInAuthorizationDenied
} NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0), tvos(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, macCatalyst);

