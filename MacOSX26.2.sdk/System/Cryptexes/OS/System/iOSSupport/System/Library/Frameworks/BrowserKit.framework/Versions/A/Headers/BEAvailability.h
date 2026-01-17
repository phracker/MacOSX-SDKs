// Copyright © 2025 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/* @enum BEEligibilityContext
 @abstract The context for which eligibility should be queried.
 @constant BEEligibilityContextWebBrowser   Eligible for alternative Browser Engines in Web browsers.
 */
typedef NS_ENUM(NSInteger, BEEligibilityContext) {
    BEEligibilityContextWebBrowser,
} NS_SWIFT_NAME(BEAvailability.Context) API_AVAILABLE(ios(18.4));

API_AVAILABLE(ios(18.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEAvailability : NSObject
/* @abstract Check eligibility for context.
 @param context The context for which eligibility will be queried
 @param completionHandler The completion handler to be called when eligibility has been determined.
 @discussion The completion handler will provide the eligibility status in the `eligible` parameter. If the call fails, the error is included.
*/
+ (void)isEligibleForContext:(BEEligibilityContext)context completionHandler:(void (^)(BOOL eligible, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(isEligible(for:));
@end

NS_ASSUME_NONNULL_END
