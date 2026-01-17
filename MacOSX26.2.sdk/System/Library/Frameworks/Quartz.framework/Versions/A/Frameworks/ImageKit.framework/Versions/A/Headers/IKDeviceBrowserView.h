//
//  IKDeviceBrowserView.h
//  ImageKit
//
//  Copyright 2008 Apple Inc.. All rights reserved.
//


#ifndef IKDeviceBrowserView_h
#define IKDeviceBrowserView_h

#import <Cocoa/Cocoa.h>
#import <ImageCaptureCore/ImageCaptureCore.h>
#import <ImageKit/ImageKitBase.h>

@class IKDeviceBrowserView;


/*! 
 @protocol IKDeviceBrowserViewDelegate
 @abstract A delegate of IKDeviceBrowserView must conform to IKDeviceBrowserViewDelegate protocol.
 */

@protocol IKDeviceBrowserViewDelegate
@required
/*! 
 @method deviceBrowserView:selectionDidChange:
 @abstract This message is sent when the user selection did change.
 @discussion The device may be a ICCameraDevice or a ICScannerDevice.
 */
- (void)deviceBrowserView: (IKDeviceBrowserView *)deviceBrowserView selectionDidChange: (ICDevice *)device;

@optional
/*! 
 @method deviceBrowserView:didEncounterError:
 @abstract This message is sent every time the device browser reports an error.
 */
- (void)deviceBrowserView: (IKDeviceBrowserView *)deviceBrowserView didEncounterError: (NSError *)error;

@end


typedef NS_CLOSED_ENUM(NSInteger, IKDeviceBrowserViewDisplayMode)
{
    IKDeviceBrowserViewDisplayModeTable,
    IKDeviceBrowserViewDisplayModeOutline,
    IKDeviceBrowserViewDisplayModeIcon
};


/*! 
 @class IKDeviceBrowserView
 @abstract IKDeviceBrowserView displays Image Capture cameras and scanners.
 */

IK_CLASS_AVAILABLE(10.6)
@interface IKDeviceBrowserView : NSView
{
@private
    id _privateData;
}

/*!
 @property delegate
 @abstract delegate of the IKDeviceBrowserView.
 */
@property (assign) IBOutlet id<IKDeviceBrowserViewDelegate> delegate;

/*!
 @property displaysLocalCameras
 @abstract for device filtering - indicates that the IKDeviceBrowserView should include local cameras.
 */
@property BOOL displaysLocalCameras;

/*!
 @property displaysNetworkCameras
 @abstract for device filtering - indicates that the IKDeviceBrowserView should include network/shared cameras.
 */
@property BOOL displaysNetworkCameras;

/*!
 @property displaysLocalScanners
 @abstract for device filtering - indicates that the IKDeviceBrowserView should include local scanners.
 */
@property BOOL displaysLocalScanners;

/*!
 @property displaysNetworkScanners
 @abstract for device filtering - indicates that the IKDeviceBrowserView should include network/shared scanners.
 */
@property BOOL displaysNetworkScanners;

/*!
 @property mode
 @abstract one of the supported display modes (table, outline, or icon mode).
 */
@property IKDeviceBrowserViewDisplayMode mode;

/*!
 @property selectedDevice
 @abstract user selected device (ICCameraDevice or ICScannerDevice).
 */
@property (readonly) ICDevice * selectedDevice;
@end

#endif
