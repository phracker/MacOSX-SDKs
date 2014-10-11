/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_IOGRAPHICSTYPES_H
#define _IOKIT_IOGRAPHICSTYPES_H


#include <IOKit/IOTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOGRAPHICSTYPES_REV	5

typedef SInt32	IOIndex;
typedef UInt32	IOSelect;
typedef UInt32	IOFixed1616;
typedef SInt32	IODisplayModeID;
typedef UInt32	IODisplayVendorID;
typedef UInt32	IODisplayProductID;

enum {
    kIOMaxPixelBits 	= 64
};
typedef char IOPixelEncoding[ kIOMaxPixelBits ];

// Common Apple pixel formats

#define IO1BitIndexedPixels	"P"
#define IO2BitIndexedPixels	"PP"
#define IO4BitIndexedPixels	"PPPP"
#define IO8BitIndexedPixels	"PPPPPPPP"
#define IO16BitDirectPixels	"-RRRRRGGGGGBBBBB"
#define IO32BitDirectPixels	"--------RRRRRRRRGGGGGGGGBBBBBBBB"

// other possible pixel formats

#define IOYUV422Pixels		"Y4U2V2"
#define IO8BitOverlayPixels	"O8"
// page flipping
#define IOPagedPixels		"Page1"

#define IO_SampleTypeAlpha	'A'
#define IO_SampleTypeSkip	'-'

// Info about a pixel format
enum {
    kIOCLUTPixels		= 0,
    kIOFixedCLUTPixels		= 1,
    kIORGBDirectPixels 		= 2,
    kIOMonoDirectPixels 	= 3,
    kIOMonoInverseDirectPixels	= 4
};

/*!
 * @struct IOPixelInformation
 * @abstract A structure defining the format of a framebuffer.
 * @discussion This structure is used by IOFramebuffer to define the format of the pixels.
 * @field bytesPerRow The number of bytes per row.
 * @field bytesPerPlane Not used.
 * @field bitsPerPixel The number of bits per pixel, including unused bits and alpha.
 * @field pixelType One of kIOCLUTPixels (indexed pixels with changeable CLUT), kIORGBDirectPixels (direct pixels).
 * @field componentCount One for indexed pixels, three for direct pixel formats.
 * @field bitsPerComponent Number of bits per component in each pixel.
 * @field componentMasks Mask of the bits valid for each component of the pixel - in R, G, B order for direct pixels.
 * @field pixelFormat String description of the pixel format - IO32BitDirectPixels, IO16BitDirectPixels etc.
 * @field flags None defined - set to zero.
 * @field activeWidth Number of pixels visible per row.
 * @field activeHeight Number of visible pixel rows.
 * @field reserved Set to zero.
 */

struct IOPixelInformation {
    IOByteCount			bytesPerRow;
    IOByteCount			bytesPerPlane;
    UInt32			bitsPerPixel;
    UInt32			pixelType;
    UInt32			componentCount;
    UInt32			bitsPerComponent;
    UInt32			componentMasks[ 8 * 2 ];
    IOPixelEncoding		pixelFormat;
    UInt32			flags;
    UInt32			activeWidth;
    UInt32			activeHeight;
    UInt32			reserved[ 2 ];
};
typedef struct IOPixelInformation IOPixelInformation;

// Info about a display mode
typedef UInt32  IOAppleTimingID;

/*!
 * @struct IODisplayModeInformation
 * @abstract A structure defining the format of a framebuffer.
 * @discussion This structure is used by IOFramebuffer to define the format of the pixels.
 * @field nominalWidth Number of pixels visible per row.
 * @field nominalHeight Number of visible pixel rows.
 * @field refreshRate Refresh rate in fixed point 16.16.
 * @field maxDepthIndex Highest depth index available in this display mode.
 * @field flags Flags for the mode, including: <br>
    kDisplayModeInterlacedFlag mode is interlaced. <br>
    kDisplayModeSimulscanFlag mode is available on multiple display connections. <br>
    kDisplayModeNotPresetFlag mode is not a factory preset for the display (geometry may need correction). <br>
    kDisplayModeStretchedFlag mode is stretched/distorted to match the display aspect ratio. <br>
 * @field reserved Set to zero.
 */

