#if !__has_include(<AVFCapture/AVCaptureControl.h>)
/*
    File:  AVCaptureControl.h
 
    Framework:  AVFoundation
 
    Copyright 2024 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @protocol AVCaptureControl
 @abstract
    AVCaptureControl is an abstract class that defines an interface for a unique type of control which allows deep integration with the camera system through AVCaptureSession.
 
 @discussion
    Various concrete subclasses of `AVCaptureControl` are provided by AVFoundation to allow your application to both leverage common system controls and define unique custom controls.
 
    Controls may be added to an `AVCaptureSession` using `-[AVCaptureSession addControl:]`.
 
    For controls that use symbols to represent them, only SF Symbols may be used.
 */
API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureControl : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property enabled
 @abstract
    Indicates whether the control should be enabled for user interaction.

 @discussion
    The value of this property is a `BOOL` that determines whether the control should be enabled for user interaction. Clients can set this property to keep a control added to an `AVCaptureSession` but prevent it from being interacted with by the user. A control's value may still be changed while it is disabled. The default value is `YES`.
 */
@property(nonatomic, getter=isEnabled) BOOL enabled;

@end

NS_ASSUME_NONNULL_END


#else
#import <AVFCapture/AVCaptureControl.h>
#endif
