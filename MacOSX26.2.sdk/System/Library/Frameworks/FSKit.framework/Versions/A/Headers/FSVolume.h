//
//  Copyright (c) 2022 Apple Inc. All rights reserved.
//
//  FSVolume.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>
#import <FSKit/FSEntityIdentifier.h>
#import <FSKit/FSItem.h>
#import <FSKit/FSContainer.h>
#import <FSKit/FSFileName.h>
#import <FSKit/FSResource.h>
#import <FSKit/FSMutableFileDataBuffer.h>

NS_ASSUME_NONNULL_BEGIN

/// A value that indicates a location in a directory from which to enumerate.
///
/// Your implementation of ``FSVolume/Operations/enumerateDirectory(_:startingAt:verifier:attributes:packer:replyHandler:)`` defines the semantics of this value; it's opaque to FSKit.
FSKIT_API_AVAILABILITY_V1
typedef uint64_t FSDirectoryCookie NS_TYPED_EXTENSIBLE_ENUM;

/// The constant initial value for the directory-enumeration cookie.
FSKIT_API_AVAILABILITY_V1
FS_EXPORT FSDirectoryCookie const FSDirectoryCookieInitial;

/// A tool to detect whether the directory contents changed since the last call to enumerate a directory.
///
/// Your implementation of ``FSVolume/Operations/enumerateDirectory(_:startingAt:verifier:attributes:packer:replyHandler:)`` defines the semantics of this value; it's opaque to FSKit.
FSKIT_API_AVAILABILITY_V1
typedef uint64_t FSDirectoryVerifier NS_TYPED_EXTENSIBLE_ENUM;

/// The constant initial value for the directory-enumeration verifier.
FSKIT_API_AVAILABILITY_V1
FS_EXPORT FSDirectoryVerifier const FSDirectoryVerifierInitial;

/// Options that affect the behavior of deactivate methods.
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSInteger, FSDeactivateOptions) {
    /// An option to force deactivation.
    FSDeactivateOptionsForce = 1 << 0
};

/// Behavior flags for use with synchronization calls.
///
/// These values are based on flags defined in `mount.h`. Since there are system-defined flags that are valid in the kernel but not in FSKit, this type defines its members as options rather than use an enumeration.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(NSInteger, FSSyncFlags) {
    /// A flag for synchronized I/O with file-integrity completion.
    FSSyncFlagsWait = 1,
    /// A flag for synchronized I/O that starts I/O but doesn't wait for it.
    FSSyncFlagsNoWait = 2,
    /// A flag for synchronized I/O with data-integrity completion.
    FSSyncFlagsDWait = 4,
};

/// A type that identifies a volume.
///
/// For most volumes, the volume identifier is the UUID identifying the volume.
///
/// Network file systems may access the same underlying volume using different authentication credentials.
/// To handle this situation, add qualifying data to identify the specific container, as discussed in the superclass, ``FSEntityIdentifier``.
///
/// > Important: Don't subclass this class.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.Identifier)
@interface FSVolumeIdentifier : FSEntityIdentifier
@end

/// An object used to provide items during a directory enumeration.
///
/// You use this type in your implementation of ``FSVolume/Operations/enumerateDirectory(_:startingAt:verifier:attributes:packer:replyHandler:)``.
///
/// Packing allows your implementation to provide information FSKit needs, including each item's name, type, and identifier (such as an inode number).
/// Some directory enumerations require other attributes, as indicated by the ``FSItemGetAttributesRequest`` sent to the enumerate method.
FSKIT_API_AVAILABILITY_V1
@interface FSDirectoryEntryPacker : NSObject

-(instancetype)init NS_UNAVAILABLE;

/// Provides a directory entry during enumeration.
///
/// You call this method in your implementation of ``FSVolume/Operations/enumerateDirectory(_:startingAt:verifier:attributes:packer:replyHandler:)``, for each directory entry you want to provide to the enumeration.
///
/// - Parameters:
///   - name: The item's name.
///   - itemType: The type of the item.
///   - itemID: The item's identifier. Typically this is an inode number, or one of the constants defined by ``FSItem/Identifier`` like ``FSItem/Identifier/rootDirectory``.
///   - nextCookie: A value to indicate the next entry in the directory to enumerate. FSKit passes this value as the `cookie` parameter on the next call to ``FSVolume/Operations/enumerateDirectory(_:startingAt:verifier:attributes:packer:replyHandler:)``. Use whatever value is appropriate for your implementation; the value is opaque to FSKit.
///   - attributes: The item's attributes. Pass `nil` if the enumeration call didn't request attributes.
/// - Returns: `true` (Swift) or `YES` (Objective-C) if packing was successful and enumeration can continue with the next directory entry. If the value is `false` (Swift) or `NO` (Objective-C), stop enumerating. This result can happen when the entry is too big for the remaining space in the buffer.
-(BOOL)packEntryWithName:(FSFileName *)name
                itemType:(FSItemType)itemType
                  itemID:(FSItemID)itemID
              nextCookie:(FSDirectoryCookie)nextCookie
              attributes:(FSItemAttributes * _Nullable)attributes
NS_SWIFT_NAME(packEntry(name:itemType:itemID:nextCookie:attributes:))
FSKIT_API_AVAILABILITY_V1;

@end

/// An enumeration of case-sensitivity support types.
///
/// A case-sensitive volume is a volume that treats upper and lower case characters in file and directory names as being distinct from each other. For example, `FILE.TXT` and `file.TXT` are different names in a case-sensitive volume, and the same name in a case-insensitive volume.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(NSInteger, FSVolumeCaseFormat) {
    /// The volume is case sensitive.
    FSVolumeCaseFormatSensitive = 0,
    /// The volume isn't case sensitive.
    FSVolumeCaseFormatInsensitive = 1,
    /// The volume isn't case sensitive, but supports preserving the case of file and directory names.
    FSVolumeCaseFormatInsensitiveCasePreserving = 2
} NS_SWIFT_NAME(FSVolume.CaseFormat);


/// A type that represents capabillities supported by a volume, such as hard and symbolic links, journaling, and large file sizes.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.SupportedCapabilities)
@interface FSVolumeSupportedCapabilities : NSObject<NSSecureCoding>

/// A Boolean property that indicates whether the volume supports persistent object identifiers and can look up file system objects by their IDs.
@property (nonatomic) BOOL supportsPersistentObjectIDs;

/// A Boolean property that indicates whether the volume supports symbolic links.
@property (nonatomic) BOOL supportsSymbolicLinks;

/// A Boolean property that indicates whether the volume supports hard links.
@property (nonatomic) BOOL supportsHardLinks;

/// A Boolean property that indicates whether the volume supports a journal used to speed recovery in case of unplanned restart, such as a power outage or crash.
///
/// This property doesn't necessarily mean the volume is actively using a journal.
@property (nonatomic) BOOL supportsJournal;

/// A Boolean property that indicates whether the volume currently uses a journal for speeding recovery after an unplanned shutdown.
@property (nonatomic) BOOL supportsActiveJournal;

