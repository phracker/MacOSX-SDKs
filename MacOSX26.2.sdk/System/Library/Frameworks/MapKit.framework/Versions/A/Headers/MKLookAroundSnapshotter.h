//
//  MKLookAroundSnapshotter.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MKLookAroundScene;
@class MKLookAroundSnapshot;
@class MKLookAroundSnapshotOptions;

API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos)
@interface MKLookAroundSnapshotter : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithScene:(MKLookAroundScene *)scene options:(MKLookAroundSnapshotOptions *)options NS_DESIGNATED_INITIALIZER;

// defaults to the main queue
- (void)getSnapshotWithCompletionHandler:(NS_SWIFT_UI_ACTOR void (^)(MKLookAroundSnapshot * _Nullable snapshot, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:snapshot());
- (void)cancel;

@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@end

NS_ASSUME_NONNULL_END
