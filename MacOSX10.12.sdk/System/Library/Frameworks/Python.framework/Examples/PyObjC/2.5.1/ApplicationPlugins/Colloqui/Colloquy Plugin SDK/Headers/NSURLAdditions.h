#import <Foundation/NSURL.h>

@interface NSURL (NSURLAdditions)
+ (id) URLWithInternetLocationFile:(NSString *) path;
- (void) writeToInternetLocationFile:(NSString *) path;

- (BOOL) isChatURL;
- (BOOL) isChatRoomURL;
- (BOOL) isDirectChatURL;
@end
