//
//  MLFeatureProvider.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureValue.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * Protocol for accessing a feature value for a feature name
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@protocol MLFeatureProvider

@property (readonly, nonatomic) NSSet<NSString *> *featureNames;

/// Returns nil if the provided featureName is not in the set of featureNames
- (nullable MLFeatureValue *)featureValueForName:(NSString *)featureName;

@end

NS_ASSUME_NONNULL_END

