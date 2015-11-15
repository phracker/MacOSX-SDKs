//
//  ABImageLoading.h
//  AddressBook
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#ifndef __ABIMAGELOADING__
#define __ABIMAGELOADING__

#import <AddressBook/AddressBook.h>

@protocol ABImageClient <NSObject>
- (void)consumeImageData:(NSData *)data forTag:(NSInteger)tag;
    // data will be in an NSImage/QuickTime compatible format or nil if no image could be found.
    // This is always called on the main thread.
	// Use the tag returned by the -beginLoadingImageDataForClient: method
@end

@interface ABPerson (ABPersonImageAdditions)

- (BOOL)setImageData:(NSData *)data;
    // Set the image of a person to data. data should be in an NSImage/QuickTime compatible format.
    // Pass nil to clear the image.

- (NSData *)imageData;
    // Synchronously returns data containing an image for this person. Only does local
    // file system searches. Data will be in an NSImage/QuickTime compatible format.

- (NSInteger)beginLoadingImageDataForClient:(id<ABImageClient>)client;
    // Starts an asynchronous fetch for image data in all locations using all. Returns a non-zero tag for tracking.
    // The consumer will not be called back until after this method has returned.
    // Cancel with +[ABPerson cancelLoadingImageDataForTag:].

+ (void)cancelLoadingImageDataForTag:(NSInteger)tag;
    // Cancels an asynchronous fetch for a specific tag
    // Use the tag returned by the -beginLoadingImageDataForClient: method

@end

#endif // __ABIMAGELOADING__
