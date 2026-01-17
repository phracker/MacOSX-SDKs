//
//  TKTokenWatcher.h
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0)
@interface TKTokenWatcher : NSObject

/// Array of currently known TokenIDs in the system.  Tokens are identified by instance's names. It is possible to use KVO to be notified about token arrivals and removals.
@property (readonly) NSArray<NSString *> *tokenIDs;

/// Init watcher
- (instancetype)init;

/// Init watcher with insertion handler
/// @disscussion init watcher with insertion handler which is called when a new token arrives
/// @param insertionHandler
- (instancetype)initWithInsertionHandler:(void(^)(NSString* tokenID)) insertionHandler __OSX_DEPRECATED(10.12, 10.13, "Use 'setInsertionHandler' instead") __IOS_DEPRECATED(10.12, 10.13, "Use 'setInsertionHandler' instead");

/// Set insertion handler
/// @disscussion when an insertion handler is set the TokenWatcher will call this handler when new token appears in the system. TokenWatcher will call the handler also for tokens which was registered in the system before the handler was set.
/// @param insertionHandler
- (void)setInsertionHandler:(void(^)(NSString* tokenID)) insertionHandler __OSX_AVAILABLE(10.13) __IOS_AVAILABLE(10.13);

/// Add removal watcher for specific tokenID
/// @disscussion after removalHandler for a specific tokenID is called the reference to this handler is removed. For one tokenID just one handler can be added, so next call to addRemovalHandler will replace previous handler
/// @param removalHandler
/// @param tokenID specified tokenID, if tokenID does not exist removal handler is called imediately
- (void)addRemovalHandler:(void(^)(NSString* tokenID)) removalHandler forTokenID:(NSString*) tokenID;

@end

NS_ASSUME_NONNULL_END
