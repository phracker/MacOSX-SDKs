#if !__has_include(<AVFCore/AVContentKeySession.h>)
/*
    File: AVContentKeySession.h

    Copyright (c) 2015-2018 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

@class AVContentKeySessionInternal;
@class AVContentKeyRequest;
@class AVContentKeyResponse;
@class AVPersistableContentKeyRequest;
@protocol AVContentKeyRecipient;
@protocol AVContentKeySessionDelegate;
@class AVContentKeySpecifier;
@class AVContentKey;

/// Used by AVContentKeySession to determine the method of key delivery
typedef NSString *AVContentKeySystem NS_STRING_ENUM API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

/// Used to specify FairPlay Streaming (FPS) as the method of key delivery.
AVF_EXPORT AVContentKeySystem const AVContentKeySystemFairPlayStreaming API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

/// Used to specify clear key as the method of key delivery.
AVF_EXPORT AVContentKeySystem const AVContentKeySystemClearKey API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(7.0), visionos(1.0));

/// Used to specify a token that could be used to authorize playback of associated content key recipients.
AVF_EXPORT AVContentKeySystem const AVContentKeySystemAuthorizationToken API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(7.0), visionos(1.0));

/// An AVContentKeySession is used to create and track decryption keys for media data. Objects conforming to the AVContentKeyRecipient protocol, such as AVURLAssets, can be added to an AVContentKeySession to employ the services of the AVContentKeySession in handling new key requests and to obtain access to the session's already existing keys.
///
/// Its secondary purpose is to provide a report of expired sessions to assist a controlling entity that wishes to track the set of sessions that are still active. If initialized with a location at which to store them, AVContentKeySession maintains a global collection of pending "expired session reports", each associated with an identifier for the app that created the session. The contents of this identifier are specified by the controlling entity that provides media data or that grants permission for its use.
///
/// Expired sessions are tracked as follows: a stream processing session is considered to be started after an instance of AVContentKeySession is created and the first object conforming to the AVContentKeyRecipient protocol is added to it. If an instance of AVContentKeySession that has reached this state does not receive an expire message before it's deallocated or the process in which it's running is terminated, an "expired session report" will subsequently be added to the pending list of expired session reports that indicates that the session expired abnormally. In contrast, for AVContentKeySessions that reach the state of having at least one object conforming to the AVContentKeyRecipient protocol added to them and later receive an expire message, "expired session reports" will be generated that indicate that the session expired normally.
///
/// To obtain the collection of pending expired session reports in order to provide them to the controlling entity associated with a specific app identifier, use +pendingExpiredSessionReportsWithAppIdentifier:.
///
/// After pending expired session reports have been sent to the controlling entity and their receipt has been acknowledged, they can be removed from the collection of pending expired session reports maintained by AVContentKeySession by using +removePendingExpiredSessionReports:withAppIdentifier:.
///
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0))
@interface AVContentKeySession : NSObject {
@private
    AVContentKeySessionInternal *_session;
}
AV_INIT_UNAVAILABLE

/// Creates a new instance of AVContentKeySession to manage a collection of media content keys.
/// 
/// This method returns an AVContentKeySession instance that is capable of managing collection of media content keys corresponding to the input keySystem. An NSInvalidArgumentException will be raised if the value of keySystem is unsupported.
/// 
/// - Parameter keySystem: A valid key system for retrieving keys.
/// 
/// - Returns: A new AVContentKeySession.
+ (instancetype)contentKeySessionWithKeySystem:(AVContentKeySystem)keySystem API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(7.0), visionos(1.0));

/// Creates a new instance of AVContentKeySession to manage a collection of media content keys.
/// 
/// This method returns an AVContentKeySession instance that is capable of managing collection of media content keys corresponding to the input keySystem. An NSInvalidArgumentException will be raised if the value of keySystem is unsupported.
/// 
/// - Parameter keySystem: A valid key system for retrieving keys.
/// - Parameter storageURL: URL to a writable directory that the session will use to facilitate expired session reports after abnormal session termination.
/// 
/// - Returns: A new AVContentKeySession.
+ (instancetype)contentKeySessionWithKeySystem:(AVContentKeySystem)keySystem storageDirectoryAtURL:(NSURL *)storageURL;

/// Sets the receiver's delegate. A delegate is required to handle content key initialization.
/// 
/// - Parameter delegate: An object conforming to the AVContentKeySessionDelegate protocol.
/// - Parameter delegateQueue: A dispatch queue on which delegate methods will be invoked whenever processes requiring content keys are executed asynchronously. Passing a value of nil for the delegateQueue parameter along with a non-nil value for the delegate parameter will result in an invalid argument exception.
- (void)setDelegate:(nullable id <AVContentKeySessionDelegate>)delegate queue:(nullable dispatch_queue_t)delegateQueue;

/// The receiver's delegate.
/// 
/// The value of this property is an object conforming to the AVContentKeySessionDelegate protocol. The delegate is set using the setDelegate:queue: method.
@property (readonly, weak, nullable) id<AVContentKeySessionDelegate> delegate;

/// The dispatch queue on which all delegate methods will be invoked whenever processes requiring content keys are executed asynchronously.
/// 
/// The value of this property is a dispatch_queue_t. The queue is set using the setDelegate:queue: method.
@property (readonly, nullable) dispatch_queue_t delegateQueue;

/// The storage URL provided when the AVContentKeySession was created. May be nil.
/// 
/// URL to a writable directory; may be nil. The session will use this to facilitate expired session reports after abnormal session termination.
@property (readonly, nullable) NSURL *storageURL;

/// The key system used for retrieving keys
@property (readonly) AVContentKeySystem keySystem;

/// Tells the receiver to treat the session as having been intentionally and normally expired.
/// 
/// When an instance of AVContentKeySession receives an expire message, all of its associated objects conforming to the AVContentKeyRecipient protocol will become inoperable. Send this message only after you have finished operating on the media data.
- (void)expire;

/// An opaque identifier for the current content protection session.
/// 
/// May be nil. Will call the delegate's contentKeySessionContentProtectionSessionIdentifierDidChange: when the identifier changes. The protection session ID is a unique string identifier generated by the AVContentKeySession that can be used by the application to identify content key session objects.
@property (readonly, nullable) NSData *contentProtectionSessionIdentifier;

/// Informs the receiver that it should attempt to instantiate a content decryption key using the specified initialization data.
/// 
/// May be used to generate an AVContentKeyRequest from request initialization data already in hand, without awaiting such data during the processing of media data of an associated recipient.
/// 
/// - Parameter identifier: Container- and protocol-specific identifier to be used to obtain a key response. Either identifier or initializationData must be non-nil. Both can be non-nil, if the content protection protocol requires both.
/// - Parameter initializationData: Container- and protocol-specific data to be used to obtain a key response. Either identifier or initializationData must be non-nil. Both can be non-nil, if the content protection protocol requires both.
/// - Parameter options: Additional information necessary to obtain the key, or nil if none. See AVContentKeyRequest*Key below.
- (void)processContentKeyRequestWithIdentifier:(nullable id) NS_SWIFT_SENDABLE identifier initializationData:(nullable NSData *)initializationData options:(nullable NSDictionary<NSString *, id> *) NS_SWIFT_SENDABLE options;

/// Informs the receiver that the already provided response data for an earlier AVContentKeyRequest will imminently expire.
/// 
/// In response the receiver will invoke your delegate with a new content key request entreating it to renew the expiring response data, via -contentKeySession:didProvideRenewingContentKeyRequest:.
- (void)renewExpiringResponseDataForContentKeyRequest:(AVContentKeyRequest *)contentKeyRequest;

/// Creates a secure server playback context (SPC) that the client could send to the key server to obtain an expiration date for the provided persistable content key data.
/// 
/// - Parameter persistableContentKeyData: Persistable content key data that was previously created using -[AVContentKeyRequest persistableContentKeyFromKeyVendorResponse:options:error:] or obtained via AVContentKeySessionDelegate callback -contentKeySession:didUpdatePersistableContentKey:forContentKeyIdentifier:.
/// - Parameter handler: Once the secure token is ready, this block will be called with the token or an error describing the failure.
- (void)makeSecureTokenForExpirationDateOfPersistableContentKey:(NSData *)persistableContentKeyData
											  completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSData * _Nullable secureTokenData, NSError * _Nullable error))handler API_AVAILABLE(macos(10.15), ios(11.0), tvos(17.0), watchos(7.0), visionos(1.0));

/// Options keys used to specify additional information for generating server playback context (SPC) in
/// -[AVContentKeySession invalidatePersistableContentKey:options:completionHandler:] and
/// -[AVContentKeySession invalidateAllPersistableContentKeysForApp:options:completionHandler:]
typedef NSString * AVContentKeySessionServerPlaybackContextOption NS_STRING_ENUM;

/// Specifies the versions of the content protection protocol supported by the application; as an NSArray of one or more NSNumber objects. If this option is not set, an appropriate protocol version will be selected based on sideband information such as an associated HLS playlist. If such information is not available, a protocol version of 1 is assumed
AVF_EXPORT AVContentKeySessionServerPlaybackContextOption const AVContentKeySessionServerPlaybackContextOptionProtocolVersions API_AVAILABLE(macos(10.15), ios(12.2), tvos(17.0), watchos(7.0), visionos(1.0));

/// Specifies a nonce as a 8-byte NSData object to be included in the secure server playback context (SPC) in order to prevent replay attacks. If not specified default server challenge of 0 is assumed.
AVF_EXPORT AVContentKeySessionServerPlaybackContextOption const AVContentKeySessionServerPlaybackContextOptionServerChallenge API_AVAILABLE(macos(10.15), ios(12.2), tvos(17.0), watchos(7.0), visionos(1.0));

/// Invalidates the persistable content key and creates a secure server playback context (SPC) that the client could send to the key server to verify the outcome of invalidation request.
/// 
/// Once invalidated, a persistable content key cannot be used to answer key requests during later playback sessions.
/// 
/// - Parameter persistableContentKeyData: Persistable content key data that was previously created using -[AVContentKeyRequest persistableContentKeyFromKeyVendorResponse:options:error:] or obtained via AVContentKeySessionDelegate callback -contentKeySession:didUpdatePersistableContentKey:forContentKeyIdentifier:.
/// - Parameter options: Additional information necessary to generate the server playback context, or nil if none. See AVContentKeySessionServerPlaybackContextOption for supported options.
/// - Parameter handler: Once the server playback context is ready, this block will be called with the data or an error describing the failure.
- (void)invalidatePersistableContentKey:(NSData *)persistableContentKeyData
								options:(nullable NSDictionary<AVContentKeySessionServerPlaybackContextOption, id> *)options
					  completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSData * _Nullable secureTokenData, NSError * _Nullable error))handler API_AVAILABLE(macos(10.15), ios(12.2), tvos(17.0), watchos(7.0), visionos(1.0));

/// Invalidates all persistable content keys associated with the application and creates a secure server playback context (SPC) that the client could send to the key server to verify the outcome of invalidation request.
/// 
/// Once invalidated, persistable content keys cannot be used to answer key requests during later playback sessions.
/// 
/// - Parameter appIdentifier: An opaque identifier for the application. The contents of this identifier depend on the particular protocol in use by the entity that controls the use of the media data.
/// - Parameter options: Additional information necessary to generate the server playback context, or nil if none. See AVContentKeySessionServerPlaybackContextOption for supported options.
/// - Parameter handler: Once the server playback context is ready, this block will be called with the data or an error describing the failure.
- (void)invalidateAllPersistableContentKeysForApp:(NSData *)appIdentifier
										  options:(nullable NSDictionary<AVContentKeySessionServerPlaybackContextOption, id> *)options
								completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSData * _Nullable secureTokenData, NSError * _Nullable error))handler API_AVAILABLE(macos(10.15), ios(12.2), tvos(17.0), watchos(7.0), visionos(1.0));

@end

@interface AVContentKeySession (AVContentKeyRecipients)

/// Informs the receiver that the specified recipient will be used for the session.
/// 
/// It is an error to add recipient to sessions that have received an expire message. It is also an error to add recipients after they have already begun to process media data (e.g. after an AVURLAsset has loaded the values of any of its keys). Such errors will result in NSInternalInconsistencyExceptions. Sending this message to an AVContentKeySession is atomic.
- (void)addContentKeyRecipient:(id<AVContentKeyRecipient>)recipient;

/// Informs the receiver that the specified recipient will no longer be used.
/// 
/// After the specified recipient is removed from the receiver it will become inoperable. Remove the recipient only after you have finished operating on the media data associated with it. Sending this message to an AVContentKeySession is atomic.
- (void)removeContentKeyRecipient:(id<AVContentKeyRecipient>)recipient;

/// The array of recipients of content keys currently associated with the AVContentKeySession.
@property (readonly) NSArray<id<AVContentKeyRecipient>> *contentKeyRecipients;

@end

@interface AVContentKeySession (AVContentKeySessionPendingExpiredSessionReports)

/// Provides "expired session reports" for prior AVContentKeySessions created with the specified app identifier that have expired either normally or abnormally.
/// 
/// Note that no reports for sessions still in progress will be included.
/// 
/// - Parameter appIdentifier: An opaque identifier for the application. The contents of this identifier depend on the particular protocol in use by the entity that controls the use of the media data.
/// - Parameter storageURL: URL to a directory previously used with one or more instances of AVContentKeySession for the storage of expired session reports.
/// 
/// - Returns: An NSArray containing instances of NSData, each containing a pending expired session report as a property-list serialization of an NSDictionary object. The contents of expired session reports depend on the particular protocol in use by the entity that controls the use of the media data.
+ (NSArray <NSData *> *)pendingExpiredSessionReportsWithAppIdentifier:(NSData *)appIdentifier storageDirectoryAtURL:(NSURL *)storageURL;

/// Removes expired session reports for prior AVContentKeySessions from storage. Once they have been removed, they will no longer be available via subsequent invocations of +pendingExpiredSessionReportsWithAppIdentifier:.
/// 
/// This method is most suitable for use only after the specified expired session reports have been sent to the entity that controls the use of the media data and the entity has acknowledged their receipt.
/// 
/// - Parameter expiredSessionReports: An array of expired session reports to be discarded.
/// - Parameter appIdentifier: An opaque identifier for the application. The contents of this identifier depend on the particular protocol in use by the entity that controls the use of the media data.
/// - Parameter storageURL: URL to a writable folder.
+ (void)removePendingExpiredSessionReports:(NSArray <NSData *> *)expiredSessionReports withAppIdentifier:(NSData *)appIdentifier storageDirectoryAtURL:(NSURL *)storageURL;

@end

/// Used to specify a reason for asking the client to retry a content key request.
typedef NSString *AVContentKeyRequestRetryReason NS_STRING_ENUM API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

/// Indicates that the content key request should be retried because the key response was not set soon enough either due the initial request/response was taking too long, or a lease was expiring in the meantime.
AVF_EXPORT AVContentKeyRequestRetryReason const AVContentKeyRequestRetryReasonTimedOut API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

/// Indicates that the content key request should be retried because a key response with expired lease was set on the previous content key request.
AVF_EXPORT AVContentKeyRequestRetryReason const AVContentKeyRequestRetryReasonReceivedResponseWithExpiredLease API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

/// Indicates that the content key request should be retried because an obsolete key response was set on the previous content key request.
AVF_EXPORT AVContentKeyRequestRetryReason const AVContentKeyRequestRetryReasonReceivedObsoleteContentKey API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0))
@protocol AVContentKeySessionDelegate <NSObject>

/// Provides the receiver with a new content key request.
/// 
/// Will be invoked by an AVContentKeySession as a result of a call to -processContentKeyRequestWithIdentifier:initializationData:options:. Can be invoked during playback or other processing of an AVURLAsset added to the AVContentKeySession.
/// 
/// Note that `AVContentKeyRequest` objects provided by this method are strongly tied to the lifetime of their managing `AVContentKeySession`. Attempting to use `AVContentKeyRequest` objects after their corresponding `AVContentKeySession` has been released may result in an exception.
/// 
/// - Parameter session: An instance of AVContentKeySession that's providing a new content key request.
/// - Parameter keyRequest: An instance of AVContentKeyRequest.
@required
- (void)contentKeySession:(AVContentKeySession *)session didProvideContentKeyRequest:(AVContentKeyRequest *)keyRequest;

/// Provides the receiver with a new content key request representing a renewal of an existing content key.
/// 
/// Will be invoked by an AVContentKeySession as the result of a call to -renewExpiringResponseDataForContentKeyRequest:.
/// 
/// Note that `AVContentKeyRequest` objects provided by this method are strongly tied to the lifetime of their managing `AVContentKeySession`. Attempting to use `AVContentKeyRequest` objects after their corresponding `AVContentKeySession` has been released may result in an exception.
/// 
/// - Parameter session: An instance of AVContentKeySession that's providing a new content key request.
/// - Parameter keyRequest: An instance of AVContentKeyRequest representing renewal of a previous content key.
@optional
- (void)contentKeySession:(AVContentKeySession *)session didProvideRenewingContentKeyRequest:(AVContentKeyRequest *)keyRequest;

/// Provides the receiver with a new content key request that allows key persistence.
/// 
/// Will be invoked by an AVContentKeyRequest as the result of a call to -respondByRequestingPersistableContentKeyRequest.
/// 
/// Note that `AVPersistableContentKeyRequest` objects provided by this method are strongly tied to the lifetime of their managing `AVContentKeySession`. Attempting to use `AVPersistableContentKeyRequest` objects after their corresponding `AVContentKeySession` has been released may result in an exception.
/// 
/// - Parameter session: An instance of AVContentKeySession that's providing a new content key request.
/// - Parameter keyRequest: An instance of AVPersistableContentKeyRequest.
@optional
- (void)contentKeySession:(AVContentKeySession *)session didProvidePersistableContentKeyRequest:(AVPersistableContentKeyRequest *)keyRequest;

/// Provides the receiver with an updated persistable content key for a particular key request.
/// 
/// If the content key session provides an updated persistable content key data, the previous key data is no longer valid and cannot be used to answer future loading requests.
/// 
/// - Parameter session: An instance of AVContentKeySession that is providing the updated persistable content key.
/// - Parameter persistableContentKey: Updated persistable content key data that may be stored offline and used to answer future requests to content keys with matching key identifier.
/// - Parameter keyIdentifier: Container- and protocol-specific identifier for the persistable content key that was updated.
@optional
- (void)contentKeySession:(AVContentKeySession *)session didUpdatePersistableContentKey:(NSData *)persistableContentKey forContentKeyIdentifier:(id)keyIdentifier API_AVAILABLE(macos(10.15), ios(11.0), tvos(17.0), watchos(7.0), visionos(1.0));

/// Informs the receiver a content key request has failed.
/// 
/// - Parameter session: The instance of AVContentKeySession that initiated the content key request.
/// - Parameter keyRequest: The instance of AVContentKeyRequest that has failed.
/// - Parameter error: An instance of NSError that describes the failure that occurred.
@optional
- (void)contentKeySession:(AVContentKeySession *)session contentKeyRequest:(AVContentKeyRequest *)keyRequest didFailWithError:(NSError *)err;

/// Provides the receiver a content key request that should be retried because a previous content key request failed.
/// 
/// Will be invoked by an AVContentKeySession when a content key request should be retried. The reason for failure of previous content key request is specified. The receiver can decide if it wants to request AVContentKeySession to retry this key request based on the reason. If the receiver returns YES, AVContentKeySession would restart the key request process. If the receiver returns NO or if it does not implement this delegate method, the content key request would fail and AVContentKeySession would let the receiver know through -contentKeySession:contentKeyRequest:didFailWithError:.
/// 
/// - Parameter session: An instance of AVContentKeySession that's providing the content key request that should be retried.
/// - Parameter keyRequest: An instance of AVContentKeyRequest that should be retried.
/// - Parameter retryReason: An enum value to explain why the receiver could retry the new content key request.
/// 
/// - Returns: A BOOL value indicating receiver's desire to retry the failed content key request.
@optional
- (BOOL)contentKeySession:(AVContentKeySession *)session shouldRetryContentKeyRequest:(AVContentKeyRequest *)keyRequest reason:(AVContentKeyRequestRetryReason)retryReason;

/// Informs the receiver that the response to content key request was successfully processed.
/// 
/// Will be invoked by an AVContentKeySession when it is certain that the response client provided via -[AVContentKeyRequest processContentKeyResponse:] was successfully processed by the system.
/// 
/// - Parameter session: The instance of AVContentKeySession that initiated the content key request.
/// - Parameter keyRequest: The instance of AVContentKeyRequest whose response was successfully processed.
@optional
- (void)contentKeySession:(AVContentKeySession *)session contentKeyRequestDidSucceed:(AVContentKeyRequest *)keyRequest API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(7.0), visionos(1.0));

/// Informs the receiver that the value of -[AVContentKeySession contentProtectionSessionIdentifier] has changed.
@optional
- (void)contentKeySessionContentProtectionSessionIdentifierDidChange:(AVContentKeySession *)session;

/// Notifies the sender that a expired session report has been generated
/// 
/// Will be invoked by an AVContentKeySession when an expired session report is added to the storageURL
/// 
/// - Parameter session: An instance of AVContentKeySession that recorded the generation of an expired session report.
@optional
- (void)contentKeySessionDidGenerateExpiredSessionReport:(AVContentKeySession *)session API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(7.0), visionos(1.0));

/// Informs the receiver when external protection state has changed.
/// 
/// When externalProtectionStatusDidChangeForContentKey is received, externalContentProtectionStatus should be queried to obtain the latest state.
/// 
/// - Parameter session: An instance of AVContentKeySession that loaded the content key.
/// - Parameter contentKey: The content key for which the external protection state changed.
@optional
- (void)contentKeySession:(AVContentKeySession *)session externalProtectionStatusDidChangeForContentKey:(AVContentKey *)contentKey API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Provides the receiver with a list of new content key requests.
/// 
/// Will be invoked by an AVContentKeySession as a result of a call to -processContentKeyRequestWithIdentifier:initializationData:options:.
/// The requests for all keys in an initializationData will be provided at once through contentKeySession:didProvideContentKeyRequests:forInitializationData: and it takes precedence over contentKeySession:didProvideContentKeyRequest:.
/// 
/// - Parameter session: An instance of AVContentKeySession that's providing the list of new content key requests.
/// - Parameter keyRequests: An array with new AVContentKeyRequest instances.
/// - Parameter initializationData: InitializationData corresponding to the new AVContentKeyRequests. May be nil.
@optional
- (void)contentKeySession:(AVContentKeySession *)session didProvideContentKeyRequests:(NSArray<AVContentKeyRequest *> *)keyRequests forInitializationData:(nullable NSData *)initializationData API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), watchos(10.4), visionos(1.1));

@end


typedef NS_ENUM(NSInteger, AVContentKeyRequestStatus) {
    /// Indicates that the request has just been created.
    AVContentKeyRequestStatusRequestingResponse = 0,
    /// Indicates that a response to a key reequest was received and key is in use. This does not indicate that the key is valid.
    AVContentKeyRequestStatusReceivedResponse = 1,
    /// Indicates that the key request was renewed. This does not indicate that the key is valid.
    AVContentKeyRequestStatusRenewed = 2,
	/// Indicates that the key request was retried.
	AVContentKeyRequestStatusRetried = 3,
    /// Indicates that the key request was cancelled.
    AVContentKeyRequestStatusCancelled = 4,
    /// Indicates that the request has encountered an error. See also the error property.
    AVContentKeyRequestStatusFailed = 5
} API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

@class AVContentKeyRequestInternal;

/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0))
@interface AVContentKeyRequest : NSObject
{
@private
    AVContentKeyRequestInternal *_contentKeyRequest;
}

/// This describes the state of the AVContentKeyRequest, value is one of AVContentKeyRequestStatus.
@property (readonly) AVContentKeyRequestStatus status;

/// If the receiver's status is AVContentKeyRequestStatusFailed, this describes the error that caused the failure.
/// 
/// The value of this property is an NSError that describes what caused the content key request to fail. If the receiver's status is not AVContentKeyRequestStatusFailed, the value of this property is nil.
@property (readonly, nullable) NSError *error;

/// Container- and protocol-specific identifier for the content key.
/// 
/// In order to use a key with an HTTP Live Streaming AVURLAsset, the identifier must be an NSURL that matches a key URI in the Media Playlist.
@property (readonly, nullable) id NS_SWIFT_SENDABLE identifier;

/*
 @property      initializationData
 @abstract      Container- and protocol-specific data to be used to obtain a key response.
*/
@property (nonatomic, readonly, nullable) NSData *initializationData;

