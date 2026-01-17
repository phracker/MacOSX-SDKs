//
//  HKObserverQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^HKObserverQueryCompletionHandler)(void);

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKObserverQuery : HKQuery

/*!
 @method        initWithSampleType:predicate:updateHandler:
 @abstract      This method installs a handler that is called when a sample type has a new sample added.
 @discussion    If you have subscribed to background updates you must call the passed completion block
                once you have processed data from this notification. Otherwise the system will continue
                to notify you of this data.
 */

- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                         predicate:(nullable NSPredicate *)predicate
                     updateHandler:(void(^)(HKObserverQuery *query, HKObserverQueryCompletionHandler completionHandler, NSError * _Nullable error))updateHandler;

@end

NS_ASSUME_NONNULL_END
