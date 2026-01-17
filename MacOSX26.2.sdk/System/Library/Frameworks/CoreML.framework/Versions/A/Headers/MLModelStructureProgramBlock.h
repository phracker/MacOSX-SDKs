//
//  MLModelStructureProgramBlock.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLModelStructureProgramNamedValueType;
@class MLModelStructureProgramOperation;

NS_ASSUME_NONNULL_BEGIN

/// A class representing a block in the Program.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructureProgramBlock : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The named inputs to the block.
@property (readonly, copy, nonatomic) NSArray<MLModelStructureProgramNamedValueType *> *inputs;
/// The output names.
@property (readonly, copy, nonatomic) NSArray<NSString *> *outputNames;
/// The list of topologically sorted operations in the block.
@property (readonly, copy, nonatomic) NSArray<MLModelStructureProgramOperation *> *operations;

@end

NS_ASSUME_NONNULL_END
