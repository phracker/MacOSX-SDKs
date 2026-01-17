//
//  PGDisplay.h
//  ParavirtualizedGraphics
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#ifndef PGDisplay_h
#define PGDisplay_h

#import <Foundation/Foundation.h>
#import <dispatch/dispatch.h>
#import <IOSurface/IOSurface.h>
#import <AppKit/NSBitmapImageRep.h>
#import <CoreVideo/CoreVideo.h>
#import <Metal/Metal.h>
#import <ParavirtualizedGraphics/PGDefines.h>

/*!
 @typedef PGDisplayCoord_t
 @abstract A struct for describing size of or offsets into a 2D array of pixels (used for size of display mode, size of cursor, and cursor hotSpot).
 @field x Represents horizontal pixel offset/size
 @field y Represents vertical pixel offset/size
 */
typedef struct {
    uint16_t x;
    uint16_t y;
} PGDisplayCoord_t API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
@protocol PGDisplay;

/*!
 @typedef PGDisplayModeChangeHandler
 @abstract A block that will be invoked at display mode change boundaries.
 @param sizeInPixels Size of upcoming frames.
 @param pixelFormat Pixel format of upcoming frames.
 */
typedef void (^PGDisplayModeChangeHandler)(PGDisplayCoord_t sizeInPixels, OSType pixelFormat) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGDisplayNewFrameEventHandler
 @abstract A block that will be invoked to notify client of availability of new Guest compositor frame to be further processed.
 @discussion See encodeCurrentFrameToCommandBuffer:texture:region: below to get further processing underway.
 */
typedef void (^PGDisplayNewFrameEventHandler)(void) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGDisplayCursorGlyphHandler
 @abstract A block that will be invoked to handle cursor glyph updates.
 @param glyph Cursor glyph to apply.
 @param hotSpot Top,left relative location of hotSpot.
 */
typedef void (^PGDisplayCursorGlyphHandler)(NSBitmapImageRep * _Nonnull glyph, PGDisplayCoord_t hotSpot) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGDisplayCursorShowHandler_t
 @abstract A block that will be invoked to handle cursor show/hide updates.
 @param show Flag indicating whether to show cursor glyph.
 */
typedef void (^PGDisplayCursorShowHandler)(BOOL show) API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @typedef PGDisplayCursorMoveHandler_t
 @abstract A block that will be invoked to handle cursor movement.
 */
typedef void (^PGDisplayCursorMoveHandler)(void) API_AVAILABLE(macos(11.1)) API_UNAVAILABLE(ios);

/*!
 @interface PGDisplayDescriptor:
 @abstract Descriptor to facilitate creation of PGDisplay.
 @discussion See [PGDevice newDisplayWithDescriptor:port:serialNum]
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
@interface PGDisplayDescriptor : NSObject

/*!
 @property name
 @abstract Client supplied name of display, as seen by guest.
 @discussion Truncates to 13 characters.  Defaults to "Apple Virtual".  Value provided here may be made visible via guest UI.
 */
@property(readwrite, nonatomic, nullable, copy) NSString *name API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property sizeInMillimeters
 @abstract Client supplied display size conveyed to guest compositor.
 @discussion Conveyed size contributes to guest compositor layout, but host-side VM app can scale to UI of its own choosing.
 */
@property(readwrite, nonatomic) NSSize sizeInMillimeters API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property queue
 @abstract Client supplied dispatch_queue on which to invoke client supplied blocks.
 @discussion Typical client provides serial queue, and redispatches if beneficial to process out of order.
 */
@property(readwrite, nonatomic, nullable, retain) dispatch_queue_t queue API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property presentModeChangeHandler
 @abstract The block to invoke to handle display mode change.
 @discussion Handler invocation indicative of display mode change.
 */
