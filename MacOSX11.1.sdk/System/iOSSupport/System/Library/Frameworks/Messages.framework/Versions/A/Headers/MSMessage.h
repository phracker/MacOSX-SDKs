/*!
 @header     MSMessage
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

@class MSMessageLayout, MSSession;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MSMessage
 @abstract   The MSMessage encapsulates the data to be transferred to remote devices.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSMessage : NSObject <NSCopying, NSSecureCoding>

/*!
 @method     init
 @abstract   Initializes a new message that is not part of a session.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @method     initWithSession:
 @abstract   Initializes a message with a session.
 @see        insertMessage:completionHandler:
 @param      session  The session that new message will join.
 @discussion A message initialized with a session will be updated 
 and moved to the bottom of the conversation transcript when another message created
 with the same session is sent.
 */
- (instancetype)initWithSession:(MSSession *)session NS_DESIGNATED_INITIALIZER;

/*!
 @property   session
 @abstract   An MSSession that identifies the session that message belongs to.
 */
@property (nonatomic, readonly, nullable) MSSession *session;

/*!
 @property   pending
 @abstract   A BOOL representing whether the message is a pending message or is a message that has been sent/received.
 @discussion This value starts as `YES` when creating an `MSMessage` for sending. After calling `-[MSConversation insertMessage:completionHandler:]`, `isPending` still returns `YES` until `-[MSMessagesAppViewController didStartSendingMessage:conversation]` is called. This property is useful for knowing if the `selectedMessage` of `-[MSMessagesAppViewController activeConversation]` represents an unsent message.
 */
@property (nonatomic, readonly, getter=isPending) BOOL pending NS_AVAILABLE_IOS(11_0);

/*!
 @property   senderParticipantIdentifier
 @abstract   A NSUUID instance that identifies the participant that sent the message.
 @discussion This NSUUID identifies the message's sender. This value is scoped to
 the current device and will be different on all devices that participate in the
 conversation.
 */
@property (nonatomic, readonly) NSUUID *senderParticipantIdentifier;

/*!
 @property   layout
 @abstract   A subclass of MSMessageLayout.
 @discussion The MSMessageLayout subclass will be used to construct UI
 representing the message in the conversation transcript.
 */
@property (nonatomic, copy, nullable) MSMessageLayout *layout;

/*!
 @property   URL
 @abstract   A HTTP(S) or data URL used to encode data to be transferred in message.
 @discussion This URL should encode any data that is to be delivered to the extension running
 on the recipient's device(s). When no app exists on the receiving device that
 can consume the message, if this URL is a HTTP(S) url, it will be loaded in a web browser.
 */
@property (nonatomic, copy, nullable) NSURL *URL;

/*!
 @property   shouldExpire
 @abstract   A Boolean value that indicates whether the messages should expire after being read.
 @discussion YES if the message should expire after it is read. Expired messages will
 be deleted a short time after being read by the receiver. The user may opt to keep the message.
 This property defaults to NO.
 */
@property (nonatomic, assign) BOOL shouldExpire;

/*!
 @property   accessibilityLabel
 @abstract   A localized string describing the message.
 @discussion This string should provide a succinct description of the message. This
 will be used by the Accessibility Speech feature when speaking the message for users
 with disabilities.
 */
@property (nonatomic, copy, nullable) NSString *accessibilityLabel;

/*!
 @property   summaryText
 @abstract   A localized string describing the message.
 @discussion This string should provide a succinct description of the message. This
 will be used to provide a summary of the message in the UI.
 */
@property (nonatomic, copy, nullable) NSString *summaryText;

/*!
 @property   error
 @abstract   An error object that indicates why a message failed to send.
 @discussion This value is nil if the message is has not yet been sent, is still
 sending or has been sent successfully.
 */
@property (nonatomic, copy, nullable) NSError *error;

@end

NS_ASSUME_NONNULL_END
