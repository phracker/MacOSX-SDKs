#import <Foundation/NSObject.h>

@class JVChatTranscript;

@interface JVChatMessage : NSObject {
	@protected
	/* xmlNodePtr */ void *_node;
	unsigned long long _messageNumber;
	unsigned long long _envelopeNumber;
	JVChatTranscript *_transcript;
	NSString *_sender;
	NSString *_htmlMessage;
	NSTextStorage *_attributedMessage;
	NSDate *_date;
	BOOL _action;
	BOOL _highlighted;
	BOOL _loaded;
}
+ (id) messageWithNode:(/* xmlNode */ void *) node messageIndex:(unsigned long long) messageIndex andTranscript:(JVChatTranscript *) transcript;
- (id) initWithNode:(/* xmlNode */ void *) node messageIndex:(unsigned long long) messageIndex andTranscript:(JVChatTranscript *) transcript;

- (NSDate *) date;
- (NSString *) sender;

- (NSTextStorage *) message;
- (NSString *) messageAsPlainText;
- (NSString *) messageAsHTML;

- (BOOL) isAction;
- (BOOL) isHighlighted;

- (JVChatTranscript *) transcript;
- (unsigned long long) messageNumber;
- (unsigned long long) envelopeNumber;
@end
