//
//  Copyright (c) 2024 Apple Inc. All rights reserved.
//
//  FSFileDataBuffer.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A wrapper object for a data buffer.
///
/// This object provides a "zero-copy" buffer, for use when reading data from files.
/// By not requiring additional buffer copying, this object reduces the extension's memory footprint and improves performance.
/// The `FSMutableFileDataBuffer` behaves similarly to a `uio` in the kernel.
FSKIT_API_AVAILABILITY_V1
@interface FSMutableFileDataBuffer : NSObject

/// The data length of the buffer.
@property (readonly) NSUInteger length FSKIT_API_AVAILABILITY_V1;

- (instancetype)init NS_UNAVAILABLE;

/// The byte data.
-(void *)mutableBytes FSKIT_API_AVAILABILITY_V1 NS_SWIFT_UNAVAILABLE("Use withMutableBytes instead.");

@end

NS_ASSUME_NONNULL_END
