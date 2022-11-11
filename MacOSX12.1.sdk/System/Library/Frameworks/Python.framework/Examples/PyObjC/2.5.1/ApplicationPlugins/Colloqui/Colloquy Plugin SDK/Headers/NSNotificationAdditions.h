#import <Foundation/NSNotification.h>
#import <Foundation/NSNotificationQueue.h>

@interface NSNotificationCenter (NSNotificationAdditions)
- (void) postNotificationOnMainThread:(NSNotification *) notification;
@end

@interface NSNotificationQueue (NSNotificationAdditions)
- (void) enqueueNotificationOnMainThread:(NSNotification *) notification postingStyle:(NSPostingStyle) postingStyle;
- (void) enqueueNotificationOnMainThread:(NSNotification *) notification postingStyle:(NSPostingStyle) postingStyle coalesceMask:(unsigned) coalesceMask forModes:(NSArray *) modes;
@end
