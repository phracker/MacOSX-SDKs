//
//  HKCategorySample.h
//  HealthKit
//
//  Copyright (c) 2014-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKObject.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKCategoryType;

/*!
 @class      HKCategorySample
 @abstract   An HKObject subclass representing an category measurement
 @discussion Category samples are samples that can be categorized into an enum of concrete values
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKCategorySample : HKSample

@property (readonly, strong) HKCategoryType *categoryType;

/*!
 @property   value
 @discussion The preferred enum for the value is determined by the receiver's category type.
 */
@property (readonly) NSInteger value;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method     categorySampleWithType:value:startDate:endDate:metadata:
 @abstract   Creates a new HKCategorySample.
 
 @param      type       The type of the sample.
 @param      value      The enumeration value for the sample. See HKCategoryTypeIdentifier for appropriate value.
 @param      startDate  The start date of the sample.
 @param      endDate    The end date of the sample.
 @param      metadata   Metadata for the sample (optional).
 */
+ (instancetype)categorySampleWithType:(HKCategoryType *)type
                                 value:(NSInteger)value
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method     categorySampleWithType:value:startDate:endDate:
 @abstract   Creates a new HKCategorySample.
 
 @param      type       The type of the sample.
 @param      value      The enumeration value for the sample. See HKCategoryTypeIdentifier for appropriate value.
 @param      startDate  The start date of the sample.
 @param      endDate    The end date of the sample.
 */
+ (instancetype)categorySampleWithType:(HKCategoryType *)type
                                 value:(NSInteger)value
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate;

/*!
 @method     categorySampleWithType:value:startDate:endDate:device:metadata:
 @abstract   Creates a new HKCategorySample.
 
 @param      type       The type of the sample.
 @param      value      The enumeration value for the sample. See HKCategoryTypeIdentifier for appropriate value.
 @param      startDate  The start date of the sample.
 @param      endDate    The end date of the sample.
 @param      device     The HKDevice that generated the sample (optional).
 @param      metadata   Metadata for the sample (optional).
 */
+ (instancetype)categorySampleWithType:(HKCategoryType *)type
                                 value:(NSInteger)value
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                                device:(nullable HKDevice *)device
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

@end

/*!
 @constant     HKPredicateKeyPathCategoryValue
 */
HK_EXTERN NSString * const HKPredicateKeyPathCategoryValue API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
