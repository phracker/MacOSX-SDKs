#if !__has_include(<AVFCapture/AVCaptureSlider.h>)
/*
    File:  AVCaptureSlider.h
 
    Framework:  AVFoundation
 
    Copyright 2024 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureControl.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVCaptureSlider
 @abstract
    An `AVCaptureControl` for selecting a value from a bounded range of values.
 
 @discussion
    `AVCaptureSlider` is ideal when your control only needs a single float value. Controls may be added to an `AVCaptureSession` using `-[AVCaptureSession addControl:]`.
 */
API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureSlider : AVCaptureControl

/*!
 @method initWithLocalizedTitle:symbolName:minValue:maxValue:
 @abstract
    Initializes an `AVCaptureSlider` as a continuous slider between `minValue` and `maxValue`.
 
 @param localizedTitle
    A localized string that describes the slider's `action`.
 @param symbolName
    The name of a symbol to represent the slider.
 @param minValue
    The minimum value the slider can have. `minValue` must be less than `maxValue`, otherwise an `NSInvalidArgumentException` is thrown.
 @param maxValue
    The maximum value the slider can have. `maxValue` must be greater than `minValue`, otherwise an `NSInvalidArgumentException` is thrown.
 @result
    An `AVCaptureSlider` instance as a continuous slider between `minValue` and `maxValue`.
 
 @discussion
    Continuous sliders are used when any value in the range `minValue...maxValue` is supported.
 */
- (instancetype)initWithLocalizedTitle:(NSString *)localizedTitle symbolName:(NSString *)symbolName minValue:(float)minValue maxValue:(float)maxValue NS_REFINED_FOR_SWIFT;

/*!
 @method initWithLocalizedTitle:symbolName:minValue:maxValue:step:
 @abstract
    Initializes an `AVCaptureSlider` as a discrete slider where the valid values are between `minValue` and `maxValue` with `step` distance between each value.
 
 @param localizedTitle
    A localized string that describes the slider's `action`.
 @param symbolName
    The name of a symbol to represent the slider.
 @param minValue
    The minimum value the slider can have. `minValue` must be less than `maxValue`, otherwise an `NSInvalidArgumentException` is thrown.
 @param maxValue
    The maximum value the slider can have. `maxValue` must be greater than `minValue`, otherwise an `NSInvalidArgumentException` is thrown.
 @param step
    The distance between each valid value. `step` must be greater than 0, otherwise an `NSInvalidArgumentException` is thrown.
 @result
    An `AVCaptureSlider` instance as a discrete slider where the valid values are between `minValue` and `maxValue` with `step` distance between each value.
 
 @discussion
    Discrete sliders are used when only specific values are valid.
 */
- (instancetype)initWithLocalizedTitle:(NSString *)localizedTitle symbolName:(NSString *)symbolName minValue:(float)minValue maxValue:(float)maxValue step:(float)step NS_REFINED_FOR_SWIFT;

/*!
 @method initWithLocalizedTitle:symbolName:values:
 @abstract
    Initializes an `AVCaptureSlider` as a discrete slider where `values` contains the valid values.
 
 @param localizedTitle
    A localized string that describes the slider's `action`.
 @param symbolName
    The name of a symbol to represent the slider.
 @param values
    The only values the slider can have.
 @result
    An `AVCaptureSlider` instance as a discrete slider where `values` contains the valid values.
 
 @discussion
    Discrete sliders are used when only specific values are valid.
 */
- (instancetype)initWithLocalizedTitle:(NSString *)localizedTitle symbolName:(NSString *)symbolName values:(NSArray<NSNumber *> *)values NS_REFINED_FOR_SWIFT;

/*!
 @property value
 @abstract
    The current value of the slider.
 
 @discussion
    Because the camera system may be independent from the main thread or `@MainActor`, `value` must be changed on `actionQueue` – the queue provided to `setActionQueue:action:`. The default value is the slider's minimum value. A value may only be set if it is within the slider's minimum and maximum values, otherwise an `NSInvalidArgumentException` is thrown.
 */
@property(nonatomic, assign) float value;

/*!
 @property localizedValueFormat
 @abstract
    A localized string defining the presentation of the slider's value.
 
 @discussion
    To modify the presentation of the slider's value, set `localizedValueFormat` to a format string to display the slider's value with any annotation.
 
    The format string may only contain `%@` and no other placeholders like `%d`, `%s`, etc. Invalid format strings will result in the value's default presentation.
 
    Examples of valid format strings are:
    - `%@%%` for "40%"
    - `%@ fps` for "60 fps"
    - `+ %@` for "+ 20"
 */
@property(nonatomic, copy, nullable) NSString *localizedValueFormat;

/*!
 @property prominentValues
 @abstract
    Values in this array may receive unique visual representations or behaviors.
 */
@property(nonatomic, copy) NSArray<NSNumber *> *prominentValues NS_REFINED_FOR_SWIFT;

/*!
 @property localizedTitle
 @abstract
    A localized string that describes the slider's `action`.
 */
@property(nonatomic, copy, readonly) NSString *localizedTitle;

/*!
 @property symbolName
 @abstract
    The name of a symbol to represent the slider.
 */
@property(nonatomic, copy, readonly) NSString *symbolName;

/*!
 @property accessibilityIdentifier
 @abstract
    A string that identifies the slider.
 */
@property(nonatomic, copy, nullable) NSString *accessibilityIdentifier;


// MARK: Actions

/*!
 @method setActionQueue:action:
 @abstract
    Configures the slider's `action` which is called on `actionQueue` whenever the value of the slider is changed.
 
 @param actionQueue
    A queue for the `action` to be called.
 @param action
    An action called on `actionQueue` whenever the value of the slider is changed.
 
 @discussion
    Because the camera system may be independent from the main thread or `@MainActor`, `action` is always called on an internal `DispatchSerialQueue` targeted at `actionQueue`.
 
    If `action` modifies a property of the camera system, `actionQueue` must represent the same exclusive execution context as the camera system (see `isSameExclusiveExecutionContext`).
 */
- (void)setActionQueue:(dispatch_queue_t)actionQueue action:(void (^)(float newValue))action NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureSlider.h>
#endif
