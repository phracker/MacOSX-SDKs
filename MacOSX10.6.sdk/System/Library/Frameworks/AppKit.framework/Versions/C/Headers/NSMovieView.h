/*
        NSMovieView.h
        Copyright (c) 1998-2009, Apple Inc. All rights reserved.
*/

// Please note that NSMovie and NSMovieView are deprecated. NSMovieView does not exist in 64-bit.

#if !__LP64__

#import <AppKit/NSView.h>
#import <AppKit/NSUserInterfaceValidation.h>

@class NSMovie;

enum {
    NSQTMovieNormalPlayback,
    NSQTMovieLoopingPlayback,
    NSQTMovieLoopingBackAndForthPlayback
};
typedef NSUInteger NSQTMovieLoopMode;

typedef struct __MVFlags {
    unsigned int        editable:1;
    NSQTMovieLoopMode   loopMode:3;
    unsigned int        playsEveryFrame:1;
    unsigned int        playsSelectionOnly:1;
    unsigned int        controllerVisible:1;
    unsigned int        reserved:25;
} _MVFlags;

@interface NSMovieView : NSView <NSUserInterfaceValidations>
{
  @protected
    NSMovie*       _fMovie;
    float          _fRate;
    float          _fVolume;
    _MVFlags       _fFlags;

    void*          _fAuxData;
    unsigned long  _fReserved1;
    unsigned long  _fReserved2;
    unsigned long  _fReserved3;
}

- (void) setMovie:(NSMovie*)movie DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSMovie*) movie DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void* /*MovieController*/) movieController DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSRect) movieRect DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

    // playing

- (void)start:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)stop:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)isPlaying DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)gotoPosterFrame:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)gotoBeginning:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)gotoEnd:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)stepForward:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)stepBack:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)setRate:(float)rate DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (float)rate DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

    // sound

- (void)setVolume:(float)volume DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (float)volume DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setMuted:(BOOL)mute DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)isMuted DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

    // play modes

- (void)setLoopMode:(NSQTMovieLoopMode)mode DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSQTMovieLoopMode)loopMode DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setPlaysSelectionOnly:(BOOL)flag DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)playsSelectionOnly DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setPlaysEveryFrame:(BOOL)flag DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)playsEveryFrame DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

    // controller

- (void)showController:(BOOL)show adjustingSize:(BOOL)adjustSize DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)isControllerVisible DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

    // size

- (void)resizeWithMagnification:(CGFloat)magnification DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSSize)sizeForMagnification:(CGFloat)magnification DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

    // editing

- (void)setEditable:(BOOL)editable DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)isEditable DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)cut:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)copy:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)paste:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)delete:(id)sender AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
- (void)selectAll:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)clear:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;	// deprecated. use delete:

@end

#endif /* !__LP64__ */
