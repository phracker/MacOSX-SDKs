/*
	File:		QTCaptureConnection.h
 
	Copyright:	(c)2007-2012 by Apple Inc., all rights reserved.
 
*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

@class QTFormatDescription;

// Notifications
QTKIT_EXTERN NSString * const QTCaptureConnectionFormatDescriptionWillChangeNotification	AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTCaptureConnectionFormatDescriptionDidChangeNotification		AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN NSString * const QTCaptureConnectionAttributeWillChangeNotification			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTCaptureConnectionAttributeDidChangeNotification				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

// userInfo key for QTCaptureConnectionAttributeWillChangeNotification and QTCaptureConnectionAttributeDidChangeNotification for the key of the changed attribute
QTKIT_EXTERN NSString * const QTCaptureConnectionChangedAttributeKey						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

// Attributes
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioAveragePowerLevelsAttribute			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;  // NSArray of NSNumbers representing power for each audio channel in dB
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioPeakHoldLevelsAttribute				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSArray of NSNumbers representing power for each audio channel in dB
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioMasterVolumeAttribute					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSNumber between 0.0 and 1.0 for normal volume; above 1.0 for boosted gain
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioVolumesAttribute						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSArray of NSNumbers between 0.0 and 1.0 for normal volume; above 1.0 for boosted gain
QTKIT_EXTERN NSString * const QTCaptureConnectionEnabledAudioChannelsAttribute				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSIndexSet containing the indices of the audio channels that are enabled

@class QTCaptureConnectionInternal;

@interface QTCaptureConnection : NSObject {
@private
	QTCaptureConnectionInternal	*_internal;
	long						_reserved1;
	long						_reserved2;
	long						_reserved3;
}

- (id)owner AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (NSString *)mediaType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// media types are defined in QTMedia.h
- (QTFormatDescription *)formatDescription AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (BOOL)isEnabled AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setEnabled:(BOOL)enabled AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (NSDictionary *)connectionAttributes AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setConnectionAttributes:(NSDictionary *)connectionAttributes AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)attributeIsReadOnly:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)attributeForKey:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setAttribute:(id)attribute forKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
