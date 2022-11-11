//
//  HKElectrocardiogramQuery.h
//  HealthKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <HealthKit/HKElectrocardiogram.h>
#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class         HKElectrocardiogramVoltageMeasurement
@abstract      An HKElectrocardiogramVoltageMeasurement contains voltage quantities for all leads at a single instance of measurement.
@discussion    Each HKElectrocardiogramVoltageMeasurement object corresponds to the voltage quantities across all leads for a given instance in time.
*/
HK_EXTERN API_AVAILABLE(ios(14.0), watchos(7.0)) NS_SWIFT_NAME(HKElectrocardiogram.VoltageMeasurement)
@interface HKElectrocardiogramVoltageMeasurement : NSObject

/*!
 The time interval between this voltage measurement and the start of the sample.
*/
@property (nonatomic, readonly, assign) NSTimeInterval timeSinceSampleStart;

/*!
@method        quantityForLead:
@abstract      Returns an HKQuantity for the specified lead with a unit compatible with [HKUnit voltageUnit].

@param         lead      The HKElectrocardiogramLead for which voltage quantity will be returned.
*/
- (nullable HKQuantity *)quantityForLead:(HKElectrocardiogramLead)lead;

@end

/*!
@class         HKElectrocardiogramQuery
@abstract      An HKElectrocardiogramQuery is used to access voltage data associated with an HKElectrocardiogram.
@discussion    Once instantiated, call HKHealthStore executeQuery to begin enumerating the HKElectrocardiogram voltage data.
*/
HK_EXTERN API_AVAILABLE(ios(14.0), watchos(7.0))
@interface HKElectrocardiogramQuery : HKQuery

/*!
@method        initWithElectrocardiogram:dataHandler:
@abstract      Returns a query that will enumerate over voltages recorded across leads in
               an electrocardiogram.
 
 @param         electrocardiogram    The sample for which the lead data will be returned.
 @param         dataHandler          The block to invoke with results from the query. It will be called once for each voltage measurement. Call [query stop] to stop enumeration, if desired.

*/
- (instancetype)initWithElectrocardiogram:(HKElectrocardiogram *)electrocardiogram
                             dataHandler:(void (^)(HKElectrocardiogramQuery *query, HKElectrocardiogramVoltageMeasurement * _Nullable voltageMeasurement, BOOL done, NSError * _Nullable error))dataHandler NS_SWIFT_NAME(init(electrocardiogram:dataHandler:)) NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
