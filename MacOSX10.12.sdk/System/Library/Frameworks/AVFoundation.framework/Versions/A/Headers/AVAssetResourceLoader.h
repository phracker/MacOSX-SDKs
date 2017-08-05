/*
	File:  AVAssetResourceLoader.h

	Framework:  AVFoundation
 
	Copyright 2010-2016 Apple Inc. All rights reserved.

*/

/*!
  @class		AVAssetResourceLoader

  @abstract		An AVAssetResourceLoader mediates requests to load resources required by an AVURLAsset by asking a delegate object that you provide for assistance. When a resource is required that cannot be loaded by the AVURLAsset itself, the resource loader makes a request of its delegate to load it and proceeds according to the delegate's response.
	
  @discussion
	You should not create resource loader objects. Instead, you should retrieve a resource loader from the resourceLoader property of an AVURLAsset and use it to assign your delegate object for resource loading.
 
	The delegate associated with this object must adopt the AVAssetResourceLoaderDelegate protocol.
*/
#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVAssetResourceLoaderDelegate;

@class AVAssetResourceLoadingRequest;
@class AVAssetResourceRenewalRequest;
@class AVAssetResourceLoaderInternal;

NS_CLASS_AVAILABLE(10_9, 6_0)
@interface AVAssetResourceLoader : NSObject {
@private
	AVAssetResourceLoaderInternal *_resourceLoader;
}
AV_INIT_UNAVAILABLE

/*!
 @method 		setDelegate:queue:
 @abstract		Sets the receiver's delegate that will mediate resource loading and the dispatch queue on which delegate methods will be invoked.
 @param			delegate
				An object conforming to the AVAssetResourceLoaderDelegate protocol.
 @param			delegateQueue
				A dispatch queue on which all delegate methods will be invoked.
 @discussion
  If you employ an AVAssetResourceLoader delegate that loads media data for playback, you should set the value of your AVPlayer’s automaticallyWaitsToMinimizeStalling property to NO. Allowing the value of automaticallyWaitsToMinimizeStalling to remain YES — its default value — when an AVAssetResourceLoader delegate is used for the loading of media data can result in poor start-up times for playback and poor recovery from stalls, because the behaviors provided by AVPlayer when automaticallyWaitsToMinimizeStalling has a value of YES depend on predictions of the future availability of media data that that do not function as expected when data is loaded via a client-controlled means, using the AVAssetResourceLoader delegate interface.

  You can allow the value of automaticallyWaitsToMinimizeStalling to remain YES if you use an AVAssetResourceLoader delegate to manage content keys for FairPlay Streaming, to provide dynamically-generated master playlists for HTTP Live Streaming, or to respond to authentication challenges, but not to load media data for playback.
*/
- (void)setDelegate:(nullable id <AVAssetResourceLoaderDelegate>)delegate queue:(nullable dispatch_queue_t)delegateQueue;

/*!
 @property 		delegate
 @abstract		The receiver's delegate.
 @discussion
  The value of this property is an object conforming to the AVAssetResourceLoaderDelegate protocol. The delegate is set using the setDelegate:queue: method. The delegate is held using a zeroing-weak reference, so this property will have a value of nil after a delegate that was previously set has been deallocated.
*/
@property (nonatomic, readonly, weak, nullable) id <AVAssetResourceLoaderDelegate> delegate;

/*!
 @property 		delegateQueue
 @abstract		The dispatch queue on which all delegate methods will be invoked.
 @discussion
  The value of this property is a dispatch_queue_t. The queue is set using the setDelegate:queue: method.
*/
@property (nonatomic, readonly, nullable) dispatch_queue_t delegateQueue;

@end

/*!
	@protocol		AVAssetResourceLoaderDelegate
	@abstract		The AVAssetResourceLoaderDelegate protocol defines methods that allow your code to handle resource loading requests coming from an AVULRAsset.
*/

@class NSURLAuthenticationChallenge;

@protocol AVAssetResourceLoaderDelegate <NSObject>

@optional

