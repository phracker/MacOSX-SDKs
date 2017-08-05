//
//  MLFeatureDescription.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLFeatureValue.h>
#import <CoreML/MLDictionaryConstraint.h>
#import <CoreML/MLMultiArrayConstraint.h>
#import <CoreML/MLImageConstraint.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Description of a feature
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLFeatureDescription : NSObject<NSCopying>

/// Name of feature
@property (readonly, nonatomic, copy) NSString *name;

/// Type of data
@property (readonly, nonatomic) MLFeatureType type;

/// Whether this feature can take an undefined value or not
@property (readonly, nonatomic, getter=isOptional) BOOL optional;

/// Check if MLFeatureValue is valid based on this description
- (BOOL)isAllowedValue:(MLFeatureValue *)value;

@end

/*!
 * Feature value constraints for specific types
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLFeatureDescription (MLFeatureValueConstraints)

/// Constraint when type == MLFeatureTypeMultiArray, nil otherwise
@property (readwrite, nullable, nonatomic) MLMultiArrayConstraint *multiArrayConstraint;

/// Constraint when type == MLFeatureTypeImage, nil otherwise
@property (readwrite, nullable, nonatomic) MLImageConstraint *imageConstraint;

/// Constraint when type == MLFeatureTypeDictionary, nil otherwise
@property (readwrite, nullable, nonatomic) MLDictionaryConstraint *dictionaryConstraint;

@end

NS_ASSUME_NONNULL_END
