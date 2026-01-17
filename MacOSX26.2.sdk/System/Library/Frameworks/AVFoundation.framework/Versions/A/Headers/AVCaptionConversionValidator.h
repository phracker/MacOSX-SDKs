#if !__has_include(<AVFCore/AVCaptionConversionValidator.h>)
/*
    File:  AVCaptionConversionValidator.h
 
    Framework:  AVFoundation
 
	Copyright 2017-2023 Apple Inc. All rights reserved.
 
*/

#import <AVFoundation/AVBase.h>
#if ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#import <AVFoundation/AVCaption.h>
#import <AVFoundation/AVCaptionSettings.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptionConversionWarning;

/*!
 @enum AVCaptionConversionValidatorStatus
 @abstract
	These constants are returned by the AVCaptionConversionValidator status property to indicate the progress of a validation operation.
 
 @constant	 AVCaptionConversionValidatorStatusUnknown
	Indicates that the validation operation has not yet been initiated.
 @constant	 AVCaptionConversionValidatorStatusValidating
	Indicates that the validation operation is currently in progress.
 @constant	 AVCaptionConversionValidatorStatusCompleted
	Indicates that the validation operation has been completed.
 @constant	 AVCaptionConversionValidatorStatusStopped
	Indicates that the validation operation was stopped prior to completion.
*/
typedef NS_ENUM(NSInteger, AVCaptionConversionValidatorStatus) {
	AVCaptionConversionValidatorStatusUnknown = 0,
    AVCaptionConversionValidatorStatusValidating = 1,
    AVCaptionConversionValidatorStatusCompleted = 2,
    AVCaptionConversionValidatorStatusStopped = 3
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @class         AVCaptionConversionValidator
 @abstract      Performs a validation of captions for a conversion operation and warns about problems that are encountered.
*/
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface AVCaptionConversionValidator : NSObject
AV_INIT_UNAVAILABLE

/*!
 @method        captionConversionValidatorWithCaptions:startTime:conversionSettings:
 @abstract      Returns an instance of AVCaptionConversionValidator that can validate an array of captions for a specific conversion operation and warn about problems that are encountered.
 @param         captions
				The array of captions to be validated.
 @param         timeRange
                The timeRange of the media timeline into which the specified captions must be integrated. See the timeRange property for further details.
 @param         conversionSettings
                Describes the conversion operation for which the captions are to be validated.
 @result        A new instance of AVCaptionConversionValidator configured to perform the specified validation.
 @discussion    This method throws an exception if the conversion setting's AVCaptionMediaTypeKey is not equal to AVMediaTypeClosedCaption, or if its AVCaptionMediaSubTypeKey is not equal to kCMClosedCaptionFormatType_CEA608.
*/
+ (instancetype)captionConversionValidatorWithCaptions:(NSArray<AVCaption *> *)captions timeRange:(CMTimeRange)timeRange conversionSettings:(NSDictionary<AVCaptionSettingsKey, id> *)conversionSettings;

/*!
 @method        initWithCaptions:startTime:conversionSettings:
 @abstract      Returns an instance of AVCaptionConversionValidator that can validate an array of captions for a specific conversion operation and warn about problems that are encountered.
 @param         captions
				The array of captions for which the validation is requested.
 @param         timeRange
				The timeRange of the media timeline into which the specified captions must be integrated. See the timeRange property for further details.
 @param         conversionSettings
				Describes the conversion operation for which the captions are to be validated.
 @result        A new instance of AVCaptionConversionValidator configured to perform the specified validation.
*/
- (instancetype)initWithCaptions:(NSArray<AVCaption *> *)captions timeRange:(CMTimeRange)timeRange conversionSettings:(NSDictionary<AVCaptionSettingsKey, id> *)conversionSettings;

/*!
 @property      status
 @abstract      Indicates the status of the validation.
*/
@property (readonly) AVCaptionConversionValidatorStatus status;

/*!
 @property      captions
 @abstract      The array of captions to be validated for the specified conversion operation.
*/
@property (readonly) NSArray<AVCaption *> *captions;

/*!
 @property      timeRange
 @abstract      The timeRange of the media timeline into which the specified captions must be integrated.
 @discussion
   The start of this timeRange may be less than the start of the timeRange of the initial caption in the captions array, if the captions are to appear only after the start of accompanying video or audio. If no definite duration for the media timeline is known, the timeRange can have a duration of kCMTimePositiveInfinity. However, in order to perform a comprehensive validation of a conversion to closed captions, setting the duration of the timeRange to the duration of accompanying video media is recommended.
*/
@property (readonly) CMTimeRange timeRange;

/*!
 @method        validateCaptionConversionWithWarningHandler:
 @abstract      Initiates the specified validation and changes the value of status to AVCaptionConversionValidatorStatusValidating.
 @param         handler
                Specifies a block to be executed in order to warn you of a specific problem.
 @discussion
   It is an error to invoke this method when the value of status is greater than AVCaptionConversionValidatorStatusUnknown.
   If you wish to stop a validation operation in progress before it has been completed, send the message stopValidating to the receiver.
   When the validation is complete and all warnings have been reported, the block will be executed once with a value of nil for its warning parameter. When this occurs, the value of status will have been changed to AVCaptionConversionValidatorStatusCompleted.
*/
- (void)validateCaptionConversionWithWarningHandler:(void (^ NS_SWIFT_SENDABLE)(AVCaptionConversionWarning * _Nullable warning))handler;

/*!
 @method        stopValidating
 @abstract      Stops validation and changes the value of status to AVCaptionConversionValidatorStatusStopped.
 @discussion
   You can call this method at any time, even within your warning handler.
*/
- (void)stopValidating;

/*!
 @property      warnings
 @abstract      Provides the collection of warnings for problems that have been encountered. While the value of status is AVCaptionConversionValidatorStatusValidating, the count of warnings may increase.
*/
@property (readonly) NSArray<AVCaptionConversionWarning *> *warnings;

@end

@class AVCaptionConversionAdjustment;

/*!
 @typedef       AVCaptionConversionWarningType
 @abstract      The type of a caption conversion warning.
*/
typedef NSString *AVCaptionConversionWarningType NS_TYPED_ENUM API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @constant      AVCaptionConversionWarningTypeExcessMediaData
 @abstract      Indicates that one or more captions in the validator's captions array exceed the capacity for media data of the media type and subtype specified by the conversion settings.
*/
AVF_EXPORT AVCaptionConversionWarningType const AVCaptionConversionWarningTypeExcessMediaData API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @class         AVCaptionConversionWarning
 @abstract      Reports a specific problem encountered during the validation of a caption conversion.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface AVCaptionConversionWarning : NSObject
AV_INIT_UNAVAILABLE

/*!
 @property      warningType
 @abstract      Indicates the type of warning provided by the receiver.
*/
@property (readonly) AVCaptionConversionWarningType warningType;

/*!
 @property      rangeOfCaptions
 @abstract      Indicates the range of captions in the validator's captions array for which the specified warning has been issued.
 @discussion    Only captions with the same start time and duration will be referenced. If captions with different start times and durations exhibit similar problems, a separate instance of AVCaptionConversionWarning will be used to indicate each problematic case. If the referenced captions have multiple problems, a separate instance of AVCaptionConversionWarning will be issued to indicate each problem.
*/
@property (readonly) NSRange rangeOfCaptions;

/*!
 @property      adjustment
 @abstract      Indicates an adjustment to the indicated captions that can be applied in order to correct the problem.
 @discussion    If the value of adjustment is not nil and the conversion operation is performed without correcting the problem, the adjustment will be applied during conversion. If the value of adjustment is nil and the conversion operation is performed without correcting the problem, the indicated captions will be omitted from the output media data.
*/
@property (readonly, nullable) AVCaptionConversionAdjustment *adjustment;

@end

/*!
 @typedef       AVCaptionConversionAdjustmentType
 @abstract      The type of a caption conversion adjustment.
*/
typedef NSString *AVCaptionConversionAdjustmentType NS_TYPED_ENUM API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @constant      AVCaptionConversionAdjustmentTypeTimeRange
 @abstract      Indicates a timing adjustment.
*/
AVF_EXPORT AVCaptionConversionAdjustmentType const AVCaptionConversionAdjustmentTypeTimeRange API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @class         AVCaptionConversionAdjustment
 @abstract      Describes an adjustment that can be performed in order to correct a problem encountered during the validation of a caption conversion.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface AVCaptionConversionAdjustment : NSObject
AV_INIT_UNAVAILABLE

/*!
 @property      adjustmentType
 @abstract      Indicates the type of adjustment described by the receiver.
*/
@property (readonly) AVCaptionConversionAdjustmentType adjustmentType;

@end

/*!
 @class         AVCaptionConversionTimeRangeAdjustment
 @abstract      Describes an adjustment to the timeRange of one or more captions.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface AVCaptionConversionTimeRangeAdjustment : AVCaptionConversionAdjustment
AV_INIT_UNAVAILABLE

/*!
 @property      startTimeOffset
 @abstract      Indicates the amount by which the timeRange.start of the captions must be adjusted in order to correct a problem.
 @discussion    The value may any numeric value, positive, negative, or zero.
*/
@property (readonly) CMTime startTimeOffset;

/*!
 @property      durationOffset
 @abstract      Indicates the amount by which the timeRange.duration of the captions must be adjusted in order to correct a problem.
 @discussion    The value may any numeric value, positive, negative, or zero.
*/
@property (readonly) CMTime durationOffset;

@end

NS_ASSUME_NONNULL_END

#endif // ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#else
#import <AVFCore/AVCaptionConversionValidator.h>
#endif
