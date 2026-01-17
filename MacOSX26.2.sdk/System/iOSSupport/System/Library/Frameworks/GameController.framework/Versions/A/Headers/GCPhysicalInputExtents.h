//  
//  GCPhysicalInputExtents.h
//  GameController
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Physical extents scale the normalized value reported by `GCLinearInput`
 *  into physical units.
 */
API_AVAILABLE(macos(26.2), ios(26.2), tvos(26.2), visionos(26.2))
@protocol GCPhysicalInputExtents <NSObject>

/**
 *  The value of the input, scaled into physical units.
 */
@property (readonly) double scaledValue;

/**
 *  The minimum value for the physical extent of the input.
 */
@property (readonly) double minimumValue;

/**
 *  The maximum value for the physical extent of the input.
 */
@property (readonly) double maximumValue;

@end

NS_ASSUME_NONNULL_END
