//
//  HKQuantitySeriesSampleBuilder.h
//  HealthKit
//
//  Copyright © 2018-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKDevice;
@class HKHealthStore;
@class HKQuantity;
@class HKQuantitySample;
@class HKQuantityType;

/*!
 @class         HKQuantitySeriesSampleBuilder
 @abstract      An HKQuantitySeriesSampleBuilder is used to generate HKQuantitySample(s) with multiple
                quantities.
 @discussion    An HKQuantitySeriesSampleBuilder is used to incrementally create a new quantity series
                sample in the HealthKit database. This class may be used to create long-running quantity
                series samples that are associated with an activity like a workout. After inserting each
                of the quantities that make up the series, the series may be finalized by calling
                -finishSeriesWithMetadata:completion:. Calling -discard invalidates the series and
                discards any data that was previously associated with it.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0))
@interface HKQuantitySeriesSampleBuilder : NSObject

/*!
 @method        initWithHealthStore:quantityType:device:
 @abstract      The designated initializer to create an HKQuantitySeriesSampleBuilder.
 @discussion    The HKHealthStore is retained during the life of the object for the saving of the
                series data and final return of the series sample.

 @param         healthStore     Specifies the HKHealthStore object to use for building the series.
 @param         quantityType    Specifies the quantity type for which to build the series.
 @param         startDate       The date from which the produced sample(s) start.
 @param         device          The optional device represents the HKDevice from which the data is
                                provided.
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                       quantityType:(HKQuantityType *)quantityType
                          startDate:(NSDate *)startDate
                             device:(nullable HKDevice *)device NS_SWIFT_NAME(init(healthStore:quantityType:startDate:device:));

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property      quantityType
 */
@property (readonly, copy) HKQuantityType *quantityType;

/*!
 @property      startDate
 */
@property (readonly, copy) NSDate *startDate;

/*!
 @property      device
 */
@property (readonly, copy, nullable) HKDevice *device;

/*!
 @method            insertQuantity:dateInterval:completion:
 @abstract          Associate a new quantity with the receiver with a specific date interval.
 @discussion        Use this method to add a quantity to the series. The quantity must have a unit
                    that is compatible with the receiver's quantity type.
                    See -[HKQuantityType isCompatibleWithUnit:].
                    Note that quantities may be inserted in any order,
                    but will be sorted by dateInterval.startDate when the series is finished.
 
 @param             quantity        The quantity to insert.
 @param             dateInterval    The dateInterval associated with the quantity.
                                    If dateInterval.startDate is the same as a previously-provided
                                    quantity, the new value will replace the old value.
                                    An HKErrorInvalidArgument will be returned if
                                    dateInterval.startDate is earlier than the receiver's startDate.
 */
- (BOOL)insertQuantity:(HKQuantity *)quantity
          dateInterval:(NSDateInterval *)dateInterval
                 error:(NSError **)error NS_SWIFT_NAME(insert(_:for:)) API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

/*!
 @method            insertQuantity:date:completion:
 @abstract          Associate a new quantity with the receiver at a specific instantaneous
                    date interval.
 @discussion        This method acts as a convenience for insertQuantity:dateInterval:completion:
                    where dateInterval has a duration of 0.

 @param             quantity    The quantity to insert.
 @param             date        The start date associated with the quantity. If this is the same
                                start date as a previously-provided quantity, the new value will
                                replace the old value. An HKErrorInvalidArgument will be returned
                                if date is earlier than the receiver's startDate.
 */
- (BOOL)insertQuantity:(HKQuantity *)quantity
                  date:(NSDate *)date
                 error:(NSError **)error NS_SWIFT_NAME(insert(_:at:));

