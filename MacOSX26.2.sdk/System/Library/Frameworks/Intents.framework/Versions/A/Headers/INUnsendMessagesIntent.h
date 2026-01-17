//
//  INUnsendMessagesIntent.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0))
API_UNAVAILABLE(tvos)
@interface INUnsendMessagesIntent : INIntent

- (instancetype)initWithMessageIdentifiers:(nullable NSArray<NSString *> *)messageIdentifiers NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *messageIdentifiers;

@end

@class INUnsendMessagesIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INUnsendMessagesIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0))
API_UNAVAILABLE(tvos)
@protocol INUnsendMessagesIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INUnsendMessagesIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INUnsendMessagesIntentResponse containing the details of the result of having executed the intent

 @see  INUnsendMessagesIntentResponse
 */

- (void)handleUnsendMessages:(INUnsendMessagesIntent *)intent
                  completion:(void (^)(INUnsendMessagesIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INUnsendMessagesIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INUnsendMessagesIntentResponse
 */

- (void)confirmUnsendMessages:(INUnsendMessagesIntent *)intent
                   completion:(void (^)(INUnsendMessagesIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

@end

NS_ASSUME_NONNULL_END
