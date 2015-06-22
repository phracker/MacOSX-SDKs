/*
	File:		QTMovie.h

	Copyright:	(c)2004-2012 by Apple Inc., all rights reserved.

*/
/*!
    @class			QTMovie

    @abstract		A QTMovie object is an object that represents a playable collection of media data.
 
	@discussion		A QTMovie object can be initialized from a file, from a resource specified by a URL, from a block of memory, 
					from a pasteboard, or from an existing QuickTime movie. Once a QTMovie object has been initialized, 
					it will typically be used in combination with a QTMovieView for playback. It can also be used for other purposes,
					such as converting the media data into a different format.
 
					The designated initializer for the QTMovie class is initWithAttributes:error:, whose first parameter is a dictionary
					of attribute keys and their desired values. One of these attributes must specify the location of the media data (for instance,
					using the QTMovieURLAttribute key). Other attributes may specify desired movie-opening behaviors, and others still may
					specify desired initial values of QTMovie properties (for instance, QTMovieVolumeAttribute).
 
					There are two movie-opening behaviors. Specifying QTMovieOpenForPlaybackAttribute with the value YES indicates that 
					the QTMovie object will be used only for playback, in which case QTKit may be able to use more efficient code paths for some media data.
					Specifying QTMovieOpenAsyncRequiredAttribute with the value YES indicates that all operations necessary to open the movie file (or other container)
					and to create a valid QTMovie object must occur asynchronously. In other words, initWithAttributes:error: will return almost immediately, 
					performing any lengthy operations on another thread.
 
					The initializer for a QTMovie object must be called on the main thread. As just indicated, you can use the QTMovieOpenAsyncRequiredAttribute
					to request that any lengthy loading operations be done on a background thread. In that case, you must monitor the movie load state to determine
					when and if the movie has loaded successfully. Some media types cannot successfully be loaded on a background thread and your application should
					be prepared for that possibility. Once a QTMovie object has been successfully loaded, you can migrate it to other threads; see the 
					QTMovie_Threading category below for methods that you can use to do this. 
 
					An exception, QTDisallowedForInitializationPurposeException, is raised whenever the client attempts to call a method that is not allowed
					under a requested movie-opening behavior. For example, if a QTMovie object is initialized with QTMovieOpenForPlaybackAttribute set to YES,
					then QTDisallowedForInitializationPurposeException is raised if the client attempts to call methods that export the media data.
					
					An exception, QTMovieUneditableException, is raised whenever the client attempts to directly or indirectly edit a QTMovie object 
					that is not currently set as editable (for instance, by calling appendSelectionFromMovie: on an uneditable movie).
*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>

#import <Cocoa/Cocoa.h>

#if !__LP64__
#import <QuickTime/QuickTime.h>
#endif

@class QTMovie;
@class QTTrack;
@class QTDataReference;
@class QTMovieMediaHelper;
@class QTInvalidationSet;

	// pasteboard support
QTKIT_EXTERN NSString * const QTMoviePasteboardType							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// notifications                                                                                                    description									parameter			parameter type
QTKIT_EXTERN NSString * const QTMovieEditabilityDidChangeNotification		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in movie editability				-					-
QTKIT_EXTERN NSString * const QTMovieEditedNotification						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // edit was done to the movie				-					-
QTKIT_EXTERN NSString * const QTMovieLoadStateDidChangeNotification			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in movie load state				-					-
QTKIT_EXTERN NSString * const QTMovieLoopModeDidChangeNotification			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in movie looping mode				-					-
QTKIT_EXTERN NSString * const QTMovieMessageStringPostedNotification		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // message string							message				NSString
QTKIT_EXTERN NSString * const QTMovieRateDidChangeNotification				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in movie rate						rate				NSNumber (float)
QTKIT_EXTERN NSString * const QTMovieSelectionDidChangeNotification			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in selection start/duration		-					-
QTKIT_EXTERN NSString * const QTMovieNaturalSizeDidChangeNotification       AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;    // change in movie natural size             -                   -
QTKIT_EXTERN NSString * const QTMovieSizeDidChangeNotification				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3;
QTKIT_EXTERN NSString * const QTMovieStatusStringPostedNotification			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // status string							status				NSString
QTKIT_EXTERN NSString * const QTMovieTimeDidChangeNotification				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // goto time occurred						-					-
QTKIT_EXTERN NSString * const QTMovieVolumeDidChangeNotification			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in volume						-					-
QTKIT_EXTERN NSString * const QTMovieDidEndNotification						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // movie ended							-					-
QTKIT_EXTERN NSString * const QTMovieChapterDidChangeNotification			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in current chapter				-					-
QTKIT_EXTERN NSString * const QTMovieChapterListDidChangeNotification		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in chapter list					-					-
QTKIT_EXTERN NSString * const QTMovieEnterFullScreenRequestNotification		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // full screen playback requested			-					-
QTKIT_EXTERN NSString * const QTMovieExitFullScreenRequestNotification		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // normal windowed playback requested		-					-
QTKIT_EXTERN NSString * const QTMovieCloseWindowRequestNotification			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // window close requested					-					-
QTKIT_EXTERN NSString * const QTMovieApertureModeDidChangeNotification		AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // change in visual aperture mode			-					-

	// notification parameters
QTKIT_EXTERN NSString * const QTMovieMessageNotificationParameter			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieRateDidChangeNotificationParameter		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieStatusFlagsNotificationParameter		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieStatusCodeNotificationParameter		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieStatusStringNotificationParameter		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN NSString * const QTMovieTargetIDNotificationParameter			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieTargetNameNotificationParameter		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// writeToFile: attributes dictionary keys
QTKIT_EXTERN NSString * const QTMovieExport									AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieExportType								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (long)
QTKIT_EXTERN NSString * const QTMovieFlatten								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieExportSettings							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSData (QTAtomContainer)
QTKIT_EXTERN NSString * const QTMovieExportManufacturer						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (long)

	// addImage: attributes dictionary keys
QTKIT_EXTERN NSString * const QTAddImageCodecType							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString
QTKIT_EXTERN NSString * const QTAddImageCodecQuality						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber

	// data locators for movieWithAttributes/initWithAttributes
/*!
	@constant		QTMovieDataReferenceAttribute
	@abstract		The data reference of a QTMovie object; the value for this key is of type QTDataReference.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieDataReferenceAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // QTDataReference
QTKIT_EXTERN NSString * const QTMoviePasteboardAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSPasteboard
QTKIT_EXTERN NSString * const QTMovieDataAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSData

	// movie instantiation options for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString * const QTMovieFileOffsetAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (long long)
QTKIT_EXTERN NSString * const QTMovieDontInteractWithUserAttribute			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieResolveDataRefsAttribute
	@abstract		Indicates whether external data references in a movie file should be resolved (NSNumber YES) or not resolved (NSNumber NO).
	@discussion		A movie file can contain references to media data in other locations. By default, QTMovie attempts to resolve these references
					at the time that the movie file is opened and a QTMovie object is instantiated. You can prevent that resolution from occurring 
					by passing an NSNumber wrapping the value NO as the value of this attribute.
 */
QTKIT_EXTERN NSString * const QTMovieResolveDataRefsAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL) (default = YES)

/*!
	@constant		QTMovieAskUnresolvedDataRefsAttribute
	@abstract		Indicates whether the user should be prompted to help find any unresolved data references (NSNumber YES) or not (NSNumber NO).
	@discussion		When the value of the QTMovieResolveDataRefsAttribute attribute is an NSNumber wrapping the value YES and a movie file contains 
					unresolved data references, this attribute indicates whether the user should be prompted to help find the missing referenced data
					(NSNumber YES) or not (NSNumber NO). Typically QTMovie will display a dialog box that allows the user to navigate to the file or URL
					containing the referenced data. By setting this attribute to NO, you can prevent that dialog box from being displayed and thereby
					speed up the movie opening and initialization process.
 */
QTKIT_EXTERN NSString * const QTMovieAskUnresolvedDataRefsAttribute			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL) (default = YES)

