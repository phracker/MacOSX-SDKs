/*
    File:  AVAsynchronousKeyValueLoading.h
 
    Framework:  AVFoundation
 
	Copyright 2010-2016 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, AVKeyValueStatus) {
	AVKeyValueStatusUnknown,
	AVKeyValueStatusLoading,
	AVKeyValueStatusLoaded,
	AVKeyValueStatusFailed,
	AVKeyValueStatusCancelled
};

/*!
	@protocol	AVAsynchronousKeyValueLoading
 
	@abstract	The AVAsynchronousKeyValueLoading protocol defines methods that let clients use an AVAsset or AVAssetTrack object without blocking a thread. Using methods in the protocol, one can find out the current status of a key (for example, whether the corresponding value has been loaded); and ask the object to load values asynchronously, informing the client when the operation has completed.
 
	@discussion
		Because of the nature of timed audiovisual media, successful initialization of an asset does not necessarily mean that all its data is immediately available. Instead, an asset will wait to load data until an operation is performed on it (for example, directly invoking any relevant AVAsset methods, playback via an AVPlayerItem object, export using AVAssetExportSession, reading using an instance of AVAssetReader, and so on). This means that although you can request the value of any key at any time, and its value will be returned synchronously, the calling thread may be blocked until the request can be satisfied. To avoid blocking, you can:

			1. First, determine whether the value for a given key is available using statusOfValueForKey:error:.
			2. If a value has not been loaded yet, you can ask for to load one or more values and be notified when they become available using loadValuesAsynchronouslyForKeys:completionHandler:.
		
		Even for use cases that may typically support ready access to some keys (such as for assets initialized with URLs for files in the local filesystem), slow I/O may require AVAsset to block before returning their values. Although blocking may be acceptable for OS X API clients in cases where assets are being prepared on background threads or in operation queues, in all cases in which blocking should be avoided you should use loadValuesAsynchronouslyForKeys:completionHandler:. For iOS clients, blocking to obtain the value of a key synchronously is never recommended under any circumstances.
*/
@protocol AVAsynchronousKeyValueLoading
@required

/*!
  @method		statusOfValueForKey:
  @abstract		Reports whether the value for a key is immediately available without blocking.
  @param		key
    An instance of NSString containing the specified key.
  @param		outError
    If the status of the value for the key is AVKeyValueStatusFailed, *outError is set to a non-nil NSError that describes the failure that occurred.
  @result		The value's current loading status.
  @discussion
    Clients can use -statusOfValueForKey: to determine the availability of the value of any key of interest. However, this method alone does not prompt the receiver to load the value of a key that's not yet available. To request values for keys that may not already be loaded, without blocking, use -loadValuesAsynchronouslyForKeys:completionHandler:, await invocation of the completion handler, and test the availability of each key via -statusOfValueForKey: before invoking its getter.
 
    Even if access to values of some keys may be readily available, as can occur with receivers initialized with URLs for resources on local volumes, extensive I/O or parsing may be needed for these same receivers to provide values for other keys. A duration for a local MP3 file, for example, may be expensive to obtain, even if the values for other AVAsset properties may be trivial to obtain.

    Blocking that may occur when calling the getter for any key should therefore be avoided in the general case by loading values for all keys of interest via -loadValuesAsynchronouslyForKeys:completionHandler: and testing the availability of the requested values before fetching them by calling getters.
      
    The sole exception to this general rule is in usage on Mac OS X on the desktop, where it may be acceptable to block in cases in which the client is preparing objects for use on background threads or in operation queues. On iOS, values should always be loaded asynchronously prior to calling getters for the values, in any usage scenario.
*/
- (AVKeyValueStatus)statusOfValueForKey:(NSString *)key error:(NSError * _Nullable * _Nullable)outError;

/*!
  @method		loadValuesAsynchronouslyForKeys:completionHandler:
  @abstract		Directs the target to load the values of any of the specified keys that are not already loaded.
  @param		keys
    An instance of NSArray, containing NSStrings for the specified keys.
  @param		completionHandler
    The block to be invoked when loading succeeds, fails, or is cancelled.
*/
- (void)loadValuesAsynchronouslyForKeys:(NSArray<NSString *> *)keys completionHandler:(nullable void (^)(void))handler;

@end

NS_ASSUME_NONNULL_END
