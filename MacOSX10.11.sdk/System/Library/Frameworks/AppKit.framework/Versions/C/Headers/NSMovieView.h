/*
        NSMovieView.h
        Copyright (c) 1998-2015, Apple Inc. All rights reserved.
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

NS_DEPRECATED_MAC(10_0, 10_5, "Use QTMovieView instead")
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

- (void) setMovie:(NSMovie*)movie NS_DEPRECATED_MAC(10_0, 10_5);
- (NSMovie*) movie NS_DEPRECATED_MAC(10_0, 10_5);

- (void* /*MovieController*/) movieController NS_RETURNS_INNER_POINTER NS_DEPRECATED_MAC(10_0, 10_5);
- (NSRect) movieRect NS_DEPRECATED_MAC(10_0, 10_5);

    // playing

- (void)start:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)stop:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (BOOL)isPlaying NS_DEPRECATED_MAC(10_0, 10_5);

- (void)gotoPosterFrame:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)gotoBeginning:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)gotoEnd:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)stepForward:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)stepBack:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);

- (void)setRate:(float)rate NS_DEPRECATED_MAC(10_0, 10_5);
- (float)rate NS_DEPRECATED_MAC(10_0, 10_5);

    // sound

- (void)setVolume:(float)volume NS_DEPRECATED_MAC(10_0, 10_5);
- (float)volume NS_DEPRECATED_MAC(10_0, 10_5);
- (void)setMuted:(BOOL)mute NS_DEPRECATED_MAC(10_0, 10_5);
- (BOOL)isMuted NS_DEPRECATED_MAC(10_0, 10_5);

    // play modes

- (void)setLoopMode:(NSQTMovieLoopMode)mode NS_DEPRECATED_MAC(10_0, 10_5);
- (NSQTMovieLoopMode)loopMode NS_DEPRECATED_MAC(10_0, 10_5);
- (void)setPlaysSelectionOnly:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_5);
- (BOOL)playsSelectionOnly NS_DEPRECATED_MAC(10_0, 10_5);
- (void)setPlaysEveryFrame:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_5);
- (BOOL)playsEveryFrame NS_DEPRECATED_MAC(10_0, 10_5);

    // controller

- (void)showController:(BOOL)show adjustingSize:(BOOL)adjustSize NS_DEPRECATED_MAC(10_0, 10_5);
- (BOOL)isControllerVisible NS_DEPRECATED_MAC(10_0, 10_5);

    // size

- (void)resizeWithMagnification:(CGFloat)magnification NS_DEPRECATED_MAC(10_0, 10_5);
- (NSSize)sizeForMagnification:(CGFloat)magnification NS_DEPRECATED_MAC(10_0, 10_5);

    // editing

- (void)setEditable:(BOOL)editable NS_DEPRECATED_MAC(10_0, 10_5);
- (BOOL)isEditable NS_DEPRECATED_MAC(10_0, 10_5);

- (void)cut:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)copy:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)paste:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);
- (void)delete:(id)sender NS_DEPRECATED_MAC(10_3, 10_5);
- (void)selectAll:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);

- (void)clear:(id)sender NS_DEPRECATED_MAC(10_0, 10_5);	// deprecated. use delete:

@end

#endif /* !__LP64__ */
