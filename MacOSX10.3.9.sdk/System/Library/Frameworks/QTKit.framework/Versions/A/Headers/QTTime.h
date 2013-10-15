/*
	File:		QTTime.h

	Copyright:	(c)2004 by Apple Computer, Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QuickTime/QuickTime.h>
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

QTKIT_EXTERN QTTime QTMakeTimeWithTimeRecord(TimeRecord timeRecord)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTMakeTimeWithTimeInterval(NSTimeInterval timeInterval)			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTMakeTime(long long timeValue, long timeScale)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTMakeTimeScaled(QTTime time, long timeScale)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN BOOL QTGetTimeRecord(QTTime time, TimeRecord* timeRecord)				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN BOOL QTGetTimeInterval(QTTime time, NSTimeInterval* timeInterval)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN NSComparisonResult QTTimeCompare(QTTime time, QTTime otherTime)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN QTTime QTTimeIncrement(QTTime time, QTTime increment)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTTimeDecrement(QTTime time, QTTime decrement)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//¥¥¥dd:hh:mm:ss.ff/ts
QTKIT_EXTERN NSString* QTStringFromTime(QTTime time)								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTime QTTimeFromString(NSString* string)								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN BOOL QTTimeIsIndefinite(QTTime time)									AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@interface NSValue (NSValueQTTimeExtensions)
+ (NSValue *)valueWithQTTime:(QTTime)time;
- (QTTime)QTTimeValue;
@end

@interface NSCoder (NSQTTimeCoding)
- (void)encodeQTTime:(QTTime)time forKey:(NSString *)key;
- (QTTime)decodeQTTimeForKey:(NSString *)key;
@end
