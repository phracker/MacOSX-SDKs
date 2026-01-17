/*
 * Copyright (c) 1999-2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_IOGRAPHICSLIB_H
#define _IOKIT_IOGRAPHICSLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <IOKit/IOKitLib.h>
#include <IOKit/graphics/IOFramebufferShared.h>
#include <IOKit/graphics/IOGraphicsInterface.h>

/*! @header IOGraphicsLib
IOGraphicsLib implements non-kernel task access to IOGraphics family object types - IOFramebuffer and IOAccelerator. These functions implement a graphics family specific API.<br>
A connection to a graphics IOService must be made before these functions are called. A connection is made with the IOServiceOpen() function described in IOKitLib.h. An io_connect_t handle is returned by IOServiceOpen(), which must be passed to the IOGraphicsLib functions. The appropriate connection type from IOGraphicsTypes.h must be specified in the call to IOServiceOpen(). All of the IOFramebuffer functions can only be called from a kIOFBServerConnectType connection. Except as specified below, functions whose names begin with IOFB are IOFramebuffer functions. Functions whose names begin with IOPS are IOAccelerator functions and must be called from connections of type kIOFBEngineControllerConnectType or kIOFBEngineConnectType.<br>
The functions in IOGraphicsLib use a number of special types. The display mode is the screen's resolution and refresh rate. The known display modes are referred to by an index of type IODisplayModeID. The display depth is the number of significant color bits used in representing each pixel. Depths are also referred to by an index value that is 0 for 8 bits, 1 for 15 bits, and 2 for 24 bits. A combination of display mode and depth may have a number of supported pixel formats. The pixel aperture is an index of supported pixel formats for a display mode and depth. This index is of type IOPixelAperture. All of these graphics specific types are defined in IOGraphicsTypes.h.
*/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

extern kern_return_t
IOFramebufferOpen(
        io_service_t    service,
        task_port_t     owningTask,
        unsigned int    type,
        io_connect_t  * connect );

/*! @function IOFBCreateSharedCursor
    @abstract Create shared cursor memory.
    @discussion This function allocates memory, containing details about the cursor, that can be shared with a calling non-kernel task. The memory contains a StdFBShmem_t structure, which is defined in IOFrameBufferShared.h. This structure contains information on the cursor image, whether it is current shown, its location, etc. The allocated memory can be mapped to the non-kernel task's memory space by calling IOConnectMapMemory() and passing kIOFBCursorMemory for memoryType.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param version The version of cursor shared memory to use. For the current version, pass kIOFBCurrentShmemVersion.
    @param maxWidth The maximum width of the cursor.
    @param maxHeight The maximum height of the cursor.
    @result A kern_return_t error code. */

extern kern_return_t
IOFBCreateSharedCursor( io_connect_t connect,
        unsigned int version,
        unsigned int maxWidth, unsigned int maxHeight );

/*! @function IOFBGetFramebufferInformationForAperture
    @abstract Get framebuffer information for a pixel format.
    @discussion This function returns framebuffer information for a pixel format that is supported for the current display mode and depth. The returned IOFrameBufferInformation structure contains details on the physical address of the framebuffer, height, width, etc. This structure is defined in IOGraphicsTypes.h.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param aperture The pixel aperture to retrieve information on. The pixel aperture is an index into supported pixel formats for a display mode and depth. To get information for the current aperture, use kIOFBSystemAperture.
    @param info A pointer to an IOFramebufferInformation structure where the information will be returned.
    @result A kern_return_t error code. */

extern kern_return_t
IOFBGetFramebufferInformationForAperture( io_connect_t connect,
            IOPixelAperture               aperture,
            IOFramebufferInformation    * info );

/*! @function IOFBGetFramebufferOffsetForAperture
    @abstract Get the byte offset for a framebuffer's VRAM.
    @discussion [place holder]
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param aperture The pixel aperture to retrieve information on. The pixel aperture is an index into supported pixel formats. To get information for the current aperture, use kIOFBSystemAperture.
    @param offset The number of bytes offset is returned on success.
    @result A kern_return_t error code. */

extern kern_return_t
IOFBGetFramebufferOffsetForAperture( mach_port_t connect,
            IOPixelAperture               aperture,
            IOByteCount                 * offset );

