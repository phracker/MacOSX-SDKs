//
//  Copyright (c) 2022-2023 Apple Inc. All rights reserved.
//
//  FSResource.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSContainer.h>
#import <FSKit/FSKitDefines.h>
#import <FSKit/FSKitTypes.h>
#import <FSKit/FSTask.h>
#import <FSKit/FSTaskOptions.h>

NS_ASSUME_NONNULL_BEGIN

/// A type that represents the recognition and usability of a probed resource.
FSKIT_API_AVAILABILITY_V1
typedef NS_ENUM(NSInteger, FSMatchResult) {
    /// The probe doesn't recognize the resource.
    ///
    /// This match result is appropriate when the file system module determines that the resource uses a completely different format.
    FSMatchResultNotRecognized = 0,
    /// The probe recognizes the resource but can't use it.
    ///
    /// This match result is appropriate when the file system module identifies the resource's format but can't use it. For example, if the resource uses a newer version than the module supports, the module can name the resource but can't safely do anything with it.
    FSMatchResultRecognized,
    /// The probe recognizes the resource and is ready to use it, but only in a limited capacity.
    ///
    /// This match result is appropriate when the file system module identifies the resource's format but also identifies incompatibilities. For example, if the module determines the resource uses new features that the module doesn't support, the module may only offer read-only access.
    FSMatchResultUsableButLimited,
    /// The probe recognizes the resource and is ready to use it.
    FSMatchResultUsable,
};

/// An abstract resource a file system uses to provide data for a volume.
///
/// `FSResource` is a base class to represent the various possible sources of data for a file system.
/// These range from dedicated storage devices like hard drives and flash storage to network connections, and beyond.
/// Subclasses define behavior specific to a given kind of resource, such as ``FSBlockDeviceResource-c.class`` for disk partition (IOMedia) file systems.
/// These file systems are typical disk file systems such as HFS, APFS, ExFAT, ext2fs, or NTFS.
///
/// A resource's type also determines its life cycle.
/// Resources based on block storage devices come into being when the system probes the media underlying the volumes and container.
/// Other kinds of resources, like those based on URLs, might have different life cycles.
/// For example, a resource based on a `file://` URL might iniitalize when a person uses the "Connect to server" command in the macOS Finder.
///
/// ### Proxying resources
///
/// Some resources, like ``FSBlockDeviceResource``, come in proxy and non-proxy variants.
/// This addresses the issue that opening an external device like `/dev/disk2s1` requires an entitlement.
/// Proxy resources allow unentitled clients of FSKit to describe which disk an ``FSBlockDeviceResource`` should represent.
/// This allows, for example, the `mount(8)` tool to mount FSKit file systems on block devices when run as root.
/// The tool uses a proxy when executing a command like `mount -t ffs /dev/disk2s1 /some/path`, which prevents leaking privileged resource access.
FSKIT_API_AVAILABILITY_V1
@interface FSResource : NSObject<NSSecureCoding>

/// A Boolean value that indicates whether the resource is revoked.
///
/// If this is a proxy resource, the value of this property is always `true` (Swift) or `YES` (Objective-C).
@property (nonatomic, readonly, getter=isRevoked) BOOL revoked;

- (instancetype)init NS_UNAVAILABLE;

/// Creates a proxy object of this resource.
///
/// If you create a proxy from a proxy resource, this method returns a copy of the proxy.
- (instancetype)makeProxy;

/// Revokes the resource.
///
/// This method works by stripping away any underlying privileges associated with the resource.
/// This effectively disconnects this object from its underlying resource.
- (void)revoke;

@end

#pragma mark - FSBlockDeviceResource class and helpers

