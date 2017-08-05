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
@interface SFSafariToolbarItem : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Sets the enabled state and the badge text for the toolbar item. The badge text is visible even when the toolbar item is disabled.
- (void)setEnabled:(BOOL)enabled withBadgeText:(nullable NSString *)badgeText;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
