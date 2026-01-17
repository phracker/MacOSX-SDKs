#import <Foundation/NSObject.h>

@class NSLock;

@interface JVNotificationController : NSObject {
	NSMutableDictionary *_bubbles;
}
+ (JVNotificationController *) defaultManager;
- (void) performNotification:(NSString *) identifier withContextInfo:(NSDictionary *) context;
@end
