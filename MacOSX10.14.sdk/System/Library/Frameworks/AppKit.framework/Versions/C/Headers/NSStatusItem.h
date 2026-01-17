/*
    NSStatusItem.h
    Application Kit
    Copyright (c) 1997-2018, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSEvent.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * NSStatusItemAutosaveName NS_SWIFT_BRIDGED_TYPEDEF;

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
    NSStatusBar* _fStatusBar APPKIT_IVAR;
    CGFloat      _fLength APPKIT_IVAR;
    NSWindow*    _fWindow APPKIT_IVAR;
    NSView*      _fView APPKIT_IVAR;
    int          _fPriority APPKIT_IVAR;
    NSUInteger   _fFlags APPKIT_IVAR;
    id		 _statusItemMenu APPKIT_IVAR;
    NSMutableDictionary *_replicants APPKIT_IVAR;
    id _fReserved __unused APPKIT_IVAR;
    NSString *_displayIdentifier APPKIT_IVAR;
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
/* These methods simply forward their calls onto the button property. */
@property (nullable) SEL action NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.action instead");
@property (nullable) SEL doubleAction NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.doubleAction instead");
@property (nullable, weak) id target NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.target instead");
@property (nullable, copy) NSString *title NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.title instead");
@property (nullable, copy) NSAttributedString *attributedTitle NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.attributedTitle instead");
@property (nullable, strong) NSImage *image NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.image instead");
@property (nullable, strong) NSImage *alternateImage NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.alternateImage instead");
@property (getter=isEnabled) BOOL enabled NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.enabled instead");
@property BOOL highlightMode NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.cell.highlightsBy instead");
@property (nullable, copy) NSString *toolTip NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button.toolTip instead");

#if __LP64__
- (NSInteger)sendActionOn:(NSEventMask)mask NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button's -sendActionOn: instead");
#else
- (NSInteger)sendActionOn:(NSInteger)mask NS_DEPRECATED_MAC(10_0, 10_14, "Use the receiver's button's -sendActionOn: instead");
#endif

/*
 Custom views should not be set on a status item.
 The button property with a template image will allow proper styling of the status item in various states and contexts and should be used instead.
 */
@property (nullable, strong) NSView *view NS_DEPRECATED_MAC(10_0, 10_14, "Use the standard button property instead");
- (void)drawStatusBarBackgroundInRect:(NSRect)rect withHighlight:(BOOL)highlight NS_DEPRECATED_MAC(10_0, 10_14, "Use the standard button instead which handles highlight drawing, making this method obsolete");
- (void)popUpStatusItemMenu:(NSMenu *)menu NS_DEPRECATED_MAC(10_0, 10_14, "Use the menu property instead");

@end

NS_ASSUME_NONNULL_END

