#if !__has_include(<AVFCapture/AVContinuityDevice.h>)
/*
    File:  AVContinuityDevice.h
 
    Framework:  AVFoundation
 
    Copyright 2023 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFAudio/AVFAudio.h>
#import <AVFoundation/AVCaptureDevice.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - AVContinuityDevice

/*!
 @class AVContinuityDevice
 @abstract
    An AVContinuityDevice represents a physical iOS device that provides capture devices and audio session ports.
 
 @discussion
    Each instance of AVContinuityDevice corresponds to a continuity device, such as an iPhone or iPad. Instances of AVContinuityDevice cannot be created directly.
 */
API_AVAILABLE(tvos(17.0)) API_UNAVAILABLE(macos, macCatalyst, ios, watchos)
@interface AVContinuityDevice : NSObject

AV_INIT_UNAVAILABLE

/*!
  @property connectionID
  @abstract
     A connection ID of the continuity device.
  
  @discussion
     This property can be used to uniquely identify a continuity device. Every available continuity device has a unique ID that regenerates across device connections and disconnections.
  */
 @property(nonatomic, readonly) NSUUID *connectionID;

/*!
 @property connected
 @abstract
    Indicates whether the continuity device is connected and available to the system.
 
 @discussion
    The value of this property is a BOOL indicating whether the continuity device represented by the receiver is connected and available for use. Clients can key value observe the value of this property to be notified when a continuity device is no longer available. When the value of this property becomes NO for a given instance, it will not become YES again. If the same physical continuity device again becomes available to the system, it will be represented using a new instance of AVContinuityDevice.
 */
@property(nonatomic, readonly, getter=isConnected) BOOL connected;

/*!
 @property videoDevices
 @abstract
    The video capture devices available from the continuity device.
 */
@property(nonatomic, readonly) NSArray<AVCaptureDevice *> *videoDevices;

/*!
 @property audioSessionInputs
 @abstract
    The audio session inputs available from the continuity device.
 */
@property(nonatomic, readonly) NSArray<AVAudioSessionPortDescription *> *audioSessionInputs;

@end

NS_ASSUME_NONNULL_END


#else
#import <AVFCapture/AVContinuityDevice.h>
#endif
