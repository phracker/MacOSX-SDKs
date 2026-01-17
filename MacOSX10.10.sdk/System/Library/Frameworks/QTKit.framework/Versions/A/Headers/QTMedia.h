/*
	File:		QTMedia.h

	Copyright:	(c)2004-2012 by Apple Inc., all rights reserved.

*/
/*!
    @class			QTMedia

    @abstract		A QTMedia object is an object that represents the data associated with a QTTrack object.
 
	@discussion		A QTMovie object typically contains one or more streams of media data, which are represented by
					QTTrack objects. A QTTrack object has exactly one QTMedia object associated with it. The QTMedia
					object exposes attributes such as media type and media characteristics.
 
					When a QTMovie object has been initialized with QTMovieOpenForPlaybackAttribute set to NO,
					a QTMedia object wraps the underlying QuickTime media (of type Media).
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

	// media types
/*!
	@constant		QTMediaTypeVideo
	@abstract		The media type of a video track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeVideo								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeSound
	@abstract		The media type of a sound track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeSound								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeText
	@abstract		The media type of a text track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeText								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeBase
	@abstract		The media type of a base track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeBase								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeMPEG
	@abstract		The media type of an MPEG track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeMPEG								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeMusic
	@abstract		The media type of a music track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeMusic								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeTimeCode
	@abstract		The media type of a timecode track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeTimeCode							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeSprite
	@abstract		The media type of a sprite track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeSprite								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeFlash
	@abstract		The media type of a Flash track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeFlash								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeMovie
	@abstract		The media type of a movie media track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeMovie								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeTween
	@abstract		The media type of a tween track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeTween								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaType3D
	@abstract		The media type of a QuickDraw 3D track.
 */
QTKIT_EXTERN NSString * const QTMediaType3D									AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeSkin
	@abstract		The media type of a skin track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeSkin								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeQTVR
	@abstract		The media type of a QuickTime VR track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeQTVR								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeHint
	@abstract		The media type of a hint track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeHint								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeStream
	@abstract		The media type of a stream track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeStream								AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeMuxed
	@abstract		The media type of a multiplexed audio and video track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeMuxed								AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeQuartzComposer
	@abstract		The media type of a Quartz Composer track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeQuartzComposer						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeSubtitle
	@abstract		The media type of a subtitle track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeSubtitle							AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaTypeClosedCaption
	@abstract		The media type of a closed-caption track.
 */
QTKIT_EXTERN NSString * const QTMediaTypeClosedCaption						AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// media characteristics
/*!
	@constant		QTMediaCharacteristicVisual
	@abstract		Indicates whether a QTMedia object has visual data.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicVisual					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicAudio
	@abstract		Indicates whether a QTMedia object has audio data.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicAudio					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicCanSendVideo
	@abstract		Indicates whether a QTMedia object can send visual data to another track.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicCanSendVideo				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicProvidesActions
	@abstract		Indicates whether a QTMedia object has actions.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicProvidesActions			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicNonLinear
	@abstract		Indicates whether a QTMedia object is non-linear.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicNonLinear				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicCanStep
	@abstract		Indicates whether a QTMedia object can step.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicCanStep					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicHasNoDuration
	@abstract		Indicates whether a QTMedia object has no duration.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicHasNoDuration			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicHasSkinData
	@abstract		Indicates whether a QTMedia object has skin data.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicHasSkinData				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicProvidesKeyFocus
	@abstract		Indicates whether key events can be focused at a QTMedia object.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicProvidesKeyFocus			AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@constant		QTMediaCharacteristicHasVideoFrameRate
	@abstract		Indicates whether a QTMedia object has a video frame rate.
 */
