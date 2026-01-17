//
//  MKMapSnapshotter.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKMapSnapshotOptions;
@class MKMapSnapshot;

NS_ASSUME_NONNULL_BEGIN

typedef void (^MKMapSnapshotCompletionHandler)(MKMapSnapshot * __nullable snapshot, NSError * __nullable error);

API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2), watchos(1.0))
@interface MKMapSnapshotter : NSObject

- (instancetype)initWithOptions:(MKMapSnapshotOptions *)options NS_DESIGNATED_INITIALIZER;

- (void)startWithCompletionHandler:(NS_SWIFT_UI_ACTOR MKMapSnapshotCompletionHandler)completionHandler; // defaults to the main queue
- (void)startWithQueue:(dispatch_queue_t)queue completionHandler:(MKMapSnapshotCompletionHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@end

NS_ASSUME_NONNULL_END
