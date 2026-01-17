//
//  HKObject.h
//  HealthKit
//
//  Copyright (c) 2014-2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSource;
@class HKSourceRevision;
@class HKDevice;

HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      A unique identifier of the receiver in the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

@property (readonly, strong) HKSource *source API_DEPRECATED_WITH_REPLACEMENT("sourceRevision", ios(8.0, 9.0));

/*!
 @property      sourceRevision
 @abstract      Represents the revision of the source responsible for saving the receiver.
 */
@property (readonly, strong) HKSourceRevision *sourceRevision API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @property      device
 @abstract      Represents the device that generated the data of the receiver.
 */
@property (readonly, strong, nullable) HKDevice *device API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, NSDate, or
                HKQuantity. See HKMetadata.h for potential metadata keys and values.
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata;

- (instancetype)init NS_UNAVAILABLE;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathUUID API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathSource API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathMetadata API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathCorrelation API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkout API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathDevice API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathSourceRevision API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutEffortRelationship API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

NS_ASSUME_NONNULL_END
