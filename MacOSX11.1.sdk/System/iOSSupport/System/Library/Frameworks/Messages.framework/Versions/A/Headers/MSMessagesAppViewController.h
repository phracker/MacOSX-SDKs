/*!
 @header     MSMessagesAppViewController
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

@class MSConversation, MSMessage;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum       MSMessagesAppPresentationStyle
 @abstract   Describes how the extension is presented in Messages.
 @constant   MSMessagesAppPresentationStyleCompact     The extension's UI is presented compact in the keyboard area.
 @constant   MSMessagesAppPresentationStyleExpanded   The extension's UI is presented expanded taking up most of the screen.
 @constant   MSMessagesAppPresentationStyleTranscript   The extension's UI is presented in the transcript of the conversation in Messages.
 */
typedef NS_ENUM(NSUInteger, MSMessagesAppPresentationStyle) {
    MSMessagesAppPresentationStyleCompact,
    MSMessagesAppPresentationStyleExpanded,
    MSMessagesAppPresentationStyleTranscript NS_ENUM_AVAILABLE_IOS(11_0),
} NS_ENUM_AVAILABLE_IOS(10_0);


/*!
 @enum       MSMessagesAppPresentationContext
 @abstract   Describes the context for which the extension was launched
 @constant   MSMessagesAppPresentationContextMessages   The extension was launched for presentation in Messages
 @constant   MSMessagesAppPresentationContextMedia      The extension was launched for presentation over media content, such as a photo or camera feed
 */
typedef NS_ENUM(NSUInteger, MSMessagesAppPresentationContext) {
    MSMessagesAppPresentationContextMessages,
    MSMessagesAppPresentationContextMedia,
} NS_ENUM_AVAILABLE_IOS(12_0);


NS_AVAILABLE_IOS(11_0)
@protocol MSMessagesAppTranscriptPresentation

/*!
 @method     contentSizeThatFits:
 @abstract   The content size of the view controller's view fitting the constraining size.
 @discussion This method will only be called if the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 @param      size    The maximum size the view will be displayed at.
 */
- (CGSize)contentSizeThatFits:(CGSize)size NS_AVAILABLE_IOS(11_0);

@end


NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSMessagesAppViewController : UIViewController <MSMessagesAppTranscriptPresentation>

/*!
 @property   activeConversation
 @abstract   Current active conversation.
 */
@property (nonatomic, strong, readonly, nullable) MSConversation *activeConversation;

/*!
 @property   presentationStyle
 @abstract   Get the presentation extension's current presentation style.
 */
@property (nonatomic, assign, readonly) MSMessagesAppPresentationStyle presentationStyle;

/*!
 @property   presentationContext
 @abstract   The context for which the extension was launched
 */
@property (nonatomic, readonly) MSMessagesAppPresentationContext presentationContext NS_AVAILABLE_IOS(12_0);

/*!
 @method     requestPresentationStyle:
 @abstract   Requests that Messages transition the extension to the specified presentation style.
 @discussion When the current `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`, a new instance of `MSMessagesAppViewController` will be instantiated with the requested presentation style if needed.
 @param      presentationStyle   The presentation style to transition to. `MSMessagesAppPresentationStyleTranscript` is not a valid presentation style to request.
 */
- (void)requestPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle;

/*!
 @method     willBecomeActiveWithConversation:
 @abstract   Called when the extension is about to become active.
 @param      conversation   The current conversation.
 */
- (void)willBecomeActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     didBecomeActiveWithConversation:
 @abstract   Called when the extension has become active.
 @param      conversation   The current conversation.
 */
- (void)didBecomeActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     willResignActiveWithConversation:
 @abstract   Called when the extension will resign active.
 @param      conversation   The current conversation.
 */
- (void)willResignActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     didResignActiveWithConversation:
 @abstract   Called when the extension has resigned active.
 @param      conversation   The current conversation.
 */
- (void)didResignActiveWithConversation:(MSConversation *)conversation;

@end


@interface MSMessagesAppViewController (CompactOrExpandedPresentation)

/*!
 @method     dismiss
 @abstract   Tells Messages to dismiss the extension and present the keyboard.
 @discussion Calling this method does nothing when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 */
- (void)dismiss NS_AVAILABLE_IOS(10_0);

/*!
 @method     willSelectMessage:conversation:
 @abstract   Informs the extension that a new message will be selected in the conversation.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message selected.
 @param      conversation    The conversation.
 */
- (void)willSelectMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didSelectMessage:conversation:
 @abstract   Informs the extension that a new message has been selected in the conversation.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message selected.
 @param      conversation    The conversation.
 */
- (void)didSelectMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didReceiveMessage:conversation:
 @abstract   Informs the extension that a new message has arrived.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message received.
 @param      conversation    The conversation.
 */
- (void)didReceiveMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didStartSendingMessage:conversation:
 @abstract   Informs the extension that the message send has been triggered.
 @discussion This is called when a user interaction with Messages start the message send process. It does not guarantee the message will be successfully sent or delivered. This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message being sent.
 @param      conversation    The conversation the message belongs to.
 */
- (void)didStartSendingMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didCancelSendingMessage:conversation:
 @abstract   Informs the extension that the user has removed the message from the input field.
 @discussion This method will not be called when the `presentationStyle` is MSMessagesAppPresentationStyleTranscript or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message sent.
 @param      conversation    The conversation.
 */
- (void)didCancelSendingMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     willTransitionToPresentationStyle:
 @abstract   Called when the extension is about to transition to a new presentation style.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 @param      presentationStyle   The new presentation style.
 */
- (void)willTransitionToPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle NS_AVAILABLE_IOS(10_0);

/*!
 @method     didTransitionToPresentationStyle:
 @abstract   Called when the extension finished transitioning to a presentation style.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 @param      presentationStyle   The new presentation style.
 */
- (void)didTransitionToPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle NS_AVAILABLE_IOS(10_0);

@end


NS_ASSUME_NONNULL_END


