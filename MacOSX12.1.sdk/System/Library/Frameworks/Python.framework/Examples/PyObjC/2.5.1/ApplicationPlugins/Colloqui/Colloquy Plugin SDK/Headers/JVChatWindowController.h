#import <AppKit/NSWindowController.h>
#import <AppKit/NSNibDeclarations.h>
#import "JVInspectorController.h"

@class NSDrawer;
@class NSOutlineView;
@class MVMenuButton;
@class NSMutableArray;
@class MVChatConnection;
@class NSArray;
@class NSToolbarItem;
@class NSString;
@class NSView;
@class JVChatWindowController;
@class NSToolbar;
@class NSImage;
@class NSMenu;

@protocol JVChatViewController;
@protocol JVChatListItem;

extern NSString *JVToolbarToggleChatDrawerItemIdentifier;
extern NSString *JVToolbarToggleChatActivityItemIdentifier;
extern NSString *JVChatViewPboardType;

@interface JVChatWindowController : NSWindowController <JVInspectionDelegator> {
	@protected
	IBOutlet NSDrawer *viewsDrawer;
	IBOutlet NSOutlineView *chatViewsOutlineView;
	IBOutlet MVMenuButton *viewActionButton;
	IBOutlet MVMenuButton *favoritesButton;
	IBOutlet MVMenuButton *activityToolbarButton;
	NSToolbarItem *_activityToolbarItem;
	NSView *_placeHolder;
	NSMutableArray *_views;
	id <JVChatViewController> _activeViewController;
	BOOL _usesSmallIcons;
}
- (void) showChatViewController:(id <JVChatViewController>) controller;

- (void) addChatViewController:(id <JVChatViewController>) controller;
- (void) insertChatViewController:(id <JVChatViewController>) controller atIndex:(unsigned int) index;

- (void) removeChatViewController:(id <JVChatViewController>) controller;
- (void) removeChatViewControllerAtIndex:(unsigned int) index;
- (void) removeAllChatViewControllers;

- (void) replaceChatViewController:(id <JVChatViewController>) controller withController:(id <JVChatViewController>) newController;
- (void) replaceChatViewControllerAtIndex:(unsigned int) index withController:(id <JVChatViewController>) controller;

- (NSArray *) chatViewControllersForConnection:(MVChatConnection *) connection;
- (NSArray *) chatViewControllersWithControllerClass:(Class) class;
- (NSArray *) allChatViewControllers;

- (id <JVChatViewController>) activeChatViewController;
- (id <JVChatListItem>) selectedListItem;

- (IBAction) getInfo:(id) sender;

- (IBAction) joinRoom:(id) sender;

- (IBAction) closeCurrentPanel:(id) sender;
- (IBAction) detachCurrentPanel:(id) sender;
- (IBAction) selectPreviousPanel:(id) sender;
- (IBAction) selectPreviousActivePanel:(id) sender;
- (IBAction) selectNextPanel:(id) sender;
- (IBAction) selectNextActivePanel:(id) sender;

- (NSToolbarItem *) toggleChatDrawerToolbarItem;
- (NSToolbarItem *) chatActivityToolbarItem;
- (IBAction) toggleViewsDrawer:(id) sender;
- (IBAction) openViewsDrawer:(id) sender;
- (IBAction) closeViewsDrawer:(id) sender;
	
- (void) reloadListItem:(id <JVChatListItem>) controller andChildren:(BOOL) children;
- (BOOL) isListItemExpanded:(id <JVChatListItem>) item;
- (void) expandListItem:(id <JVChatListItem>) item;
- (void) collapseListItem:(id <JVChatListItem>) item;
@end

@interface JVChatWindowController (JVChatWindowControllerScripting)
- (NSNumber *) uniqueIdentifier;
@end

@protocol JVChatViewController <NSObject, JVChatListItem>
- (MVChatConnection *) connection;

- (JVChatWindowController *) windowController;
- (void) setWindowController:(JVChatWindowController *) controller;

- (NSView *) view;
- (NSResponder *) firstResponder;
- (NSToolbar *) toolbar;
- (NSString *) windowTitle;
- (NSString *) identifier;
@end

@interface NSObject (JVChatViewControllerOptional)
- (void) willSelect;
- (void) didSelect;

- (void) willUnselect;
- (void) didUnselect;

- (void) willDispose;
@end

@protocol JVChatListItemScripting
- (NSNumber *) uniqueIdentifier;
@end

@protocol JVChatListItem <NSObject>
- (id <JVChatListItem>) parent;

- (NSImage *) icon;
- (NSString *) title;
@end

@interface NSObject (JVChatListItemOptional)
- (BOOL) acceptsDraggedFileOfType:(NSString *) type;
- (void) handleDraggedFile:(NSString *) path;
- (IBAction) doubleClicked:(id) sender;
- (BOOL) isEnabled;

- (NSMenu *) menu;
- (NSString *) information;
- (NSString *) toolTip;
- (NSImage *) statusImage;

- (int) numberOfChildren;
- (id) childAtIndex:(int) index;
@end