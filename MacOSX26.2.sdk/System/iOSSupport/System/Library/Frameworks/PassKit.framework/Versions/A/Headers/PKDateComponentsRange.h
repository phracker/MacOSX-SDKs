#if !__has_include(<PassKitCore/PKDateComponentsRange.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKDateComponentsRange.h
//    PassKit
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#ifndef __PKDATECOMPONENTSRANGE_H
#define __PKDATECOMPONENTSRANGE_H

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), watchos(8.0))
@interface PKDateComponentsRange : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
// The date components must have valid dates and a calendar.
- (nullable instancetype)initWithStartDateComponents:(NSDateComponents *)startDateComponents
                          endDateComponents:(NSDateComponents *)endDateComponents;

@property (copy, readonly, nonatomic) NSDateComponents *startDateComponents;
@property (copy, readonly, nonatomic) NSDateComponents *endDateComponents;

@end

NS_ASSUME_NONNULL_END

#endif

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKDateComponentsRange.h>
#endif