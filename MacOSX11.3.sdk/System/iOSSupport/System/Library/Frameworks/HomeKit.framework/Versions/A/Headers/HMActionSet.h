//
//  HMActionSet.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAction;
@class HMCharacteristic;


/*!
 * @brief This class represents a collection of action objects that can be executed. 
 *        The order of execution of these actions is undefined.
 */             
HM_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMActionSet : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The name of the action set.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Set of HMAction objects that represent the individual items of the action set.
 */
@property(readonly, copy, nonatomic) NSSet<HMAction *> *actions;

/*!
 * @brief Specifies whether the action set is currently executing or not.
 */
@property(readonly, getter=isExecuting, nonatomic) BOOL executing;

/*!
 * @brief Specifies the action set type - user-defined, trigger-owned or one of the builtin types.
 *        Builtin action sets cannot be removed from the home. trigger-owned action sets cannot
 *        be executed, renamed or associated with another trigger.
 */
@property(readonly, copy, nonatomic) NSString * actionSetType API_AVAILABLE(ios(9.0));

/*!
 * @brief A unique identifier for the action set.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief Specifies the last execution date for the action set.
 */
@property(readonly, copy, nonatomic, nullable) NSDate *lastExecutionDate API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @brief This method is used to change the name of the action set.
 *
 * @param name New name for the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(HMErrorBlock)completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Adds an action to the action set.
 *
 * @param action Action object to add to the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAction:(HMAction *)action completionHandler:(HMErrorBlock)completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an existing action from the action set.
 *
 * @param action Action object to remove from the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeAction:(HMAction *)action completionHandler:(HMErrorBlock)completion API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @brief Builtin action set type for WakeUp.
 */

HM_EXTERN NSString * const HMActionSetTypeWakeUp API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for builtin action set Sleep.
 */
HM_EXTERN NSString * const HMActionSetTypeSleep API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for builtin action set HomeDeparture.
 */
HM_EXTERN NSString * const HMActionSetTypeHomeDeparture API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for builtin action set HomeArrival.
 */
HM_EXTERN NSString * const HMActionSetTypeHomeArrival API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for user-defined action sets.
 */
HM_EXTERN NSString * const HMActionSetTypeUserDefined API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for trigger-owned action sets.
 *
 * @discussion An action set of this type is owned by a trigger and is not listed
 *             as part of the home. An action set of this type cannot be executed,
 *             renamed, or associated with a different trigger.
 */
HM_EXTERN NSString * const HMActionSetTypeTriggerOwned API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
