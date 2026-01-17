//
//  VZGenericMachineIdentifier.h
//  Virtualization
//
//  Copyright © 2022-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract An identifier to make a virtual machine unique.
 @discussion
    The generic machine identifier is used by guests to uniquely identify the virtual hardware.

    If the virtual machine is serialized to disk, the identifier can be preserved in a binary representation through VZGenericMachineIdentifier.dataRepresentation.
    The identifier can then be recreated with -[VZGenericMachineIdentifier initWithDataRepresentation:] from the binary representation.

    The contents of two identifiers can be compared with -[VZGenericMachineIdentifier isEqual:].
 @seealso VZGenericPlatformConfiguration
*/

VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZGenericMachineIdentifier : NSObject <NSCopying>

/*!
 @abstract Create a new unique machine identifier.
 */
- (instancetype)init;

/*!
 @abstract Get the machine identifier described by the specified data representation.
 @param dataRepresentation The opaque data representation of the machine identifier to be obtained.
 @return A unique identifier identical to the one that generated the dataRepresentation, or nil if the data is invalid.
 @see VZGenericMachineIdentifier.dataRepresentation
 */
- (nullable instancetype)initWithDataRepresentation:(NSData *)dataRepresentation;

/*!
 @abstract Opaque data representation of the machine identifier.
 @discussion This can be used to recreate the same machine identifier with -[VZGenericMachineIdentifier initWithDataRepresentation:].
 @see -[VZGenericMachineIdentifier initWithDataRepresentation:]
 */
@property (readonly, copy) NSData *dataRepresentation;

@end

NS_ASSUME_NONNULL_END