/// A range that describes contiguous metadata segments on disk.
///
/// This type represents a range that begins at `startOffset` and ends at `startOffset + segmentLength * segmentCount`.
/// Each segment in the range represents a single block in the resource's buffer cache.
///
/// For example, given an `FSMetadataRange` with the following properties:
///
/// * `startOffset = 0`
/// * `segmentLength = 512`
/// * `segmentCount = 8`
///
/// The range represents eight segments: from 0 to 511, then from 512 to 1023, and so on until a final segment of 3584 to 4095.
///
/// Ensure that each metadata segment represents a range that's already present in the resource's buffer cache.
/// Similarly, ensure that each segment's offset and length matches the offset and length of the corresponding block in the buffer cache.
@interface FSMetadataRange : NSObject

/// The start offset of the range in bytes.
///
/// Ensure this value is a multiple of the corresponding resource's ``FSBlockDeviceResource-c.class/blockSize``.
@property (readonly) off_t     startOffset;

/// The segment length in bytes.
///
/// Ensure this value is a multiple of the corresponding resource's ``FSBlockDeviceResource-c.class/blockSize``.
@property (readonly) uint64_t  segmentLength;

/// The number of segments in the range.
@property (readonly) uint64_t  segmentCount;

/// Initializes a metadata range with the given properties.
///
/// - Parameters:
///   - startOffset: The start offset of the range in bytes. Ensure this value is a multiple of the corresponding resource's ``FSBlockDeviceResource-c.class/blockSize``.
///   - segmentLength: The segment length in bytes. Ensure this value is a multiple of the corresponding resource's ``FSBlockDeviceResource-c.class/blockSize``.
///   - segmentCount: The number of segments in the range.
-(instancetype)initWithOffset:(off_t)startOffset
                segmentLength:(uint64_t)segmentLength
                 segmentCount:(uint64_t)segmentCount;

/// Creates a metadata range with the given properties.
/// - Parameters:
///   - startOffset: The start offset of the range in bytes. Ensure this value is a multiple of the corresponding resource's ``FSBlockDeviceResource-c.class/blockSize``.
///   - segmentLength: The segment length in bytes. Ensure this value is a multiple of the corresponding resource's ``FSBlockDeviceResource-c.class/blockSize``.
///   - segmentCount: The number of segments in the range.
+(instancetype)rangeWithOffset:(off_t)startOffset
                 segmentLength:(uint64_t)segmentLength
                  segmentCount:(uint64_t)segmentCount;

- (instancetype)init NS_UNAVAILABLE;

@end

/// A resource that represents a block storage disk partition.
///
/// A `FSBlockDeviceResource` can exist in either a proxied or nonproxied version.
///  Only the `fskitd` daemon creates "real" (nonproxied) instances of this class.
///  Client applications and daemons create proxy objects for requests, and `fskitd` opens the underlying device during the processing of the request.
///
///  This class wraps a file descriptor for a disk device or partition.
///  Its fundamental identifier is the BSD disk name (``bsdName``) for the underlying IOMedia object.
///  However, ``FSBlockDeviceResource-c.class`` doesn't expose the underlying file descriptor.
///  Instead, it provides accessor methods that can read from and write to the partition, either directly or using the kernel buffer cache.
///
///  When you use a `FSBlockDeviceResource`, your file system implementation also conforms to a maintenance operation protocol.
///  These protocols add support for checking, repairing, and optionally formatting file systems.
///  The system doesn't mount block device file systems until they pass a file system check.
///  For an ``FSUnaryFileSystem`` that uses `FSBlockDeviceResource`, conform to `FSManageableResourceMaintenanceOperations`.
FSKIT_API_AVAILABILITY_V1
@interface FSBlockDeviceResource : FSResource

/// The device name of the resource.
@property (readonly, copy)      NSString       *BSDName;

/// A Boolean property that indicates whether the resource can write data to the device.
@property (readonly, getter=isWritable)
                                BOOL            writable;

/// The logical block size, the size of data blocks used by the file system.
///
/// This is equivalent to the `DKIOCGETBLOCKSIZE` device parameter.
@property (readonly)            uint64_t        blockSize;