struct IODisplayModeInformation {
    UInt32			nominalWidth;
    UInt32			nominalHeight;
    IOFixed1616			refreshRate;
    IOIndex			maxDepthIndex;
    UInt32			flags;
    UInt32			reserved[ 4 ];
};
typedef struct IODisplayModeInformation IODisplayModeInformation;

// flags
enum {
    kDisplayModeSafetyFlags		= 0x00000007,

    kDisplayModeAlwaysShowFlag		= 0x00000008,
    kDisplayModeNeverShowFlag		= 0x00000080,
    kDisplayModeNotResizeFlag		= 0x00000010,
    kDisplayModeRequiresPanFlag		= 0x00000020,

    kDisplayModeInterlacedFlag		= 0x00000040,

    kDisplayModeSimulscanFlag		= 0x00000100,
    kDisplayModeBuiltInFlag		= 0x00000400,
    kDisplayModeNotPresetFlag		= 0x00000200,
    kDisplayModeStretchedFlag		= 0x00000800,
    kDisplayModeNotGraphicsQualityFlag	= 0x00001000,
    kDisplayModeTelevisionFlag		= 0x00100000
};
enum {
    kDisplayModeValidFlag		= 0x00000001,
    kDisplayModeSafeFlag		= 0x00000002,
    kDisplayModeDefaultFlag		= 0x00000004
};

// Framebuffer info - obsolete

struct IOFramebufferInformation {
    IOPhysicalAddress		baseAddress;
    UInt32			activeWidth;
    UInt32			activeHeight;
    IOByteCount			bytesPerRow;
    IOByteCount			bytesPerPlane;
    UInt32			bitsPerPixel;
    UInt32			pixelType;
    UInt32			flags;
    UInt32			reserved[ 4 ];
};
typedef struct IOFramebufferInformation IOFramebufferInformation;

// flags
enum {
    kFramebufferSupportsCopybackCache	= 0x00010000,
    kFramebufferSupportsWritethruCache	= 0x00020000,
    kFramebufferSupportsGammaCorrection	= 0x00040000,
    kFramebufferDisableAltivecAccess	= 0x00080000
};

// Aperture is an index into supported pixel formats for a mode & depth
typedef IOIndex IOPixelAperture;
enum {
    kIOFBSystemAperture	= 0
};

//// CLUTs

typedef UInt16 IOColorComponent;

/*!
 * @struct IOColorEntry
 * @abstract A structure defining one entry of a color lookup table.
 * @discussion This structure is used by IOFramebuffer to define an entry of a color lookup table.
 * @field index Number of pixels visible per row.
 * @field red Value of red component 0-65535.
 * @field green Value of green component 0-65535.
 * @field blue Value of blue component 0-65535.
 */

struct IOColorEntry {
    UInt16	   		index;
    IOColorComponent   		red;
    IOColorComponent   		green;
    IOColorComponent   		blue;
};
typedef struct IOColorEntry IOColorEntry;

// options (masks)
enum {
    kSetCLUTByValue		= 0x00000001,		// else at index
    kSetCLUTImmediately		= 0x00000002,		// else at VBL
    kSetCLUTWithLuminance	= 0x00000004		// else RGB
};

//// Controller attributes

enum {
    kIOPowerAttribute			= 'powr',
    kIOHardwareCursorAttribute		= 'crsr',

    kIOMirrorAttribute			= 'mirr',
    kIOMirrorDefaultAttribute		= 'mrdf',

    kIOCapturedAttribute		= 'capd',

    kIOCursorControlAttribute		= 'crsc'
};

