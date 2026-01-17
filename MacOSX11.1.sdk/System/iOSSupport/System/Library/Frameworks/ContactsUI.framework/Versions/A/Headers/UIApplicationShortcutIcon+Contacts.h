//
//  UIApplicationShortcutIcon+Contacts.h
//  ContactsUI
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Contacts/Contacts.h>
#import <UIKit/UIApplicationShortcutItem.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(9.0))
API_UNAVAILABLE(tvos)
API_UNAVAILABLE(macos, macCatalyst)
@interface UIApplicationShortcutIcon (ContactsUI)

+ (instancetype)iconWithContact:(CNContact *)contact;

@end

NS_ASSUME_NONNULL_END
