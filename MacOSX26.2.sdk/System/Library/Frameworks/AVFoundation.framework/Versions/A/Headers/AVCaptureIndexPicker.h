#if !__has_include(<AVFCapture/AVCaptureIndexPicker.h>)
/*
    File:  AVCaptureIndexPicker.h
 
    Framework:  AVFoundation
 
    Copyright 2024 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureControl.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVCaptureIndexPicker
 @abstract
    An `AVCaptureControl` for selecting from a set of mutually exclusive values by index.
 
 @discussion
    `AVCaptureIndexPicker` is ideal when the set of values is provided by an indexed container like `NSArray`, `Array`, or `Sequence`. Controls may be added to an `AVCaptureSession` using `-[AVCaptureSession addControl:]`.
 
    `AVCaptureIndexPicker` uses zero-based indexing.
 */
API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureIndexPicker : AVCaptureControl

/*!
 @method initWithLocalizedTitle:symbolName:numberOfIndexes:
 @abstract
    Initializes an `AVCaptureIndexPicker` to pick between `numberOfIndexes` values.
 
 @param localizedTitle
    A localized string that describes the picker's `action`.
 @param symbolName
    The name of a symbol to represent the picker.
 @param numberOfIndexes
    The number of indexes to pick between. `numberOfIndexes` must be greater than 0, otherwise an `NSInvalidArgumentException` is thrown.
 @result
    An `AVCaptureIndexPicker` instance that picks between `numberOfIndexes` values.
 
 @discussion
    Suitable when your picked values don't need titles.
 */
- (instancetype)initWithLocalizedTitle:(NSString *)localizedTitle symbolName:(NSString *)symbolName numberOfIndexes:(NSInteger)numberOfIndexes NS_SWIFT_NAME(init(_:symbolName:numberOfIndexes:));

/*!
 @method initWithLocalizedTitle:symbolName:numberOfIndexes:localizedTitleTransform:
 @abstract
    Initializes an `AVCaptureIndexPicker` to pick between `numberOfIndexes` values.
    
 @param localizedTitle
    A localized string that describes the picker's `action`.
 @param symbolName
    The name of a symbol to represent the picker.
 @param numberOfIndexes
    The number of indexes to pick between. `numberOfIndexes` must be greater than 0, otherwise an `NSInvalidArgumentException` is thrown.
 @param localizedTitleTransform
    A transformation from index to localized title.
 @result
    An `AVCaptureIndexPicker` instance that picks between `numberOfIndexes` values with a transformation from index to localized title.
 
 @discussion
    Suitable when you want to provide a title for each picked value lazily.
 */
- (instancetype)initWithLocalizedTitle:(NSString *)localizedTitle symbolName:(NSString *)symbolName numberOfIndexes:(NSInteger)numberOfIndexes localizedTitleTransform:(NS_NOESCAPE NSString * (^)(NSInteger index))localizedTitleTransform NS_SWIFT_NAME(init(_:symbolName:numberOfIndexes:localizedTitleTransform:));

/*!
 @method initWithLocalizedTitle:symbolName:localizedIndexTitles:
 @abstract
    Initializes an `AVCaptureIndexPicker` to pick between `localizedIndexTitles.count` values.
    
 @param localizedTitle
    A localized string that describes the picker's `action`.
 @param symbolName
    The name of a symbol to represent the picker.
 @param localizedIndexTitles
    The titles to use for each index. `localizedIndexTitles` must be greater than 0, otherwise an `NSInvalidArgumentException` is thrown.
 @result
    An `AVCaptureIndexPicker` instance that picks between `localizedIndexTitles.count` values.
 
 @discussion
    Suitable when you already have an array containing a title for each picked value.
 */
- (instancetype)initWithLocalizedTitle:(NSString *)localizedTitle symbolName:(NSString *)symbolName localizedIndexTitles:(NSArray<NSString *> *)localizedIndexTitles NS_SWIFT_NAME(init(_:symbolName:localizedIndexTitles:));

/*!
 @property selectedIndex
 @abstract
    The currently selected index.
 
 @discussion
    Because the camera system may be independent from the main thread or `@MainActor`, `selectedIndex` must be changed on `actionQueue` – the queue provided to `setActionQueue:action:`. The default value is 0. An index may only be set if it is greater than 0 or less than `numberOfIndexes`, otherwise an `NSInvalidArgumentException` is thrown.
 */
@property(nonatomic, assign) NSInteger selectedIndex;

/*!
 @property localizedTitle
 @abstract
    A localized string that describes the picker's `action`.
 */
@property(nonatomic, copy, readonly) NSString *localizedTitle;

/*!
 @property symbolName
 @abstract
    The name of a symbol to represent the picker.
 */
@property(nonatomic, copy, readonly) NSString *symbolName;

/*!
 @property numberOfIndexes
 @abstract
    The number of indexes to pick between.
 */
@property(nonatomic, assign, readonly) NSInteger numberOfIndexes;

/*!
 @property localizedIndexTitles
 @abstract
    The titles used for each index.
 */
@property(nonatomic, copy, readonly) NSArray<NSString *> *localizedIndexTitles;

/*!
 @property accessibilityIdentifier
 @abstract
    A string that identifies the picker.
 */
@property(nullable, nonatomic, copy) NSString *accessibilityIdentifier;

// MARK: Actions

/*!
 @method setActionQueue:action:
 @abstract
    Configures the picker's `action` which is called on `actionQueue` whenever the index of the picker is changed.
 
 @param actionQueue
    A queue for the `action` to be called.
 @param action
    An action called on `actionQueue` whenever the selected index of the picker is changed.
 
 @discussion
    Because the camera system may be independent from the main thread or `@MainActor`, `action` is always called on an internal `DispatchSerialQueue` targeted at `actionQueue`.
 
    If `action` modifies a property of the camera system, `actionQueue` must represent the same exclusive execution context as the camera system (see `isSameExclusiveExecutionContext`).
 */
- (void)setActionQueue:(dispatch_queue_t)actionQueue action:(void (^)(NSInteger selectedIndex))action NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureIndexPicker.h>
#endif