/*! @function IOFBSetBounds
    @abstract Set the location of the framebuffer within display space.
    @discussion If there is more than one screen in use, the locations of the screens relative to each other must be specified. These locations are specified in a "display space" that encompasses all the screens. The bounding regions of the screens within display space indicate their location relative to each other as the cursor moves between them. This function sets the bounding region for a framebuffer within display space. If there is only one screen, this does not need to specified, because by default the screen coordinates and display space coordinates will be the same.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param rect An IOGBounds structure specifying a rectangular region of the framebuffer.
    @result A kern_return_t error code. */

extern kern_return_t
IOFBSetBounds( io_connect_t connect,
            IOGBounds   * rect );

/*! @function IOFBGetCurrentDisplayModeAndDepth
    @abstract Get the current display mode and depth.
    @discussion The display mode index returned by this function can be used to determine information about the current display mode and its supported pixel formats through calls to IOFBGetDisplayModeInformation(), IOFBGetPixelFormats(), and IOFBGetPixelInformation().
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param displayMode The ID of the current display mode is returned.
    @param depth The current display depth is returned (0 = 8 bits, 1 = 15 bits, 2 = 24 bits)
    @result A kern_return_t error code. */

extern kern_return_t
IOFBGetCurrentDisplayModeAndDepth( io_connect_t connect,
        IODisplayModeID * displayMode,
        IOIndex         * depth );

/*! @function IOFBGetPixelFormat
    @abstract Get pixel format information.
    @discussion Displayed colors are encoded in framebuffer memory in a variety of ways. IOFBGetPixelFormat returns a pixel encoding array specifying how each bit of a particular pixel should be interpreted. The definition of the IOPixelEncoding array returned and common Apple pixel formats are described in IOGraphicsTypes.h.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param displayMode A display mode index.
    @param depth A display depth index.
    @param aperture The pixel aperture to retrieve the pixel format for. The pixel aperture is an index into supported pixel formats. To get information on the current aperture, use kIOFBSystemAperture.
    @param pixelFormat The returned pixel format.
    @result A kern_return_t error code. */

extern kern_return_t
IOFBGetPixelFormat( io_connect_t connect,
        IODisplayModeID displayMode,
        IOIndex         depth,
        IOPixelAperture aperture,
        IOPixelEncoding * pixelFormat );

/*! @function IOFBSetCLUT
    @abstract Set the color table.
    @discussion Indexed pixel formats require a color table to convert from the index stored in a pixel memory location to a displayed color. IOFBSetCLUT sets one or more entries of the color table.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param startIndex The first index to set in the color table.
    @param numEntries The number of entries to set.
    @param options kSetCLUTByValue may be set to use the index member of the IOColorEntry structure to determine where the entry should be written to the color table. Otherwise the index is taken from the location in the IOColorEntry array. kSetClutImmediately may be set to change the color table immediately instead of waiting for vertical blanking interval. kSetClubWithLuminance may be set to use luminance rather than RGB entries.
    @param colors The array of color table entries to set. The IOColorEntry structure is defined in IOGraphicsTypes.h.
    @result A kern_return_t error code. */

extern kern_return_t
IOFBSetCLUT( io_connect_t connect,
        UInt32          startIndex,
        UInt32          numEntries,
        IOOptionBits    options,
        IOColorEntry *  colors );

/*! @function IOFBSetGamma
    @abstract Set the gamma data.
    @discussion [place holder]
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param channelCount
    @param dataCount
    @param dataWidth
    @param data
    @result A kern_return_t error code. */

extern kern_return_t
IOFBSetGamma( io_connect_t connect,
        UInt32          channelCount,
        UInt32          dataCount,
        UInt32          dataWidth,
        void *          data );

/*! @function IOFBSet888To256Table
    @abstract [place holder]
    @discussion [place holder]
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param table
    @result A kern_return_t error code. */

extern kern_return_t
IOFBSet888To256Table( io_connect_t connect,
        const unsigned char *   table );

/*! @function IOFBSet256To888Table
    @abstract [place holder]
    @discussion [place holder]
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param table
    @result A kern_return_t error code. */

