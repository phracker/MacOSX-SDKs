//
//  MLFeatureType.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * Supported data type enumeration
 */
typedef NS_ENUM(NSInteger, MLFeatureType) {
    // MUST be kept in sync with DataTypes.proto in libmlmodelspec!
    // TODO -- make this handle parameterized types and remove constraints
    // in the Objective-C layer.

    MLFeatureTypeInvalid = 0,

    /// Discrete values, sometimes used to hold numeric encoding of a categorical value
    MLFeatureTypeInt64 = 1,

    /// Continuous values
    MLFeatureTypeDouble = 2,

    // Text or categorical strings
    MLFeatureTypeString = 3,
    
    /// CVPixelBufferRef
    MLFeatureTypeImage = 4,

    /// MLMultiArray
    MLFeatureTypeMultiArray = 5,

    /// Numerically weighted hashable objects (e.g. word counts)
    MLFeatureTypeDictionary = 6,

} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));



