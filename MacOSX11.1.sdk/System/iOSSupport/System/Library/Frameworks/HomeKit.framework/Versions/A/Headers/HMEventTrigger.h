//
//  HMEventTrigger.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEventTriggerActivationState.h>
#import <HomeKit/HMSignificantTimeEvent.h>
#import <HomeKit/HMTrigger.h>

NS_ASSUME_NONNULL_BEGIN

@class HMEvent;
@class HMCharacteristic;
@class HMPresenceEvent;


/*!
 * @group Specifies a group of events that are deemed significant events in a day.
 *        These are also the key paths for the event in a NSPredicate.
 */

/*!
 * @brief Specifies the key path for a characteristic in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicKeyPath API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Specifies the key path for a characteristic value in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicValueKeyPath API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Specifies the key path for a presence event in a NSPredicate
 */
HM_EXTERN NSString * const HMPresenceKeyPath API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);


/*!
 * @brief Triggers based on events.
 *
 * @discussion This class represents a trigger that is based on events.
 */
HM_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMEventTrigger : HMTrigger

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new event trigger object.
 *
 * @param name Name of the event trigger.
 *
 * @param events Array of events that can trigger the evaluation of the trigger. Note: The trigger will
 *               be evaluated if any one of the events is true.
 *
 * @param predicate The predicate to evaluate before executing any of the actions sets associated to this
 *                  event.
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithName:(NSString *)name
                      events:(NSArray<HMEvent *> *)events
                   predicate:(nullable NSPredicate *)predicate API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Initializes a new event trigger object.
 *
 * @param name Name of the event trigger.
 *
 * @param events Array of events that can trigger the evaluation of the trigger. Note: The trigger will
 *               be evaluated if any one of the events is true.
 *
 * @param endEvents Array of end events that can trigger the restoration to the state before the scene was run.
 *
 * @param recurrences Specifies the days of the week when the trigger is to be evaluated. Only the 'weekday' property
 *                    is honored in NSDateComponents.
 *
 * @param predicate The predicate to evaluate before executing any of the actions sets associated to this
 *                  event.
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithName:(NSString *)name
                      events:(NSArray<HMEvent *> *)events
                   endEvents:(nullable NSArray<HMEvent *> *)endEvents
                 recurrences:(nullable NSArray<NSDateComponents *> *)recurrences
                   predicate:(nullable NSPredicate *)predicate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief The events associated with the trigger.
 */
@property(readonly, copy, nonatomic) NSArray<HMEvent *> *events;

/*!
 * @brief The events that correspond to executing the restore of the scene before the trigger was executed.
 *        E.g. Execute the scene for 10 mins and restore original state is achieved by specifying a corresponding
 *        HMDurationEvent in the list of endEvents.
 */
@property(readonly, copy, nonatomic) NSArray<HMEvent *> *endEvents API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief The predicate to evaluate before executing the action sets associated with the trigger.
 */
@property(readonly, copy, nonatomic, nullable) NSPredicate *predicate;

/*!
 * @brief recurrences Specifies the recurrences for when the trigger is evaluated. This only supports days of the week.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSDateComponents *> *recurrences API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Specifies whether this trigger is executed only once after which the trigger is disabled.
 */
@property(readonly, nonatomic) BOOL executeOnce API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Specifies the current activation state of the trigger.
 */
@property(readonly, assign, nonatomic) HMEventTriggerActivationState triggerActivationState API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));


/*!
 * @brief Adds a new event to the event trigger.
 *
 * @param event Event to add to the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("Use updateEvents:completionHandler: instead", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes the specified event from the event trigger.
 *
 * @param event Event to remove from the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("Use updateEvents:completionHandler: instead", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Updates the set of events in the event trigger.
 *
 * @param events Events to update in the event trigger
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateEvents:(NSArray<HMEvent *> *)events completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Updates the set of events in the event trigger.
 *
 * @param endEvents Events to update in the event trigger
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateEndEvents:(NSArray<HMEvent *> *)endEvents completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method replaces the predicate used to evaluate execution of the action sets associated with the trigger.
 *
 * @param predicate The new predicate for the event trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success. 
 */
- (void)updatePredicate:(nullable NSPredicate *)predicate completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method replaces the recurrences which secifies the days of the week when the trigger is to be evaluated.
 *
 * @param recurrences The new recurrences for the event trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success.
 */
- (void)updateRecurrences:(nullable NSArray<NSDateComponents *> *)recurrences completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method is used to update whether the event trigger repeats or not.
 *
 * @param executeOnce Specifies whether the event trigger is repeated or not.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateExecuteOnce:(BOOL)executeOnce completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

@interface HMEventTrigger(NSPredicate)

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *                         The valid values are: HMSignificantEventSunrise and HMSignificantEventSunset.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeSignificantEvent:(NSString *)significantEvent
                                                               applyingOffset:(nullable NSDateComponents *)offset API_DEPRECATED("Use predicateForEvaluatingTriggerOccurringBeforeSignificantEvent: instead", ios(9.0, 11.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeSignificantEvent:(HMSignificantTimeEvent *)significantEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred after a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *                         The valid values are: HMSignificantEventSunrise and HMSignificantEventSunset.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset after the significant event, the
 *               properties of the NSDateComponents must be positive value. e.g. To specify 30 mins after sunset, the
 *               'minute' property must be set to 30.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterSignificantEvent:(NSString *)significantEvent
                                                              applyingOffset:(nullable NSDateComponents *)offset API_DEPRECATED("Use predicateForEvaluatingTriggerOccurringAfterSignificantEvent: instead", ios(9.0, 11.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred after a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterSignificantEvent:(HMSignificantTimeEvent *)significantEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred between two significant events.
 *
 * @param firstSignificantEvent The first significant event.
 *
 * @param secondSignificantEvent The second significant event.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBetweenSignificantEvent:(HMSignificantTimeEvent *)firstSignificantEvent
                                                        secondSignificantEvent:(HMSignificantTimeEvent *)secondSignificantEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred at the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringOnDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred at or after the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred between two times.
 *
 * @param firstDateComponents The first date component.
 *
 * @param secondDateWithComponents The second date component.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBetweenDateWithComponents:(NSDateComponents *)firstDateComponents
                                                        secondDateWithComponents:(NSDateComponents *)secondDateWithComponents API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0));

/*!
 * @brief Creates a predicate that will evaluate whether a characteristic value is related to the specified value.
 *
 * @param characteristic The characteristic that is evaluated as part of the predicate.
 *
 * @param operatorType The relation between the characteristic and the target value. 
 *                     This can be either Less Than, Greater Than, Less Than or Equal, Greater Than or Equal, Equal, or Not Equal.
 *                     Anything else will cause an exception to be thrown.
 *
 * @param value The value of the characteristic to compare when evaluating the predicate.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerWithCharacteristic:(HMCharacteristic *)characteristic
                                                       relatedBy:(NSPredicateOperatorType)operatorType
                                                         toValue:(id)value;

/*!
 * @brief Creates a predicate that will evaluate based on the presence event.
 *
 * @param presenceEvent The presenceEvent that is evaluated as part of the predicate.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerWithPresence:(HMPresenceEvent *)presenceEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0));

@end

NS_ASSUME_NONNULL_END