/*!
 @method 		resourceLoader:shouldWaitForLoadingOfRequestedResource:
 @abstract		Invoked when assistance is required of the application to load a resource.
 @param 		resourceLoader
				The instance of AVAssetResourceLoader for which the loading request is being made.
 @param 		loadingRequest
				An instance of AVAssetResourceLoadingRequest that provides information about the requested resource. 
 @result 		YES if the delegate can load the resource indicated by the AVAssetResourceLoadingRequest; otherwise NO.
 @discussion
  Delegates receive this message when assistance is required of the application to load a resource. For example, this method is invoked to load decryption keys that have been specified using custom URL schemes.
  If the result is YES, the resource loader expects invocation, either subsequently or immediately, of either -[AVAssetResourceLoadingRequest finishLoading] or -[AVAssetResourceLoadingRequest finishLoadingWithError:]. If you intend to finish loading the resource after your handling of this message returns, you must retain the instance of AVAssetResourceLoadingRequest until after loading is finished.
  If the result is NO, the resource loader treats the loading of the resource as having failed.
  Note that if the delegate's implementation of -resourceLoader:shouldWaitForLoadingOfRequestedResource: returns YES without finishing the loading request immediately, it may be invoked again with another loading request before the prior request is finished; therefore in such cases the delegate should be prepared to manage multiple loading requests.

*/
- (BOOL)resourceLoader:(AVAssetResourceLoader *)resourceLoader shouldWaitForLoadingOfRequestedResource:(AVAssetResourceLoadingRequest *)loadingRequest NS_AVAILABLE(10_9, 6_0);

/*!
 @method 		resourceLoader:shouldWaitForRenewalOfRequestedResource:
 @abstract		Invoked when assistance is required of the application to renew a resource.
 @param 		resourceLoader
 The instance of AVAssetResourceLoader for which the loading request is being made.
 @param 		renewalRequest
 An instance of AVAssetResourceRenewalRequest that provides information about the requested resource.
 @result 		YES if the delegate can renew the resource indicated by the AVAssetResourceLoadingRequest; otherwise NO.
 @discussion
 Delegates receive this message when assistance is required of the application to renew a resource previously loaded by resourceLoader:shouldWaitForLoadingOfRequestedResource:. For example, this method is invoked to renew decryption keys that require renewal, as indicated in a response to a prior invocation of resourceLoader:shouldWaitForLoadingOfRequestedResource:.
 If the result is YES, the resource loader expects invocation, either subsequently or immediately, of either -[AVAssetResourceRenewalRequest finishLoading] or -[AVAssetResourceRenewalRequest finishLoadingWithError:]. If you intend to finish loading the resource after your handling of this message returns, you must retain the instance of AVAssetResourceRenewalRequest until after loading is finished.
 If the result is NO, the resource loader treats the loading of the resource as having failed.
 Note that if the delegate's implementation of -resourceLoader:shouldWaitForRenewalOfRequestedResource: returns YES without finishing the loading request immediately, it may be invoked again with another loading request before the prior request is finished; therefore in such cases the delegate should be prepared to manage multiple loading requests.
*/
- (BOOL)resourceLoader:(AVAssetResourceLoader *)resourceLoader shouldWaitForRenewalOfRequestedResource:(AVAssetResourceRenewalRequest *)renewalRequest NS_AVAILABLE(10_10, 8_0);

/*!
 @method 		resourceLoader:didCancelLoadingRequest:
 @abstract		Informs the delegate that a prior loading request has been cancelled.
 @param 		loadingRequest
				The loading request that has been cancelled. 
 @discussion	Previously issued loading requests can be cancelled when data from the resource is no longer required or when a loading request is superseded by new requests for data from the same resource. For example, if to complete a seek operation it becomes necessary to load a range of bytes that's different from a range previously requested, the prior request may be cancelled while the delegate is still handling it.
*/
- (void)resourceLoader:(AVAssetResourceLoader *)resourceLoader didCancelLoadingRequest:(AVAssetResourceLoadingRequest *)loadingRequest NS_AVAILABLE(10_9, 7_0);

/*!
 @method 		resourceLoader:shouldWaitForResponseToAuthenticationChallenge:
 @abstract		Invoked when assistance is required of the application to respond to an authentication challenge.
 @param 		resourceLoader
				The instance of AVAssetResourceLoader asking for help with an authentication challenge.
 @param 		authenticationChallenge
				An instance of NSURLAuthenticationChallenge. 
 @discussion
  Delegates receive this message when assistance is required of the application to respond to an authentication challenge.
  If the result is YES, the resource loader expects you to send an appropriate response, either subsequently or immediately, to the NSURLAuthenticationChallenge's sender, i.e. [authenticationChallenge sender], via use of one of the messages defined in the NSURLAuthenticationChallengeSender protocol (see NSAuthenticationChallenge.h). If you intend to respond to the authentication challenge after your handling of -resourceLoader:shouldWaitForResponseToAuthenticationChallenge: returns, you must retain the instance of NSURLAuthenticationChallenge until after your response has been made.
*/
- (BOOL)resourceLoader:(AVAssetResourceLoader *)resourceLoader shouldWaitForResponseToAuthenticationChallenge:(NSURLAuthenticationChallenge *)authenticationChallenge NS_AVAILABLE(10_10, 8_0);

