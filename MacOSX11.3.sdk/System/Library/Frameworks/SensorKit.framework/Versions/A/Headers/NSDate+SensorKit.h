//
//  NSDate+SensorKit.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRAbsoluteTime.h>

NS_ASSUME_NONNULL_BEGIN

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface NSDate (SensorKit)

+ (instancetype)dateWithSRAbsoluteTime:(SRAbsoluteTime)time;
- (instancetype)initWithSRAbsoluteTime:(SRAbsoluteTime)time;

@property (readonly) SRAbsoluteTime srAbsoluteTime;

@end

NS_ASSUME_NONNULL_END
