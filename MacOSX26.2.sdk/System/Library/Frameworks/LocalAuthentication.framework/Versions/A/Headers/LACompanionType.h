//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAPublicDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, LACompanionType)
{
    /// Paired Apple Watch
    LACompanionTypeWatch API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = kLACompanionTypeWatch,
    
    /// Paired Mac
    LACompanionTypeMac API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(macos, watchos, tvos, visionos) = kLACompanionTypeMac,
    
    /// Paired Vision Pro
    LACompanionTypeVision API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos, tvos, visionos) = kLACompanionTypeVision,
} API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0));

NS_ASSUME_NONNULL_END
