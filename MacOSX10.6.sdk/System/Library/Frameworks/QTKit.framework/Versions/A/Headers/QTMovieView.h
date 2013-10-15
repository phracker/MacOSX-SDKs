/*
	File:		QTMovieView.h

	Copyright:	(c)2004-2010 by Apple Inc., all rights reserved.

*/

#import <Cocoa/Cocoa.h>
#import <QTKit/QTKitDefines.h>

@class QTMovie;
@class QTMovieControllerView;
@class QTMovieViewInternal;

QTKIT_EXTERN NSString * const QTMovieViewMovieBinding						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewControllerVisibleBinding			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewPreservesAspectRatioBinding		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewFillColorBinding					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;

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

- (QTMovie *)movie;
- (void)setMovie:(QTMovie *)movie;

- (BOOL)preservesAspectRatio;
- (void)setPreservesAspectRatio:(BOOL)preservesAspectRatio;
- (NSColor *)fillColor;
- (void)setFillColor:(NSColor *)fillColor;

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
- (BOOL)isControllerVisible;
- (void)setControllerVisible:(BOOL)controllerVisible;
- (void)setShowsResizeIndicator:(BOOL)show;
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (BOOL)isBackButtonVisible;
- (void)setBackButtonVisible:(BOOL)state;
- (BOOL)isCustomButtonVisible;
- (void)setCustomButtonVisible:(BOOL)state;
- (BOOL)isHotSpotButtonVisible;
- (void)setHotSpotButtonVisible:(BOOL)state;
- (BOOL)areStepButtonsVisible;
- (void)setStepButtonsVisible:(BOOL)state;
- (BOOL)isTranslateButtonVisible;
- (void)setTranslateButtonVisible:(BOOL)state;
- (BOOL)isVolumeButtonVisible;
- (void)setVolumeButtonVisible:(BOOL)state;
- (BOOL)areZoomButtonsVisible;
- (void)setZoomButtonsVisible:(BOOL)state;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */ 

- (NSRect)movieBounds;
- (NSRect)movieControllerBounds;
- (float)controllerBarHeight;

- (IBAction)play:(id)sender;
- (IBAction)pause:(id)sender;
- (IBAction)gotoBeginning:(id)sender;
- (IBAction)gotoEnd:(id)sender;
- (IBAction)gotoNextSelectionPoint:(id)sender;
- (IBAction)gotoPreviousSelectionPoint:(id)sender;
- (IBAction)gotoPosterFrame:(id)sender;
- (IBAction)stepForward:(id)sender;
- (IBAction)stepBackward:(id)sender;

- (BOOL)isEditable;
- (void)setEditable:(BOOL)editable;

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
- (id)delegate;
- (void)setDelegate:(id)delegate;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */ 

@end

@interface NSObject (QTMovieView_Delegate)

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)
- (CIImage *)view:(QTMovieView *)view willDisplayImage:(CIImage *)image;
#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6)
/*!
 @method		menuForEventDelegate:
 @param			An NSEvent object that specifies an event.
 @abstract		Returns an NSMenu object that is the contextual menu for the specified event.
 @discussion	This delegate method can be used instead of subclassing QTMovieView in cases that
				an application cannot hard link against the QTKit framework.
 */

- (NSMenu *)menuForEventDelegate:(NSEvent *)event;
#endif

@end
