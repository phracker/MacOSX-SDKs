/*
 *  CMStepCounter.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMStepQueryHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when the step count query is completed.
 */
typedef void (^CMStepQueryHandler)(NSInteger numberOfSteps, NSError * __nullable error) API_UNAVAILABLE(watchos, tvos);

/*
 *  CMStepUpdateHandler
 *
 *  Discussion:
 *      Typedef of block to be invoked on every update.  The total step count since startStepCountingUpdatesToQueue
 *      was called along with the timestamp associated with the latest determination will be returned.
 */
typedef void (^CMStepUpdateHandler)(NSInteger numberOfSteps, NSDate *timestamp, NSError * __nullable error) API_UNAVAILABLE(watchos);

/*
 *  CMStepCounter
 *
 *  Discussion:
 *      CMStepCounter allows access to the approximate number of steps a user has taken
 *      with a device.  Steps can be retrieved in one of two ways:
 *
 *      1. Via a query specifying a time range from which the approximate number of steps is
 *      tabulated and returned. (See queryStepCountStartingFrom:to:toQueue:withHandler)
 *
 *      2. By providing a queue and a block to startStepCountingUpdatesToQueue:withHandler,
 *      step count updates will be provided on a best effort basis.  Each update will return a
 *      monotonically increasing number of steps counted since
 *      startStepCountingUpdatesToQueue:withHandler was called and a timestamp
 *      associated with the latest stepcount determination.  Step count updates can be stopped
 *      by either calling stopStepCountingUpdates or upon CMStepCounter deallocation.
 *
 */
NS_CLASS_DEPRECATED_IOS(7_0,8_0,"Use CMPedometer instead") API_UNAVAILABLE(watchos)
@interface CMStepCounter : NSObject

/*
 *  isStepCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports step counting.
 */
+ (BOOL)isStepCountingAvailable;

/*
 *  queryStepCountStartingFrom:to:toQueue:withHandler
 *
 *  Discussion:
 *      Queries for the approximate number of steps taken in the given time range, for up to 7 days.
 *      The step count returned is computed from a system wide history that is continuously being
 *      collected in the background.  The result is returned to the handler/queue specified.
 */
- (void)queryStepCountStartingFrom:(NSDate *)start
                                to:(NSDate *)end
                           toQueue:(NSOperationQueue *)queue
                       withHandler:(CMStepQueryHandler)handler;

/*
 *  startStepCountingUpdatesToQueue:withHandler
 *
 *  Discussion:
 *       Starts a series of continuous step counting updates to the handler on the designated queue.  For each
 *       update, the app will receive the total step count since this method was called (this includes
 *       subsequent calls) and the timestamp associated with the latest determination.  If the app is backgrounded
 *       and resumed at a later time, the app will receive all of the steps counted during the background
 *       period in the very next update.  The handler will be called when the number of steps (as defined by
 *       the user) has been detected on a best effort basis.
 */
- (void)startStepCountingUpdatesToQueue:(NSOperationQueue *)queue
                               updateOn:(NSInteger)stepCounts
                            withHandler:(CMStepUpdateHandler)handler;


/*
 *  stopStepCountingUpdates
 *
 *  Discussion:
 *      Stops step counting updates.  Upon deallocation of CMStepCounter, this function will be
 *      automatically invoked if updates are still active and stopStepCountingUpdates has not been
 *      called.
 */
- (void)stopStepCountingUpdates;

@end

NS_ASSUME_NONNULL_END