/*!
 @method 		resourceLoader:didCancelAuthenticationChallenge:
 @abstract		Informs the delegate that a prior authentication challenge has been cancelled.
 @param 		authenticationChallenge
				The authentication challenge that has been cancelled. 
*/
- (void)resourceLoader:(AVAssetResourceLoader *)resourceLoader didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)authenticationChallenge NS_AVAILABLE(10_10, 8_0);

@end

/*!
	@class		AVAssetResourceLoadingRequest
 
	@abstract	AVAssetResourceLoadingRequest encapsulates information about a resource request issued by a resource loader.
 
	@discussion	
		When an AVURLAsset needs help loading a resource, it asks its AVAssetResourceLoader object to assist. The resource loader encapsulates the request information by creating an instance of this object, which it then hands to its delegate for processing. The delegate uses the information in this object to perform the request and report on the success or failure of the operation.
 
*/

@class AVAssetResourceLoadingRequestInternal;
@class AVAssetResourceLoadingContentInformationRequest;
@class AVAssetResourceLoadingDataRequest;

NS_CLASS_AVAILABLE(10_9, 6_0)
@interface AVAssetResourceLoadingRequest : NSObject {
@private
	AVAssetResourceLoadingRequestInternal *_loadingRequest;
}
AV_INIT_UNAVAILABLE

/*! 
 @property 		request
 @abstract		An NSURLRequest for the requested resource.
*/
@property (nonatomic, readonly) NSURLRequest *request;

/*! 
 @property 		finished
 @abstract		Indicates whether loading of the resource has been finished.
 @discussion	The value of this property becomes YES only in response to an invocation of either -finishLoading or -finishLoadingWithError:.
*/
@property (nonatomic, readonly, getter=isFinished) BOOL finished;

/*! 
 @property 		cancelled
 @abstract		Indicates whether the request has been cancelled.
 @discussion	The value of this property becomes YES when the resource loader cancels the loading of a request, just prior to sending the message -resourceLoader:didCancelLoadingRequest: to its delegate.
*/
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled NS_AVAILABLE(10_9, 7_0);

/*! 
 @property 		contentInformationRequest
 @abstract		An instance of AVAssetResourceLoadingContentInformationRequest that you should populate with information about the resource. The value of this property will be nil if no such information is being requested.
*/
@property (nonatomic, readonly, nullable) AVAssetResourceLoadingContentInformationRequest *contentInformationRequest NS_AVAILABLE(10_9, 7_0);

/*! 
 @property 		dataRequest
 @abstract		An instance of AVAssetResourceLoadingDataRequest that indicates the range of resource data that's being requested. The value of this property will be nil if no data is being requested.
*/
@property (nonatomic, readonly, nullable) AVAssetResourceLoadingDataRequest *dataRequest NS_AVAILABLE(10_9, 7_0);

/*! 
 @property 		response
 @abstract		Set the value of this property to an instance of NSURLResponse indicating a response to the loading request. If no response is needed, leave the value of this property set to nil.
*/
@property (nonatomic, copy, nullable) NSURLResponse *response NS_AVAILABLE(10_9, 7_0);

/*! 
 @property 		redirect
 @abstract		Set the value of this property to an instance of NSURLRequest indicating a redirection of the loading request to another URL. If no redirection is needed, leave the value of this property set to nil.
 @discussion	AVAssetResourceLoader supports redirects to HTTP URLs only. Redirects to other URLs will result in a loading failure.
*/
@property (nonatomic, copy, nullable) NSURLRequest *redirect NS_AVAILABLE(10_9, 7_0);

/*! 
 @method 		finishLoading   
 @abstract		Causes the receiver to treat the processing of the request as complete.
 @discussion	If a dataRequest is present and the resource does not contain the full extent of the data that has been requested according to the values of the requestedOffset and requestedLength properties of the dataRequest, or if requestsAllDataToEndOfResource has a value of YES, you may invoke -finishLoading after you have provided as much of the requested data as the resource contains.
*/
- (void)finishLoading NS_AVAILABLE(10_9, 7_0);

