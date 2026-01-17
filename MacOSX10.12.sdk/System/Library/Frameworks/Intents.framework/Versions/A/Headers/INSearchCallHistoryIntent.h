//
//  INSearchCallHistoryIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallCapabilityOptions.h>
#import <Intents/INCallRecordType.h>

@class INCallRecordTypeResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSearchCallHistoryIntent : INIntent

- (instancetype)initWithCallType:(INCallRecordType)callType
                     dateCreated:(nullable INDateComponentsRange *)dateCreated
                       recipient:(nullable INPerson *)recipient
                callCapabilities:(INCallCapabilityOptions)callCapabilities NS_DESIGNATED_INITIALIZER;

// What type of call record to search for.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType callType;

// Date of the call to search for in the call history.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateCreated;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *recipient;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapabilityOptions callCapabilities;

@end

@class INSearchCallHistoryIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSearchCallHistoryIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INSearchCallHistoryIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSearchCallHistoryIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  searchCallHistoryIntent The input intent
 @param  completion The response handling block takes a INSearchCallHistoryIntentResponse containing the details of the result of having executed the intent

 @see  INSearchCallHistoryIntentResponse
 */

- (void)handleSearchCallHistory:(INSearchCallHistoryIntent *)intent
                     completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(handle(searchCallHistory:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  searchCallHistoryIntent The input intent
 @param  completion The response block contains an INSearchCallHistoryIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchCallHistoryIntentResponse

 */

- (void)confirmSearchCallHistory:(INSearchCallHistoryIntent *)intent
                      completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(confirm(searchCallHistory:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  searchCallHistoryIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveCallTypeForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                             withCompletion:(void (^)(INCallRecordTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCallType(forSearchCallHistory:with:));

- (void)resolveDateCreatedForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                                withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(forSearchCallHistory:with:));

- (void)resolveRecipientForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                              withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRecipient(forSearchCallHistory:with:));

@end

NS_ASSUME_NONNULL_END
