#import <AppKit/NSWindowController.h>
#import <AppKit/NSNibDeclarations.h>
#import "JVInspectorController.h"

@class MVTableView;
@class NSWindow;
@class NSView;
@class NSMenu;
@class NSButton;
@class NSImageView;
@class NSTextField;
@class NSPopUpButton;
@class JVBuddy;
@class NSMutableSet;
@class NSMutableArray;
@class NSString;
@class NSTimer;
@class ABPeoplePickerController;
@class MVChatConnection;

typedef enum {
	MVAvailabilitySortOrder = 'avlY',
	MVFirstNameSortOrder = 'fSnM',
	MVLastNameSortOrder = 'lSnM',
	MVServerSortOrder = 'serV'
} MVBuddyListSortOrder;

@interface MVBuddyListController : NSWindowController <JVInspectionDelegator> {
	@private
	IBOutlet MVTableView *buddies;
	IBOutlet NSMenu *actionMenu;
	IBOutlet NSButton *sendMessageButton;
	IBOutlet NSButton *infoButton;

	IBOutlet NSWindow *pickerWindow;
	IBOutlet NSView *pickerView;

	IBOutlet NSWindow *newPersonWindow;
	IBOutlet NSTextField *nickname;
	IBOutlet NSPopUpButton *server;
	IBOutlet NSTextField *firstName;
	IBOutlet NSTextField *lastName;
	IBOutlet NSTextField *email;
	IBOutlet NSImageView *image;
	IBOutlet NSButton *addButton;

	NSMutableSet *_buddyList;
	NSMutableSet *_onlineBuddies;
	NSMutableArray *_buddyOrder;
	ABPeoplePickerController* _picker;
	NSString *_addPerson;

	BOOL _showFullNames;
	BOOL _showNicknameAndServer;
	BOOL _showIcons;
	BOOL _showOfflineBuddies;
	MVBuddyListSortOrder _sortOrder;

	float _animationPosition;
	NSMutableArray *_oldPositions;
	NSTimer *_sortTimer;
	BOOL _viewingTop;
	BOOL _needsToAnimate;
	BOOL _animating;
}
+ (MVBuddyListController *) sharedBuddyList;

- (IBAction) getInfo:(id) sender;

- (IBAction) showBuddyList:(id) sender;
- (IBAction) hideBuddyList:(id) sender;

- (JVBuddy *) buddyForNickname:(NSString *) name onServer:(NSString *) address;
- (NSArray *) buddies;
- (NSArray *) onlineBuddies;

- (IBAction) showBuddyPickerSheet:(id) sender;
- (IBAction) cancelBuddySelection:(id) sender;
- (IBAction) confirmBuddySelection:(id) sender;

- (IBAction) showNewPersonSheet:(id) sender;
- (IBAction) cancelNewBuddy:(id) sender;
- (IBAction) confirmNewBuddy:(id) sender;

- (void) setNewBuddyNickname:(NSString *) nick;
- (void) setNewBuddyFullname:(NSString *) name;
- (void) setNewBuddyServer:(MVChatConnection *) connection;

- (IBAction) messageSelectedBuddy:(id) sender;
- (IBAction) sendFileToSelectedBuddy:(id) sender;

- (void) setShowFullNames:(BOOL) flag;
- (BOOL) showFullNames;
- (IBAction) toggleShowFullNames:(id) sender;

- (void) setShowNicknameAndServer:(BOOL) flag;
- (BOOL) showNicknameAndServer;
- (IBAction) toggleShowNicknameAndServer:(id) sender;

- (void) setShowIcons:(BOOL) flag;
- (BOOL) showIcons;
- (IBAction) toggleShowIcons:(id) sender;

- (void) setShowOfflineBuddies:(BOOL) flag;
- (BOOL) showOfflineBuddies;
- (IBAction) toggleShowOfflineBuddies:(id) sender;

- (void) setSortOrder:(MVBuddyListSortOrder) order;
- (MVBuddyListSortOrder) sortOrder;
- (IBAction) sortByAvailability:(id) sender;
- (IBAction) sortByFirstName:(id) sender;
- (IBAction) sortByLastName:(id) sender;
- (IBAction) sortByServer:(id) sender;
@end
