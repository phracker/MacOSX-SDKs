//
//  HKQueryDescriptor.h
//  HealthKit
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKObjectType.h>

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(15.0), watchos(8.0))
@interface HKQueryDescriptor : NSObject<NSCopying, NSSecureCoding>

/*!
 @property      sampleType
 @abstract      The type of sample to retrieve in an HKQuery.
 */
@property (nonatomic, readonly, copy) HKSampleType *sampleType;

/*!
 @property      predicate
 @abstract      The predicate which samples should match.
 */
@property (nonatomic, readonly, copy, nullable) NSPredicate *predicate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @method        initWithSampleType:predicate:
 @abstract      Returns a query descriptor that describes a data type and predicate to be used in an HKQuery.
 
 @param         sampleType      The type of sample to retrieve.
 @param         predicate       The predicate which samples should match.
*/
- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                         predicate:(nullable NSPredicate *)predicate NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
