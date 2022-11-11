//
//  GKLeaderboardEntry.h
//  Game Center
//
//  Copyright 2018-2021 Apple Inc. All rights reserved.
//


NS_ASSUME_NONNULL_BEGIN

@class GKPlayer;

API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0))
NS_SWIFT_NAME(GKLeaderboard.Entry)
@interface GKLeaderboardEntry : NSObject

@property (strong, readonly, nonatomic) GKPlayer *player;
@property (readonly, nonatomic) NSInteger rank;
@property (readonly, nonatomic) NSInteger score;
@property (strong, readonly, nonatomic) NSString *formattedScore;
@property (assign, readonly, nonatomic) NSUInteger context;
@property (strong, readonly, nonatomic) NSDate *date;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
