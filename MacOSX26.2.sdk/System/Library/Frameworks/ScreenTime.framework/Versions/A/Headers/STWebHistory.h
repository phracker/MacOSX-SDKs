//
//  STWebHistory.h
//  ScreenTime
//
//  Copyright © 2019–2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// An identifier representing a web history profile.
///
/// Profiles allow you to keep your web history separate for topics like work, personal, or school.
typedef NSString * STWebHistoryProfileIdentifier NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(STWebHistory.ProfileIdentifier) API_AVAILABLE(macos(15.4), ios(18.4));

/// The object you use to delete web-usage data.
///
/// This class provides an easy way for you to delete web history, including:
///
/// - All history
/// - History associated to a specific URL
/// - History during a specific time interval
API_AVAILABLE(macos(11.0), ios(14.0))
@interface STWebHistory : NSObject

/// Creates a web history instance to delete web-usage data associated to the
/// bundle identifier and profile identifier you specify.
///
/// The default value for `bundleIdentifier` is `Bundle.main.bundleIdentifier`.
/// This is the recommended identifier to use, except for example, if a helper
/// process is presenting web UI and you want to group that web-usage under the
/// main app’s bundle identifier.
///
/// The default value for `profileIdentifier` is `nil`. This identifier can be used to delete
/// browsing history for a specific profile. Using `nil` will only delete web history reported
/// without a profile identifier.
///
/// - Parameters:
///   - bundleIdentifier: The bundle identifier.
///   - profileIdentifier: The identifier of the current browsing profile.
///   - error: Any error that occurred while changing the bundle identifier.
- (nullable instancetype)initWithBundleIdentifier:(NSString *)bundleIdentifier profileIdentifier:(nullable STWebHistoryProfileIdentifier)profileIdentifier error:(NSError **)error API_AVAILABLE(macos(15.4), ios(18.4));

/// Creates a web history instance to delete web-usage data associated to the
/// profile identifier you specify.
///
/// The default value for `profileIdentifier` is `nil`. This identifier can be used to delete
/// browsing history for a specific profile. Using `nil` will only delete web history reported
/// without a profile identifier.
///
/// - Parameters:
///   - profileIdentifier: The identifier of the current browsing profile.
- (instancetype)initWithProfileIdentifier:(nullable STWebHistoryProfileIdentifier)profileIdentifier API_AVAILABLE(macos(15.4), ios(18.4));

/// Creates a web history instance to delete web-usage data associated to the
/// bundle identifier you specify.
///
/// The default value for `bundleIdentifier` is `Bundle.main.bundleIdentifier`.
/// This is the recommended identifier to use, except for example, if a helper
/// process is presenting web UI and you want to group that web-usage under the
/// main app’s bundle identifier.
///
/// - Parameters:
///   - bundleIdentifier: The bundle identifier.
///   - error: Any error that occurred while changing the bundle identifier.
- (nullable instancetype)initWithBundleIdentifier:(NSString *)bundleIdentifier error:(NSError **)error;
// -init uses NSBundle.mainBundle.bundleIdentifier as the bundle identifier.

/// Fetches web history that occurred during the date interval you specify.
///
/// - Parameters:
///   - interval: The date interval of web history you want to fetch.
- (void)fetchHistoryDuringInterval:(NSDateInterval *)interval completionHandler:(void (^)(NSSet<NSURL *> * _Nullable urls, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(15.4), ios(18.4)) NS_SWIFT_NAME(fetchHistory(during:completionHandler:));

/// Fetches all web history associated with the bundle identifier and profile identifier
/// you specified during initialization.
- (void)fetchAllHistoryWithCompletionHandler:(void (^)(NSSet<NSURL *> * _Nullable urls, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(15.4), ios(18.4));

/// Deletes all the web history for the URL you specify.
///
/// The framework references the entire URL to determine which web-usage data to
/// delete.
///
/// - Parameters:
///   - url: The URL associated with the web history to delete.
- (void)deleteHistoryForURL:(NSURL *)url NS_SWIFT_NAME(deleteHistory(for:));

/// Deletes web history that occurred during the date interval you specify.
///
/// - Parameters:
///   - interval: The date interval of web history you want to delete.
- (void)deleteHistoryDuringInterval:(NSDateInterval *)interval NS_SWIFT_NAME(deleteHistory(during:));

/// Deletes all web history associated with the bundle identifier you specified
/// during initialization.
- (void)deleteAllHistory;

@end

NS_ASSUME_NONNULL_END
