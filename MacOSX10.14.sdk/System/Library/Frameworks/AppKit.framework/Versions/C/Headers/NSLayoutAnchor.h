/*
 NSLayoutAnchor.h
 Application Kit
 Copyright (c) 2015-2018, Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSGeometry.h>
#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSLayoutConstraint, NSLayoutDimension;

/*
 An NSLayoutAnchor represents an edge or dimension of a layout item.  Its concrete subclasses allow concise creation of constraints.  The idea is that instead of invoking +[NSLayoutConstraint constraintWithItem: attribute: relatedBy: toItem: attribute: multiplier: constant:] directly, you can instead do something like this:
 
 [myView.topAnchor constraintEqualToAnchor:otherView.topAnchor constant:10];
 
 The -constraint* methods are available in multiple flavors to support use of different relations and omission of unused options.
 
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSLayoutAnchor<AnchorType> : NSObject <NSCopying, NSCoding>
{
    @private
    id  _item APPKIT_IVAR;
    NSInteger _attr APPKIT_IVAR;
    id _reserved1 APPKIT_IVAR;
    id _reserved2 APPKIT_IVAR;
    id _reserved3 APPKIT_IVAR;
    id _reserved4 APPKIT_IVAR;
    id _reserved5 APPKIT_IVAR;
}

// These methods return an inactive constraint of the form thisAnchor = otherAnchor.
- (NSLayoutConstraint*)constraintEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor;
- (NSLayoutConstraint*)constraintGreaterThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor;
- (NSLayoutConstraint*)constraintLessThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor;

// These methods return an inactive constraint of the form thisAnchor = otherAnchor + constant.
- (NSLayoutConstraint*)constraintEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor constant:(CGFloat)c;
- (NSLayoutConstraint*)constraintGreaterThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor constant:(CGFloat)c;
- (NSLayoutConstraint*)constraintLessThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor constant:(CGFloat)c;


// These properties are for debugging only:
@property (readonly, copy) NSString *name NS_AVAILABLE(10_12, 10_0);
@property (readonly, nullable, weak) id item NS_AVAILABLE(10_12, 10_0);
@property (readonly) BOOL hasAmbiguousLayout NS_AVAILABLE(10_12, 10_0);
@property (readonly) NSArray<NSLayoutConstraint *> *constraintsAffectingLayout NS_AVAILABLE(10_12, 10_0);

@end


// Axis-specific subclasses for location anchors: top/bottom, leading/trailing, baseline, etc.
@class NSLayoutXAxisAnchor, NSLayoutYAxisAnchor;

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSLayoutXAxisAnchor : NSLayoutAnchor<NSLayoutXAxisAnchor*>

// Creation of composite anchors:
- (NSLayoutDimension *)anchorWithOffsetToAnchor:(NSLayoutXAxisAnchor *)otherAnchor NS_AVAILABLE(10_12, 10_0);
@end

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSLayoutYAxisAnchor : NSLayoutAnchor<NSLayoutYAxisAnchor*>

// Creation of composite anchors:
- (NSLayoutDimension *)anchorWithOffsetToAnchor:(NSLayoutYAxisAnchor *)otherAnchor NS_AVAILABLE(10_12, 10_0);
@end


/*
 This layout anchor subclass is used for sizes (width & height).
 */
@class NSLayoutDimension;
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSLayoutDimension : NSLayoutAnchor<NSLayoutDimension*>

// These methods return an inactive constraint of the form thisVariable = constant.
- (NSLayoutConstraint*)constraintEqualToConstant:(CGFloat)c;
- (NSLayoutConstraint*)constraintGreaterThanOrEqualToConstant:(CGFloat)c;
- (NSLayoutConstraint*)constraintLessThanOrEqualToConstant:(CGFloat)c;

// These methods return an inactive constraint of the form thisAnchor = otherAnchor * multiplier.
- (NSLayoutConstraint*)constraintEqualToAnchor:(NSLayoutDimension*)anchor multiplier:(CGFloat)m;
- (NSLayoutConstraint*)constraintGreaterThanOrEqualToAnchor:(NSLayoutDimension*)anchor multiplier:(CGFloat)m;
- (NSLayoutConstraint*)constraintLessThanOrEqualToAnchor:(NSLayoutDimension*)anchor multiplier:(CGFloat)m;

// These methods return an inactive constraint of the form thisAnchor = otherAnchor * multiplier + constant.
- (NSLayoutConstraint*)constraintEqualToAnchor:(NSLayoutDimension*)anchor multiplier:(CGFloat)m constant:(CGFloat)c;
- (NSLayoutConstraint*)constraintGreaterThanOrEqualToAnchor:(NSLayoutDimension*)anchor multiplier:(CGFloat)m constant:(CGFloat)c;
- (NSLayoutConstraint*)constraintLessThanOrEqualToAnchor:(NSLayoutDimension*)anchor multiplier:(CGFloat)m constant:(CGFloat)c;

@end


NS_ASSUME_NONNULL_END
