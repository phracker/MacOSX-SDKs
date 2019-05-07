//
//  MLMultiArrayConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLMultiArray.h>
#import <CoreML/MLMultiArrayShapeConstraint.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Constraint describing expected MLMultiArray properties
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLMultiArrayConstraint : NSObject

// Required or default shape of multiarray
@property (readonly, nonatomic) NSArray<NSNumber *> *shape;

// Required dataType
@property (readonly, nonatomic) MLMultiArrayDataType dataType;

// Detailed shape constraint
@property (readonly, nonatomic) MLMultiArrayShapeConstraint *shapeConstraint API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END

