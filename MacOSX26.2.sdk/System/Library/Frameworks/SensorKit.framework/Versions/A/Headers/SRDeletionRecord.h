//
//  SRDeletionRecord.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <SensorKit/SRAbsoluteTime.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SRDeletionReason) {
    /// The user initiated deletion
    SRDeletionReasonUserInitiated,

    /// Samples were removed due to low disk conditions
    SRDeletionReasonLowDiskSpace,

    /// Samples were removed because they were recorded beyond our retention limit
    SRDeletionReasonAgeLimit,

    /// Samples were removed because there are no longer any interested clients
    SRDeletionReasonNoInterestedClients,

    /// Samples were removed because the system was in an invalid state
    SRDeletionReasonSystemInitiated,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos) 
@interface SRDeletionRecord : NSObject <NSSecureCoding>
@property (readonly) SRAbsoluteTime startTime;
@property (readonly) SRAbsoluteTime endTime;
@property (readonly) SRDeletionReason reason;
@end

NS_ASSUME_NONNULL_END
