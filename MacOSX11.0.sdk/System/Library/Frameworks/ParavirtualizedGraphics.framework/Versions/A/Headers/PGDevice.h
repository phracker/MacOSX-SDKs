//
//  PGDevice.h
//  ParavirtualizedGraphics
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#ifndef PGDevice_h
#define PGDevice_h

#include <stdint.h>
#include <Metal/Metal.h>
#include <IOSurface/IOSurface.h>
#include <ParavirtualizedGraphics/PGDefines.h>

@protocol PGDevice;
@protocol PGDisplay;
@class PGDisplayDescriptor;

/*!
 @typedef PGPhysicalMemoryRange_t
 @abstract A struct for a guest physical memory range
 @field physicalAddress The starting physical address of the range
 @field physicalLength The length of the range
 */
typedef struct PGPhysicalMemoryRange_s
{
    uint64_t physicalAddress;
    uint64_t physicalLength;
} PGPhysicalMemoryRange_t API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGTask_t
 @abstract Opaque type to represent a Task.  The ParavirtualizedGraphics framework will not
 access the contents of this type.
 */
typedef struct PGTask_s PGTask_t API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGTraceRange_t
 @abstract Opaque type to represent a memory trace range.  The ParavirtualizedGraphics framework will not
 access the contents of this type.
 */
typedef struct PGTraceRange_s PGTraceRange_t API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGCreateTask
 @abstract A block that will be invoked to create a task object.
 @param vmSize The size of the virtual memory reserveration that should be made to back this
 task.
 @param baseAddress An out parameter that returns the base host-virtually-contiguous address for
 the task.
 @return A PGTask_t pointer.  The framework will not attempt to access the contents of this pointer.
 Implementation should return NULL on failure.  This pointer will be passed to other task access blocks.
 */
typedef PGTask_t * _Nullable (^PGCreateTask)(uint64_t vmSize, void * _Nullable * _Nonnull baseAddress) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGDestroyTask
 @abstract A block that will be invoked to destroy a task object.
 @param task The APVTask object created by an invocation of the APVCreateTask block.
 */
typedef void (^PGDestroyTask)(PGTask_t * _Nonnull task) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGMapMemory
 @abstract A block that will be invoked to map guest physical memory into a task.
 @param task The task to map the memory into.
 @param rangeCount The number of ranges to map.
 @param virtualOffset The offset from the task base address to make the mapping at.
 @param readOnly True if the memory should be mapped read only.
 @param ranges The set of PGPhysicalMemoryRange to map.
 @return true if the mapping was successful, false otherwise.
 */
typedef bool(^PGMapMemory)(PGTask_t * _Nonnull task, uint32_t rangeCount, uint64_t virtualOffset, bool readOnly, PGPhysicalMemoryRange_t * _Nonnull ranges) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGUnmapMemory
 @abstract A block that will be invoked to unmap guest physical memory into a task.
 @param task The task to unmap memory from.
 @param virtualOffset The offset to start unmapping from.
 @param length The number of bytes to unmap.
 */
typedef bool(^PGUnmapMemory)(PGTask_t * _Nonnull task, uint64_t virtualOffset, uint64_t length) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGReadMemory
 @abstract A block that will be invoked to read from guest physical memory into the dst pointer.
 @param physicalAddress The base address of the read.
 @param length The length of region to read.
 @param dst The destination to write the read bytes into.
 */
typedef bool(^PGReadMemory)(uint64_t physicalAddress, uint64_t length, void * _Nonnull dst) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGRaiseInterrupt
 @abstract A block that is invoked to raise an interrupt to the guest.
 @param vector The MSI vector to raise an interrupt on.
 */
typedef void(^PGRaiseInterrupt)(uint32_t vector) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGTraceRangeHandler
 @abstract A block that will be invoked by the device client code when a trace handler fires.  The device client code should watch the memory identified
 by each installed trace range and notify the device when the memory has been changed.  The client is encouraged to coalesce the handling of these notifications
 over the course of several milliseconds.  This functionality is used to provide a low overhead framebuffer implementation that is used by the device before the guest
 OS has fully booted and entered accelerated rendering and display.
 @param dirty The range of memory that was detected to be dirtied by the guest.
 @discussion The returned range may be larger than the range that was actually written, for example, if the client can only determine at page granularity the memory that was
 affected by guest writes, then it may report a larger region.  Clients are also encouraged to coalesce writes over a period of time into a single notification of activity.
 */
