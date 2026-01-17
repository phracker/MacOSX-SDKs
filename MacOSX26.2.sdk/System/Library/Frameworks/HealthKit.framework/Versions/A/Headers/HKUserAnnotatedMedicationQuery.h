//
//  HKUserAnnotatedMedicationQuery.h
//  HealthKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <HealthKit/HKQuery.h>

@class HKUserAnnotatedMedication;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKUserAnnotatedMedicationQuery : HKQuery

/*!
@method        initWithPredicate:limit:resultsHandler:
@abstract      Returns a query that will retrieve HKUserAnnotatedMedications matching the given predicate and limit.

@param         predicate       The predicate which user annotated medications should match.
@param         limit           The maximum number of  user annotated medications to return.  Pass HKObjectQueryNoLimit for no limit.
@param         resultsHandler  The block to invoke with results to deliver to the client. The results handler will be called with done = YES when there are no more user annotated medications to enumerate.
*/
- (instancetype)initWithPredicate:(nullable NSPredicate *)predicate
                            limit:(NSUInteger)limit
                   resultsHandler:(void (^)(HKUserAnnotatedMedicationQuery *query,
                                            __kindof HKUserAnnotatedMedication * _Nullable userAnnotatedMedication,
                                            BOOL done,
                                            NSError * _Nullable error))resultsHandler;

@end

NS_ASSUME_NONNULL_END
