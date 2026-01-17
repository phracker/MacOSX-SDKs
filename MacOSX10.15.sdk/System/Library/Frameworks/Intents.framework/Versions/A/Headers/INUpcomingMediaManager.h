//
//  INUpcomingMediaManager.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Intents/INPlayMediaIntent.h>
#import <Intents/INMediaItemType.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INUpcomingMediaPredictionMode) {
    INUpcomingMediaPredictionModeDefault = 0,
    INUpcomingMediaPredictionModeOnlyPredictSuggestedIntents = 1,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos, macosx);

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos, macosx)
@interface INUpcomingMediaManager : NSObject

@property (class, readonly, NS_NONATOMIC_IOSONLY) INUpcomingMediaManager *sharedManager;

- (void)setSuggestedMediaIntents:(NSOrderedSet<INPlayMediaIntent *> *)intents;

- (void)setPredictionMode:(INUpcomingMediaPredictionMode)mode forType:(INMediaItemType)type;

@end

NS_ASSUME_NONNULL_END