/// Additional information specified while initiaing key loading using -processContentKeyRequestWithIdentifier:initializationData:options:.
@property (readonly, copy) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE options API_AVAILABLE(macos(10.14.4), ios(12.2), tvos(12.2), watchos(7.0), visionos(1.0));

/// When the value of this property is YES, you can use the method -persistableContentKeyFromKeyVendorResponse:options:error: to create a persistable content key from the content key response.
///
/// The value of this property will be YES only when the receiver is provided to your AVContentKeySession delegate via the method -contentKeySession:didProvidePersistableContentKeyRequest:. If you have an AVContentKeyRequest for which the value of canProvidePersistableContentKey is NO, but you wish to obtain a persistable content key, send the AVContentKeyRequest the message -respondByRequestingPersistableContentKeyRequest.
@property (readonly) BOOL canProvidePersistableContentKey;

/// Specifies the requested content key.
@property (readonly) AVContentKeySpecifier *contentKeySpecifier API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0));

/// Represents an AVContentKey that results from an invocation of -processContentKeyResponse:.
/// 
/// Before the receiver achieves the status AVContentKeyRequestReceivedResponse, the value of this property will be nil. Once that status has been achieved, the value of this property becomes a non-nil AVContentKey that can be provided to content key recipients that apply content keys manually to objects that require them, such as CMSampleBuffers, or to initiate renewal. A non-nil value does not indicate that the content key is valid; authorization failures may yet be possible.
@property (readonly, nullable) AVContentKey *contentKey API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0));