/*!
	@constant		QTMovieOpenAsyncOKAttribute
	@abstract		Indicates whether a movie file can be opened asynchronously if possible (NSNumber YES) or not (NSNumber NO).
	@discussion		Opening a movie file and initializing a QTMovie object for that file may require a considerable amount of time, perhaps to
					convert the data in the file from one format to another. By setting this attribute to an NSNumber wrapping the value YES, you
					grant QTMovie permission to return a non-nil QTMovie identifier to your application immediately and then to continue processing the
					file data internally. If a movie is opened asynchronously, you must monitor the movie load state and ensure that it has reached the
					appropriate threshold before attempting to perform certain operations on the movie. For instance, you cannot export or copy 
					a QTMovie object until its load state has reached QTMovieLoadStateComplete. 
 */
QTKIT_EXTERN NSString * const QTMovieOpenAsyncOKAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL) (default = YES)

/*!
	@constant		QTMovieOpenAsyncRequiredAttribute
	@abstract		Indicates whether the QTMovie must be opened asynchronously (NSNumber YES) or not (NSNumber NO).
	@discussion		Set this attribute to an NSNumber wrapping YES to indicate that all operations necessary to open the movie file (or other container)
					and create a valid QTMovie object must occur asynchronously. That is to say, the methods +movieWithAttributes:error:
					and -initWithAttributes:error: must return almost immediately, performing any lengthy operations on another thread. Your application
					can monitor the movie load state to determine the progress of those operations. 
 */
QTKIT_EXTERN NSString * const QTMovieOpenAsyncRequiredAttribute				AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSNumber (BOOL) (default = NO)

/*!
	@constant		QTMovieOpenForPlaybackAttribute
	@abstract		Indicates whether the QTMovie will be used only for playback (NSNumber YES) or not (NSNumber NO).
	@discussion		Set this attribute to an NSNumber wrapping YES to indicate that you intend to use movie playback methods (such as -play or -stop, 
					or corresponding movie view methods such as -play: or -pause:) to control the movie, but do not intend to use other methods that edit,
					export, or in any way modify the movie. Knowing that you need playback services only may allow QTMovie to use more efficient code paths
					for some media files.
					
					This attribute is meaningful only when added to the dictionary passed to -initWithAttributes:error:. In particular, setting this
					attribute on a QTMovie object that is already open has no effect.
 */
QTKIT_EXTERN NSString * const QTMovieOpenForPlaybackAttribute				AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSNumber (BOOL) (default = NO)

// movie attributes
/*!
	@constant		QTMovieApertureModeAttribute
	@abstract		The aperture mode attribute of a QTMovie object.
					This value is an NSString that indicates the current aperture mode of the QTMovie object.
	@discussion		The values of this key are QTMovieApertureModeClassic, QTMovieApertureModeClean, QTMovieApertureModeProduction, 
					and QTMovieApertureModeEncodedPixels.
					This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieApertureModeAttribute					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString

/*!
	@constant		QTMovieActiveSegmentAttribute
	@abstract		The active segment of a QTMovie object; the value for this key is of type NSValue, interpreted as a QTTimeRange structure.
	@discussion		This constant is available in Mac OS X 10.4 and later, but deprecated in Mac OS X 10.5 and later.
					This attribute can be read and written.
					This attribute cannot be read or written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieActiveSegmentAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_2;

/*!
	@constant		QTMovieAutoAlternatesAttribute
	@abstract		The auto-alternate state of a QTMovie object. The value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieAutoAlternatesAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieCopyrightAttribute
	@abstract		The copyright string of a QTMovie object; the value for this key is of type NSString.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieCopyrightAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString

/*!
	@constant		QTMovieCreationTimeAttribute
	@abstract		The creation time of the container from which a QTMovie object was initialized; the value for this key is of type NSDate.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieCreationTimeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSDate

/*!
	@constant		QTMovieCurrentSizeAttribute
	@abstract		The current size of a QTMovie object; the value for this key is of type NSValue, interpreted as an NSSize structure.
	@discussion		This attribute can be read and written.
					This attribute cannot be read or written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					This attribute is deprecated in QTKit version 7.6 and later.
 */
QTKIT_EXTERN NSString * const QTMovieCurrentSizeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3;

