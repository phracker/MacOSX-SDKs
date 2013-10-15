/*
	File:		QTTrack.h

	Copyright:	(c)2004 by Apple Computer, Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QuickTime/QuickTime.h>
#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>

@class QTMovie;
@class QTMedia;
@class NSImage;

    // track attributes
QTKIT_EXTERN NSString *QTTrackBoundsAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (NSRect)
QTKIT_EXTERN NSString *QTTrackCreationTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSDate
QTKIT_EXTERN NSString *QTTrackDimensionsAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (NSSize)
QTKIT_EXTERN NSString *QTTrackDisplayNameAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString
QTKIT_EXTERN NSString *QTTrackEnabledAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTTrackHasApertureModeDimensionsAttribute	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTTrackIDAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)
QTKIT_EXTERN NSString *QTTrackLayerAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (short)
QTKIT_EXTERN NSString *QTTrackMediaTypeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString
QTKIT_EXTERN NSString *QTTrackModificationTimeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString *QTTrackRangeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTimeRange)
QTKIT_EXTERN NSString *QTTrackTimeScaleAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)
QTKIT_EXTERN NSString *QTTrackUsageInMovieAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTTrackUsageInPosterAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTTrackUsageInPreviewAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTTrackVolumeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (float)

@interface QTTrack : NSObject
{
@private
    Track			_track;
    void			*_objectToken;
	NSUndoManager   *_undoManager;
	NSDictionary	*_undoAttributes;
    UInt32			_trackID;
    Movie			_trackMovie;
    long			_reserved1;
    long			_reserved2;
    long			_reserved3;
}

    // class/init methods
+ (id)trackWithQuickTimeTrack:(Track)track error:(NSError **)errorPtr;
- (id)initWithQuickTimeTrack:(Track)track error:(NSError **)errorPtr;

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

    // underlying QT object
- (Track)quickTimeTrack;

	// track-level editing
- (void)insertSegmentOfTrack:(QTTrack *)track timeRange:(QTTimeRange)range atTime:(QTTime)time;
- (void)insertSegmentOfTrack:(QTTrack *)track fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange;
- (void)insertEmptySegmentAt:(QTTimeRange)range;
- (void)deleteSegment:(QTTimeRange)segment;
- (void)scaleSegment:(QTTimeRange)segment newDuration:(QTTime)newDuration;

- (void)addImage:(NSImage *)image forDuration:(QTTime)duration withAttributes:(NSDictionary *)attributes;

@end

@interface QTTrack (QTTrackVisualSupport)

- (NSSize)apertureModeDimensionsForMode:(NSString *)mode;
- (void)setApertureModeDimensions:(NSSize)dimensions forMode:(NSString *)mode;

- (void)generateApertureModeDimensions;
- (void)removeApertureModeDimensions;

@end