/// The AVContentKeyRecipient which initiated this request, if any.
/// 
/// The originatingRecipient is an AVFoundation object responsible for initiating an AVContentKeyRequest.
/// For example, an AVURLAsset used for playback can trigger an AVContentKeyRequest.
/// 
/// If an application triggers key loading directly, for example with
/// -[AVContentKeySession processContentKeyRequestWithIdentifier:initializationData:options:],
/// the value of originatingRecipient will be nil.
/// 
/// The originatingRecipient of key requests from HLS interstitials will always be the corresponding
/// interstitial AVURLAsset. To receive key requests for DRM-protected interstitial content, applications
/// must ensure their AVContentKeySession is attached to these interstitial AVURLAssets.
/// 
/// These interstitial AVURLAssets may be retrieved from the primary AVURLAsset via AVPlayerInterstitialEventMonitor.
@property (readonly, nullable, weak) id <AVContentKeyRecipient> originatingRecipient API_AVAILABLE(macos(15.4), ios(18.4), tvos(18.4), watchos(11.4), visionos(2.4));

/// Request secure token to have extended validation data. The value for the key should be previously created offline key using -[AVContentKeyRequest persistableContentKeyFromKeyVendorResponse:options:error:].
AVF_EXPORT NSString *const AVContentKeyRequestRequiresValidationDataInSecureTokenKey API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0), visionos(1.0));

