//
//  VSAutoSignInTokenUpdateContext.h
//  VideoSubscriberAccountFramework
//
//  Created by Felipe (fcy) Cypriano on 2/26/25.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>


#import <VideoSubscriberAccount/VSAutoSignInAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/// Context object used to update the auto sign in token.
/// This object has to be obtained through a user consent flow using `-[VSUserAccountManager requestAutoSignInAuthorizationWithCompletionHandler:]`,
/// then it is passed to `-[VSUserAccountManager updateAutoSignInToken:updateContext:completionHandler:]`
VS_EXPORT API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(macos, watchos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
@interface VSAutoSignInTokenUpdateContext : NSObject

@property (nonatomic, readonly) VSAutoSignInAuthorization authorization;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

