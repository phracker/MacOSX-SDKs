//
//  MLMultiArrayShapeConstraint.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLMultiArrayShapeConstraintType.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLMultiArrayShapeConstraint : NSObject

@property (readonly, nonatomic) MLMultiArrayShapeConstraintType type;

// Size of each dimension i must fall within sizeRangeForDimension[i].rangeValue
@property (readonly, nonatomic) NSArray<NSValue *> * sizeRangeForDimension;

// If type == MLMultiArrayShapeConstraintTypeEnumerated then
// only shapes in this set are allowed
@property (readonly, nonatomic) NSArray<NSArray<NSNumber *> *> * enumeratedShapes;

@end

NS_ASSUME_NONNULL_END
