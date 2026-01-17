/*
    NSStatusItem.h
    Application Kit
    Copyright (c) 1997-2014, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

@class NSAttributedString;
@class NSStatusBarButton;
@class NSStatusBar;
@class NSWindow;
@class NSImage;
@class NSMenu;
@class NSView;

@interface NSStatusItem : NSObject {
 @private
    NSStatusBar* _fStatusBar;
    CGFloat        _fLength;
    NSWindow*    _fWindow;
    NSView*      _fView;
    int          _fPriority;
    struct {
	unsigned int customView:1;
	unsigned int highlightMode:1;
	unsigned int hasAlternateImage:1;
	unsigned int hidden:1;
	unsigned int backgroundStyle:4;
	unsigned int inAdjustLength:1;
        unsigned int pendingReplicantDisplay:1;
        unsigned int disableImageReplicationCount:4;
        unsigned int updatingReplicant:1;
        unsigned int didInactiveTemplateStyling:1;
        unsigned int reserved:16;
    }	 _fFlags;
    id		 _statusItemMenu;
    NSMutableDictionary *_replicants;
    NSData *_subitemOffsets;
    NSString *_displayIdentifier;
}

/// The status bar that the receiver is displayed in.
@property (readonly, assign) NSStatusBar *statusBar;

/// The amount of space in the status bar that should be allocated to the receiver. \c NSVariableStatusItemLength will adjust the length to the size of the status item's contents and \c NSSquareStatusItemLength will keep the length the same as the status bar's height.
@property CGFloat length;

/// The drop down menu that is displayed when the status item is pressed or clicked.
@property (strong) NSMenu *menu;

/// The button that is displayed in the status bar. This is created automatically on the creation of the StatusItem. Behavior customization for the button, such as image, target/action, tooltip, can be set with this property.
@property (readonly, strong) NSStatusBarButton *button NS_AVAILABLE_MAC(10_10);

@end


@interface NSStatusItem (NSStatusItemDeprecated)

/* 
 These are softly deprecated methods of NSStatusItem.
 Their past and current behavior is to forward their calls onto the button property.
 They will be formally deprecated in a later release. 
 */
@property SEL action;
@property SEL doubleAction;
@property (weak) id target;
@property (copy) NSString *title;
@property (copy) NSAttributedString *attributedTitle;
@property (strong) NSImage *image;
@property (strong) NSImage *alternateImage;
@property (getter=isEnabled) BOOL enabled;
@property BOOL highlightMode;
@property (copy) NSString *toolTip;
- (NSInteger)sendActionOn:(NSInteger)mask;

/*
 Custom views should not be set on a status item.
 The button property with a template image will allow proper styling of the status item in various states and contexts and should be used instead.
 */
@property (strong) NSView *view;
- (void)drawStatusBarBackgroundInRect:(NSRect)rect withHighlight:(BOOL)highlight;
- (void)popUpStatusItemMenu:(NSMenu*)menu;

@end