/// A Boolan property that indicates the volume doesn't store reliable times for the root directory.
///
/// If this value is `true` (Swift) or `YES` (Objective-C), the volume doesn't store reliable times for the root directory.
@property (nonatomic) BOOL doesNotSupportRootTimes;

/// A Boolean property that indicates whether the volume supports sparse files.
///
/// A sparse file is a file that can have "holes" that the file system has never written to, and as a result don't consume space on disk.
@property (nonatomic) BOOL supportsSparseFiles;

/// A Boolean property that indicates whether the volume supports zero runs
///
/// If this value is true, the volume keeps track of allocated but unwritten runs of a file so that it can substitute zeroes without actually writing zeroes to the media.
@property (nonatomic) BOOL supportsZeroRuns;

/// A Boolean property that indicates whether the volume supports fast results when fetching file system statistics.
///
/// A true value means this volume hints to upper layers to indicate that `statfs(2)` is fast enough that its results need not be cached by the caller.
@property (nonatomic) BOOL supportsFastStatFS;

/// A Boolean property that indicates whether the volume supports file sizes larger than 4GB, and potentially up to 2TB.
@property (nonatomic) BOOL supports2TBFiles;

/// A Boolean property that indicates whether the volume supports open deny modes.
///
/// These are modes such as "open for read write, deny write".
@property (nonatomic) BOOL supportsOpenDenyModes;

/// A Boolean property that indicates whether the volume supports hidden files.
///
/// A `true` value means the volume supports the `UF_HIDDEN` file flag.
@property (nonatomic) BOOL supportsHiddenFiles;

/// A Boolean property that indicates the volume doesn't support certain volume size reports.
///
/// A true value means the volume doesn't support determining values for total data blocks, available blocks, or free blocks, as in `f_blocks`, `f_bavail`, and `f_bfree` in the struct `statFS` returned by `statfs(2)`.
@property (nonatomic) BOOL doesNotSupportVolumeSizes;

/// A Boolean property that indicates whether the volume supports 64-bit object IDs.
@property (nonatomic) BOOL supports64BitObjectIDs;

/// A Boolean property that indicates whether the volume supports document IDs for document revisions.
///
/// A document ID is an identifier that persists across object ID changes.
@property (nonatomic) BOOL supportsDocumentID;

/// A Boolean property that indicates the volume doesn't support immutable files.
///
/// A `true` value means this volume doesn't support setting the `UF_IMMUTABLE` flag.
@property (nonatomic) BOOL doesNotSupportImmutableFiles;

/// A Boolean property that indicates the volume doesn't set file permissions.
///
/// If this value is `true` (Swift) or `YES` (Objective-C), the volume doesn't support setting file permissions.
@property (nonatomic) BOOL doesNotSupportSettingFilePermissions;

/// A Boolean property that indicates whether the volume supports multiple logical file systems that share space in a single "partition."
@property (nonatomic) BOOL supportsSharedSpace;

/// A Boolean property that indicates whether the volume supports volume groups.
///
/// Volume groups involve multiple logical file systems that the system can mount and unmount together, and for which the system can present common file system identifier information.
@property (nonatomic) BOOL supportsVolumeGroups;

/// A value that indicates the volume's support for case sensitivity.
@property (nonatomic) FSVolumeCaseFormat caseFormat;

@end

/// A directory structure for files and folders.
///
/// A file system, depending on its type, provides one or more volumes to clients.
/// The ``FSUnaryFileSystem`` by definition provides only one volume, while an ``FSFileSystem`` supports multiple volumes.
///
/// You implement a volume for your file system type by subclassing this class, and also conforming to the ``FSVolume/Operations`` and ``FSVolume/PathConfOperations`` protocols.
/// This protocol defines the minimum set of operations supported by a volume, such as mounting, activating, creating and removing items, and more.
///
/// Your volume can provide additional functionality by conforming to other volume operations protocols.
/// These protocols add support for operations like open and close, read and write, extended attribute (Xattr) manipulation, and more.
FSKIT_API_AVAILABILITY_V1
@interface FSVolume : NSObject

/// An identifier that uniquely identifies the volume.
@property (strong, readonly)    FSVolumeIdentifier  *volumeID;

/// The name of the volume.
@property (copy)                FSFileName          *name;

-(instancetype)init NS_UNAVAILABLE;

/// Creates a volume with the given identifier and name.
/// - Parameters:
///   - volumeID: An ``FSVolumeIdentifier`` to uniquely identify the volume. For a network file system that supports multiple authenticated users, disambiguate the users by using qualifying data in the identifier.
///   - volumeName: A name for the volume.
-(instancetype)initWithVolumeID:(FSVolumeIdentifier *)volumeID
                     volumeName:(FSFileName *)volumeName NS_DESIGNATED_INITIALIZER;

@end

/// Properties implemented by volumes that support providing the values of system limits or options.
///
/// This protocol gathers properties related to the `pathconf` and `fpathconf` system calls.
///
/// For a file, the value of a property applies to just that file; for a directory, the value applies to all items in the directory.
///
/// Properties that represent limits and have a numeric type use `-1` to represent no limit.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.PathConfOperations)
@protocol FSVolumePathConfOperations <NSObject>

/// A property that represents the maximum number of hard links to the object.
@property (readonly) NSInteger maximumLinkCount;

/// A property that represents the maximum length of a component of a filename.
@property (readonly) NSInteger maximumNameLength;

/// A Boolean property that indicates whether the volume restricts ownership changes based on authorization.
///
/// If this value is true, the volume rejects a `chown(2)` from anyone other than the superuser.
@property (readonly) BOOL restrictsOwnershipChanges;

/// A property that indicates whether the volume truncates files longer than its maximum supported length.
///
/// If this value is `true`, the volume truncates the filename to ``maximumNameLength`` if the filename is longer than that.
/// If this value is false, the file system responds with the error code `ENAMETOOLONG` if the filename is longer than ``maximumNameLength``.
@property (readonly) BOOL truncatesLongNames;

@optional

/// The maximum extended attribute size in bytes.
///
/// Implement at least one of `maximumXattrSize` or ``maximumXattrSizeInBits``.
/// FSKit automatically converts from one to another if needed.
/// If you implement both, FSKit uses only the `maximumXattrSizeInBits` implementation.
@property (readonly) NSInteger maximumXattrSize;

/// The maximum extended attribute size in bits.
///
/// Implement at least one of ``maximumXattrSize`` or `maximumXattrSizeInBits`.
/// FSKit automatically converts from one to another if needed.
/// If you implement both, FSKit uses only the `maximumXattrSizeInBits` implementation.
@property (readonly) NSInteger maximumXattrSizeInBits;

/// The maximum size of a regular file allowed in the volume.
///
/// Implement at least one of `maximumFileSize` or ``maximumFileSizeInBits``.
/// FSKit automatically converts from one to another if needed.
/// If you implement both, FSKit uses only the `maximumFileSizeInBits` implementation.
@property (readonly) uint64_t maximumFileSize;