/*! 
 @method 		finishLoadingWithError:   
 @abstract		Causes the receiver to treat the request as having failed.
 @param			error
 				An instance of NSError indicating the reason for failure.
*/
- (void)finishLoadingWithError:(nullable NSError *)error;

@end

/*!
 @class		AVAssetResourceRenewalRequest

 @abstract	AVAssetResourceRenewalRequest encapsulates information about a resource request issued by a resource loader for the purpose of renewing a request previously issued.

 @discussion
 When an AVURLAsset needs to renew a resource (because contentInformationRequest.renewalDate has been set on a previous loading request), it asks its AVAssetResourceLoader object to assist. The resource loader encapsulates the request information by creating an instance of this object, which it then hands to its delegate for processing. The delegate uses the information in this object to perform the request and report on the success or failure of the operation.

 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAssetResourceRenewalRequest : AVAssetResourceLoadingRequest

@end

/*!
	@class		AVAssetResourceLoadingContentInformationRequest
 
	@abstract	An AVAssetResourceLoadingContentInformationRequest represents a query for essential information about a resource referenced by an asset resource loading request.
 
	@discussion
		When a resource loading delegate accepts responsibility for loading a resource by returning YES from its implementation of resourceLoader:shouldWaitForLoadingOfRequestedResource:, it must check whether the contentInformationRequest property of the AVAssetResourceLoadingRequest is not nil. Whenever the value is not nil, the request includes a query for the information that AVAssetResourceLoadingContentInformationRequest encapsulates. In response to such queries, the resource loading delegate should set the values of the content information request's properties appropriately before invoking the AVAssetResourceLoadingRequest method finishLoading.
 
		When finishLoading is invoked, the values of the properties of its contentInformationRequest property will, in part, determine how the requested resource is processed. For example, if the requested resource's URL is the URL of an AVURLAsset and contentType is set by the resource loading delegate to a value that the underlying media system doesn't recognize as a supported media file type, operations on the AVURLAsset, such as playback, are likely to fail.
*/

@class AVAssetResourceLoadingContentInformationRequestInternal;

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVAssetResourceLoadingContentInformationRequest : NSObject {
@private
	AVAssetResourceLoadingContentInformationRequestInternal *_contentInformationRequest;
}
AV_INIT_UNAVAILABLE

/*! 
 @property 		contentType
 @abstract		A UTI that indicates the type of data contained by the requested resource.
 @discussion	Before you finish loading an AVAssetResourceLoadingRequest, if its contentInformationRequest is not nil, you should set the value of this property to a UTI indicating the type of data contained by the requested resource.
*/
@property (nonatomic, copy, nullable) NSString *contentType;

/*! 
 @property 		contentLength
 @abstract		Indicates the length of the requested resource, in bytes.
 @discussion	Before you finish loading an AVAssetResourceLoadingRequest, if its contentInformationRequest is not nil, you should set the value of this property to the number of bytes contained by the requested resource.
*/
@property (nonatomic) long long contentLength;

/*! 
 @property 		byteRangeAccessSupported
 @abstract		Indicates whether random access to arbitrary ranges of bytes of the resource is supported. Such support also allows portions of the resource to be requested more than once.
 @discussion	Before you finish loading an AVAssetResourceLoadingRequest, if its contentInformationRequest is not nil, you should set the value of this property to YES if you support random access to arbitrary ranges of bytes of the resource. If you do not set this property to YES for resources that must be loaded incrementally, loading of the resource may fail. Such resources include anything that contains media data.
*/
@property (nonatomic, getter=isByteRangeAccessSupported) BOOL byteRangeAccessSupported;

/*!
 @property		renewalDate
 @abstract		For resources that expire, the date at which a new AVAssetResourceLoadingRequest will be issued for a renewal of this resource, if the media system still requires it.
 @discussion	Before you finish loading an AVAssetResourceLoadingRequest, if the resource is prone to expiry you should set the value of this property to the date at which a renewal should be triggered. This value should be set sufficiently early enough to allow an AVAssetResourceRenewalRequest, delivered to your delegate via -resourceLoader:shouldWaitForRenewalOfRequestedResource:, to finish before the actual expiry time. Otherwise media playback may fail.
 */
@property (nonatomic, copy, nullable) NSDate *renewalDate NS_AVAILABLE(10_10, 8_0);

@end

