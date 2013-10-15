/*
	File:		QTCaptureAudioPreviewOutput.h

	Copyright:	(c)2007 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTCaptureOutput.h>

@class QTCaptureAudioPreviewOutputInternal;

@interface QTCaptureAudioPreviewOutput : QTCaptureOutput {
@private
#if !__LP64__
	QTCaptureAudioPreviewOutputInternal	*_internal;
#endif
	long								_reserved4;
	long								_reserved5;
	long								_reserved6;
}

// These methods determine the unique ID of the CoreAudio device being used for audio preview. A unique ID of nil corresponds to the default system output device.
- (NSString *)outputDeviceUniqueID;
- (void)setOutputDeviceUniqueID:(NSString *)uniqueID;

- (float)volume;
- (void)setVolume:(float)volume;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
