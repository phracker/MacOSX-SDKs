/*
    NSAnimation.h
    Application Kit
    Copyright (c) 2004-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NSGraphicsContext, NSString, NSDisplayLink;
@protocol NSAnimationDelegate;

typedef NS_ENUM(NSUInteger, NSAnimationCurve) {
    NSAnimationEaseInOut,       // default
    NSAnimationEaseIn,
    NSAnimationEaseOut,
    NSAnimationLinear
};

typedef NS_ENUM(NSUInteger, NSAnimationBlockingMode) {
    NSAnimationBlocking,
    NSAnimationNonblocking,
    NSAnimationNonblockingThreaded
};

typedef float NSAnimationProgress;

APPKIT_EXTERN NSString * NSAnimationProgressMarkNotification; // has single entry in user info dictionary
APPKIT_EXTERN NSString * NSAnimationProgressMark; // NSNumber(float) with NSAnimationProgress

@interface NSAnimation : NSObject <NSCopying, NSCoding> {
  @private
    NSTimeInterval       _duration;
    NSAnimationProgress  _currentProgress;
    float                 _framesPerSecond;
    id                   _delegate;
    NSDisplayLink       *_displayLink;
    NSTimeInterval       _startTime;
    NSMutableArray      *_progressMarks;
    NSAnimation         *_startAnimation;
    NSAnimation         *_stopAnimation;
    int                  _nextProgressMark;
    struct __aFlags {
	unsigned int delegateAnimationShouldStart:1;
	unsigned int delegateAnimationDidStop:1;
	unsigned int delegateAnimationDidEnd:1;
	unsigned int delegateAnimationValueForProgress:1;
	unsigned int delegateAnimationDidReachProgressMark:1;
	unsigned int animating:1;
	unsigned int blocking:1;
        unsigned int sendProgressAllTheTime:1;
	unsigned int reserved:24;
    } _aFlags;
    struct __aSettings {
	unsigned int animationCurve:8;
	unsigned int animationBlockingMode:2;
	unsigned int reserved:22;
    } _aSettings;
    NSRunLoop *_scheduledRunLoop;
    NSInteger _reserved2;
    NSInteger _reserved3;
    NSInteger _reserved4;
}

- (instancetype)initWithDuration:(NSTimeInterval)duration animationCurve:(NSAnimationCurve)animationCurve;

- (void)startAnimation;
- (void)stopAnimation;
@property (getter=isAnimating, readonly) BOOL animating;

@property NSAnimationProgress currentProgress;

@property NSTimeInterval duration;

@property NSAnimationBlockingMode animationBlockingMode;

@property float frameRate;

@property NSAnimationCurve animationCurve;

@property (readonly) float currentValue;

@property (nullable, assign) id<NSAnimationDelegate> delegate;

@property (copy) NSArray<NSNumber *> *progressMarks;

- (void)addProgressMark:(NSAnimationProgress)progressMark;
- (void)removeProgressMark:(NSAnimationProgress)progressMark;

- (void)startWhenAnimation:(NSAnimation *)animation reachesProgress:(NSAnimationProgress)startProgress;
- (void)stopWhenAnimation:(NSAnimation *)animation reachesProgress:(NSAnimationProgress)stopProgress;

- (void)clearStartAnimation;
- (void)clearStopAnimation;

@property (nullable, readonly, copy) NSArray<NSString *> *runLoopModesForAnimating;

@end

@protocol NSAnimationDelegate <NSObject>
@optional
- (BOOL)animationShouldStart:(NSAnimation *)animation;
- (void)animationDidStop:(NSAnimation *)animation;
- (void)animationDidEnd:(NSAnimation *)animation;
- (float)animation:(NSAnimation *)animation valueForProgress:(NSAnimationProgress)progress;
- (void)animation:(NSAnimation *)animation didReachProgressMark:(NSAnimationProgress)progress;
@end

/*-----------------------------------------------------------------------------------------*/

APPKIT_EXTERN NSString * NSViewAnimationTargetKey;       // NSWindow* or NSView* (required)
APPKIT_EXTERN NSString * NSViewAnimationStartFrameKey;   // NSValue*(NSRect) (optional)
APPKIT_EXTERN NSString * NSViewAnimationEndFrameKey;     // NSValue*(NSRect) (optional)
APPKIT_EXTERN NSString * NSViewAnimationEffectKey;       // NSString*(effect strings) (optional)
APPKIT_EXTERN NSString * NSViewAnimationFadeInEffect;
APPKIT_EXTERN NSString * NSViewAnimationFadeOutEffect;

