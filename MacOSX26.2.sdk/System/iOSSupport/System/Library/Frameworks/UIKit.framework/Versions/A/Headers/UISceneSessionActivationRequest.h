#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneSessionActivationRequest.h>)
//
//  UISceneSessionActivationRequest.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UISceneDefinitions.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UISceneSession, UISceneActivationRequestOptions;

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface UISceneSessionActivationRequest : NSObject <NSCopying>

/// The role to request. If the request was created using `requestWithSession:`, this reflects
/// the role of the `session`.
@property (nonatomic, readonly) UISceneSessionRole role;

/// The specific scene session that should be activated, if provided when creating the request.
@property (nonatomic, nullable, readonly) UISceneSession *session;

/// An optional user activity to send to the newly activated scene.
///
/// Only sessions with a matching `role` will have their `activationConditions` evaluated
/// against the user activity's `targetContentIdentifier`.
@property (nonatomic, nullable, strong) NSUserActivity *userActivity;

/// Optional parameters used for further customizing the request.
@property (nonatomic, nullable, copy) UISceneActivationRequestOptions *options;

/// Creates a request for activating a session with the role of `UIWindowSceneSessionRoleApplication`.
+ (instancetype)request;

/// Creates a request for activating a session with the specified `role`.
/// - Parameter role: The requested scene session role.
+ (instancetype)requestWithRole:(UISceneSessionRole)role;

/// Creates a request for activating an existing scene session.
/// - Parameter session: The existing session to activate.
+ (instancetype)requestWithSession:(UISceneSession *)session;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneSessionActivationRequest.h>
#endif