typedef void(^PGTraceRangeHandler)(PGPhysicalMemoryRange_t * _Nonnull dirty) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGAddTraceRange
 @abstract A block that will be invoked by the device to install a new trace range.
 @param range The range to trace.  The provided range  will be page aligned in both start address and length.  The range will not overlap with any existing trace range for this device.
 The range will cover a contiguous range of guest system memory.
 @param handler The handler to invoke when a range has been modified by the guest.
 @return An opaque handle to the trace range.  The device code will not attempt to access the contents of this structure.
 */
typedef PGTraceRange_t* _Nullable(^PGAddTraceRange)(PGPhysicalMemoryRange_t * _Nonnull range, PGTraceRangeHandler _Nonnull handler) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGRemoveTraceRange
 @abstract A block that will be invoked by the device to remove a trace range.
 @param range The range to remove.
 @discussion The client should consume any pending invocations of the range handler before the end of this block invocation.
 */
typedef void(^PGRemoveTraceRange)(PGTraceRange_t * _Nonnull range) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);


PG_EXTERN API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
@interface PGDeviceDescriptor : NSObject
/*!
 @property device
 @abstract The metal device to use to back the PGDevice
 */
@property (readwrite, nonatomic, retain, nullable) id<MTLDevice> device API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property mmioLength
 @abstract The length, of the memory that backs the APPLEGPU_BAR_MMIO
 @discussion By default, the value of mmioLength will be the recommended default size for
 the MMIO memory.
 */
@property (readwrite, nonatomic) size_t mmioLength API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property createTask
 @abstract The block to invoke to create a task.
 */
@property (readwrite, nonatomic, copy, nullable) PGCreateTask createTask API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property destroyTask
 @abstract The block to invoke to destroy a task.
 */
@property (readwrite, nonatomic, copy, nullable) PGDestroyTask destroyTask API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property mapMemory
 @abstract The block to invoke to map guest memory into a task.
 */
@property (readwrite, nonatomic, copy, nullable) PGMapMemory mapMemory API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property unmapMemory
 @abstract The block to invoke to unmap guest memory from a task.
 */
@property (readwrite, nonatomic, copy, nullable) PGUnmapMemory unmapMemory API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property readMemory
 @abstract The block to invoke to perform a read of guest memory
 */
@property (readwrite, nonatomic, copy, nullable) PGReadMemory readMemory API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property raiseInterrupt
 @abstract The block to invoke to raise an interrupt to the guest.  May be raised from a dispatch queue
 must be thread safe.
 */
@property (readwrite, nonatomic, copy, nullable) PGRaiseInterrupt raiseInterrupt API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property addTraceRange
 @abstract The block to invoke to add a trace range.
 @discussion If the client is unable to provide range tracing, it should not populate this property or removeTraceRange.
 */
@property (readwrite, nonatomic, copy, nullable) PGAddTraceRange addTraceRange API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property removeTraceRange
 @abstract The block to invoke to remove a trace range.
 @discussion This property must be populated if addTraceRange is populated.
 */
@property (readwrite, nonatomic, copy, nullable) PGRemoveTraceRange removeTraceRange API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);
@end

/*!
 @protocol PGDevice
 @abstract The PGDevice protocol represents a paravirtualized GPU device.
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
@protocol PGDevice<NSObject>
/*!
 @method mmioReadAtOffset:
 @abstract Perform an MMIO read from the device.
 @param offset The offset into the MMIO BAR to read from.
 @return The 32-bit value for the read.
 */
-(uint32_t)mmioReadAtOffset:(size_t) offset API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method mmioWriteAtOffset:value:
 @abstract Perform an MMIO write to the device.
 @param offset The offset into the MMIO bar to write to.
 @param value The 32-bit value to write to the device.
 */
-(void)mmioWriteAtOffset:(size_t) offset value:(uint32_t)value API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method newDisplayWithDescriptor:port:serialNum
 @abstract Create a display based on the given descriptor and uniquifying parameters.
 @param descriptor Description of desired display object.
 @param port Port number on accelerator that display will plug into (one display per port).
 @param serialNum Serial Number of display (should be unique so Guest compositor can maintain persistent layout of displays on desktop across boots).
 @discussion New display won't hot-plug until first modeList is established.  Releasing this object emulates a hot-unplug.
 */
