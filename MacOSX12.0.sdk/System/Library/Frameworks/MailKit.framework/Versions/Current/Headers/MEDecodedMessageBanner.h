//
//  MEDecodedMessageBanner.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Contains security information in order to populate a banner in the message view.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@interface MEDecodedMessageBanner : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic, readonly, strong) NSString *title;
@property (nonatomic, readonly, strong) NSString *primaryActionTitle;
@property (nonatomic, readonly, getter=isDismissable) BOOL dismissable;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithTitle:(NSString *)title primaryActionTitle:(NSString *)primaryActionTitle dismissable:(BOOL)dismissable;
@end

NS_ASSUME_NONNULL_END
