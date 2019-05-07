//
//  INRelevantShortcutStore.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INRelevantShortcut;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INRelevantShortcutStore : NSObject

@property (class, readonly, strong) INRelevantShortcutStore *defaultStore;

- (void)setRelevantShortcuts:(NSArray<INRelevantShortcut *> *)shortcuts completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
