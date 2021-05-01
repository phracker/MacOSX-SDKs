//
//  HMCharacteristicMetadata.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class defines the metadata for a characteristic. Metadata provides
 *		  further information about a characteristic’s value, which can be used
 * 		  for presentation purposes.
 */
HM_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristicMetadata : NSObject

/*!
 * @brief The minimum value for the characteristic if it has a format of "int" or "float".
 */
@property(readonly, nonatomic, nullable) NSNumber *minimumValue;

/*!
 * @brief The maximum value for the characteristic if it has a format of "int" or "float".
 */
@property(readonly, nonatomic, nullable) NSNumber *maximumValue;

/*!
 * @brief Step value for the characteristic that indicates the minimum step value allowed if it has a format of "int" or "float".
 */
@property(readonly, nonatomic, nullable) NSNumber *stepValue;

/*!
 * @brief Max length value for the characteristic that indicates the maximum number of UTF-8 characters allowed if it has a format of "string".
 */
@property(readonly, nonatomic, nullable) NSNumber *maxLength;

/*!
 * @brief The format of the value. Refer to HMCharacteristicMetadataFormat constants for supported units.
 */
@property(readonly, copy, nonatomic, nullable) NSString *format;

/*!
 * @brief The units of the value. Refer to HMCharacteristicMetadataUnits constants for supported units.
 */
@property(readonly, copy, nonatomic, nullable) NSString *units;

/*!
 * @brief Manufacturer provided description for the characteristic to present to the user.
 */
@property(readonly, copy, nonatomic, nullable) NSString *manufacturerDescription;

/*!
 * @brief The subset of valid values supported by the characteristic when the format is unsigned integral type.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSNumber *> *validValues API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

@end

/*!
 * @group HMCharacteristicMetadataFormat constants
 */

/*!
 * @brief Describes that the value format is boolean.
 *
 * @discussion The value is an NSNumber containing the boolean value.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatBool API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an integer.
 *
 * @discussion The value is an NSNumber containing a signed 32-bit integer with a range [-2147483648, 2147483647].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatInt API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a float.
 *
 * @discussion The value is an NSNumber containing a 32-bit float.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatFloat API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a string.
 *
 * @discussion The value is an NSString.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatString API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an array.
 *
 * @discussion The value is an NSArray.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatArray API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a dictionary.
 *
 * @discussion The value is an NSDictionary.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatDictionary API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 8-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 8-bit integer with a range [0, 255].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt8 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 16-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 16-bit integer with a range [0, 65535].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt16 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 32-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 32-bit integer with a range [0, 4294967295].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt32 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 64-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 64-bit integer with a range [0, 18446744073709551615].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt64 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a data blob.
 *
 * @discussion The value is an NSData containing the bytes of data.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatData API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a TLV8.
 *
 * @discussion The value is an NSData containing a set of one or more TLV8's, which are packed type-length-value items with an 8-bit type, 8-bit length, and N-byte value.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatTLV8 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);


/*!
 * @group HMCharacteristicMetadataUnits constants
 */

/*!
 * @brief Describes that the unit of the characteristic is in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsCelsius API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is in Fahrenheit.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsFahrenheit API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is a percentage.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsPercentage API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is arc degree.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsArcDegree API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is seconds.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsSeconds API_AVAILABLE(ios(8.3), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is Lux (illuminance).
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsLux API_AVAILABLE(ios(9.3), watchos(2.2), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is parts per million.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsPartsPerMillion API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is micrograms per cubic meter.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsMicrogramsPerCubicMeter API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);


NS_ASSUME_NONNULL_END
