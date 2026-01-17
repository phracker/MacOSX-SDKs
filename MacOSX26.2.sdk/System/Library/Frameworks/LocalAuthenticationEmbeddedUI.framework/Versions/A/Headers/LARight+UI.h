//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LARight.h>
#import <LocalAuthenticationEmbeddedUI/LAPresentationContext.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Groups methods that control aspects of the UI used for authorizing a right
API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
@interface LARight (UI)

/// @brief Tries to authorize the right.
/// @param localizedReason Localized explanation for the authorization. Appears in the UI presented to the user.
/// @param presentationContext Container where the authorization UI will be presented.
/// @param handler Completion handler called after the authorization finishses. Returns an error when the authorization fails.
- (void)authorizeWithLocalizedReason:(NSString *)localizedReason
               inPresentationContext:(LAPresentationContext)presentationContext
                          completion:(void (^)(NSError *_Nullable))handler
NS_SWIFT_NAME(authorize(localizedReason:in:completion:));

@end

NS_ASSUME_NONNULL_END
