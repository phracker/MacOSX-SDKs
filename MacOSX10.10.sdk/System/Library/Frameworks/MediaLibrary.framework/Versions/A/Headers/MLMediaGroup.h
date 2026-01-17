//
//  MLMediaGroup.h
//  iLifeMediaBrowser
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaLibrary/MLMediaTypes.h>

@class MLMediaLibrary;
@class NSImage;

@interface MLMediaGroup : NSObject

@property (readonly, assign) MLMediaLibrary *mediaLibrary;
@property (readonly, assign) MLMediaGroup *parent;
@property (readonly, copy) NSString *mediaSourceIdentifier;

@property (readonly, copy) NSString *name;
@property (readonly, copy) NSString *identifier;
@property (readonly, copy) NSString *typeIdentifier;

@property (readonly, copy) NSDictionary *attributes;
@property (readonly, copy) NSArray *childGroups;

@property (readonly, copy) NSURL *URL;
@property (readonly, copy) NSDate *modificationDate;

@property (readonly, copy) NSImage *iconImage;

// This accessor property is non-blocking.
// If there is no data yet, it will return nil and automatically trigger an internal async request.
// A KVO notification will be sent via the main thread when data arrives.
@property (readonly, copy) NSArray *mediaObjects;

@end
