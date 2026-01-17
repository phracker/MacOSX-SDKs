//
//  Copyright (c) 2022 Apple Inc. All rights reserved.
//
//  FSItem.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A value that indicates a set of item attributes to get or set.
///
/// This type is an option set in Swift.
/// In Objective-C, you use the cases of this enumeration to create a bit field.
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSInteger, FSItemAttribute) {
    /// The type attribute.
    FSItemAttributeType                     = 1UL <<  0,
    /// The mode attribute.
    FSItemAttributeMode                     = 1UL <<  1,
    /// The link count attribute.
    FSItemAttributeLinkCount                = 1UL <<  2,
    /// The user ID (uid) attribute.
    FSItemAttributeUID NS_SWIFT_NAME(uid)   = 1UL <<  3,
    /// The group ID (gid) attribute.
    FSItemAttributeGID NS_SWIFT_NAME(gid)   = 1UL <<  4,
    /// The flags attribute.
    FSItemAttributeFlags                    = 1UL <<  5,
    /// The size attribute.
    FSItemAttributeSize                     = 1UL <<  6,
    /// The allocated size attribute.
    FSItemAttributeAllocSize                = 1UL <<  7,
    /// The file ID attribute.
    FSItemAttributeFileID                   = 1UL <<  8,
    /// The parent ID attribute.
    FSItemAttributeParentID                 = 1UL <<  9,
    /// The last-accessed time attribute.
    FSItemAttributeAccessTime               = 1UL << 10,
    /// The last-modified time attribute.
    FSItemAttributeModifyTime               = 1UL << 11,
    /// The last-changed time attribute.
    FSItemAttributeChangeTime               = 1UL << 12,
    /// The creation time attribute.
    FSItemAttributeBirthTime                = 1UL << 13,
    /// The backup time attribute.
    FSItemAttributeBackupTime               = 1UL << 14,
    /// The time added attribute.
    FSItemAttributeAddedTime                = 1UL << 15,
    /// The supports limited extended attributes attribute.
    FSItemAttributeSupportsLimitedXAttrs    = 1UL << 16,
    /// The inhibit kernel offloaded I/O attribute.
    FSItemAttributeInhibitKernelOffloadedIO = 1UL << 17,
} NS_SWIFT_NAME(FSItem.Attribute);

/// An enumeration of item types, such as file, directory, or symbolic link.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(NSInteger, FSItemType) {
    /// The item type of an unknown item.
    FSItemTypeUnknown = 0,
    /// The item type of a regular file.
    FSItemTypeFile,
    /// The item type of a directory.
    FSItemTypeDirectory,
    /// The item type of a symbolic link.
    FSItemTypeSymlink,
    /// The item type of a first-in/first-out named pipe.
    FSItemTypeFIFO NS_SWIFT_NAME(fifo),
    /// The item type of a character device.
    FSItemTypeCharDevice,
    /// The item type of a block device.
    FSItemTypeBlockDevice,
    /// The item type of a socket.
    FSItemTypeSocket
}NS_SWIFT_NAME(FSItem.ItemType);

/// The unique identifier for an item.
///
/// Use this type when packing items for an enumeration in ``FSDirectoryEntryPacker/packEntry(name:itemType:itemID:nextCookie:attributes:)``.
/// Either provide a unique identifier like an inode number, or one of the special enumeration cases this type defines, like ``FSItem/Identifier/rootDirectory``.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(UInt64, FSItemID) {
    /// The identifier for an invalid item.
    FSItemIDInvalid = 0,
    /// The identifier for an item that serves as the parent of the root directory.
    FSItemIDParentOfRoot = 1,
    /// The item identifier for the root directory.
    FSItemIDRootDirectory = 2,
} NS_SWIFT_NAME(FSItem.Identifier);

/// A distinct object in a file hierarchy, such as a file, directory, symlink, socket, and more.
///
/// An `FSItem` is a mostly opaque object, which your file system implementation defines as needed.
///
/// The ``FSItemAttributes`` class defines nonatomic properties to support `FSItem` instances.
/// An ``FSItemAttributes`` instance contains a snapshot of the attributes of an `FSItem` at one point in time.
/// The ``FSItemAttributes`` properties have no explicit thread safety provisions, since the operations that either get or set these properties enforce thread safety.
///
/// You test an attribute's validity with the the method ``FSItem/Attributes/isValid(_:)``.
/// If the value is `true` (Swift) or `YES` (Objective-C), it's safe to use the attribute.
///
/// Methods that get or set an item's attribute use ``FSItemGetAttributesRequest`` or ``FSItemSetAttributesRequest``, respectively.
/// Both are subclasses of ``FSItemAttributes``.
/// An ``FSItemGetAttributesRequest`` contains a ``FSItemGetAttributesRequest/wantedAttributes`` property to indicate the attributes a file system provides for the request.
/// Similarly, ``FSItemSetAttributesRequest`` uses the property ``FSItemSetAttributesRequest/consumedAttributes`` for a file system to signal back which attributes it successfully used.
///
/// `FSItem` is the FSKit equivelant of a vnode in the kernel.
/// For every FSKit vnode in the kernel, the `FSModule` hosting the volume has an instantiated `FSItem`.
FSKIT_API_AVAILABILITY_V1
@interface FSItem : NSObject

