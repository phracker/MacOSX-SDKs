//
//  MKMapSnapshotter.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKMapSnapshotOptions;
@class MKMapSnapshot;

typedef void (^MKMapSnapshotCompletionHandler)(MKMapSnapshot *snapshot, NSError *error);

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKMapSnapshotter : NSObject

- (instancetype)initWithOptions:(MKMapSnapshotOptions *)options NS_DESIGNATED_INITIALIZER;

- (void)startWithCompletionHandler:(MKMapSnapshotCompletionHandler)completionHandler; // defaults to the main queue
- (void)startWithQueue:(dispatch_queue_t)queue completionHandler:(MKMapSnapshotCompletionHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@end