/// Obtains a content key request data for a specific combination of application and content.
/// 
/// If option AVContentKeyRequestProtocolVersionsKey is not specified the default protocol version of 1 is assumed.
/// 
/// - Parameter appIdentifier: An opaque identifier for the application. The value of this identifier depends on the particular system used to provide the content key.
/// - Parameter contentIdentifier: An optional opaque identifier for the content. The value of this identifier depends on the particular system used to provide the content key.
/// - Parameter options: Additional information necessary to obtain the key, or nil if none. See AVContentKeyRequest*Key below.
/// - Parameter handler: Once the streaming content key request is prepared, this block will be called with the request data or an error describing the failure.
- (void)makeStreamingContentKeyRequestDataForApp:(NSData *)appIdentifier
                               contentIdentifier:(nullable NSData *)contentIdentifier
                                         options:(nullable NSDictionary<NSString *, id> *)options
                               completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSData * _Nullable contentKeyRequestData, NSError * _Nullable error))handler;

/// Informs the receiver to process the specified content key response.
/// 
/// After you receive an AVContentKeyRequest via -contentKeySession:didProvideContentKeyRequest: and after you invoke -[AVContentKeyRequest makeStreamingContentKeyRequestDataForApp:contentIdentifier:options:completionHandler:] on that request, you must obtain a response to the request in accordance with the protocol in use by the entity that controls the use of the media data. This is the method you use to provide the content key response to make protected content available for processing. If obtaining the content key response fails, use -processContentKeyResponseError:.
/// 
/// - Parameter keyResponse: An instance of AVContentKeyResponse carrying a response to a content key request.
- (void)processContentKeyResponse:(AVContentKeyResponse *)keyResponse;

