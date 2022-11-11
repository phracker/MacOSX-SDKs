// Copyright © 2021 Apple Inc. All rights reserved.

#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_EXTERN API_AVAILABLE(ios(15.0))
NS_SWIFT_NAME(SFSafariViewController.PrewarmingToken)
@interface SFSafariViewControllerPrewarmingToken : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! @abstract Ends all prewarmed connections associated with the token, except for connections
    that are also kept alive by other tokens.
 */
- (void)invalidate;

@end

NS_ASSUME_NONNULL_END
