/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>

/* HIGH-LEVEL NOTES:
- QCCompositions are opaque objects representing Quartz compositions that can be created from a file or data, or retrieved from the Composition Repository.
- QCCompositions objects can be passed to other Quartz Composer APIs like QCRenderer, QCCompositionLayer or QCView.
- A composition protocol is identified by a name and defines a set of required and optional input parameters and output results compositions conforming to that protocol must have.
- The QCComposition class cannot be subclassed.
*/

/* Keys for composition attributes */
extern NSString* const QCCompositionAttributeNameKey; //NSString
extern NSString* const QCCompositionAttributeDescriptionKey; //NSString
extern NSString* const QCCompositionAttributeCopyrightKey; //NSString
#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
extern NSString* const QCCompositionAttributeBuiltInKey; //NSNumber - Boolean
extern NSString* const QCCompositionAttributeIsTimeDependentKey; //NSNumber - Boolean
extern NSString* const QCCompositionAttributeHasConsumersKey; //NSNumber - Boolean
extern NSString* const QCCompositionAttributeCategoryKey; //NSString
#endif


#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)


/* Standard composition categories */
extern NSString* const QCCompositionCategoryDistortion;
extern NSString* const QCCompositionCategoryStylize;
extern NSString* const QCCompositionCategoryUtility;

/* Standard composition input port keys */
extern NSString* const QCCompositionInputImageKey; //Image port
extern NSString* const QCCompositionInputSourceImageKey; //Image port
extern NSString* const QCCompositionInputDestinationImageKey; //Image port
extern NSString* const QCCompositionInputRSSFeedURLKey; //String port (must be passed a http or feed scheme URL)
extern NSString* const QCCompositionInputRSSArticleDurationKey; //Number port (expressed in seconds)
extern NSString* const QCCompositionInputPreviewModeKey; //Boolean port
extern NSString* const QCCompositionInputXKey; //Number port (normalized to the image width with the origin on the left)
extern NSString* const QCCompositionInputYKey; //Number port (normalized to the image height with the origin at the bottom)
extern NSString* const QCCompositionInputScreenImageKey; //Image port
extern NSString* const QCCompositionInputAudioPeakKey; //Number port (in [0,1] range as a mono signal with no decay applied)
extern NSString* const QCCompositionInputAudioSpectrumKey; //Structure port (contains 16 numbers in [0,1] range representing 16 spectrum bands of the mono signal from low to high frequencies with no decay applied)
extern NSString* const QCCompositionInputTrackPositionKey; //Number port (expressed in seconds)
extern NSString* const QCCompositionInputTrackInfoKey; //Structure port (contains the optional entries: "name" of type String, "artist" of type String, "album" of type String, "genre" of type String, "duration" of type Number and "artwork" of type Image)
extern NSString* const QCCompositionInputTrackSignalKey; //Boolean port
extern NSString* const QCCompositionInputPrimaryColorKey; //Color port
extern NSString* const QCCompositionInputSecondaryColorKey; //Color port
extern NSString* const QCCompositionInputPaceKey; //Number port (in [0,1] range)
#ifdef __QUARTZCOMPOSER_CORE3D__
extern NSString* const QCCompositionInputMeshKey; //Mesh port
#endif

/* Standard composition output port keys */
extern NSString* const QCCompositionOutputImageKey; //Image port
extern NSString* const QCCompositionOutputWebPageURLKey; //String port
#ifdef __QUARTZCOMPOSER_CORE3D__
extern NSString* const QCCompositionOutputMeshKey; //Mesh port
#endif

/* Composition graphic animation protocol (the composition renders a generic graphical animation):
- QCCompositionInputPrimaryColorKey (optional): The primary color of the animation
- QCCompositionInputSecondaryColorKey (optional): The secondary color of the animation
- QCCompositionInputPaceKey (optional): The global pace of the animation
- QCCompositionInputPreviewModeKey (optional): Indicates if the animation should run in lower-quality for preview purposes
*/
extern NSString* const QCCompositionProtocolGraphicAnimation;

/* Composition image transition protocol (the composition renders a transition between two images for time in [0,1] range):
- QCCompositionInputSourceImageKey: Image to transition from
- QCCompositionInputDestinationImageKey: Image to transition to
- QCCompositionInputPrimaryColorKey (optional): The primary color of the transition
- QCCompositionInputSecondaryColorKey (optional): The secondary color of the transition
- QCCompositionInputPreviewModeKey (optional): Indicates if the transition should run in lower-quality for preview purposes
*/
extern NSString* const QCCompositionProtocolGraphicTransition;

