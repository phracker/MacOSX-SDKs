//
//  VZMacMachineIdentifier.h
//  Virtualization
//
//  Copyright © 2021-2024 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract An identifier to make a virtual machine unique.
 @discussion
    The Mac machine identifier is used by macOS guests to uniquely identify the virtual hardware.

    Two virtual machines running concurrently should not use the same identifier.

    If the virtual machine is serialized to disk, the identifier can be preserved in a binary representation through VZMacMachineIdentifier.dataRepresentation.
    The identifier can then be recreated with -[VZMacMachineIdentifier initWithDataRepresentation:] from the binary representation.

    The contents of two identifiers can be compared with -[VZMacMachineIdentifier isEqual:].
 @seealso VZMacPlatformConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacMachineIdentifier : NSObject <NSCopying>

/*!
 @abstract Create a new unique machine identifier.
 */
- (instancetype)init;

/*!
 @abstract Get the machine identifier described by the specified data representation.
 @param dataRepresentation The opaque data representation of the machine identifier to be obtained.
 @return A unique identifier identical to the one that generated the dataRepresentation, or nil if the data is invalid.
 @see VZMacMachineIdentifier.dataRepresentation
 */
- (nullable instancetype)initWithDataRepresentation:(NSData *)dataRepresentation;

/*!
 @abstract Opaque data representation of the machine identifier.
 @discussion This can be used to recreate the same machine identifier with -[VZMacMachineIdentifier initWithDataRepresentation:].
 @see -[VZMacMachineIdentifier initWithDataRepresentation:]
 */
@property (readonly, copy) NSData *dataRepresentation;

@end

NS_ASSUME_NONNULL_END

#endif
