//
//  SLComposeSheetConfigurationItem.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Social/SocialDefines.h>
#import <Foundation/Foundation.h>

typedef void (^SLComposeSheetConfigurationItemTapHandler)(void);

// Represents a user-configurable option for the compose session.
// For allowing the user to choose which account to post from, what privacy settings to use, etc.
SOCIAL_CLASS_AVAILABLE(NA, 8_0)
@interface SLComposeSheetConfigurationItem : NSObject

// Designated initializer
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSString *title; // The displayed name of the option.
@property (nonatomic, copy) NSString *value; // The current value/setting of the option.
@property (nonatomic, assign) BOOL valuePending; // Default is NO. set to YES to show a progress indicator. Can be used with a value too.

// Called on the main queue when the configuration item is tapped.
// Your block should not keep a strong reference to either the configuration item, or the SLComposeServiceViewController, otherwise you'll end up with a retain cycle.
@property (nonatomic, copy) SLComposeSheetConfigurationItemTapHandler tapHandler;

@end