/*!
 @method            finishSeriesWithMetadata:endDate:completion:
 @abstract          Finalizes the series and returns the resulting HKQuantitySample(s).
 @discussion        Call this method when all quantities for the series have been inserted.
                    The completion handler will return the resulting HKQuantitySample(s)
                    Note that it is possible for a single HKQuantitySeriesSampleBuilder to produce
                    multiple samples. If no quantity data was added, then samples will be nil and
                    an error will be returned. After calling this method, the receiver will be
                    considered invalid and calling any other method will result in an error.
 
 @param             metadata    Optional metadata may be added to associate with the series.
                                Predefined keys are found in HKMetadata.h, or custom NSString
                                keys used by the client are allowed. Acceptable metadata value types
                                are NSString, NSDate, NSNumber and HKQuantity.
 @param             endDate     Optional date at which the produced sample(s) end.
                                An HKErrorInvalidArgument will be returned if endDate
                                is earlier than the receiver's startDate,
                                or is earlier than the dateInterval.endDate of any inserted quantity.
 @param             completion  The completion handler will return the resulting HKQuantitySample(s)
                                for the series. Note that it is possible for a single
                                HKQuantitySeriesSampleBuilder to produce multiple samples.
                                If data could not be inserted because of an authorization failure,
                                samples will be nil and and an error with code
                                HKErrorAuthorizationDenied or HKErrorAuthorizationNotDetermined
                                will be returned. If the resulting sample(s) could not be accessed
                                after they have been created, then samples will be nil and an error
                                with code HKErrorDatabaseInaccessible will be returned. Any other
                                error indicates the resulting samples could not be returned.
                                After calling this method, the receiver will be considered invalid
                                and calling any other method will result in an error.
 */
- (void)finishSeriesWithMetadata:(nullable NSDictionary<NSString *, id> *)metadata
                         endDate:(nullable NSDate *)endDate
                      completion:(void(^)(NSArray<__kindof HKQuantitySample *> * _Nullable samples, NSError * _Nullable error))completion NS_SWIFT_NAME(finishSeries(metadata:endDate:completion:));

/*!
 @method            finishSeriesWithMetadata:completion:
 @abstract          Finalizes the series and returns the resulting HKQuantitySample(s).
 @discussion        Call this method when all quantities for the series have been inserted.
                    The completion handler will return the resulting HKQuantitySample(s)
                    Note that it is possible for a single HKQuantitySeriesSampleBuilder to produce
                    multiple samples. If no quantity data was added, then samples will be nil and
                    an error will be returned. This method functions as a convenience for
                    finishSeriesWithMetadata:endDate:completion: when endDate is nil.
                    After calling this method, the receiver will be considered invalid
                    and calling any other method will result in an error.

 @param             metadata    Optional metadata may be added to associate with the series.
                                Predefined keys are found in HKMetadata.h, or custom NSString
                                keys used by the client are allowed. Acceptable metadata value types
                                are NSString, NSDate, NSNumber and HKQuantity.
 @param             completion  The completion handler will return the resulting HKQuantitySample(s)
                                for the series. Note that it is possible for a single
                                HKQuantitySeriesSampleBuilder to produce multiple samples.
                                If data could not be inserted because of an authorization failure,
                                samples will be nil and and an error with code
                                HKErrorAuthorizationDenied or HKErrorAuthorizationNotDetermined
                                will be returned. If the resulting sample(s) could not be accessed
                                after they have been created, then samples will be nil and an error
                                with code HKErrorDatabaseInaccessible will be returned. Any other
                                error indicates the resulting samples could not be returned.
                                After calling this method, the receiver will be considered invalid
                                and calling any other method will result in an error.
 */
- (void)finishSeriesWithMetadata:(nullable NSDictionary<NSString *, id> *)metadata
                      completion:(void(^)(NSArray<__kindof HKQuantitySample *> * _Nullable samples, NSError * _Nullable error))completion NS_SWIFT_NAME(finishSeries(metadata:completion:));

/*!
 @method            discard
 @abstract          Discards all previously inserted data and invalidates the series.
 @discussion        Calling this method will delete all quantities that were previously inserted into
                    the series and invalidate the receiver. Calling other methods on the receiver
                    after calling -discard will result in an exception.
 */
- (void)discard;

@end

NS_ASSUME_NONNULL_END
