//
//  HKLiveWorkoutDataSource.h
//  HealthKit
//
//  Copyright © 2017-2025  Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKWorkoutBuilder.h>

NS_ASSUME_NONNULL_BEGIN

@class HKWorkoutConfiguration;
@class HKQuantityType;

/*!
 @class         HKLiveWorkoutDataSource
 @discussion    An HKLiveWorkoutDataSource is to be used with an HKWorkoutBuilder to automatically collect samples
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(5.0)) API_UNAVAILABLE(visionos)
@interface HKLiveWorkoutDataSource : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property      typesToCollect
 @abstract      The quantity types the receiver is collecting.
 */
@property (copy, readonly) NSSet<HKQuantityType *> *typesToCollect API_AVAILABLE(ios(26.0), watchos(5.0));

/*!
 @method        initWithHealthStore:workoutConfiguration:
 @abstract      The designated initializer of HKLiveWorkoutDataSource.
 
 @param         healthStore     The HKHealthStore. This should match the one used to create the corresponding
                                HKWorkoutBuilder.
 @param         configuration   An optional workout configuration. typesToCollect will be populated with default
                                types for the workout configuration
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
               workoutConfiguration:(nullable HKWorkoutConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

/*!
 @method        enableCollectionForType:predicate
 @abstract      Adds a new type of quantity sample to collect.
 @discussion    Calling this method for a type that is already being collected will override the predicate for that type.
 
 @param         quantityType    The type of sample to collect.
 @param         predicate       If non-nil, collected samples must match this predicate.
 */
- (void)enableCollectionForType:(HKQuantityType *)quantityType
                      predicate:(nullable NSPredicate *)predicate;

/*!
 @method        disableCollectionForType:
 @abstract      Removes the specified quantity type from the types to collect.
 
 @param         quantityType    The type of sample to no longer collect.
 */
- (void)disableCollectionForType:(HKQuantityType *)quantityType;

@end

NS_ASSUME_NONNULL_END
