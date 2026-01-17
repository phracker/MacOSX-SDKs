/*!
 *  @header MPSAccelerationStructureGroup.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector acceleration structure group interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSAccelerationStructureGroup_h
#define MPSAccelerationStructureGroup_h

#import <MPSCore/MPSKernel.h>

/**
 * @brief A group of acceleration structures which may be used together in an instance acceleration
 * structure.
 *
 * @discussion All acceleration structures in an instance acceleration structures must be created
 * with the same group, although they do not all need to be used in the same instance acceleration
 * structure. The acceleration structures in a group share internal GPU memory allocations, so
 * the total number and size of acceleration structures that can be created with the same group is
 * limited by the Metal device's buffer size limits. Therefore, do not group acceleration
 * structures unless they are likely to be used in the same instance acceleration structure.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface MPSAccelerationStructureGroup : NSObject

/**
 * @brief The Metal device this acceleration structure group was created with
 */
@property (nonatomic, readonly) id <MTLDevice> _Nonnull device;

- (nonnull instancetype)init NS_UNAVAILABLE;

- (nonnull instancetype)initWithDevice:(id <MTLDevice> _Nonnull)device;

@end

#endif
