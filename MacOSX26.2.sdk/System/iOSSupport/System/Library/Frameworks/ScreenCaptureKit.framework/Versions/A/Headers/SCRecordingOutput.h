//
//  SCRecordingOutput.h
//  ScreenCaptureKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#ifndef SCRecordingOutput_h
#define SCRecordingOutput_h

#import <CoreMedia/CMTime.h>
#import <AVFoundation/AVVideoSettings.h>
#import <AVFoundation/AVMediaFormat.h>

NS_ASSUME_NONNULL_BEGIN

@class SCRecordingOutput;

/*!
 @abstract SCRecordingOutputConfiguration
 @discussion SCRecordingOutputConfiguration is an object that encapsulates the configuration for recording.
*/
API_AVAILABLE(macos(15.0), macCatalyst(18.2))
@interface SCRecordingOutputConfiguration : NSObject

/*!
 @abstract Specifies output URL to save the recording.
 */
@property(nonatomic, copy) NSURL *outputURL;

/*!
 @abstract Specifies video codec for the recording output, default is AVVideoCodecTypeH264, supported values can be obtained using availableVideoCodecTypes
 */
@property(nonatomic, copy) AVVideoCodecType videoCodecType;

/*!
 @abstract Specifies file type for the recording output, default is AVFileTypeMPEG4, supported values can be obtained using availableOutputFileTypes
 */
@property(nonatomic, copy) AVFileType outputFileType;

/*!
 @abstract Returns an array of supported video codec formats that can be specified in SCRecordingOutputConfiguration for videoCodecType
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableVideoCodecTypes;

/*!
 @abstract Returns an array of supported file types that can be specified in SCRecordingOutputConfiguration for outputFileType
    Provides the file types AVCaptureAudioFileOutput can write.
 */
@property(nonatomic, readonly) NSArray<AVFileType> *availableOutputFileTypes;

@end

/*!
 @protocol SCRecordingOutputDelegate
 @abstract
    Defines an interface for delegates of SCRecordingOutput to respond to events that occur in the process of recording to file.
 */
API_AVAILABLE(macos(15.0), macCatalyst(18.2))
@protocol SCRecordingOutputDelegate <NSObject>

@optional
/*!
 @abstract recordingOutputDidStartRecording:
 @param recordingOutput the SCRecordingOutput object
 @discussion notifies the delegate that recording has succesfully started.
*/
- (void)recordingOutputDidStartRecording:(SCRecordingOutput *)recordingOutput;

/*!
 @abstract recordingOutput:didFailWithError:
 @param recordingOutput the SCRecordingOutput object
 @param error error describing why the recording failed.
 @discussion notifies the delegate that recording has failed with error associated.
*/
- (void)recordingOutput:(SCRecordingOutput *)recordingOutput didFailWithError:(NSError *)error;

/*!
 @abstract recordingOutputDidFinishRecording:
 @discussion notifies the delegate that recording has finished successfully.
*/
- (void)recordingOutputDidFinishRecording:(SCRecordingOutput *)recordingOutput;

@end

API_AVAILABLE(macos(15.0), macCatalyst(18.2))
@interface SCRecordingOutput : NSObject
/*!
 @abstract Indicates current duration of recording to the output file.
 */
@property(nonatomic, readonly) CMTime recordedDuration;

/*!
 @abstract Indicates current size, in bytes, of the data recorded to the output file.
 */
@property(nonatomic, readonly) NSInteger recordedFileSize;

/*!
 @method initWithConfiguration:delegate:
 @abstract initialize SCRecordingOutput object with SCRecordingOutputConfiguration and SCRecordingOutputDelegate
 @param recordingOutputConfiguration the requested recording configuration to be applied to the SCRecordingOutput
 @parame delegate object conforming SCRecordingOutputDelegate protocol. Clients must specify a delegate so that they can be notified about recording event.
 @discussion Client can create a SCRecordingOutput with this initializer and add to SCStream to record all captured media into one recording file given output url specified in recordingOutputConfig. The recording will be using H264 and file format is MPEG-4.
*/
- (instancetype)initWithConfiguration:(SCRecordingOutputConfiguration *)recordingOutputConfiguration delegate:(id<SCRecordingOutputDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

#endif /* SCRecordingOutput_h */