/// The block count on this resource.
@property (readonly)            uint64_t        blockCount;

/// The sector size of the device.
///
/// This is equivalent to the `DKIOCGETPHYSICALBLOCKSIZE` device parameter.
@property (readonly)            uint64_t        physicalBlockSize;

- (instancetype)init NS_UNAVAILABLE;


/// Reads data from the resource into a buffer and executes a block afterwards.
///
/// For the read to succeed, requests must conform to any transfer requirements of the underlying resource.
/// Disk drives typically require sector (`physicalBlockSize`) addressed operations of one or more sector-aligned offsets.
///
/// - Parameters:
///   - buffer: A buffer to receive the data.
///   - offset: The offset into the resource from which to start reading.
///   - length: A maximum number of bytes to read. The completion handler receives a parameter with the actual number of bytes read.
///   - completionHandler: A block that executes after the read operation completes. If successful, the first parameter contains the number of bytes actually read. In the case of an error, the second parameter contains a non-`nil` error. This value is `EFAULT` if `buffer` is `NULL`, or `errno` if reading from the resource failed.
-  (void)readInto:(void *)buffer
       startingAt:(off_t)offset
           length:(size_t)length
completionHandler:(void(^)(size_t actuallyRead,
                           NSError * _Nullable error))completionHandler FSKIT_API_AVAILABILITY_V1 NS_REFINED_FOR_SWIFT;

/// Synchronously reads data from the resource into a buffer.
///
/// This is a synchronous version of ``readInto:startingAt:length:completionHandler:``.
///
/// > Note: In some cases, this method performs a partial read. In this case, the return value is shorter than the requested length, and the `error` is set to `nil`.
///
/// - Parameters:
///   - buffer: A buffer to receive the data.
///   - offset: The offset into the resource from which to start reading.
///   - length: A maximum number of bytes to read. The method's return value contains the actual number of bytes read.
///   - error: On return, any error encountered while reading data, or `nil` if no error occurred.
///
/// - Returns: The actual number of bytes read.
-(size_t)readInto:(void *)buffer
       startingAt:(off_t)offset
           length:(size_t)length
            error:(NSError **)error FSKIT_API_AVAILABILITY_V1 NS_REFINED_FOR_SWIFT;


/// Writes data from from a buffer to the resource and executes a block afterwards.
///
/// For the write to succeed, requests must conform to any transfer requirements of the underlying resource.
/// Disk drives typically require sector (`physicalBlockSize`) addressed operations of one or more sector-aligned offsets.
///
/// - Parameters:
///   - buffer: A buffer to provide the data.
///   - offset: The offset into the resource from which to start writing.
///   - length: A maximum number of bytes to write. The completion handler receives a parameter with the actual number of bytes write.
///   - completionHandler: A block that executes after the write operation completes. If successful, the first parameter contains the number of bytes actually written. In the case of an error, the second parameter contains a non-`nil` error. This value is `EFAULT` if `buffer` is `NULL`, or `errno` if writing to the resource failed.
- (void)writeFrom:(void *)buffer
       startingAt:(off_t)offset
           length:(size_t)length
completionHandler:(void(^)(size_t actuallyWritten,
                           NSError * _Nullable error))completionHandler FSKIT_API_AVAILABILITY_V1 NS_REFINED_FOR_SWIFT;

/// Synchronously writes data from from a buffer to the resource and executes a block afterwards.
///
/// This is a synchronous version of ``writeFrom:startingAt:length:completionHandler:``.
///
/// > Note: In some cases, this method performs a partial write. In this case, the return value is shorter than the requested length, and the `error` is set to `nil`.
///
/// - Parameters:
///   - buffer: A buffer to provide the data.
///   - offset: The offset into the resource from which to start writing.
///   - length: A maximum number of bytes to write. The completion handler receives a parameter with the actual number of bytes write.
///   - error: On return, any error encountered while writing data, or `nil` if no error occurred.
///
/// - Returns: The actual number of bytes written.
-(size_t)writeFrom:(void *)buffer
        startingAt:(off_t)offset
            length:(size_t)length
             error:(NSError **)error FSKIT_API_AVAILABILITY_V1 NS_REFINED_FOR_SWIFT;

