//
//  INSearchForMessagesIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INMessageAttributeOptions.h>

@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INMessageAttributeOptionsResolutionResult;
@class INPerson;
@class INPersonResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INSearchForMessagesIntent : INIntent

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
               speakableGroupNames:(nullable NSArray<INSpeakableString *> *)speakableGroupNames
           conversationIdentifiers:(nullable NSArray<NSString *> *)conversationIdentifiers NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14));

// Contact that received the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

// Describes how to combine the contents of the recipient array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator recipientsOperator;

// Sender of the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *senders;

// Describes how to combine the contents of the sender array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator sendersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *searchTerms;

// Describes how to combine the contents of the searchTerm array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator searchTermsOperator;

// Attributes of the message to be found.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageAttributeOptions attributes;

// Time range in which to search for the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateTimeRange;

// If available, the identifier of a particular message to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *identifiers;

// Describes how to combine the contents of the identifier array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator identifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *notificationIdentifiers;

// Describes how to combine the contents of the notificationIdentifier array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator notificationIdentifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *speakableGroupNames API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

// Describes how to combine the contents of the speakableGroupName array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator speakableGroupNamesOperator API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *conversationIdentifiers API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos);

// Describes how to combine the contents of the conversationIdentifier array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator conversationIdentifiersOperator API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos);

@end

@class INSearchForMessagesIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchForMessagesIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INSearchForMessagesIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchForMessagesIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchForMessagesIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForMessagesIntentResponse
 */

- (void)handleSearchForMessages:(INSearchForMessagesIntent *)intent
                     completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchForMessagesIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForMessagesIntentResponse
 */

- (void)confirmSearchForMessages:(INSearchForMessagesIntent *)intent
                      completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveRecipientsForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(for:with:));

- (void)resolveSendersForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveSenders(for:with:));

- (void)resolveAttributesForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(INMessageAttributeOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAttributes(for:with:));

- (void)resolveDateTimeRangeForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateTimeRange(for:with:));

- (void)resolveGroupNamesForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveGroupNames(for:with:)) API_DEPRECATED("resolveGroupNamesForSearchForMessages:withCompletion: is deprecated. Use resolveSpeakableGroupNamesForSearchForMessages:withCompletion: instead", ios(10.0, 11.0), watchos(3.2, 4.0)) API_UNAVAILABLE(macos);

- (void)resolveSpeakableGroupNamesForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INSpeakableStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveSpeakableGroupNames(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