/*!
	@class		AVAssetResourceLoadingDataRequest
 
	@abstract	An AVAssetResourceLoadingDataRequest is used to request data from a resource referenced by an AVAssetResourceLoadingRequest.
 
	@discussion
		The AVAssetResourceLoaderDelegate uses the AVAssetResourceLoadingDataRequest class to do the actual data reading, and its methods will be invoked, as necessary, to acquire data for the AVAssetResourceLoadingRequest instance.

		When a resource loading delegate accepts responsibility for loading a resource by returning YES from its implementation of resourceLoader:shouldWaitForLoadingOfRequestedResource:, it must check whether the dataRequest property of the AVAssetResourceLoadingRequest instance is not nil. If it is not nil, the resource loading delegate is informed of the range of bytes within the resource that are required by the underlying media system. In response, the data is provided by one or more invocations of respondWithData: as needed for provision of the requested data. The data can be provided in increments determined by the resource loading delegate according to convenience or efficiency.

		When the AVAssetResourceLoadingRequest method finishLoading is invoked, the data request is considered fully satisfied. If the entire range of bytes requested has not yet been provided, the underlying media system assumes that the resource's length is limited to the provided content. 
*/

@class AVAssetResourceLoadingDataRequestInternal;

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVAssetResourceLoadingDataRequest : NSObject {
@private
	AVAssetResourceLoadingDataRequestInternal *_dataRequest;
}
AV_INIT_UNAVAILABLE

/*! 
 @property 		requestedOffset
 @abstract		The position within the resource of the first byte requested.
*/
@property (nonatomic, readonly) long long requestedOffset;

/*! 
 @property 		requestedLength
 @abstract		The length of the data requested.
 @discussion	Note that requestsAllDataToEndOfResource will be set to YES when the entire remaining length of the resource is being requested from requestedOffset to the end of the resource. This can occur even when the content length has not yet been reported by you via a prior finished loading request.
 				When requestsAllDataToEndOfResource has a value of YES, you should disregard the value of requestedLength and incrementally provide as much data starting from the requestedOffset as the resource contains, until you have provided all of the available data successfully and invoked -finishLoading, until you have encountered a failure and invoked -finishLoadingWithError:, or until you have received -resourceLoader:didCancelLoadingRequest: for the AVAssetResourceLoadingRequest from which the AVAssetResourceLoadingDataRequest was obtained.
 				When requestsAllDataToEndOfResource is YES and the content length has not yet been provided by you via a prior finished loading request, the value of requestedLength is set to NSIntegerMax. Starting in OS X 10.11 and iOS 9.0, in 32-bit applications requestedLength is also set to NSIntegerMax when all of the remaining resource data is being requested and the known length of the remaining data exceeds NSIntegerMax.
*/
@property (nonatomic, readonly) NSInteger requestedLength;

/*! 
 @property 		requestsAllDataToEndOfResource
 @abstract		Specifies that the entire remaining length of the resource from requestedOffset to the end of the resource is being requested.
 @discussion	When requestsAllDataToEndOfResource has a value of YES, you should disregard the value of requestedLength and incrementally provide as much data starting from the requestedOffset as the resource contains, until you have provided all of the available data successfully and invoked -finishLoading, until you have encountered a failure and invoked -finishLoadingWithError:, or until you have received -resourceLoader:didCancelLoadingRequest: for the AVAssetResourceLoadingRequest from which the AVAssetResourceLoadingDataRequest was obtained.
*/
@property (nonatomic, readonly) BOOL requestsAllDataToEndOfResource NS_AVAILABLE(10_11, 9_0);

/*! 
 @property 		currentOffset
 @abstract		The position within the resource of the next byte within the resource following the bytes that have already been provided via prior invocations of -respondWithData.
*/
@property (nonatomic, readonly) long long currentOffset;

/*! 
 @method 		respondWithData:   
 @abstract		Provides data to the receiver.
 @param			data
 				An instance of NSData containing some or all of the requested bytes.
 @discussion	May be invoked multiple times on the same instance of AVAssetResourceLoadingDataRequest to provide the full range of requested data incrementally. Upon each invocation, the value of currentOffset will be updated to accord with the amount of data provided.
*/
- (void)respondWithData:(NSData *)data;

@end

@interface AVAssetResourceLoader (AVAssetResourceLoaderContentKeySupport)

