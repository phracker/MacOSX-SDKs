//
//  MLMediaObject.h
//  iLifeMediaBrowser
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaLibrary/MLMediaTypes.h>

@class MLMediaLibrary;
@class NSImage;

@interface MLMediaObject : NSObject

@property (readonly, assign) MLMediaLibrary *mediaLibrary;

@property (readonly, copy) NSString *identifier;
@property (readonly, copy) NSString *mediaSourceIdentifier;

@property (readonly, copy) NSDictionary *attributes;

@property (readonly, assign) MLMediaType mediaType;
@property (readonly, copy) NSString *contentType;
@property (readonly, copy) NSString *name;
@property (readonly, copy) NSURL *URL;
@property (readonly, copy) NSURL *originalURL; // if URL is not the original (master)
@property (readonly, assign) NSUInteger fileSize; // in bytes
@property (readonly, copy) NSDate *modificationDate;
@property (readonly, copy) NSURL *thumbnailURL;

@property (readonly, copy) NSImage *artworkImage; // returns nil if not applicable.

@end