/*!
	@constant		QTMovieCurrentTimeAttribute
	@abstract		The current time of a QTMovie object; the value for this key is of type NSValue, interpreted as a QTTime structure.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieCurrentTimeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (QTTime)

/*!
	@constant		QTMovieDataSizeAttribute
	@abstract		The data size of a QTMovie object. The value for this key is of type NSNumber, which is interpreted as a long long.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieDataSizeAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (long long)

/*!
	@constant		QTMovieDelegateAttribute
	@abstract		The delegate for a QTMovie object. The value for this key is of type NSObject.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieDelegateAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSObject

/*!
	@constant		QTMovieDisplayNameAttribute
	@abstract		The display name of a QTMovie object.
					A display name is stored as user data in a movie file and hence may differ from the base name of the movie’s filename or URL.
					The value for this key is of type NSString.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieDisplayNameAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString

/*!
	@constant		QTMovieDurationAttribute
	@abstract		The duration of a QTMovie object; the value for this key is of type NSValue, interpreted as a QTTime structure.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieDurationAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (QTTime)

/*!
	@constant		QTMovieEditableAttribute
	@abstract		The editable setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie can be edited, NO otherwise.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieEditableAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieFileNameAttribute
	@abstract		The file name string of a QTMovie object; the value for this key is of type NSString.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieFileNameAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString

/*!
	@constant		QTMovieHasApertureModeDimensionsAttribute
	@abstract		The aperture mode dimensions set on any track in this QTMovie object, even if those dimemsions are all identical to the classic dimensions 
					(as is the case for content with square pixels and no edge-processing region). 
					The value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieHasApertureModeDimensionsAttribute		AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieHasAudioAttribute
	@abstract		The audio data setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL. 
					This value is YES if the movie contains audio data, NO otherwise.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieHasAudioAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieHasDurationAttribute
	@abstract		The duration setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie has a duration, NO otherwise. 
					(Some types of movies, for instance QuickTime VR movies, have no duration.)
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieHasDurationAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieHasVideoAttribute
	@abstract		The video data setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie contains video data, NO otherwise.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieHasVideoAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieIsActiveAttribute
	@abstract		The active setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieIsActiveAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieIsInteractiveAttribute
	@abstract		The interactive setting of a QTMovie object.
					The value for this key is of type NSNumber, interpreted as a BOOL. This value is YES if the movie is interactive, NO otherwise.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieIsInteractiveAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieIsLinearAttribute
	@abstract		The linear setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie is linear, as opposed to a non-linear QuickTime VR movie.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieIsLinearAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieIsSteppableAttribute
	@abstract		The steppable setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL. 
					This value is YES if the movie can step from frame to frame, NO otherwise.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieIsSteppableAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieLoadStateAttribute
	@abstract		The load state value of a QTMovie object; the value for this key is of type NSNumber, interpreted as a long.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieLoadStateAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (long)

/*!
	@constant		QTMovieLoadStateErrorAttribute
	@abstract		The load state error of a QTMovie object; the value for this key is of type NSError.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieLoadStateErrorAttribute				AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;    // NSError

/*!
	@constant		QTMovieLoopsAttribute
	@abstract		The looping setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie is set to loop, NO otherwise.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieLoopsAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieLoopsBackAndForthAttribute
	@abstract		The palindrome looping setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie is set to loop back and forth.
	@discussion		Note that QTMovieLoopsAttribute and QTMovieLoopsBackAndForthAttribute are independent and indeed exclusive.
					QTMovieLoopsAttribute is used to get and set the state of normal looping; QTMovieLoopsBackAndForthAttribute is used to get and set
					the state of palindrome looping.
					This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieLoopsBackAndForthAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieModificationTimeAttribute
	@abstract		The modification time of a QTMovie object; the value for this key is of type NSDate.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieModificationTimeAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSDate

/*!
	@constant		QTMovieMutedAttribute
	@abstract		The mute setting of a QTMovie object. The value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie volume is muted, NO otherwise.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieMutedAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMovieNaturalSizeAttribute
	@abstract		The natural size of a QTMovie object; the value for this key is of type NSValue, interpreted as an NSSize structure.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieNaturalSizeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (NSSize)

/*!
	@constant		QTMoviePlaysAllFramesAttribute
	@abstract		The play-all-frames setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie will play all frames, NO otherwise.
	@discussion		This attribute can be read and written.
					This attribute cannot be read or written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePlaysAllFramesAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMoviePlaysSelectionOnlyAttribute
	@abstract		The play-selection setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie will play only the current selection, NO otherwise.
	@discussion		This attribute can be read and written.
					This attribute cannot be read or written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePlaysSelectionOnlyAttribute			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMoviePosterTimeAttribute
	@abstract		The movie poster time of a QTMovie object; the value for this key is of type NSValue, interpreted as a QTTime structure.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePosterTimeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (QTTime)

/*!
	@constant		QTMoviePreferredMutedAttribute
	@abstract		The preferred mute setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie preferred mute setting is muted, NO otherwise.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePreferredMutedAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMoviePreferredRateAttribute
	@abstract		The preferred rate of a QTMovie object; the value for this key is of type NSNumber, interpreted as a float.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePreferredRateAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (float)

/*!
	@constant		QTMoviePreferredVolumeAttribute
	@abstract		The preferred volume of a QTMovie object; the value for this key is of type NSNumber, interpreted as a float.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePreferredVolumeAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (float)

/*!
	@constant		QTMoviePreviewModeAttribute
	@abstract		The preview mode setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
					This value is YES if the movie is in preview mode, NO otherwise.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePreviewModeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

/*!
	@constant		QTMoviePreviewRangeAttribute
	@abstract		The preview range of a QTMovie object; the value for this key is of type NSValue, interpreted as a QTTimeRange structure.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMoviePreviewRangeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (QTTimeRange)

/*!
	@constant		QTMovieRateAttribute
	@abstract		The playback rate of a QTMovie object; the value for this key is of type NSNumber, interpreted as a float
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieRateAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (float)

/*!
	@constant		QTMovieSelectionAttribute
	@abstract		The selection range of a QTMovie object; the value for this key is of type NSValue, interpreted as a QTTimeRange structure.
	@discussion		This attribute can be read and written.
					This attribute cannot be read or written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieSelectionAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (QTTimeRange)

/*!
	@constant		QTMovieTimeScaleAttribute
	@abstract		The time scale of a QTMovie object; the value for this key is of type NSNumber, interpreted as a long.
	@discussion		This attribute can be read and (in Mac OS X 10.5 and later) written; in earlier versions of Mac OS X, this attribute is readable only.
					In general, you should set this attribute only on newly-created movies or on movies that have not been edited.
					Also, you should only increase the time scale value, and you should try to use integer multiples of the existing time scale.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieTimeScaleAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (long)

/*!
	@constant		QTMovieURLAttribute
	@abstract		The URL of a QTMovie object; the value for this key is of type NSURL.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieURLAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSURL

/*!
	@constant		QTMovieVolumeAttribute
	@abstract		The volume of a QTMovie object; the value for this key is of type NSNumber, interpreted as a float.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieVolumeAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (float)

/*!
	@constant		QTMovieRateChangesPreservePitchAttribute
	@abstract		The rate-changes-preserve-pitch setting of a QTMovie object; the value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		When the playback rate is not unity, audio must be resampled in order to play at a new rate.
					The default resampling affects the pitch of the audio (for example, playing at 2x speed raises the pitch by an octave,
					1/2x lowers an octave). If this property is set on the movie, an alternative algorithm is used,
					which alters the speed without changing the pitch.
					Since this is more computationally expensive, this property may be silently ignored on some slow CPUs.
					This attribute can be read but not written; it must be among the initialization attributes to have any effect.
					This attribute can be read but not written when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMovieRateChangesPreservePitchAttribute		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL)

	// aperture modes
QTKIT_EXTERN NSString * const QTMovieApertureModeClassic					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieApertureModeClean						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieApertureModeProduction					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieApertureModeEncodedPixels				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// movie frame image options for frameImageAtTime:withAttributes:error:
QTKIT_EXTERN NSString * const QTMovieFrameImageSize							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (NSSize)
QTKIT_EXTERN NSString * const QTMovieFrameImageType							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeNSImage					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCGImageRef				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCIImage					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCVPixelBufferRef			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCVOpenGLTextureRef		AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTMovieFrameImageOpenGLContext				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (CGLContextObj)
QTKIT_EXTERN NSString * const QTMovieFrameImagePixelFormat					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (CGLPixelFormatObj)
QTKIT_EXTERN NSString * const QTMovieFrameImageRepresentationsType			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSArray of NSString; strings are, e.g., NSBitmapImageRep
QTKIT_EXTERN NSString * const QTMovieFrameImageDeinterlaceFields			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL) (default = YES)
QTKIT_EXTERN NSString * const QTMovieFrameImageHighQuality					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL) (default = YES)
QTKIT_EXTERN NSString * const QTMovieFrameImageSingleField					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber (BOOL) (default = YES)

/*!
 @constant		QTMovieFrameImageSessionMode
 @abstract		Indicates that two or more calls to frameImageAtTime:withAttributes:error: will be made on the same QTMovie object.
 @discussion	By adding this key with the associated value that is an NSNumber wrapping the BOOL YES to the dictionary of
				attributes, an application indicates that it will make more than one call to frameImageAtTime:withAttributes:error: on
				the same QTMovie object. This knowledge permits QTMovie to cache certain objects and data structures used to generate
				a frame image, thereby improving performance. When the caller has obtained all the frame images desired from a
				given QTMovie object, the caller should follow those session calls with a call where this value is NO; this is
				a signal to QTMovie to dispose of that cached data.
 */
QTKIT_EXTERN NSString * const QTMovieFrameImageSessionMode					AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSNumber (BOOL) (default = NO)

	// exceptions
QTKIT_EXTERN NSString * const QTMovieUneditableException					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTDisallowedForInitializationPurposeException					
																			AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// keys for dictionaries in -chapters array
QTKIT_EXTERN NSString * const QTMovieChapterName							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString
QTKIT_EXTERN NSString * const QTMovieChapterStartTime						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue (QTTime)

	// keys for attributes dictionary in -addChapters
QTKIT_EXTERN NSString * const QTMovieChapterTargetTrackAttribute			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // QTTrack

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

@interface NSObject (QTMovie_Delegate)
/*!
	@method			movie:linkToURL:
	@abstract		If implemented by a delegate of a QTMovie object, called to handle the movie controller action mcActionLinkToURL.
	@param			movie
					A QTMovie object.
	@param			url
					An NSURL object.
	@discussion		QTMovie objects can contain requests to open URLs; an application can implement this delegate method to
					override the default URL-opening mechanism in QTKit. In general, most applications will not need to install a delegate
					to handle this.
					This delegate method is not called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A BOOL value; a delegate should return YES if it handled this method, NO otherwise.
*/
	- (BOOL)movie:(QTMovie *)movie linkToURL:(NSURL *)url AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;			// return YES if delegate handled link-to-URL request

/*!
	@method			movieShouldLoadData:
	@abstract		If implemented by a delegate of a QTMovie object, called periodically while the movie is loading its data.
	@param			sender
					The QTMovie object that is loading its data.
	@discussion		This delegate method is deprecated and should not be used in new code.
					This delegate method is not called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A BOOL value; this value is ignored by QTKit.
*/
	- (BOOL)movieShouldLoadData:(id)sender AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieShouldTask:
	@abstract		If implemented by a delegate of a QTMovie object, called before QTKit performs the standard idle processing on a movie.
	@param			movie
					The QTMovie object that is about to perform idle processing.
	@discussion		This delegate method is deprecated and should not be used in new code.
					This delegate method is not called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A BOOL value; a delegate should return YES to cancel the standard movie idle processing, NO otherwise.
*/
	- (BOOL)movieShouldTask:(id)movie AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			externalMovie:
	@abstract		If implemented by a delegate of a QTMovie object, called when an external movie needs to be found
					(usually for a wired action targeted at an external movie).
	@param			dictionary
					An NSDictionary object that contains information about the desired external movie.
					The keys for the dictionary in this delegate method are QTMovieTargetIDNotificationParameter and QTMovieTargetNameNotificationParameter.
					The QTMovieTargetIDNotificationParameter key indicates that the delegate should return a QTMovie object that has the specified movie ID.
					The QTMovieTargetNameNotificationParameter key indicates that the delegate should return a QTMovie object that has the specified movie name.
	@discussion		This delegate method is not called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A QTMovie object.
*/
	- (QTMovie *)externalMovie:(NSDictionary *)dictionary AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movie:shouldContinueOperation:withPhase:atPercent:withAttributes:
	@abstract		If implemented by a delegate of a QTMovie object, called periodically during lengthy operations (such as exporting a movie).
	@param			op
					An NSString object that is a localized description of the operation being performed.
	@param			phase
					A value of type QTMovieOperationPhase that indicates indicates whether the operation is just beginning (QTMovieOperationBeginPhase), 
					ending (QTMovieOperationEndPhase), or is at a certain percentage of completion (QTMovieOperationUpdatePercentPhase).
	@param			percent
					When the phase paramter is QTMovieOperationUpdatePercentPhase, the approximate percentage of the operation completed.
	@param			attributes
					An NSDictionary object that the same dictionary passed to a QTMovie method that caused the lengthy operation 
					(for example, the attributes dictionary passed to writeToFile:withAttributes:error:). This parameter may be nil.
	@discussion		This delegate method is not called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A BOOL value; a delegate should return YES to continue the lengthy operation, NO to cancel it.
*/
	- (BOOL)movie:(QTMovie *)movie shouldContinueOperation:(NSString *)op withPhase:(QTMovieOperationPhase)phase atPercent:(NSNumber *)percent withAttributes:(NSDictionary *)attributes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
@end

@interface QTMovie : NSObject <NSCoding, NSCopying>
{
@private
#if !__LP64__
	Movie					_movie;
#endif
	long					_state;
	QTMovieMediaHelper		*_mediaHelper;
	CFBooleanRef			_initedViaInitWithAttributes;
	QTInvalidationSet		*_children;
	long					_reserved1;
	long					_reserved2;
	long					_reserved3;
	long					_reserved4;
	long					_reserved5;
	long					_reserved6;
	long					_reserved7;
	long					_reserved8;
	long					_reserved9;
	long					_reserved10;
	long					_reserved11;
	long					_reserved12;
	long					_reserved13;
	long					_reserved14;
	long					_reserved15;
}

/*!
	@method			duration
	@abstract		Returns the duration of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A QTTime structure that indicates the duration of the movie.
*/
- (QTTime)duration AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

@interface QTMovie (QTMovie_Initialization)

/*!
	@method			canInitWithPasteboard:
	@abstract		Determines whether the contents of the specified pasteboard can be used to initialize a QTMovie object.
	@param			pasteboard
					An NSPasteboard object.
	@result			YES if a QTMovie object can be initialized from the specified pasteboard, NO otherwise.
*/
+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			canInitWithFile:
	@abstract		Determines whether the contents of the specified file can be used to initialize a QTMovie object.
	@param			fileName
					An NSString object that specifies a full pathname to a file.
	@result			YES if a QTMovie object can be initialized from the specified file, NO otherwise.
*/
+ (BOOL)canInitWithFile:(NSString *)fileName AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			canInitWithURL:
	@abstract		Determines whether the contents of the specified URL can be used to initialize a QTMovie object.
	@param			url
					An NSURL object.
	@result			YES if a QTMovie object can be initialized from the specified URL, NO otherwise.
*/
+ (BOOL)canInitWithURL:(NSURL *)url AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			canInitWithDataReference:
	@abstract		Determines whether the specified data reference can be used to initialize a QTMovie object.
	@param			dataReference
					An QTDataReference object.
	@result			YES if a QTMovie object can be initialized from the specified data reference, NO otherwise.
*/
+ (BOOL)canInitWithDataReference:(QTDataReference *)dataReference AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieFileTypes:
	@abstract		Returns an array of file types that can be used to initialize a QTMovie object.
	@param			types
					A value of type QTMovieFileTypeOptions that indicates the kinds of file types that are to be returned.
					Passing QTIncludeCommonTypes as the types parameter returns an array of all the common file types that QTKit can open in place on the current system.
					This array includes the file types .mov and .mqv, and any files types that can be opened using a movie importer
					that does not need to write data into a new file while performing the import.
					This array excludes any file types for still images and any file types that require an aggressive movie importer
					(for instance, the movie importer for text files).
	@result			An NSArray object that contains NSString objects indicating supported file types.
*/
+ (NSArray *)movieFileTypes:(QTMovieFileTypeOptions)types AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieUnfilteredFileTypes
	@abstract		Returns an array of file types that can be used to initialize a QTMovie object.
	@result			An NSArray object that contains NSString objects indicating supported file types.
*/
+ (NSArray *)movieUnfilteredFileTypes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieUnfilteredPasteboardTypes
	@abstract		Returns an array of pasteboard types that can be used to initialize a QTMovie object.
	@result			An NSArray object that contains NSString objects indicating supported pasteboard types.
*/
+ (NSArray *)movieUnfilteredPasteboardTypes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			movieTypesWithOptions:
	@abstract		Returns an array of UTIs that QTKit can open.
	@param			types
					A value of type QTMovieFileTypeOptions that indicates the kinds of UTIs that are to be returned.
					See the description of +movieFileTypes for more information.
	@result			An NSArray object that contains NSString objects indicating supported file types.
*/
+ (NSArray *)movieTypesWithOptions:(QTMovieFileTypeOptions)types AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

/*!
	@method			movie
	@abstract		Creates an empty QTMovie object.
	@result			An empty QTMovie object. This movie contains no playable data.
*/
+ (id)movie AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieWithFile:error:
	@abstract		Creates a QTMovie object initialized with the data in a specified file.
	@param			fileName
					An NSString object that specifies a full pathname to a file.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			An autoreleased QTMovie object.
*/
+ (id)movieWithFile:(NSString *)fileName error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieWithURL:error:
	@abstract		Creates a QTMovie object initialized with the contents of the specified URL.
	@param			url
					An NSURL object.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			An autoreleased QTMovie object.
*/
+ (id)movieWithURL:(NSURL *)url error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieWithDataReference:error:
	@abstract		Creates a QTMovie object initialized with data specified by a data reference.
	@param			dataReference
					A QTDataReference object that specifies data from which a QTMovie object can be initialized.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			An autoreleased QTMovie object.
*/
+ (id)movieWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieWithPasteboard:error:
	@abstract		Creates a QTMovie object initialized with the contents of the specified pasteboard.
	@param			pasteboard
					An NSPasteboard object that contains data from which a QTMovie object can be initialized.
					The contents of the pasteboard can be a QuickTime movie (of type Movie), a file path, or data of type QTMoviePasteboardType.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			An autoreleased QTMovie object.
*/
+ (id)movieWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieWithData:error:
	@abstract		Creates a QTMovie object initialized with data specified by an NSData object.
	@param			data
					An NSData object that contains data from which a QTMovie object can be initialized.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			An autoreleased QTMovie object.