/// Informs the receiver that obtaining a content key response has failed, resulting in failure handling.
/// 
/// - Parameter error: An instance of NSError that describes the specific failure that occurred.
- (void)processContentKeyResponseError:(NSError *)error;

/// Informs the receiver to process a persistable content key request.
/// 
/// When you receive an AVContentKeyRequest via -contentKeySession:didProvideContentKeyRequest: and you want the resulting key response to produce a key that can persist across multiple playback sessions, you must invoke -respondByRequestingPersistableContentKeyRequest on that AVContentKeyRequest in order to signal that you want to process an AVPersistableContentKeyRequest instead. If the underlying protocol supports persistable content keys, in response your delegate will receive an AVPersistableContentKeyRequest via -contentKeySession:didProvidePersistableContentKeyRequest:. NSInternalInconsistencyException will be raised, if you are attempting to create and use a persistable key but your AVContentKeySession delegate does not respond to contentKeySession:didProvidePersistableContentKeyRequest:.
- (void)respondByRequestingPersistableContentKeyRequest API_DEPRECATED_WITH_REPLACEMENT("respondByRequestingPersistableContentKeyRequestAndReturnError:", ios(10.3, 11.2)) API_UNAVAILABLE(macos, tvos, watchos, visionos);

/// Informs the receiver to process a persistable content key request.
/// 
/// When you receive an AVContentKeyRequest via -contentKeySession:didProvideContentKeyRequest: and you want the resulting key response to produce a key that can persist across multiple playback sessions, you must invoke -respondByRequestingPersistableContentKeyRequest on that AVContentKeyRequest in order to signal that you want to process an AVPersistableContentKeyRequest instead. If the underlying protocol supports persistable content keys, in response your delegate will receive an AVPersistableContentKeyRequest via -contentKeySession:didProvidePersistableContentKeyRequest:. NSInternalInconsistencyException will be raised, if you are attempting to create and use a persistable key but your AVContentKeySession delegate does not respond to contentKeySession:didProvidePersistableContentKeyRequest:.
/// 
/// - Parameter outError: The error returned if a persistable content key request cannot be requested.
/// 
/// - Returns: YES if sucessful. If NO, this request should be responded to via processContentKeyResponse: or processContentKeyResponseError:.
- (BOOL)respondByRequestingPersistableContentKeyRequestAndReturnError:(NSError **)outError API_AVAILABLE(macos(10.15), ios(11.2), tvos(17.0), watchos(7.0), visionos(1.0));

