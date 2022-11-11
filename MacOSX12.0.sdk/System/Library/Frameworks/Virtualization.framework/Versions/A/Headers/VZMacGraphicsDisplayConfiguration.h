//
//  VZMacGraphicsDisplayConfiguration.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration for a display attached to a Mac graphics device.
 @discussion This display can be shown in a VZVirtualMachineView.
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacGraphicsDisplayConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Create a display configuration with the specified pixel dimensions and pixel density.
 @param widthInPixels The width of the display, in pixels.
 @param heightInPixels The height of the display, in pixels.
 @param pixelsPerInch The pixel density as a number of pixels per inch.
*/
- (instancetype)initWithWidthInPixels:(NSInteger)widthInPixels heightInPixels:(NSInteger)heightInPixels pixelsPerInch:(NSInteger)pixelsPerInch NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Create a display configuration suitable for showing on the specified screen.
 @param screen The screen on which you intend to present the VZVirtualMachineView for the display.
 @param sizeInPoints The intended logical size of the display.
 @discussion
     The pixel dimensions and pixel density will be initialized based on the specified screen and
     size. Note: an instance of macOS running in the virtual machine may not necessarily provide
     a display mode with a backing scale factor matching the specified screen.
*/
- (instancetype)initForScreen:(NSScreen *)screen sizeInPoints:(NSSize)sizeInPoints NS_SWIFT_NAME(init(for:sizeInPoints:));

/*!
 @abstract The width of the display, in pixels.
*/
@property NSInteger widthInPixels;

/*!
 @abstract The height of the display, in pixels.
*/
@property NSInteger heightInPixels;

/*!
 @abstract The pixel density as a number of pixels per inch.
*/
@property NSInteger pixelsPerInch;

@end

NS_ASSUME_NONNULL_END
