//
//  MLMediaSource.h
//  iLifeMediaBrowser
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaLibrary/MLMediaTypes.h>

@class MLMediaLibrary;
@class MLMediaGroup;
@class MLMediaObject;

@interface MLMediaSource : NSObject

@property (readonly, assign) MLMediaLibrary *mediaLibrary;

@property (readonly, copy) NSString *mediaSourceIdentifier;

@property (readonly, copy) NSDictionary *attributes;

// This accessor property is non-blocking.
// If there is no data yet, it will return nil and automatically trigger an internal async request.
// A KVO notification will be sent via the main thread when data arrives.
@property (readonly, retain) MLMediaGroup *rootMediaGroup;

- (MLMediaGroup *) mediaGroupForIdentifier: (NSString *) mediaGroupIdentifier;
- (NSDictionary *) mediaGroupsForIdentifiers: (NSArray *) mediaGroupIdentifiers; // returns identifier (key) to group (value)

- (MLMediaObject *) mediaObjectForIdentifier: (NSString *) mediaObjectIdentifier;
- (NSDictionary *) mediaObjectsForIdentifiers: (NSArray *) mediaObjectIdentifiers; // returns identifier (key) to object (value)

@end
