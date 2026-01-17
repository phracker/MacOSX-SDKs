//
//  ABImageLoading.h
//  AddressBook
//
//  Copyright (c) 2002-2003 Apple Computer. All rights reserved.
//

#import <AddressBook/AddressBook.h>

@protocol ABImageClient <NSObject>
- (void)consumeImageData:(NSData *)data forTag:(int)tag;
    // data will be in an NSImage/QuickTime compatible format or nil if no image could be found.
    // This is always called on the main thread.
@end

@interface ABPerson (ABPersonImageAdditions)

- (BOOL)setImageData:(NSData *)data;
    // Set the image of a person to data. data should be in an NSImage/QuickTime compatible format.
    // Pass nil to clear the image.

- (NSData *)imageData;
    // Synchronously returns data containing an image for this person. Only does local
    // file system searches. Data will be in an NSImage/QuickTime compatible format.

- (int)beginLoadingImageDataForClient:(id<ABImageClient>)client;
    // Starts an asynchronous fetch for image data in all locations using all. Returns a non-zero tag for tracking.
    // The consumer will not be called back until after this method has returned.
    // Cancel with -[ABPerson cancelLoadingImageDataForTag:].

+ (void)cancelLoadingImageDataForTag:(int)tag;
    // Cancels an asynchronous fetch for a specific tag

@end
