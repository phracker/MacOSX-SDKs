//
//  CMAmbientPressure.h
//  CMAmbientPressure
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.
//

#import <CoreMotion/CMLogItem.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMAmbientPressureData
 *
 *  Discussion:
 *    Contains a single pressure measurement.
 *
 */
COREMOTION_EXPORT API_AVAILABLE(ios(10.0))
@interface CMAmbientPressureData : CMLogItem

/**
 *  Discussion:
 *    The pressure as measured by the pressure sensor.
 *    Pressure is in kPa (kilopascals).
 */
@property(readonly, strong, nonatomic) NSMeasurement<NSUnitPressure *> *pressure;

/**
 *  Discussion:
 *    The temperature as measured by the pressure sensor.
 *    Temperature is in C (degrees centrigrade).
 */
@property(readonly, strong, nonatomic) NSMeasurement<NSUnitTemperature *> *temperature;

@end

NS_ASSUME_NONNULL_END