/// Synchronously reads file system metadata from the resource into a buffer.
///
/// This method provides access to the Kernel Buffer Cache, which is the primary system cache for file system metadata.
/// Unlike equivalent kernel APIs, this method doesn't hold any kernel-level claim to the underlying buffers.
///
/// For the read to succeed, requests must conform to any transfer requirements of the underlying resource.
/// Disk drives typically require sector (`physicalBlockSize`) addressed operations of one or more sector-aligned offsets.
///
/// This method doesn't support partial reading of metadata.
///
/// - Parameters:
///   - buffer: A buffer to receive the data.
///   - offset: The offset into the resource from which to start reading.
///   - length: The number of bytes to read.
///   - error: On return, any error encountered while reading data, or `nil` if no error occurred.
///
/// - Returns: A Boolean value indicating whether the metadata read succeeded.
-(BOOL)metadataReadInto:(void *)buffer
             startingAt:(off_t)offset
                 length:(size_t)length
                  error:(NSError **)error FSKIT_API_AVAILABILITY_V1 NS_REFINED_FOR_SWIFT;

/// Synchronously writes file system metadata from a buffer to the resource.
///
/// This method provides access to the Kernel Buffer Cache, which is the primary system cache for file system metadata.
/// Unlike equivalent kernel APIs, this method doesn't hold any kernel-level claim to the underlying buffers.
///
/// For the write to succeed, requests must conform to any transfer requirements of the underlying resource.
/// Disk drives typically require sector (`physicalBlockSize`) addressed operations of one or more sector-aligned offsets.
///
/// This method doesn't support partial writing of metadata.
///
/// - Parameters:
///   - buffer: A buffer to provide the data.
///   - offset: The offset into the resource from which to start writing.
///   - length: The number of bytes to writing.
///   - error: On return, any error encountered while writing data, or `nil` if no error occurred.
///
/// - Returns: A Boolean value indicating whether the metadata write succeeded.
-(BOOL)metadataWriteFrom:(void *)buffer
              startingAt:(off_t)offset
                  length:(size_t)length
                   error:(NSError **)error FSKIT_API_AVAILABILITY_V1 NS_REFINED_FOR_SWIFT;

/// Writes file system metadata from a buffer to a cache, prior to flushing it to the resource.
///
/// This method provides access to the Kernel Buffer Cache, which is the primary system cache for file system metadata.
/// Unlike equivalent kernel APIs, this method doesn't hold any kernel-level claim to the underlying buffers.
///
/// This method is equivalent to ``metadataWriteFrom:startingAt:length:error:``, except that it writes data to the resource's buffer cache instead of writing to disk immediately.
/// To ensure writing data to disk, the client must flush the metadata by calling ``metadataFlushWithError:`` or ``asynchronousMetadataFlushWithError:``.
///
/// Delayed writes offer two significant advantages:
/// - Delayed writes are more performant, since the file system can avoid waiting for the actual write, reducing I/O latency.
/// - When writing to a specific range repeatedly, delayed writes allow the file system to flush data to the disk only when necessary. This reduces disk usage by eliminating unnecessary writes.
///
/// For the write to succeed, requests must conform to any transfer requirements of the underlying resource.
/// Disk drives typically require sector (`physicalBlockSize`) addressed operations of one or more sector-aligned offsets.
///
/// This method doesn't support partial writing of metadata.
///
/// - Parameters:
///   - buffer: A buffer to provide the data.
///   - offset: The offset into the resource from which to start writing.
///   - length: The number of bytes to writing.
///   - error: On return, any error encountered while writing data, or `nil` if no error occurred.
///
/// - Returns: A Boolean value indicating whether the metadata write succeeded.
-(BOOL)delayedMetadataWriteFrom:(void *)buffer
                     startingAt:(off_t)offset
                         length:(size_t)length
                          error:(NSError **)error FSKIT_API_AVAILABILITY_V1 NS_REFINED_FOR_SWIFT;

