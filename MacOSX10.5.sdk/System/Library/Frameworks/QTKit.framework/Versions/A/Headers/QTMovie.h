/*
	File:		QTMovie.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

*/


#import <Cocoa/Cocoa.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>

@class QTMovie;
@class QTTrack;
@class QTDataReference;

	// pasteboard support
QTKIT_EXTERN NSString * const QTMoviePasteboardType							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// notifications                                                                                                    description									parameter			parameter type
QTKIT_EXTERN NSString * const QTMovieEditabilityDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie editability				-					-
QTKIT_EXTERN NSString * const QTMovieEditedNotification						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// edit was done to the movie				-					-
QTKIT_EXTERN NSString * const QTMovieLoadStateDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie load state				-					-
QTKIT_EXTERN NSString * const QTMovieLoopModeDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie looping mode				-					-
QTKIT_EXTERN NSString * const QTMovieMessageStringPostedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// message string							message				NSString
QTKIT_EXTERN NSString * const QTMovieRateDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie rate						rate				NSNumber (float)
QTKIT_EXTERN NSString * const QTMovieSelectionDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in selection start/duration		-					-
QTKIT_EXTERN NSString * const QTMovieSizeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie size						-					-
QTKIT_EXTERN NSString * const QTMovieStatusStringPostedNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// status string							status				NSString
QTKIT_EXTERN NSString * const QTMovieTimeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// goto time occured						-					-
QTKIT_EXTERN NSString * const QTMovieVolumeDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in volume							-					-
QTKIT_EXTERN NSString * const QTMovieDidEndNotification						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// movie ended								-					-
QTKIT_EXTERN NSString * const QTMovieChapterDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in current chapter				-					-
QTKIT_EXTERN NSString * const QTMovieChapterListDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in chapter list					-					-
QTKIT_EXTERN NSString * const QTMovieEnterFullScreenRequestNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// full screen playback requested			-					-
QTKIT_EXTERN NSString * const QTMovieExitFullScreenRequestNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// normal windowed playback requested		-					-
QTKIT_EXTERN NSString * const QTMovieCloseWindowRequestNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// window close requested					-					-
QTKIT_EXTERN NSString * const QTMovieApertureModeDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// change in visual aperture mode			-					-

	// notification parameters
QTKIT_EXTERN NSString * const QTMovieMessageNotificationParameter			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieRateDidChangeNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieStatusFlagsNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieStatusCodeNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieStatusStringNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN NSString * const QTMovieTargetIDNotificationParameter			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieTargetNameNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// writeToFile: attributes dictionary keys
QTKIT_EXTERN NSString * const QTMovieExport									AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieExportType								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMovieFlatten								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieExportSettings							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSData (QTAtomContainer)
QTKIT_EXTERN NSString * const QTMovieExportManufacturer						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)

	// addImage: attributes dictionary keys
QTKIT_EXTERN NSString * const QTAddImageCodecType							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTAddImageCodecQuality						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber

	// data locators for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString * const QTMovieDataReferenceAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// QTDataReference
QTKIT_EXTERN NSString * const QTMoviePasteboardAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSPasteboard
QTKIT_EXTERN NSString * const QTMovieDataAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSData

	// movie instantiation options for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString * const QTMovieFileOffsetAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long long)
QTKIT_EXTERN NSString * const QTMovieResolveDataRefsAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieAskUnresolvedDataRefsAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieOpenAsyncOKAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)

// movie attributes
QTKIT_EXTERN NSString * const QTMovieApertureModeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieActiveSegmentAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
QTKIT_EXTERN NSString * const QTMovieAutoAlternatesAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieCopyrightAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieCreationTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTMovieCurrentSizeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (NSSize)
QTKIT_EXTERN NSString * const QTMovieCurrentTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTime)
QTKIT_EXTERN NSString * const QTMovieDataSizeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long long)
QTKIT_EXTERN NSString * const QTMovieDelegateAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSObject
QTKIT_EXTERN NSString * const QTMovieDisplayNameAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieDontInteractWithUserAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieDurationAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTime)
QTKIT_EXTERN NSString * const QTMovieEditableAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieFileNameAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieHasApertureModeDimensionsAttribute		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieHasAudioAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieHasDurationAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieHasVideoAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsActiveAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsInteractiveAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsLinearAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsSteppableAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieLoadStateAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMovieLoopsAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieLoopsBackAndForthAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieModificationTimeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTMovieMutedAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieNaturalSizeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (NSSize)
QTKIT_EXTERN NSString * const QTMoviePlaysAllFramesAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePlaysSelectionOnlyAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePosterTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTime)
QTKIT_EXTERN NSString * const QTMoviePreferredMutedAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePreferredRateAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMoviePreferredVolumeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMoviePreviewModeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePreviewRangeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTimeRange)
QTKIT_EXTERN NSString * const QTMovieRateAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMovieSelectionAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTimeRange)
QTKIT_EXTERN NSString * const QTMovieTimeScaleAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMovieURLAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSURL
QTKIT_EXTERN NSString * const QTMovieVolumeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMovieRateChangesPreservePitchAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)

	// aperture modes
