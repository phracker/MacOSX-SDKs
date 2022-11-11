//
//  STWebHistory.h
//  ScreenTime
//
//  Copyright © 2019–2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(11.0), ios(14.0))
@interface STWebHistory : NSObject

/// Creates a web history that will delete web usage for the given bundle identifier.
///
/// Using a bundle identifier other than @c NSBundle.mainBundle.bundleIdentifier is only supported for
/// web browsers that have been properly registered with Screen Time.
///
/// @param bundleIdentifier Used to facilitate deletion of a parent web browser's history from one of its
/// helper processes or extensions.
/// @param error Any error that occurred during initialization.
- (nullable instancetype)initWithBundleIdentifier:(NSString *)bundleIdentifier error:(NSError **)error;
// -init uses NSBundle.mainBundle.bundleIdentifier as the bundle identifier.

/// @param url The URL for which to delete Screen Time usage history. The full URL is used, i.e. the scheme, path, et al. are significant.
- (void)deleteHistoryForURL:(NSURL *)url NS_SWIFT_NAME(deleteHistory(for:));
- (void)deleteHistoryDuringInterval:(NSDateInterval *)interval NS_SWIFT_NAME(deleteHistory(during:));
- (void)deleteAllHistory;

@end

NS_ASSUME_NONNULL_END
