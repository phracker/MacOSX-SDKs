/*
	File:		QTMovie.h

	Copyright:	(c)2004-2005 by Apple Computer, Inc., all rights reserved.

*/


#import <Cocoa/Cocoa.h>
#import <QuickTime/QuickTime.h>
#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>

@class QTMovie;
@class QTTrack;
@class QTDataReference;

	// pasteboard support
QTKIT_EXTERN NSString *QTMoviePasteboardType						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

    // notifications																							description                             parameter			parameter type
QTKIT_EXTERN NSString *QTMovieEditabilityDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in movie editability              -                   -
QTKIT_EXTERN NSString *QTMovieEditedNotification					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // edit was done to the movie               -                   -
QTKIT_EXTERN NSString *QTMovieLoadStateDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in movie load state               -                   -
QTKIT_EXTERN NSString *QTMovieLoopModeDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in movie looping mode				-                   -
QTKIT_EXTERN NSString *QTMovieMessageStringPostedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // message string                           message				NSString
QTKIT_EXTERN NSString *QTMovieRateDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in movie rate                     rate				NSNumber (float)
QTKIT_EXTERN NSString *QTMovieSelectionDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in selection start/duration       -                   -
QTKIT_EXTERN NSString *QTMovieSizeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in movie size                   -                   -
QTKIT_EXTERN NSString *QTMovieStatusStringPostedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // status string                            status				NSString
QTKIT_EXTERN NSString *QTMovieTimeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // goto time occured                        -                   -
QTKIT_EXTERN NSString *QTMovieVolumeDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in volume                         -                   -
QTKIT_EXTERN NSString *QTMovieDidEndNotification					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // movie ended                              -                   -
QTKIT_EXTERN NSString *QTMovieChapterDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in current chapter                -                   -
QTKIT_EXTERN NSString *QTMovieChapterListDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // change in chapter list                   -                   -
QTKIT_EXTERN NSString *QTMovieEnterFullScreenRequestNotification	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // full screen playback requested			-					-
QTKIT_EXTERN NSString *QTMovieExitFullScreenRequestNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // normal windowed playback requested		-					-
QTKIT_EXTERN NSString *QTMovieCloseWindowRequestNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // window close requested					-					-
QTKIT_EXTERN NSString *QTMovieApertureModeDidChangeNotification     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // change in visual aperture mode           -                   -

    // notification parameters
QTKIT_EXTERN NSString *QTMovieMessageNotificationParameter			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieRateDidChangeNotificationParameter	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieStatusFlagsNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieStatusCodeNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieStatusStringNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN NSString *QTMovieTargetIDNotificationParameter			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString *QTMovieTargetNameNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// writeToFile: attributes dictionary keys
QTKIT_EXTERN NSString *QTMovieExport								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieExportType							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)
QTKIT_EXTERN NSString *QTMovieFlatten								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieExportSettings						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSData (QTAtomContainer)
QTKIT_EXTERN NSString *QTMovieExportManufacturer					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)

	// addImage: attributes dictionary keys
QTKIT_EXTERN NSString *QTAddImageCodecType							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString
QTKIT_EXTERN NSString *QTAddImageCodecQuality						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber

	// data locators for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString *QTMovieDataReferenceAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // QTDataReference
QTKIT_EXTERN NSString *QTMoviePasteboardAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSPasteboard
QTKIT_EXTERN NSString *QTMovieDataAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSData

	// movie instantiation options for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString *QTMovieFileOffsetAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long long)
QTKIT_EXTERN NSString *QTMovieResolveDataRefsAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieAskUnresolvedDataRefsAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieOpenAsyncOKAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)

