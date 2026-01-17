//
//  CPLane.h
//  CarPlay
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CPLaneStatus)
{
    CPLaneStatusNotGood = 0,
    CPLaneStatusGood,
    CPLaneStatusPreferred
} API_AVAILABLE(ios(17.4));

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPLane represents information about a single lane.
 */
API_AVAILABLE(ios(17.4))
@interface CPLane : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init API_DEPRECATED("-[CPLane initWithAngles:] or -[CPLane initWithHighlightedAngle:angles:isPreferred:]", ios(17.4, 18.0));
- (instancetype)initWithAngles:(NSArray<NSMeasurement<NSUnitAngle *> *> *)angles API_AVAILABLE(ios(18.0));
- (instancetype)initWithAngles:(NSArray<NSMeasurement<NSUnitAngle *> *> *)angles highlightedAngle:(NSMeasurement<NSUnitAngle *> *)highlightedAngle isPreferred:(BOOL)preferred API_AVAILABLE(ios(18.0));

/**
 status is a @c CPLaneStatus representing the status of this lane.
 */
@property (nonatomic, assign) CPLaneStatus status API_AVAILABLE(ios(17.4));
- (void)setStatus:(CPLaneStatus)status API_DEPRECATED("Use -[CPLane initWithAngles:] to create a CPLane with CPLaneStatusNotGood, use -[CPLane initAngles:highlightedAngle:isPreferred:] to create a CPLane with status CPLaneStatusGood or CPLaneStatusPreferred", ios(17.4, 18.0));

/**
 primaryAngle is the angle to be highlighted if this lane is preferred or good. If primaryAngle is present it can not be included in secondaryAngles.
 */
@property (nonatomic, strong) NSMeasurement<NSUnitAngle *> *primaryAngle API_DEPRECATED("Use highlightedAngle to get value, use -[CPLane initAngles:highlightedAngle:isPreferred:] to create a CPLane with highlightedAngle set", ios(17.4, 18.0));

/**
 @c highlightedAngle is the angle to be highlighted. If @c highlightedAngle is present it can not be included in @c angles. @c highlightedAngle must not be set if status is @c CPLaneStatusNotGood
 */
@property (nonatomic, strong, nullable, readonly) NSMeasurement<NSUnitAngle *> *highlightedAngle API_AVAILABLE(ios(18.0));

/**
 secondaryAngles is a list of the remaining angles of this lane guidance.
 */
@property (nonatomic, strong) NSArray<NSMeasurement<NSUnitAngle *> *> *secondaryAngles API_DEPRECATED("Use angles to get value, Use -[CPLane initWithAngles:] or -[CPLane initAngles:highlightedAngle:isPreferred:] to create a CPLane with angles", ios(17.4, 18.0));

/**
 @c angles is a list of the remaining angles of this lane guidance. If @c highlightedAngle is set, that angle must not be included in @c angles
 */
@property (nonatomic, copy, readonly) NSArray<NSMeasurement<NSUnitAngle *> *> *angles API_AVAILABLE(ios(18.0));

@end

NS_ASSUME_NONNULL_END