QTKIT_EXTERN NSString * const QTMediaCharacteristicHasVideoFrameRate		AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// media attributes
/*!
	@constant		QTMediaCreationTimeAttribute
	@abstract		The creation time of the container from which a QTMedia object was initialized; the value for this key is of type NSDate.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMediaCreationTimeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;  // NSDate

/*!
	@constant		QTMediaDurationAttribute
	@abstract		The duration of a QTMedia object; the value for this key is of type NSValue, interpreted as a QTTime.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMediaDurationAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSValue (QTTime)

/*!
	@constant		QTMediaModificationTimeAttribute
	@abstract		The modification time of a QTMedia object; the value for this key is of type NSDate.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMediaModificationTimeAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSDate

/*!
	@constant		QTMediaSampleCountAttribute
	@abstract		The number of samples in a QTMedia object; the value for this key is of type NSNumber, interpreted as a long.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMediaSampleCountAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSNumber (long)

/*!
	@constant		QTMediaQualityAttribute
	@abstract		The quality of a QTMedia object; the value for this key is of type NSNumber, interpreted as a short.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMediaQualityAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSNumber (short)

/*!
	@constant		QTMediaTimeScaleAttribute
	@abstract		The time scale of a QTMedia object; the value for this key is of type NSNumber, interpreted as a long.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMediaTimeScaleAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSNumber (long)

/*!
	@constant		QTMediaTypeAttribute
	@abstract		The type of a QTMedia object; the value for this key is of type NSString.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTMediaTypeAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// NSString

@class QTMovie;
@class QTTrack;
@class QTQuickTimeMovieWrapper;

@interface QTMedia : NSObject
{
@private
#if __LP64__
	int32_t					_proxy;
#else
	Media					_quickTimeMedia;
	NSUndoManager			*_undoManager;
	NSDictionary			*_undoAttributes;
	QTQuickTimeMovieWrapper	*_quickTimeMovieWrapper;
#endif
	long					_flags;
	QTTrack					*_track;
}

#if !__LP64__
	// class/init methods
/*!
	@method			mediaWithQuickTimeMedia:error:
	@abstract		Returns a QTMedia object associated with a QuickTime Media.
	@discussion		This method cannot be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					In addition, this method cannot be called by 64-bit applications.
	@param			media
					A QuickTime Media with which to initialize the QTMedia object.
	@param			errorPtr
					A pointer to an NSError object; if a QTMedia object cannot be created, an NSError object is returned in this location.
*/
+ (id)mediaWithQuickTimeMedia:(Media)media error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			initWithQuickTimeMedia:error:
	@abstract		Returns a QTMedia object associated with a QuickTime Media.
	@discussion		This method cannot be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					In addition, this method cannot be called by 64-bit applications.
	@param			media
					A QuickTime Media with which to initialize the QTMedia object.
	@param			errorPtr
					A pointer to an NSError object; if a QTMedia object cannot be created, an NSError object is returned in this location.
*/
- (id)initWithQuickTimeMedia:(Media)media error:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

	// parent
/*!
	@method			track
	@abstract		Returns the QTTrack object associated with a QTMedia object.
	@discussion		This method can be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (QTTrack *)track AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// attributes
/*!
	@method			mediaAttributes
	@abstract		Returns a dictionary containing the current values of all public attributes of a QTMedia object.
	@discussion		This method can be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (NSDictionary *)mediaAttributes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setMediaAttributes:
	@abstract		Sets the attributes of a QTMedia object using the key-value pairs in a specified dictionary.
	@discussion		This method can be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					However, certain attributes may not be writable when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			attributes
					An NSDictionary object that specifies the attributes to set and their desired values.
*/
- (void)setMediaAttributes:(NSDictionary *)attributes AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			attributeForKey:
	@abstract		Returns the current value of an attribute of a QTMedia object.
	@discussion		This method can be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			attributeKey
					An NSString object that specifies the attribute to be read; pass strings like QTMediaTimeScaleAttribute or QTMediaTypeAttribute.
*/
- (id)attributeForKey:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
	@method			setAttribute:forKey:
	@abstract		Sets an attribute of a QTMedia object to a specified value.
	@discussion		This method can be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					However, certain attributes may not be writable when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			value
					An object that specifies the value of the attribute to be written.
	@param			attributeKey
					An NSString object that specifies the attribute to be written; pass strings like QTMediaTimeScaleAttribute or QTMediaTypeAttribute.
*/
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// characteristics
/*!
	@method			hasCharacteristic:
	@abstract		Indicates whether a QTMedia object has a specified characteristic.
	@discussion		This method can be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			characteristic
					An NSString object that specifies the characteristic to be read; pass strings like QTMediaCharacteristicVisual or QTMediaCharacteristicAudio.
	@result			Returns YES if the QTMedia object has the specified characteristic, NO otherwise. 
*/
- (BOOL)hasCharacteristic:(NSString *)characteristic AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if !__LP64__
	// underlying QT object
/*!
	@method			quickTimeMedia
	@abstract		Returns the QuickTime Media associated with a QTMedia object.
	@discussion		This method cannot be called when the movie containing this media has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					In addition, this method cannot be called by 64-bit applications.
*/
- (Media)quickTimeMedia AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif

@end
