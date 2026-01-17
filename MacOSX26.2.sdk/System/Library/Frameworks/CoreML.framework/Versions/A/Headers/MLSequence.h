//
//  MLSequence.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * An immutable container holding an ordered collection of feature values
 * of the same type.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLSequence : NSObject <NSSecureCoding>

/// Type of values held
@property (readonly, nonatomic) MLFeatureType type;

/// Empty sequence of a sepcific type
+ (instancetype)emptySequenceWithType:(MLFeatureType)type;

/// String sequences, property will be empty array if type is MLFeatureTypeString
+ (instancetype)sequenceWithStringArray:(NSArray<NSString *> *)stringValues;
@property (readonly, nonatomic) NSArray<NSString *> *stringValues;

/// int64 sequence, propery will be empty array if type is MLFeatureTypeInt64
+ (instancetype)sequenceWithInt64Array:(NSArray<NSNumber *> *)int64Values;
@property (readonly, nonatomic) NSArray<NSNumber *> *int64Values;

@end

NS_ASSUME_NONNULL_END
