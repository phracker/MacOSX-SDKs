//
//  MKAnnotationView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

// Post this notification to re-query callout information.
MK_EXTERN NSString * const MKAnnotationCalloutInfoDidChangeNotification;

typedef NS_ENUM(NSUInteger, MKAnnotationViewDragState) {
    MKAnnotationViewDragStateNone = 0,      // View is at rest, sitting on the map.
    MKAnnotationViewDragStateStarting,      // View is beginning to drag (e.g. pin lift)
    MKAnnotationViewDragStateDragging,      // View is dragging ("lift" animations are complete)
    MKAnnotationViewDragStateCanceling,     // View was not dragged and should return to its starting position (e.g. pin drop)
    MKAnnotationViewDragStateEnding         // View was dragged, new coordinate is set and view should return to resting position (e.g. pin drop)
} NS_ENUM_AVAILABLE(10_9, 4_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

typedef float MKFeatureDisplayPriority NS_TYPED_EXTENSIBLE_ENUM NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0) __WATCHOS_PROHIBITED;
static const MKFeatureDisplayPriority MKFeatureDisplayPriorityRequired NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0) __WATCHOS_PROHIBITED = 1000;
static const MKFeatureDisplayPriority MKFeatureDisplayPriorityDefaultHigh NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0) __WATCHOS_PROHIBITED = 750;
static const MKFeatureDisplayPriority MKFeatureDisplayPriorityDefaultLow NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0) __WATCHOS_PROHIBITED = 250;

typedef NS_ENUM(NSInteger, MKAnnotationViewCollisionMode) {
    MKAnnotationViewCollisionModeRectangle,
    MKAnnotationViewCollisionModeCircle
} NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0) __WATCHOS_PROHIBITED;

@protocol MKAnnotation;

#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 3_0) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKAnnotationView : UIView
#else
NS_CLASS_AVAILABLE(10_9, NA)
@interface MKAnnotationView : NSView
#endif

- (instancetype)initWithAnnotation:(nullable id <MKAnnotation>)annotation reuseIdentifier:(nullable NSString *)reuseIdentifier NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, nullable) NSString *reuseIdentifier;

// Classes that override must call super.
- (void)prepareForReuse;

- (void)prepareForDisplay NS_REQUIRES_SUPER NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0);

@property (nonatomic, strong, nullable) id <MKAnnotation> annotation;

#if TARGET_OS_IPHONE
@property (nonatomic, strong, nullable) UIImage *image;
#else
@property (nonatomic, strong, nullable) NSImage *image;
#endif

// By default, the center of annotation view is placed over the coordinate of the annotation.
// centerOffset is the offset in screen points from the center of the annotion view.
@property (nonatomic) CGPoint centerOffset;

// calloutOffset is the offset in screen points from the top-middle of the annotation view, where the anchor of the callout should be shown.
@property (nonatomic) CGPoint calloutOffset;

#if !TARGET_OS_IPHONE
// leftCalloutOffset is the offset in screen points from the middle-left of the annotation view, where the anchor of the callout should be shown when oriented off the left side of the annotation view
@property (nonatomic) CGPoint leftCalloutOffset;

// rightCalloutOffset is the offset in screen points from the middle-right of the annotation view, where the anchor of the callout should be shown when oriented off the right side of the annotation view
@property (nonatomic) CGPoint rightCalloutOffset;
#endif

// Defaults to YES. If NO, ignores touch events and subclasses may draw differently.
@property (nonatomic, getter=isEnabled) BOOL enabled;

// Defaults to NO. This gets set/cleared automatically when touch enters/exits during tracking and cleared on up.
@property (nonatomic, getter=isHighlighted) BOOL highlighted;

// Defaults to NO. Becomes YES when tapped/clicked on in the map view.
@property (nonatomic, getter=isSelected) BOOL selected;
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

// If YES, a standard callout bubble will be shown when the annotation is selected.
// The annotation must have a title for the callout to be shown.
@property (nonatomic) BOOL canShowCallout;

// The left accessory view to be used in the standard callout.
#if TARGET_OS_IPHONE
@property (strong, nonatomic, nullable) UIView *leftCalloutAccessoryView;
#else
@property (strong, nonatomic, nullable) NSView *leftCalloutAccessoryView;
#endif

// The right accessory view to be used in the standard callout.
#if TARGET_OS_IPHONE
@property (strong, nonatomic, nullable) UIView *rightCalloutAccessoryView;
#else
@property (strong, nonatomic, nullable) NSView *rightCalloutAccessoryView;
#endif

// The detail accessory view to be used in the standard callout.
#if TARGET_OS_IPHONE
@property (nonatomic, strong, nullable) UIView *detailCalloutAccessoryView NS_AVAILABLE(10_11, 9_0);
#else
@property (nonatomic, strong, nullable) NSView *detailCalloutAccessoryView NS_AVAILABLE(10_11, 9_0);
#endif

// If YES and the underlying id<MKAnnotation> responds to setCoordinate:, 
// the user will be able to drag this annotation view around the map.
@property (nonatomic, getter=isDraggable) BOOL draggable NS_AVAILABLE(10_9, 4_0) __TVOS_PROHIBITED;

// Automatically set to MKAnnotationViewDragStateStarting, Canceling, and Ending when necessary.
// Implementer is responsible for transitioning to Dragging and None states as appropriate.
@property (nonatomic) MKAnnotationViewDragState dragState NS_AVAILABLE(10_9, 4_0) __TVOS_PROHIBITED;

// Developers targeting iOS 4.2 and after must use setDragState:animated: instead of setDragState:.
- (void)setDragState:(MKAnnotationViewDragState)newDragState animated:(BOOL)animated NS_AVAILABLE(10_9, 4_2) __TVOS_PROHIBITED;

// Annotation views with equal non-nil identifiers can cluster together.
@property (nonatomic, copy, nullable) NSString *clusteringIdentifier  NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0);

// If non-nil this is the annotation view this view is clustered into.
@property (nonatomic, weak, readonly, nullable) MKAnnotationView *clusterAnnotationView NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0);

// Default is MKFeatureDisplayPriorityRequired, other values opts into collision occlusion by priority.
@property (nonatomic) MKFeatureDisplayPriority displayPriority NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0);

// Default collision mode is rectangle.
@property (nonatomic) MKAnnotationViewCollisionMode collisionMode NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0);

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