extern kern_return_t
IOFBSet256To888Table( io_connect_t connect,
        const unsigned int *    table );

/*! @function IOFBSet444To555Table
    @abstract [place holder]
    @discussion [place holder]
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param table
    @result A kern_return_t error code. */

extern kern_return_t
IOFBSet444To555Table( io_connect_t connect,
        const unsigned char *   table );

/*! @function IOFBSet555To444Table
    @abstract [place holder]
    @discussion [place holder]
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param table
    @result A kern_return_t error code. */

extern kern_return_t
IOFBSet555To444Table( io_connect_t connect,
        const unsigned char *   table );

// Array of supported display modes

/*! @function IOFBGetDisplayModeCount
    @abstract Get the number of display modes.
    @discussion IOFBGetDisplayModeCount returns the number of display modes that the IOFramebuffer service is aware of.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param count The display mode count is returned.
    @result A kern_return_t error code. */

kern_return_t
IOFBGetDisplayModeCount( io_connect_t connect,
        UInt32 * count );

/*! @function IOFBGetDisplayModes
    @abstract Get an array of known display modes.
    @discussion This function returns an array containing the display modes that the framebuffer service is aware of. To get all display modes, pass the count from IOFBGetDisplayModeCount().
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param count The number of display modes to get.
    @param allDisplayModes An array of IODisplayModeID's with enough space for all entries. The array is filled in upon return.
    @result A kern_return_t error code. */

kern_return_t
IOFBGetDisplayModes( io_connect_t connect,
        UInt32                  count,
        IODisplayModeID *       allDisplayModes );

// Info about a display mode

/*! @function IOFBGetDisplayModeInformation
    @abstract Get information about a display mode.
    @discussion Display modes are referred to by their index of type IODisplayModeID. This function returns a structure containing the width, height, refresh rate, maximum depth, etc. of a display mode. The IODisplayModeInformation structure is defined in IOGraphicsTypes.h.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param displayMode The display mode index.
    @param info A pointer to an IODisplayModeInformation structure where the display mode information will be returned.
    @result A kern_return_t error code. */

kern_return_t
IOFBGetDisplayModeInformation( io_connect_t connect,
        IODisplayModeID         displayMode,
        IODisplayModeInformation * info );


// Mask of pixel formats available in mode and depth

/*! @function IOFBGetPixelFormats
    @abstract Get pixel formats that are supported for a display mode and depth.
    @discussion This function returns a mask of all supported pixel formats for a particular display mode and depth. [How should the mask be interpreted?]
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param displayMode A display mode index.
    @param depth A display depth index.
    @param mask The returned mask of pixel formats.
    @result A kern_return_t error code. */

kern_return_t
IOFBGetPixelFormats( io_connect_t connect,
        IODisplayModeID         displayMode,
        IOIndex                 depth,
        UInt32 *                mask );

/*! @function IOFBGetPixelInformation
    @abstract Get information about a pixel format.
    @discussion IOFBGetPixelInformation returns a structure containing information about a pixel format such as the bits per pixel, pixel format, etc. The IOPixelInformation structure is defined in IOGraphicsTypes.h.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param displayMode A display mode index.
    @param depth A display depth index.
    @param aperture A pixel aperture. The pixel aperture is an index into supported pixel formats for a display mode and depth. To get information on the current aperture, use kIOFBSystemAperture.
    @param IOPixelInformation A pointer to an IOPixelInformation structure where the pixel information will be returned.
    @result A kern_return_t error code. */

kern_return_t
IOFBGetPixelInformation( io_connect_t connect,
        IODisplayModeID         displayMode,
        IOIndex                 depth,
        IOPixelAperture         aperture,
        IOPixelInformation *    pixelInfo );

/*! @function IOFBSetDisplayModeAndDepth
    @abstract Set the current display mode and depth.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param displayMode The index of the new display mode.
    @param depth The index of the new depth.
    @result A kern_return_t error code. */

kern_return_t
IOFBSetDisplayModeAndDepth( io_connect_t connect,
        IODisplayModeID         displayMode,
        IOIndex                 depth );

/*! @function IOFBSetStartupDisplayModeAndDepth
    @abstract Set the display mode and depth to use on startup.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param displayMode The index of the new display mode.
    @param depth The index of the new depth.
    @result A kern_return_t error code. */

