#import <Foundation/NSObject.h>
#import "MVChatPluginManager.h"

@class NSMutableDictionary;

@interface JVAutoEmotionDisplay : NSObject <MVChatPlugin> {
	NSMutableDictionary *_emotions;
	MVChatPluginManager *_manager;
}
@end