// movie attributes
QTKIT_EXTERN NSString *QTMovieApertureModeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
QTKIT_EXTERN NSString *QTMovieActiveSegmentAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTimeRange)
QTKIT_EXTERN NSString *QTMovieAutoAlternatesAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieCopyrightAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString
QTKIT_EXTERN NSString *QTMovieCreationTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSDate
QTKIT_EXTERN NSString *QTMovieCurrentSizeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (NSSize)
QTKIT_EXTERN NSString *QTMovieCurrentTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTime)
QTKIT_EXTERN NSString *QTMovieDataSizeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long long)
QTKIT_EXTERN NSString *QTMovieDelegateAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSObject
QTKIT_EXTERN NSString *QTMovieDisplayNameAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString
QTKIT_EXTERN NSString *QTMovieDontInteractWithUserAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieDurationAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTime)
QTKIT_EXTERN NSString *QTMovieEditableAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieFileNameAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString
QTKIT_EXTERN NSString *QTMovieHasApertureModeDimensionsAttribute	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieHasAudioAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieHasDurationAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieHasVideoAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieIsActiveAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieIsInteractiveAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieIsLinearAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieIsSteppableAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieLoadStateAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)
QTKIT_EXTERN NSString *QTMovieLoopsAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieLoopsBackAndForthAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieModificationTimeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSDate
QTKIT_EXTERN NSString *QTMovieMutedAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMovieNaturalSizeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (NSSize)
QTKIT_EXTERN NSString *QTMoviePlaysAllFramesAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMoviePlaysSelectionOnlyAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMoviePosterTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTime)
QTKIT_EXTERN NSString *QTMoviePreferredMutedAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMoviePreferredRateAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (float)
QTKIT_EXTERN NSString *QTMoviePreferredVolumeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (float)
QTKIT_EXTERN NSString *QTMoviePreviewModeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)
QTKIT_EXTERN NSString *QTMoviePreviewRangeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTimeRange)
QTKIT_EXTERN NSString *QTMovieRateAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (float)
QTKIT_EXTERN NSString *QTMovieSelectionAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSValue (QTTimeRange)
QTKIT_EXTERN NSString *QTMovieTimeScaleAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (long)
QTKIT_EXTERN NSString *QTMovieURLAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSURL
QTKIT_EXTERN NSString *QTMovieVolumeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (float)
QTKIT_EXTERN NSString *QTMovieRateChangesPreservePitchAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSNumber (BOOL)

	// aperture modes
QTKIT_EXTERN NSString *QTMovieApertureModeClassic					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString *QTMovieApertureModeClean						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString *QTMovieApertureModeProduction				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString *QTMovieApertureModeEncodedPixels				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

	// exceptions
QTKIT_EXTERN NSString *QTMovieUneditableException					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// constants for movieFileTypes method
typedef enum {
	QTIncludeStillImageTypes			= 1 << 0,
	QTIncludeTranslatableTypes			= 1 << 1,
	QTIncludeAggressiveTypes			= 1 << 2,
	QTIncludeCommonTypes				= 0,
	QTIncludeAllTypes					= 0xffff
} QTMovieFileTypeOptions;

// constants for movieShouldContinueOp delegate method
typedef enum {
	QTMovieOperationBeginPhase			= movieProgressOpen,
	QTMovieOperationUpdatePercentPhase  = movieProgressUpdatePercent,
	QTMovieOperationEndPhase			= movieProgressClose
} QTMovieOperationPhase;


@interface NSObject (QTMovieDelegate)

- (BOOL)movie:(QTMovie *)movie linkToURL:(NSURL *)url;			// return YES if delegate handled link-to-URL request
- (BOOL)movieShouldLoadData:(id)sender;
- (BOOL)movieShouldTask:(id)movie;
- (QTMovie *)externalMovie:(NSDictionary *)dictionary;
- (BOOL)movie:(QTMovie *)movie shouldContinueOperation:(NSString *)op withPhase:(QTMovieOperationPhase)phase atPercent:(NSNumber *)percent withAttributes:(NSDictionary *)attributes;

@end

@interface QTMovie : NSObject <NSCoding, NSCopying>
{
@private
    Movie			_movie;
    MovieController	_movieController;
    id				_dataReference;
	void			*_objectToken;
    void			*_movieControllerObjectToken;
    long            _reserved1;
    long            _reserved2;
    long            _reserved3;
	MovieEditState  _editState;
	NSUndoManager   *_undoManager;
	NSDictionary	*_undoAttributes;
    id              _delegate;
    BOOL            _disposeWhenDone;
    BOOL            _delegateLinkToURL;
    BOOL            _delegateShouldLoadData;
    BOOL            _delegateGetExternalMovie;
    BOOL            _delegateShouldContinueOp;
    BOOL            _delegateShouldChangeController;
    BOOL            _delegatePostNetworkDiagnosticUI;
    BOOL            _delegateHandleIdleEvent;
    BOOL            _haveSetControllerFromUserData;
    BOOL            _keepInactive;
    BOOL            _newEqualizer;
    BOOL            _draggable;
	long			_reserved4;
	NSDate			*_lastCheckDate;
	NSDictionary	*_pendingAttributes;
	SInt16			_resourceID;
	long			_seed;
}

- (QTTime)duration;

@end

