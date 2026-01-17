/*
        NSMenuItemBadge.h
        Application Kit
        Copyright (c) 2023-2024, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/// The badge type is used to specify one of the pre-defined or custom
/// string portions of a menu item badge, ensuring appropriate localization
/// and pluralization behaviors automatically when using a pre-defined type.
typedef NS_ENUM(NSInteger, NSMenuItemBadgeType) {
    /// The badge should have no string portion.
    NSMenuItemBadgeTypeNone = 0,
    
    /// The badge represents the number of available updates.
    NSMenuItemBadgeTypeUpdates,
    
    /// The badge represents the number of new items.
    NSMenuItemBadgeTypeNewItems,
    
    /// The badge represents the number of alerts.
    NSMenuItemBadgeTypeAlerts
} NS_SWIFT_NAME(NSMenuItemBadge.BadgeType) API_AVAILABLE(macos(14.0));

/// A badge used to provide additional quantitative information specific
/// to the menu item, such as the number of available updates.
API_AVAILABLE(macos(14.0))
@interface NSMenuItemBadge : NSObject <NSCopying>

/// Creates a badge with an integer count and a label representing
/// the number of available updates.
+ (instancetype)updatesWithCount:(NSInteger)itemCount NS_SWIFT_NAME(updates(count:));

/// Creates a badge with an integer count and a label representing
/// the number of new items.
+ (instancetype)newItemsWithCount:(NSInteger)itemCount NS_SWIFT_NAME(newItems(count:));

/// Creates a badge with an integer count and a label representing
/// the number of alerts.
+ (instancetype)alertsWithCount:(NSInteger)itemCount NS_SWIFT_NAME(alerts(count:));

/// Initializes the badge with a count and a pre-defined badge type.
- (instancetype)initWithCount:(NSInteger)itemCount type:(NSMenuItemBadgeType)type NS_SWIFT_UNAVAILABLE("Use updates(count:), newItems(count:), or alerts(count:) instead.");

/// Initializes the badge with an integer count and an empty string.
- (instancetype)initWithCount:(NSInteger)itemCount NS_SWIFT_NAME(init(count:));

/// Initializes the badge with the provided custom string.
- (instancetype)initWithString:(NSString *)string NS_SWIFT_NAME(init(string:));

- (instancetype)init NS_UNAVAILABLE;

/// The count of items the badge displays. If a custom string was used
/// to create a badge, the value is 0.
@property (readonly) NSInteger itemCount;

/// The type of items the badge displays. If a custom string was used
/// to create a badge, this value is @c NSMenuItemBadgeTypeNone.
@property (readonly) NSMenuItemBadgeType type;

/// The string representation of the badge as it would appear when the
/// badge is displayed.
@property (readonly, nullable) NSString *stringValue;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
