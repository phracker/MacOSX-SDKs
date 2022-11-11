#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAttachmentBehavior.h>)
//
//  UIAttachmentBehavior.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIAttachmentBehaviorType) {
    UIAttachmentBehaviorTypeItems,
    UIAttachmentBehaviorTypeAnchor
} API_AVAILABLE(ios(7.0));

typedef struct {
    CGFloat minimum;
    CGFloat maximum;
} UIFloatRange;

UIKIT_EXTERN const UIFloatRange UIFloatRangeZero API_AVAILABLE(ios(9.0));
UIKIT_EXTERN const UIFloatRange UIFloatRangeInfinite API_AVAILABLE(ios(9.0));
UIKIT_EXTERN BOOL UIFloatRangeIsInfinite(UIFloatRange range) API_AVAILABLE(ios(9.0));

UIKIT_STATIC_INLINE UIFloatRange UIFloatRangeMake(CGFloat minimum, CGFloat maximum) {
    return (UIFloatRange){minimum, maximum};
}

UIKIT_STATIC_INLINE BOOL UIFloatRangeIsEqualToRange(UIFloatRange range, UIFloatRange otherRange) {
    return range.minimum == otherRange.minimum && range.maximum == otherRange.maximum;
}

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) NS_SWIFT_UI_ACTOR
@interface UIAttachmentBehavior : UIDynamicBehavior

- (instancetype)initWithItem:(id <UIDynamicItem>)item attachedToAnchor:(CGPoint)point;
- (instancetype)initWithItem:(id <UIDynamicItem>)item offsetFromCenter:(UIOffset)offset attachedToAnchor:(CGPoint)point NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithItem:(id <UIDynamicItem>)item1 attachedToItem:(id <UIDynamicItem>)item2;
- (instancetype)initWithItem:(id <UIDynamicItem>)item1 offsetFromCenter:(UIOffset)offset1 attachedToItem:(id <UIDynamicItem>)item2 offsetFromCenter:(UIOffset)offset2 NS_DESIGNATED_INITIALIZER;

/*!
 A sliding attachment allows for relative translation of two items along a specified axis with respect to the anchor point. A sliding
 attachment prevents all relative rotation of the dynamic items.
 @param item1 The first of two dynamic items connected by the attachment behavior.
 @param item2 The second of two dynamic items connected by the attachment behavior.
 @param point The point for which each item will be attached. The anchor point will be converted to each items local coordinate system.
 @param axis Axis of allowed relative translation between local anchor point. Must be a unit vector.
 @see attachmentRange, Represents the slidable range of the attachment with respect to the anchor point along the specified axis, this range must include 0
 */
+ (instancetype)slidingAttachmentWithItem:(id <UIDynamicItem>)item1 attachedToItem:(id <UIDynamicItem>)item2 attachmentAnchor:(CGPoint)point axisOfTranslation:(CGVector)axis API_AVAILABLE(ios(9.0));

/*!
 A sliding attachment allows for translation of the item along a specified axis with respect to the anchor point. A sliding
 attachment prevents all relative rotation of the dynamic items.
 @param item1 The dynamic item connected by the attachment behavior.
 @param point The point for the item will be anchored by the attachment.
 @param axis Axis of allowed translation for the item. Must be a unit vector.
 @see attachmentRange, Represents the slidable range of the attachment with respect to the anchor point along the specified axis, this range must include 0
 */
+ (instancetype)slidingAttachmentWithItem:(id <UIDynamicItem>)item attachmentAnchor:(CGPoint)point axisOfTranslation:(CGVector)axis API_AVAILABLE(ios(9.0));

/*!
 A limit attachment imposes a maximum distance between two dynamic items, as if they were connected by a rope.
 @param item1 The first of two dynamic items connected by the attachment behavior.
 @param offset1 The point, within the dynamic item and described as an offset from its center point, for the attachment behavior.
 @param item2 The second of two dynamic items connected by the attachment behavior.
 @param offset2 The point, within the dynamic item and described as an offset from its center point, for the attachment behavior.
 @see length
 */
+ (instancetype)limitAttachmentWithItem:(id <UIDynamicItem>)item1 offsetFromCenter:(UIOffset)offset1 attachedToItem:(id <UIDynamicItem>)item2 offsetFromCenter:(UIOffset)offset2 API_AVAILABLE(ios(9.0));

/*!
 A fixed attachment fuses two dynamic items together at a reference point. 
 Fixed attachments are useful for creating complex shapes that can be broken apart later.
 @param item1 The first of two dynamic items connected by the attachment behavior.
 @param item2 The second of two dynamic items connected by the attachment behavior.
 @param point The point for which each item will be attached. The anchor point will be converted to each items local coordinate system.
 */
+ (instancetype)fixedAttachmentWithItem:(id <UIDynamicItem>)item1 attachedToItem:(id <UIDynamicItem>)item2 attachmentAnchor:(CGPoint)point API_AVAILABLE(ios(9.0));

/*!
 A pin attachment allows two dynamic items to independently rotate around the anchor point as if pinned together. 
 You can configure how far the two objects may rotate and the resistance to rotation
 @param item1 The first of two dynamic items connected by the attachment behavior.
 @param item2 The second of two dynamic items connected by the attachment behavior.
 @param point The point for which each item will be attached. The anchor point will be converted to each items local coordinate system
 @see frictionTorque, resistance to rotation
 */
+ (instancetype)pinAttachmentWithItem:(id <UIDynamicItem>)item1 attachedToItem:(id <UIDynamicItem>)item2 attachmentAnchor:(CGPoint)point API_AVAILABLE(ios(9.0));

@property (nonatomic, readonly, copy) NSArray<id <UIDynamicItem>> *items;

@property (readonly, nonatomic) UIAttachmentBehaviorType attachedBehaviorType;

@property (readwrite, nonatomic) CGPoint anchorPoint;

@property (readwrite, nonatomic) CGFloat length;
@property (readwrite, nonatomic) CGFloat damping; // 1: critical damping
@property (readwrite, nonatomic) CGFloat frequency; // in Hertz
@property (readwrite, nonatomic) CGFloat frictionTorque API_AVAILABLE(ios(9.0)); // default is 0.0
@property (readwrite, nonatomic) UIFloatRange attachmentRange API_AVAILABLE(ios(9.0)); // default is UIFloatRangeInfinite

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIAttachmentBehavior.h>
#endif
