//
//  MLStateConstraint.h
//  CoreML
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>
#import <CoreML/MLMultiArray.h>

NS_ASSUME_NONNULL_BEGIN

/// Constraint of a state feature value.
API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0))
ML_EXPORT
@interface MLStateConstraint : NSObject <NSSecureCoding>

/// The shape of the state buffer.
@property (readonly, nonatomic) NSArray<NSNumber *> *bufferShape
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// The data type of scalars in the state buffer.
@property (readonly, nonatomic) MLMultiArrayDataType dataType
    API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

@end

NS_ASSUME_NONNULL_END
