/*
    NSStatusItem.h
    Application Kit
    Copyright (c) 1997-2017, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSEvent.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * NSStatusItemAutosaveName NS_EXTENSIBLE_STRING_ENUM;

@class NSAttributedString;
@class NSStatusBarButton;
@class NSStatusBar;
@class NSWindow;
@class NSImage;
@class NSMenu;
@class NSView;

typedef NS_OPTIONS(NSUInteger, NSStatusItemBehavior) {
    /* Allow the user to remove the item. By default, an item is not removable. To provide consistency with system status items, RemovalAllowed should be set if your application remains usable without the status item. It is the application's responsibility to allow the user to re-add the item. Upon removal, -visible is set to NO. This is observable through KVO.
     */
    NSStatusItemBehaviorRemovalAllowed = (1 << 1),
    
    /* The application terminates when the user removes the item. Implies NSStatusItemBehaviorRemovalAllowed.
     */
    NSStatusItemBehaviorTerminationOnRemoval = (1 << 2),
} NS_ENUM_AVAILABLE_MAC(10_12);

@interface NSStatusItem : NSObject {
 @private
    NSStatusBar* _fStatusBar;
    CGFloat      _fLength;
    NSWindow*    _fWindow;
    NSView*      _fView;
    int          _fPriority;
    NSUInteger   _fFlags;
    id		 _statusItemMenu;
    NSMutableDictionary *_replicants;
    id _fReserved __unused;
    NSString *_displayIdentifier;
}

/*  The status bar that the receiver is displayed in.
 */
@property (readonly, weak) NSStatusBar *statusBar;

/*  The amount of space in the status bar that should be allocated to the receiver. \c NSVariableStatusItemLength will adjust the length to the size of the status item's contents and \c NSSquareStatusItemLength will keep the length the same as the status bar's height.
 */
@property CGFloat length;

/*  The drop down menu that is displayed when the status item is pressed or clicked.
 */
@property (nullable, strong) NSMenu *menu;

/*  The button that is displayed in the status bar. This is created automatically on the creation of the StatusItem. Behavior customization for the button, such as image, target/action, tooltip, can be set with this property.
 */
@property (nullable, readonly, strong) NSStatusBarButton *button NS_AVAILABLE_MAC(10_10);

/*  Specifies the behavior of the status item.
 */
@property (assign) NSStatusItemBehavior behavior NS_AVAILABLE_MAC(10_12);

/*  Specifies if the status item is currently visible in the status bar, even if it is obscured by the application menu. Defaults to YES. Persisted based on the -autosaveName. This is observable through KVO.
 */
@property (assign, getter=isVisible) BOOL visible NS_AVAILABLE_MAC(10_12);

/*  Specifies a unique name for persisting visibility information. If none is specified, one is automatically chosen. Apps with multiple status bar items should set an autosave after creation. Setting to nil resets the automatically chosen name and clears saved information.
 */
@property (null_resettable, copy) NSStatusItemAutosaveName autosaveName NS_AVAILABLE_MAC(10_12);

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

#if __LP64__
- (NSInteger)sendActionOn:(NSEventMask)mask;
#else
- (NSInteger)sendActionOn:(NSInteger)mask;
#endif

/*
 Custom views should not be set on a status item.
 The button property with a template image will allow proper styling of the status item in various states and contexts and should be used instead.
 */
@property (nullable, strong) NSView *view;
- (void)drawStatusBarBackgroundInRect:(NSRect)rect withHighlight:(BOOL)highlight;
- (void)popUpStatusItemMenu:(NSMenu*)menu;

@end

NS_ASSUME_NONNULL_END

