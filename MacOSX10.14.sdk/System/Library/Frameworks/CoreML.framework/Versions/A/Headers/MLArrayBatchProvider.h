//
//  MLArrayBatchProvider.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CoreML/MLBatchProvider.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A concrete convenience class conforming to MLBatchProvider.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLArrayBatchProvider : NSObject<MLBatchProvider>

@property (readonly, nonatomic) NSArray<id<MLFeatureProvider>> *array;

/// Initalize with an array of feature providers
- (instancetype)initWithFeatureProviderArray:(NSArray<id<MLFeatureProvider>> *)array;

/// Initialize with a dictionary which maps feature names to an array of values [String : [Any]]
/// Error is returned if all arrays do not have equal length or if array values
/// for a specific feature name do not have the same type or not expressible as MLFeatureValue
- (nullable instancetype)initWithDictionary:(NSDictionary<NSString *, NSArray *> *)dictionary
                                      error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