@end

/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.15), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0))
@interface AVPersistableContentKeyRequest : AVContentKeyRequest

/// Obtains a persistable content key from a context.
/// 
/// The data returned from this method may be used to immediately satisfy an AVPersistableContentKeyRequest, as well as any subsequent requests for the same key url using processContentKeyResponse: method. When you receive an AVContentKeyRequest via -contentKeySession:didProvideContentKeyRequest: and you want to use existing persistent content key from storage, you must invoke -respondByRequestingPersistableContentKeyRequest on that AVContentKeyRequest in order to signal that you want to process an AVPersistableContentKeyRequest instead. If the underlying protocol supports persistable content keys, in response your delegate will receive an AVPersistableContentKeyRequest via -contentKeySession:didProvidePersistableContentKeyRequest:. You can set the persistent key from storage on the AVPersistableContentKeyRequest using processContentKeyResponse:.
/// 
/// - Parameter keyVendorResponse: The response returned from the key vendor as a result of a request generated from makeStreamingContentKeyRequestDataForApp:contentIdentifier:options:completionHandler:.
/// - Parameter options: Additional information necessary to obtain the persistable content key, or nil if none.
/// - Parameter outError: If obtaining the persistable content key fails, will be set to an instance of NSError describing the failure.
/// 
/// - Returns: The persistable content key data that may be stored offline to answer future loading requests of the same content key.
- (nullable NSData *)persistableContentKeyFromKeyVendorResponse:(NSData *)keyVendorResponse
                                                        options:(nullable NSDictionary <NSString *, id> *)options
                                                          error:(NSError * _Nullable * _Nullable)outError;

