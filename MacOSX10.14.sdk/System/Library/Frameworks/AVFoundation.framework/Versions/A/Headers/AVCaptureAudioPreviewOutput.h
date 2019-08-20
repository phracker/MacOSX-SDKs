/*
    File:  AVCaptureAudioPreviewOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2017 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutputBase.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureAudioPreviewOutput

@class AVCaptureAudioPreviewOutputInternal;

/*!
 @class AVCaptureAudioPreviewOutput
 @abstract
    AVCaptureAudioPreviewOutput is a concrete subclass of AVCaptureOutput that can be used to preview the audio being captured.
 
 @discussion
    Instances of AVCaptureAudioPreviewOutput have an associated Core Audio output device that can be used to play audio being captured by the capture session. The unique ID of a Core Audio device can be obtained from its kAudioDevicePropertyDeviceUID property.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos)
@interface AVCaptureAudioPreviewOutput : AVCaptureOutput
{
@private
    AVCaptureAudioPreviewOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @property outputDeviceUniqueID
 @abstract
    Specifies the unique ID of the Core Audio output device being used to play preview audio.
 
 @discussion
    The value of this property is an NSString containing the unique ID of the Core Audio device to be used for output, or nil if the default system output should be used.
 */
@property(nonatomic, copy, nullable) NSString *outputDeviceUniqueID;

/*!
 @property volume
 @abstract
    Specifies the preview volume of the output.
 
 @discussion
    The value of this property is the preview volume of the receiver, where 1.0 is the maximum volume and 0.0 is muted. 
 */
@property(nonatomic) float volume;

@end

NS_ASSUME_NONNULL_END
