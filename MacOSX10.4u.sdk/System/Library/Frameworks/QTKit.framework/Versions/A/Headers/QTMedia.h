/*
	File:		QTMedia.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

*/


#import <Foundation/Foundation.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <QTKit/QTKitDefines.h>

	// media types
QTKIT_EXTERN NSString * const QTMediaTypeVideo								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeSound								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeText								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeBase								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeMPEG								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeMusic								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeTimeCode							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeSprite								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeFlash								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeMovie								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeTween								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaType3D									AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeSkin								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeQTVR								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeHint								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeStream								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeMuxed								AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaTypeQuartzComposer						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

	// media characteristics
QTKIT_EXTERN NSString * const QTMediaCharacteristicVisual					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicAudio					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicCanSendVideo				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicProvidesActions			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicNonLinear				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicCanStep					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicHasNoDuration			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicHasSkinData				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicProvidesKeyFocus			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMediaCharacteristicHasVideoFrameRate		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// media attributes
QTKIT_EXTERN NSString * const QTMediaCreationTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTMediaDurationAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTime)
QTKIT_EXTERN NSString * const QTMediaModificationTimeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTMediaSampleCountAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMediaQualityAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (short)
QTKIT_EXTERN NSString * const QTMediaTimeScaleAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMediaTypeAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString

@class QTMovie;
@class QTTrack;

@interface QTMedia : NSObject
{
@private
#if __LP64__
	int32_t			_proxy;
#else
	Media			_media;
	NSUndoManager	*_undoManager;
	NSDictionary	*_undoAttributes;
#endif
	long			_reserved1;
	long			_reserved2;
	long			_reserved3;
}

#if !__LP64__
	// class/init methods
+ (id)mediaWithQuickTimeMedia:(Media)media error:(NSError **)errorPtr;
- (id)initWithQuickTimeMedia:(Media)media error:(NSError **)errorPtr;
#endif

	// parent
- (QTTrack *)track;

	// attributes
- (NSDictionary *)mediaAttributes;
- (void)setMediaAttributes:(NSDictionary *)attributes;

- (id)attributeForKey:(NSString *)attributeKey;
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey;

	// characteristics
- (BOOL)hasCharacteristic:(NSString *)characteristic;

#if !__LP64__
	// underlying QT object
- (Media)quickTimeMedia;
#endif

@end