*/
+ (id)movieWithData:(NSData *)data error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if !__LP64__
/*!
	@method			movieWithQuickTimeMovie:disposeWhenDone:error:
	@abstract		Creates a QTMovie object initialized from an existing QuickTime movie.
	@discussion		This method cannot be called by 64-bit applications.
	@param			movie
					A QuickTime movie (of type Movie).
	@param			dispose
					A BOOL value that indicates whether QTKit should call DisposeMovie on the specified QuickTime movie
					when the QTMovie object is deallocated. Passing YES effectively transfers ownership of the Movie to QTKit.
					Most applications will probably want to pass YES; passing NO means that the application wants to call DisposeMovie itself,
					perhaps so that it can operate on a Movie after it has been disassociated from a QTMovie object.
					Clients that pass NO for the dispose parameter must invalidate the QTMovie object (by calling -[QTMovie invalidate])
					before calling DisposeMovie on the specified QuickTime movie. Failure to do this may result in a crash.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			An autoreleased QTMovie object.
*/
+ (id)movieWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

/*!
	@method			movieWithAttributes:error:
	@abstract		Creates a QTMovie object initialized with a specified set of attributes.
	@param			attributes
					An NSDictionary object whose key-value pairs specify the attributes to use when initializing the movie.
					There are three types of attributes that can be included in this dictionary: (1) attributes that specify the location
					of the movie data (for instance, QTMovieFileNameAttribute); (2) attributes that specify how the movie is to be instantiated
					(for instance, QTMovieOpenForPlaybackAttribute); (3) attributes that specify playback characteristics of the movie
					or other properties of the QTMovie object (for instance, QTMovieVolumeAttribute).
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			An autoreleased QTMovie object.
*/
+ (id)movieWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieNamed:error:
	@abstract		Creates a QTMovie object initialized with the data from the movie having the specified name in the application’s bundle.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
+ (id)movieNamed:(NSString *)name error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initWithFile:error:
	@abstract		Creates a QTMovie object initialized with the data in a specified file.
	@param			fileName
					An NSString object that specifies a full pathname to a file.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithFile:(NSString *)fileName error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initWithURL:error:
	@abstract		Creates a QTMovie object initialized with the contents of the specified URL.
	@param			url
					An NSURL object.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithURL:(NSURL *)url error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initWithDataReference:error:
	@abstract		Creates a QTMovie object initialized with data specified by a data reference.
	@param			dataReference
					A QTDataReference object that specifies data from which a QTMovie object can be initialized.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initWithPasteboard:error:
	@abstract		Creates a QTMovie object initialized with the contents of the specified pasteboard.
	@param			pasteboard
					An NSPasteboard object that contains data from which a QTMovie object can be initialized.
					The contents of the pasteboard can be a QuickTime movie (of type Movie), a file path, or data of type QTMoviePasteboardType.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initWithData:error:
	@abstract		Creates a QTMovie object initialized with data specified by an NSData object.
	@param			data
					An NSData object that contains data from which a QTMovie object can be initialized.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithData:(NSData *)data error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initWithMovie:timeRange:error:
	@abstract		Creates a QTMovie object initialized with some or all of the data from an existing QTMovie object.
	@discussion		This method cannot be called when the QTMovie object specified by the movie parameter has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			movie
					A QTMovie object.
	@param			range
					A QTTimeRange structure that delimits the segment of data from the movie parameter to be used to initialize the receiver.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithMovie:(QTMovie *)movie timeRange:(QTTimeRange)range error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if !__LP64__
/*!
	@method			initWithQuickTimeMovie:disposeWhenDone:error:
	@abstract		Creates a QTMovie object initialized from an existing QuickTime movie.
	@discussion		This method cannot be called by 64-bit applications.
	@param			movie
					A QuickTime movie (of type Movie).
	@param			dispose
					A BOOL value that indicates whether QTKit should call DisposeMovie on the specified QuickTime movie
					when the QTMovie object is deallocated. Passing YES effectively transfers ownership of the Movie to QTKit.
					Most applications will probably want to pass YES; passing NO means that the application wants to call DisposeMovie itself,
					perhaps so that it can operate on a Movie after it has been disassociated from a QTMovie object.
					Clients that pass NO for the dispose parameter must invalidate the QTMovie object (by calling -[QTMovie invalidate])
					before calling DisposeMovie on the specified QuickTime movie. Failure to do this may result in a crash.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

/*!
	@method			initWithAttributes:error:
	@abstract		Creates a QTMovie object initialized with a specified set of attributes.
	@param			attributes
					An NSDictionary object whose key-value pairs specify the attributes to use when initializing the movie.
					There are three types of attributes that can be included in this dictionary: (1) attributes that specify the location
					of the movie data (for instance, QTMovieFileNameAttribute); (2) attributes that specify how the movie is to be instantiated
					(for instance, QTMovieOpenForPlaybackAttribute); (3) attributes that specify playback characteristics of the movie
					or other properties of the QTMovie object (for instance, QTMovieVolumeAttribute).
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)initWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			movieWithTimeRange:error:
	@abstract		Returns a QTMovie object initialized with the data in the specified time range of an existing QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			range
					A QTTimeRange structure that indicates the segment in the movie to use to initialize a QTMovie object.
	@param			errorPtr
					A pointer to an NSError object; if a movie cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object.
*/
- (id)movieWithTimeRange:(QTTimeRange)range error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			initToWritableFile:error:
	@abstract		Creates an empty, writable storage container at the location specified by the data reference and returns an editable QTMovie object associated with that container.
	@discussion		Movie data can be added to the QTMovie object returned by this method (for example, using the addImage:forDuration:withAttributes: method).
	@param			filename
					An NSString object that specifies a full pathname to a file.
	@param			errorPtr
					A pointer to an NSError object; if the storage container or the QTMovie object cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object. This object is editable.
*/
- (id)initToWritableFile:(NSString *)filename error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initToWritableData:error:
	@abstract		Creates an empty, writable storage container in memory and returns an editable QTMovie object associated with that container.
	@discussion		Movie data can be added to the QTMovie object returned by this method (for example, using the addImage:forDuration:withAttributes: method).
	@param			data
					An NSMutableData object.
	@param			errorPtr
					A pointer to an NSError object; if the storage container or the QTMovie object cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object. This object is editable.
*/
- (id)initToWritableData:(NSMutableData *)data error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initToWritableDataReference:error:
	@abstract		Creates an empty, writable storage container at the location specified by the data reference and returns an editable QTMovie object associated with that container.
	@discussion		Movie data can be added to the QTMovie object returned by this method (for example, using the addImage:forDuration:withAttributes: method).
	@param			dataReference
					A QTDataReference object.
	@param			errorPtr
					A pointer to an NSError object; if the storage container or the QTMovie object cannot be created, an NSError object is returned in this location.
	@result			A QTMovie object. This object is editable.
*/
- (id)initToWritableDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			invalidate
	@abstract		Invalidates a QTMovie object immediately.
	@discussion		By the time this method has returned, the receiver will have detached itself from any resources it is using, 
					disposing of these resources when appropriate.
					Attempting to make any non-trivial use of the receiver after invalidating it will result in undefined behavior.
					This method does not release the receiver, so under retain/release memory management
					release must still be called on the receiver for it to be fully deallocated.
					Because this method defeats sharing of QTMovie objects,
					it should only be called when it is known that the object is no longer needed.
					This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)invalidate AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

@end

@interface QTMovie (QTMovie_Inspection)

	// attributes
/*!
	@method			movieAttributes
	@abstract		Returns a dictionary containing the current values of all public attributes of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (NSDictionary *)movieAttributes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setMovieAttributes:
	@abstract		Sets the attributes of a QTMovie object using the key-value pairs in a specified dictionary.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					However, certain attributes may not be writable when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			attributes
					An NSDictionary object that specifies the attributes to set and their desired values.
*/
- (void)setMovieAttributes:(NSDictionary *)attributes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			attributeForKey:
	@abstract		Returns the current value of an attribute of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			attributeKey
					An NSString object that specifies the attribute to be read; pass strings like QTMovieTimeScaleAttribute or QTMovieVolumeAttribute.
	@result			An NSObject that is the value of the specified attribute key.
