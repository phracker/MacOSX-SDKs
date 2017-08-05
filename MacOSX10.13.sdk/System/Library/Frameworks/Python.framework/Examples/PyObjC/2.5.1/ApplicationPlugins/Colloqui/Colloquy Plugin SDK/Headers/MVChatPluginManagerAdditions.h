#import "MVChatPluginManager.h"

@class MVConnectionsController;
@class JVChatController;
@class MVFileTransferController;
@class MVBuddyListController;
@class JVPreferencesController;

@interface MVChatPluginManager (MVChatPluginManagerAdditions)
- (MVConnectionsController *) connectionsController;
- (JVChatController *) chatController;
- (MVFileTransferController *) fileTransferController;
- (MVBuddyListController *) buddyListController;
- (JVPreferencesController *) preferencesController;
@end