// values for kIOMirrorAttribute
enum {
    kIOMirrorIsPrimary			= 0x80000000,
    kIOMirrorHWClipped			= 0x40000000
};

// values for kIOMirrorDefaultAttribute
enum {
    kIOMirrorDefault			= 0x00000001,
    kIOMirrorForced			= 0x00000002
};

//// Display mode timing information

struct IODetailedTimingInformation {
    // from EDID defn
    UInt32			pixelClock;		// Hertz
    UInt32			horizontalActive;	// pixels
    UInt32			horizontalBlanking;	// pixels
    UInt32			horizontalBorder;	// pixels
    UInt32			horizontalSyncOffset;	// pixels
    UInt32			horizontalSyncWidth;	// pixels
    UInt32			verticalActive;		// lines
    UInt32			verticalBlanking;	// lines
    UInt32			verticalBorder;		// lines
    UInt32			verticalSyncOffset;	// lines
    UInt32			verticalSyncWidth;	// lines
};
typedef struct IODetailedTimingInformation IODetailedTimingInformation;

/*!
 * @struct IODetailedTimingInformationV2
 * @abstract A structure defining the detailed timing information of a display mode.
 * @discussion This structure is used by IOFramebuffer to define detailed timing information for a display mode. The VESA EDID document has more information.
 * @field __reservedA Set to zero.
 * @field scalerFlags If the mode is scaled, kScaleStretchToFitMask may be set to allow stretching.
 * @field horizontalScaled If the mode is scaled, sets the size of the image before scaling.
 * @field verticalScaled If the mode is scaled, sets the size of the image before scaling.
 
 * @field signalConfig kAnalogSetupExpectedMask set if display expects a blank-to-black setup or pedestal.  See VESA signal standards.
 * @field signalLevels One of:<br>
    kAnalogSignalLevel_0700_0300 0.700 - 0.300 V p-p.<br>
    kAnalogSignalLevel_0714_0286 0.714 - 0.286 V p-p.<br>
    kAnalogSignalLevel_1000_0400 1.000 - 0.400 V p-p.<br>
    kAnalogSignalLevel_0700_0000 0.700 - 0.000 V p-p.<br>
 * @field pixelClock Pixel clock frequency in Hz.
 * @field minPixelClock Minimum pixel clock frequency in Hz, with error.
 * @field maxPixelClock Maximum pixel clock frequency in Hz, with error.
 * @field horizontalActive Pixel clocks per line.
 * @field horizontalBlanking Blanking clocks per line.
 * @field horizontalSyncOffset First clock of horizontal sync.
 * @field horizontalSyncPulseWidth Width of horizontal sync.
 * @field verticalActive Number of lines per frame.
 * @field verticalBlanking Blanking lines per frame.
 * @field verticalSyncOffset First line of vertical sync.
 * @field verticalSyncPulseWidth Height of vertical sync.
 * @field horizontalBorderLeft First clock of horizontal border or zero.
 * @field horizontalBorderRight Last clock of horizontal border or zero.
 * @field verticalBorderTop First line of vertical border or zero.
 * @field verticalBorderBottom Last line of vertical border or zero.
 * @field horizontalSyncConfig kSyncPositivePolarityMask for positive polarity horizontal sync.
 * @field horizontalSyncLevel Zero.
 * @field verticalSyncConfig kSyncPositivePolarityMask for positive polarity vertical sync.
 * @field verticalSyncLevel Zero.
 * @field __reservedB Reserved set to zero.
 */

struct IODetailedTimingInformationV2 {

    UInt32	__reservedA[5];			// Init to 0

    UInt32	scalerFlags;
    UInt32	horizontalScaled;
    UInt32	verticalScaled;

    UInt32	signalConfig;
    UInt32	signalLevels;

    UInt64	pixelClock;			// Hz

    UInt64	minPixelClock;			// Hz - With error what is slowest actual clock
    UInt64	maxPixelClock;			// Hz - With error what is fasted actual clock