/// The minimum number of bits needed to represent, as a signed integer value, the maximum size of a regular file allowed in the volume.
///
/// The maximum file size is `2^(maximumFileSizeInBits - 1)`.
///
/// | Maximum file size (bytes)  | Maximum (in hex)     | Unsigned bits | Signed bits |
/// | -------------------------: | -------------------: | ------------: | ----------: |
/// |                     65,535 |             `0xFFFF` |            16 |          17 |
/// |              2,147,483,647 |         `0x7FFFFFFF` |            31 |          32 |
/// |              4,294,967,295 |         `0xFFFFFFFF` |            32 |          33 |
/// | 18,446,744,073,709,551,615 | `0xFFFFFFFFFFFFFFFF` |            64 |          65 |
///
/// Implement at least one of ``maximumFileSize`` or `maximumFileSizeInBits`.
/// FSKit automatically converts from one to another if needed.
/// If you implement both, FSKit uses only the `maximumFileSizeInBits` implementation.
@property (readonly) NSInteger maximumFileSizeInBits;

@end

/// A type used to report a volume's statistics.
///
/// The names of this type's properties match those in the `statfs` structure in `statfs(2)`, which reports these values for an FSKit file system.
/// All numeric properties default to `0`.
/// Override these values, unless a given property has no meaningful value to provide.
///
/// > Note: Available space, free space, total space, and used space have properties to express their values either as a number of blocks or a number of bytes.
/// Your module may supply both of these values by setting both the relevant block or byte property.
/// Alternatively, a module may set only one of the two properties.
/// When you do this, FSKit calculates the matching value based on ``blockSize``.
///
/// For the read-only ``fileSystemTypeName``, set this value with the designated initializer.
FSKIT_API_AVAILABILITY_V1
@interface FSStatFSResult : NSObject <NSSecureCoding>

/// A property for the volume's block size, in bytes.
///
/// This value defaults to `4096`. Zero isn't a valid block size.
@property NSInteger blockSize;
/// A property for the optimal block size with which to perform I/O.
///
/// For best performance, specify an `ioSize` that's an even multiple of ``blockSize``.
@property NSInteger ioSize;
/// A property for the volume's total data block count.
@property uint64_t totalBlocks;
/// A property for the number of free blocks available to a non-superuser on the volume.
@property uint64_t availableBlocks;
/// A property for the number of free blocks in the volume.
@property uint64_t freeBlocks;
/// A property for the number of used blocks in the volume.
@property uint64_t usedBlocks;
/// A property for the total size, in bytes, of the volume.
@property uint64_t totalBytes;
/// A property for the amount of space available to users, in bytes, in the volume.
@property uint64_t availableBytes;
/// A property for the amount of free space, in bytes, in the volume.
@property uint64_t freeBytes;
/// A property for the amount of used space, in bytes, in the volume.
@property uint64_t usedBytes;
/// A property for the total number of file slots in the volume,
@property uint64_t totalFiles;
/// A property for the total number of free file slots in the volume.
@property uint64_t freeFiles;
/// A property for the file system's subtype or flavor.
///
/// Match this value to the `FSPersonalities`'s `FSSubType` attribute, if it exists within the `EXAppExtensionAttributes` dictionary of the module's `Info.plist`.
@property NSInteger fileSystemSubType;
/// A property for the file system type name.
///
/// Match this value to the `FSShortName` attribute within the `EXAppExtensionAttributes` dictionary of the module's `Info.plist`.
/// The maximum allowed length is `MFSTYPENAMELEN`, including the terminating `NUL` character.
@property (readonly, copy) NSString * fileSystemTypeName;

/// Creates an statistics result instance, using the given file system type name.
///
/// - Parameters fileSystemTypeName: A type name for the file system. The maximum allowed length is `MFSTYPENAMELEN`, including the terminating `NUL` character.
- (instancetype)initWithFileSystemTypeName:(NSString *)fileSystemTypeName;

- (instancetype)init NS_UNAVAILABLE;

@end

/// Methods that all volumes implement to provide required capabilities.
///
/// Conform to this protocol in your subclass of ``FSVolume``.
/// To provide additional capabilities, conform to the other `FSVolume` operations protocols, like ``FSVolumeOpenCloseOperations`` and ``FSVolumeReadWriteOperations``.
///
/// > Note: This protocol extends ``FSVolumePathConfOperations``, so your volume implementation must also conform to that protocol.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.Operations)
@protocol FSVolumeOperations <NSObject, FSVolumePathConfOperations>

/// A property that provides the supported capabilities of the volume.
@property (readonly, nonatomic) FSVolumeSupportedCapabilities *supportedVolumeCapabilities;

/// A property that provides up-to-date statistics of the volume.
@property (readonly, nonatomic) FSStatFSResult * volumeStatistics;

@optional

/// A property that allows the file system to use open-unlink emulation.
///
/// _Open-unlink_ functionality refers to a file system's ability to support an open file being fully unlinked from the file system namespace.
/// If a file system doesn't support this functionality, FSKit can emulate it instead; this is called "open-unlink emulation".
///
/// Implement this property to return `true` (Swift) or `YES` (Objective-C) to allow FSKit to perform open-unlink emulation.
/// If you don't implement this property at all, FSKit doesn't perform open-unlink emulation for this volume.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property BOOL enableOpenUnlinkEmulation FSKIT_API_AVAILABILITY_V2;

@required