*/
- (id)attributeForKey:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setAttribute:forKey:
	@abstract		Sets an attribute of a QTMovie object to a specified value.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					However, certain attributes may not be writable when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			value
					An object that specifies the value of the attribute to be written.
	@param			attributeKey
					An NSString object that specifies the attribute to be written; pass strings like QTMovieTimeScaleAttribute or QTMovieVolumeAttribute.
*/
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			tracks
	@abstract		Returns an array of QTTrack objects representing the tracks in a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (NSArray *)tracks AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			tracksOfMediaType:
	@abstract		Returns an array of QTTrack objects representing the tracks in a QTMovie object of a specified media type.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			type
					An NSString object that specifies a media type; pass strings like QTMediaTypeVideo or QTMediaTypeText.
*/
- (NSArray *)tracksOfMediaType:(NSString *)type AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

@interface QTMovie (QTMovie_Image)

/*!
	@method			posterImage
	@abstract		Returns an NSImage that is the poster image of a QTMovie object.
	@discussion		This method may return nil when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			An NSImage object representing the movie poster image. If the movie has no visual data at the poster image time,
					nil is returned.
*/
- (NSImage *)posterImage AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			currentFrameImage
	@abstract		Returns an NSImage object for the frame at the current time in a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			An NSImage object representing the frame image at the current time. If the movie has no visual data at the
					current time, nil is returned.
*/
- (NSImage *)currentFrameImage AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			frameImageAtTime:
	@abstract		Returns an NSImage that is the frame image at a specified time in a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			time
					A QTTime structure that specifies the time at which a frame image is to returned.
	@result			An NSImage object representing the frame image at the specified time. If the movie has no visual data at the
					specified time, nil is returned.
*/
- (NSImage *)frameImageAtTime:(QTTime)time AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			frameImageAtTime:withAttributes:error:
	@abstract		Returns the frame image at a specified time in a QTMovie object.
	@param			time
					A QTTime structure that specifies the time at which a frame image is to returned.
	@param			attributes
					An NSDictionary object that specifies the desired attributes of the returned frame image.
	@param			errorPtr
					A pointer to an NSError object; if a frame image cannot be created, an NSError object is returned in this location.
	@result			An NSImage object, a CIImage object, a CGImageRef reference, a CVPixelBufferRef reference, or a  CVOpenGLTextureRef reference 
					for the movie image at the specified time. If the movie has no visual data at the specified time, nil is returned.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					All images returned by this method are autoreleased objects and must be retained by the caller if they are to be accessed outside
					of the current run loop cycle. However, applications running under garbage collection must call CVPixelBufferRelease on any
					CVPixelBufferRef returned by this method.
*/
- (void *)frameImageAtTime:(QTTime)time withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

@end

@interface QTMovie (QTMovie_Format)

/*!
	@method			movieFormatRepresentation
	@abstract		Returns the movie atom data of a QTMovie object in an NSData object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			An NSData object that contains the movie atom data of a movie.
*/
- (NSData *)movieFormatRepresentation AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
 
/*!
	@method			writeToFile:withAttributes:
	@abstract		Exports or flattens a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			fileName
					An NSString object that specifies a full pathname to a file.
	@param			attributes
					An NSDictionary object that specifies the desired operation and its options. If the dictionary attributes contains an object
					whose key is QTMovieFlatten, then the movie is flattened into the specified file. If the dictionary attributes contains an object
					whose key is QTMovieExport, then the movie is exported into the specified file using a movie exporter whose type is specified by
					the value of the key QTMovieExportType. The value associated with the QTMovieExportSettings key should be an object of type NSData
					that contains an atom container of movie export settings.
	@result			YES if the movie file was successfully created, NO otherwise. NO will also be returned if the load state of the target movie
					is less than QTMovieLoadStateComplete, in which case no attempt is made to write the QTMovie into a file.
*/
- (BOOL)writeToFile:(NSString *)fileName withAttributes:(NSDictionary *)attributes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			writeToFile:withAttributes:error:
	@abstract		Exports or flattens a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			fileName
					An NSString object that specifies a full pathname to a file.
	@param			attributes
					An NSDictionary object that specifies the desired operation and its options. If the dictionary attributes contains an object
					whose key is QTMovieFlatten, then the movie is flattened into the specified file. If the dictionary attributes contains an object
					whose key is QTMovieExport, then the movie is exported into the specified file using a movie exporter whose type is specified by
					the value of the key QTMovieExportType. The value associated with the QTMovieExportSettings key should be an object of type NSData
					that contains an atom container of movie export settings.
	@param			errorPtr
					A pointer to an NSError object; if the operation fails, an NSError object is returned in this location.
	@result			YES if the movie file was successfully created, NO otherwise. NO will also be returned if the load state of the target movie
					is less than QTMovieLoadStateComplete, in which case no attempt is made to write the QTMovie into a file.
*/
- (BOOL)writeToFile:(NSString *)fileName withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

/*!
	@method			canUpdateMovieFile
	@abstract		Indicates whether a movie file can be updated with changes made to a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			YES if the movie file can be updated, NO otherwise.
*/
- (BOOL)canUpdateMovieFile AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			updateMovieFile
	@abstract		Updates the movie file of a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			YES if the update succeeds, NO otherwise.
*/
- (BOOL)updateMovieFile AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

@interface QTMovie (QTMovie_Time)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			autoplay
	@abstract		Sets a QTMovie object to start playing when a sufficient amount of media data is available.
	@discussion		The autoplay method configures a QTMovie object to begin playing as soon as enough data is available that
					the playback can likely continue uninterrupted to the end of the movie. This is most useful for movies being loaded from a remote URL
					or from an extremely slow local device. For movies stored on most local devices, this method has the same effect as the -play method.
					This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)autoplay AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3;
#endif

/*!
	@method			play
	@abstract		Starts a QTMovie object playing.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)play AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			stop
	@abstract		Stops a QTMovie object playing.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)stop AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			currentTime
	@abstract		Returns the current time of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (QTTime)currentTime AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setCurrentTime:
	@abstract		Sets the current time of a QTMovie object to a specified time.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			time
					A QTTime structure that specifies the time to be made the current movie time.
*/
- (void)setCurrentTime:(QTTime)time AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			gotoBeginning
	@abstract		Sets the current time of a QTMovie object to the beginning of the movie.
	@discussion		If the movie is playing, the movie continues playing at the new time.
					This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)gotoBeginning AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			gotoEnd
	@abstract		Sets the current time of a QTMovie object to the end of the movie.
	@discussion		If the movie is playing in one of the looping modes, the movie continues playing accordingly; otherwise, it stops.
					This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)gotoEnd AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			gotoNextSelectionPoint
	@abstract		Sets the current time of a QTMovie object to the next selection point.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)gotoNextSelectionPoint AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			gotoPreviousSelectionPoint
	@abstract		Sets the current time of a QTMovie object to the previous selection point.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)gotoPreviousSelectionPoint AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			gotoPosterTime
	@abstract		Sets the current time of a QTMovie object to the movie poster time.
	@discussion		If no movie poster time is defined, the current time is set to the beginning of the movie. If the movie is playing,
					the movie continues playing at the new time.
					This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)gotoPosterTime AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			stepForward
	@abstract		Steps a QTMovie object forward one frame.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)stepForward AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			stepBackward
	@abstract		Steps a QTMovie object backward one frame.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)stepBackward AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

@interface QTMovie (QTMovie_PlaybackControl)

/*!
	@method			rate
	@abstract		Returns the current playback rate of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A float value that is the current playback rate.
*/
- (float)rate AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setRate:
	@abstract		Sets the playback rate of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			rate
					A float value that specifies the desired movie playback rate.
*/
- (void)setRate:(float)rate AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			volume
	@abstract		Returns the current volume of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (float)volume AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setVolume:
	@abstract		Sets the volume of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			volume
					A float value that specifies the desired movie volume.
*/
- (void)setVolume:(float)volume AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			muted
	@abstract		Returns the current muted state of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			YES if the movie is currently muted, NO otherwise.