    UInt32	horizontalActive;	  	// pixels
    UInt32	horizontalBlanking;	  	// pixels
    UInt32	horizontalSyncOffset;	  	// pixels
    UInt32	horizontalSyncPulseWidth;	// pixels

    UInt32	verticalActive;			// lines
    UInt32	verticalBlanking;		// lines
    UInt32	verticalSyncOffset;		// lines
    UInt32	verticalSyncPulseWidth;		// lines

    UInt32	horizontalBorderLeft;		// pixels
    UInt32	horizontalBorderRight;		// pixels
    UInt32	verticalBorderTop;		// lines
    UInt32	verticalBorderBottom;		// lines

    UInt32	horizontalSyncConfig;
    UInt32	horizontalSyncLevel;		// Future use (init to 0)
    UInt32	verticalSyncConfig;
    UInt32	verticalSyncLevel;		// Future use (init to 0)

    UInt32	__reservedB[8];			// Init to 0
};
typedef struct IODetailedTimingInformationV2 IODetailedTimingInformationV2;

struct IOTimingInformation {
    IOAppleTimingID		appleTimingID;	// appleTimingXXX const
    UInt32			flags;
    union {
      IODetailedTimingInformation	v1;
      IODetailedTimingInformationV2	v2;
    }				detailedInfo;
};
typedef struct IOTimingInformation IOTimingInformation;

enum {
    // b0-7 from EDID flags
    kIODetailedTimingValid	= 0x80000000,
    kIOScalingInfoValid		= 0x40000000
};

struct IOFBDisplayModeDescription {
    IODisplayModeInformation	info;
    IOTimingInformation 	timingInfo;
};
typedef struct IOFBDisplayModeDescription IOFBDisplayModeDescription;

//// Connections

enum {
    kOrConnections			= 0xffffffe,
    kAndConnections			= 0xffffffd
};

enum {
    kConnectionFlags			= 'flgs',
    kConnectionSyncEnable		= 'sync',
    kConnectionSyncFlags		= 'sycf',
    kConnectionSupportsAppleSense	= 'asns',
    kConnectionSupportsLLDDCSense	= 'lddc',
    kConnectionSupportsHLDDCSense	= 'hddc',
    kConnectionEnable			= 'enab',
    kConnectionChanged			= 'chng',
    kConnectionPower			= 'powr'
};

// kConnectionFlags values
enum {
    kIOConnectionBuiltIn		= 0x00000800
};

// kConnectionSyncControl values
enum {
    kIOHSyncDisable			= 0x00000001,
    kIOVSyncDisable			= 0x00000002,
    kIOCSyncDisable			= 0x00000004,
    kIONoSeparateSyncControl		= 0x00000040,
    kIOTriStateSyncs			= 0x00000080,
    kIOSyncOnBlue			= 0x00000008,
    kIOSyncOnGreen			= 0x00000010,
    kIOSyncOnRed			= 0x00000020
};


#define IO_DISPLAY_CAN_FILL		0x00000040
#define IO_DISPLAY_CAN_BLIT		0x00000020

#define IO_24BPP_TRANSFER_TABLE_SIZE	256
#define IO_15BPP_TRANSFER_TABLE_SIZE	256
#define IO_8BPP_TRANSFER_TABLE_SIZE	256
#define IO_12BPP_TRANSFER_TABLE_SIZE	256
#define IO_2BPP_TRANSFER_TABLE_SIZE	256

#define STDFB_BM256_TO_BM38_MAP_SIZE	256
#define STDFB_BM38_TO_BM256_MAP_SIZE	256
#define STDFB_BM38_TO_256_WITH_LOGICAL_SIZE	\
	(STDFB_BM38_TO_BM256_MAP_SIZE + (256/sizeof(int)))

#define STDFB_4BPS_TO_5BPS_MAP_SIZE	16
#define STDFB_5BPS_TO_4BPS_MAP_SIZE	32