@interface QTMovie (QTMovieInitialization)

+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;
+ (BOOL)canInitWithFile:(NSString *)fileName;
+ (BOOL)canInitWithURL:(NSURL *)url;
+ (BOOL)canInitWithDataReference:(QTDataReference *)dataReference;

+ (NSArray *)movieFileTypes:(QTMovieFileTypeOptions)types;
+ (NSArray *)movieUnfilteredFileTypes;
+ (NSArray *)movieUnfilteredPasteboardTypes;

+ (id)movie;
+ (id)movieWithFile:(NSString *)fileName error:(NSError **)errorPtr;
+ (id)movieWithURL:(NSURL *)url error:(NSError **)errorPtr;
+ (id)movieWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;
+ (id)movieWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr;
+ (id)movieWithData:(NSData *)data error:(NSError **)errorPtr;
+ (id)movieWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr;
+ (id)movieWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
+ (id)movieNamed:(NSString *)name error:(NSError **)errorPtr;

- (id)initWithFile:(NSString *)fileName error:(NSError **)errorPtr;
- (id)initWithURL:(NSURL *)url error:(NSError **)errorPtr;
- (id)initWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;
- (id)initWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr;
- (id)initWithData:(NSData *)data error:(NSError **)errorPtr;
- (id)initWithMovie:(QTMovie *)movie timeRange:(QTTimeRange)range error:(NSError **)errorPtr;
- (id)initWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr;
- (id)initWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;

- (QTMovie *)movieWithTimeRange:(QTTimeRange)range error:(NSError **)errorPtr;

@end

@interface QTMovie (QTMovieInspection)

- (QTTime)currentTime;
- (float)rate;
- (float)volume;
- (BOOL)muted;

    // attributes
- (NSDictionary *)movieAttributes;
- (void)setMovieAttributes:(NSDictionary *)attributes;

- (id)attributeForKey:(NSString *)attributeKey;
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey;

- (NSArray *)tracks;
- (NSArray *)tracksOfMediaType:(NSString *)type;

@end

@interface QTMovie (QTMovieImage)

- (NSImage *)posterImage;
- (NSImage *)currentFrameImage;
- (NSImage *)frameImageAtTime:(QTTime)time;

@end

@interface QTMovie (QTMovieFormat)

- (NSData *)movieFormatRepresentation;
- (BOOL)writeToFile:(NSString *)fileName withAttributes:(NSDictionary *)attributes;
- (BOOL)canUpdateMovieFile;
- (BOOL)updateMovieFile;

@end

@interface QTMovie (QTMovieTime)

- (void)play;
- (void)stop;

- (void)setCurrentTime:(QTTime)time;

- (void)gotoBeginning;
- (void)gotoEnd;
- (void)gotoNextSelectionPoint;
- (void)gotoPreviousSelectionPoint;
- (void)gotoPosterTime;
- (void)stepForward;
- (void)stepBackward;

@end

@interface QTMovie (QTMoviePlaybackControl)

- (void)setRate:(float)rate;
- (void)setVolume:(float)volume;
- (void)setMuted:(BOOL)mute;

@end

@interface QTMovie (QTSelection)

- (void)setSelection:(QTTimeRange)selection;
- (QTTime)selectionStart;
- (QTTime)selectionEnd;
- (QTTime)selectionDuration;

@end

@interface QTMovie (QTEditing)

- (void)replaceSelectionWithSelectionFromMovie:(id)movie;
- (void)appendSelectionFromMovie:(id)movie;

- (void)insertSegmentOfMovie:(QTMovie *)movie timeRange:(QTTimeRange)range atTime:(QTTime)time;
- (void)insertSegmentOfMovie:(QTMovie *)movie fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange;
- (void)insertEmptySegmentAt:(QTTimeRange)range;
- (void)deleteSegment:(QTTimeRange)segment;
- (void)scaleSegment:(QTTimeRange)segment newDuration:(QTTime)newDuration;

- (void)addImage:(NSImage *)image forDuration:(QTTime)duration withAttributes:(NSDictionary *)attributes;

@end

@interface QTMovie (QTDelegate)

- (id)delegate;
- (void)setDelegate:(id)delegate;

@end

@interface QTMovie (QTPrimitives)

- (Movie)quickTimeMovie;
- (MovieController)quickTimeMovieController;

@end

@interface QTMovie (QTMovieVisualSupport)

- (void)generateApertureModeDimensions;
- (void)removeApertureModeDimensions;

@end

