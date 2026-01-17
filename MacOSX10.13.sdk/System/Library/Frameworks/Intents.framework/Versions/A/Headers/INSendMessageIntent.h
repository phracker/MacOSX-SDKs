//
//  INSendMessageIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;
@class INSendMessageRecipientResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INSendMessageIntent : INIntent

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           content:(nullable NSString *)content
                speakableGroupName:(nullable INSpeakableString *)speakableGroupName
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Contacts to whom the message should be sent.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

// Body text of the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *speakableGroupName API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *conversationIdentifier API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Specified service for the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *serviceName;

// The person, or account, sending the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *sender;

@end

@class INSendMessageIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSendMessageIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
@protocol INSendMessageIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSendMessageIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSendMessageIntentResponse containing the details of the result of having executed the intent

 @see  INSendMessageIntentResponse
 */

- (void)handleSendMessage:(INSendMessageIntent *)intent
               completion:(void (^)(INSendMessageIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSendMessageIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSendMessageIntentResponse
 */

- (void)confirmSendMessage:(INSendMessageIntent *)intent
                completion:(void (^)(INSendMessageIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveRecipientsForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(for:with:)) API_DEPRECATED("resolveRecipientsForSendMessage:withCompletion: is deprecated. Use resolveRecipientsForSendMessage:completion: instead", ios(10.0, 11.0), watchos(3.2, 4.0));

- (void)resolveRecipientsForSendMessage:(INSendMessageIntent *)intent
                    completion:(void (^)(NSArray<INSendMessageRecipientResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)resolveGroupNameForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGroupName(for:with:)) API_DEPRECATED("resolveGroupNameForSendMessage:withCompletion: is deprecated. Use resolveSpeakableGroupNameForSendMessage:withCompletion: instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

- (void)resolveContentForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(for:with:));

- (void)resolveSpeakableGroupNameForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSpeakableGroupName(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
