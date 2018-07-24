//
//  MLBatchProvider.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MLFeatureProvider;

/*!
 * Protocol for accessing a collection of feature providers
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
@protocol MLBatchProvider

/// Total number of feature providers
@property (readonly, nonatomic) NSInteger count;

/// Indexed access to collection
- (id<MLFeatureProvider>)featuresAtIndex:(NSInteger)index;

// Deprecated, do not use
@optional

@property (readonly, nonatomic) NSInteger featureProviderCount NS_DEPRECATED(10_14, 10_14, 12_0, 12_0, "Use count instead. If this is code generated for you please regenerate it with the latest coremlcompiler");
- (nullable id<MLFeatureProvider>)featureProviderAtIndex:(NSInteger)index NS_DEPRECATED(10_14, 10_14, 12_0, 12_0, "Use featuresAtIndex instead. If this is code generated for you please regenerate it with the latest coremlcompiler");

@end

NS_ASSUME_NONNULL_END
