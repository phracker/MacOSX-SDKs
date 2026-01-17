//
//  Copyright (c) 2022-2023 Apple Inc. All rights reserved.
//
//  FSContainer.h
//  FSKit
//

//
//  Common container-level protocols used by all modules. The
//  container-level operations needed to ADD support for any
//  given resource type is common for all module types.
//  Those operations are defined here.
//

#import <Foundation/Foundation.h>

#import <FSKit/FSKitDefines.h>
#import <FSKit/FSEntityIdentifier.h>

NS_ASSUME_NONNULL_BEGIN

/// An enumeration of container state values.
///
/// This enumeration represents values for a container's state engine.
/// Containers start in the ``notReady`` state.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(NSInteger, FSContainerState) {
    /// The container isn't ready.
    FSContainerStateNotReady = 0,
    /// The container is blocked from transitioning from the not-ready state to the ready state by a potentially-recoverable error.
    ///
    /// This state implies that the error has a resolution that would allow the container to become ready, such as correcting an incorrect password.
    FSContainerStateBlocked,
    /// The container is ready, but inactive.
    FSContainerStateReady,
    /// The container is active, and one or more volumes are active.
    FSContainerStateActive
};

/// A type that represents a container's status.
///
/// This type contains two properties:
///
/// * The ``state`` value that indicates the state of the container, such as ``FSContainerState/ready`` or ``FSContainerState/blocked``.
/// * The ``status`` is an error (optional in Swift, nullable in Objective-C) that provides further information about the state, such as why the container is blocked.
///
/// Examples of statuses that require intervention include errors that indicate the container isn't ready (POSIX `EAGAIN` or `ENOTCONN`), the container needs authentication (`ENEEDAUTH`), or that authentication failed (`EAUTH`).
/// The status can also be an informative error, such as the FSKit error ``FSError/Code/statusOperationInProgress``.
///
@interface FSContainerStatus : NSObject <NSCopying>

/// A value that represents the container state, such as ready, active, or blocked.
@property (readonly)                FSContainerState        state;
/// An optional error that provides further information about the state.
@property (readonly,copy,nullable)  NSError *               status;

- (instancetype)init NS_UNAVAILABLE;

/// A status that represents an active container with no error.
///
/// This value is a ``FSContainerStatus`` with a ``state`` that is ``active``, and has a ``status`` that is `nil`.
@property (class,readonly)      FSContainerStatus   *active;    // Container is active, status is nil

/// Returns a active container status instance with the provided error status.
///
/// - Parameter errorStatus: The error status, if any, for the new instance.
+ (instancetype)activeWithStatus:(NSError *)errorStatus NS_SWIFT_NAME(active(status:));

/// Returns a blocked container status instance with the provided error status.
///
/// - Parameter errorStatus: The error status, if any, for the new instance.
+ (instancetype)blockedWithStatus:(NSError *)errorStatus NS_SWIFT_NAME(blocked(status:));

/// Returns a not-ready container status instance with the provided error status.
///
/// - Parameter errorStatus: The error status, if any, for the new instance.
+ (instancetype)notReadyWithStatus:(NSError *)errorStatus NS_SWIFT_NAME(notReady(status:));

/// A status that represents a ready container with no error.
///
/// This value is a ``FSContainerStatus`` with a ``state`` that is ``ready``, and a ``status`` that is `nil`.
@property (class,readonly)      FSContainerStatus   *ready;    // Container is ready, status is nil

/// Returns a ready container status instance with the provided error status.
///
/// - Parameter errorStatus: The error status, if any, for the new instance.
+ (instancetype)readyWithStatus:(NSError *)errorStatus NS_SWIFT_NAME(ready(status:));

@end

@class FSVolumeIdentifier;

/// A type that identifies a container.
///
/// The identifier is either a UUID or a UUID with additional differentiating bytes.
/// Some network protocols evaluate access based on a user ID when connecting.
/// In this situation, when a file server receives multiple client connections with different user IDs, the server provides different file hierarchies to each.
/// For such systems, represent the container identifier as the UUID associated with the server, followed by four or eight bytes to differentiate connections.
///
/// > Important: Don't subclass this class.
FSKIT_API_AVAILABILITY_V1
@interface FSContainerIdentifier : FSEntityIdentifier

/*
 * For Unary file systems, the container identifier is the same
 * as the volume identifier.
 */
/// The volume identifier associated with the container.
///
/// For unary file systems, the volume identifier is the same as the container identifier.
@property (readonly,copy)   FSVolumeIdentifier *volumeIdentifier;

@end

NS_ASSUME_NONNULL_END