kern_return_t
IOFBSetStartupDisplayModeAndDepth( io_connect_t connect,
        IODisplayModeID         displayMode,
        IOIndex                 depth );

kern_return_t
IOFBGetDefaultDisplayMode( io_connect_t connect,
        IODisplayModeID * displayMode, IOIndex * displayDepth );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct IOFBMessageCallbacks {
    IOReturn (*WillPowerOff)    (void * callbackRef, void * notificationID);
    IOReturn (*DidPowerOn)      (void * callbackRef, void * notificationID);
    IOReturn (*ConnectionChange)(void * callbackRef, void * notificationID);
};
typedef struct IOFBMessageCallbacks IOFBMessageCallbacks;

enum {
    IOFBMessageCallbacksVersion = 1
};

mach_port_t
IOFBGetNotificationMachPort( io_connect_t connect );

kern_return_t
IOFBDispatchMessageNotification( io_connect_t connect, mach_msg_header_t * message,
                                 UInt32 version, const IOFBMessageCallbacks * callbacks, void * callbackRef);

kern_return_t
IOFBAcknowledgeNotification( void * notificationID );

enum {
    kIOFBConnectStateOnline     = 0x00000001
};

kern_return_t
IOFBGetConnectState( io_connect_t connect, IOOptionBits * state );

kern_return_t
IOFBGetAttributeForFramebuffer( io_connect_t connect, io_connect_t otherConnect,
                                IOSelect attribute, UInt32 * value );
kern_return_t
IOFBSetAttributeForFramebuffer( io_connect_t connect, io_connect_t otherConnect,
                                IOSelect attribute, UInt32 value );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*! @function IOFBCreateDisplayModeDictionary
    @abstract Create a CFDictionary with information about a display mode.
    @discussion This function creates a dictionary containing information about a display mode. The display mode properties that are represented by the kernel as OSDictionary, OSArray, OSSet, OSSymbol, OSString, OSData, OSNumber, or OSBoolean are converted to their CF counterparts and put in the dictionary.
    @param framebuffer The IOService handle for an IOFramebuffer service.
    @param displayMode A display mode index.
    @result The returned CFDictionary that should be released by the caller with CFRelease(). */

CFDictionaryRef
IOFBCreateDisplayModeDictionary(
        io_service_t            framebuffer,
        IODisplayModeID         displayMode );

/*! @function IOFBGetPixelInfoDictionary
    @abstract Get a CFDictionary with information about a pixel format.
    @discussion This function extracts a CFDictionary containing information about a supported pixel format from a larger CFDictionary describing a display mode. IOFBCreateDisplayModeDictionary() must be called first to generate the CFDictionary for a display mode.
    @param modeDictionary The CFDictionary containing information about a display mode.
    @param depth A depth index.
    @param aperture The pixel aperture to information about. The pixel aperture is an index into supported pixel formats. To get information on the current aperture, use kIOFBSystemAperture.
    @result The returned CFDictionary that should be released by the caller with CFRelease(). */

CFDictionaryRef
IOFBGetPixelInfoDictionary( 
        CFDictionaryRef         modeDictionary,
        IOIndex                 depth,
        IOPixelAperture         aperture );

/*! @enum IODisplayDictionaryOptions
    @constant kIODisplayMatchingInfo Include only the keys necessary to match two displays with IODisplayMatchDictionaries().
    @constant kIODisplayOnlyPreferredName The kDisplayProductName property includes only the localized names returned by CFBundleCopyPreferredLocalizationsFromArray().
    @constant kIODisplayNoProductName The kDisplayProductName property is not included in the returned dictionary.
*/
enum {
    kIODisplayMatchingInfo      = 0x00000100,
    kIODisplayOnlyPreferredName = 0x00000200,
    kIODisplayNoProductName     = 0x00000400
};

/*! @function IODisplayCreateInfoDictionary
    @abstract Create a CFDictionary with information about display hardware.
    @discussion The CFDictionary created by this function contains information about the display hardware associated with a framebuffer. The keys for the dictionary are listed in IOGraphicsTypes.h.
    @param framebuffer The IOService handle for an IOFramebuffer service.
    @param options Use IODisplayDictionaryOptions to specify which keys to include.
    @result The returned CFDictionary that should be released by the caller with CFRelease(). */

