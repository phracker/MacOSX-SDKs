//
//  INMediaSearch_Deprecated.h
//  Intents
//
//  Copyright (c) 2019-2020 Apple Inc. All rights reserved.
//

#import <Intents/INMediaSearch.h>

NS_ASSUME_NONNULL_BEGIN

@interface INMediaSearch (Deprecated)

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *activityNames API_DEPRECATED("Use `moodNames` property instead.", ios(13.0, 13.0), watchos(6.0, 6.0));

@end

NS_ASSUME_NONNULL_END