enum {
    // connection types for IOServiceOpen
    kIOFBServerConnectType		= 0,
    kIOFBSharedConnectType		= 1
};

enum {
    // options for IOServiceRequestProbe()
    kIOFBUserRequestProbe		= 0x00000001
};

struct IOGPoint {
    SInt16	x;
    SInt16	y;
};
typedef struct IOGPoint IOGPoint;

struct IOGSize {
    SInt16	width;
    SInt16	height;
};
typedef struct IOGSize IOGSize;

struct IOGBounds {
    SInt16	minx;
    SInt16	maxx;
    SInt16	miny;
    SInt16	maxy;
};
typedef struct IOGBounds IOGBounds;

#if !defined(__Point__) && !defined(BINTREE_H) && !defined(__MACTYPES__)
#define __Point__
typedef IOGPoint Point;
#endif

#if !defined(__Bounds__) && !defined(BINTREE_H) && !defined(__MACTYPES__)
#define __Bounds__
typedef IOGBounds Bounds;
#endif

// cursor description

enum {
   kTransparentEncoding 	= 0,
   kInvertingEncoding
};

enum {
   kTransparentEncodingShift	= (kTransparentEncoding << 1),
   kTransparentEncodedPixel	= (0x01 << kTransparentEncodingShift),

   kInvertingEncodingShift	= (kInvertingEncoding << 1),
   kInvertingEncodedPixel	= (0x01 << kInvertingEncodingShift)
};

enum {
   kHardwareCursorDescriptorMajorVersion	= 0x0001,
   kHardwareCursorDescriptorMinorVersion	= 0x0000
};

/*!
 * @struct IOHardwareCursorDescriptor
 * @abstract A structure defining the format of a hardware cursor.
 * @discussion This structure is used by IOFramebuffer to define the format of a hardware cursor.
 * @field majorVersion Set to kHardwareCursorDescriptorMajorVersion.
 * @field minorVersion Set to kHardwareCursorDescriptorMinorVersion.
 * @field height Maximum size of the cursor.
 * @field width Maximum size of the cursor.
 * @field bitDepth Number bits per pixel, or a QD/QT pixel type, for example kIO8IndexedPixelFormat, kIO32ARGBPixelFormat.
 * @field maskBitDepth Unused.
 * @field numColors Number of colors for indexed pixel types.
 * @field colorEncodings An array pointer specifying the pixel values corresponding to the indices into the color table, for indexed pixel types.
 * @field flags None defined, set to zero.
 * @field supportedSpecialEncodings Mask of supported special pixel values, eg. kTransparentEncodedPixel, kInvertingEncodedPixel.
 * @field specialEncodings Array of pixel values for each supported special encoding.
 */

struct IOHardwareCursorDescriptor {
   UInt16		majorVersion;
   UInt16		minorVersion;
   UInt32		height;
   UInt32		width;
   UInt32		bitDepth;			// bits per pixel, or a QD/QT pixel type
   UInt32		maskBitDepth;			// unused
   UInt32		numColors;			// number of colors in the colorMap. ie. 
   UInt32 *		colorEncodings;
   UInt32		flags;
   UInt32		supportedSpecialEncodings;
   UInt32		specialEncodings[16];
};
typedef struct IOHardwareCursorDescriptor IOHardwareCursorDescriptor;

// interrupt types

enum {
    kIOFBVBLInterruptType		= 'vbl ',
    kIOFBHBLInterruptType		= 'hbl ',
    kIOFBFrameInterruptType		= 'fram',
    // Demand to check configuration (Hardware unchanged)
    kIOFBConnectInterruptType		= 'dci ',
    // Demand to rebuild (Hardware has reinitialized on dependent change)
    kIOFBChangedInterruptType		= 'chng',
    // Demand to remove framebuffer (Hardware not available on dependent change -- but must not buserror)
    kIOFBOfflineInterruptType		= 'remv',
    // Notice that hardware is available (after being removed)
    kIOFBOnlineInterruptType		= 'add '
};

