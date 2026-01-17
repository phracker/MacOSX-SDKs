//
//  Copyright (c) 2024 Apple Inc. All rights reserved.
//
//  FSVolumeExtent.h
//  FSKit
//

/*
 * For block device resource file systems, FSKit offers a facility called
 * Kernel-Offloaded I/O (KOIO) allowing higher file transfer performance.
 * Rather than transfer file data between the module and the kernel, the module
 * supplies file extent mappings to the kernel and the kernel then performs data
 * transfers directly, using the same infrastructure as KEXT file systems.
 *
 * This file contains definitions related to the Kernel-Offloaded I/O mechanism.
 */

#import <Foundation/Foundation.h>
#import <FSKit/FSResource.h>
#import <FSKit/FSVolume.h>

NS_ASSUME_NONNULL_BEGIN

/// A unique identifier for an operation.
FSKIT_API_AVAILABILITY_V1
typedef NSUInteger FSOperationID NS_TYPED_EXTENSIBLE_ENUM;

FSKIT_API_AVAILABILITY_V1
FS_EXPORT FSOperationID const FSOperationIDUnspecified;

/// Flags that describe the behavior of a blockmap operation.
///
/// This type is an option set in Swift.
/// In Objective-C, you use the cases of this enumeration to create a bit field.
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSUInteger, FSBlockmapFlags) {
    /// A flag that describes a read operation.
    FSBlockmapFlagsRead          = 0x000100,
    /// A flag that describes a write operation.
    FSBlockmapFlagsWrite         = 0x000200,
};

/// Flags that describe the behavior of an I/O completion operation.
///
/// This type is an option set in Swift.
/// In Objective-C, the cases of this enumeration combine to create a bit field.
FSKIT_API_AVAILABILITY_V1
typedef NS_OPTIONS(NSUInteger, FSCompleteIOFlags) {
    /// A flag that describes a read operation.
    FSCompleteIOFlagsRead          = FSBlockmapFlagsRead,
    /// A flag that describes a write operation.
    FSCompleteIOFlagsWrite         = FSBlockmapFlagsWrite,
    /// A flag that requests that the file system module flush metadata I/O asynchronously.
    FSCompleteIOFlagsAsync         = 0x000400,
};

/**
 * @typedef FSExtentType
 * Possible extent types.
 */

/// An enumeration of types of extents.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(NSInteger, FSExtentType) {
    /// An extent type to indicate valid data.
    ///
    /// Use this type for all extents on a file system that doesn't support sparse files.
    ///
    /// > Tip: The kernel keeps track of the end of file, so it knows a range of `[EOF, allocated space]` is uninitialized. Because of this behavior, it's valid to pass the data extent type for such a range.
    FSExtentTypeData = 0,

    /// An extent type to indicate uninitialized data.
    ///
    /// Only use this extent type in file systems that support sparse files, and only then to represent ranges in the file that aren't allocated yet.
    FSExtentTypeZeroFill = 1,
};

/// A type that directs the kernel to map space on disk to a specific file managed by this file system.
///
/// _Extents_ provide the kernel the logical-to-physical mapping of a given file.
/// An extent describes a physical offset on disk, and a length and a logical offset within the file.
/// Rather than working with extents directly, you use this type's methods to provide or "pack" extent information, which FSKit then passes to the kernel.
FSKIT_API_AVAILABILITY_V1
@interface FSExtentPacker : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// Packs a single extent to send to the kernel.
///
/// - Parameters:
///   - resource: The resource on which to perform I/O.
///   - type: The type of extent, indicating whether it contains valid data.
///   - logicalOffset: The extent offset within the file, in bytes.
///   - physicalOffset: The extent offset on disk, in bytes.
///   - length: The extent length, in bytes.
/// - Returns: A Boolean value that indicates whether the packer can pack more extents.
- (BOOL)packExtentWithResource:(FSBlockDeviceResource *)resource
                          type:(FSExtentType)type
                 logicalOffset:(off_t)logicalOffset
                physicalOffset:(off_t)physicalOffset
                        length:(size_t)length
NS_SWIFT_NAME(packExtent(resource:type:logicalOffset:physicalOffset:length:));

@end

