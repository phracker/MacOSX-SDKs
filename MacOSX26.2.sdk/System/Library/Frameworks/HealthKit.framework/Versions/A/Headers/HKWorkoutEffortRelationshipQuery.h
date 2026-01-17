//
//  HKWorkoutEffortRelationshipQuery.h
//  HealthKit
//
//  Copyright © 2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKQuery.h>
#import <HealthKit/HKQueryAnchor.h>
#import <HealthKit/HKQueryDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKWorkoutEffortRelationship : NSObject<NSSecureCoding, NSCopying>

/*!
 @property      workout
 */
@property (nonatomic, readonly, copy) HKWorkout *workout;

/*!
 @property      activity
 */
@property (nonatomic, readonly, copy, nullable) HKWorkoutActivity *activity;

/*!
 @property      samples
 @abstract      The samples related to the workout but not any sub-activities
 */
@property (nonatomic, readonly, copy, nullable) NSArray<HKSample *> *samples;

@end

/*!
 @enum          HKWorkoutEffortRelationshipQueryOptions
 @abstract      Option for specifying which workout effort relationship sample(s) to retrieve
 
 @constant      HKWorkoutEffortRelationshipQueryOptionsDefault
 @constant      HKWorkoutEffortRelationshipQueryOptionsMostRelevant The most relevant sample will be returned
 */
typedef NS_ENUM(NSInteger, HKWorkoutEffortRelationshipQueryOptions) {
    HKWorkoutEffortRelationshipQueryOptionsDefault = 0,
    HKWorkoutEffortRelationshipQueryOptionsMostRelevant = 1 << 0,
} API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/*!
 @class         HKWorkoutEffortRelationshipQuery
 @abstract      A concrete subclass of HKQuery that provides an interface to observe associations with a workout sample.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKWorkoutEffortRelationshipQuery : HKQuery

/*!
 @method        initWithPredicate:anchor:options:
 @abstract      Returns a query that will retrieve HKWorkoutEffortRelationship matching the given predicate that are
                newer than the given anchor.
 @discussion    This is a long running query and it is the responsibility of the caller to stop the query
                after they have received the results they desire.
                The first call to resultsHandler will contain the inital results which may be empty and future callbacks
                will contain new relationships as well as any changes to previous relationships along with a new anchor
 @param         predicate       The predicate on the workout(s) which samples should match.
 @param         anchor          The anchor which was returned by a previous HKWorkoutEffortRelationshipQuery result or update
                                handler.  Pass nil when querying for the first time.
 @param         options         The options for the query, one of types from `HKWorkoutEffortRelationshipQueryOptions`
 @param         resultsHandler         The block to invoke with related sample results
 */
- (instancetype)initWithPredicate:(nullable NSPredicate *)predicate
                           anchor:(nullable HKQueryAnchor *)anchor
                          options:(HKWorkoutEffortRelationshipQueryOptions)options 
                   resultsHandler:(void(^NS_SWIFT_SENDABLE)(HKWorkoutEffortRelationshipQuery *query, NSArray<HKWorkoutEffortRelationship *> * _Nullable relationships, HKQueryAnchor * _Nullable newAnchor, NSError * _Nullable error))resultsHandler;
@end

NS_ASSUME_NONNULL_END