/** metadataFlushWithError: - synchronously flush the resource's buffer cache.
    This method preforms metadata flush to the resource, which means any cached metadata operations are being written to the resource.

    Returns values:
    - YES on success
    - NO with an error code of EIO
 */

/// Synchronously flushes the resource's buffer cache.
///
/// This method flushes data previously written with ``delayedMetadataWriteFrom:startingAt:length:error:`` to the resource.
///
/// - Parameter error: On return, any error encountered while writing data, or `nil` if no error occurred.
///
/// - Returns: A Boolean value indicating whether the metadata flush succeeded.
-(BOOL)metadataFlushWithError:(NSError **)error FSKIT_API_AVAILABILITY_V1;

/// Asynchronously flushes the resource's buffer cache.
///
/// This method schedules a flush of data previously written with ``delayedMetadataWriteFrom:startingAt:length:error:`` to the resource and returns immediately without blocking.
/// This method doesn't wait to check the flush's status.
/// If an error prevents the flush from being scheduled, the error is indicated by the in-out `error` parameter.
///
/// - Parameter error: On return, any error encountered while writing data, or `nil` if no error occurred.
///
/// - Returns: A Boolean value indicating whether scheduling the metadata flush succeeded.
-(BOOL)asynchronousMetadataFlushWithError:(NSError **)error FSKIT_API_AVAILABILITY_V1;

/// Clears the given ranges within the buffer cache.
///
/// This method clears the specified ranges in the resource’s buffer cache by writing zeroes into them.
///
/// - Parameters:
///   - rangesToClear: The metadata ranges to clear.
///   - withDelayedWrites: A Boolean value that determines whether to perform the clear operation with delayed writes. The delay works in the same manner as ``delayedMetadataWriteFrom:startingAt:length:error:``. When using delayed writes, the client can flush the metadata with ``metadataFlushWithError:`` or ``asynchronousMetadataFlushWithError:``. The system also flushes stale data in the buffer cache periodically.
///   - error: On return, any error encountered while writing data, or `nil` if no error occurred. This value is `EINVAL` if `rangesToClear` is invalid.
///
/// - Returns: A Boolean value indicating whether clearing the metadata succeeded.
-(BOOL)metadataClear:(NSArray<FSMetadataRange *> *)rangesToClear
   withDelayedWrites:(BOOL)withDelayedWrites
               error:(NSError **)error FSKIT_API_AVAILABILITY_V1;

/// Synchronously purges the given ranges from the buffer cache.
///
/// This method removes the given ranges from the resource's buffer cache.
/// This process drops any dirty data in the cache, preventing the data from reaching the device.
///
/// - Parameters:
///   - rangesToPurge: The metadata ranges to purge.
///   - error: On return, any error encountered while writing data, or `nil` if no error occurred. This value is `EINVAL` if `rangesToPurge` is invalid.
///
/// - Returns: A Boolean value indicating whether purging the metadata succeeded.
-(BOOL)metadataPurge:(NSArray<FSMetadataRange *> *)rangesToPurge
               error:(NSError **)error FSKIT_API_AVAILABILITY_V1;

@end

/// A resource that represents an abstract URL.
///
/// An `FSGenericURLResource` is a completely abstract resource.
/// The only reference to its contents is a single URL, the contents of which are arbitrary.
/// This URL might represent a PCI locator string like `/pci@f0000000/usb@5`, or some sort of network address for a remote file system.
/// FSKit leaves interpretation of the URL and its contents entirely up to your implementation.
///
/// Use the `Info.plist` key `FSSupportedSchemes` to provide an array of case-insensitive URL schemes that your implementation supports.
/// The following example shows how a hypothetical `FSGenericURLResource` implementation declares support for the `rsh` and `ssh` URL schemes:
/// ```
/// <key>FSSupportedSchemes</key>
/// <array>
///     <string>rsh</string>
///     <string>ssh</string>
/// </array>
/// ```
FSKIT_API_AVAILABILITY_V2
@interface FSGenericURLResource : FSResource

