//
//  CPInformationItem.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPInformationItem : NSObject <NSSecureCoding>

/**
 Initializes a new  item to be used with @c CPInformationTemplate.
 
 @param title An optional string that will be styled by the template as the title text of the item.
 @param detail An optional string that will be styled by the template as the detail text of the item.
 */
- (instancetype)initWithTitle:(nullable NSString *)title detail:(nullable NSString *)detail NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, nullable) NSString *title;
@property (nonatomic, readonly, nullable) NSString *detail;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
