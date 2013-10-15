/*
	File:		QTTrack.h

	Copyright:	(c)2004-2007 by Apple Computer, Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>

@class QTMovie;
@class QTMedia;
@class NSImage;

	// track attributes
QTKIT_EXTERN NSString * const QTTrackBoundsAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (NSRect)
QTKIT_EXTERN NSString * const QTTrackCreationTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTTrackDimensionsAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (NSSize)
QTKIT_EXTERN NSString * const QTTrackDisplayNameAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTTrackEnabledAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTTrackFormatSummaryAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTTrackIsChapterTrackAttribute				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTTrackHasApertureModeDimensionsAttribute		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTTrackIDAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTTrackLayerAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (short)
QTKIT_EXTERN NSString * const QTTrackMediaTypeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTTrackModificationTimeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTTrackRangeAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTimeRange)
QTKIT_EXTERN NSString * const QTTrackTimeScaleAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTTrackUsageInMovieAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTTrackUsageInPosterAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTTrackUsageInPreviewAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTTrackVolumeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)

@interface QTTrack : NSObject
{
@private
#if __LP64__
	int32_t			_proxy;
#else
	Track			_track;
	void			*_objectToken;
	NSUndoManager	*_undoManager;
	NSDictionary	*_undoAttributes;
	UInt32			_trackID;
	Movie			_trackMovie;
#endif
	long			_reserved1;
	long			_reserved2;
	long			_reserved3;
}

#if !__LP64__
	// class/init methods
+ (id)trackWithQuickTimeTrack:(Track)track error:(NSError **)errorPtr;
- (id)initWithQuickTimeTrack:(Track)track error:(NSError **)errorPtr;
#endif

	// parent/child
- (QTMovie *)movie;
- (QTMedia *)media;

	// attributes
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)enabled;

- (float)volume;
- (void)setVolume:(float)volume;

- (NSDictionary *)trackAttributes;
- (void)setTrackAttributes:(NSDictionary *)attributes;

- (id)attributeForKey:(NSString *)attributeKey;
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey;

#if !__LP64__
	// underlying QT object
- (Track)quickTimeTrack;
#endif

	// track-level editing
- (void)insertSegmentOfTrack:(QTTrack *)track timeRange:(QTTimeRange)range atTime:(QTTime)time;
- (void)insertSegmentOfTrack:(QTTrack *)track fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange;
- (void)insertEmptySegmentAt:(QTTimeRange)range;
- (void)deleteSegment:(QTTimeRange)segment;
- (void)scaleSegment:(QTTimeRange)segment newDuration:(QTTime)newDuration;

- (void)addImage:(NSImage *)image forDuration:(QTTime)duration withAttributes:(NSDictionary *)attributes;

@end

@interface QTTrack (QTTrackVisualSupport)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (NSSize)apertureModeDimensionsForMode:(NSString *)mode;
- (void)setApertureModeDimensions:(NSSize)dimensions forMode:(NSString *)mode;

- (void)generateApertureModeDimensions;
- (void)removeApertureModeDimensions;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */

@end

