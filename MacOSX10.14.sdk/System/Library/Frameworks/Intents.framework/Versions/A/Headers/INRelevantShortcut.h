//
//  INRelevantShortcut.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Intents/INRelevanceProvider.h>
#import <Intents/INDefaultCardTemplate.h>
#import <Intents/INShortcut.h>

@class INShortcut;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INRelevantShortcutRole) {
    INRelevantShortcutRoleAction,
    INRelevantShortcutRoleInformation,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx);

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INRelevantShortcut : NSObject <NSSecureCoding, NSCopying>

@property (copy, NS_NONATOMIC_IOSONLY) NSArray<INRelevanceProvider *> *relevanceProviders;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INDefaultCardTemplate *watchTemplate;
@property (NS_NONATOMIC_IOSONLY) INRelevantShortcutRole shortcutRole;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INShortcut *shortcut;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithShortcut:(INShortcut *)shortcut NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
