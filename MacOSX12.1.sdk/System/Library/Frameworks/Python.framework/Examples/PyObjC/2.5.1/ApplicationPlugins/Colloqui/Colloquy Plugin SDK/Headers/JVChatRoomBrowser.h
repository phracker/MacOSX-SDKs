#import <AppKit/NSWindowController.h>
#import <AppKit/NSNibDeclarations.h>

@class MVChatConnection;
@class NSTableView;
@class NSTabView;
@class NSPopUpButton;
@class NSComboBox;
@class NSTextField;
@class NSButton;
@class NSMutableArray;
@class NSMutableDictionary;

@interface JVChatRoomBrowser : NSWindowController {
	IBOutlet NSTableView *roomsTable;
	IBOutlet NSTabView *borwserArea;
	IBOutlet NSTabView *searchArea;
	IBOutlet NSPopUpButton *connectionPopup;
	IBOutlet NSComboBox *roomField;
	IBOutlet NSTextField *searchField;
	IBOutlet NSTextField *indexResults;
	IBOutlet NSTextField *indexAndFindResults;
	IBOutlet NSButton *showBroswer;
	IBOutlet NSButton *acceptButton;
	BOOL _collapsed;
	BOOL _ascending;
	BOOL _needsRefresh;
	NSString *_sortColumn;
	MVChatConnection *_connection;
	NSMutableDictionary *_roomResults;
	NSMutableArray *_roomOrder;
	NSString *_currentFilter;
	NSTimer *_refreshTimer;
}
+ (id) chatRoomBrowserForConnection:(MVChatConnection *) connection;

- (IBAction) close:(id) sender;
- (IBAction) joinRoom:(id) sender;

- (IBAction) hideRoomBrowser:(id) sender;
- (IBAction) showRoomBrowser:(id) sender;
- (IBAction) toggleRoomBrowser:(id) sender;

- (IBAction) changeConnection:(id) sender;

- (void) setFilter:(NSString *) filter;
- (NSString *) filter;

- (void) setConnection:(MVChatConnection *) connection;
- (MVChatConnection *) connection;
@end
