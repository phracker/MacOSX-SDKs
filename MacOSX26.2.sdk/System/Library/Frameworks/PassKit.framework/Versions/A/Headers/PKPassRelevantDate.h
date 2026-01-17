#if !__has_include(<PassKitCore/PKPassRelevantDate.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPassRelevantDate.h
//    PassKit
//
//  Copyright © 2023 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@interface PKPassRelevantDate : NSObject

@property (nonatomic, nullable, copy, readonly) NSDateInterval *interval;
@property (nonatomic, nullable, copy, readonly) NSDate *date;

@end

@interface PKPassRelevantDate ()

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end
NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKPassRelevantDate.h>
#endif