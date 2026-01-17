//
//  GKLeaderboardScore.h
//  GameCenterFoundation.framework
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//
NS_ASSUME_NONNULL_BEGIN

@class GKPlayer;

API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0))
@interface GKLeaderboardScore : NSObject

@property (strong, nonatomic) GKPlayer *player;
@property (assign, nonatomic) NSInteger value;
@property (assign, nonatomic) NSUInteger context;
@property (strong, nonatomic) NSString *leaderboardID;

@end

NS_ASSUME_NONNULL_END
