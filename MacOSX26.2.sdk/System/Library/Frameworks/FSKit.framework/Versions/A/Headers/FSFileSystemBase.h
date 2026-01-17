//
//  Copyright (c) 2023 Apple Inc.  All rights reserved.
//
//  FSFileSystemBase.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>
#import <FSKit/FSContainer.h>
#import <FSKit/FSVolume.h>

@class FSBlockDeviceResource;

NS_ASSUME_NONNULL_BEGIN

/// A protocol containing functionality supplied by FSKit to file system implementations.
///
/// Both ``FSFileSystem`` and ``FSUnaryFileSystem`` conform to this protocol.
FSKIT_API_AVAILABILITY_V1
@protocol FSFileSystemBase <NSObject>

/* Container state diagram for containerStatus:

    ┌────────────────────────────┐
 ┌─▶│  FSContainerStateNotReady  │◀──────────────────────┐
 │  └────────────────────────────┘                       ▼
 │                 ▲                      ┌────────────────────────────┐
 │                 │                      │  FSContainerStateBlocked   │
 │                 ▼                      └────────────────────────────┘
 │  ┌────────────────────────────┐                       ▲
 │  │   FSContainerStateReady    │◀──────────────────────┘
 │  └────────────────────────────┘
 │                 ▲
 │                 │
 │                 ▼
 │  ┌────────────────────────────┐
 └──│   FSContainerStateActive   │
    └────────────────────────────┘
  */

/// The status of the file system container, indicating its readiness and activity.
///
/// A file system container starts in the ``FSContainerState/notReady`` state, and then transitions to the other values of the ``FSContainerState`` enumeration.
/// The following diagram illustrates the possible state transitions.
///
/// ![A flow diagram of four possible container states. The initial state, notReady, can transition to ready or blocked. The ready state can transition back to not ready, or to blocked or active. The blocked state can transition to ready or not ready. The active state can transition back to ready or to not ready.](fs-file-system-base)
///
/// Your file system implementation updates this property as it changes state.
/// Many events and operations may trigger a state transition, and some transitions depend on a specific file system's design.
///
/// When using ``FSBlockDeviceResource``, implement the following common state transitions:
///
/// * Calling `loadResource` transitions the state out of ``FSContainerState/notReady``. For all block device file systems, this operation changes the state to either ``FSContainerState/ready`` or ``FSContainerState/blocked``.
/// * Calling `unloadResource` transitions to the ``FSContainerState/notReady`` state, as does device termination.
/// * Transitioning from ``FSContainerState/blocked`` to ``FSContainerState/ready`` occurs as a result of resolving the underlying block favorably.
/// * Transitioning from ``FSContainerState/ready`` to ``FSContainerState/blocked`` is unusal, but valid.
/// * Transitioning between ``FSContainerState/ready`` and ``FSContainerState/active`` can result from maintenance operations such as ``FSManageableResourceMaintenanceOperations/startCheckWithTask:options:error:``. For a ``FSUnaryFileSystem``, this transition can also occur when activating or deactivating the container's single volume.
///
@property (copy)  FSContainerStatus   *containerStatus FSKIT_API_AVAILABILITY_V1;

/// Wipes existing file systems on the specified resource.
///
/// This method wraps the `wipefs` functionality from `libutil`.
/// For more information, see the `man` page for `wipefs`.
///
/// - Parameters:
///   - resource: The ``FSBlockDeviceResource`` to wipe.
///   - completion: A block or closure that executes after the wipe operation completes. The completion handler receives a single parameter indicating any error that occurs during the operation. If the value is `nil`, the wipe operation succeeded.
-(void)wipeResource:(FSBlockDeviceResource * )resource
  completionHandler:(void(^)(NSError * _Nullable error))completion FSKIT_API_AVAILABILITY_V1;

@end

NS_ASSUME_NONNULL_END
