//
//  MLModelStructureProgramNamedValueType.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLModelStructureProgramValueType;

NS_ASSUME_NONNULL_BEGIN

/// A class representing a named value type in a Program.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructureProgramNamedValueType : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The name of the parameter.
@property (readonly, copy, nonatomic) NSString *name;
/// The type of the parameter.
@property (readonly, strong, nonatomic) MLModelStructureProgramValueType *type;

@end

NS_ASSUME_NONNULL_END
