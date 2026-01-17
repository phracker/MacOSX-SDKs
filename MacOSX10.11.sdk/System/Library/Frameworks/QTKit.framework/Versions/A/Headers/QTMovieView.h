/*
	File:		QTMovieView.h

	Copyright:	(c)2004-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <Cocoa/Cocoa.h>
#import <QTKit/QTKitDefines.h>

@class QTMovie;
@class QTMovieControllerView;
@class QTMovieViewInternal;

QTKIT_EXTERN NSString * const QTMovieViewMovieBinding						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieViewControllerVisibleBinding			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieViewPreservesAspectRatioBinding		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieViewFillColorBinding					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if __LP64__
@interface QTMovieView : NSView <NSCoding, NSUserInterfaceValidations>
#else
@interface QTMovieView : NSView <NSCoding, NSUserInterfaceValidations, NSTextInput>
#endif
{
@private
    QTMovie                 *_movie;
    
    NSColor                 *_fillColor;
    BOOL                    _controllerVisible;
	BOOL                    _preservesAspectRatio;
    
#if !__LP64__
    NSView                  *_rendererView;
    QTMovieControllerView   *_movieControllerView;
#endif    
    NSUInteger              _viewFlags;
    QTMovieViewInternal     *_internal;
	long					_reserved3;
	id						_delegate;
#if __LP64__
	int32_t					_proxy;
	int32_t					_delegateProxy;
    BOOL					_useVisualContext;
    NSView                  *_rendererView;
	QTMovieControllerView   *_movieControllerView;
#endif
}

- (QTMovie *)movie AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setMovie:(QTMovie *)movie AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (BOOL)preservesAspectRatio AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setPreservesAspectRatio:(BOOL)preservesAspectRatio AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSColor *)fillColor AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setFillColor:(NSColor *)fillColor AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
 @method		isControllerVisible
 @abstract		Returns an indication of whether the QTMovieView has been requested to display a built-in movie controller UI.
 @discussion	Via -setControllerVisible: the client tells QTMovieView whether or not to display a user interface for controlling
 				the movie within its bounds. Via -isControllerVisible the client can determine whether a QTMovieView has been configured
 				to display such an interface. Via -controllerBarHeight the client can determine the height of the portion of the
 				QTMovieView that's required to display that interface. Note that some types of QuickTime content are authored to
 				display their own user interface; for those types of content it's possible for -controllerBarHeight to return 0
 				even when -isControllerVisible is YES.
*/
- (BOOL)isControllerVisible AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setControllerVisible:(BOOL)controllerVisible AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setShowsResizeIndicator:(BOOL)show AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (BOOL)isBackButtonVisible AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setBackButtonVisible:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)isCustomButtonVisible AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setCustomButtonVisible:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)isHotSpotButtonVisible AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setHotSpotButtonVisible:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)areStepButtonsVisible AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setStepButtonsVisible:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)isTranslateButtonVisible AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setTranslateButtonVisible:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)isVolumeButtonVisible AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setVolumeButtonVisible:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)areZoomButtonsVisible AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setZoomButtonsVisible:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */ 

- (NSRect)movieBounds AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSRect)movieControllerBounds AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (float)controllerBarHeight AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (IBAction)play:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)pause:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)gotoBeginning:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)gotoEnd:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)gotoNextSelectionPoint:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)gotoPreviousSelectionPoint:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)gotoPosterFrame:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)stepForward:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)stepBackward:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (BOOL)isEditable AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setEditable:(BOOL)editable AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (IBAction)cut:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)copy:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)paste:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)selectAll:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)selectNone:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)delete:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)add:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)addScaled:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)replace:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (IBAction)trim:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (id)delegate AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setDelegate:(id)delegate AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */ 

@end

@interface NSObject (QTMovieView_Delegate)

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)
- (CIImage *)view:(QTMovieView *)view willDisplayImage:(CIImage *)image AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6)
/*!
 @method		menuForEventDelegate:
 @param			An NSEvent object that specifies an event.
 @abstract		Returns an NSMenu object that is the contextual menu for the specified event.
 @discussion	This delegate method can be used instead of subclassing QTMovieView in cases that
				an application cannot hard link against the QTKit framework.
 */

- (NSMenu *)menuForEventDelegate:(NSEvent *)event AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

@end
