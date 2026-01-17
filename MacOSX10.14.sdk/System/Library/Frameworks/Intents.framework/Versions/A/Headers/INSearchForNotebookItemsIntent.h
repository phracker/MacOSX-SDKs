//
//  INSearchForNotebookItemsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INDateSearchType.h>
#import <Intents/INLocationSearchType.h>
#import <Intents/INNotebookItemType.h>
#import <Intents/INTaskStatus.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INDateSearchTypeResolutionResult;
@class INLocationSearchTypeResolutionResult;
@class INNotebookItemTypeResolutionResult;
@class INPlacemarkResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INStringResolutionResult;
@class INTaskStatusResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSearchForNotebookItemsIntent : INIntent

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                      content:(nullable NSString *)content
                     itemType:(INNotebookItemType)itemType
                       status:(INTaskStatus)status
                     location:(nullable CLPlacemark *)location
           locationSearchType:(INLocationSearchType)locationSearchType
                     dateTime:(nullable INDateComponentsRange *)dateTime
               dateSearchType:(INDateSearchType)dateSearchType
       notebookItemIdentifier:(nullable NSString *)notebookItemIdentifier NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.2), watchos(4.2));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INNotebookItemType itemType;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *location;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INLocationSearchType locationSearchType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateTime;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INDateSearchType dateSearchType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *notebookItemIdentifier API_AVAILABLE(ios(11.2), watchos(4.2));

@end

@class INSearchForNotebookItemsIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchForNotebookItemsIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INSearchForNotebookItemsIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchForNotebookItemsIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchForNotebookItemsIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForNotebookItemsIntentResponse
 */

- (void)handleSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                          completion:(void (^)(INSearchForNotebookItemsIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchForNotebookItemsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForNotebookItemsIntentResponse
 */

- (void)confirmSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                           completion:(void (^)(INSearchForNotebookItemsIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTitleForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTitle(for:with:));

- (void)resolveContentForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(for:with:));

- (void)resolveItemTypeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INNotebookItemTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveItemType(for:with:));

- (void)resolveStatusForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INTaskStatusResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStatus(for:with:));

- (void)resolveLocationForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocation(for:with:));

- (void)resolveLocationSearchTypeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INLocationSearchTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocationSearchType(for:with:));

- (void)resolveDateTimeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateTime(for:with:));

- (void)resolveDateSearchTypeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INDateSearchTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateSearchType(for:with:));

@end

NS_ASSUME_NONNULL_END
