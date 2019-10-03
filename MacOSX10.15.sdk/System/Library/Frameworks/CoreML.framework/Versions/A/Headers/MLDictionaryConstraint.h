//
//  MLDictionaryConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLDictionaryConstraint
 *
 * Constraint describing expected NSDictionary properties
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLDictionaryConstraint : NSObject <NSSecureCoding>

/// Required key type, described as MLFeatureType
@property (readonly, nonatomic) MLFeatureType keyType;

@end

NS_ASSUME_NONNULL_END

