/*
	File:		QTCaptureConnection.h
 
	Copyright:	(c)2007 by Apple Inc., all rights reserved.
 
 */

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

@class QTFormatDescription;

// Notifications
QTKIT_EXTERN NSString * const QTCaptureConnectionFormatDescriptionWillChangeNotification	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureConnectionFormatDescriptionDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

QTKIT_EXTERN NSString * const QTCaptureConnectionAttributeWillChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureConnectionAttributeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// userInfo key for QTCaptureConnectionAttributeWillChangeNotification and QTCaptureConnectionAttributeDidChangeNotification for the key of the changed attribute
QTKIT_EXTERN NSString * const QTCaptureConnectionChangedAttributeKey						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Attributes
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioAveragePowerLevelsAttribute			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSArray of NSNumbers representing power for each audio channel in dB
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioPeakHoldLevelsAttribute				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSArray of NSNumbers representing power for each audio channel in dB
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioMasterVolumeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber between 0.0 and 1.0 for normal volume; above 1.0 for boosted gain
QTKIT_EXTERN NSString * const QTCaptureConnectionAudioVolumesAttribute						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSArray of NSNumbers between 0.0 and 1.0 for normal volume; above 1.0 for boosted gain
QTKIT_EXTERN NSString * const QTCaptureConnectionEnabledAudioChannelsAttribute				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSIndexSet containing the indices of the audio channels that are enabled

@class QTCaptureConnectionInternal;

@interface QTCaptureConnection : NSObject {
@private
#if __LP64__
	int32_t						_proxy;
#else
	QTCaptureConnectionInternal	*_internal;
#endif
	long						_reserved1;
	long						_reserved2;
	long						_reserved3;
}

- (id)owner;

- (NSString *)mediaType;	// media types are defined in QTMedia.h
- (QTFormatDescription *)formatDescription;

- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)enabled;

- (NSDictionary *)connectionAttributes;
- (void)setConnectionAttributes:(NSDictionary *)connectionAttributes;
- (BOOL)attributeIsReadOnly:(NSString *)attributeKey;
- (id)attributeForKey:(NSString *)attributeKey;
- (void)setAttribute:(id)attribute forKey:(NSString *)key;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