@end

@interface AVContentKeyRequest (AVContentKeyRequestRenewal)

/// Indicates whether the receiver represents a request to renew previously provided response data that is expiring or has expired.
@property (readonly) BOOL renewsExpiringResponseData;

@end

@class AVContentKeyResponseInternal;

/// AVContentKeyResponse is used to represent the data returned from the key server when requesting a key for decrypting content.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0))
@interface AVContentKeyResponse : NSObject
{
@private
    AVContentKeyResponseInternal * _keyResponse;
}

/// Create an AVContentKeyResponse from the server response to a key request made when using FairPlayStreaming (FPS) as the method of key delivery.
/// 
/// The object created by this method is typically used with an AVContentKeyRequest created by an AVContentKeySession using keySystem AVContentKeySystemFairPlayStreaming. It is passed to AVContentKeyRequest -processContentKeyResponse: in order to supply the decryptor with key data
/// 
/// - Parameter keyResponseData: The response from the FairPlayStreaming key server
/// 
/// - Returns: A new AVContentKeyResponse holding data from a FairPlayStreaming key server that is used to decrypt the content
+ (instancetype)contentKeyResponseWithFairPlayStreamingKeyResponseData:(NSData *)keyResponseData;

/// Create an AVContentKeyResponse from the key and IV when using AVContentKeySystemClearKey as the key system
/// 
/// The object created by this method is typically used with an AVContentKeyRequest created by an AVContentKeySession using keySystem AVContentKeySystemClearKey. It is passed to AVContentKeyRequest -processContentKeyResponse: in order to supply the decryptor with key data.
/// 
/// - Parameter keyData: The key used for decrypting content.
/// - Parameter initializationVector: The initialization vector used for decrypting content, or nil if initialization vector is available in the media to be decrypted
/// 
/// - Returns: A new AVContentKeyResponse holding Clear Key data.
+ (instancetype)contentKeyResponseWithClearKeyData:(NSData *)keyData initializationVector:(nullable NSData *)initializationVector API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(7.0), visionos(1.0));

/// Create an AVContentKeyResponse from authorization token data when using AVContentKeySystemAuthorizationToken key system.
/// 
/// The object created by this method is typically used with an AVContentKeyRequest created by an AVContentKeySession using keySystem AVContentKeySystemAuthorizationToken. It is passed to AVContentKeyRequest -processContentKeyResponse: in order to supply the authorization token data.
/// 
/// - Parameter authorizationTokenData: Data blob containing the authorization token.
/// 
/// - Returns: A new AVContentKeyResponse holding the authorization token data.
+ (instancetype) contentKeyResponseWithAuthorizationTokenData:(NSData *)authorizationTokenData API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(7.0), visionos(1.0));

@end

/*
 Options keys for use with the following methods:
 -[AVContentKeySession processContentKeyRequestWithIdentifier:initializationData:options:]
 -[AVContentKeyRequest makeStreamingContentKeyRequestDataForApp:contentIdentifier:options:completionHandler:]
 */

/// Specifies the versions of the content protection protocol supported by the application as an NSArray of one or more NSNumber objects.
AVF_EXPORT NSString *const AVContentKeyRequestProtocolVersionsKey API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0));

/// Value is an Boolean indicating whether the user's deviceID contained in the SPC blob during FairPlay key exchange should be randomized using a system generated seed
/// 
/// Content providers use the SPC to distinguish the playback device from other devices, typically to enforce per-screen business rule limits.
/// If the app developer, in cooperation with the content vendor, does not require to distinguish the playback device, they can further enhance user
/// privacy by making this identifier non-constant, using this option.
/// In either case, apps are not allowed to store or use the FairPlay anonymized device ID for anything other than to enforce business rule limits.
/// App developers must use the AppTrackingTransparency framework to disclose to users if the application or the related FairPlay Key Server collect
/// data about end users and share it with other companies for purposes of tracking across apps and web sites.
/// When true, the system generates a random seed with which the device id will be randomized. To override the seed used; use this property in conjunction with AVContentKeyRequestRandomDeviceIdentifierSeedKey
/// to provide a seed generated by your application.
AVF_EXPORT NSString *const AVContentKeyRequestShouldRandomizeDeviceIdentifierKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Value is an NSData containing a 16-byte seed to randomize the user's deviceID contained in the SPC blob during FairPlay key exchange
/// 
/// This property must be used in conjunction with AVContentKeyRequestShouldRandomizeDeviceIdentifierKey. Use a RND function to generate a 16 byte seed.
/// This seed will be used to randomize the user's anonymized device ID if AVContentKeyRequestShouldRandomizeDeviceIdentifierKey is true.
/// Content providers use the SPC to distinguish the playback device from other devices, typically to enforce per-screen business rule limits.
/// If the app developer, in cooperation with the content vendor, does not require to distinguish the playback device, they can further enhance user
/// privacy by making this identifier non-constant, using this option.
/// In either case, apps are not allowed to store or use the FairPlay anonymized device ID for anything other than to enforce business rule limits.
/// App developers must use the AppTrackingTransparency framework to disclose to users if the application or the related FairPlay Key Server collect
/// data about end users and share it with other companies for purposes of tracking across apps and web sites.
AVF_EXPORT NSString *const AVContentKeyRequestRandomDeviceIdentifierSeedKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Classes of objects that may require decryption keys for media data in order to enable processing, such as parsing or playback, conform to this protocol.
API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(7.0), visionos(1.0))
@protocol AVContentKeyRecipient

