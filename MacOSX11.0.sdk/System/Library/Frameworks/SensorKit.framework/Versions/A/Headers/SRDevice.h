//
//  SRDeviceDescription.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos)
@interface SRDevice : NSObject <NSSecureCoding, NSCopying>

@property (class, readonly) SRDevice *currentDevice;

@property (readonly, copy) NSString *name;              // e.g. "My iPhone"
@property (readonly, copy) NSString *model;             // e.g. @"iPhone"
@property (readonly, copy) NSString *systemName;        // e.g. @"iOS"
@property (readonly, copy) NSString *systemVersion;     // e.g. @"4.0"

@end

NS_ASSUME_NONNULL_END
