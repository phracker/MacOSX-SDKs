//
//  MEEmailAddress.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos)
/// @brief Contain information about an email address. This can include both valid and invalid email addresses.
@interface MEEmailAddress : NSObject <NSSecureCoding, NSCopying>
/// @brief The raw string for the email address.
@property (nonatomic, readonly, copy) NSString *rawString;
/// @brief The simple address string portion of the raw string if it is valid. For example, the  @c addressString
/// of "John Appleseed <j.appleseed@example.com>" will be "j.appleseed@example.com".
@property (nonatomic, nullable, readonly, copy) NSString *addressString;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithRawString:(NSString *)rawString;

@end

NS_ASSUME_NONNULL_END
