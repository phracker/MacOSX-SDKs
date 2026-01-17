//
//  MLNumericConstraint.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Allows enforcement of constraints on the values of update parameters.
 */
ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0))
@interface MLNumericConstraint : NSObject<NSSecureCoding>

// Minimum value of the parameter can take.
@property (readonly, nonatomic) NSNumber *minNumber;

// Maximum value of the parameter can take.
@property (readonly, nonatomic) NSNumber *maxNumber;

// If not nil, list of restricted set of values the parameter can take.
@property (readonly, nonatomic, nullable) NSSet<NSNumber *> *enumeratedNumbers;

@end

NS_ASSUME_NONNULL_END