/// The URL represented by the resource.
@property (readonly, copy)              NSURL *    url;

/// Creates a generic URL resource with the given URL.
/// - Parameter url: A URL that provides the content of the file system. The format of this URL is completely arbitrary. It's up to your extension to access the contents represented by the URL and make them available as an ``FSVolume`` that FSKit can load.
- (instancetype)initWithURL:(NSURL *)url;

- (instancetype)init NS_UNAVAILABLE;

@end

/// A resource that represents a path in the system file space.
///
/// The URL passed to `FSPathURLResource` may be a security-scoped URL.
/// If the URL is a security-scoped URL, FSKit transports it intact from a client application to your extension.
FSKIT_API_AVAILABILITY_V2
@interface FSPathURLResource : FSResource

/// The URL represented by the resource.
@property (readonly, copy)              NSURL *    url;

/// Creates a path URL resource.
/// - Parameters:
///   - URL: A URL in the system file space that represents the contents of a file system. This parameter uses the `file:` scheme.
///   - writable: A Boolean value that indicates whether the file system supports writing to the contents of the URL.
- (instancetype)initWithURL:(NSURL *)URL
                   writable:(BOOL)writable;

- (instancetype)init NS_UNAVAILABLE;

/// A Boolean value that indicates whether the file system supports writing to the contents of the path URL.
@property (readonly, getter=isWritable)
                                BOOL            writable;

@end

/// Maintenance operations for a file system's resources.
///
/// This protocol includes operations to check and format a resource for an ``FSUnaryFileSystem``.
/// Conform to this protocol if you implement a ``FSUnaryFileSystem`` that uses an ``FSBlockDeviceResource-c.class``.
FSKIT_API_AVAILABILITY_V1
@protocol FSManageableResourceMaintenanceOperations <NSObject>

/// Starts checking the file system with the given options.
///
/// - Parameters:
///   - task: A task object you use to communicate back to the client.
///   - options: Options for performing the check.
///   - error: In Objective-C, a pointer to an <doc://com.apple.documentation/documentation/Foundation/NSError>. Populate this with any error that occurs when starting the check. In Swift, throw an <doc://com.apple.documentation/documentation/Swift/Error> instead.
/// - Returns: An <doc://com.apple.documentation/documentation/Foundation/NSProgress> object that you use to update progress as the check operation progresses. Return `nil` if starting the file system check encountered an error.
-(NSProgress * _Nullable)startCheckWithTask:(FSTask *)task
                                    options:(FSTaskOptions *)options
                                      error:(NSError**)error FSKIT_API_AVAILABILITY_V1 NS_SWIFT_NAME(startCheck(task:options:));

/// Starts formatting the file system with the given options.
///
/// - Parameters:
///   - task: A task object you use to communicate back to the client.
///   - options: Options for performing the format.
///   - error: In Objective-C, a pointer to an <doc://com.apple.documentation/documentation/Foundation/NSError>. Populate this with any error that occurs when starting the format. In Swift, throw an <doc://com.apple.documentation/documentation/Swift/Error> instead.
/// - Returns: An <doc://com.apple.documentation/documentation/Foundation/NSProgress> object that you use to update progress as the format operation progresses. Return `nil` if starting to format the file system encountered an error.
-(NSProgress * _Nullable)startFormatWithTask:(FSTask *)task
                                     options:(FSTaskOptions *)options
                                       error:(NSError**)error FSKIT_API_AVAILABILITY_V1 NS_SWIFT_NAME(startFormat(task:options:));

@end

