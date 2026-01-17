#import <Foundation/NSObject.h>
#import <Foundation/NSMethodSignature.h>

@class NSMutableDictionary;
@class NSArray;
@class NSSet;
@class NSEnumerator;

@interface MVChatPluginManager : NSObject {
	@private
	NSMutableDictionary *_plugins;
}
+ (MVChatPluginManager *) defaultManager;

- (NSArray *) pluginSearchPaths;
- (void) findAndLoadPlugins;

- (NSSet *) plugins;
- (NSSet *) pluginsThatRespondToSelector:(SEL) selector;
- (NSSet *) pluginsOfClass:(Class) class thatRespondToSelector:(SEL) selector;

- (NSEnumerator *) pluginEnumerator;
- (NSEnumerator *) enumeratorOfPluginsThatRespondToSelector:(SEL) selector;
- (NSEnumerator *) enumeratorOfPluginsOfClass:(Class) class thatRespondToSelector:(SEL) selector;

- (unsigned int) numberOfPlugins;
- (unsigned int) numberOfPluginsThatRespondToSelector:(SEL) selector;
- (unsigned int) numberOfPluginsOfClass:(Class) class thatRespondToSelector:(SEL) selector;

- (NSArray *) makePluginsPerformInvocation:(NSInvocation *) invocation;
- (NSArray *) makePluginsPerformInvocation:(NSInvocation *) invocation stoppingOnFirstSuccessfulReturn:(BOOL) stop;
- (NSArray *) makePluginsOfClass:(Class) class performInvocation:(NSInvocation *) invocation stoppingOnFirstSuccessfulReturn:(BOOL) stop;
@end

@protocol MVChatPlugin
- (id) initWithManager:(MVChatPluginManager *) manager;
@end
