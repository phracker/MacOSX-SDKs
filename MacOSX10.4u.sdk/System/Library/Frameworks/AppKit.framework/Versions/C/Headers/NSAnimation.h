/*
    NSAnimation.h
    Application Kit
    Copyright (c) 2004-2005, Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/Foundation.h>
#import <AppKit/AppKitDefines.h>

@class NSGraphicsContext;

typedef enum {
    NSAnimationEaseInOut,       // default
    NSAnimationEaseIn,
    NSAnimationEaseOut,
    NSAnimationLinear
} NSAnimationCurve;

typedef enum {
    NSAnimationBlocking,
    NSAnimationNonblocking,
    NSAnimationNonblockingThreaded
} NSAnimationBlockingMode;

typedef float NSAnimationProgress;

extern NSString* NSAnimationProgressMarkNotification;   // has single entry in user info dictionary
extern NSString*    NSAnimationProgressMark;		    // NSNumber(float) with NSAnimationProgress

@interface NSAnimation : NSObject <NSCopying, NSCoding> {
  @private
    NSTimeInterval       _duration;
    NSAnimationProgress  _currentProgress;
    float                _framesPerSecond;
    id                   _delegate;
    NSTimer*             _timer;
    NSTimeInterval       _startTime;
    NSMutableArray*      _progressMarks;
    NSAnimation*	 _startAnimation;
    NSAnimation*	 _stopAnimation;
    int                  _nextProgressMark;
    struct __aFlags {
	unsigned int delegateAnimationShouldStart:1;
	unsigned int delegateAnimationDidStop:1;
	unsigned int delegateAnimationDidEnd:1;
	unsigned int delegateAnimationValueForProgress:1;
	unsigned int delegateAnimationDidReachProgressMark:1;
	unsigned int animating:1;
	unsigned int blocking:1;
	unsigned int reserved:25;
    } _aFlags;
    struct __aSettings {
	unsigned int animationCurve:8;
	unsigned int animationBlockingMode:2;
	unsigned int reserved:22;
    } _aSettings;
    long _reserved1;
    long _reserved2;
    long _reserved3;
    long _reserved4;
}

- (id)initWithDuration:(NSTimeInterval)duration animationCurve:(NSAnimationCurve)animationCurve;

- (void)startAnimation;
- (void)stopAnimation;
- (BOOL)isAnimating;

- (NSAnimationProgress)currentProgress;
- (void)setCurrentProgress:(NSAnimationProgress)progress;

- (void)setDuration:(NSTimeInterval)duration;
- (NSTimeInterval)duration;

- (NSAnimationBlockingMode)animationBlockingMode;
- (void)setAnimationBlockingMode:(NSAnimationBlockingMode)animationBlockingMode;

- (void)setFrameRate:(float)framesPerSecond;
- (float)frameRate;

- (void)setAnimationCurve:(NSAnimationCurve)curve;
- (NSAnimationCurve)animationCurve;

- (float)currentValue;

- (void)setDelegate:(id)delegate;
- (id)delegate;

- (NSArray*)progressMarks;
- (void)setProgressMarks:(NSArray*)progressMarks;

- (void)addProgressMark:(NSAnimationProgress)progressMark;
- (void)removeProgressMark:(NSAnimationProgress)progressMark;

- (void)startWhenAnimation:(NSAnimation*)animation reachesProgress:(NSAnimationProgress)startProgress;
- (void)stopWhenAnimation:(NSAnimation*)animation reachesProgress:(NSAnimationProgress)stopProgress;

- (void)clearStartAnimation;
- (void)clearStopAnimation;

- (NSArray*)runLoopModesForAnimating;

@end

@interface NSObject (NSAnimationDelegate)
- (BOOL)animationShouldStart:(NSAnimation*)animation;
- (void)animationDidStop:(NSAnimation*)animation;
- (void)animationDidEnd:(NSAnimation*)animation;
- (float)animation:(NSAnimation*)animation valueForProgress:(NSAnimationProgress)progress;
- (void)animation:(NSAnimation*)animation didReachProgressMark:(NSAnimationProgress)progress;
@end

/*-----------------------------------------------------------------------------------------*/

APPKIT_EXTERN NSString* NSViewAnimationTargetKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;       // NSWindow* or NSView* (required)
APPKIT_EXTERN NSString* NSViewAnimationStartFrameKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;   // NSValue*(NSRect) (optional)
APPKIT_EXTERN NSString* NSViewAnimationEndFrameKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;     // NSValue*(NSRect) (optional)
APPKIT_EXTERN NSString* NSViewAnimationEffectKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;       // NSString*(effect strings) (optional)
APPKIT_EXTERN NSString*     NSViewAnimationFadeInEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString*     NSViewAnimationFadeOutEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@interface NSViewAnimation : NSAnimation {
  @private
    NSArray*               _viewAnimations;
    CFMutableDictionaryRef _viewAnimationInfo;
    CFMutableDictionaryRef _windowAnimationInfo;
    CFMutableDictionaryRef _viewCacheContexts;
    NSGraphicsContext*     _saveContext;
    NSGraphicsContext*     _currentCacheContext;
    struct __vaFlags {
	unsigned int caching:1;
	unsigned int reserved:31;
    }                       _vaFlags;    
    unsigned int            _reserved5;
    unsigned int            _reserved6;
    unsigned int            _reserved7;
    unsigned int            _reserved8;    
}

- (id)initWithViewAnimations:(NSArray*)viewAnimations;

- (NSArray*)viewAnimations;
- (void)setViewAnimations:(NSArray*)viewAnimations;

@end

#endif
