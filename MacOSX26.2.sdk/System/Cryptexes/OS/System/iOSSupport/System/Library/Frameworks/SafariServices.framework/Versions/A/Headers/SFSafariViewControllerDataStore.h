// Copyright © 2022 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos)
API_UNAVAILABLE(visionos)
NS_SWIFT_NAME(SFSafariViewController.DataStore)
@interface SFSafariViewControllerDataStore : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@property (class, nonatomic, readonly, strong) SFSafariViewControllerDataStore *defaultDataStore;

/*! Clear associated website data accrued from browsing activity within your app. This includes all local storage,
    cached resources, and cookies.
 */
- (void)clearWebsiteDataWithCompletionHandler:(nullable void (^)(void))completion;

@end

NS_ASSUME_NONNULL_END
