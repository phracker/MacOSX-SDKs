#import "JVDirectChat.h"
#import <AppKit/NSNibDeclarations.h>

@class NSTextView;
@class WebView;
@class NSMutableDictionary;
@class NSMutableArray;
@class NSData;
@class NSString;
@class JVChatRoomMember;

extern NSString *MVChatRoomModeChangedNotification;

@interface JVChatRoom : JVDirectChat {
	@protected
	IBOutlet NSTextView *topicLine;

	NSMutableDictionary *_members;
	NSMutableArray *_sortedMembers;
	NSMutableSet *_nextMessageAlertMembers;
	NSAttributedString *_topicAttributed;
	NSData *_topic;
	NSString *_topicAuth;
	NSString *_key;
	unsigned int _modes;
	unsigned int _limit;

	BOOL _kickedFromRoom;
	BOOL _inRoom;
	BOOL _keepAfterPart;
	
	BOOL _initialBanlistReceived;
}
- (void) joined;
- (void) parting;

- (void) joinChat:(id) sender;
- (void) partChat:(id) sender;

- (BOOL) keepAfterPart;
- (void) setKeepAfterPart:(BOOL) keep;

- (void) addWhoInformationToMembers:(NSArray *) members;
- (void) addExistingMembersToChat:(NSArray *) members;
- (void) addMemberToChat:(NSString *) member withInformation:(NSDictionary *) info;
- (void) removeChatMember:(NSString *) member withReason:(NSData *) reason;
- (void) changeChatMember:(NSString *) member to:(NSString *) nick;

- (void) promoteChatMember:(NSString *) member by:(NSString *) by;
- (void) demoteChatMember:(NSString *) member by:(NSString *) by;
- (void) voiceChatMember:(NSString *) member by:(NSString *) by;
- (void) devoiceChatMember:(NSString *) member by:(NSString *) by;

- (void) chatMember:(NSString *) member kickedBy:(NSString *) by forReason:(NSData *) reason;
- (void) kickedFromChatBy:(NSString *) by forReason:(NSData *) reason;

- (void) newBan:(NSString *) ban by:(NSString *) by;
- (void) removedBan:(NSString *) ban by:(NSString *) by;
- (void) banlistReceived;

- (void) changeTopic:(NSData *) topic by:(NSString *) author displayChange:(BOOL) showChange;
- (NSAttributedString *) topic;

- (void) setModes:(unsigned int) modes;
- (unsigned int) modes;

- (void) setKey:(NSString *) key;
- (NSString *) key;

- (void) setLimit:(unsigned int) limit;
- (unsigned int) limit;

- (JVChatRoomMember *) chatRoomMemberWithName:(NSString *) name;
- (void) resortMembers;
@end

@interface NSObject (MVChatPluginRoomSupport)
- (BOOL) processUserCommand:(NSString *) command withArguments:(NSAttributedString *) arguments toRoom:(JVChatRoom *) room;

- (void) processMessage:(NSMutableString *) message asAction:(BOOL) action fromMember:(JVChatRoomMember *) member inRoom:(JVChatRoom *) room;
- (void) processMessage:(NSMutableAttributedString *) message asAction:(BOOL) action toRoom:(JVChatRoom *) room;

- (void) memberJoined:(JVChatRoomMember *) member inRoom:(JVChatRoom *) room;
- (void) memberParted:(JVChatRoomMember *) member fromRoom:(JVChatRoom *) room forReason:(NSString *) reason;
- (void) memberKicked:(JVChatRoomMember *) member fromRoom:(JVChatRoom *) room by:(JVChatRoomMember *) by forReason:(NSString *) reason;

- (void) memberPromoted:(JVChatRoomMember *) member inRoom:(JVChatRoom *) room by:(JVChatRoomMember *) by;
- (void) memberDemoted:(JVChatRoomMember *) member inRoom:(JVChatRoom *) room by:(JVChatRoomMember *) by;
- (void) memberVoiced:(JVChatRoomMember *) member inRoom:(JVChatRoom *) room by:(JVChatRoomMember *) by;
- (void) memberDevoiced:(JVChatRoomMember *) member inRoom:(JVChatRoom *) room by:(JVChatRoomMember *) by;

- (void) joinedRoom:(JVChatRoom *) room;
- (void) partingFromRoom:(JVChatRoom *) room;
- (void) kickedFromRoom:(JVChatRoom *) room by:(JVChatRoomMember *) by forReason:(NSString *) reason;

- (void) topicChangedTo:(NSString *) topic inRoom:(JVChatRoom *) room by:(JVChatRoomMember *) member;
@end