/// Methods and properties implemented by volumes that use kernel-offloaded I/O to achieve higher file transfer performance.
///
/// A volume that conforms to this protocol supplies file extent mappings to FSKit, which allows file transfers to take place in the kernel.
/// This approach provides higher-performance file transfer than transferring data between the module and kernel, while still allowing the file system to run in user space.
///
/// This protocol uses _extents_ to provide the kernel the logical-to-physical mapping of a given file.
/// An extent describes a physical offset on disk, and a length and a logical offset within the file.
/// You don't manage extents directly.
/// Instead, FSKit provides you with an ``FSExtentPacker`` to define and pack the extents in your implementations of this protocol's methods.
///
/// Most volumes conform to either this protocol or ``FSVolumeReadWriteOperations``.
/// You can conform to both if you need to provide kernel-offloaded I/O only for certain files.
/// In that case, files with the ``FSItem/Attribute/inhibitKernelOffloadedIO`` attribute set use ``FSVolumeReadWriteOperations``, and those without it use this protocol.
/// A volume that doesn't conform to either protocol can't support any I/O operation.
FSKIT_API_AVAILABILITY_V1
@protocol FSVolumeKernelOffloadedIOOperations <NSObject>

#pragma mark - Kernel Offloaded IO operations

/// Maps a file's disk space into extents, allowing the kernel to perform I/O with that space.
///
/// FSKit calls this method when the kernel needs to get a mapping of logical-to-physical offsets of the file's data.
/// This call may occur as part of an I/O operation on the file, or just to get the mapping as part of a `fcntl(F_LOG2PHYS)` system call.
/// In the case of an I/O operation on the file, `operationID` has a nonzero value; a future call to ``completeIO(for:offset:length:status:flags:operationID:replyHandler:)`` uses the same `operationID` to indicate which operation it completes.
/// In the case of a `fcntl(F_LOG2PHYS)` system call, the `operationID` parameter is `0` (Objective-C) or ``FSOperationID/unspecified`` (Swift).
/// In both cases the kernel retains the mapping, and it may perform I/O to this range (or a part of it) at any time.
///
/// If satisfying a blockmap request requires more extents than `packer` can handle, FSKit makes additional calls to this method with the same operation ID to collect the remainder.
///
/// - Parameters:
///   - file: The file for which to map disk space.
///   - offset: The starting logical offset of the range to be mapped (in bytes).
///   - length: The length of the range to be mapped (in bytes).
///   - flags: Flags that affect the behavior of the blockmap operation.
///   - operationID: A unique identifier of the blockmap call. Any value other than `0` (Objective-C) or ``FSOperationID/unspecified`` (Swift) indicates the beginning of an I/O operation. A value of `0` or ``FSOperationID/unspecified`` indicates the kernel maps the file without performing I/O. In this case, FSKit doesn't perform a corresponding call to ``completeIO(for:offset:length:status:flags:operationID:replyHandler:)``.
///   - packer: An extent packer you use to pack the requested range of the file's allocated disk space. FSKit sends all of the packed extents to the kernel when it invokes `reply`.
///   - reply: A block or closure to indicate success or failure. If mapping fails, pass an error as the one parameter to the reply handler. If mapping succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
- (void)blockmapFile:(FSItem *)file
              offset:(off_t)offset
              length:(size_t)length
               flags:(FSBlockmapFlags)flags
         operationID:(FSOperationID)operationID
              packer:(FSExtentPacker *)packer
        replyHandler:(void (^)(NSError * _Nullable error))reply;

/// Completes an I/O operation for a given file.
///
/// Implement this method by updating a file's metadata, such as its size and modification time.
///
/// FSKit may call this method without an earlier call to ``blockmapFile(_:offset:length:flags:operationID:packer:replyHandler:)``.
/// In this case, the `operationID` is `0` (Objective-C) or ``FSOperationID/unspecified`` (Swift).
///
/// - Parameters:
///   - file: The file for which the I/O operation completed.
///   - offset: The starting logical offset at which I/O started.
///   - length: The length of the I/O range (in bytes).
///   - status: Any error that occurred during the operation. If no error occurred, this parameter is `nil`.
///   - flags: Flags that affect the behavior of the complete I/O operation.
///   - operationID: A unique identifier of the blockmap call. Any value other than `0` (Objective-C) or ``FSOperationID/unspecified`` (Swift) corresponds to a previous call to ``blockmapFile(_:offset:length:flags:operationID:packer:replyHandler:)`` with the same `operationID`.
///   - reply: A block or closure to indicate success or failure. If completing I/O fails, pass an error as the one parameter to the reply handler. If completing I/O succeeds, pass `nil`. For an `async` Swift implementation, there's no reply handler; simply throw an error or return normally.
- (void)completeIOForFile:(FSItem *)file
                   offset:(off_t)offset
                   length:(size_t)length
                   status:(NSError *)status
                    flags:(FSCompleteIOFlags)flags
              operationID:(FSOperationID)operationID
             replyHandler:(void (^)(NSError * _Nullable error))reply
NS_SWIFT_NAME(completeIO(for:offset:length:status:flags:operationID:replyHandler:));

