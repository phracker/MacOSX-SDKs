//------------------------------------------------------------------------------------------------------------------------------
//
//  ICDeviceBrowser.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
    @header ICDeviceBrowser
    @discussion The ICDeviceBrowser object is used to find devices such as digital cameras and scanners that are supported by Image Capture. These device may be directly attached to the USB or FireWire bus on the host computer, shared by other computers, or available over a TCP/IP network. This object communicates with an Image Capture agent process asynchronously to accomplish this.
*/

#import <ImageCaptureCore/ICDevice.h>

//------------------------------------------------------------------------------------------------------------------------------
// Forward declarations

@class ICDeviceBrowser;

CF_ASSUME_NONNULL_BEGIN

//------------------------------------------------------------------------------------------------------ ICDeviceBrowserDelegate
/*! 
  @protocol ICDeviceBrowserDelegate <NSObject>
  @abstract A delegate of ICDeviceBrowser must conform to ICDeviceBrowserDelegate protocol. 
*/

@protocol ICDeviceBrowserDelegate <NSObject>

@required

/*! 
  @method deviceBrowser:didAddDevice:moreComing:
  @abstract This message is sent to the delegate to inform that a device has been added.
  @discussion If several devices are found during the initial search, then this message is sent once for each device with the value of 'moreComing' set to YES in each message except the last one. 
*/
- (void)deviceBrowser:( ICDeviceBrowser*)browser didAddDevice:( ICDevice*)device moreComing:(BOOL)moreComing;

/*! 
  @method deviceBrowser:didRemoveDevice:moreGoing:
  @abstract This message is sent to the delegate to inform that a device has been removed.
  @discussion If several devices are removed at the same time, then this message is sent once for each device with the value of 'moreGoing' set to YES in each message except the last one. 
*/
- (void)deviceBrowser:( ICDeviceBrowser*)browser didRemoveDevice:( ICDevice*)device moreGoing:(BOOL)moreGoing;

@optional

/*! 
  @method deviceBrowser:deviceDidChangeName:
  @abstract This message is sent if the name of a device changes.
  @discussion This happens if the device module overrides the default name of the device reported by the device's transport layer, or if the name of the filesystem volume mounted by the device is changed by the user.
*/
- (void)deviceBrowser:( ICDeviceBrowser*)browser deviceDidChangeName:( ICDevice*)device;

/*! 
  @method deviceBrowser:deviceDidChangeSharingState:
  @abstract This message is sent when the sharing state of a device has changes.
  @discusson Any Image Capture client application can choose to share the device over the network using the sharing or webSharing facility in Image Capture.
*/
- (void)deviceBrowser:( ICDeviceBrowser*)browser deviceDidChangeSharingState:( ICDevice*)device;

/*! 
  @method deviceBrowser:requestsSelectDevice:
  @abstract This message is sent when an event that occurred on the device may be of interest to the client application.
  @discussion In Mac OS X 10.6, this message is sent when a button is pressed on a device and the current application is the target for that button press. In the case of the button-press event, if a session is open on the device, this message will not be sent to the browser delegate, instead the message 'device:didReceiveButtonPress:' is sent to the device delegate.
*/
- (void)deviceBrowser:( ICDeviceBrowser*)browser requestsSelectDevice:( ICDevice*)device;

@optional
/*! 
  @method deviceBrowserDidEnumerateLocalDevices:
  @abstract This message is sent after the device browser completes sending 'deviceBrowser:didAddDevice:moreComing:' message for all local devices.
  @discusson Detecting locally connected devices (USB and FireWire devices) is faster than detecting devices connected using a network protocol. An Image Capture client application may use this message to update its user interface to let the user know that it has completed looking for locally connected devices and then start looking for network devices.
*/
- (void)deviceBrowserDidEnumerateLocalDevices:( ICDeviceBrowser*)browser;

@end

//-------------------------------------------------------------------------------------------------------------- ICDeviceBrowser
/*! 
  @class ICDeviceBrowser
  @abstract The ICDeviceBrowser object is used to find devices such as digital cameras and scanners that are supported by Image Capture. These device may be directly attached to the USB or FireWire bus on the host computer, shared by other computers, or available over a TCP/IP network. This object communicates with an Image Capture agent process asynchronously to accomplish this.
*/
@interface ICDeviceBrowser : NSObject
{
@private
    id _privateData;
}

/*! 
  @property delegate
  @abstract The delegate. It must conform to ICDeviceBrowserDelegate protocol. The messages this delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
@property(assign, nullable)          id <ICDeviceBrowserDelegate>  delegate;

/*! 
  @property browsing
  @abstract Indicates whether the device browser is browsing for devices.
*/
@property(readonly, getter=isBrowsing)  BOOL                          browsing;

/*! 
  @property browsedDeviceTypeMask
  @abstract A mask whose set bits indicate the type of device(s) being browsed after the receiver receives the start message. This property can be changed while the browser is browsing for devices. This property can be constructed by OR'd values of ICDeviceTypeMask with values of ICDeviceLocationTypeMask.
*/
@property(readwrite)                    ICDeviceTypeMask              browsedDeviceTypeMask;

/*! 
  @property devices
  @abstract All devices found by the browser. This property will change as devices appear and disappear. This array is empty before the first invocation of the delegate method 'deviceBrowser:didAddDevice:moreComing:'.
*/
@property(readonly,nullable)            NSArray<ICDevice*>*                      devices;

/*!
    @method preferredDevice
    @abstract This method returns a device object that should be selected by the client application when it is launched.
    @discussion If the client application that calls this method is the auto-launch application associated with a device and that device is the last device attached (through USB, FireWire or network), then that device will be the preferred device. The best place to call this method is in the implmentation of the ICDeviceBrowser delegate method "deviceBrowser:didAddDevice:moreComing:", if the "moreComing" parameter passed to the delegate is "NO"; or in the delegate method "deviceBrowserDidEnumerateLocalDevices:".
*/
- ( ICDevice*)preferredDevice;

/*! 
  @method init
  @abstract This is the designated initializer.
*/
- ( id)init;

/*! 
  @method start:
  @abstract This message tells the receiver to start looking for devices.
  @discussion Make sure that the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. The messages the delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
- (void)start;

/*! 
  @method stop:
  @abstract This method tells the receiver to stop looking for devices.
  @discussion This will free all device instances that are not in use.
*/
- (void)stop;

CF_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------
