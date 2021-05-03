//
//  INRelevantShortcutStore.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INRelevantShortcut;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Where relevant shortcuts are provided to Siri.
 @seealso INRelevantShortcut
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos)
@interface INRelevantShortcutStore : NSObject

@property (class, readonly, strong) INRelevantShortcutStore *defaultStore;

/*!
 @abstract Provide a new set of relevant shortcuts that should be suggested by Siri.
 @note Setting new relevant shortcuts will replace all relevant shortcuts that were previously provided.
 */
- (void)setRelevantShortcuts:(NSArray<INRelevantShortcut *> *)shortcuts completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

/*!
 @note Use the @c defaultStore singleton.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
