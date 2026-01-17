//
//  MLDictionaryFeatureProvider.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureProvider.h>
#import <CoreML/MLFeatureValue.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A concrete convenience class conforming to MLFeatureProvider.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLDictionaryFeatureProvider : NSObject<MLFeatureProvider, NSFastEnumeration>

/// Dictionary holding the feature values
@property (readonly, nonatomic) NSDictionary<NSString *, MLFeatureValue *> *dictionary;

/*!
 * Create from a generic dictionary by converting all values to MLFeatureValues
 * or from a dictionary with values already stored as MLFeatureValues.
 *
 * An error results if the values are not or cannot be represented as MLFeatureValues.
 */
- (nullable instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary
                                      error:(NSError **)error;

/// Get the value for specified feature
- (nullable MLFeatureValue *)objectForKeyedSubscript:(NSString *)featureName;

@end

NS_ASSUME_NONNULL_END
