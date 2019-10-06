//
//  MLParameterDescription.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

@class MLNumericConstraint;

/*!
 * Describes a model parameter along with a default value and any applicable constaint on the values.
 */
ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0))
@interface MLParameterDescription : NSObject<NSSecureCoding>

// Name and type of the parameter
@property (readonly, nonatomic) MLParameterKey *key;

// Default value of the parameter
@property (readonly, nonatomic) id defaultValue;

// Any applicable constraint on the parameter value
@property (readonly, nonatomic, nullable) MLNumericConstraint *numericConstraint;

@end

NS_ASSUME_NONNULL_END

