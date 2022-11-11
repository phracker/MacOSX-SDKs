// Copyright © 2021 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * ASAuthorizationCustomMethod NS_TYPED_ENUM API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios, macos, watchos);

/// An authorization method that uses the VideoSubscriberAccount framework to sign in.
AS_EXTERN ASAuthorizationCustomMethod const ASAuthorizationCustomMethodVideoSubscriberAccount API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios, macos, watchos);

/// An authorization method that restores an in-app purchase to sign in.
AS_EXTERN ASAuthorizationCustomMethod const ASAuthorizationCustomMethodRestorePurchase API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios, macos, watchos);

/// An authorization method that uses some other sign-in mechanism.
AS_EXTERN ASAuthorizationCustomMethod const ASAuthorizationCustomMethodOther API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios, macos, watchos);

NS_ASSUME_NONNULL_END
