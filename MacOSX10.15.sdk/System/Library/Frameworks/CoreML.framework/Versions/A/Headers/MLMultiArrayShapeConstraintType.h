//
//  MLMultiArrayShapeConstraintType.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>


API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
typedef NS_ENUM(NSInteger, MLMultiArrayShapeConstraintType) {

    MLMultiArrayShapeConstraintTypeUnspecified = 1, // An unconstrained shape. Any multi array satisfies this constraint.

    MLMultiArrayShapeConstraintTypeEnumerated = 2, // Limited to an enumerated set of shapes

    MLMultiArrayShapeConstraintTypeRange = 3,      // Allow full specified range per dimension

};