*/
- (BOOL)muted AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setMuted:
	@abstract		Sets the muted state of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			mute
					A BOOL value that indicates the desired muted state of the movie.
*/
- (void)setMuted:(BOOL)mute AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

@interface QTMovie (QTMovie_Selection)

/*!
	@method			setSelection:
	@abstract		Sets the selection of a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			selection
					A QTTimeRange structure that indicates the desired movie selection.
*/
- (void)setSelection:(QTTimeRange)selection AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			selectionStart
	@abstract		Returns the start time of the current selection of a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A QTTime structure that indicates the start time of the current selection of a movie.
*/
- (QTTime)selectionStart AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			selectionEnd
	@abstract		Returns the end time of the current selection of a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A QTTime structure that indicates the end time of the current selection of a movie.
*/
- (QTTime)selectionEnd AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			selectionDuration
	@abstract		Returns the duration of the current selection of a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			A QTTime structure that indicates the duration of the current selection of a movie.
*/
- (QTTime)selectionDuration AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

@interface QTMovie (QTMovie_Editing)

/*!
	@method			replaceSelectionWithSelectionFromMovie:
	@abstract		Replaces the current selection in a QTMovie object with the current selection in a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			movie
					A QTMovie object. (This may be the same object as the receiver.)
*/
- (void)replaceSelectionWithSelectionFromMovie:(id)movie AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			appendSelectionFromMovie:
	@abstract		Appends to a QTMovie object the currently selected segment in a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			movie
					A QTMovie object. (This may be the same object as the receiver.)
*/
- (void)appendSelectionFromMovie:(id)movie AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			insertSegmentOfMovie:timeRange:atTime:
	@abstract		Inserts into a QTMovie object the specified selection of a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			movie
					The QTMovie object from which the segment to be inserted is copied.
	@param			range
					A QTTimeRange structure that indicates the segment in movie to be copied.
	@param			time
					A QTTime structure that indicates the time in the target movie at which the copied segment is to be inserted.
*/
- (void)insertSegmentOfMovie:(QTMovie *)movie timeRange:(QTTimeRange)range atTime:(QTTime)time AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			insertSegmentOfMovie:fromRange:scaledToRange:
	@abstract		Inserts into a QTMovie object the specified segment of another QTMovie object, scaling that new segment to a specified start time and duration.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			movie
					The QTMovie object from which the segment to be inserted is copied.
	@param			srcRange
					A QTTimeRange structure that indicates the segment in movie to be copied.
	@param			dstRange
					A QTTimeRange structure that indicates the range in the target movie into which the copied segment is to be inserted.
*/
- (void)insertSegmentOfMovie:(QTMovie *)movie fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			insertEmptySegmentAt:
	@abstract		Inserts an empty segment into a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			range
					A QTTimeRange structure that indicates the range in the movie at which an empty segment is to be inserted.
*/
- (void)insertEmptySegmentAt:(QTTimeRange)range AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			deleteSegment:
	@abstract		Deletes a specified segment from a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			segment
					A QTTimeRange structure that indicates the segment in the movie to be deleted.
*/
- (void)deleteSegment:(QTTimeRange)segment AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			scaleSegment:newDuration:
	@abstract		Scales a segment of a QTMovie object to a new duration.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			segment
					A QTTimeRange structure that indicates the segment in the movie to be scaled.
	@param			newDuration
					A QTTime structure that indicates the desired duration of the segment that is to be scaled.
*/
- (void)scaleSegment:(QTTimeRange)segment newDuration:(QTTime)newDuration AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			addImage:forDuration:withAttributes:
	@abstract		Adds an image to a QTMovie object for the specified duration, using attributes specified in the attributes dictionary.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			image
					An NSImage that is to be appended to the target movie.
	@param			duration
					A QTTime structure that indicates the desired duration of the appended image in the movie.
	@param			attributes
					An NSDictionary object that specifies attributes of the appended image.
					Keys in this dictionary can be QTAddImageCodecType to select a codec type and QTAddImageCodecQuality to select a quality.
					Qualities are expected to be specified as NSNumbers, using the codec values like codecNormalQuality.
					The attributes dictionary can also contain a value for the QTTrackTimeScaleAttribute key,
					which is used as the time scale of the new track, should one need to be created.
					The default time scale for a new track is 600.
*/
- (void)addImage:(NSImage *)image forDuration:(QTTime)duration withAttributes:(NSDictionary *)attributes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			insertSegmentOfTrack:timeRange:atTime:
	@abstract		Inserts into a QTMovie object the specified segment of a QTTrack object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
					This method is deprecated and should not be used in new code.
	@param			track
					The QTTrack object from which the segment to be inserted is copied.
	@param			range
					A QTTimeRange structure that indicates the segment in track to be copied.
	@param			time
					A QTTime structure that indicates the time in the target movie at which the copied segment is to be inserted.
	@result			The QTTrack object into which the copied segment is inserted.
*/
- (QTTrack *)insertSegmentOfTrack:(QTTrack *)track timeRange:(QTTimeRange)range atTime:(QTTime)time AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3;

/*!
	@method			insertSegmentOfTrack:fromRange:scaledToRange:
	@abstract		Inserts into a QTMovie object the specified segment of a QTTrack object, scaling that new segment to a specified start time and duration.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
					This method is deprecated and should not be used in new code.
	@param			track
					The QTTrack object from which the segment to be inserted is copied.
	@param			srcRange
					A QTTimeRange structure that indicates the segment in track to be copied.
	@param			dstRange
					A QTTimeRange structure that indicates the range in the target movie at which the copied segment is to be inserted.
	@result			The QTTrack object into which the copied segment is inserted.
*/
- (QTTrack *)insertSegmentOfTrack:(QTTrack *)track fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3;

/*!
	@method			removeTrack:
	@abstract		Removes a track from a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			track
					The QTTrack object to be removed.
*/
- (void)removeTrack:(QTTrack *)track AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3;
#endif

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_7
/*!
	@method			trackByInsertingSegmentOfTrack:timeRange:atTime:
	@abstract		Inserts into a QTMovie object the specified segment of a QTTrack object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			track
					The QTTrack object from which the segment to be inserted is copied.
	@param			range
					A QTTimeRange structure that indicates the segment in track to be copied.
	@param			time
					A QTTime structure that indicates the time in the target movie at which the copied segment is to be inserted.
	@result			The QTTrack object into which the copied segment is inserted; this is an autoreleased object.
*/
- (QTTrack *)trackByInsertingSegmentOfTrack:(QTTrack *)track timeRange:(QTTimeRange)range atTime:(QTTime)time AVAILABLE_QTKIT_VERSION_7_7_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			trackByInsertingSegmentOfTrack:fromRange:scaledToRange:
	@abstract		Inserts into a QTMovie object the specified segment of a QTTrack object, scaling that new segment to a specified start time and duration.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			track
					The QTTrack object from which the segment to be inserted is copied.
	@param			srcRange
					A QTTimeRange structure that indicates the segment in track to be copied.
	@param			dstRange
					A QTTimeRange structure that indicates the range in the target movie at which the copied segment is to be inserted.
	@result			The QTTrack object into which the copied segment is inserted; this is an autoreleased object.
*/
- (QTTrack *)trackByInsertingSegmentOfTrack:(QTTrack *)track fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange AVAILABLE_QTKIT_VERSION_7_7_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

@end

@interface QTMovie (QTMovie_Delegate)

/*!
	@method			delegate
	@abstract		Returns the delegate of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (id)delegate AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setDelegate:
	@abstract		Sets the delegate of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			delegate
					An object that is to serve as the delegate for the movie.
*/
- (void)setDelegate:(id)delegate AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

#if !__LP64__
@interface QTMovie (QTMovie_Primitives)

/*!
	@method			quickTimeMovie
	@abstract		Returns the QuickTime Movie associated with a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					This method cannot be called by 64-bit applications.
	@result			A QuickTime Movie.
*/
- (Movie)quickTimeMovie AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			quickTimeMovieController
	@abstract		Returns the QuickTime movie controller associated with a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					This method cannot be called by 64-bit applications.
	@result			A QuickTime MovieController.
