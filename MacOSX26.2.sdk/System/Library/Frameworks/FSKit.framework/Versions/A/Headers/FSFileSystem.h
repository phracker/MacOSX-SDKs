//
//  Copyright (c) 2022-2023 Apple Inc. All rights reserved.
//
//  FSFileSystem.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSFileSystemBase.h>

NS_ASSUME_NONNULL_BEGIN

/// An abstract base class for implementing a full-featured file system.
///
/// `FSFileSystem` is a full-featured file system, which works with one or more ``FSResource`` instances and presents one or more ``FSVolume`` references to callers.
///
/// Implement your app extension by providing a subclass of `FSFileSystem` as a delegate object.
/// Your delegate also needs to implement the `FSFileSystemOperations` protocol so that it can probe, load, and unload resources.
///
/// > Note: The current version of FSKit supports only ``FSUnaryFileSystem``, not `FSFileSystem`.
FSKIT_API_UNAVAILABLE_V1
@interface FSFileSystem : NSObject <FSFileSystemBase>

@end

NS_ASSUME_NONNULL_END