/// An object that represents the results of a specific probe.
///
/// For any ``result`` value other than ``FSMatchResult/notRecognized``, ensure the ``name`` and ``containerID`` values are non-`nil`.
/// When a container or volume format doesn't use a name, return an empty string.
/// Also use an empty string in the case in which the format supports a name, but the value isn't set yet.
///
/// Some container or volume formats may lack a durable UUID on which to base a container identifier.
/// This situation is only valid for unary file systems.
/// In such a case, return a random UUID.
///
/// With a block device resource, a probe operation may successfully get a result but encounter an error reading the name or UUID.
/// If this happens, use whatever information is available, and provide an empty string or random UUID for the name or container ID, respectively.
FSKIT_API_AVAILABILITY_V1
@interface FSProbeResult : NSObject <NSSecureCoding>

/// The match result, representing the recognition and usability of a probed resource.
@property (readonly)                    FSMatchResult           result;

/// The resource name, as found during the probe operation.
///
/// This value is non-`nil` unless the ``FSProbeResult/result`` is ``FSMatchResult/notRecognized`.
/// For formats that lack a name, this value may be an empty string.
/// This value can also be an empty string if the format supports a name, but the value isn't set yet.
@property (readonly, copy, nullable)    NSString               *name;

/// The container identifier, as found during the probe operation.
///
/// This value is non-`nil` unless the ``FSProbeResult/result`` is ``FSMatchResult/notRecognized``.
/// For formats that lack a durable UUID on which to base a container identifier --- which is only legal for a ``FSUnaryFileSystem`` --- this value may be a random UUID.
@property (readonly, nullable)          FSContainerIdentifier  *containerID;

- (instancetype)init NS_UNAVAILABLE;

/// A probe result for an unrecognized file system.
///
/// An unrecognized probe result contains `nil` for its ``FSProbeResult/name`` and ``FSProbeResult/containerID`` properties.
@property (class, readonly) FSProbeResult * notRecognizedProbeResult;

/// Creates a probe result for a recognized file system.
///
/// - Parameters:
///   - name: The resource name, as found during the probe operation. If the file system doesn't support names, or is awaiting naming, use an empty string.
///   - containerID: The container identifier, as found during the probe operation. If the file system doesn't support durable identifiers, use a random UUID.
+ (instancetype)recognizedProbeResultWithName:(NSString *)name
                                  containerID:(FSContainerIdentifier *)containerID
                                        NS_SWIFT_NAME(recognized(name:containerID:));

/// A probe result for a recognized file system that is usable, but with limited capabilities.
///
/// This kind of probe result lacks the ``FSProbeResult/name``, ``FSProbeResult/containerID``, or both.
/// Don't return this result from probing a resource that isn't limited.
@property (class, readonly) FSProbeResult * usableButLimitedProbeResult;

/// Creates a probe result for a recognized file system that is usable, but with limited capabilities.
///
/// - Parameters:
///   - name: The resource name, as found during the probe operation. If the file system doesn't support names, or is awaiting naming, use an empty string.
///   - containerID: The container identifier, as found during the probe operation. If the file system doesn't support durable identifiers, use a random UUID.
+ (instancetype)usableButLimitedProbeResultWithName:(NSString *)name
                                        containerID:(FSContainerIdentifier *)containerID
                                        NS_SWIFT_NAME(usableButLimited(name:containerID:));

/// Creates a probe result for a recognized and usable file system.
///
/// - Parameters:
///   - name: The resource name, as found during the probe operation. If the file system doesn't support names, or is awaiting naming, use an empty string.
///   - containerID: The container identifier, as found during the probe operation. If the file system doesn't support durable identifiers, use a random UUID.
+ (instancetype)usableProbeResultWithName:(NSString *)name
                              containerID:(FSContainerIdentifier *)containerID
                                        NS_SWIFT_NAME(usable(name:containerID:));

@end

NS_ASSUME_NONNULL_END
