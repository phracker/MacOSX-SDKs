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

@end

NS_ASSUME_NONNULL_END
