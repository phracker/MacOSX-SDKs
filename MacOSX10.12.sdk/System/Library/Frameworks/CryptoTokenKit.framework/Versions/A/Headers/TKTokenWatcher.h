//
//  TKTokenWatcher.h
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TKTokenWatcher : NSObject

/// Array of currently known TokenIDs in the system.  Tokens are identified by instance's names. It is possible to use KVO to be notified about token arrivals and removals.
@property (readonly) NSArray<NSString *> *tokenIDs;

/// Init watcher
- (instancetype)init;

/// Init watcher with insertion handler
/// @disscussion init watcher with insertion handler which is called when a new token arrives
/// @param insertionHandler
- (instancetype)initWithInsertionHandler:(void(^)(NSString* tokenID)) insertionHandler;

/// Add removal watcher for specific tokenID
/// @disscussion after removalHandler for a specific tokenID is called the reference to this handler is removed. For one tokenID just one handler can be added, so next call to addRemovalHandler will replace previous handler
/// @param removalHandler
/// @param tokenID specified tokenID, if tokenID does not exist removal handler is called imediately
- (void)addRemovalHandler:(void(^)(NSString* tokenID)) removalHandler forTokenID:(NSString*) tokenID;

@end

NS_ASSUME_NONNULL_END