#import <Foundation/NSString.h>
#import <Foundation/NSObject.h>
#import <AppKit/NSNibDeclarations.h>
#import "JVChatWindowController.h"

@class WebView;
@class MVMenuButton;
@class NSMutableSet;
@class NSString;
@class JVStyle;
@class NSBundle;
@class NSDictionary;
@class NSMutableDictionary;
@class JVChatMessage;
@class NSLock;

extern NSMutableSet *JVChatStyleBundles;
extern NSMutableSet *JVChatEmoticonBundles;

extern NSString *JVChatStylesScannedNotification;
extern NSString *JVChatEmoticonsScannedNotification;

@interface JVChatTranscript : NSObject <JVChatViewController> {
	@protected
	IBOutlet NSView *contents;
	IBOutlet WebView *display;
	BOOL _nibLoaded;

	JVChatWindowController *_windowController;

	NSString *_filePath;
	BOOL _isArchive;

	NSLock *_logLock;
	void *_xmlLog; /* xmlDocPtr */
	NSMutableArray *_messages;

	NSMenu *_styleMenu;
	JVStyle *_chatStyle;
	NSString *_chatStyleVariant;
	NSMutableDictionary *_styleParams;

	NSMenu *_emoticonMenu;
	NSBundle *_chatEmoticons;
	NSDictionary *_emoticonMappings;

	BOOL _previousStyleSwitch;
}
- (id) initWithTranscript:(NSString *) filename;

- (void) saveTranscriptTo:(NSString *) path;

- (IBAction) changeChatStyle:(id) sender;
- (void) setChatStyle:(JVStyle *) style withVariant:(NSString *) variant;
- (JVStyle *) chatStyle;

- (IBAction) changeChatStyleVariant:(id) sender;
- (void) setChatStyleVariant:(NSString *) variant;
- (NSString *) chatStyleVariant;

- (IBAction) changeChatEmoticons:(id) sender;
- (void) setChatEmoticons:(NSBundle *) emoticons;
- (void) setChatEmoticons:(NSBundle *) emoticons performRefresh:(BOOL) refresh;
- (NSBundle *) chatEmoticons;

- (unsigned long) numberOfMessages;
- (JVChatMessage *) messageAtIndex:(unsigned long) index;
- (NSArray *) messagesInRange:(NSRange) range;

- (IBAction) leaveChat:(id) sender;
@end

#pragma mark -

@interface JVChatTranscript (JVChatTranscriptScripting) <JVChatListItemScripting>
- (NSNumber *) uniqueIdentifier;
@end

#pragma mark -

@interface NSObject (MVChatPluginLinkClickSupport)
- (BOOL) handleClickedLink:(NSURL *) url inView:(id <JVChatViewController>) view;
@end