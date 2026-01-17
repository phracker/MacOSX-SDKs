/*
	File:		QTTime.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <CoreAudio/CoreAudioTypes.h>	// SMPTETime
#import <QTKit/QTKitDefines.h>

enum {
    kQTTimeIsIndefinite = 1 << 0
};

typedef struct {
	long long		timeValue;
	long			timeScale;
	long			flags;
} QTTime;

QTKIT_EXTERN const QTTime QTZeroTime												AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN const QTTime QTIndefiniteTime											AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN QTTime QTMakeTimeWithTimeRecord (TimeRecord timeRecord)				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTMakeTimeWithTimeInterval (NSTimeInterval timeInterval)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTMakeTime (long long timeValue, long timeScale)				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTMakeTimeScaled (QTTime time, long timeScale)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN BOOL QTGetTimeRecord (QTTime time, TimeRecord *timeRecord)				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN BOOL QTGetTimeInterval (QTTime time, NSTimeInterval *timeInterval)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN NSComparisonResult QTTimeCompare (QTTime time, QTTime otherTime)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN QTTime QTTimeIncrement (QTTime time, QTTime increment)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTTimeDecrement (QTTime time, QTTime decrement)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// dd:hh:mm:ss.ff/ts
QTKIT_EXTERN NSString *QTStringFromTime (QTTime time)								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTTimeFromString (NSString *string)								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN BOOL QTTimeIsIndefinite (QTTime time)									AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@interface NSValue (NSValueQTTimeExtensions)
+ (NSValue *)valueWithQTTime:(QTTime)time;
- (QTTime)QTTimeValue;
@end

@interface NSCoder (NSQTTimeCoding)
- (void)encodeQTTime:(QTTime)time forKey:(NSString *)key;
- (QTTime)decodeQTTimeForKey:(NSString *)key;
@end

// SMPTETime:

// hh:mm:ss:ff or hh:mm:ss;ff for drop frame
QTKIT_EXTERN NSString *QTStringFromSMPTETime(SMPTETime time)						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2

@interface NSValue (NSValueQTSMPTETimeExtensions)
+ (NSValue *)valueWithSMPTETime:(SMPTETime)time;
- (SMPTETime)SMPTETimeValue;
@end

@interface NSCoder (NSCoderQTSMPTETimeCoding)
- (void)encodeSMPTETime:(SMPTETime)time forKey:(NSString *)key;
- (SMPTETime)decodeSMPTETimeForKey:(NSString *)key;
@end

#endif	/* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */
