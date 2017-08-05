#import "JVChatTranscript.h"
#import <AppKit/NSNibDeclarations.h>
#import <Foundation/NSFileHandle.h>

@class NSView;
@class MVTextView;
@class NSPopUpButton;
@class NSString;
@class NSPanel;
@class MVChatConnection;
@class NSDate;
@class NSMutableData;
@class NSMutableArray;
@class NSMutableDictionary;
@class NSMutableString;
@class NSBundle;
@class NSDictionary;
@class NSToolbar;
@class NSData;
@class NSAttributedString;
@class NSMutableAttributedString;
@class JVBuddy;

@interface JVDirectChat : JVChatTranscript {
	@protected
	IBOutlet MVTextView *send;

	NSString *_target;
	NSStringEncoding _encoding;
	NSMenu *_encodingMenu;
	MVChatConnection *_connection;
	NSMutableArray *_sendHistory;
	NSMutableArray *_waitingAlerts;
	NSMutableDictionary *_waitingAlertNames;
	NSMutableDictionary *_settings;
	NSMenu *_spillEncodingMenu;
	JVBuddy *_buddy;
	NSFileHandle *_logFile;
	NSMutableArray *_messageQueue;

	unsigned int _messageId;
	BOOL _firstMessage;
	BOOL _requiresFullMessage;
	BOOL _isActive;
	unsigned int _newMessageCount;
	unsigned int _newHighlightMessageCount;
	BOOL _cantSendMessages;

	int _historyIndex;	
	float _sendHeight;
	BOOL _scrollerIsAtBottom;
	long _previousLogOffset;
	BOOL _forceSplitViewPosition;
}
- (id) initWithTarget:(NSString *) target forConnection:(MVChatConnection *) connection;

- (void) setTarget:(NSString *) target;
- (NSString *) target;
- (JVBuddy *) buddy;

- (void) unavailable;

- (IBAction) addToFavorites:(id) sender;

- (void) showAlert:(NSPanel *) alert withName:(NSString *) name;

- (void) setPreference:(id) value forKey:(NSString *) key;
- (id) preferenceForKey:(NSString *) key;

- (NSStringEncoding) encoding;
- (IBAction) changeEncoding:(id) sender;	

- (void) addEventMessageToDisplay:(NSString *) message withName:(NSString *) name andAttributes:(NSDictionary *) attributes;
- (void) addEventMessageToDisplay:(NSString *) message withName:(NSString *) name andAttributes:(NSDictionary *) attributes entityEncodeAttributes:(BOOL) encode;
- (void) addMessageToDisplay:(NSData *) message fromUser:(NSString *) user asAction:(BOOL) action;
- (void) processMessage:(NSMutableString *) message asAction:(BOOL) action fromUser:(NSString *) user;
- (void) echoSentMessageToDisplay:(NSAttributedString *) message asAction:(BOOL) action;

- (unsigned int) newMessagesWaiting;
- (unsigned int) newHighlightMessagesWaiting;

- (IBAction) send:(id) sender;
- (void) sendAttributedMessage:(NSMutableAttributedString *) message asAction:(BOOL) action;
- (BOOL) processUserCommand:(NSString *) command withArguments:(NSAttributedString *) arguments;

- (IBAction) clear:(id) sender;
- (IBAction) clearDisplay:(id) sender;
@end

@interface NSObject (MVChatPluginDirectChatSupport)
- (BOOL) processUserCommand:(NSString *) command withArguments:(NSAttributedString *) arguments toChat:(JVDirectChat *) chat;

- (void) processMessage:(NSMutableString *) message asAction:(BOOL) action inChat:(JVDirectChat *) chat;
- (void) processMessage:(NSMutableAttributedString *) message asAction:(BOOL) action toChat:(JVDirectChat *) chat;

- (void) userNamed:(NSString *) nickname isNowKnownAs:(NSString *) newNickname inView:(id <JVChatViewController>) view;
@end
