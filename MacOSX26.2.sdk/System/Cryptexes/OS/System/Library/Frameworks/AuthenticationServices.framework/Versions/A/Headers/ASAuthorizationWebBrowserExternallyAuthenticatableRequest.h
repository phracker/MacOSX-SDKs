// Copyright © 2022 Apple Inc. All rights reserved.

@class LAContext;

API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos)
@protocol ASAuthorizationWebBrowserExternallyAuthenticatableRequest <NSObject>
@property (nonatomic, nullable) LAContext *authenticatedContext;
@end
