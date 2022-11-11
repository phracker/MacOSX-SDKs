//
//  MEAddressAnnotation.h
//  MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief An instance of this class can be used to change the visual style of recipeint email address token when user in composing a mail message.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@interface MEAddressAnnotation : NSObject <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// @brief An annotation to denote a recipeint email address has an error when composing a mail message.
/// @param localizedDescription - A localized string with a brief description of the error that may be presented to the user.
+ (MEAddressAnnotation *)errorWithLocalizedDescription:(NSString *)localizedDescription;

/// @brief An annotation to warn about a recipeint email address when composing a mail message.
/// @param localizedDescription - A localized string with a brief description of the warning may be presented to the user. .
+ (MEAddressAnnotation *)warningWithLocalizedDescription:(NSString *)localizedDescription;

/// @brief An annotation to  denote a valid recipeint email address when composing a mail message.
/// @param localizedDescription - A localized string with a brief description that may be presented to the user. .
+ (MEAddressAnnotation *)successWithLocalizedDescription:(NSString *)localizedDescription;

@end

NS_ASSUME_NONNULL_END
