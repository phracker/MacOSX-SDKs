//
//  NSLocalizedNumberFormatRule.h
//  Foundation
//
//  Copyright (c) 2024, Apple Inc.
//  All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0))
NS_REFINED_FOR_SWIFT
@interface NSLocalizedNumberFormatRule : NSObject <NSCopying, NSSecureCoding>

+ (id)new NS_UNAVAILABLE;
- (id)init NS_UNAVAILABLE;

+ (NSLocalizedNumberFormatRule *)automatic;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

