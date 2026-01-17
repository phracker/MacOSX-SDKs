//
//  ASWebAuthenticationSessionWebBrowserSessionManager.h
//  AuthenticationServices Framework
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import "ASWebAuthenticationSessionWebBrowserSessionHandling.h"
#import "ASFoundation.h"

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos)
@interface ASWebAuthenticationSessionWebBrowserSessionManager : NSObject

@property (class, readonly, nonatomic) ASWebAuthenticationSessionWebBrowserSessionManager *sharedManager;
@property (nonatomic) id<ASWebAuthenticationSessionWebBrowserSessionHandling> sessionHandler;
@property (nonatomic, readonly) BOOL wasLaunchedByAuthenticationServices;

@end

NS_ASSUME_NONNULL_END