QTKIT_EXTERN NSString * const QTMovieApertureModeClassic					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieApertureModeClean						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieApertureModeProduction					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieApertureModeEncodedPixels				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

	// movie frame image options for frameImageAtTime:withAttributes:error:
QTKIT_EXTERN NSString * const QTMovieFrameImageSize							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (NSSize)
QTKIT_EXTERN NSString * const QTMovieFrameImageType							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeNSImage					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCGImageRef				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCIImage					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCVPixelBufferRef			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCVOpenGLTextureRef		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageOpenGLContext				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (CGLContextObj)
QTKIT_EXTERN NSString * const QTMovieFrameImagePixelFormat					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (CGLPixelFormatObj)
QTKIT_EXTERN NSString * const QTMovieFrameImageRepresentationsType			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSArray of NSString; strings are, e.g., NSBitmapImageRep
QTKIT_EXTERN NSString * const QTMovieFrameImageDeinterlaceFields			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL) (default = YES)
QTKIT_EXTERN NSString * const QTMovieFrameImageHighQuality					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL) (default = YES)
QTKIT_EXTERN NSString * const QTMovieFrameImageSingleField					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL) (default = YES)

	// exceptions
QTKIT_EXTERN NSString * const QTMovieUneditableException					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// keys for dictionaries in -chapters array
QTKIT_EXTERN NSString * const QTMovieChapterName							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieChapterStartTime						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (QTTime)

	// keys for attributes dictionary in -addChapters
QTKIT_EXTERN NSString * const QTMovieChapterTargetTrackAttribute			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// QTTrack

// constants for movieFileTypes method
typedef enum {
	QTIncludeStillImageTypes			= 1 << 0,
	QTIncludeTranslatableTypes			= 1 << 1,
	QTIncludeAggressiveTypes			= 1 << 2,
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
	QTIncludeDynamicTypes				= 1 << 3,
#endif
	QTIncludeCommonTypes				= 0,
	QTIncludeAllTypes					= 0xffff
} QTMovieFileTypeOptions;

// constants for movieShouldContinueOp delegate method
typedef enum {
#if __LP64__
	QTMovieOperationBeginPhase			= 0,
	QTMovieOperationUpdatePercentPhase  = 1,
	QTMovieOperationEndPhase			= 2
#else
	QTMovieOperationBeginPhase			= movieProgressOpen,
	QTMovieOperationUpdatePercentPhase  = movieProgressUpdatePercent,
	QTMovieOperationEndPhase			= movieProgressClose
#endif
} QTMovieOperationPhase;

// constants for QTMovieLoadStateAttribute
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
enum {
	QTMovieLoadStateError				= -1L,			// an error occurred while loading the movie
	QTMovieLoadStateLoading				= 1000,			// the movie is loading
	QTMovieLoadStateLoaded				= 2000,			// the movie atom has loaded; it's safe to query movie properties
	QTMovieLoadStatePlayable			= 10000,		// the movie has loaded enough media data to begin playing
	QTMovieLoadStatePlaythroughOK		= 20000,		// the movie has loaded enough media data to play through to the end
	QTMovieLoadStateComplete			= 100000L		// the movie has loaded completely
};
typedef NSInteger QTMovieLoadState;
#endif

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
#if __LP64__
	int32_t				_proxy;
	int32_t				_delegateProxy;
#else
	Movie				_movie;
	MovieController		_movieController;
#endif
	id					_dataReference;
	void				*_objectToken;
	void				*_movieControllerObjectToken;
	long				_reserved1;
	long				_reserved2;
	long				_reserved3;
#if !__LP64__
	MovieEditState		_editState;
