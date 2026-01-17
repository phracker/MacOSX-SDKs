/*!
 @header     MSConversation
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSSticker;
@class MSMessage;

NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSConversation : NSObject

/*!
 @property   localParticipantIdentifier
 @abstract   A NSUUID that identifies conversation participant on this device.
 @discussion This NSUUID  that identifies conversation participant on this device,
 this value will be stable while the extension is enabled. If the extension is
 disabled and re-enabled or the containing App is removed and re-installed this
 value will change.
 */
@property (nonatomic, readonly) NSUUID *localParticipantIdentifier;

/*!
 @property   remoteParticipantIdentifiers
 @abstract   A NSArray of NSUUID instances, each uniquely identifies a remote participant in the conversation.
 @discussion Each NSUUID identifies the a remote participant in the conversation scoped to
 this device. These values will be stable while the extension is enabled. If the extension
 is disabled and re-enabled or the containing App is removed and re-installed these
 values will change.
 */
@property (nonatomic, readonly) NSArray<NSUUID *> *remoteParticipantIdentifiers;

/*!
 @property   selectedMessage
 @abstract   An MSMessage instance that may be edited and returned to Messages
 @discussion If the extension has been invoked in response to the user interacting with
 a message in the conversation transcript this property will contain the message.
 Otherwise this property will be nil. The message object provided may be saved to the
 file system. Later, this saved object may be loaded, modified and staged for sending.
 */
@property (nonatomic, readonly, nullable) MSMessage *selectedMessage;

/*!
 @method     insertMessage:completionHandler:
 @abstract   Stages the provided MSMessage object for sending.
 @discussion This method inserts a MSMessage object into the Messages input field,
 Subsequent calls to this method will replace any existing message on the input field. 
 If the message was successfully inserted on the input field, the completion handler
 will be called with a nil error parameter otherwise the error parameter will be
 populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      message            The MSMessage instance describing the message to be sent.
 @param      completionHandler  A completion handler called when the message has been staged or if there was an error.
 */
- (void)insertMessage:(MSMessage *)message completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     insertSticker:completionHandler:
 @abstract   The sticker is inserted into the Messages.app input field.
 @param      sticker            The sticker to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)insertSticker:(MSSticker *)sticker completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     insertText:completionHandler:
 @abstract   The NSString instance provided in the text parameter is inserted into the Messages.app input field.
 @discussion Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      text               The text to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)insertText:(NSString *)text completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     insertAttachment:withAlternateFilename:completionHandler:
 @abstract   The NSURL instance provided in the URL parameter is inserted into the Messages.app
 input field. This must be a file URL.
 @discussion Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext` if the attachment type is not an image type supported by `MSSticker`.
 @param      URL                The URL to the media file to be inserted.
 @param      filename           If you supply a string here, the message UI uses it for the attachment. Use an alternate filename to better describe the attachment or to make the name more readable.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)insertAttachment:(NSURL *)URL withAlternateFilename:(nullable NSString *)filename completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     sendMessage:completionHandler:
 @abstract   Start sending a message
 @discussion This method begins sending the provided MSMessage. The app must be visible and have had a recent touch interaction since either last launch or last send to succeed. If the message started sending successfully, the completion handler will be called with a nil error parameter. Otherwise the error parameter will be populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      message            The MSMessage instance describing the message to be sent.
 @param      completionHandler  A completion handler called when the message has been staged or if there was an error.
 */
- (void)sendMessage:(MSMessage *)message completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

/*!
 @method     sendSticker:completionHandler:
 @abstract   Start sending a sticker
 @discussion Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      sticker            The sticker to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)sendSticker:(MSSticker *)sticker completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

/*!
 @method     sendText:completionHandler:
 @abstract   Start sending text
 @discussion This method begins sending the provided NSString. The app must be visible and have had a recent touch interaction since either last launch or last send to succeed. If the message started sending successfully, the completion handler will be called with a nil error parameter. Otherwise the error parameter will be populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      text               The text to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)sendText:(NSString *)text completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

/*!
 @method     sendAttachment:withAlternateFilename:completionHandler:
 @abstract   Start sending a file located at the provided URL. This must be a file URL.
 @discussion This method begins sending the file at the provided file URL. The app must be visible and have had a recent touch interaction since either last launch or last send to succeed. If the message started sending successfully, the completion handler will be called with a nil error parameter. Otherwise the error parameter will be populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      URL                The URL to the media file to be inserted.
 @param      filename           If you supply a string here, the message UI uses it for the attachment. Use an alternate filename to better describe the attachment or to make the name more readable.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)sendAttachment:(NSURL *)URL withAlternateFilename:(nullable NSString *)filename completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

@end

NS_ASSUME_NONNULL_END