// framebuffer property keys

#define kIOFramebufferInfoKey		"IOFramebufferInformation"

#define kIOFBWidthKey			"IOFBWidth"
#define kIOFBHeightKey			"IOFBHeight"
#define kIOFBRefreshRateKey		"IOFBRefreshRate"
#define kIOFBFlagsKey			"IOFBFlags"
#define kIOFBBytesPerRowKey		"IOFBBytesPerRow"
#define kIOFBBytesPerPlaneKey		"IOFBBytesPerPlane"
#define kIOFBBitsPerPixelKey		"IOFBBitsPerPixel"
#define kIOFBComponentCountKey		"IOFBComponentCount"
#define kIOFBBitsPerComponentKey	"IOFBBitsPerComponent"

#define kIOFBDetailedTimingsKey		"IOFBDetailedTimings"
#define kIOFBTimingRangeKey		"IOFBTimingRange"
#define kIOFBScalerInfoKey		"IOFBScalerInfo"
#define kIOFBCursorInfoKey		"IOFBCursorInfo"

#define kIOFBHostAccessFlagsKey		"IOFBHostAccessFlags"

#define kIOFBMemorySizeKey		"IOFBMemorySize"

#define kIOFBProbeOptionsKey		"IOFBProbeOptions"

// diagnostic keys

#define kIOFBConfigKey			"IOFBConfig"
#define kIOFBModesKey			"IOFBModes"
#define kIOFBModeIDKey			"ID"
#define kIOFBModeDMKey			"DM"
#define kIOFBModeTMKey			"TM"
#define kIOFBModeAIDKey			"AID"
#define kIOFBModeDFKey			"DF"

// display property keys

#define kIODisplayEDIDKey		"IODisplayEDID"
#define kIODisplayLocationKey		"IODisplayLocation"		// CFString
#define kIODisplayConnectFlagsKey	"IODisplayConnectFlags"		// CFNumber
#define kIODisplayHasBacklightKey	"IODisplayHasBacklight"		// CFBoolean
#define kIODisplayIsDigitalKey		"IODisplayIsDigital"		// CFBoolean
#define kDisplayBundleKey		"DisplayBundle"

#define kAppleDisplayTypeKey		"AppleDisplayType"
#define kAppleSenseKey			"AppleSense"


enum {
    kDisplayVendorIDUnknown	= 'unkn',
    kDisplayProductIDGeneric	= 0x717
};

#define kDisplayVendorID		"DisplayVendorID"	 // CFNumber
#define kDisplayProductID		"DisplayProductID"	 // CFNumber
#define kDisplaySerialNumber		"DisplaySerialNumber"	 // CFNumber
#define kDisplaySerialString		"DisplaySerialString"	 // CFString
#define kDisplayWeekOfManufacture	"DisplayWeekManufacture" // CFNumber
#define kDisplayYearOfManufacture	"DisplayYearManufacture" // CFNumber

// CFDictionary of language-locale keys, name values
// eg. "en"="Color LCD", "en-GB"="Colour LCD"
#define kDisplayProductName		"DisplayProductName"

// all CFNumber or CFArray of CFNumber (floats)
#define kDisplayWhitePointX		"DisplayWhitePointX"
#define kDisplayWhitePointY		"DisplayWhitePointY"
#define kDisplayRedPointX		"DisplayRedPointX"
#define kDisplayRedPointY		"DisplayRedPointY"
#define kDisplayGreenPointX		"DisplayGreenPointX"
#define kDisplayGreenPointY		"DisplayGreenPointY"
#define kDisplayBluePointX		"DisplayBluePointX"
#define kDisplayBluePointY		"DisplayBluePointY"
#define kDisplayWhiteGamma		"DisplayWhiteGamma"
#define kDisplayRedGamma		"DisplayRedGamma"
#define kDisplayGreenGamma		"DisplayGreenGamma"
#define kDisplayBlueGamma		"DisplayBlueGamma"

