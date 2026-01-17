//
//  MLModelStructurePipeline.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLModelStructure.h>

NS_ASSUME_NONNULL_BEGIN

/// A class representing the structure of a Pipeline model.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructurePipeline : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The names of the sub models in the pipeline.
@property (readonly, copy, nonatomic) NSArray<NSString *> *subModelNames;
/// The structure of the sub models in the pipeline.
@property (readonly, copy, nonatomic) NSArray<MLModelStructure *> *subModels;

@end

NS_ASSUME_NONNULL_END