*/
- (MovieController)quickTimeMovieController AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end
#endif

@interface QTMovie (QTMovie_VisualSupport)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2

/*!
	@method			generateApertureModeDimensions
	@abstract		Adds aperture mode dimensions information to a QTMovie object.
	@discussion		This method adds information to a QTMovie object needed to support aperture modes for movies created with
					applications and/or versions of QuickTime that did not support aperture mode dimensions.
					If the image descriptions in video tracks lack tags describing clean aperture and pixel aspect ratio information,
					the media data is scanned to see if the correct values can be divined and attached. Then the aperture mode dimensions
					are calculated and set. Afterwards, the QTTrackHasApertureModeDimensionsAttribute property will be set to YES for those tracks.
					Tracks that do not support aperture modes are not changed.
					This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)generateApertureModeDimensions AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			removeApertureModeDimensions
	@abstract		Removes aperture mode dimensions information from a QTMovie object.
	@discussion		This method does not attempt to modify sample descriptions, so it may not completely reverse the effects of generateApertureModeDimensions.
					It sets the QTMovieHasApertureModeDimensionsAttribute property to NO.
					This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)removeApertureModeDimensions AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

@end

@interface QTMovie (QTMovie_VisualContext)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
#if !__LP64__
/*!
	@method			setVisualContext:
	@abstract		Sets the visual context of a QTMovie object to a specified visual context.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					This method cannot be called by 64-bit applications.
	@param			visualContext
					A visual context.
*/
- (void)setVisualContext:(QTVisualContextRef)visualContext AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			visualContext
	@abstract		Returns the current visual context of a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					This method cannot be called by 64-bit applications.
*/
- (QTVisualContextRef)visualContext AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif
#endif

@end

@interface QTMovie (QTMovie_Threading)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			enterQTKitOnThread
	@abstract		Performs any QTKit-specific initialization for the current (non-main) thread.
	@discussion		A call to this method must be paired with a subsequent call to exitQTKitOnThread.
*/
+ (void)enterQTKitOnThread AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			enterQTKitOnThreadDisablingThreadSafetyProtection
	@abstract		Performs any QTKit-specific initialization for the current (non-main) thread, allowing non-threadsafe components.
	@discussion		A call to this method must be paired with a subsequent call to exitQTKitOnThread.
*/
+ (void)enterQTKitOnThreadDisablingThreadSafetyProtection AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			exitQTKitOnThread
	@abstract		Performs any QTKit-specific shut-down for the current (non-main) thread.
	@discussion		A call to this method must be paired with a previous call to enterQTKitOnThread or enterQTKitOnThreadDisablingThreadSafetyProtection.
*/
+ (void)exitQTKitOnThread AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			attachToCurrentThread
	@abstract		Attaches a QTMovie object to the current thread.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			YES if successful, NO otherwise.
*/
- (BOOL)attachToCurrentThread AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			detachFromCurrentThread
	@abstract		Detaches a QTMovie object from the current thread.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			YES if successful, NO otherwise.
*/
- (BOOL)detachFromCurrentThread AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setIdling:
	@abstract		Sets the idling state of a QTMovie object.
	@discussion		Movies attached to background threads should not be idled; if they are idled, unexpected behavior can result.
					This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			state
					A BOOL value that indicates whether to idle the movie (YES) or not (NO).
*/
- (void)setIdling:(BOOL)state AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			isIdling
	@abstract		Returns the current idling state of a QTMovie object.
	@discussion		This method returns the idling state of a QTMovie object (that is, whether it is being tasked).
					Movies attached to background threads should not be idled; if they are idled, unexpected behavior can result.
					This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			YES if the movie is idling, NO otherwise.
*/
- (BOOL)isIdling AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

@end

@interface QTMovie (QTMovie_Chapters)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			hasChapters
	@abstract		Returns a BOOL value that indicates whether a QTMovie object has chapters.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			YES if the movie has chapters, NO otherwise.
*/
- (BOOL)hasChapters AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			chapterCount
	@abstract		Returns the number of chapters in a QTMovie object, or 0 if there are no chapters.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@result			The number of chapters in a movie, or 0 if there are no chapters.
*/
- (NSInteger)chapterCount AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			chapters
	@abstract		Returns an NSArray object containing information about the chapters in a QTMovie object.
	@discussion		Each array element is an NSDictionary object containing key-value pairs. Currently two keys are defined for this dictionary:
					QTMovieChapterName and QTMovieChapterStartTime. The value for the QTMovieChapterName key is an NSString object that is the chapter name.
					The value for the QTMovieChapterStartTime key is an NSValue object that wraps a QTTime structure that indicates the start time of the chapter.
					This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (NSArray *)chapters AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			addChapters:withAttributes:error:
	@abstract		Adds chapters to a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@param			chapters
					An NSArray object whose elements are NSDictionary objects. Currently two keys are defined for this dictionary:
					QTMovieChapterName and QTMovieChapterStartTime. The value for the QTMovieChapterName key is an NSString object that is the chapter name.
					The value for the QTMovieChapterStartTime key is an NSValue object that wraps a QTTime structure that indicates the start time of the chapter. 
	@param			attributes
					An NSDictionary object that contains additional attributes for the chapters. Currently only one key is recognized for this dictionary:
					QTMovieChapterTargetTrackAttribute, which specifies the QTTrack object in the QTMovie object that is the target of the chapters;
					if none is specified, this method uses first video track in movie. If no video track is in the movie,
					this method uses the first audio track in the movie. If no audio track is in the movie, this method uses the first track in the movie. 
	@param			errorPtr
					A pointer to an NSError object; if chapters cannot be added to the movie, an NSError object is returned in this location.
*/
- (void)addChapters:(NSArray *)chapters withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			removeChapters
	@abstract		Removes any existing chapters from a QTMovie object.
	@discussion		This method cannot be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie is not editable, an exception will be raised.
	@result			YES if either the QTMovie object has no chapters or the chapters were successfully removed from it; NO if the chapters could not be removed from the receiver.
*/
- (BOOL)removeChapters AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			startTimeOfChapter:
	@abstract		Returns the start time of the chapter having the specified 0-based index in the list of chapters.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			chapterIndex
					A 0-based index.
	@result			A QTTime structure that indicates the start time of the chapter having the specified 0-based index in the list of chapters.
*/
- (QTTime)startTimeOfChapter:(NSInteger)chapterIndex AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;		// 0-based index

/*!
	@method			chapterIndexForTime:
	@abstract		Returns the 0-based index of the chapter that contains the specified time in a QTMovie object.
	@discussion		This method can be called when the movie has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			time
					A QTTime structure that indicates the time in the movie at which to find the current chapter.
*/
- (NSInteger)chapterIndexForTime:(QTTime)time AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;				// 0-based index

#endif

@end

@interface QTMovie (QTMovie_MetadataReading)

#if (defined(MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7))
/*!
	@method			commonMetadata
	@abstract		Returns an NSArray containing QTMetadataItem objects for each common metadata key for which a value for the current locale is available.
	@result			An NSArray containing QTMetadataItem objects for each common metadata key for which a value for the current locale is available; may be nil if there is no metadata that's appropriately localized.
	@discussion		The returned metadata may be tagged with default locale information or with no locale information, if that's the best available choice.
*/
- (NSArray *)commonMetadata AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method			availableMetadataFormats
	@abstract		Returns an NSArray containing NSString objects representing the metadata formats available to the receiver.
	@result			An NSArray containing an NSString objects, each of which represents a metadata format that is available to the receiver.
*/
- (NSArray *)availableMetadataFormats AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method			metadataForFormat:
	@abstract		Returns an NSArray of QTMetadataItem objects having a specified format.
	@param			format
					The metadata format for which items are requested.
	@result			An NSArray containing all QTMetadataItem objects of the receiver that have the specified format; may be nil if there is no metadata of the specified format.
*/
- (NSArray *)metadataForFormat:(NSString *)format AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;
#endif

@end