// Display gamma
#define kDisplayGammaChannels		"DisplayGammaChannels" 	  // CFNumber 1 or 3 channel count
#define kDisplayGammaEntryCount		"DisplayGammaEntryCount"  // CFNumber 1-based count of entries per channel
#define kDisplayGammaEntrySize		"DisplayGammaEntrySize"	  // CFNumber size in bytes of each table entry
#define kDisplayGammaTable		"DisplayGammaTable" 	  // CFData

// CFBoolean
#define kDisplayBrightnessAffectsGamma	"DisplayBrightnessAffectsGamma"
#define kDisplayViewAngleAffectsGamma	"DisplayViewAngleAffectsGamma"

// CFData
#define kDisplayCSProfile		"DisplayCSProfile"

// CFNumber
#define kDisplayHorizontalImageSize	"DisplayHorizontalImageSize"
#define kDisplayVerticalImageSize	"DisplayVerticalImageSize"

// Pixel description

// CFBoolean
#define kDisplayFixedPixelFormat	"DisplayFixedPixelFormat"

enum {
    kDisplaySubPixelLayoutUndefined	= 0x00000000,
    kDisplaySubPixelLayoutRGB		= 0x00000001,
    kDisplaySubPixelLayoutBGR		= 0x00000002,
    kDisplaySubPixelLayoutQuadGBL	= 0x00000003,
    kDisplaySubPixelLayoutQuadGBR	= 0x00000004,

    kDisplaySubPixelConfigurationUndefined    = 0x00000000,
    kDisplaySubPixelConfigurationDelta	      = 0x00000001,
    kDisplaySubPixelConfigurationStripe	      = 0x00000002,
    kDisplaySubPixelConfigurationStripeOffset = 0x00000003,
    kDisplaySubPixelConfigurationQuad	      = 0x00000004,

    kDisplaySubPixelShapeUndefined	= 0x00000000,
    kDisplaySubPixelShapeRound		= 0x00000001,
    kDisplaySubPixelShapeSquare		= 0x00000002,
    kDisplaySubPixelShapeRectangular	= 0x00000003,
    kDisplaySubPixelShapeOval		= 0x00000004,
    kDisplaySubPixelShapeElliptical	= 0x00000005
};

// CFNumbers
#define kDisplaySubPixelLayout		"DisplaySubPixelLayout"
#define kDisplaySubPixelConfiguration	"DisplaySubPixelConfiguration"
#define kDisplaySubPixelShape		"DisplaySubPixelShape"

// Display parameters

#define kIODisplayParametersKey		"IODisplayParameters"
#define kIODisplayGUIDKey		"IODisplayGUID"

#define kIODisplayValueKey		"value"
#define kIODisplayMinValueKey		"min"
#define kIODisplayMaxValueKey		"max"

#define kIODisplayBrightnessKey		"brightness"
#define kIODisplayContrastKey		"contrast"
#define kIODisplayHorizontalPositionKey	"horizontal-position"
#define kIODisplayHorizontalSizeKey	"horizontal-size"
#define kIODisplayVerticalPositionKey	"vertical-position"
#define kIODisplayVerticalSizeKey	"vertical-size"
#define kIODisplayTrapezoidKey		"trapezoid"
#define kIODisplayPincushionKey		"pincushion"
#define kIODisplayParallelogramKey	"parallelogram"
#define kIODisplayRotationKey		"rotation"
#define kIODisplayTheatreModeKey	"theatre-mode"
#define kIODisplayTheatreModeWindowKey	"theatre-mode-window"

#define kIODisplayParametersCommitKey	"commit"
#define kIODisplayParametersDefaultKey	"defaults"

#ifdef __cplusplus
}
#endif

#endif /* ! _IOKIT_IOGRAPHICSTYPES_H */
