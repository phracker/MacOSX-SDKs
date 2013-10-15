/*
	File:		QTMedia.h

	Copyright:	(c)2004 by Apple Computer, Inc., all rights reserved.

*/


#import <Foundation/Foundation.h>
#import <QuickTime/QuickTime.h>
#import <QTKit/QTKitDefines.h>

    // media types
QTKIT_EXTERN NSString *QTMediaTypeVideo								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeSound								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeText								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeBase								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeMPEG								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeMusic								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeTimeCode							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeSprite							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeFlash								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeMovie								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeTween								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaType3D								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeSkin								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeQTVR								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeHint								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaTypeStream							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

    // media characteristics
QTKIT_EXTERN NSString *QTMediaCharacteristicVisual					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicAudio					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicCanSendVideo			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicProvidesActions			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicNonLinear				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicCanStep					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicHasNoDuration			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicHasSkinData				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicProvidesKeyFocus		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMediaCharacteristicHasVideoFrameRate		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

    // media attributes
QTKIT_EXTERN NSString *QTMediaCreationTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSDate
QTKIT_EXTERN NSString *QTMediaDurationAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTime)
QTKIT_EXTERN NSString *QTMediaModificationTimeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString *QTMediaSampleCountAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)
QTKIT_EXTERN NSString *QTMediaQualityAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (short)
QTKIT_EXTERN NSString *QTMediaTimeScaleAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)
QTKIT_EXTERN NSString *QTMediaTypeAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString

@class QTMovie;
@class QTTrack;

@interface QTMedia : NSObject
{
@private
    Media			_media;
	NSUndoManager   *_undoManager;
	NSDictionary	*_undoAttributes;
    long			_reserved1;
    long			_reserved2;
    long			_reserved3;
}

    // class/init methods
+ (id)mediaWithQuickTimeMedia:(Media)media error:(NSError **)errorPtr;
- (id)initWithQuickTimeMedia:(Media)media error:(NSError **)errorPtr;

    // parent
- (QTTrack *)track;

    // attributes
- (NSDictionary *)mediaAttributes;
- (void)setMediaAttributes:(NSDictionary *)attributes;

- (id)attributeForKey:(NSString *)attributeKey;
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey;

    // characteristics
- (BOOL)hasCharacteristic:(NSString *)characteristic;

    // underlying QT object
- (Media)quickTimeMedia;

@end
