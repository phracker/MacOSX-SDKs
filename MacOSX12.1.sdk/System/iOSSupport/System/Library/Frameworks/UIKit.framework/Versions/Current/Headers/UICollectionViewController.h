#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollectionViewController.h>)
//
//  UICollectionViewController.h
//  UIKit
//
//  Copyright (c) 2011-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <UIKit/UICollectionView.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UICollectionViewLayout;
@class UICollectionViewController;

UIKIT_EXTERN API_AVAILABLE(ios(6.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionViewController : UIViewController <UICollectionViewDelegate, UICollectionViewDataSource>

- (instancetype)initWithCollectionViewLayout:(UICollectionViewLayout *)layout NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (null_resettable, nonatomic, strong) __kindof UICollectionView *collectionView;

// Defaults to YES, and if YES, any selection is cleared in viewWillAppear:
// This property has no effect if the useLayoutToLayoutNavigationTransitions property is set to YES
@property (nonatomic) BOOL clearsSelectionOnViewWillAppear;

// Set to YES before pushing a a UICollectionViewController onto a
// UINavigationController. The top view controller of the navigation controller
// must be a UICollectionViewController that was pushed with this property set
// to NO. This property should NOT be changed on a UICollectionViewController that
// has already been pushed onto a UINavigationController.
@property (nonatomic, assign) BOOL useLayoutToLayoutNavigationTransitions API_AVAILABLE(ios(7.0));

// The layout object is needed when defining interactive layout to layout transitions.
@property (nonatomic, readonly) UICollectionViewLayout *collectionViewLayout API_AVAILABLE(ios(7.0));

// Defaults to YES, and if YES, a system standard reordering gesture is used to drive collection view reordering
@property (nonatomic) BOOL installsStandardGestureForInteractiveMovement API_AVAILABLE(ios(9.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UICollectionViewController.h>
#endif