CFDictionaryRef
IODisplayCreateInfoDictionary(
        io_service_t            framebuffer,
        IOOptionBits            options );

/*! @defined IOCreateDisplayInfoDictionary
    @discussion IOCreateDisplayInfoDictionary() was renamed IODisplayCreateInfoDictionary(). IOCreateDisplayInfoDictionary() is now a macro for IODisplayCreateInfoDictionary() for compatibility with older code. */

#define IOCreateDisplayInfoDictionary(f,o)      \
        IODisplayCreateInfoDictionary(f,o)

/*! @function IODisplayMatchDictionaries
    @abstract Match two display information dictionaries to see if they are for the same display.
    @discussion By comparing two CFDictionaries returned from IODisplayCreateInfoDictionary(), this function determines if the displays are the same. The information compared is what is returned by calling IODisplayCreateInfoDictionary() with an option of kIODisplayMatchingInfo. This includes information such as the vendor, product, and serial number.
    @param matching1 A CFDictionary returned from IODisplayCreateInfoDictionary().
    @param matching2 Another CFDictionary returned from IODisplayCreateInfoDictionary().
    @param options No options are currently defined.
    @result Returns FALSE if the two displays are not equivalent or TRUE if they are. */

SInt32
IODisplayMatchDictionaries(
        CFDictionaryRef         matching1,
        CFDictionaryRef         matching2,
        IOOptionBits            options );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

io_service_t
IODisplayForFramebuffer(
        io_service_t    framebuffer,
        IOOptionBits    options );

IOReturn
IODisplaySetParameters(
        io_service_t    service,
        IOOptionBits    options,
        CFDictionaryRef params );

IOReturn
IODisplaySetFloatParameter(
        io_service_t    service,
        IOOptionBits    options,
        CFStringRef     parameterName,
        float           value );
IOReturn
IODisplaySetIntegerParameter(
        io_service_t    service,
        IOOptionBits    options,
        CFStringRef     parameterName,
        SInt32          value );

IOReturn
IODisplayCopyParameters(
        io_service_t      service,
        IOOptionBits      options,
        CFDictionaryRef * params );

IOReturn
IODisplayCopyFloatParameters(
        io_service_t      service,
        IOOptionBits      options,
        CFDictionaryRef * params );

IOReturn
IODisplayGetFloatParameter(
        io_service_t    service,
        IOOptionBits    options,
        CFStringRef     parameterName,
        float *         value );

IOReturn
IODisplayGetIntegerRangeParameter(
        io_service_t    service,
        IOOptionBits    options,
        CFStringRef     parameterName,
        SInt32 *        value,
        SInt32 *        min,
        SInt32 *        max );

IOReturn
IODisplayCommitParameters(
        io_service_t    service,
        IOOptionBits    options );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*! @function IOFBSetNewCursor
    @abstract Set a new hardware cursor.
    @discussion A non-kernel task interacts with the IOFramebuffer service through a slice of shared memory that is created with the IOFBCreateSharedCursor function. The shared memory is a structure of type StdFBShmem_t. In this shared memory several cursor images, or frames may be defined. The maximum number of frames is kIOFBNumCursorFrames. StdFBShmem_t and kIOFBNumCursorFrames are defined in IOFramebufferShared.h. This function sets a new frame to be used as the current cursor image and activates the hardware cursor.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param cursor This parameter is currently not used and must be 0.
    @param frame An index to the cursor image to use that must be less than kIOFBNumCursorFrames. Currently only frame 0 is supported.
    @param options No options are currently defined.
    @result A kern_return_t error code. */

kern_return_t
IOFBSetNewCursor( io_connect_t connect,
        void *                  cursor,
        IOIndex                 frame,
        IOOptionBits            options );

/*! @function IOFBSetCursorVisible
    @abstract Set the hardware cursor visible or invisible.
    @discussion The hardware cursor can only be set visible or invisible when it is active. Use IOFBSetNewCursor() to activate the hardware cursor.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param visible TRUE to make the cursor visible and FALSE to make it invisible.
    @result A kern_return_t error code. */

