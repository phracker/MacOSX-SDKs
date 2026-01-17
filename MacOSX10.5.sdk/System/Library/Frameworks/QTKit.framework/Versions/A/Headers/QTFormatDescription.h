/*
	File:		QTFormatDescription.h
 
	Copyright:	(c)2007 by Apple Inc., all rights reserved.
 
 */

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

// Attribute Keys:

// Audio-specific
QTKIT_EXTERN NSString * const QTFormatDescriptionAudioStreamBasicDescriptionAttribute			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue interpreted as AudioStreamBasicDescription
QTKIT_EXTERN NSString * const QTFormatDescriptionAudioMagicCookieAttribute						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSData
QTKIT_EXTERN NSString * const QTFormatDescriptionAudioChannelLayoutAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSData interpreted as AudioChannelLayout

// Video-specific
QTKIT_EXTERN NSString * const QTFormatDescriptionVideoCleanApertureDisplaySizeAttribute			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue interpreted as NSSize
QTKIT_EXTERN NSString * const QTFormatDescriptionVideoProductionApertureDisplaySizeAttribute	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue interpreted as NSSize
QTKIT_EXTERN NSString * const QTFormatDescriptionVideoEncodedPixelsSizeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue interpreted as NSSize

@class QTFormatDescriptionInternal;

@interface QTFormatDescription : NSObject {
@private
#if __LP64__
	int32_t						_proxy;
#else
	QTFormatDescriptionInternal	*_internal;
#endif	
	long						_reserved1;
	long						_reserved2;
	long						_reserved3;
}

- (NSString *)mediaType;	// Media types defined in QTMedia.h
- (UInt32)formatType;		// A four character code representing the format or codec type. Video codec types are defined in <QuickTime/ImageCompression.h>. Audio codec types are define in <CoreAudio/CoreAudioTypes.h>.
- (NSString *)localizedFormatSummary;

#if !__LP64__
- (NSData *)quickTimeSampleDescription;	// Contains a QuickTime SampleDescription structure
#endif

- (NSDictionary *)formatDescriptionAttributes;
- (id)attributeForKey:(NSString *)key;

- (BOOL)isEqualToFormatDescription:(QTFormatDescription *)formatDescription;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
