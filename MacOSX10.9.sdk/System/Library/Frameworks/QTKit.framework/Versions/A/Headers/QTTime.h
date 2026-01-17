/*
	File:		QTTime.h

	Copyright:	(c)2004-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
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

QTKIT_EXTERN const QTTime QTZeroTime												AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN const QTTime QTIndefiniteTime											AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN QTTime QTMakeTimeWithTimeRecord (TimeRecord timeRecord)				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN QTTime QTMakeTimeWithTimeInterval (NSTimeInterval timeInterval)		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN QTTime QTMakeTime (long long timeValue, long timeScale)				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN QTTime QTMakeTimeScaled (QTTime time, long timeScale)					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN BOOL QTGetTimeRecord (QTTime time, TimeRecord *timeRecord)				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN BOOL QTGetTimeInterval (QTTime time, NSTimeInterval *timeInterval)		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN NSComparisonResult QTTimeCompare (QTTime time, QTTime otherTime)		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN QTTime QTTimeIncrement (QTTime time, QTTime increment)					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN QTTime QTTimeDecrement (QTTime time, QTTime decrement)					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

// dd:hh:mm:ss.ff/ts
QTKIT_EXTERN NSString *QTStringFromTime (QTTime time)								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN QTTime QTTimeFromString (NSString *string)								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN BOOL QTTimeIsIndefinite (QTTime time)									AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@interface NSValue (NSValueQTTimeExtensions)
+ (NSValue *)valueWithQTTime:(QTTime)time AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (QTTime)QTTimeValue AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
@end

@interface NSCoder (NSQTTimeCoding)
- (void)encodeQTTime:(QTTime)time forKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (QTTime)decodeQTTimeForKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
@end

// SMPTETime:

// hh:mm:ss:ff or hh:mm:ss;ff for drop frame
QTKIT_EXTERN NSString *QTStringFromSMPTETime(SMPTETime time)						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2

@interface NSValue (NSValueQTSMPTETimeExtensions)
+ (NSValue *)valueWithSMPTETime:(SMPTETime)time AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (SMPTETime)SMPTETimeValue AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
@end

@interface NSCoder (NSCoderQTSMPTETimeCoding)
- (void)encodeSMPTETime:(SMPTETime)time forKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (SMPTETime)decodeSMPTETimeForKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
@end

#endif	/* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */
