#import <Foundation/NSObject.h>
#import <AppKit/NSNibDeclarations.h>

@class NSMutableSet;
@class MVChatConnection;
@class NSSet;
@class JVChatWindowController;
@class NSString;
@class JVChatRoom;
@class JVDirectChat;
@class JVChatTranscript;
@class JVChatConsole;
@class NSAttributedString;

@protocol JVChatViewController;

@interface JVChatController : NSObject {
	@private
	NSMutableArray *_chatWindows;
	NSMutableArray *_chatControllers;
	NSMutableDictionary *_ignoreRules;
}
+ (JVChatController *) defaultManager;

- (NSSet *) allChatWindowControllers;
- (JVChatWindowController *) newChatWindowController;
- (void) disposeChatWindowController:(JVChatWindowController *) controller;

- (NSSet *) allChatViewControllers;
- (NSSet *) chatViewControllersWithConnection:(MVChatConnection *) connection;
- (NSSet *) chatViewControllersOfClass:(Class) class;
- (NSSet *) chatViewControllersKindOfClass:(Class) class;
- (JVChatRoom *) chatViewControllerForRoom:(NSString *) room withConnection:(MVChatConnection *) connection ifExists:(BOOL) exists;
- (JVDirectChat *) chatViewControllerForUser:(NSString *) user withConnection:(MVChatConnection *) connection ifExists:(BOOL) exists;
- (JVDirectChat *) chatViewControllerForUser:(NSString *) user withConnection:(MVChatConnection *) connection ifExists:(BOOL) exists userInitiated:(BOOL) requested;
- (JVChatTranscript *) chatViewControllerForTranscript:(NSString *) filename;
- (JVChatConsole *) chatConsoleForConnection:(MVChatConnection *) connection ifExists:(BOOL) exists;

- (void) disposeViewController:(id <JVChatViewController>) controller;
- (void) detachViewController:(id <JVChatViewController>) controller;

- (IBAction) detachView:(id) sender;

- (void) addIgnore:(NSString *)inIgnoreName withKey:(NSString *)ignoreKeyExpression inRooms:(NSArray *) rooms usesRegex:(BOOL) regex isMember:(BOOL) member;
- (BOOL) shouldIgnoreUser:(NSString *) user inRoom:(NSString *) room;
- (BOOL) shouldIgnoreMessage:(NSAttributedString *) message inRoom:(NSString *) room;
- (BOOL) shouldIgnoreMessage:(NSAttributedString *) message fromUser:(NSString *)user inRoom:(NSString *) room;
@end
