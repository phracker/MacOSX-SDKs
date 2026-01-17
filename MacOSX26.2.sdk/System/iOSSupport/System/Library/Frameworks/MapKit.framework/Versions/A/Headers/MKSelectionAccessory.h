//
//  MKSelectionAccessory.h
//  MapKit
//
//  Copyright © 2024 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIViewController.h>
#else
#import <AppKit/NSViewController.h>
#endif

@class MKMapItemDetailSelectionAccessoryPresentationStyle;

NS_ASSUME_NONNULL_BEGIN

// The type of accessory to display for a selected annotation
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0))
API_UNAVAILABLE(watchos, tvos)
@interface MKSelectionAccessory : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// Detailed information about a place
//
// Supported for `MKMapFeatureAnnotation` and `MKMapItemAnnotation`.
//
// - Parameters:
//   - presentation: the presentation style to use
+ (MKSelectionAccessory *)mapItemDetailWithPresentationStyle:(MKMapItemDetailSelectionAccessoryPresentationStyle *)presentationStyle NS_SWIFT_NAME(mapItemDetail(_:));
@end


// The style to use for map item detail callout presentation
typedef NS_ENUM(NSInteger, MKMapItemDetailSelectionAccessoryCalloutStyle) {
    // An appropriate callout style will be chosen automatically.
    MKMapItemDetailSelectionAccessoryCalloutStyleAutomatic,

    // A rich, detailed view
    MKMapItemDetailSelectionAccessoryCalloutStyleFull,

    // A compact, space-saving presentation
    MKMapItemDetailSelectionAccessoryCalloutStyleCompact
} NS_SWIFT_NAME(MKMapItemDetailSelectionAccessoryPresentationStyle.CalloutStyle)
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);


// The type of map item detail accessory presentation to use.
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0))
API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_NAME(MKSelectionAccessory.MapItemDetailPresentationStyle)
@interface MKMapItemDetailSelectionAccessoryPresentationStyle : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// An appropriate presentation style will be chosen automatically
//
// Supplying a non-nil `presentationViewController` will enable sheet
// presentation, if appropriate.
#if TARGET_OS_IPHONE
+ (MKMapItemDetailSelectionAccessoryPresentationStyle *)automaticWithPresentationViewController:(nullable UIViewController *)presentationViewController NS_REFINED_FOR_SWIFT;
#else
+ (MKMapItemDetailSelectionAccessoryPresentationStyle *)automaticWithPresentationViewController:(nullable NSViewController *)presentationViewController NS_REFINED_FOR_SWIFT;
#endif

// Show map item detail as an annotation callout on the map
//
// Uses the `automatic` callout style.
@property (class, nonatomic, strong, readonly) MKMapItemDetailSelectionAccessoryPresentationStyle *callout;

// Show map item detail as an annotation callout on the map
//
// - Parameters:
//   - style: the callout style to use
+ (MKMapItemDetailSelectionAccessoryPresentationStyle *)calloutWithCalloutStyle:(MKMapItemDetailSelectionAccessoryCalloutStyle)style NS_REFINED_FOR_SWIFT;

// Show map item detail by presenting a sheet
//
// - Parameters:
//   - presentedFrom: the view controller that will present the sheet
#if TARGET_OS_IPHONE
+ (MKMapItemDetailSelectionAccessoryPresentationStyle *)sheetPresentedFromViewController:(UIViewController *)viewController
#else
+ (MKMapItemDetailSelectionAccessoryPresentationStyle *)sheetPresentedFromViewController:(NSViewController *)viewController
#endif
NS_SWIFT_NAME(sheet(presentedFrom:));

// display a small "Open in Maps" affordance
@property (class, nonatomic, strong, readonly) MKMapItemDetailSelectionAccessoryPresentationStyle *openInMaps;
@end

NS_ASSUME_NONNULL_END