@end

/// Attributes of an item, such as size, creation and modification times, and user and group identifiers.
FSKIT_API_AVAILABILITY_V1 NS_SWIFT_NAME(FSItem.Attributes)
@interface FSItemAttributes : NSObject <NSSecureCoding>

/// Marks all attributes inactive.
-(void)invalidateAllProperties;

/// The user identifier.
@property (nonatomic)           uint32_t        uid;
/// The group identifier.
@property (nonatomic)           uint32_t        gid;
/// The mode of the item.
///
/// The mode is often used for `setuid`, `setgid`, and `sticky` bits.
@property (nonatomic)           uint32_t        mode;
/// The item type, such as a regular file, directory, or symbolic link.
@property (nonatomic)           FSItemType      type;
/// The number of hard links to the item.
@property (nonatomic)           uint32_t        linkCount;
/// The item's behavior flags.
///
/// See `st_flags` in `stat.h` for flag definitions.
@property (nonatomic)           uint32_t        flags;
/// The item's size.
@property (nonatomic)           uint64_t        size;
/// The item's allocated size.
@property (nonatomic)           uint64_t        allocSize;
/// The item's file identifier.
@property (nonatomic)           FSItemID        fileID;
/// The identifier of the item's parent.
@property (nonatomic)           FSItemID        parentID;
/// A Boolean value that indicates whether the item supports a limited set of extended attributes.
@property (nonatomic)           BOOL            supportsLimitedXAttrs;
/// A Boolean value that indicates whether the file system overrides the per-volume settings for kernel offloaded I/O for a specific file.
///
/// This property has no meaning if the volume doesn't conform to ``FSVolumeKernelOffloadedIOOperations``.
@property (nonatomic)           BOOL            inhibitKernelOffloadedIO;
/// The item's last-modified time.
///
/// This property represents `mtime`, the last time the item's contents changed.
@property (nonatomic)           struct timespec modifyTime;
/// The item's added time.
///
/// This property represents the time the file system added the item to its parent directory.
@property (nonatomic)           struct timespec addedTime;
/// The item's last-changed time.
///
/// This property represents `ctime`, the last time the item's metadata changed.
@property (nonatomic)           struct timespec changeTime;
/// The item's last-accessed time.
@property (nonatomic)           struct timespec accessTime;
/// The item's creation time.
@property (nonatomic)           struct timespec birthTime;
/// The item's last-backup time.
@property (nonatomic)           struct timespec backupTime;

/// Returns a Boolean value that indicates whether the attribute is valid.
///
/// If the value returned by this method is `YES` (Objective-C) or `true` (Swift), a caller can safely use the given attribute.
-(BOOL)isValid:(FSItemAttribute)attribute;

@end

/// A request to set attributes on an item.
///
/// Methods that take attributes use this type to receive attribute values and to indicate which attributes they support.
/// The various members of the parent type, ``FSItemAttributes``, contain the values of the attributes to set.
///
/// Modify the ``consumedAttributes`` property to indicate which attributes your file system successfully used.
/// FSKit calls the ``wasAttributeConsumed(_:)`` method to determine whether the file system successfully used a given attribute.
/// Only set the attributes that your file system supports.
FSKIT_API_AVAILABILITY_V1 NS_SWIFT_NAME(FSItem.SetAttributesRequest)
@interface FSItemSetAttributesRequest : FSItemAttributes

/// The attributes successfully used by the file system.
///
/// This property is a bit field in Objective-C and an <doc://com.apple.documentation/documentation/Swift/OptionSet> in Swift.
@property (nonatomic) FSItemAttribute consumedAttributes;

/// A method that indicates whether the file system used the given attribute.
///
/// - Parameter attribute: The ``FSItemAttribute`` to check.
-(BOOL)wasAttributeConsumed:(FSItemAttribute)attribute;

@end

/// A request to get attributes from an item.
///
/// Methods that retrieve attributes use this type and inspect the ``wantedAttributes`` property to determine which attributes to provide. FSKit calls the ``isAttributeWanted(_:)`` method to determine whether the request requires a given attribute.
FSKIT_API_AVAILABILITY_V1 NS_SWIFT_NAME(FSItem.GetAttributesRequest)
@interface FSItemGetAttributesRequest : NSObject <NSSecureCoding>

/// The attributes requested by the request.
///
/// This property is a bit field in Objective-C and an <doc://com.apple.documentation/documentation/Swift/OptionSet> in Swift.
@property (nonatomic) FSItemAttribute wantedAttributes;

/// A method that indicates whether the request wants given attribute.
///
/// - Parameter attribute: The ``FSItemAttribute`` to check.
-(BOOL)isAttributeWanted:(FSItemAttribute)attribute;

@end

NS_ASSUME_NONNULL_END
