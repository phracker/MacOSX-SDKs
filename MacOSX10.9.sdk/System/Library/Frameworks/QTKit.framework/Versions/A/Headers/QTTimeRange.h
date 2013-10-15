/*
	File:		QTTimeRange.h

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
#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>

typedef struct {
	QTTime		time;
	QTTime		duration;
} QTTimeRange;

QTKIT_EXTERN QTTimeRange QTMakeTimeRange (QTTime time, QTTime duration)						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN BOOL QTTimeInTimeRange (QTTime time, QTTimeRange range)						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN BOOL QTEqualTimeRanges (QTTimeRange range, QTTimeRange range2)					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN QTTime QTTimeRangeEnd (QTTimeRange range)										AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN QTTimeRange QTUnionTimeRange (QTTimeRange range1, QTTimeRange range2)			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN QTTimeRange QTIntersectionTimeRange (QTTimeRange range1, QTTimeRange range2)	AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

// dd:hh:mm:ss.ff/ts~dd:hh:mm:ss.ff/ts
QTKIT_EXTERN NSString *QTStringFromTimeRange (QTTimeRange range)							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN QTTimeRange QTTimeRangeFromString (NSString* string)							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@interface NSValue (NSValueQTTimeRangeExtensions)
+ (NSValue *)valueWithQTTimeRange:(QTTimeRange)range AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (QTTimeRange)QTTimeRangeValue AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
@end

@interface NSCoder (NSQTTimeRangeCoding)
- (void)encodeQTTimeRange:(QTTimeRange)range forKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (QTTimeRange)decodeQTTimeRangeForKey:(NSString *)key AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
@end