#pragma mark - extent-supplying versions of create and lookup
/*
 * These methods allow the module to opportunistically supply extents in order
 * to save future 'blockmapFile' calls.  An implementation not supplying the
 * extents can ignore the packer, and call the corresponding FSVolumeOperation's
 * method.
 */

/// Creates a new file item and map its disk space.
///
/// This method allows the module to opportunistically supply extents, avoiding future calls to ``blockmapFile(_:offset:length:flags:operationID:packer:replyHandler:)``.
/// Only perform this technique opportunistically.
/// In particular, don't perform additional I/O to fetch extent data.
///
/// Packing extents in this method requires that `attributes` defines a size greater than 0.
///
/// An implementation that doesn't supply the extents can ignore the packer and call the corresponding method in the ``FSVolume/Operations`` protocol, ``FSVolume/Operations/createItem(named:type:inDirectory:attributes:replyHandler:)``.
///
/// - Parameters:
///   - name: The new file's name.
///   - directory: The directory in which to create the file.
///   - attributes: Attributes to apply to the new file.
///   - packer: An extent packer you use to pack the file's allocated disk space.
///   - reply: A block or closure to indicate success or failure. If creation succeeds, pass the newly created ``FSItem`` and its ``FSFileName``, along with a `nil` error. If creation fails, pass the relevant error as the third parameter; FSKit ignores any ``FSItem`` or ``FSFileName`` in this case. For an `async` Swift implementation, there's no reply handler; instead, return a tuple of the ``FSItem`` and its ``FSFileName`` or throw an error.
- (void)createFileNamed:(FSFileName *)name
            inDirectory:(FSItem *)directory
             attributes:(FSItemSetAttributesRequest *)attributes
                 packer:(FSExtentPacker *)packer
           replyHandler:(void(^)(FSItem * _Nullable newFile,
                                 FSFileName * _Nullable newFileName,
                                 NSError * _Nullable error))reply
NS_SWIFT_NAME(createFile(name:in:attributes:packer:replyHandler:));

/// Looks up an item within a directory and maps its disk space.
///
/// This method allows the module to opportunistically supply extents, avoiding future calls to ``blockmapFile(_:offset:length:flags:operationID:packer:replyHandler:)``.
/// Only perform this technique opportunistically.
/// In particular, don't perform additional I/O to fetch extent data.
///
/// - Parameters:
///   - name: The name of the file to look up.
///   - directory: The directory in which to look up the file.
///   - packer: An extent packer you use to pack the file's allocated disk space.
///   - reply: A block or closure to indicate success or failure. If lookup succeeds, pass the found ``FSItem`` and its ``FSFileName``, along with a `nil` error. If lookup fails, pass the relevant error as the third parameter; FSKit ignores any ``FSItem`` or ``FSFileName`` in this case. For an `async` Swift implementation, there's no reply handler; instead, return a tuple of the ``FSItem`` and its ``FSFileName`` or throw an error.
- (void)lookupItemNamed:(FSFileName *)name
            inDirectory:(FSItem *)directory
                 packer:(FSExtentPacker *)packer
           replyHandler:(void(^)(FSItem * _Nullable theItem,
                                 FSFileName * _Nullable itemName,
                                 NSError * _Nullable error))reply
NS_SWIFT_NAME(lookupItem(name:in:packer:replyHandler:));

#pragma mark - extent-supplying version of preallocate

@optional

/// Preallocates and maps disk space for the given file.
///
/// This method allows the module to opportunistically supply extents, avoiding future calls to ``blockmapFile(_:offset:length:flags:operationID:packer:replyHandler:)``.
///
/// > Important: Only implement this method if your file system conforms to ``FSVolume/PreallocateOperations``.
///
/// - Parameters:
///   - file: The item for which to preallocate space.
///   - offset: The offset from which to allocate.
///   - length: The length of the space in bytes.
///   - flags: Flags that affect the preallocation behavior.
///   - packer: An extent packer you use to pack the file's preallocated disk space.
///   - reply: A block or closure to indicate success or failure. If preallocation succeeds, pass the amount of bytes allocated and a nil error. If preallocation fails, pass the relevant error as the second parameter; FSKit ignores any byte count in this case. For an `async` Swift implementation, there’s no reply handler; simply return the allocated byte count or throw an error.
- (void)preallocateSpaceForFile:(FSItem *)file
                       atOffset:(off_t)offset
                         length:(size_t)length
                          flags:(FSPreallocateFlags)flags
                         packer:(FSExtentPacker *)packer
                   replyHandler:(void(^)(size_t bytesAllocated,
                                         NSError * _Nullable error))reply
NS_SWIFT_NAME(preallocateSpace(for:at:length:flags:packer:replyHandler:));

@end

NS_ASSUME_NONNULL_END
