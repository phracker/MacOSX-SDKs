//
//  HKWorkoutRouteQuery.h
//  HealthKit
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKWorkoutRoute;
@class CLLocation;

/*!
 @class         HKWorkoutRouteQuery
 @abstract      An HKWorkoutRouteQuery is used to access data associated with an HKWorkoutRoute.
 @discussion    Once instantiated, call HKHealthStore executeQuery to begin enumerating the route data. Call
                HKHealthStore stopQuery to discontinue further route data reporting.
 */
HK_EXTERN
#if defined(__swift__) && __swift__
API_DEPRECATED("Use HKWorkoutRouteQueryDescriptor", ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED));
#else
API_AVAILABLE(ios(11.0), watchos(4.0))
#endif
@interface HKWorkoutRouteQuery : HKQuery

/*!
 @method        initWithRoute:handler:
 @abstract      Returns a query that will retrieve CLLocation objects for the specified
 workoutRoute.
 
 @param workoutRoute    The HKWorkoutRoute for which the location data will be returned.
 @param dataHandler     The block to invoke with results from the query. It is called repeatedly with an array of
                        CLLocation objects until all data is returned and the done parameter is YES or if HKHealthStore
                        stopQuery: is called. The stopQuery call can be made within the dataHandler block. The number of
                        objects returned in routeData per dataHandler call is unspecified. Once done is YES, or
                        stopQuery called, the query is complete and no more calls to the handler will be made.
 */
- (instancetype)initWithRoute:(HKWorkoutRoute *)workoutRoute
                  dataHandler:(void(^)(HKWorkoutRouteQuery *query, NSArray<CLLocation *> * _Nullable routeData, BOOL done, NSError * _Nullable error))dataHandler NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
