/*
	File:		QTMovieView.h

	Copyright:	(c)2004 by Apple Computer, Inc., all rights reserved.

*/


#import <Cocoa/Cocoa.h>
#import <QTKit/QTKitDefines.h>

@class QTMovie;
@class QTMovieContentView;
@class QTMovieControllerView;

    // bindings
QTKIT_EXTERN NSString *QTMovieViewMovieBinding						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieViewControllerVisibleBinding			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieViewPreservesAspectRatioBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieViewFillColorBinding					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@interface QTMovieView : NSView <NSCoding, NSUserInterfaceValidations>
{
@private
    QTMovie                 *_movie;
    NSColor                 *_fillColor;
    BOOL                    _controllerVisible;
    BOOL                    _preservesAspectRatio;
    QTMovieContentView      *_movieContentView;
    QTMovieControllerView   *_movieControllerView;
    long                    _reserved1;
    long                    _reserved2;
    long                	_reserved3;
    id						_delegate;
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
- (void)setMovie:(QTMovie*)movie;
- (void)setControllerVisible:(BOOL)controllerVisible;
- (void)setPreservesAspectRatio:(BOOL)preservesAspectRatio;
- (void)setFillColor:(NSColor *)fillColor;
- (void)setEditable:(BOOL) editable;

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

@end
