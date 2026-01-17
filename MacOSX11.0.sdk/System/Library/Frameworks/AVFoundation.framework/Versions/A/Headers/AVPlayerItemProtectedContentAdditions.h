#if !__has_include(<AVFCore/AVPlayerItemProtectedContentAdditions.h>)
/*
	File:  AVPlayerItemProtectedContentAdditions.h
 
	Framework:  AVFoundation
 
	Copyright 2010-2018 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVPlayerItem.h>

NS_ASSUME_NONNULL_BEGIN

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @enum		Authorization Request Status
 @abstract	Possible status values resulting from a call to requestContentAuthorizationAsynchronouslyWithTimeoutInterval:CompletionHandler:.
 @constant	AVContentAuthorizationUnknown		No call to request content authorization has completed yet.
 @constant	AVContentAuthorizationCompleted		The last completed call to request content authorization completed.
 @constant	AVContentAuthorizationCancelled		The last call to request content authorization was cancelled by the user.
 @constant	AVContentAuthorizationTimedOut		The last call to request content authorization was cancelled because the timeout interval was reached.
 @constant	AVContentAUthorizationBusy			The last call to request content authorization could not be completed because another asset is currently attempting authorization.
 @constant	AVContentAuthorizationNotAvailable	The last call to request content authorization could not be completed because there was no known mechanism by which to attempt authorization.
 @constant	AVContentAuthorizationNotPossible	The last call to request content authorization could not be completed in a non-recoverable way (i.e. a newer version of iTunes is required).
 @discussion
 Even if authorization is completed by the user, there is no guarantee that the content will then be authorized.  The caller should re-check
 whether the content is authorized before proceeding.
 */
typedef NS_ENUM(NSInteger, AVContentAuthorizationStatus){
	AVContentAuthorizationUnknown = 0,
	AVContentAuthorizationCompleted = 1,
	AVContentAuthorizationCancelled = 2,
	AVContentAuthorizationTimedOut = 3,
	AVContentAuthorizationBusy = 4,
	AVContentAuthorizationNotAvailable = 5,
	AVContentAuthorizationNotPossible = 6,
};

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @category		AVPlayerItem (AVPlayerItemProtectedContent)
 @abstract		Methods supporting protected content.
 */
@interface AVPlayerItem (AVPlayerItemProtectedContent)

/*!
 @property		authorizationRequiredForPlayback
 @abstract		Indicates whether or not authorization is required to play the content.
 @discussion
 This property reports whether or not authorization is required for the receiver's content to be played.  If it does not require authorization, then none of the other
 methods or properties in the AVPlayerItemProtectedContent category apply (though they will return sensible values where possible). This value is NOT key-value observable.
 */
@property (nonatomic, readonly, getter=isAuthorizationRequiredForPlayback) BOOL authorizationRequiredForPlayback API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property		applicationAuthorizedForPlayback
 @abstract		Indicates whether the calling application can be used to play the content.
 @discussion		
 This property reports whether or not the calling application is authorized to play the content associated with the receiver.  Note that application authorization
 is independent of content authorization (see contentAuthorizedForPlayback) and that both must be granted in order for an application to be allowed to play protected content.
 Also, unlike content authorization, application authorization is not dependent on user credentials (i.e. if applicationAuthorizedForPlayback is NO, there are no means to obtain authorization).
 This value is NOT key-value observable.
 */
@property (nonatomic, readonly, getter=isApplicationAuthorizedForPlayback) BOOL applicationAuthorizedForPlayback API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property		contentAuthorizedForPlayback
 @abstract		Indicates whether the content has been authorized by the user (e.g. by authorizing the content's associated account in iTunes).
 @discussion
 This property reports whether or not the user has provided the necessary credentials to the system in order for the content to be decrypted for playback.
 Note that content authorization is independent of application authorization (see applicationAuthorizedForPlayback) and that both must be 
 granted in order for an application to be allowed to play protected content. This value is NOT key-value observable.
 */
@property (nonatomic, readonly, getter=isContentAuthorizedForPlayback) BOOL contentAuthorizedForPlayback API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0)) API_UNAVAILABLE(watchos);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @method		requestContentAuthorizationAsynchronouslyWithTimeoutInterval:completionHandler:
 @abstract		Causes appropriate action to be taken to allow the user to authorize the content for playback.
 @discussion
 Calling this method will present the user with the opportunity to authorize the content (e.g. by launching iTunes and prompting the user to enter their Apple ID and password).
 When the user has taken action (or the timeout has elapsted), the completion handler will be invoked.  The status of the authorization attempt can be determined by checking
 the value of the contentAuthorizationRequestStatus property.  Note that even if the status indicates a completed authorization, the content may still not be authorized
 (e.g. if the user authorizes an Apple ID other than that associated with the content).  The contentAuthorizedForPlayback property should be re-checked to verify whether
 the content has actually been authorized before continuing.  It is not necessary to call this method if the value of contentAuthorizedForPlayback is already true.
 
 @param			timoutInterval	The maximum amount of time to wait for the user to authorize the content in seconds before calling the handler block with a timeout result.
 @param			handler			Block to be called upon completion.
 */
- (void)requestContentAuthorizationAsynchronouslyWithTimeoutInterval:(NSTimeInterval)timeoutInterval completionHandler:(void (^)(void))handler API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
 @method		cancelContentAuthorizationRequest
 @abstract		Causes the currently outstanding content authorization request to be cancelled.
 @discussion
 Calling this method while a content authorization request is pending will cause that request to be cancelled and its completion handler to be invoked
 with a status of AVContentAuthorizationCancelled.  This call does not block.
 */
- (void)cancelContentAuthorizationRequest API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
 @property		contentAuthorizationRequestStatus
 @abstract		Indicates the status of the most recent call to requestContentAuthorizationAsynchronouslyWithTimeoutInterval:CompletionHandler:
 @discussion
 This property reports the authorization status as determined by the most recent call to requestContentAuthorizationAsynchronouslyWithTimeoutInterval:CompletionHandler:.
 The value will be AVContentAuthorizationUnknown before the first call and between the time a request call is made and just prior to the completion handler being executed
 (i.e. it is safe to query this property from the completion handler). This value is NOT key-value observable.
 */
@property (nonatomic, readonly) AVContentAuthorizationStatus contentAuthorizationRequestStatus API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerItemProtectedContentAdditions.h>
#endif
