//
//  TKTokenWatcher.h
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(TKTokenWatcher.TokenInfo)
@interface TKTokenWatcherTokenInfo : NSObject

/// TokenID
@property (readonly, nonatomic) NSString *tokenID;
/// The slot name (if available)
@property (readonly, nonatomic, nullable) NSString *slotName;
/// Localized driver name (if available)
@property (readonly, nonatomic, nullable) NSString *driverName;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKTokenWatcher : NSObject

/// Array of currently known TokenIDs in the system.  Tokens are identified by instance's names. It is possible to use KVO to be notified about token arrivals and removals.
@property (readonly) NSArray<NSString *> *tokenIDs;

/// Init watcher
- (instancetype)init;

/// Init watcher with insertion handler
/// @disscussion init watcher with insertion handler which is called when a new token arrives
/// @param insertionHandler called when a new token is inserted
- (instancetype)initWithInsertionHandler:(void(^)(NSString* tokenID)) insertionHandler
API_DEPRECATED_WITH_REPLACEMENT("setInsertionHandler", macos(10.12, 10.13), ios(10.0, 11.0));

/// Set insertion handler
/// @disscussion when an insertion handler is set the TokenWatcher will call this handler when new token appears in the system. TokenWatcher will call the handler also for tokens which was registered in the system before the handler was set.
/// @param insertionHandler called when a new token is inserted
- (void)setInsertionHandler:(void(^)(NSString* tokenID)) insertionHandler
API_AVAILABLE(macos(10.13), ios(11.0));

/// Add removal watcher for specific tokenID
/// @disscussion after removalHandler for a specific tokenID is called the reference to this handler is removed. For one tokenID just one handler can be added, so next call to addRemovalHandler will replace previous handler
/// @param removalHandler called when a token is removed
/// @param tokenID specified tokenID, if tokenID does not exist removal handler is called imediately
- (void)addRemovalHandler:(void(^)(NSString* tokenID)) removalHandler forTokenID:(NSString*) tokenID;

/// Return TokenInfo for specific tokenID
/// @param tokenID specified tokenID
/// @return A TokenInfo object, or nil if tokenID does not exist
- (nullable TKTokenWatcherTokenInfo *)tokenInfoForTokenID:(NSString *) tokenID
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end

NS_ASSUME_NONNULL_END
