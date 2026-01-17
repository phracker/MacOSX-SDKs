//
//  INAppendToNoteIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INNote;
@class INNoteContent;
@class INNoteContentResolutionResult;
@class INNoteResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INAppendToNoteIntent : INIntent

- (instancetype)initWithTargetNote:(nullable INNote *)targetNote
                           content:(nullable INNoteContent *)content NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INNote *targetNote;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INNoteContent *content;

@end

@class INAppendToNoteIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INAppendToNoteIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INAppendToNoteIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INAppendToNoteIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INAppendToNoteIntentResponse containing the details of the result of having executed the intent

 @see  INAppendToNoteIntentResponse
 */

- (void)handleAppendToNote:(INAppendToNoteIntent *)intent
                completion:(void (^)(INAppendToNoteIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INAppendToNoteIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INAppendToNoteIntentResponse
 */

- (void)confirmAppendToNote:(INAppendToNoteIntent *)intent
                 completion:(void (^)(INAppendToNoteIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTargetNoteForAppendToNote:(INAppendToNoteIntent *)intent
                    withCompletion:(void (^)(INNoteResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTargetNote(for:with:));

- (void)resolveContentForAppendToNote:(INAppendToNoteIntent *)intent
                    withCompletion:(void (^)(INNoteContentResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(for:with:));

@end

NS_ASSUME_NONNULL_END
