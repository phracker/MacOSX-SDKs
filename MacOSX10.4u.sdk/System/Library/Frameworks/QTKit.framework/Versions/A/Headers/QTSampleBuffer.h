/*
	File:		QTSampleBuffer.h
 
	Copyright:	(c)2007 by Apple Inc., all rights reserved.
 
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTTime.h>
#import <CoreAudio/CoreAudioTypes.h>	// AudioBufferList and AudioStreamPacketDescription

QTKIT_EXTERN NSString * const QTSampleBufferSMPTETimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // NSValue interpreted as a SMPTETime (defined in CoreAudio/CoreAudioTypes.h). See QTTime.h for operations that can be performed on SMPTETime structures.
QTKIT_EXTERN NSString * const QTSampleBufferDateRecordedAttribute				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // NSDate
QTKIT_EXTERN NSString * const QTSampleBufferHostTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // NSNumber, interpreted as a uint64_t
QTKIT_EXTERN NSString * const QTSampleBufferSceneChangeTypeAttribute			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // One of the following string constants:
QTKIT_EXTERN NSString * const QTSampleBufferExplicitSceneChange					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // scene change is explicitly marked in the metadata of the sample buffer
QTKIT_EXTERN NSString * const QTSampleBufferTimeStampDiscontinuitySceneChange	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // scene change indicated by a discontinuity between this sample buffer's time stamp and the previous sample buffer's time stamp

// Options passed to audioBufferListWithOptions:
enum {
	QTSampleBufferAudioBufferListOptionAssure16ByteAlignment = (1L << 0)
};
typedef NSUInteger QTSampleBufferAudioBufferListOptions;

@class QTFormatDescription;
@class QTSampleBufferInternal;

@interface QTSampleBuffer : NSObject {
@private
#if __LP64__
	int32_t					_proxy;
#else
	QTSampleBufferInternal	*_internal;
#endif	
	long					_reserved1;
	long					_reserved2;
	long					_reserved3;
}

#if !__LP64__
- (void *)bytesForAllSamples;
- (NSUInteger)lengthForAllSamples;
#endif

// Format info
- (QTFormatDescription *)formatDescription;

// Timing info
- (QTTime)duration;
- (QTTime)decodeTime;
- (QTTime)presentationTime;

// Multiple sample info
- (NSUInteger)numberOfSamples;

// Attributes
- (NSDictionary *)sampleBufferAttributes;
- (id)attributeForKey:(NSString *)key;

@end

// These methods allow clients to control when the potentially large memory buffers owned by a QTSampleBuffer are deallocated. A newly allocated QTSampleBuffer has a sample use count of 1. When the sample use count drops to 0, the memory allocated for the samples will be freed and the bytesForAllSamples, lengthForAllSamples, and audioBufferListWithOptions: methods will each throw an NSInternalInconsistencyException when called. Clients using garbage collection in particular should ensure that the sample use count is 0 when they no longer require the sample data owned by a QTSampleBuffer, so that memory can be deallocated propmptly rather than when the object is finalized.
// Clients interested in the sample data of QTSampleBuffer objects returned by other APIs in QTKit should call incrementSampleUseCount to ensure that they have acceess to the sample data, and later call decrementSampleUseCount when they no longer need that data.
@interface QTSampleBuffer (QTSampleBufferUseCount)

- (NSUInteger)sampleUseCount;
- (void)incrementSampleUseCount;
- (void)decrementSampleUseCount;

@end

// These methods provide functionality specific to audio sample buffers. If the receiver of one of these methods is not an audio sample buffer an NSInternalInconsistencyException will be thrown.
@interface QTSampleBuffer (QTAudioSampleBuffer)

#if !__LP64__
// This method returns a pointer to a CoreAudio AudioBufferList containing all of the audio data in the sample buffer. The AudioBufferList can then be passed to CoreAudio APIs for rendering and processing audio. The returned AudioBufferList will be valid for as long as the QTSampleBuffer is valid and its sample use count has not been decpremented to 0. Clients passing the AudioBufferList to an audio unit must include the QTSampleBufferAudioBufferListOptionAssure16ByteAlignment flag in the options parameter.
- (AudioBufferList *)audioBufferListWithOptions:(QTSampleBufferAudioBufferListOptions)options;
#endif

// Use this method with VBR audio sample buffers to get the size of each audio packet in the buffer. The maximum value in the range must be the value returned by numberOfSamples. If the sample buffer does not contain VBR audio, this method returns NO and leaves audioStreamPacketDescriptions untouched. Otherwise it fills the memory pointed to by audioStreamPacketDescriptions with an array of CoreAudio AudioStreamPacketDescription structures and returns YES.
- (BOOL)getAudioStreamPacketDescriptions:(AudioStreamPacketDescription *)audioStreamPacketDescriptions inRange:(NSRange)range;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
