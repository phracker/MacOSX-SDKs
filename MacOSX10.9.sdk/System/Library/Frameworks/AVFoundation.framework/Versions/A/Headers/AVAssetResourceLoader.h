/*
	File:  AVAssetResourceLoader.h

	Framework:  AVFoundation
 
	Copyright 2010-2013 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

@protocol AVAssetResourceLoaderDelegate;

@class AVAssetResourceLoadingRequest;
@class AVAssetResourceLoaderInternal;

NS_CLASS_AVAILABLE(10_9, 6_0)
@interface AVAssetResourceLoader : NSObject {
@private
	AVAssetResourceLoaderInternal *_resourceLoader;
}

/*!
 @method 		setDelegate:queue:
 @abstract		Sets the receiver's delegate that will mediate resource loading and the dispatch queue on which delegate methods will be invoked.
 @param			delegate
				An object conforming to the AVAssetResourceLoaderDelegate protocol.
 @param			delegateQueue
				A dispatch queue on which all delegate methods will be invoked.
*/
- (void)setDelegate:(id<AVAssetResourceLoaderDelegate>)delegate queue:(dispatch_queue_t)delegateQueue;

/*!
 @property 		delegate
 @abstract		The receiver's delegate.
 @discussion
  The value of this property is an object conforming to the AVAssetResourceLoaderDelegate protocol. The delegate is set using the setDelegate:queue: method.
*/
@property (nonatomic, readonly) id<AVAssetResourceLoaderDelegate> delegate;

/*!
 @property 		delegateQueue
 @abstract		The dispatch queue on which all delegate methods will be invoked.
 @discussion
  The value of this property is a dispatch_queue_t. The queue is set using the setDelegate:queue: method.
*/
@property (nonatomic, readonly) dispatch_queue_t delegateQueue;

@end


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
 @method 		resourceLoader:didCancelLoadingRequest:
 @abstract		Informs the delegate that a prior loading request has been cancelled.
 @param 		loadingRequest
				The loading request that has been cancelled. 
 @discussion	Previously issued loading requests can be cancelled when data from the resource is no longer required or when a loading request is superseded by new requests for data from the same resource. For example, if to complete a seek operation it becomes necessary to load a range of bytes that's different from a range previously requested, the prior request may be cancelled while the delegate is still handling it.
*/
- (void)resourceLoader:(AVAssetResourceLoader *)resourceLoader didCancelLoadingRequest:(AVAssetResourceLoadingRequest *)loadingRequest NS_AVAILABLE(10_9, 7_0);

@end


@class AVAssetResourceLoadingRequestInternal;
@class AVAssetResourceLoadingContentInformationRequest;
@class AVAssetResourceLoadingDataRequest;

NS_CLASS_AVAILABLE(10_9, 6_0)
@interface AVAssetResourceLoadingRequest : NSObject {
@private
	AVAssetResourceLoadingRequestInternal *_loadingRequest;
}

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
@property (nonatomic, readonly) AVAssetResourceLoadingContentInformationRequest *contentInformationRequest NS_AVAILABLE(10_9, 7_0);

/*! 
 @property 		dataRequest
 @abstract		An instance of AVAssetResourceLoadingDataRequest that indicates the range of resource data that's being requested. The value of this property will be nil if no data is being requested.
*/
@property (nonatomic, readonly) AVAssetResourceLoadingDataRequest *dataRequest NS_AVAILABLE(10_9, 7_0);

/*! 
 @property 		response
 @abstract		Set the value of this property to an instance of NSURLResponse indicating a response to the loading request. If no response is needed, leave the value of this property set to nil.
*/
@property (nonatomic, copy) NSURLResponse *response NS_AVAILABLE(10_9, 7_0);

/*! 
 @property 		redirect
 @abstract		Set the value of this property to an instance of NSURLRequest indicating a redirection of the loading request to another URL. If no redirection is needed, leave the value of this property set to nil.
*/
@property (nonatomic, copy) NSURLRequest *redirect NS_AVAILABLE(10_9, 7_0);

/*! 
 @method 		finishLoading   
 @abstract		Causes the receiver to treat the processing of the request as complete.
 @discussion	If a dataRequest is present and the resource does not contain the full extent of the data that has been requested according to the values of the requestedOffset and requestedLength properties of the dataRequest, you may invoke -finishLoading after you have provided as much of the requested data as the resource contains.
*/
- (void)finishLoading NS_AVAILABLE(10_9, 7_0);

/*! 
 @method 		finishLoadingWithError:   
 @abstract		Causes the receiver to treat the request as having failed.
 @param			error
 				An instance of NSError indicating the reason for failure.
*/
- (void)finishLoadingWithError:(NSError *)error;

@end


@class AVAssetResourceLoadingContentInformationRequestInternal;

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVAssetResourceLoadingContentInformationRequest : NSObject {
@private
	AVAssetResourceLoadingContentInformationRequestInternal *_contentInformationRequest;
}

/*! 
 @property 		contentType
 @abstract		A UTI that indicates the type of data contained by the requested resource.
 @discussion	Before you finish loading an AVAssetResourceLoadingRequest, if its contentInformationRequest is not nil, you should set the value of this property to a UTI indicating the type of data contained by the requested resource.
*/
@property (nonatomic, copy) NSString *contentType;

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

@end


@class AVAssetResourceLoadingDataRequestInternal;

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVAssetResourceLoadingDataRequest : NSObject {
@private
	AVAssetResourceLoadingDataRequestInternal *_dataRequest;
}

/*! 
 @property 		requestedOffset
 @abstract		The position within the resource of the first byte requested.
*/
@property (nonatomic, readonly) long long requestedOffset;

/*! 
 @property 		requestedLength
 @abstract		The length of the data requested.
 @discussion	If the content length of the resource is not precisely known, the sum of requestedLength and requestedOffset may be greater than the actual content length of the resource. When this occurs, you should attempt to provide as much of the requested data from the requestedOffset as the resource contains before invoking either -finishLoading (if you succeed) or -finishLoadingWithError: (if you encounter a failure in the course of providing the data).
*/
@property (nonatomic, readonly) NSInteger requestedLength;

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


@interface AVAssetResourceLoadingRequest (AVAssetResourceLoader_ContentKeyRequestSupport)

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
- (NSData *)streamingContentKeyRequestDataForApp:(NSData *)appIdentifier contentIdentifier:(NSData *)contentIdentifier options:(NSDictionary *)options error:(NSError **)outError;

@end


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
- (void)finishLoadingWithResponse:(NSURLResponse *)response data:(NSData *)data redirect:(NSURLRequest *)redirect NS_DEPRECATED_IOS(6_0, 7_0);

@end
