//
//  MLSequenceConstraint.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

@class MLFeatureDescription;

/*!
 * Constraint describing expected MLSequence properties
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLSequenceConstraint : NSObject

// Description all sequence elements / values must match
@property (readonly, nonatomic) MLFeatureDescription *valueDescription;

// Restriction on the length of the sequence
@property (readonly, nonatomic) NSRange countRange;

@end

NS_ASSUME_NONNULL_END
