//
//  ATTrackingManager.h
//  AppTrackingTransparency
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ATTrackingManagerAuthorizationStatus) {
    ATTrackingManagerAuthorizationStatusNotDetermined = 0,
    ATTrackingManagerAuthorizationStatusRestricted,
    ATTrackingManagerAuthorizationStatusDenied,
    ATTrackingManagerAuthorizationStatusAuthorized
} NS_SWIFT_NAME(ATTrackingManager.AuthorizationStatus) API_AVAILABLE(ios(14), macosx(11.0), tvos(14));

API_AVAILABLE(ios(14), macosx(11.0), tvos(14))
@interface ATTrackingManager : NSObject

/*!
 * @property trackingAuthorizationStatus
 *
 * @abstract
 * Returns information about your application’s tracking authorization status.
 * Users are able to grant or deny developers tracking privileges on a per-app basis.
 * Application developers must call `requestTrackingAuthorizationWithCompletionHandler:` for the ability to track users.
 *
 * @result
 * The current authorization status. If the user has not yet been prompted to approve access, the return value will either be
 * ATTrackingManagerAuthorizationStatusNotDetermined, or ATTrackingManagerAuthorizationStatusRestricted if this value is managed.
 * Once the user has been prompted, the return value will be either ATTrackingManagerAuthorizationStatusDenied or ATTrackingManagerAuthorizationStatusAuthorized.
 */
@property (class, nonatomic, readonly, assign) ATTrackingManagerAuthorizationStatus trackingAuthorizationStatus;

/*!
 * @method requestTrackingAuthorizationWithCompletionHandler:completion:
 *
 * @abstract
 * Request user tracking authorization with a completion handler returning the user's authorization status.
 * Users are able to grant or deny developers tracking privileges on a per-app basis.
 * This method allows developers to determine if access has been granted. On first use, this method will prompt the user to grant or deny access.
 *
 * The completion handler will be called with the result of the user's decision for granting or denying permission to use application tracking.
 * The completion handler will be called immediately if access to request authorization is restricted.
 */
+ (void)requestTrackingAuthorizationWithCompletionHandler:(void(^)(ATTrackingManagerAuthorizationStatus status))completion;

// This class, at this time, should not be instantiated.
+ (instancetype)new NS_UNAVAILABLE;

// This class, at this time, should not be instantiated.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
