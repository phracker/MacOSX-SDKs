//
//  SFSafariToolbarItem.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariToolbarItem : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Sets the enabled state and the badge text for the toolbar item. The badge text is visible even when the toolbar item is disabled.
- (void)setEnabled:(BOOL)enabled withBadgeText:(nullable NSString *)badgeText SF_DEPRECATED_MAC_SAFARI(10_0, 11_0, "use -setEnabled: and -setBadgeText:");

/// Sets the enabled state for the toolbar item.
- (void)setEnabled:(BOOL)enabled SF_AVAILABLE_MAC_SAFARI(10_1);

/// Sets the badge text for the toolbar item. The badge text is visible even when the toolbar item is disabled. Setting the text to nil will clear the badge.
- (void)setBadgeText:(nullable NSString *)badgeText SF_AVAILABLE_MAC_SAFARI(10_1);

/// Sets the image for the toolbar item. Setting the image to nil will set the default image.
- (void)setImage:(nullable NSImage *)image SF_AVAILABLE_MAC_SAFARI(10_1);

/// Sets the label for the toolbar button. Setting the label to nil will set the default label.
- (void)setLabel:(nullable NSString *)label SF_AVAILABLE_MAC_SAFARI(11_0);

/// Shows the popover associated with this toolbar button.
- (void)showPopover SF_AVAILABLE_MAC_SAFARI(12_1);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
