//
//  Copyright (c) 2022-2023 Apple Inc. All rights reserved.
//
//  FSUnaryFileSystem.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSFileSystemBase.h>
#import <FSKit/FSResource.h>

NS_ASSUME_NONNULL_BEGIN

/// An abstract base class for implementing a minimal file system.
///
/// `FSUnaryFileSystem` is a simplified file system, which works with one ``FSResource`` and presents it as one ``FSVolume``.
///
/// The one volume and its container have a shared state and lifetime, a more constrained life cycle than the ``FSFileSystem`` design flow.
///
/// Implement your app extension by providing a subclass of `FSUnaryFileSystem` as a delegate object.
/// Your delegate also needs to implement the ``FSUnaryFileSystemOperations`` protocol so that it can load resources.
FSKIT_API_AVAILABILITY_V1
@interface FSUnaryFileSystem : NSObject <FSFileSystemBase>

@end

/// Operations performed by a unary file system.
///
/// Make sure your subclass of ``FSUnaryFileSystem`` conforms to this protocol.
FSKIT_API_AVAILABILITY_V1
@protocol FSUnaryFileSystemOperations <NSObject>

/// Requests that the file system probe the specified resource.
///
/// Implement this method to indicate whether the resource is recognizable and usable.
/// - Parameters:
///   - resource: The ``FSResource`` to probe.
///   - reply: A block or closure that your implementation invokes when it finishes the probe or encounters an error. Pass an instance of ``FSProbeResult`` with probe results as the first parameter if your probe operation succeeds. If probing fails, pass an error as the second parameter.
-(void)probeResource:(FSResource *)resource
        replyHandler:(void(^)(FSProbeResult * _Nullable result,
                              NSError * _Nullable error))reply FSKIT_API_AVAILABILITY_V1 NS_SWIFT_NAME(probeResource(resource:replyHandler:));

/// Requests that the file system load a resource and present it as a volume.
///
/// Implement this method by inspecting the provided resource and verifying it uses a supported format.
/// If the resource does use a supported format, create a subclass of `FSVolume`, clear the container error state, and invoke the `reply` callback, passing your volume as a parameter.
/// If loading can't proceed, invoke `reply` and send an appropriate error as the second parameter.
///
/// - Parameters:
///   - resource: An ``FSResource`` to load.
///   - options: An ``FSTaskOptions`` object specifying options to apply when loading the resource. An ``FSUnaryFileSystem`` supports two options: `-f` for "force" and `--rdonly` for read-only. The file system must remember if the read-only option is present.
///   - reply: A block or closure that your implementation invokes when it finishes setting up or encounters an error. Pass a subclass of `FSVolume` as the first parameter if loading succeeds. If loading fails, pass an error as the second parameter.
-(void)loadResource:(FSResource *)resource
            options:(FSTaskOptions *)options
       replyHandler:(void (^)(FSVolume * _Nullable volume,
                              NSError * _Nullable err))reply NS_SWIFT_NAME(loadResource(resource:options:replyHandler:)) FSKIT_API_AVAILABILITY_V1;

/// Requests that the file system unload the specified resource.
///
/// - Parameters:
///   - resource: An ``FSResource`` to unload.
///   - options: An ``FSTaskOptions`` object specifying options to apply when unloading the resource.
///   - reply: A block or closure that your implementation invokes when it finishes unloading or encounters an error. If unloading fails, pass an error as the parameter to describe the problem. Otherwise, pass `nil`.
-(void)unloadResource:(FSResource *)resource
              options:(FSTaskOptions *)options
         replyHandler:(void (^)(NSError * _Nullable err))reply NS_SWIFT_NAME(unloadResource(resource:options:replyHandler:)) FSKIT_API_AVAILABILITY_V1;

@optional
/// Notifies you that the system finished loading your file system extension.
///
/// The system performs this callback after the main run loop starts and before receiving the first message from the FSKit daemon.
///
/// Implement this method if you want to perform any setup prior to receiving FSKit callbacks.
-(void)didFinishLoading FSKIT_API_AVAILABILITY_V1;

@end

NS_ASSUME_NONNULL_END
