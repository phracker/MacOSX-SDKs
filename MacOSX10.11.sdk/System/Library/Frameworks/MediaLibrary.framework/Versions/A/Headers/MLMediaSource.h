//
//  MLMediaSource.h
//  iLifeMediaBrowser
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaLibrary/MLMediaTypes.h>

@class MLMediaLibrary;
@class MLMediaGroup;
@class MLMediaObject;

NS_ASSUME_NONNULL_BEGIN
@interface MLMediaSource : NSObject

@property (readonly, assign, nullable) MLMediaLibrary *mediaLibrary;

@property (readonly, copy) NSString *mediaSourceIdentifier;

@property (readonly, copy) NSDictionary<NSString *, id> *attributes;

// This accessor property is non-blocking.
// If there is no data yet, it will return nil and automatically trigger an internal async request.
// A KVO notification will be sent via the main thread when data arrives.
@property (readonly, retain, nullable) MLMediaGroup *rootMediaGroup;

- (nullable MLMediaGroup *) mediaGroupForIdentifier: (NSString *) mediaGroupIdentifier;
- (NSDictionary<NSString *, MLMediaGroup *> *) mediaGroupsForIdentifiers: (NSArray<NSString *> *) mediaGroupIdentifiers; // returns identifier (key) to group (value)

- (nullable MLMediaObject *) mediaObjectForIdentifier: (NSString *) mediaObjectIdentifier;
- (NSDictionary<NSString *, MLMediaObject *> *) mediaObjectsForIdentifiers: (NSArray<NSString *> *) mediaObjectIdentifiers; // returns identifier (key) to object (value)

@end
NS_ASSUME_NONNULL_END