@interface NSViewAnimation : NSAnimation {
  @private
    NSArray                *_viewAnimations;
    id                      _viewAnimationInfo;
    id                      _windowAnimationInfo;
    NSUInteger                  _reserved4a;
    NSUInteger                  _reserved4b;
    NSUInteger                  _reserved4c;
    struct __vaFlags {
	unsigned int reserved:32;
    }                       _vaFlags;    
    NSUInteger                  _reserved5;
    NSUInteger                  _reserved6;
    NSUInteger                  _reserved7;
    NSUInteger                  _reserved8;    
}

- (instancetype)initWithViewAnimations:(NSArray<NSDictionary<NSString *, id> *> *)viewAnimations;

@property (copy) NSArray<NSDictionary<NSString *, id> *> *viewAnimations;

@end


@protocol NSAnimatablePropertyContainer

/* Returns a proxy object for the receiver that can be used to initiate implied animation of property changes. An object's "animator" should be treated as if it was the object itself, and may be passed to any code that accepts the object as a parameter. Sending of KVC-compliant "set" messages to the proxy will trigger animation for automatically animated properties of its target object, if the active NSAnimationContext in the current thread has a duration value greater than zero, and an animation to use for the property key is found by the -animationForKey: search mechanism defined below. An object's automatically animated properties are those for which [theObject animationForKey:] finds and returns an CAAnimation instead of nil, often because [[theObject class] defaultAnimationForKey:] specifies a default animation for the key.

It's perfectly valid to set a new value for a property for which an animation is currently in progress; this simply sets a new target value for that property, with animation to the new target proceeding from whatever current value the property has reached. An in-flight property animation can be stopped by setting a new value for the property with 0.0 as the surrounding NSAnimationContext's duration value.
*/
- (instancetype)animator NS_AVAILABLE_MAC(10_5);

/* An animatable property container's optional "animations" dictionary maps NSString keys to CAAnimation values. When an occurrence matching the key fires for the view, -animationForKey: first looks in this dictionary for an animation to execute in response. Typically, the key will name a property of the object whose value has just changed, but it may instead specify a special event trigger (NSAnimationTriggerOrderIn or NSAnimationTriggerOrderOut).
*/
@property (readwrite, copy) NSDictionary<NSString *, id> *animations NS_AVAILABLE_MAC(10_5);

/* When the occurrence specified by "key" fires for an object, this method is consulted to find the animation, if any, that should be performed in response. Like its counterpart, -[CALayer actionForKey:], this method is a funnel point that defines the order in which the search for an animation proceeds, and is not one that clients would typically need to override. It first checks the receiver's "animations" dictionary, then falls back to  +defaultAnimationForKey: for the receiver's class.
*/
- (nullable id)animationForKey:(NSString *)key NS_AVAILABLE_MAC(10_5);

/* As described above, -animationForKey: consults this class method when its search of an instance's "animations" dictionary doesn't turn up an animation to use for a given property change.

An animatable property container should implement +defaultAnimationForKey: to return a default animation to be performed for each key that it wants to make auto-animatable, where "key" usually names a property of the receiver, but can also specify a special animation trigger (NSAnimationTriggerOrderIn or NSAnimationTriggerOrderOut).

A developer implementing a custom view subclass, for example, can enable automatic animation the subclass' added properties by overriding this method, and having it return the desired default CAAnimation to use for each of the property keys of interest. The override should defer to super for any keys it doesn't specifically handle, facilitating inheritance of default animation specifications.

The full set of available CAAnimation classes can be found in QuartzCore/CAAnimation.h.  Useful concrete animation classes are CABasicAnimation, CAKeyframeAnimation, CAAnimationGroup, and CATransition, all of which can be instantiated with default parameters by sending the class an +animation message.

@implementation MyView
+ (id)defaultAnimationForKey:(NSString *)key {
    if ([key isEqualToString:@"borderColor"]) {
        // By default, animate border color changes with simple linear interpolation to the new color value.
        return [CABasicAnimation animation];
    } else {
        // Defer to super's implementation for any keys we don't specifically handle.
        return [super defaultAnimationForKey:key];
    }
}
@end
*/
+ (nullable id)defaultAnimationForKey:(NSString *)key NS_AVAILABLE_MAC(10_5);

@end /* @protocol NSAnimatablePropertyContainer */

APPKIT_EXTERN NSString * NSAnimationTriggerOrderIn NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSAnimationTriggerOrderOut NS_AVAILABLE_MAC(10_5);

NS_ASSUME_NONNULL_END


