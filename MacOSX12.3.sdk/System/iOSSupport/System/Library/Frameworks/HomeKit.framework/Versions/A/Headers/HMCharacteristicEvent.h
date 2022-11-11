//
//  HMCharacteristicEvent.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCharacteristic;

/*!
 * @brief This class represents an event that is evaluated based on the value of a characteristic
 *        set to a particular value.
 */
HM_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristicEvent<TriggerValueType : id<NSCopying>> : HMEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new characteristic event object
 *
 * @param characteristic The characteristic bound to the event. The characteristic must 
 *                       support notification. An exception will be thrown otherwise.
 *
 * @param triggerValue The value of the characteristic that triggers the event. 
 *                     Specifying nil as the trigger value corresponds to any change in the value of the
 *                     characteristic.
 *
 * @return Instance object representing the characteristic event.
 */
- (instancetype)initWithCharacteristic:(HMCharacteristic *)characteristic
                          triggerValue:(nullable TriggerValueType)triggerValue API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief The characteristic associated with the event.
 */
@property(readonly, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The value of the characteristic that triggers the event.
 *        A value of nil corresponds to any change in the value of the characteristic.
 */
@property(readonly, copy, nonatomic, nullable) TriggerValueType triggerValue;

/*!
 * @brief This method is used to change trigger value for the characteristic.
 *
 * @param triggerValue New trigger value for the characteristic.
 *                     Specifying nil as the trigger value corresponds to any change in the value of the
 *                     characteristic.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateTriggerValue:(nullable TriggerValueType)triggerValue completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("No longer supported.", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @brief This class represents an event that is evaluated based on the value of a characteristic
 *        set to a particular value.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableCharacteristicEvent<TriggerValueType : id<NSCopying>> : HMCharacteristicEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The characteristic associated with the event.
 */
@property(readwrite, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The value of the characteristic that triggers the event.
 *        A value of nil corresponds to any change in the value of the characteristic.
 */
@property(readwrite, copy, nonatomic, nullable) TriggerValueType triggerValue;

@end

NS_ASSUME_NONNULL_END