-(id<PGDisplay> _Nullable)newDisplayWithDescriptor:(PGDisplayDescriptor * _Nonnull)descriptor port:(NSUInteger)port serialNum:(uint32_t)serialNum API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method willSuspend
 @abstract Notify the device that it will suspend.  This will quiesce the device but not begin resource serialization. Upon return from this method,
 no new interrupts will be generated by the device.  The device will stop accepting commands from the guest.
 @note Mac guests have several wall-clock time limits on command buffer completion so the guest CPUs need to be halted within a short interval
 after this method is called.
 */
-(void)willSuspend API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method finishSuspend
 @abstract Finish the suspend.  This method may take an arbitrary amount of time as the device needs to complete any GPU work that is in flight.
 @return The suspend state data.  This data should be serialized and returned to the device on resume.  Returns nil on suspend failure.
 @note It is not legal to perform any further operations on this device after finishSuspend is called, the device must be released.
 */
-(NSData *_Nullable)finishSuspend NS_RETURNS_RETAINED API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method willResumeWithSuspendState:error:
 @abstract Begin the resume.  This method will set up the device to appear in the same state as it was in before the suspend.  At this point, the guest CPUs should not
 yet be running and no guest memory accesses will be attempted.
 @param suspendState The suspend state recorded during the finishSuspend:.
 @param error An error out parameter, will be populated on resume failure.  Error will be in PGResumeErrorDomain and will have an error code from the PGResumeErrorCode enum.
 @return Returns YES on success.  On failure will return NO and populate error.
 @note Suspended displays should be reattached after this method has been called, but before -[PGDevice didResume:] is invoked.
 @note For resume, this must be the first method invoked on a newly created device.
 */
-(bool)willResumeWithSuspendState:(NSData *_Nonnull)suspendState error:(NSError * __autoreleasing _Nullable * _Nullable)error API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method didResume
 @abstract Complete the resume.  After this method is invoked, new interrupts may be generated by the device.  Guest memory must be accessible at the time this method is invoked.
 @note An initial interrupt may be generated during the duration of this call.
 */
-(void)didResume API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);
@end

/*!
 @function PGNewDeviceWithDescriptor
 @abstract Create a new PGDevice implementation object based on the provided descriptor.
 @param descriptor The device descriptor for the new device.
 */
PG_EXTERN id<PGDevice> _Nullable PGNewDeviceWithDescriptor(PGDeviceDescriptor * _Nonnull descriptor) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @const PGResumeErrorDomain The error domain for reporting errors in resume.
 */
PG_EXTERN NSErrorDomain const _Nonnull PGResumeErrorDomain API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @enum PGResumeErrorCode
 @abstract Resume error codes
 @constant PGResumeErrorCodeInternalFault Some internal fault occurred.
 @constant PGResumeErrorCodeInvalidSuspendStateVersion The suspend state version is incompatible with this framework version.
 @constant PGResumeErrorCodeInvalidContent The content the suspend state or guest memory is invalid.
 @constant PGResumeErrorCodeInvalidGuestVersion The guest version is incompatible with this framework version.
 @constant PGResumeErrorCodeDeviceIncompatible The resume device is missing capabilities provided by the suspend device.
 */
typedef NS_ENUM(NSUInteger, PGResumeErrorCode) {
    PGResumeErrorCodeInternalFault = 0,
    PGResumeErrorCodeInvalidSuspendStateVersion,
    PGResumeErrorCodeInvalidContent,
    PGResumeErrorCodeInvalidGuestVersion,
    PGResumeErrorCodeIncompatibleDevice,
} API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @function PGCopyOptionROMURL
 @abstract Copy the URL of the option ROM to be used by the device.  The URL will be a local file path to a flat ROM image.  The client code should
 pad the ROM image out to a power of 2 size with a zero-filled trailer and present the resulting bytes as read only memory to the PCI option ROM BAR for
 the device.
 @return The URL.
 */
PG_EXTERN NSURL * _Nonnull PGCopyOptionROMURL(void)  API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

#endif /* PGDevice_h */
