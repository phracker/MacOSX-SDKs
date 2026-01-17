//
//  MKLookAroundViewController.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class MKLookAroundScene;
@class MKPointOfInterestFilter;

@protocol MKLookAroundViewControllerDelegate;

typedef NS_ENUM(NSInteger, MKLookAroundBadgePosition) {
    MKLookAroundBadgePositionTopLeading = 0,
    MKLookAroundBadgePositionTopTrailing,
    MKLookAroundBadgePositionBottomTrailing,
} API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos);

API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos)
#if TARGET_OS_IPHONE
@interface MKLookAroundViewController : UIViewController <NSSecureCoding, NSCoding>
#else
@interface MKLookAroundViewController : NSViewController <NSSecureCoding, NSCoding>
#endif

- (instancetype)initWithScene:(MKLookAroundScene *)scene NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, weak, nullable) IBOutlet id <MKLookAroundViewControllerDelegate> delegate;

@property (nonatomic, copy, nullable) MKLookAroundScene *scene;

// Defaults to YES
@property (nonatomic, assign, getter=isNavigationEnabled) BOOL navigationEnabled;

// Defaults to YES
@property (nonatomic, assign) BOOL showsRoadLabels;

@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter;

// Defaults to MKLookAroundBadgePositionTopLeading
@property (nonatomic, assign) MKLookAroundBadgePosition badgePosition;

@end

API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos)
@protocol MKLookAroundViewControllerDelegate <NSObject>

@optional
- (void)lookAroundViewControllerWillUpdateScene:(MKLookAroundViewController *)viewController;
- (void)lookAroundViewControllerDidUpdateScene:(MKLookAroundViewController *)viewController;

- (void)lookAroundViewControllerWillPresentFullScreen:(MKLookAroundViewController *)viewController;
- (void)lookAroundViewControllerDidPresentFullScreen:(MKLookAroundViewController *)viewController;
- (void)lookAroundViewControllerWillDismissFullScreen:(MKLookAroundViewController *)viewController;
- (void)lookAroundViewControllerDidDismissFullScreen:(MKLookAroundViewController *)viewController;

@end

NS_ASSUME_NONNULL_END
