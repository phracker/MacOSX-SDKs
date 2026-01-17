//
//  HMCharacteristicNumberRangeEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCharacteristic;
@class HMNumberRange;

/*!
 * @brief This class represents an event when a characteristic's value falls within the specified 
 * number range.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristicThresholdRangeEvent : HMEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new characteristic number range event object
 *
 * @param characteristic The characteristic bound to the event. The characteristic must
 *                       support notification. An exception will be thrown otherwise.
 *
 * @param thresholdRange The range for the characteristic value to trigger the event.
 *
 * @return Instance object representing the characteristic event.
 */
- (instancetype)initWithCharacteristic:(HMCharacteristic *)characteristic
                        thresholdRange:(HMNumberRange *)thresholdRange;

/*!
 * @brief The characteristic associated with the event.
 */
@property(readonly, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The range of the characteristic value that triggers the event.
 */
@property(readonly, copy, nonatomic) HMNumberRange *thresholdRange;

@end


/*!
 * @brief This class represents an event when a characteristic's value falls within the specified
 * number range.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableCharacteristicThresholdRangeEvent : HMCharacteristicThresholdRangeEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The characteristic associated with the event.
 */
@property(readwrite, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The range of the characteristic value that triggers the event.
 */
@property(readwrite, copy, nonatomic) HMNumberRange *thresholdRange;

@end

NS_ASSUME_NONNULL_END