/* Composition image filter protocol (the composition applies an effect to a source image):
- QCCompositionInputImageKey: Source image
- QCCompositionInputXKey (optional): X position of the effect center point
- QCCompositionInputYKey (optional): Y position of the effect center point
- QCCompositionInputPreviewModeKey (optional): Indicates if the filter should run in lower-quality for preview purposes
- QCCompositionOutputImageKey: New image with the applied effect
*/
extern NSString* const QCCompositionProtocolImageFilter;

/* Composition screen saver protocol (the composition can be used as a screen saver):
- QCCompositionInputScreenImageKey (optional): Receives a screenshot image of the screen the screen saver will run on
- QCCompositionInputPreviewModeKey (optional): Indicates if the screen saver is rendering in preview mode
- QCCompositionOutputWebPageURLKey (optional): Web page URL to open in default web browser when screen saver exits (only allowed if screen saver password is disabled)
*/
extern NSString* const QCCompositionProtocolScreenSaver;

/* Composition RSS visualizer protocol (the composition acts as a visualizer for a RSS feed):
- QCCompositionInputRSSFeedURLKey: RSS Feed URL
- QCCompositionInputRSSArticleDurationKey (optional): The display duration of each feed article
*/
extern NSString* const QCCompositionProtocolRSSVisualizer;

/* Composition music visualizer protocol (the composition acts as a visualizer for music):
- QCCompositionInputAudioPeakKey: the instantaneous audio peak
- QCCompositionInputAudioSpectrumKey: the instantaneous audio spectrum
- QCCompositionInputTrackInfoKey (optional): Receives information about the currently playing track
- QCCompositionInputTrackSignalKey (optional): Indicates a new track has started playing
*/
extern NSString* const QCCompositionProtocolMusicVisualizer;

#ifdef __QUARTZCOMPOSER_CORE3D__
/* Composition mesh filter protocol (the composition applies an effect to a source image):
- QCCompositionInputMeshKey: Source image
- QCCompositionOutputMeshKey: New image with the applied effect
*/
extern NSString* const QCCompositionProtocolMeshFilter;
#endif

/* Opaque composition object */
@interface QCComposition : NSObject <NSCopying>
{
@private
	NSArray*				_protocols;
	NSDictionary*			_attributes;
	NSArray*				_inputKeys;
	NSArray*				_outputKeys;
	id						_backing;
	
	NSString*				_identifier;
	NSTimeInterval			_timestamp;
	BOOL					_stateOK;
}

/*
Returns an autoreleased QCComposition initialized from a Quartz composition file or nil on error.
*/
+ (QCComposition*) compositionWithFile:(NSString*)path;

/*
Returns an autoreleased QCComposition initialized from the contents of a Quartz composition file or nil on error.
*/
+ (QCComposition*) compositionWithData:(NSData*)data;

/*
Returns the list of protocol names this composition conforms to.
*/
- (NSArray*) protocols;

/*
Returns a dictionary containing attributes describing the composition and the input / output ports on its root patch.
The dictionary may define the following composition attributes:
	- QCCompositionAttributeNameKey: the name of the composition as specified in the information dialog in Quartz Composer (NSString)
	- QCCompositionAttributeDescriptionKey: the description of the composition as specified in the information dialog in Quartz Composer (NSString)
	- QCCompositionAttributeCopyrightKey: the copyright of the composition as specified in the information dialog in Quartz Composer (NSString)
The dictionary also contains dictionaries corresponding to the keys identifying each input / output port of the root patch of the composition. Each of those dictionaries defines the following port attributes:
	- QCPortAttributeTypeKey: the type of the port (NSString)
	- QCPortAttributeNameKey: the name of the port if available (NSString)
	- QCPortAttributeMinimumValueKey: the minimum numerical value accepted by the port if available - smaller values will be clamped (NSNumber)
	- QCPortAttributeMaximumValueKey: the maximum numerical value accepted by the port if available - bigger values will be clamped (NSNumber)
	- QCPortAttributeMenuItemsKey: the list of menu item titles if available - index ports only (NSArray of NSStrings)
*/
- (NSDictionary*) attributes;

/*
Returns an array listing the keys identifying the input ports of the root patch of the composition.
*/
- (NSArray*) inputKeys;

/*
Returns an array listing the keys identifying the output ports of the root patch of the composition.
*/
- (NSArray*) outputKeys;

@end

#endif
