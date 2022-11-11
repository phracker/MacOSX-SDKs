//
//  PHPicker.h
//  PhotosUI
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE_BEGIN(ios(14))
API_UNAVAILABLE_BEGIN(macos, tvos, watchos)
NS_ASSUME_NONNULL_BEGIN

@class PHPhotoLibrary;

/// A mode that determines which representation an item provider should provide if multiple representations of the same asset are available for the requested type identifier or class.
 NS_REFINED_FOR_SWIFT
 typedef NS_ENUM(NSInteger, PHPickerConfigurationAssetRepresentationMode) {
     /// Uses the best representation determined by the system. This may change in future releases.
     PHPickerConfigurationAssetRepresentationModeAutomatic = 0,
     /// Uses the current representation to avoid transcoding if possible.
     PHPickerConfigurationAssetRepresentationModeCurrent = 1,
     /// Uses the most compatible representation if possible.
     PHPickerConfigurationAssetRepresentationModeCompatible = 2,
 };

/// An enum that determines how the picker handles user selection.
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, PHPickerConfigurationSelection) {
    /// Uses the default selection behavior.
    PHPickerConfigurationSelectionDefault = 0,
    /// Uses the selection order made by the user. Selected assets are numbered.
    PHPickerConfigurationSelectionOrdered = 1,
} API_AVAILABLE(ios(15));

/// A filter used to restrict the types \c PHPickerViewController can display.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
NS_REFINED_FOR_SWIFT
@interface PHPickerFilter : NSObject <NSCopying>

/// The filter for images.
@property (NS_NONATOMIC_IOSONLY, class, readonly) PHPickerFilter *imagesFilter;

/// The filter for videos.
@property (NS_NONATOMIC_IOSONLY, class, readonly) PHPickerFilter *videosFilter;

/// The filter for live photos.
@property (NS_NONATOMIC_IOSONLY, class, readonly) PHPickerFilter *livePhotosFilter;

/// Returns a new filter formed by OR-ing the filters in a given array.
+ (PHPickerFilter *)anyFilterMatchingSubfilters:(NSArray<PHPickerFilter *> *)subfilters;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

/// A configuration for \c PHPickerViewController.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
NS_REFINED_FOR_SWIFT
@interface PHPickerConfiguration : NSObject <NSCopying>

/// Preferred representation mode of selected assets. Default is \c PHPickerConfigurationAssetRepresentationModeAutomatic.
/// @discussion Setting \c preferredAssetRepresentationMode to \c PHPickerConfigurationAssetRepresentationModeAutomatic means the best representation determined by the system will be used.
@property (NS_NONATOMIC_IOSONLY) PHPickerConfigurationAssetRepresentationMode preferredAssetRepresentationMode;

/// Selection behavior of the picker. Default is \c PHPickerConfigurationSelectionDefault.
@property (NS_NONATOMIC_IOSONLY) PHPickerConfigurationSelection selection API_AVAILABLE(ios(15));

/// Maximum number of assets that can be selected. Default is 1.
/// @discussion Setting \c selectionLimit to 0 means maximum supported by the system.
@property (NS_NONATOMIC_IOSONLY) NSInteger selectionLimit;

/// Applying a filter to restrict the types that can be displayed. Default is \c nil.
/// @discussion Setting \c filter to \c nil means all asset types can be displayed.
@property (NS_NONATOMIC_IOSONLY, copy, nullable) PHPickerFilter *filter;

/// Local identifiers of assets to be shown as selected when the picker is presented. Default is an empty array.
/// @discussion \c preselectedAssetIdentifiers should be an empty array if \c selectionLimit is 1 or \c photoLibrary is not specified. Returned item providers for preselected assets are always empty.
@property (NS_NONATOMIC_IOSONLY, copy) NSArray<NSString *> *preselectedAssetIdentifiers API_AVAILABLE(ios(15));

/// Initializes a new configuration with the \c photoLibrary the picker should use.
- (instancetype)initWithPhotoLibrary:(PHPhotoLibrary *)photoLibrary;

/// Initializes a new configuration with the system photo library. This configuration never returns asset identifiers.
- (instancetype)init;

@end

/// A user selected asset from \c PHPickerViewController.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
NS_REFINED_FOR_SWIFT
@interface PHPickerResult : NSObject

/// Representations of the selected asset.
@property (NS_NONATOMIC_IOSONLY, readonly) NSItemProvider *itemProvider;

/// Local identifier of the selected asset.
@property (NS_NONATOMIC_IOSONLY, readonly, nullable) NSString *assetIdentifier;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
API_UNAVAILABLE_END // (macos, tvos, watchos)
API_AVAILABLE_END // (ios(14))

#import <UIKit/UIKit.h>

API_AVAILABLE_BEGIN(ios(14))
API_UNAVAILABLE_BEGIN(macos, tvos, watchos)
NS_ASSUME_NONNULL_BEGIN

@class PHPickerViewController;

/// A set of methods that the delegate must implement to respond to \c PHPickerViewController user events.
OS_EXPORT
NS_REFINED_FOR_SWIFT
@protocol PHPickerViewControllerDelegate <NSObject>

/// Called when the user completes a selection or dismisses \c PHPickerViewController using the cancel button.
/// @discussion The picker won't be automatically dismissed when this method is called.
- (void)picker:(PHPickerViewController *)picker didFinishPicking:(NSArray<PHPickerResult *> *)results;

@end

/// A picker that manages the system interfaces for choosing assets from the user's photos library and delivers the results of those interactions to a delegate.
/// @discussion \c PHPickerViewController is intended to be used as-is and does not support subclassing. The view hierarchy for the picker is private and must not be modified. A picker can only be presented once and should not be used for multiple sessions.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
@interface PHPickerViewController : UIViewController

/// The configuration passed in during initialization.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) PHPickerConfiguration *configuration NS_REFINED_FOR_SWIFT;

/// The delegate to be notified.
@property (NS_NONATOMIC_IOSONLY, weak) id<PHPickerViewControllerDelegate> delegate NS_REFINED_FOR_SWIFT;

/// Initializes a new picker with the \c configuration the picker should use.
- (instancetype)initWithConfiguration:(PHPickerConfiguration *)configuration NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
API_UNAVAILABLE_END // (macos, tvos, watchos)
API_AVAILABLE_END // (ios(14))
