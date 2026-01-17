//
//  HKAudiogramSample.h
//  HealthKit
//
//  Copyright © 2017-2024 Apple. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKQuantity.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKAudiogramSensitivityPoint;
@class HKAudiogramSensitivityPointClampingRange;

/*!
 @class     HKAudiogramSample
 @abstract  A sample object representing the results of a standard hearing test.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0))
@interface HKAudiogramSample : HKSample

/*!
 @property  sensitivityPoints
 @abstract  The hearing sensitivity readings associated with a hearing test.
 */
@property (readonly, copy) NSArray<HKAudiogramSensitivityPoint *> *sensitivityPoints;
/*!
 @method                   audiogramSampleWithSensitivityPoints:startDate:endDate:metadata:
 @abstract                 Creates a new audiogram sample with the specified attributes.
 @param sensitivityPoints  Sensitivity data associated with the sample, with a maximum limit of 30 points. Frequencies must be unique, and ordered ascending.
 @param startDate          The start date for the hearing test.
 @param endDate            The end date for the hearing test.
 @param metadata           Optional meta data associated with the sample.
 @return                   A new instance of an audiogram sample.
 */
+ (instancetype)audiogramSampleWithSensitivityPoints:(NSArray<HKAudiogramSensitivityPoint *> *)sensitivityPoints
                                           startDate:(NSDate *)startDate
                                             endDate:(NSDate *)endDate
                                            metadata:(nullable NSDictionary<NSString *, id> *)metadata API_DEPRECATED_WITH_REPLACEMENT("+[HKAudiogramSample audiogramSampleWithSensitivityPoints:startDate:endDate:device:metadata:]", ios(13.0, 18.1), watchos(6.0, 11.1));
/*!
 @method                   audiogramSampleWithSensitivityPoints:startDate:endDate:device:metadata:
 @abstract                 Creates a new audiogram sample with the specified attributes.
 @param sensitivityPoints  Sensitivity data associated with the sample, with a maximum limit of 30 points. Frequencies must be unique, and ordered ascending.
 @param startDate          The start date of the hearing test.
 @param endDate            The end date of the hearing test.
 @param device             The device that generated the sample data.
 @param metadata           Optional metadata associated with the sample.
 @return                   A new instance of an audiogram sample.
 */
+ (instancetype)audiogramSampleWithSensitivityPoints:(NSArray<HKAudiogramSensitivityPoint *> *)sensitivityPoints
                                           startDate:(NSDate *)startDate
                                             endDate:(NSDate *)endDate
                                              device:(nullable HKDevice *)device
                                            metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(18.1), watchos(11.1), macCatalyst(18.1), macos(15.1), visionos(2.1));

@end

NS_ASSUME_NONNULL_END