/// Mounts this volume, using the specified options.
///
/// FSKit calls this method as a signal that some process is trying to mount this volume.
/// Your file system receives a call to ``activate(options:replyHandler:)`` prior to receiving any mount calls.
///
/// - Parameters:
///   - options: Options to apply to the mount. These can include security-scoped file paths. There are no defined options currently.
///   - reply: A block or closure to indicate success or failure. If mounting fails, pass an error as the one parameter to the reply handler. If mounting succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply return normally.
-(void)mountWithOptions:(FSTaskOptions *)options
           replyHandler:(void(^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(mount(options:replyHandler:));

/// Unmounts this volume.
///
/// Clear and flush all cached state in your implementation of this method.
///
/// - Parameters:
///   - reply: A block or closure to indicate success or failure. If unmounting fails, pass an error as the one parameter to the reply handler. If unmounting succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply return normally.
-(void)unmountWithReplyHandler:(void(^)(void))reply
NS_SWIFT_NAME(unmount(replyHandler:));

/// Synchronizes the volume with its underlying resource.
///
/// After calling this method, FSKit assumes that the volume has sent all pending I/O or metadata to its resource.
///
/// - Parameters:
///   - flags: Timing flags, as defined in `mount.h.` These flags let the file system know whether to run the operation in a blocking or nonblocking fashion.
///   - reply: A block or closure to indicate success or failure. If synchronization fails, pass an error as the one parameter to the reply handler. If synchronization succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)synchronizeWithFlags:(FSSyncFlags)flags
               replyHandler:(void(^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(synchronize(flags:replyHandler:));

/// Fetches attributes for the given item.
///
/// For file systems that don't support hard links, set ``FSItemAttributes/linkCount`` to `1` for regular files and symbolic links.
///
/// If the item's `bsdFlags` contain the `UF_COMPRESSED` flag, your file system returns the uncompressed size of the file.
///
/// - Parameters:
///   - desiredAttributes: A requested set of attributes to get. The implementation inspects the request's ``FSItemGetAttributesRequest/wantedAttributes`` to determine which attributes to populate.
///   - item: The item to get attributes for.
///   - reply: A block or closure to indicate success or failure. If getting attributes succeeds, pass an ``FSItemAttributes`` with the requested attributes populated and a `nil` error. If getting attributes fails, pass the relevant error as the second parameter; FSKit ignores any ``FSItemAttributes`` in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSItemAttributes`` or throw an error.
-(void)getAttributes:(FSItemGetAttributesRequest *)desiredAttributes
              ofItem:(FSItem *)item
        replyHandler:(void(^)(FSItemAttributes * _Nullable attributes,
                              NSError * _Nullable error))reply
NS_SWIFT_NAME(getAttributes(_:of:replyHandler:))
NS_SWIFT_ASYNC_NAME(attributes(_:of:));

/// Sets the given attributes on an item.
///
/// Several attributes are considered "read-only", and an attempt to set these attributes results in an error with the code `EINVAL`.
///
/// A request may set ``FSItem/Attributes/size`` beyond the end of the file.
/// If the underlying file system doesn't support sparse files, allocate space to fill the new file size.
/// Either fill this space with zeroes, or configure it to read as zeroes.
///
/// If a request sets the file size below the current end-of-file, truncate the file and return any unused space to the file system as free space.
///
/// Ignore attempts to set the size of directories or symbolic links; don't produce an error.
///
/// If the caller attepts to sest an attribute not supported by the on-disk file system format, don't produce an error.
/// The upper layers of the framework will detect this situation.
///
/// - Parameters:
///   - newAttributes: A request containing the attributes to set.
///   - item: The item on which to set the attributes.
///   - reply: A block or closure to indicate success or failure. If setting attributes succeeds, pass an ``FSItemAttributes`` with the item's updated attributes and a `nil` error. If setting attributes fails, pass the relevant error as the second parameter; FSKit ignores any ``FSItemAttributes`` in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSItemAttributes`` or throw an error.
-(void)setAttributes:(FSItemSetAttributesRequest *)newAttributes
              onItem:(FSItem *)item
        replyHandler:(void(^)(FSItemAttributes * _Nullable attributes,
                              NSError * _Nullable error))reply
NS_SWIFT_NAME(setAttributes(_:on:replyHandler:));

/// Looks up an item within a directory.
///
/// If no item matching `name` exists in the directory indicated by `directory`, complete the request with an error with a domain of <doc://com.apple.documentation/documentation/Foundation/NSPOSIXErrorDomain> and a code of `ENOENT`.
///
/// > Tip: The ``FSFileName`` sent back to the caller may differ from the `name` parameter. This flexibility allows your implementation to handle case-insensitive and case-sensitive file systems. It might also be the case that `name` uses a composed Unicode string, but the name maintained by the file system and provided to the caller is uncomposed Unicode.
///
/// - Parameters:
///   - name: The name of the item to look up.
///   - directory: The directory in which to look up the item.
///   - reply: A block or closure to indicate success or failure. If lookup succeeds, pass the found ``FSItem`` and its ``FSFileName`` (as saved within the file system), along with a `nil` error. If lookup fails, pass the relevant error as the third parameter; any ``FSItem`` or ``FSFileName`` are ignored in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSItem`` and ``FSFileName`` as a tuple or throw an error.
-(void)lookupItemNamed:(FSFileName *)name
           inDirectory:(FSItem *)directory
          replyHandler:(void(^)(FSItem * _Nullable theItem,
                                FSFileName * _Nullable itemName,
                                NSError * _Nullable error))reply
NS_SWIFT_NAME(lookupItem(named:inDirectory:replyHandler:));

/// Reclaims an item, releasing any resources allocated for the item.
///
/// FSKit guarantees that for every ``FSItem`` returned by the volume, a corresponding reclaim operation occurs after the upper layers no longer reference that item.
///
/// > Note: Block device file systems may assess whether an underyling resource terminates before processing reclaim operations. On unary file systems, for example, the associated volumes unmount when such resources disconnect from the system. The unmount triggers a reclaiming of all items. Some implementations benefit greatly from short-circuiting in such cases. With a terminated resource, all I/O results in an error, making short-circuiting the most efficient response.
///
/// - Parameters:
///   - item: The item to reclaim.
///   - reply: A block or closure to indicate success or failure. If removal fails, pass an error as the one parameter to the reply handler. If removal succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)reclaimItem:(FSItem *)item
      replyHandler:(void(^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(reclaimItem(_:replyHandler:));

/// Reads a symbolic link.
///
/// - Parameters:
///   - item: The symbolic link to read from. FSKit guarantees this item is of type ``FSItem/ItemType/symlink``.
///   - reply: A block or closure to indicate success or failure. If reading succeeds, pass the link's contents as an ``FSFileName`` and a `nil` error. If reading fails, pass the relevant error as the second parameter; FSKit ignores any ``FSFileName`` in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSFileName`` or throw an error.
-(void)readSymbolicLink:(FSItem *)item
           replyHandler:(void(^)(FSFileName * _Nullable contents,
                                 NSError * _Nullable error))reply;

/// Creates a new file or directory item.
///
/// If an item named `name` already exists in the directory indicated by `directory`, complete the request with an error with a domain of <doc://com.apple.documentation/documentation/Foundation/NSPOSIXErrorDomain> and a code of `EEXIST`.
///
/// - Parameters:
///   - name: The new item's name.
///   - type: The new item's type.  Valid values are ``FSItem/ItemType/file`` or ``FSItem/ItemType/directory``.
///   - directory: The directory in which to create the item.
///   - newAttributes: Attributes to apply to the new item.
///   - reply: A block or closure to indicate success or failure. If creation succeeds, pass the newly-created ``FSItem`` and its ``FSFileName``, along with a `nil` error. If creation fails, pass the relevant error as the third parameter; FSKit ignores any ``FSItem`` or ``FSFileName`` in this case. For an `async` Swift implementation, there's no reply handler; simply return a tuple of the ``FSItem`` and its ``FSFileName`` or throw an error.
-(void)createItemNamed:(FSFileName *)name
                  type:(FSItemType)type
           inDirectory:(FSItem *)directory
            attributes:(FSItemSetAttributesRequest *)newAttributes
          replyHandler:(void(^)(FSItem * _Nullable newItem,
                                FSFileName * _Nullable newItemName,
                                NSError * _Nullable error))reply
NS_SWIFT_NAME(createItem(named:type:inDirectory:attributes:replyHandler:));

/// Creates a new symbolic link.
///
/// If an item named `name` already exists in the directory indicated by `directory`, complete the request with an error with a domain of <doc://com.apple.documentation/documentation/Foundation/NSPOSIXErrorDomain> and a code of `EEXIST`.
///
/// - Parameters:
///   - name: The new item's name.
///   - directory: The directory in which to create the item.
///   - newAttributes: Attributes to apply to the new item.
///   - contents: The contents of the new symbolic link.
///   - reply: A block or closure to indicate success or failure. If creation succeeds, pass the newly-created ``FSItem`` and a `nil` error. If creation fails, pass the relevant error as the second parameter; FSKit ignores any ``FSItem`` in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSItem`` or throw an error.
-(void)createSymbolicLinkNamed:(FSFileName *)name
                   inDirectory:(FSItem *)directory
                    attributes:(FSItemSetAttributesRequest *)newAttributes
                  linkContents:(FSFileName *)contents
                  replyHandler:(void(^)(FSItem * _Nullable newItem,
                                        FSFileName * _Nullable newItemName,
                                        NSError * _Nullable error))reply
NS_SWIFT_NAME(createSymbolicLink(named:inDirectory:attributes:linkContents:replyHandler:));

/// Creates a new hard link.
///
/// If creating the link fails, complete the request with an error with a domain of <doc://com.apple.documentation/documentation/Foundation/NSPOSIXErrorDomain> and the following error codes:
///
/// * `EEXIST` if there's already an item named `name` in the directory.
/// * `EMLINK` if creating the link would exceed the maximum number of hard links supported on `item`.
/// * `ENOTSUP` if the file system doesn't support creating hard links to the type of file system object that `item` represents.
///
/// - Parameters:
///   - item: The existing item to which to link.
///   - name: The name for the new link.
///   - directory: The directory in which to create the link.
///   - reply: A block or closure to indicate success or failure. If creation succeeds, pass an ``FSFileName`` of the newly-created link and a `nil` error. If creation fails, pass the relevant error as the second parameter; FSKit ignores any ``FSFileName`` in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSFileName`` or throw an error.
-(void)createLinkToItem:(FSItem *)item
                  named:(FSFileName *)name
            inDirectory:(FSItem *)directory
           replyHandler:(void(^)(FSFileName * _Nullable linkName,
                                 NSError * _Nullable error))reply;

/// Removes an existing item from a given directory.
///
/// Don't actually remove the item object itself in your implementation; instead, only remove the given item name from the given directory.
/// Remove and deallocate the item in ``reclaimItem(_:replyHandler:)``.
///
/// - Parameters:
///   - item: The item to remove.
///   - name: The name of the item to remove.
///   - directory: The directory from which to remove the item.
///   - reply: A block or closure to indicate success or failure. If removal fails, pass an error as the one parameter to the reply handler. If removal succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)removeItem:(FSItem *)item
            named:(FSFileName *)name
    fromDirectory:(FSItem *)directory
     replyHandler:(void(^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(removeItem(_:named:fromDirectory:replyHandler:));

/// Renames an item from one path in the file system to another.
///
/// Implement renaming along the lines of this algorithm:
///
/// - If `item` is a file:
///   - If the destination file exists:
///     - Remove the destination file.
///   - If the source and destination directories are the same:
///     - Rewrite the name in the existing directory.
///   - Else:
///     - Write the new entry in the destination directory.
///     - Clear the old directory entry.
/// - If `item` is a directory:
///   - If the destination directory exists:
///     - If the destination directory isn't empty:
///       - Fail the operation with an error of <doc://com.apple.documentation/documentation/Foundation/NSPOSIXErrorDomain> and a code of `ENOTEMPTY`.
///     - Else:
///        - Remove the destination directory.
///     - If the source and destination directories are the same:
///       - Rewrite the name in the existing directory.
///     - Else:
///       - If the destination is a child of the source directory:
///         - Fail the operation with an error.
///       - Else:
///         - Write the new entry in the destination directory.
///         - Update `"."` and `".."` in the moved directory.
///         - Clear the old directory entry.
///
/// - Parameters:
///   - item: The file system object being renamed.
///   - sourceDirectory: The directory that currently contains the item to rename.
///   - sourceName: The name of the item within the source directory.
///   - destinationName: The new name of the item as it appears in `destinationDirectory`.
///   - destinationDirectory: The directory to contain the renamed object, which may be the same as `sourceDirectory`.
///   - overItem: The file system object if the destination exists, as discovered in a prior lookup. If this parameter is non-`nil`, mark `overItem` as deleted, so the file system can free its allocated space on the next call to ``reclaimItem(_:replyHandler:)``. After doing so, ensure the operation finishes without errors.
///   - reply: A block or closure to indicate success or failure. If renaming succeeds, pass the ``FSFileName`` as it exists within `destinationDirectory` and a `nil` error. If renaming fails, pass the relevant error as the second parameter; FSKit ignores any ``FSFileName`` in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSFileName`` or throw an error.
-(void)renameItem:(FSItem *)item
      inDirectory:(FSItem *)sourceDirectory
            named:(FSFileName *)sourceName
        toNewName:(FSFileName *)destinationName
      inDirectory:(FSItem *)destinationDirectory
         overItem:(FSItem * _Nullable)overItem
     replyHandler:(void(^)(FSFileName * _Nullable newName,
                           NSError * _Nullable error))reply
NS_SWIFT_NAME(renameItem(_:inDirectory:named:to:inDirectory:overItem:replyHandler:));

/// Enumerates the contents of the given directory.
///
/// This method uses the ``FSDirectoryEntryPacker/packEntry(name:itemType:itemID:nextCookie:attributes:)`` method of the `packer` parameter to deliver the enumerated items to the caller.
/// The general flow of an enumeration implementation follows these steps:
///
/// 1. Enumeration starts with a call to `enumerateDirectory` using the initial next-cookie and verifier values ``FSDirectoryCookieInitial`` and ``FSDirectoryVerifierInitial``, respectively.
/// 2. The implementation uses `packer` to pack the initial set of directory entries. Packing also sets a `nextCookie` to use on the next call.
/// 3. The implementation replies with a new verifier value, a nonzero value that reflects the directory's current version.
/// 4. On the next call the implementation packs the next set of entries, starting with the item indicated by `cookie`. If `cookie` doesn't resolve to a valid directory entry, complete the request with an error of domain <doc://com.apple.documentation/documentation/Foundation/NSPOSIXErrorDomain> and code ``FSError/Code/invalidDirectoryCookie``.
///
/// When packing, make sure to use acceptable directory entry names and unambiguous input to all file operations that take names without additional normalization, such as`lookupName`.
///
/// > Tip: If the `attributes` parameter is `nil`, include at least two entries in a directory: `"."` and `".."`, which represent the current and parent directories, respectively. Both of these items have type ``FSItem/ItemType/directory``. For the root directory, `"."` and `".."` have identical contents. Don't pack  `"."` and `".."` if `attributes` isn't `nil`.
///
/// - Parameters:
///   - directory: The item to enumerate. FSKit guarantees this item is of type ``FSItem/ItemType/directory``.
///   - cookie: A value that indicates the location within the directory from which to enumerate. Your implementation defines the semantics of the cookie values; they're opaque to FSKit. The first call to the enumerate method passes ``FSDirectoryCookieInitial`` for this parameter. Subsequent calls pass whatever cookie value you previously passed to the packer's `nextCookie` parmeter.
///   - verifier: A tool to detect whether the directory contents changed since the last call to `enumerateDirectory`. Your implementation defines the semantics of the verifier values; they're opaque to FSKit. The first call to the enumerate method passes ``FSDirectoryVerifierInitial`` for this parameter. Subsequent calls pass whatever cookie value you previously passed to the packer's `currentVerifier` parmeter.
///   - attributes: The desired attributes to provide, or `nil` if the caller doesn't require attributes.
///   - packer: An object that your implementation uses to enumerate directory items, packing one item per callback to `enumerateDirectory`.
///   - reply: A block or closure to indicate success or failure. If enumeration succeeds, pass the current verifier and a `nil` error. If enumeration fails, pass the relevant error as the second parameter; FSKit ignores any verifier in this case. For an `async` Swift implementation, there's no reply handler; simply return the current verifier or throw an error.
-(void)enumerateDirectory:(FSItem *)directory
         startingAtCookie:(FSDirectoryCookie)cookie
                 verifier:(FSDirectoryVerifier)verifier
      providingAttributes:(FSItemGetAttributesRequest * _Nullable)attributes
              usingPacker:(FSDirectoryEntryPacker *)packer
             replyHandler:(void(^)(FSDirectoryVerifier currentVerifier,
                                   NSError * _Nullable error))reply
NS_SWIFT_NAME(enumerateDirectory(_:startingAt:verifier:attributes:packer:replyHandler:));

/// Activates the volume using the specified options.
///
/// When FSKit calls this method, allocate any in-memory state required to represent the file system.
/// Also allocate an ``FSItem`` for the root directory of the file system, and pass it to the reply block.
/// FSKit caches this root item for the lifetime of the volume, and uses it as a starting point for all file look-ups.
///
/// Volume activation occurs prior to any call to mount the volume.
///
/// - Parameters:
///   - options: Options to apply to the activation. These can include security-scoped file paths. There are no defined options currently.
///   - reply: A block or closure to indicate success or failure. If activation succeeds, pass the root ``FSItem`` and a `nil` error. If activation fails, pass the relevant error as the second parameter; FSKit ignores any ``FSItem`` in this case. In Swift, `reply` takes only the ``FSItem`` as the parameter; you signal any error with a `throw`. For an `async` Swift implementation, there's no reply handler; simply return the ``FSItem`` or throw an error.
-(void)activateWithOptions:(FSTaskOptions *)options
              replyHandler:(void (^)(FSItem * _Nullable rootItem,
                                     NSError * _Nullable err))reply
NS_SWIFT_NAME(activate(options:replyHandler:));

/// Tears down a previously initialized volume instance.
///
/// Set up your implementation to release any resources allocated for the volume instance.
/// By the time you receive this callback, FSKit has already performed a reclaim call to release all other file nodes associated with this file system instance.
///
/// Avoid performing any I/O in this method.
/// Prior to calling this method, FSKit has already issued a sync call to perform any
/// cleanup-related I/O.
///
/// FSKit unmounts any mounted volume with a call to ``unmount(replyHandler:)`` prior to the deactivate callback.
///
/// - Parameters:
///   - options: Options to apply to the deactivation.
///   - reply: A block or closure to indicate success or failure. If activation fails, pass an error as the one parameter to the reply handler. If activation succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)deactivateWithOptions:(FSDeactivateOptions)options
                replyHandler:(void (^)(NSError * _Nullable err))reply
NS_SWIFT_NAME(deactivate(options:replyHandler:));

@end

/// Flags to specify the policy when setting extended file attributes.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(NSUInteger, FSSetXattrPolicy) {
    /// Set the value, regardless of previous state.
    FSSetXattrPolicyAlwaysSet      = 0,
    /// Set the value, but fail if the extended attribute already exists.
    FSSetXattrPolicyMustCreate     = 1,
    /// Set the value, but fail if the extended attribute doesn't already exist.
    FSSetXattrPolicyMustReplace    = 2,
    /// Delete the value, failing if the extended attribute doesn't exist.
    FSSetXattrPolicyDelete         = 3
} NS_SWIFT_NAME(FSVolume.SetXattrPolicy);

/// Methods and properties implemented by volumes that natively or partially support extended attributes.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.XattrOperations)
@protocol FSVolumeXattrOperations <NSObject>

@optional
/// A Boolean value that instructs FSKit not to call this protocol's methods, even if the volume conforms to it.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property BOOL xattrOperationsInhibited;

/// Returns an array that specifies the extended attribute names the given item supports.
///
/// If `item` supports no extended attributes, this method returns `nil`.
///
/// Only implement this method if your volume works with "limited" extended attributes.
/// For purposes of this protocol, "limited" support means the volume doesn't support extended attributes generally, but uses these APIs to expose specific file system data.
///
/// > Note: If a file system implements this method, FSKit assumes limited support for extended attributes exists. In this mode, FSkit only calls this protocol's methods for the extended attribute names this method returns.
///
/// - Parameter item: The item for which to get information.
-(NSArray<FSFileName *> *)supportedXattrNamesForItem:(FSItem *)item;

@required

/// Gets the specified extended attribute of the given item.
///
/// - Parameters:
///   - name: The extended attribute name.
///   - item: The item for which to get the extended attribute.
///   - reply: A block or closure to indicate success or failure. If getting the attribute succeeds, pass an data instance containing the extended attribute data and a `nil` error. If getting the attribute fails, pass the relevant error as the second parameter; FSKit ignores any data in this case. For an `async` Swift implementation, there's no reply handler; simply return the data or throw an error.
-(void)getXattrNamed:(FSFileName *)name
              ofItem:(FSItem *)item
        replyHandler:(void (^)(NSData * _Nullable value,
                               NSError * _Nullable error))reply
NS_SWIFT_NAME(getXattr(named:of:replyHandler:))
NS_SWIFT_ASYNC_NAME(xattr(named:of:));

/// Sets the specified extended attribute data on the given item.
///
/// - Parameters:
///   - name: The extended attribute name.
///   - value: The extended attribute value to set. This can't be `nil`, unless the policy is ``FSVolume/SetXattrPolicy/delete``.
///   - item: The item on which to set the extended attribute.
///   - policy: The policy to apply when setting the attribute. See ``FSSetXattrPolicy`` for possible values.
///   - reply: A block or closure to indicate success or failure. If setting the attribute fails, pass an error as the one parameter to the reply handler. If setting the attribute succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)setXattrNamed:(FSFileName *)name
              toData:(NSData * _Nullable)value
              onItem:(FSItem *)item
              policy:(FSSetXattrPolicy)policy
        replyHandler:(void (^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(setXattr(named:to:on:policy:replyHandler:));

/// Gets the list of extended attributes currently set on the given item.
///
/// - Parameters:
///   - item: The item from which to get extended attributes.
///   - reply: A block or closure to indicate success or failure. If getting the list of extended attributes succeeds, pass the xattrs as an array of ``FSFileName`` instances and a `nil` error. If getting the attriubtes fails, pass `nil` along with the relevant error. For an `async` Swift implementation, there's no reply handler; simply return the byte count or throw an error.

-(void)listXattrsOfItem:(FSItem *)item
           replyHandler:(void (^)(NSArray <FSFileName *> * _Nullable value,
                                  NSError * _Nullable error))reply
NS_SWIFT_ASYNC_NAME(xattrs(of:));

@end

/// Defined modes for opening a file.
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSUInteger, FSVolumeOpenModes) {
    /// The read mode.
    ///
    /// This mode is equivalent to POSIX `FREAD`.
    FSVolumeOpenModesRead = FREAD,
    /// The write mode.
    ///
    /// This mode is equivalent to POSIX `FRWITE`.
    FSVolumeOpenModesWrite = FWRITE
} NS_SWIFT_NAME(FSVolume.OpenModes);

/// Methods and properties implemented by volumes that want to receive open and close calls for each item.
///
/// When a file system volume conforms to this protocol, the kernel layer issues an open call to indicate desired access, and a close call to indicate what access to retain.
/// A file is fully closed when the kernel layer issues a close call with no retained open nodes.
/// When a file system receives the close call, it removes all access to the item.
/// When all memory mappings to the item release, the kernel layer issues a final close.
///
/// If a file system volume doesn't conform to this protocol, the kernel layer can skip making such calls to the volume.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.OpenCloseOperations)
@protocol FSVolumeOpenCloseOperations <NSObject>

@optional
/// A Boolean value that instructs FSKit not to call this protocol's methods, even if the volume conforms to it.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property (getter = isOpenCloseInhibited) BOOL openCloseInhibited;

@required
/// Opens a file for access.
///
/// - Parameters:
///   - item: The item to open.
///   - modes: The set of mode flags to open the item with.
///   - reply: A block or closure to indicate success or failure. If opening fails, pass an error as the one parameter to the reply handler. If opening succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)openItem:(FSItem *)item
      withModes:(FSVolumeOpenModes)modes
   replyHandler:(void (^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(openItem(_:modes:replyHandler:));

/// Closes a file from further access.
///
/// - Parameters:
///   - item: The item to close.
///   - modes: The set of mode flags to keep after this close.
///   - reply: A block or closure to indicate success or failure. If closing fails, pass an error as the one parameter to the reply handler. If closing succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)closeItem:(FSItem *)item
    keepingModes:(FSVolumeOpenModes)modes
    replyHandler:(void (^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(closeItem(_:modes:replyHandler:));

@end

/// Methods implemented for read and write operations that deliver data to and from the extension.
///
/// Most volumes conform to either this protocol or ``FSVolumeKernelOffloadedIOOperations``.
/// You can conform to both if you need to provide kernel-offloaded I/O only for certain files.
/// In that case, files with the ``FSItem/Attribute/inhibitKernelOffloadedIO`` attribute set use this protocol, and those without it use ``FSVolumeKernelOffloadedIOOperations``.
/// A volume that doesn't conform to either protocol can't support any I/O operation.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.ReadWriteOperations)
@protocol FSVolumeReadWriteOperations <NSObject>

/// Reads the contents of the given file item.
///
/// If the number of bytes requested exceeds the number of bytes available before the end of the file, then the call copies only those bytes to `buffer`.
/// If `offset` points past the last valid byte of the file, don't reply with an error but set `actuallyRead` to `0`.
///
/// - Parameters:
///   - item: The item from which to read. FSKit guarantees this item will be of type ``FSItem/ItemType/file``.
///   - offset: The offset in the file from which to start reading.
///   - length: The number of bytes to read.
///   - buffer: A buffer to receive the bytes read from the file.
///   - reply: A block or closure to indicate success or failure. If reading succeeds, pass the number of bytes read and a `nil` error. If reading fails, pass the number of bytes read prior to the error along with the relevant error. For an `async` Swift implementation, there's no reply handler; simply return the byte count or throw an error.
-(void)readFromFile:(FSItem *)item
             offset:(off_t)offset
             length:(size_t)length
         intoBuffer:(FSMutableFileDataBuffer *)buffer
       replyHandler:(void(^)(size_t actuallyRead,
                             NSError * _Nullable error))reply
NS_SWIFT_NAME(read(from:at:length:into:replyHandler:));

/// Writes contents to the given file item.
///
/// FSKit expects this routine to allocate space in the file system to extend the file as necessary.
///
/// If the volume experiences an out-of-space condition, reply with an error of domain <doc://com.apple.documentation/documentation/Foundation/NSPOSIXErrorDomain> and code `ENOSPC`.
///
/// - Parameters:
///   - contents: A buffer containing the data to write to the file.
///   - item: The item to which to write. FSKit guarantees this item will be of type ``FSItem/ItemType/file``.
///   - offset: The offset in the file from which to start writing.
///   - reply: A block or closure to indicate success or failure. If writing succeeds, pass the number of bytes written and a `nil` error. If writing fails, pass the number of bytes written prior to the error along with the relevant error. For an `async` Swift implementation, there's no reply handler; simply return the byte count or throw an error.
- (void)writeContents:(NSData *)contents
               toFile:(FSItem *)item
             atOffset:(off_t)offset
         replyHandler:(void(^)(size_t actuallyWritten,
                               NSError * _Nullable error))reply
NS_SWIFT_NAME(write(contents:to:at:replyHandler:));

@end

/// A bitmask of access rights.
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSUInteger, FSAccessMask) {
    /// The file system allows reading data.
    FSAccessReadData            = (1<<1),
    /// The file system allows listing directory contents.
    FSAccessListDirectory       = FSAccessReadData,
    /// The file system allows writing data.
    FSAccessWriteData           = (1<<2),
    /// The file system allows adding files.
    FSAccessAddFile             = FSAccessWriteData,
    /// The file system allows file executuion.
    FSAccessExecute             = (1<<3),
    /// The file system allows searching files.
    FSAccessSearch              = FSAccessExecute,
    /// The file system allows deleting a file.
    FSAccessDelete              = (1<<4),
    /// The file system allows appending data to a file.
    FSAccessAppendData          = (1<<5),
    /// The file system allows adding subdirectories.
    FSAccessAddSubdirectory     = FSAccessAppendData,
    /// The file system allows deleting subdirectories.
    FSAccessDeleteChild         = (1<<6),
    /// The file system allows reading file attributes.
    FSAccessReadAttributes      = (1<<7),
    /// The file system allows writing file attributes.
    FSAccessWriteAttributes     = (1<<8),
    /// The file system allows reading extended file attributes.
    FSAccessReadXattr           = (1<<9),
    /// The file system allows writing extended file attributes.
    FSAccessWriteXattr          = (1<<10),
    /// The file system allows reading a file's security descriptors.
    FSAccessReadSecurity        = (1<<11),
    /// The file system allows writing a file's security descriptors.
    FSAccessWriteSecurity       = (1<<12),
    /// The file system allows taking ownership of a file.
    FSAccessTakeOwnership       = (1<<13),
} NS_SWIFT_NAME(FSVolume.AccessMask);

/// Methods and properties implemented by volumes that want to enforce access check operations.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.AccessCheckOperations)
@protocol FSVolumeAccessCheckOperations <NSObject>

@optional
/// A Boolean value that instructs FSKit not to call this protocol's methods, even if the volume conforms to it.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property (getter = isAccessCheckInhibited) BOOL accessCheckInhibited;

@required

/// Checks whether the file system allows access to the given item.
///
/// - Parameters:
///   - theItem: The item for which to check access.
///   - access: A mask indicating a set of access types for which to check.
///   - reply: A block or closure to indicate success or failure. If the access check succeeds, pass a Boolean value to indicate whether the file system grants access, followed by a `nil` error. If the access check fails, pass the relevant error as the second parameter; FSKit ignores the Boolean parameter in this case. For an `async` Swift implementation, there's no reply handler; simply return the `Bool` or throw an error.
-(void)checkAccessToItem:(FSItem *)theItem
         requestedAccess:(FSAccessMask)access
            replyHandler:(void(^)(BOOL shouldAllowAccess,
                                  NSError * _Nullable error))reply;

@end

/// Methods and properties implemented by volumes that support renaming the volume.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.RenameOperations)
@protocol FSVolumeRenameOperations <NSObject>

@optional
/// A Boolean value that instructs FSKit not to call this protocol's methods, even if the volume conforms to it.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property (getter = isVolumeRenameInhibited) BOOL volumeRenameInhibited;

@required
/// Sets a new name for the volume.
///
/// - Parameters:
///   - name: The new volume name.
///   - reply: A block or closure to indicate success or failure. If renaming succeeds, pass an ``FSFileName`` of the new volume name and a `nil` error. If renaming fails, pass the relevant error as the second parameter; FSKit ignores any ``FSFileName`` in this case. For an `async` Swift implementation, there's no reply handler; simply return the ``FSFileName`` or throw an error.
-(void)setVolumeName:(FSFileName *)name
        replyHandler:(void(^)(FSFileName * _Nullable newName,
                              NSError * _Nullable error))reply;

@end

/// Behavior flags for preallocation operations.
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSUInteger, FSPreallocateFlags) {
    /// Allocates contiguous space.
    FSPreallocateFlagsContiguous    = 0x00000002,
    /// Allocates all requested space or no space at all.
    FSPreallocateFlagsAll           = 0x00000004,
    /// Allocates space that isn't freed when deleting the descriptor.
    ///
    /// This space remains allocated even after calling `close(2)`.
    FSPreallocateFlagsPersist       = 0x00000008,
    /// Allocates space from the physical end of file.
    ///
    /// When implementing this behavior, ignore any offset in the preallocate call.
    /// This flag is currently set for all ``FSVolume/PreallocateOperations/preallocateSpace(for:at:length:flags:replyHandler:)`` calls.
    FSPreallocateFlagsFromEOF       = 0x00000010,
} NS_SWIFT_NAME(FSVolume.PreallocateFlags);

/// Methods and properties implemented by volumes that want to offer preallocation functions.
///
/// A preallocation operation allocates space for a file without writing to it yet.
/// A file system may use reallocation to avoid performing space allocation while in the midst of I/O; this strategy improves performance.
/// Also, if the expected I/O pattern is many small writes, preallocating contiguous chunks may prevent fragmenting the file system.
/// This process can improve performance later.
///
/// In a kernel-based file system, you typically preallocate space with the `VNOP_ALLOCATE` operation, called from `fcntl(F_PREALLOCATE)`.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.PreallocateOperations)
@protocol FSVolumePreallocateOperations <NSObject>

@optional
/// A Boolean value that instructs FSKit not to call this protocol's methods, even if the volume conforms to it.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property (getter = isPreallocateInhibited) BOOL preallocateInhibited;

@required
/// Prealocates disk space for the given item.
///
/// - Parameters:
///   - item: The item for which to preallocate space.
///   - offset: The offset from which to allocate.
///   - length: The length of the space in bytes.
///   - flags: Flags that affect the preallocation behavior.
///   - reply: A block or closure to indicate success or failure. If preallocation succeeds, pass the amount of bytes allocated and a `nil` error. If preallocation fails, pass the relevant error as the second parameter; FSKit ignores any byte count in this case. For an `async` Swift implementation, there's no reply handler; simply return the allocated byte count or throw an error.
-(void)preallocateSpaceForItem:(FSItem *)item
                      atOffset:(off_t)offset
                        length:(size_t)length
                         flags:(FSPreallocateFlags)flags
                  replyHandler:(void(^)(size_t bytesAllocated,
                                        NSError * _Nullable error))reply
NS_SWIFT_NAME(preallocateSpace(for:at:length:flags:replyHandler:));

@end

/// Options to specify the item deactivation policy.
///
/// Callers may want to set a deactivation policy because ``FSVolume/ItemDeactivation/deactivateItem(_:replyHandler:)`` processing blocks the kernel.
/// Setting a deactivation policy allows the file system to take action at a definitive point in the item's life cycle.
/// These options allow the file system to instruct the FSKit kernel of which circumstances require the expense of a round-trip call to the module.
///
/// > Note: To avoid performing deactivation calls, Objective-C developers use the value `FSItemDeactivationNever`. In Swift, use an empty option set (`[]`).
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSUInteger, FSItemDeactivationOptions) {
    /// An option to never perform deactivation.
    ///
    /// With this deactivation option, FSKit never issues `deactivateItem` calls, even though the volume conforms to ``FSVolume/ItemDeactivation``.
    FSItemDeactivationNever                 = 0,
    /// An option to always perform deactivation calls.
    ///
    /// Use this option if the file system needs `deactivateItem` calls in circumstances beyond those covered by ``forRemovedItems`` and ``forPreallocatedItems``.
    FSItemDeactivationAlways                = NSUIntegerMax, // all bits
    /// An option to process deactivation for open-unlinked items at the moment of last close.
    FSItemDeactivationForRemovedItems       = (1 << 0),
    /// An option to process deactivation for for files with preallocated space.
    ///
    /// This option facilitates a sort of trim-on-close behavior.
    /// It is only meaningful for volumes that conform to ``FSVolume/PreallocateOperations``.
    FSItemDeactivationForPreallocatedItems  = (1 << 1),
} NS_SWIFT_NAME(FSVolume.ItemDeactivationOptions);

/// Methods and properties implemented by volumes that support deactivating items.
FSKIT_API_AVAILABILITY_V1
NS_SWIFT_NAME(FSVolume.ItemDeactivation)
@protocol FSVolumeItemDeactivation <NSObject>

/// A property that tells FSKit to which types of items the deactivation applies, if any.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property (readonly) FSItemDeactivationOptions itemDeactivationPolicy;

/// Notifies the file system that the kernel is no longer making immediate use of the given item.
///
/// This method gives a file system a chance to release resources associated wtih an item.
/// However, this method prescribes no specific action; it's acceptable to defer all reclamation until ``FSVolume/Operations/reclaimItem(_:replyHandler:)``.
/// This method is the equivalent of VFS's `VNOP_INACTIVE`.
///
/// FSKit restricts calls to this method based on the current value of ``FSVolume/ItemDeactivation/itemDeactivationPolicy``.
///
/// - Parameters:
///   - item: The item to deactivate.
///   - reply: A block or closure to indicate success or failure. If deactivation fails, pass an error as the one parameter to the reply handler. If deactivation succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
-(void)deactivateItem:(FSItem *)item
         replyHandler:(void(^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(deactivateItem(_:replyHandler:));

@end

NS_ASSUME_NONNULL_END
