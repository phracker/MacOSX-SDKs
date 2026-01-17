//
//  Copyright (c) 2024 Apple Inc.  All rights reserved.
//
//  FSEntityIdentifier.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A base type that identifies containers and volumes.
///
/// An ``FSEntityIdentifier`` is a UUID to identify a container or volume, optionally with eight bytes of qualifying (differentiating) data.
/// You use the qualifiers in cases in which a file server can receive multiple connections from the same client, which differ by user credentials.
/// In this case, the identifier for each client is the server's base UUID, and a unique qualifier that differs by client.
///
/// > Important: Don't subclass this class.
FSKIT_API_AVAILABILITY_V1
@interface FSEntityIdentifier : NSObject <NSCopying, NSSecureCoding>

/// Creates an entity identifier with a random UUID.
- (instancetype)init;

/// Creates an entity identifier with the given UUID.
///
/// - Parameter uuid: The UUID to use for this identifier.
- (instancetype)initWithUUID:(NSUUID *)uuid;

/// Creates an entity identifier with the given UUID and qualifier data as a 64-bit unsigned integer.
/// - Parameters:
///   - uuid: The UUID to use for this identifier.
///   - qualifier: The data to distinguish entities that otherwise share the same UUID.
- (instancetype)initWithUUID:(NSUUID *)uuid
                   qualifier:(uint64_t)qualifier;

/// Creates an entity identifier with the given UUID and qualifier data.
///
/// - Parameters:
///   - uuid: The UUID to use for this identifier.
///   - qualifierData: The data to distinguish entities that otherwise share the same UUID.
- (instancetype)initWithUUID:(NSUUID *)uuid
                        data:(NSData *)qualifierData;

/// A UUID to uniquely identify this entity.
@property (copy)                NSUUID  *uuid;
/// An optional piece of data to distinguish entities that otherwise share the same UUID.
@property (copy, nullable)      NSData  *qualifier;

@end

NS_ASSUME_NONNULL_END
