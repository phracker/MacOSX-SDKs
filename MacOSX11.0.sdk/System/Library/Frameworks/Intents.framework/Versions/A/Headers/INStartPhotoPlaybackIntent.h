//
//  INStartPhotoPlaybackIntent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INPhotoAttributeOptions.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;
@class INPlacemarkResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INStartPhotoPlaybackIntent : INIntent

- (instancetype)initWithDateCreated:(nullable INDateComponentsRange *)dateCreated
                    locationCreated:(nullable CLPlacemark *)locationCreated
                          albumName:(nullable NSString *)albumName
                        searchTerms:(nullable NSArray<NSString *> *)searchTerms
                 includedAttributes:(INPhotoAttributeOptions)includedAttributes
                 excludedAttributes:(INPhotoAttributeOptions)excludedAttributes
                      peopleInPhoto:(nullable NSArray<INPerson *> *)peopleInPhoto NS_DESIGNATED_INITIALIZER;

// Include photos created in the specified date interval.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateCreated;

// Include photos taken at the specified location.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *locationCreated;

// Include photos contained in albums matching this name.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *albumName;

// Include photos with keywords, names, descriptions, etc. that match these search terms.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *searchTerms;

// Describes how to combine the contents of the searchTerm array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator searchTermsOperator;

// When specified, only match photos of the given types.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPhotoAttributeOptions includedAttributes;

// When specified, do not match photos of the given types.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPhotoAttributeOptions excludedAttributes;

// INPerson objects that should be present in the included photos, dependent on the peopleInPhotoOperator.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *peopleInPhoto;

// Describes how to combine the contents of the peopleInPhoto array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator peopleInPhotoOperator;

@end

@class INStartPhotoPlaybackIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INStartPhotoPlaybackIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INStartPhotoPlaybackIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INStartPhotoPlaybackIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INStartPhotoPlaybackIntentResponse containing the details of the result of having executed the intent

 @see  INStartPhotoPlaybackIntentResponse
 */

- (void)handleStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                      completion:(void (^)(INStartPhotoPlaybackIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INStartPhotoPlaybackIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartPhotoPlaybackIntentResponse
 */

- (void)confirmStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                       completion:(void (^)(INStartPhotoPlaybackIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveDateCreatedForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(for:with:));

- (void)resolveLocationCreatedForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocationCreated(for:with:));

- (void)resolveAlbumNameForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAlbumName(for:with:));

- (void)resolvePeopleInPhotoForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolvePeopleInPhoto(for:with:));

@end

NS_ASSUME_NONNULL_END