@property(readwrite, nonatomic, nullable, copy) PGDisplayModeChangeHandler modeChangeHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property newFrameEventHandler
 @abstract The block to invoke to handle notification of the presence of a new Guest compositor frame.
 @discussion Handler invocation indicates presence of new frame to be processed for display.  Only one of newFrameEventHandler or presentHandler may be non-nil.
 */
@property(readwrite, nonatomic, nullable, copy) PGDisplayNewFrameEventHandler newFrameEventHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property cursorGlyphHandler
 @abstract The block to invoke to handle cursor glyph updates.
 @discussion Handler invocation indicative of new cursor image for display.  If this block is not set, cursor will be precomposited in presented image.
 */
@property(readwrite, nonatomic, nullable, copy) PGDisplayCursorGlyphHandler cursorGlyphHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property cursorShowHandler
 @abstract The block to invoke to handle cursor show/hide updates.
 @discussion Handler invocation indicative of hide/show of cursor glyph.  If this block is not set, cursor will be precomposited in presented image.
 */
@property(readwrite, nonatomic, nullable, copy) PGDisplayCursorShowHandler cursorShowHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property cursorMoveHandler
 @abstract The block to invoke to handle cursor movement.
 @discussion Handler invocation indicative of movement.  Handler should resampling via PGDisplay::cursorPosition.
 */
@property(readwrite, nonatomic, nullable, copy) PGDisplayCursorMoveHandler cursorMoveHandler API_AVAILABLE(macos(11.1)) API_UNAVAILABLE(ios);

@end

/*!
 @interface PGDisplayMode:
 @abstract Description of supported display mode.
 @discussion Client of PGDisplay can dynamically supply NSArray of PGDisplayMode objects to convey supported modes.  The first mode in array is preferred.
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
@interface PGDisplayMode : NSObject

/*!
 @property sizeInPixels
 @abstract Width/height of supported display mode.
 */
@property(readonly, nonatomic) PGDisplayCoord_t sizeInPixels API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property refreshRateInHz
 @abstract refreshRate of supported display mode.  Consider only supplying modes using a refreshRate equal to that of host OS's physical display where representation is ultimately shown.
 */
 @property(readonly, nonatomic) double refreshRate API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method initWithSizeInPixels:refreshRateInHz
 @abstract Used to conjure up display mode objects (to be arranged into NSArrays for modeList).
 @param sizeInPixels Width/height of supported display mode.
 @param refreshRateInHz Refresh rate of supported display mode.
 */
- (nullable PGDisplayMode *)initWithSizeInPixels:(PGDisplayCoord_t)sizeInPixels
                                 refreshRateInHz:(double)refreshRateInHz API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);
@end

/*!
 @protocol PGDisplay:
 @abstract Object providing display functionality to guest in a way that host-side VM app can intercept (and process as it chooses).
 @discussion The first time the modeList is set for a display, the guest will receive a simulated hot-plug of a display on its port. When this object is freed, the guest will receive a simulated hot-unplug of the display on its port.
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
@protocol PGDisplay<NSObject>

/*!
 @property name
 @abstract The name of the display.
 */
@property(readonly, nonatomic, nullable) NSString *name API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property sizeInMillimeters
 @abstract The size of the display.
 @discussion Mostly for debug visibility.
 */
@property(readonly, nonatomic) NSSize sizeInMillimeters API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property queue
 @abstract The dispatch_queue on which to invoke client supplied blocks.
*/
@property(readonly, nonatomic, nullable) dispatch_queue_t queue API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property modeChangeHandler
 @abstract The block to invoke to handle display mode change.
 */
@property(readonly, nonatomic, nullable) PGDisplayModeChangeHandler modeChangeHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property newFrameEventHandler
 @abstract The block to invoke to notify presence of new Guest frame to be processed.
 @discussion See encodeCurrentFrameToCommandBuffer:texture:region: below to get further processing underway.
 */
@property(readonly, nonatomic, nullable) PGDisplayNewFrameEventHandler newFrameEventHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property cursorGlyphHandler
 @abstract The block to invoke to handle cursor glyph updates.
 */
