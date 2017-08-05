#import <AppKit/NSWindowController.h>
#import <AppKit/NSNibDeclarations.h>
#import "JVInspectorController.h"

@class NSTableView;
@class NSWindow;
@class NSPanel;
@class NSTextField;
@class NSPopUpButton;
@class NSButton;
@class NSTabView;
@class NSComboBox;
@class NSString;
@class NSMutableArray;
@class MVChatConnection;
@class NSURL;

@interface MVConnectionsController : NSWindowController <JVInspectionDelegator> {
@private
	IBOutlet NSTableView *connections;
	IBOutlet NSPanel *openConnection;
	IBOutlet NSPanel *messageUser;
	IBOutlet NSPanel *nicknameAuth;

	/* Nick Auth */
	IBOutlet NSTextField *authNickname;
	IBOutlet NSTextField *authAddress;
	IBOutlet NSTextField *authPassword;
	IBOutlet NSButton *authKeychain;

	/* New Connection */
	IBOutlet NSTextField *newNickname;
	IBOutlet NSTextField *newAddress;
	IBOutlet NSTextField *newPort;
	IBOutlet NSButton *newRemember;
	IBOutlet NSButton *showDetails;
	IBOutlet NSTabView *detailsTabView;
	IBOutlet NSTextField *newServerPassword;
	IBOutlet NSTextField *newUsername;
	IBOutlet NSTextField *newRealName;
	IBOutlet NSPopUpButton *newProxy;
	IBOutlet NSTableView *newJoinRooms;
	IBOutlet NSButton *newRemoveRoom;
	IBOutlet NSButton *sslConnection;

	/* Message User */
	IBOutlet NSTextField *userToMessage;

	NSMutableArray *_bookmarks;
	NSMutableArray *_joinRooms;
	MVChatConnection *_passConnection;
}
+ (MVConnectionsController *) defaultManager;

+ (NSMenu *) favoritesMenu;
+ (void) refreshFavoritesMenu;

- (IBAction) showConnectionManager:(id) sender;
- (IBAction) hideConnectionManager:(id) sender;

- (IBAction) newConnection:(id) sender;
- (IBAction) toggleNewConnectionDetails:(id) sender;
- (IBAction) addRoom:(id) sender;
- (IBAction) removeRoom:(id) sender;
- (IBAction) openNetworkPreferences:(id) sender;
- (IBAction) conenctNewConnection:(id) sender;

- (IBAction) messageUser:(id) sender;

- (IBAction) sendPassword:(id) sender;

- (NSArray *) connections;
- (NSArray *) connectedConnections;
- (MVChatConnection *) connectionForServerAddress:(NSString *) address;
- (NSArray *) connectionsForServerAddress:(NSString *) address;

- (void) setAutoConnect:(BOOL) autoConnect forConnection:(MVChatConnection *) connection;
- (BOOL) autoConnectForConnection:(MVChatConnection *) connection;

- (void) setJoinRooms:(NSArray *) rooms forConnection:(MVChatConnection *) connection;
- (NSArray *) joinRoomsForConnection:(MVChatConnection *) connection;

- (void) setConnectCommands:(NSString *) commands forConnection:(MVChatConnection *) connection;
- (NSString *) connectCommandsForConnection:(MVChatConnection *) connection;

- (void) addConnection:(MVChatConnection *) connection;
- (void) addConnection:(MVChatConnection *) connection keepBookmark:(BOOL) keep;
- (void) insertConnection:(MVChatConnection *) connection atIndex:(unsigned) index;
- (void) removeConnectionAtIndex:(unsigned) index;
- (void) replaceConnectionAtIndex:(unsigned) index withConnection:(MVChatConnection *) connection;

- (void) handleURL:(NSURL *) url andConnectIfPossible:(BOOL) connect;
@end