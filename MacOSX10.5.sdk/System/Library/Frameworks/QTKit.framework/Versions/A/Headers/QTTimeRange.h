/*
	File:		QTTimeRange.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>

typedef struct {
	QTTime		time;
	QTTime		duration;
} QTTimeRange;

QTKIT_EXTERN QTTimeRange QTMakeTimeRange (QTTime time, QTTime duration)						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN BOOL QTTimeInTimeRange (QTTime time, QTTimeRange range)						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN BOOL QTEqualTimeRanges (QTTimeRange range, QTTimeRange range2)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN QTTime QTTimeRangeEnd (QTTimeRange range)										AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN QTTimeRange QTUnionTimeRange (QTTimeRange range1, QTTimeRange range2)			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTimeRange QTIntersectionTimeRange (QTTimeRange range1, QTTimeRange range2)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// dd:hh:mm:ss.ff/ts~dd:hh:mm:ss.ff/ts
QTKIT_EXTERN NSString *QTStringFromTimeRange (QTTimeRange range)							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN QTTimeRange QTTimeRangeFromString (NSString* string)							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@interface NSValue (NSValueQTTimeRangeExtensions)
+ (NSValue *)valueWithQTTimeRange:(QTTimeRange)range;
- (QTTimeRange)QTTimeRangeValue;
@end

@interface NSCoder (NSQTTimeRangeCoding)
- (void)encodeQTTimeRange:(QTTimeRange)range forKey:(NSString *)key;
- (QTTimeRange)decodeQTTimeRangeForKey:(NSString *)key;
@end