kern_return_t
IOFBSetCursorVisible( io_connect_t connect,
        int                     visible );

/*! @function IOFBSetCursorPosition
    @abstract Set the hardware cursor position.
    @discussion This function only works with the hardware cursor and will fail if a hardware cursor is not supported.
    @param connect The connect handle from IOServiceOpen() to an IOFramebuffer service with a kIOFBServerConnectType connection.
    @param x The x coordinate.
    @param y The y coordinate.
    @result A kern_return_t error code. */

kern_return_t
IOFBSetCursorPosition( io_connect_t connect,
        long int                x,
        long int                y );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

kern_return_t
IOFBAcknowledgePM( io_connect_t connect );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

kern_return_t
IOPSAllocateBlitEngine( io_connect_t framebuffer,
                void ** blitterRef, int * quality);

kern_return_t
IOPSBlitReset( void * blitterRef);

kern_return_t
IOPSBlitDeallocate( void * blitterRef);

kern_return_t
IOPSBlitIdle( void * blitterRef);

kern_return_t
IOPSBlitFill( void * blitterRef,
                int dst_x, int dst_y, int width, int height, int data );

kern_return_t
IOPSBlitCopy( void * blitterRef,
                int src_x, int src_y, int width, int height,
                int dst_x, int dst_y );

kern_return_t
IOPSBlitInvert( void * blitterRef,
                int x, int y, int w, int h );

enum {
    // options for IOFBSynchronize
    kIOFBSynchronizeWaitBeamExit        = kIOBlitSynchronizeWaitBeamExit,
    kIOFBSynchronizeFlushWrites         = kIOBlitSynchronizeFlushHostWrites
};

enum {
    // options for IOFBBlitVRAMCopy
    kIOFBBlitBeamSync                   = kIOBlitBeamSync,
    kIOFBBlitBeamSyncAlways             = kIOBlitBeamSyncAlways,
    kIOFBBlitBeamSyncSpin               = kIOBlitBeamSyncSpin
};

kern_return_t
IOFBBlitVRAMCopy( void * blitterRef,
                int src_x, int src_y, int width, int height,
                int dst_x, int dst_y, IOOptionBits options );

kern_return_t
IOFBBlitSurfaceCopy( void * blitterRef, IOOptionBits options, void * surfaceID,
                     IOAccelDeviceRegion * region, UInt32 surfaceX, UInt32 surfaceY );

kern_return_t
IOFBBlitSurfaceSurfaceCopy( void * blitterRef, IOOptionBits options,
                            void * sourceSurfaceID, void * destSurfaceID,
                            IOAccelDeviceRegion * region, UInt32 surfaceX, UInt32 surfaceY );

kern_return_t
IOFBSynchronize( void * blitterRef,
                 UInt32 x, UInt32 y, UInt32 w, UInt32 h, UInt32 options );

kern_return_t
IOFBBeamPosition( void * blitterRef, UInt32 options, SInt32 * position );

kern_return_t
IOFBSetupFIFOBurst( void * blitterRef,
                        UInt32 x, UInt32 y, UInt32 w, UInt32 h,
                        UInt32 options, void ** burstRef );

void
IOFBBurstWrite32( void * p1, void * p2, void * p3, void * p4,
                  void * p5, void * p6, void * p7, void * p8 );

void
IOFBSetBurstRef( void * burstRef );

kern_return_t
IOFBCommitMemory( void * blitterRef,
                vm_address_t start, vm_size_t length, IOOptionBits options,
                void ** memoryRef, IOByteCount * offset );

kern_return_t
IOFBReleaseMemory( void * blitterRef, void * memoryRef );

kern_return_t
IOFBWaitForCompletion( void * blitterRef, SInt32 token );

kern_return_t
IOFBMemoryCopy( void * blitterRef,
                        UInt32 destLeft, UInt32 destTop,
                        UInt32 width, UInt32 height, 
                        UInt32 srcByteOffset, UInt32 srcRowBytes,
                        SInt32 * token);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef __cplusplus
}
#endif

#endif /* ! _IOKIT_IOGRAPHICSLIB_H */

