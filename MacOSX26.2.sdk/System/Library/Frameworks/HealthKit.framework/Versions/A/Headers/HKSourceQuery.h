//
//  HKSourceQuery.h
//  HealthKit
//
//  Copyright (c) 2014-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKSourceQuery
 @abstract      A query that returns a set of sources that have saved objects matching certain criteria.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
#if defined(__swift__) && __swift__
API_DEPRECATED("Use HKSourceQueryDescriptor", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
#else
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
#endif
@interface HKSourceQuery : HKQuery

/*!
 @method        initWithSampleType:samplePredicate:completionHandler:
 @abstract      Returns a query that will retrieve HKSources that have saved samples of the given type matching the 
                given predicate.
 
 @param         sampleType          The type of sample.
 @param         objectPredicate     The predicate which samples must match.
 @param         completionHandler   The block to be called when the query has finished executing.
 */
- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                   samplePredicate:(nullable NSPredicate *)objectPredicate
                 completionHandler:(void(^NS_SWIFT_SENDABLE)(HKSourceQuery *query, NSSet<HKSource *> * _Nullable sources, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
