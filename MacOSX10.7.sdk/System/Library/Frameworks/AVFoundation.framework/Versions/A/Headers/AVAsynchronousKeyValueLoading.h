/*
    File:  AVAsynchronousKeyValueLoading.h
 
    Framework:  AVFoundation
 
	Copyright 2010 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

enum {
	AVKeyValueStatusUnknown,
	AVKeyValueStatusLoading,
	AVKeyValueStatusLoaded,
	AVKeyValueStatusFailed,
	AVKeyValueStatusCancelled
};
typedef NSInteger AVKeyValueStatus;

@protocol AVAsynchronousKeyValueLoading
@required

/*!
    @method			statusOfValueForKey:
    @abstract		Reports whether the value for a key is immediately available without blocking.
    @param			key
      An instance of NSString containing the specified key.
    @param			outError
      If the status of the value for the key is AVKeyValueStatusFailed, *outError is set to a non-nil NSError that describes the failure that occurred.
    @result			The value's current loading status.
    @discussion
      For any key of interest, clients can use -statusOfValueForKey: to determine the availability of its value.
      However, this method alone does not prompt the target to load the value of a key that's not yet available.
      To request values for keys that may not already be loaded without blocking, use
      -loadValuesAsynchronouslyForKeys:completionHandler: and await invocation of the completion handler
      to be informed of availability.
 
      Note that even for use cases that may typically support ready access to some keys, such as targets initialized
      with URLs for resources on local volumes, extensive I/O or parsing may require targets to block before returning their values.
      Although blocking may be acceptable in cases in which the client is preparing objects for use on background threads
      or in operation queues, in all cases in which blocking should be avoided,
      -loadValuesAsynchronouslyForKeys:completionHandler: is the recommended remedy.
*/
- (AVKeyValueStatus)statusOfValueForKey:(NSString *)key error:(NSError **)outError;

/*!
    @method			loadValuesAsynchronouslyForKeys:completionHandler:
    @abstract		Directs the target to load the values of any of the specified keys that are not already loaded.
    @param			keys
      An instance of NSArray, containing NSStrings for the specified keys.
    @param			completionHandler
      The block to be invoked when loading succeeds, fails, or is cancelled.
*/
- (void)loadValuesAsynchronouslyForKeys:(NSArray *)keys completionHandler:(void (^)(void))handler;

@end