#endif
	NSUndoManager		*_undoManager;
	NSDictionary		*_undoAttributes;
	id					_delegate;
	BOOL				_disposeWhenDone;
	BOOL				_delegateLinkToURL;
	BOOL				_delegateShouldLoadData;
	BOOL				_delegateGetExternalMovie;
	BOOL				_delegateShouldContinueOp;
	BOOL				_delegateShouldChangeController;
	BOOL				_delegatePostNetworkDiagnosticUI;
	BOOL				_delegateHandleIdleEvent;
	BOOL				_haveSetControllerFromUserData;
	BOOL				_keepInactive;
	BOOL				_newEqualizer;
	BOOL				_draggable;
	long				_reserved4;
	NSDate				*_lastCheckDate;
	NSDictionary		*_pendingAttributes;
	SInt16				_resourceID;
	long				_seed;
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
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
+ (NSArray *)movieTypesWithOptions:(QTMovieFileTypeOptions)types;
#endif

+ (id)movie;
+ (id)movieWithFile:(NSString *)fileName error:(NSError **)errorPtr;
+ (id)movieWithURL:(NSURL *)url error:(NSError **)errorPtr;
+ (id)movieWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;
+ (id)movieWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr;
+ (id)movieWithData:(NSData *)data error:(NSError **)errorPtr;
#if !__LP64__
+ (id)movieWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr;
#endif
+ (id)movieWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
+ (id)movieNamed:(NSString *)name error:(NSError **)errorPtr;

- (id)initWithFile:(NSString *)fileName error:(NSError **)errorPtr;
- (id)initWithURL:(NSURL *)url error:(NSError **)errorPtr;
- (id)initWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;
- (id)initWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr;
- (id)initWithData:(NSData *)data error:(NSError **)errorPtr;
- (id)initWithMovie:(QTMovie *)movie timeRange:(QTTimeRange)range error:(NSError **)errorPtr;
#if !__LP64__
- (id)initWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr;
#endif
- (id)initWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;

- (id)movieWithTimeRange:(QTTimeRange)range error:(NSError **)errorPtr;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (id)initToWritableFile:(NSString *)filename error:(NSError **)errorPtr;
- (id)initToWritableData:(NSMutableData *)data error:(NSError **)errorPtr;
- (id)initToWritableDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;

- (void)invalidate;
#endif

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
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (void *)frameImageAtTime:(QTTime)time withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
#endif

@end

@interface QTMovie (QTMovieFormat)

- (NSData *)movieFormatRepresentation;
- (BOOL)writeToFile:(NSString *)fileName withAttributes:(NSDictionary *)attributes;
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (BOOL)writeToFile:(NSString *)fileName withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
#endif
- (BOOL)canUpdateMovieFile;
- (BOOL)updateMovieFile;

@end

@interface QTMovie (QTMovieTime)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (void)autoplay;
#endif
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

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (QTTrack *)insertSegmentOfTrack:(QTTrack *)track timeRange:(QTTimeRange)range atTime:(QTTime)time;
- (QTTrack *)insertSegmentOfTrack:(QTTrack *)track fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange;
- (void)removeTrack:(QTTrack *)track;
#endif

@end

@interface QTMovie (QTDelegate)

- (id)delegate;
- (void)setDelegate:(id)delegate;

@end

#if !__LP64__
@interface QTMovie (QTPrimitives)

- (Movie)quickTimeMovie;
- (MovieController)quickTimeMovieController;

@end
#endif

@interface QTMovie (QTMovieVisualSupport)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (void)generateApertureModeDimensions;
- (void)removeApertureModeDimensions;
#endif

@end

@interface QTMovie (QTMovieVisualContext)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
#if !__LP64__
- (void)setVisualContext:(QTVisualContextRef)visualContext;
- (QTVisualContextRef)visualContext;
#endif
#endif

@end

@interface QTMovie (QTMovieThreading)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
+ (void)enterQTKitOnThread;
+ (void)enterQTKitOnThreadDisablingThreadSafetyProtection;
+ (void)exitQTKitOnThread;
- (BOOL)attachToCurrentThread;
- (BOOL)detachFromCurrentThread;

- (void)setIdling:(BOOL)state;
- (BOOL)isIdling;
#endif

@end

@interface QTMovie (QTMovieChapters)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (BOOL)hasChapters;
- (NSInteger)chapterCount;
- (NSArray *)chapters;
- (void)addChapters:(NSArray *)chapters withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
- (BOOL)removeChapters;
- (QTTime)startTimeOfChapter:(NSInteger)chapterIndex;		// 0-based index
- (NSInteger)chapterIndexForTime:(QTTime)time;				// 0-based index
#endif

@end

