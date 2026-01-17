//
//  MLModelStructureProgramOperation.h
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLModelStructureProgramNamedValueType;
@class MLModelStructureProgramArgument;
@class MLModelStructureProgramBlock;

NS_ASSUME_NONNULL_BEGIN

/// A class representing an Operation in a Program.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructureProgramOperation : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The name of the operator, e.g., "conv", "pool", "softmax", etc.
@property (readonly, copy, nonatomic) NSString *operatorName;
/// The arguments to the Operation.
@property (readonly, copy, nonatomic) NSDictionary<NSString *, MLModelStructureProgramArgument *> *inputs;
/// The outputs of the Operation.
@property (readonly, copy, nonatomic) NSArray<MLModelStructureProgramNamedValueType *> *outputs;
/// Nested blocks for loops and conditionals, e.g., a conditional block will have two entries here.
@property (readonly, copy, nonatomic) NSArray<MLModelStructureProgramBlock *> *blocks;

@end

NS_ASSUME_NONNULL_END
