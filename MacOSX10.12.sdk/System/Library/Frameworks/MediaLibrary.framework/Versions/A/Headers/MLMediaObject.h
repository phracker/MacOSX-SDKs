//
//  MLMediaObject.h
//  iLifeMediaBrowser
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaLibrary/MLMediaTypes.h>

@class MLMediaLibrary;
@class NSImage;

NS_ASSUME_NONNULL_BEGIN
@interface MLMediaObject : NSObject

@property (readonly, assign, nullable) MLMediaLibrary *mediaLibrary;

@property (readonly, copy) NSString *identifier;
@property (readonly, copy) NSString *mediaSourceIdentifier;

@property (readonly, copy) NSDictionary<NSString *, id> *attributes;

@property (readonly, assign) MLMediaType mediaType;
@property (readonly, copy, nullable) NSString *contentType;
@property (readonly, copy, nullable) NSString *name;
@property (readonly, copy, nullable) NSURL *URL;
@property (readonly, copy, nullable) NSURL *originalURL; // if URL is not the original (master)
@property (readonly, assign) NSUInteger fileSize; // in bytes
@property (readonly, copy, nullable) NSDate *modificationDate;
@property (readonly, copy, nullable) NSURL *thumbnailURL;

@property (readonly, copy, nullable) NSImage *artworkImage; // returns nil if not applicable.

@end
NS_ASSUME_NONNULL_END
