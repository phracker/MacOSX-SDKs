/*
    NSStatusItem.h
    Application Kit
    Copyright (c) 1997-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

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
        unsigned int needsAdditionalReplicantUpdate:1;
        unsigned int reserved:15;
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
@property (nullable, strong) NSMenu *menu;

/// The button that is displayed in the status bar. This is created automatically on the creation of the StatusItem. Behavior customization for the button, such as image, target/action, tooltip, can be set with this property.
@property (nullable, readonly, strong) NSStatusBarButton *button NS_AVAILABLE_MAC(10_10);

@end


@interface NSStatusItem (NSStatusItemDeprecated)

/* 
 These are softly deprecated methods of NSStatusItem.
 Their past and current behavior is to forward their calls onto the button property.
 They will be formally deprecated in a later release. 
 */
@property (nullable) SEL action;
@property (nullable) SEL doubleAction;
@property (nullable, weak) id target;
@property (nullable, copy) NSString *title;
@property (nullable, copy) NSAttributedString *attributedTitle;
@property (nullable, strong) NSImage *image;
@property (nullable, strong) NSImage *alternateImage;
@property (getter=isEnabled) BOOL enabled;
@property BOOL highlightMode;
@property (nullable, copy) NSString *toolTip;
- (NSInteger)sendActionOn:(NSInteger)mask;

/*
 Custom views should not be set on a status item.
 The button property with a template image will allow proper styling of the status item in various states and contexts and should be used instead.
 */
@property (nullable, strong) NSView *view;
- (void)drawStatusBarBackgroundInRect:(NSRect)rect withHighlight:(BOOL)highlight;
- (void)popUpStatusItemMenu:(NSMenu*)menu;

@end

NS_ASSUME_NONNULL_END

