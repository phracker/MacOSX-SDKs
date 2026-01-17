//
//  MLMediaGroup.h
//  iLifeMediaBrowser
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaLibrary/MLMediaTypes.h>

@class MLMediaLibrary;
@class MLMediaObject;
@class NSImage;

API_DEPRECATED_BEGIN("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.9, 10.15))

NS_ASSUME_NONNULL_BEGIN
@interface MLMediaGroup : NSObject

@property (readonly, assign, nullable) MLMediaLibrary *mediaLibrary;
@property (readonly, assign, nullable) MLMediaGroup *parent;
@property (readonly, copy) NSString *mediaSourceIdentifier;

@property (readonly, copy, nullable) NSString *name;
@property (readonly, copy) NSString *identifier;
@property (readonly, copy) NSString *typeIdentifier;

@property (readonly, copy) NSDictionary<NSString *, id> *attributes;
@property (readonly, copy, nullable) NSArray<MLMediaGroup *> *childGroups;

@property (readonly, copy, nullable) NSURL *URL;
@property (readonly, copy, nullable) NSDate *modificationDate;

@property (readonly, copy, nullable) NSImage *iconImage;

// This accessor property is non-blocking.
// If there is no data yet, it will return nil and automatically trigger an internal async request.
// A KVO notification will be sent via the main thread when data arrives.
@property (readonly, copy, nullable) NSArray<MLMediaObject *> *mediaObjects;

@end
NS_ASSUME_NONNULL_END

API_DEPRECATED_END
