//
//  MLModelStructureProgramFunction.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLModelStructureProgramBlock;
@class MLModelStructureProgramNamedValueType;

NS_ASSUME_NONNULL_BEGIN

/// A class representing a function in the Program.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructureProgramFunction : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The named inputs to the function.
@property (readonly, copy, nonatomic) NSArray<MLModelStructureProgramNamedValueType *> *inputs;
/// The active block in the function.
@property (readonly, strong, nonatomic) MLModelStructureProgramBlock *block;

@end

NS_ASSUME_NONNULL_END
