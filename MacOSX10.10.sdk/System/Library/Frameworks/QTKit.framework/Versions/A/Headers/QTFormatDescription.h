/*
	File:		QTFormatDescription.h
 
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

// Attribute Keys:

// Audio-specific
QTKIT_EXTERN NSString * const QTFormatDescriptionAudioStreamBasicDescriptionAttribute			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue interpreted as AudioStreamBasicDescription
QTKIT_EXTERN NSString * const QTFormatDescriptionAudioMagicCookieAttribute						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSData
QTKIT_EXTERN NSString * const QTFormatDescriptionAudioChannelLayoutAttribute					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSData interpreted as AudioChannelLayout

// Video-specific
QTKIT_EXTERN NSString * const QTFormatDescriptionVideoCleanApertureDisplaySizeAttribute			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue interpreted as NSSize
QTKIT_EXTERN NSString * const QTFormatDescriptionVideoProductionApertureDisplaySizeAttribute	AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue interpreted as NSSize
QTKIT_EXTERN NSString * const QTFormatDescriptionVideoEncodedPixelsSizeAttribute				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue interpreted as NSSize

@class QTFormatDescriptionInternal;

@interface QTFormatDescription : NSObject {
@private
	QTFormatDescriptionInternal	*_internal;
	long						_reserved1;
	long						_reserved2;
	long						_reserved3;
}

- (NSString *)mediaType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// Media types defined in QTMedia.h
- (UInt32)formatType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;		// A four character code representing the format or codec type. Video codec types are defined in <QuickTime/ImageCompression.h>. Audio codec types are define in <CoreAudio/CoreAudioTypes.h>.
- (NSString *)localizedFormatSummary AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (NSData *)quickTimeSampleDescription AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// Contains a QuickTime SampleDescription structure

- (NSDictionary *)formatDescriptionAttributes AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)attributeForKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (BOOL)isEqualToFormatDescription:(QTFormatDescription *)formatDescription AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
