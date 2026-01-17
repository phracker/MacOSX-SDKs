//
//  MLModelStructureProgramBinding.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLModelStructureProgramValue;

NS_ASSUME_NONNULL_BEGIN

/// A class representing a binding in the Program
///
/// A Binding is either a previously defined name of a variable or a constant value in the Program.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructureProgramBinding : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The name of the variable in the Program.
@property (readonly, copy, nonatomic, nullable) NSString *name;

/// The compile time constant value in the Program.
@property (readonly, copy, nonatomic, nullable) MLModelStructureProgramValue *value;

@end

NS_ASSUME_NONNULL_END
