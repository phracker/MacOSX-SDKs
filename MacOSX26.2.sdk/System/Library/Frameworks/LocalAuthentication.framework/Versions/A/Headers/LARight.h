//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class LAAuthenticationRequirement;
@protocol LARightDelegate;

#pragma mark -

/// @brief Each of the different states of a right
typedef NS_ENUM(NSInteger, LARightState) {
    /// @brief Right has not been evaluated yet.
    /// @discussion This is the initial state of @c LARight and changes when @c authorize method is called.
    LARightStateUnknown = 0,

    /// @brief Requirements are currently being evaluated.
    /// @discussion This happens after calling @c authorize method but before the user has granted the right.
    LARightStateAuthorizing = 1,

    /// @brief Authorization was granted
    /// @discussion This can be achieved by succesful authorization.
    LARightStateAuthorized = 2,

    /// @brief Authorization was rejected.
    /// @discussion This can be caused by several reasons. For example requirements were not satisified or user rejects to authorize.
    LARightStateNotAuthorized = 3,
} NS_SWIFT_NAME(LARight.State) API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos);

#pragma mark -

API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
/// @brief Groups a set of requirements that need to be satisfied in order to grant access to certain resource or operation
@interface LARight: NSObject

#pragma mark - Properties

/// @brief Provides the current authorization state of the @c LARight instance
@property (nonatomic, readonly) LARightState state;

/// @brief An application-supplied integer that can be used to identify right intances. The default value is @c 0.
@property (nonatomic) NSInteger tag;

#pragma mark - Initialization

/// @brief Constructs a right using default authorization requirements
/// @discussion For authorizing a right with default requirements a user will be asked to authenticate using biometry or the device passcode.
/// @return @c LARight instance
- (instancetype)init;

/// @brief Constructs a right that will be granted only when the given @c LAAuthenticationRequirement is statisfied.
/// @param requirement Requirement that needs to be satisfied to authorize the right
/// @return @c LARight instance
- (instancetype)initWithRequirement:(LAAuthenticationRequirement *)requirement;

#pragma mark - Auth operations

/// @brief Tries to authorize the right.
/// @param localizedReason Localized explanation for the authorization. Appears in the UI presented to the user.
/// @param handler Completion handler called after the authorization finishes. Returns an error when the authorization fails.
- (void)authorizeWithLocalizedReason:(NSString *)localizedReason completion:(void (NS_SWIFT_SENDABLE ^)(NSError *_Nullable error))handler NS_SWIFT_NAME(authorize(localizedReason:completion:));

/// @brief Checks whether the client can eventually be granted the right.
/// @param handler Completion handler. Returns @c nil if the right can be authorized or an error otherwise.
- (void)checkCanAuthorizeWithCompletion:(void (NS_SWIFT_SENDABLE ^)(NSError *_Nullable error))handler;

/// @brief Invalidates a previously authorized right.
/// @param handler Completion handler called after the right is deauthorized.
- (void)deauthorizeWithCompletion:(void (^)(void))handler;

@end

NS_ASSUME_NONNULL_END
