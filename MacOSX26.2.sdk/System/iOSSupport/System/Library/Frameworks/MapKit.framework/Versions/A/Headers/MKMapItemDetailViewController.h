//
//  MKMapItemDetailViewController.h
//  MapKit
//
//  Copyright © 2024 Apple, Inc. All rights reserved.
//

#import <MapKit/MKMapItem.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIViewController.h>
#else
#import <AppKit/NSViewController.h>
#endif

@class MKMapItemDetailViewController;

NS_ASSUME_NONNULL_BEGIN

// Delegate for `MKMapItemDetailViewController`
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0))
API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_UI_ACTOR
@protocol MKMapItemDetailViewControllerDelegate <NSObject>

// Called when the user is finished
- (void)mapItemDetailViewControllerDidFinish:(MKMapItemDetailViewController *)detailViewController;

@end

// Displays detailed information about a map item
//
// Presented modally, the map item detail view controller displays place
// information such as address and phone number.
//
// This class is intended to be used as-is and doesn’t support subclassing.
// The view hierarchy for this class is private and must not be modified.
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0))
API_UNAVAILABLE(watchos, tvos)
#if TARGET_OS_IPHONE
@interface MKMapItemDetailViewController : UIViewController
#else
@interface MKMapItemDetailViewController : NSViewController
#endif

// The map item to display
//
// If nil, a "loading" view is displayed
@property (nonatomic, strong, nullable) MKMapItem *mapItem;

// The map item detail view controller's delegate
@property (nonatomic, weak, nullable) id <MKMapItemDetailViewControllerDelegate> delegate;

// Create a map item detail view controller
//
// - Parameters:
//   - mapItem: The map item to display, or `nil` for "loading"
//   - displaysMap: If an inline map should be displayed with the place data.
//     A value of `YES` must be specified if the application UI is not
//     already showing the place in a map view.
- (instancetype)initWithMapItem:(nullable MKMapItem *)mapItem
                    displaysMap:(BOOL)displaysMap;

// Create a map item detail view controller
//
// Displays an inline map with the place data. If the application UI is
// already showing the place in a map view, the inline map can be disabled
// by using the `- initWithMapItem:displaysMap:` initializer.
//
// - Parameters:
//   - mapItem: The map item to display, or `nil` for "loading"
- (instancetype)initWithMapItem:(nullable MKMapItem *)mapItem;

@end

NS_ASSUME_NONNULL_END
