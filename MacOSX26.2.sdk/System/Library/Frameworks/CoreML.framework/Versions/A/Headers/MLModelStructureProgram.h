//
//  MLProgramStructure.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLModelStructureProgramFunction;

NS_ASSUME_NONNULL_BEGIN

/// A class representing the structure of an ML Program model.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructureProgram : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The functions in the program.
@property (readonly, copy, nonatomic) NSDictionary<NSString *, MLModelStructureProgramFunction *> *functions;

@end

NS_ASSUME_NONNULL_END