/*!
 @property 		preloadsEligibleContentKeys
 @abstract		When YES, eligible content keys will be loaded as eagerly as possible, potentially handled by the delegate. Setting to YES may result in network activity.
 @discussion	Any work done as a result of setting this property will be performed asynchronously.
*/
@property (nonatomic) BOOL preloadsEligibleContentKeys NS_AVAILABLE(10_11, 9_0);

@end

@interface AVAssetResourceLoadingRequest (AVAssetResourceLoadingRequestContentKeyRequestSupport)

/*! 
 @method 		streamingContentKeyRequestDataForApp:contentIdentifier:options:error:   
 @abstract		Obtains a streaming content key request for a specific combination of application and content.
 @param			appIdentifier
 				An opaque identifier for the application. The value of this identifier depends on the particular system used to provide the decryption key.
 @param			contentIdentifier
 				An opaque identifier for the content. The value of this identifier depends on the particular system used to provide the decryption key.
 @param			options
 				Additional information necessary to obtain the key, or nil if none.
 @param			error
 				If obtaining the streaming content key request fails, will be set to an instance of NSError describing the failure.
 @result		The key request data that must be transmitted to the key vendor to obtain the content key.
*/
- (nullable NSData *)streamingContentKeyRequestDataForApp:(NSData *)appIdentifier contentIdentifier:(NSData *)contentIdentifier options:(nullable NSDictionary<NSString *, id> *)options error:(NSError * _Nullable * _Nullable)outError;

/*! 
 @method 		persistentContentKeyFromKeyVendorResponse:options:error:
 @abstract		Obtains a persistable content key from a context.
 @param			keyVendorResponse
 				The response returned from the key vendor as a result of a request generated from streamingContentKeyRequestDataForApp:contentIdentifier:options:error:.
 @param			options
 				Additional information necessary to obtain the persistable content key, or nil if none.
 @param			error
 				If obtaining the persistable content key fails, will be set to an instance of NSError describing the failure.
 @result		The persistable content key data that may be stored offline to answer future loading requests of the same content key.
 @discussion	The data returned from this method may be used to immediately satisfy an AVAssetResourceLoadingDataRequest, as well as any subsequent requests for the same key url. The value of AVAssetResourceLoadingContentInformationRequest.contentType must be set to AVStreamingKeyDeliveryPersistentContentKeyType when responding with data created with this method.
*/
- (NSData *)persistentContentKeyFromKeyVendorResponse:(NSData *)keyVendorResponse options:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)outError NS_AVAILABLE_IOS(9_0);

@end

// Options keys for use with -[AVAssetResourceLoadingRequest streamingContentKeyRequestDataForApp:contentIdentifier:trackID:options:error:]
/*!
 @constant		AVAssetResourceLoadingRequestStreamingContentKeyRequestRequiresPersistentKey
 @abstract		Specifies whether the content key request should require a persistable key to be returned from the key vendor. Value should be a NSNumber created with +[NSNumber numberWithBool:].
*/
AVF_EXPORT NSString *const AVAssetResourceLoadingRequestStreamingContentKeyRequestRequiresPersistentKey NS_AVAILABLE_IOS(9_0);

@interface AVAssetResourceLoadingRequest (AVAssetResourceLoadingRequestDeprecated)

/*! 
 @method 		finishLoadingWithResponse:data:redirect:   
 @abstract		Causes the receiver to finish loading a resource that a delegate has previously assumed responsibility for loading by returning YES as the result of -resourceLoader:shouldWaitForLoadingOfRequestedResource:.
 @param			response
 				The NSURLResponse for the NSURLRequest of the receiver. Should be nil if no response is required.
 @param			data
 				An instance of NSData containing the data of the resource. Should be nil if no such data is available.
 @param			redirect
 				An instance of NSURLRequest indicating a redirect of the loading request. Should be nil if no redirect is needed.
 @discussion	This method is deprecated. Use the following methods instead.
					-[AVAssetResourceLoadingRequest setResponse:] to set the response property,
					-[AVAssetResourceLoadingRequest setRedirect:] to set the redirect property,
					-[AVAssetResourceLoadingDataRequest respondWithData:] to provide data, and
					-[AVAssetResourceLoadingRequest finishLoading] to indicate that loading is finished.
*/
- (void)finishLoadingWithResponse:(nullable NSURLResponse *)response data:(nullable NSData *)data redirect:(nullable NSURLRequest *)redirect NS_DEPRECATED_IOS(6_0, 7_0);

@end

NS_ASSUME_NONNULL_END
