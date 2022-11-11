//
//  MLFeatureValue.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLMultiArray.h>
#import <CoreML/MLSequence.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreML/MLExport.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 * An immutable variant holding a data value of a supported MLFeatureType
 *
 * MLFeatureValue does not support type conversion in its accessor properties. It
 * can also have a missing or undefined value of a well defined type.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLFeatureValue : NSObject<NSCopying, NSSecureCoding>

/// Type of the value for which the corresponding property below is held
@property (readonly, nonatomic) MLFeatureType type;

/// True if the value represents a missing or undefined value
@property (readonly, nonatomic, getter=isUndefined) BOOL undefined;

/// Populated value if the type is MLFeatureTypeInt64
@property (readonly, nonatomic) int64_t int64Value;

/// Populated value if the type is MLFeatureTypeDouble
@property (readonly, nonatomic) double doubleValue;

/// Populated value if the type is MLFeatureTypeString
@property (readonly, nonatomic, copy) NSString *stringValue;

/// Populated value if the type is MLFeatureTypeMultiArray
@property (readonly, nullable, nonatomic) MLMultiArray *multiArrayValue;

/// Populated value if the type is MLFeatureTypeDictionary
@property (readonly, nonatomic) NSDictionary<id, NSNumber *> *dictionaryValue;

/// Populated value if the type is MLFeatureTypeImage
@property (readonly, nullable, nonatomic) CVPixelBufferRef imageBufferValue;

/// Populated value if the type is MLFeatureTypeSequence
@property (readonly, nullable, nonatomic) MLSequence *sequenceValue API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// Hold an object with the specified value
+ (instancetype)featureValueWithInt64:(int64_t)value;
+ (instancetype)featureValueWithDouble:(double)value;
+ (instancetype)featureValueWithString:(NSString *)value;
+ (instancetype)featureValueWithMultiArray:(MLMultiArray *)value;
+ (instancetype)featureValueWithPixelBuffer:(CVPixelBufferRef)value;
+ (instancetype)featureValueWithSequence:(MLSequence *)sequence API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// Represent an undefined value of a specified type
+ (instancetype)undefinedFeatureValueWithType:(MLFeatureType)type;

/*!
 * For encoding a sparse feature set or for encoding probabilities. Input keys that are not
 * NSNumber * or NSString * are rejected on construction and return a MLModelErrorFeatureTypeMismatch
 * error. Further validation for consistency occurs on evaluation
 */
+ (nullable instancetype)featureValueWithDictionary:(NSDictionary<id, NSNumber *> *)value
                                              error:(NSError **)error;



- (BOOL)isEqualToFeatureValue:(MLFeatureValue *)value;

@end

NS_ASSUME_NONNULL_END
