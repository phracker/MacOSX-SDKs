/*
 NSLayoutAnchor.h
 Application Kit
 Copyright (c) 2015, Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>

@class NSLayoutConstraint;


/*
 An NSLayoutAnchor represents an edge or dimension of a layout item.  Its concrete subclasses allow concise creation of constraints.  The idea is that instead of invoking +[NSLayoutConstraint constraintWithItem: attribute: relatedBy: toItem: attribute: multiplier: constant:] directly, you can instead do something like this:
 
 [myView.topAnchor constraintEqualToAnchor:otherView.topAnchor constant:10];
 
 The -constraint* methods are available in multiple flavors to support use of different relations and omission of unused options.
 
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSLayoutAnchor<AnchorType> : NSObject
{
    @private
    id  _item;
    NSInteger _attr;
    id _reserved1;
    id _reserved2;
    id _reserved3;
    id _reserved4;
    id _reserved5;
}

// These methods return an inactive constraint of the form thisAnchor = otherAnchor.
- (NSLayoutConstraint*)constraintEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor;
- (NSLayoutConstraint*)constraintGreaterThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor;
- (NSLayoutConstraint*)constraintLessThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor;

// These methods return an inactive constraint of the form thisAnchor = otherAnchor + constant.
- (NSLayoutConstraint*)constraintEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor constant:(CGFloat)c;
- (NSLayoutConstraint*)constraintGreaterThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor constant:(CGFloat)c;
- (NSLayoutConstraint*)constraintLessThanOrEqualToAnchor:(NSLayoutAnchor<AnchorType>*)anchor constant:(CGFloat)c;
@end


// Axis-specific subclasses for location anchors: top/bottom, leading/trailing, baseline, etc.
@class NSLayoutXAxisAnchor, NSLayoutYAxisAnchor;
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSLayoutXAxisAnchor : NSLayoutAnchor<NSLayoutXAxisAnchor*>
@end
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSLayoutYAxisAnchor : NSLayoutAnchor<NSLayoutYAxisAnchor*>
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