@optional

/// Informs the receiver that an AVContentKey has been obtained as the result of an invocation of -[AVContentKeyRequest processContentKeyResponse:].
/// 
/// The recipient may employ the AVContentKey for use with objects that support manual attachment of keys, such as CMSampleBuffer via an invocation of AVSampleBufferAttachContentKey.
- (void)contentKeySession:(AVContentKeySession *)contentKeySession didProvideContentKey:(AVContentKey *)contentKey API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0));

@required

/// Indicates whether the receiver may require decryption keys for media data in order to enable processing.
/// 
/// When the value of mayRequireContentKeysForMediaDataProcessing is YES, adding the receiver to an AVContentKeySession allows it to employ the session's already existing keys and also enables the handling of new key requests by the AVContentKeySession's delegate.
@property (nonatomic, readonly) BOOL mayRequireContentKeysForMediaDataProcessing;

@end

/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0))
@interface AVContentKeySpecifier : NSObject

/// Creates a new instance of AVContentKeySpecifier.
/// 
/// This method returns an AVContentKeySpecifier instance that represents a content key in a specific content key system.
/// 
/// - Parameter keySystem: A valid key system for content keys.
/// - Parameter contentKeyIdentifier: Container and protocol-specific key identifier.
/// - Parameter options: Additional information necessary to obtain the key, can be empty if none needed.
/// 
/// - Returns: A new AVContentKeySpecifier
+ (instancetype)contentKeySpecifierForKeySystem:(AVContentKeySystem)keySystem identifier:(id)contentKeyIdentifier options:(NSDictionary<NSString *, id> *)options;

/// Initialize an instance of AVContentKeySpecifier.
/// 
/// This method returns an AVContentKeySpecifier instance that represents a content key in a specific content key system.
/// 
/// - Parameter keySystem: A valid key system for content keys.
/// - Parameter contentKeyIdentifier: Container and protocol-specific key identifier.
/// - Parameter options: Additional information necessary to obtain the key, can be empty if none needed.
/// 
/// - Returns: An instance of AVContentKeySpecifier
- (instancetype)initForKeySystem:(AVContentKeySystem)keySystem identifier:(id)contentKeyIdentifier options:(NSDictionary<NSString *, id> *)options;

/// A valid key system for content keys.
@property (readonly) AVContentKeySystem keySystem;

/// Container and protocol-specific key identifier.
@property (readonly) id NS_SWIFT_SENDABLE identifier;

/// Additional information necessary to obtain the key, can be empty if none needed.
@property (readonly) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE options;

@end

/// The constants can be used to derive whether or not we have established sufficient protection to display content protected by this AVContentKey on some set of attached displays.
typedef NS_ENUM(NSInteger, AVExternalContentProtectionStatus) {
	/// Indicates that the current protection status has not yet been discovered for the attached display(s).
	AVExternalContentProtectionStatusPending            = 0,
	/// Indicates that sufficient protection with the attached display(s) has been established, content protected by the associated AVContentKey will be eligible to be displayed on the display(s).
	AVExternalContentProtectionStatusSufficient         = 1,
	/// Indicates that sufficient protection with the attached display(s) has failed to be established, content protected by the associated AVContentKey will not be displayed.
	AVExternalContentProtectionStatusInsufficient       = 2,
} API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0))
@interface AVContentKey : NSObject

/// Specifies the content key.
@property  (readonly) AVContentKeySpecifier *contentKeySpecifier;

/// The external protection status for the AVContentKey based on all attached displays.
/// 
/// This property is not key-value observable, instead the contentKeySession:externalProtectionStatusDidChangeForContentKey: delegate method should be used.
@property  (readonly) AVExternalContentProtectionStatus externalContentProtectionStatus API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Revokes the decryption context of the content key, and removes it from its associated AVContentKeySession.
/// 
/// Once revoked, the AVContentKey is no longer eligible to be used with any media.
/// If the key is required again, or if the key is requested to be loaded by the application, a new AVContentKeyRequest will be dispatched to the delegate.
/// If there is media playback occurring which is dependent on the content key it will fail and may result in an error being generated with the playback halting.
- (void)revoke API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), watchos(10.4), visionos(1.1));
@end

/// Attaches an AVContentKey to a CMSampleBuffer for the purpose of content decryption.
/// 
/// The client is expected to attach AVContentKeys to CMSampleBuffers that have been created by the client for enqueueing with AVSampleBufferDisplayLayer or AVSampleBufferAudioRenderer, for which the AVContentKeySpecifier matches indications of suitability that are available to the client according to the content key system that's in use.
/// 
/// - Parameter sbuf: The sample buffer to which the content key is to be attached.
/// - Parameter contentKey: The content key to be attached.
/// - Parameter outError: If the result is NO and errorOut is non-NULL, the location referenced by errorOut receives an instance of NSError that describes the reason for failure to attach the content key.
AVF_EXPORT BOOL AVSampleBufferAttachContentKey(CMSampleBufferRef sbuf, AVContentKey *contentKey, NSError * _Nullable * _Nullable outError)
#if defined(__swift__)
API_DEPRECATED("Use CMReadySampleBuffer.attach(contentKey:) instead", macos(10.10, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), watchos(1.0, API_TO_BE_DEPRECATED), tvos(14.5, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED))
#else
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0))
#endif
;

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVContentKeySession.h>
#endif
