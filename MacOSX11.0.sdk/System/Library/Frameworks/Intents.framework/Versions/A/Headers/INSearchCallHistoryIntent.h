//
//  INSearchCallHistoryIntent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallCapabilityOptions.h>
#import <Intents/INCallRecordType.h>
#import <Intents/INCallRecordTypeOptions.h>

@class INBooleanResolutionResult;
@class INCallRecordTypeOptionsResolutionResult;
@class INCallRecordTypeResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INSearchCallHistoryIntent : INIntent

- (instancetype)initWithDateCreated:(nullable INDateComponentsRange *)dateCreated
                          recipient:(nullable INPerson *)recipient
                   callCapabilities:(INCallCapabilityOptions)callCapabilities
                          callTypes:(INCallRecordTypeOptions)callTypes
                             unseen:(nullable NSNumber *)unseen NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Date of the call to search for in the call history.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateCreated;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *recipient;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapabilityOptions callCapabilities;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordTypeOptions callTypes API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *unseen NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

@end

@class INSearchCallHistoryIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchCallHistoryIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INSearchCallHistoryIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchCallHistoryIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchCallHistoryIntentResponse containing the details of the result of having executed the intent

 @see  INSearchCallHistoryIntentResponse
 */

- (void)handleSearchCallHistory:(INSearchCallHistoryIntent *)intent
                     completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchCallHistoryIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchCallHistoryIntentResponse
 */

- (void)confirmSearchCallHistory:(INSearchCallHistoryIntent *)intent
                      completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveCallTypeForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INCallRecordTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCallType(for:with:)) API_DEPRECATED("resolveCallTypeForSearchCallHistory:withCompletion: is deprecated. Use resolveCallTypesForSearchCallHistory:withCompletion: instead", ios(10.0, 11.0), watchos(3.2, 4.0)) API_UNAVAILABLE(macos);

- (void)resolveDateCreatedForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(for:with:));

- (void)resolveRecipientForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRecipient(for:with:));

- (void)resolveCallTypesForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INCallRecordTypeOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCallTypes(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

- (void)resolveUnseenForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveUnseen(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
