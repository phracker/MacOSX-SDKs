/*
	File:		QTMovieView.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

*/


#import <Cocoa/Cocoa.h>
#import <QTKit/QTKitDefines.h>

#if __LP64__
#include <mach/mach.h>
#include <mach/message.h>
#endif

@class QTMovie;
@class QTMovieContentView;
@class QTMovieControllerView;

	// bindings
QTKIT_EXTERN NSString * const QTMovieViewMovieBinding						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewControllerVisibleBinding			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewPreservesAspectRatioBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewFillColorBinding					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if __LP64__
@interface QTMovieView : NSView <NSCoding, NSUserInterfaceValidations>
#else
@interface QTMovieView : NSView <NSCoding, NSUserInterfaceValidations, NSTextInput>
#endif
{
@private
	QTMovie *				_movie;
	NSColor *				_fillColor;
	BOOL					_controllerVisible;
	BOOL					_preservesAspectRatio;
#if !__LP64__
	QTMovieContentView *	_movieContentView;
	QTMovieControllerView *	_movieControllerView;
#endif
	long					_reserved1;
	long					_reserved2;
	long					_reserved3;
	id						_delegate;
#if __LP64__
	int32_t					_proxy;
	int32_t					_delegateProxy;
    BOOL					_useVisualContext;
    NSView                *	_movieContentView;
	NSView                *	_movieControllerView;
#endif
}

	// init
- (id)initWithFrame:(NSRect)frame;

	// getters
- (QTMovie *)movie;
- (BOOL)isControllerVisible;
- (BOOL)isEditable;
- (float)controllerBarHeight;
- (BOOL)preservesAspectRatio;
- (NSColor *)fillColor;

- (NSRect)movieBounds;
- (NSRect)movieControllerBounds;

	// setters
- (void)setMovie:(QTMovie *)movie;
- (void)setControllerVisible:(BOOL)controllerVisible;
- (void)setPreservesAspectRatio:(BOOL)preservesAspectRatio;
- (void)setFillColor:(NSColor *)fillColor;
- (void)setEditable:(BOOL)editable;

- (void)setShowsResizeIndicator:(BOOL)show;

	// actions
- (IBAction)play:(id)sender;
- (IBAction)pause:(id)sender;
- (IBAction)gotoBeginning:(id)sender;
- (IBAction)gotoEnd:(id)sender;
- (IBAction)gotoNextSelectionPoint:(id)sender;
- (IBAction)gotoPreviousSelectionPoint:(id)sender;
- (IBAction)gotoPosterFrame:(id)sender;
- (IBAction)stepForward:(id)sender;
- (IBAction)stepBackward:(id)sender;

- (IBAction)cut:(id)sender;
- (IBAction)copy:(id)sender;
- (IBAction)paste:(id)sender;
- (IBAction)selectAll:(id)sender;
- (IBAction)selectNone:(id)sender;
- (IBAction)delete:(id)sender;
- (IBAction)add:(id)sender;
- (IBAction)addScaled:(id)sender;
- (IBAction)replace:(id)sender;
- (IBAction)trim:(id)sender;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
	// controller bar button state accessors
- (void)setBackButtonVisible:(BOOL)state;
- (void)setCustomButtonVisible:(BOOL)state;
- (void)setHotSpotButtonVisible:(BOOL)state;
- (void)setStepButtonsVisible:(BOOL)state;
- (void)setTranslateButtonVisible:(BOOL)state;
- (void)setVolumeButtonVisible:(BOOL)state;
- (void)setZoomButtonsVisible:(BOOL)state;

- (BOOL)isBackButtonVisible;
- (BOOL)isCustomButtonVisible;
- (BOOL)isHotSpotButtonVisible;
- (BOOL)areStepButtonsVisible;
- (BOOL)isTranslateButtonVisible;
- (BOOL)isVolumeButtonVisible;
- (BOOL)areZoomButtonsVisible;

	// delegate
- (id)delegate;
- (void)setDelegate:(id)delegate;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */ 

@end

@interface NSObject (QTMovieViewDelegate)

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)
- (CIImage *)view:(QTMovieView *)view willDisplayImage:(CIImage *)image;
#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

@end