@property(readonly, nonatomic, nullable) PGDisplayCursorGlyphHandler cursorGlyphHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property cursorShowHandler
 @abstract The block to invoke to handle cursor show/hide updates.
 */
@property(readonly, nonatomic, nullable) PGDisplayCursorShowHandler cursorShowHandler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property cursorMoveHandler
 @abstract The block to invoke to handle cursor movement.
 */
@property(readonly, nonatomic, nullable) PGDisplayCursorMoveHandler cursorMoveHandler API_AVAILABLE(macos(11.1)) API_UNAVAILABLE(ios);

/*!
 @property cursorPosition
 @abstract Top,left display relative position of cursor hotSpot.
 @discussion This is a low overhead mechanism to sample cursor location on this display of guest compositor.  Sentinel value for cursor not on display is {0xffff,0xffff}.
 */
@property(readonly, nonatomic) PGDisplayCoord_t cursorPosition API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property serialNum
 @abstract Create-time serialNum of display.
 @discussion Mostly for debug visibility.  Param of [PGDevice newDisplayWithDescriptor:port:serialNum].
 */
@property(readonly, nonatomic) uint32_t serialNum API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property port
 @abstract Create-time port number of display.
 @discussion Mostly for debug visibility.  Param of [PGDevice newDisplayWithDescriptor:port:serialNum].
 */
@property(readonly, nonatomic) NSUInteger port API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property minimumTextureUsage
 @abstract Minimally required textureUsage bits for destination texture of encodeCurrentFrameToCommandBuffer:texture:region:.
 @discussion If destination texture doesn't meet this requirement, encodeCurrentFrameToCommandBuffer:texture:region: will fail.
 */
@property(readonly, nonatomic) MTLTextureUsage minimumTextureUsage API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property guestPresentCount
 @abstract The number of frame presents generated by the guest since object creation.
 @discussion This value could exceed the number of times newFrameEventHandler block is invoked when host is not encoding frames fast enough to keep up.
 */
@property(readonly, nonatomic) NSUInteger guestPresentCount API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property hostPresentCount
 @abstract The number of unique frames encoded for present by the host since object creation.
 @discussion This value could be smaller than than the count of times encodeCurrentFrameToCommandBuffer:texture:region: is invoked when same frame is encoded multiple times.
 */
@property(readonly, nonatomic) NSUInteger hostPresentCount API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @property modeList
 @abstract Supported list of display modes.
 @discussion This is the only writeable property of display object.  Setting it will update supported mode list (up to 128 modes) and potentially trigger a mode change.  First setting looks like hot-plug.
 */
@property(readwrite, nonatomic, copy, nonnull) NSArray<PGDisplayMode *>  *modeList API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/*!
 @method encodeCurrentFrameToCommandBuffer:texture:region:
 @abstract Encode processing of new frame (to deal with gamma, CSC, and more...), landing it in specific region of specific texture.
 @param commandBuffer The Metal command buffer in which to encode processing of new frame.
 @param texture The Metal texture in which the processed frame should land.
 @param region The region within the Metal texture that the (linear scaled) frame should land in.
 @return True if encoding was successful, otherwise, false.
 @discussion Client calls this method to direct display object to append encoded display processing Metal pass to client supplied commandBuffer.  Processed frame will land in specified region of client supplied texture.  Nothing outside the specified region will be written.  Note that commandBuffer and texture objects must both be descendants of host Metal device being used for guest acceleration.  Note that texture.textureUsage must contain the bits specified in self.minimumTextureUsage.  See newFrameEventHandler above since it notifies client of the existence of a new frame.
 */
- (bool) encodeCurrentFrameToCommandBuffer:(id<MTLCommandBuffer>_Nonnull)commandBuffer texture:(id<MTLTexture>_Nonnull)texture region:(MTLRegion)region API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

@end

#endif // PGDisplay_h
