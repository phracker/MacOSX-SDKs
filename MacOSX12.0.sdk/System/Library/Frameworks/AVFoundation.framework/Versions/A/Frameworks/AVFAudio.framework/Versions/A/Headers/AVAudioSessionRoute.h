#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioSessionRoute.h>)
/*!
	@file		AVAudioSessionRoute.h
	@framework	AudioSession.framework
	@copyright	(c) 2017-2020 Apple Inc. All rights reserved.
*/

#ifndef AudioSession_AVAudioSessionRoute_h
#define AudioSession_AVAudioSessionRoute_h

#import <AVFAudio/AVAudioSessionTypes.h>


NS_ASSUME_NONNULL_BEGIN

#pragma mark-- constants for data source locations, orientations, polar patterns, and channel roles --

/// The location of a data source on an iOS device.
typedef NSString *AVAudioSessionLocation NS_STRING_ENUM;
OS_EXPORT AVAudioSessionLocation const AVAudioSessionLocationUpper					API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionLocation const AVAudioSessionLocationLower					API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));

/// The orientation or directionality of a data source on an iOS device.
typedef NSString *AVAudioSessionOrientation NS_STRING_ENUM;
OS_EXPORT AVAudioSessionOrientation const AVAudioSessionOrientationTop				API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionOrientation const AVAudioSessionOrientationBottom			API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionOrientation const AVAudioSessionOrientationFront			API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionOrientation const AVAudioSessionOrientationBack				API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionOrientation const AVAudioSessionOrientationLeft				API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionOrientation const AVAudioSessionOrientationRight			API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0));

/// The possible polar patterns for a data source on an iOS device.
typedef NSString *AVAudioSessionPolarPattern NS_STRING_ENUM;
OS_EXPORT AVAudioSessionPolarPattern const AVAudioSessionPolarPatternOmnidirectional	API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionPolarPattern const AVAudioSessionPolarPatternCardioid			API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));
OS_EXPORT AVAudioSessionPolarPattern const AVAudioSessionPolarPatternSubcardioid		API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));

/*! If you select a data source with AVAudioSessionPolarPatternStereo, then you must call setPreferredInputOrientation:error: on your Audio Session so that left and right are presented from the correct directions. */
OS_EXPORT AVAudioSessionPolarPattern const AVAudioSessionPolarPatternStereo			API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos, macos);

#pragma mark-- class interfaces --

/*!
	@class	AVAudioSessionChannelDescription
	@brief	Information about a port's audio channels.
	
	AudioQueue, AURemoteIO and AUVoiceIO instances can be assigned to communicate with specific
	hardware channels by setting an array of <port UID, channel index> pairs.
*/
API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionChannelDescription : NSObject {
@private
	void *_impl;
}

/// A human-readable name for the channel.
@property (nonatomic, readonly) NSString *			channelName API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The UID (unique identifier) of the port owning the channel.
@property (nonatomic, readonly) NSString *			owningPortUID API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The index of this channel in its owning port's array of channels.
@property (nonatomic, readonly) NSUInteger			channelNumber API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Description of the physical location of this channel.
@property (nonatomic, readonly) AudioChannelLabel	channelLabel API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

@end

/// Information about one of potentially multiple data sources associated with a port.
API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionDataSourceDescription : NSObject {
@private
	void *_impl;
}

/// System-assigned ID for the data source.
@property (readonly) NSNumber *dataSourceID API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Human-readable name for the data source.
@property (readonly) NSString *dataSourceName API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*
	Location and orientation can be used to distinguish between multiple data sources
	belonging to a single port.  For example, in the case of a port of type
	AVAudioSessionPortBuiltInMic, one can use these properties to differentiate between an
	upper/front-facing microphone and a lower/bottom-facing microphone.
*/

/// Describes the general location of a data source. Will be nil for data sources for which the
/// location is not known.
@property (readonly, nullable) AVAudioSessionLocation location API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Describes the orientation of a data source.  Will be nil for data sources for which the
/// orientation is not known.
@property (readonly, nullable) AVAudioSessionOrientation orientation API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Array of one or more AVAudioSessionPolarPatterns describing the supported polar patterns for a
/// data source.  Will be nil for data sources that have no selectable patterns.
@property (readonly, nullable) NSArray<AVAudioSessionPolarPattern> *supportedPolarPatterns API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// Describes the currently selected polar pattern.  Will be nil for data sources that have no
/// selectable patterns.
@property (readonly, nullable) AVAudioSessionPolarPattern selectedPolarPattern API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// Describes the preferred polar pattern.  Will be nil for data sources that have no selectable
/// patterns or if no preference has been set.
@property (readonly, nullable) AVAudioSessionPolarPattern preferredPolarPattern API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/*!
	@brief Select the desired polar pattern from the set of available patterns. Setting a nil value
	will clear the preference.
 
	@note If the owning port and data source are part of the active audio route, changing the polar
	pattern will likely result in a route reconfiguration. If the owning port and data source are
	not part of the active route, selecting a polar pattern will not result in an immediate route
	reconfiguration.  Use AVAudioSession's setPreferredInput:error: method to activate the port. Use
	setPreferredDataSource:error: to active the data source on the port.
	You must call setPreferredInputOrientation:error: on the AVAudioSession if you chose the
	AVAudioSessionPolarPatternStereo polar pattern.
*/
- (BOOL)setPreferredPolarPattern:(nullable AVAudioSessionPolarPattern)pattern error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

@end // AVAudioSessionDataSourceDescription

/// Information about a port, a physical connector or audio device.
API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionPortDescription : NSObject {
@private
	void *_impl;
}

@property (readonly, nonatomic) AVAudioSessionPort portType API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// A descriptive name for the associated hardware port
@property (readonly, nonatomic) NSString *portName API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// A system-assigned unique identifier for the associated hardware port
@property (readonly, nonatomic) NSString *UID API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief This property's value will be true if the associated hardware port has built-in
	processing for two-way voice communication.
 
	Applications that use their own proprietary voice processing algorithms should use this property
	to decide when to disable processing.  On the other hand, if using Apple's Voice Processing I/O
	unit (subtype kAudioUnitSubType_VoiceProcessingIO), the system will automatically manage this
	for the application. In particular, ports of type AVAudioSessionPortBluetoothHFP and
	AVAudioSessionPortCarAudio often have hardware voice processing.
*/
@property (readonly) BOOL hasHardwareVoiceCallProcessing API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
    @brief This property's value will be true if the port supports spatial audio playback and the feature is
    enabled.
     
    'Now Playing' apps should also inform the system if they support multichannel audio content using
    -setSupportsMultichannelContent:error: method. Apps may also register to receive the
    AVAudioSessionSpatialPlaybackCapabilitiesChanged notification to detect changes in user preferences that
    affect spatial audio playback.
   
    This property is only relevant in the context of ports that have a small number of hardware channels
    (typically 2), but have enhanced capabilities for rendering multi-channel content. Note that some port
    types such as USB and HDMI may support multi-channel playback because they have hardware formats supporting
    more than 2 channels. For example, many HDMI receivers are connected to multiple speakers and are capable of
    rendering 5.1, 7.1, or other popular surround sound formats. Applications interested in utilizing multi-channel
    formats should also query AVAudioSession's maximumOutputNumberOfChannels property and make use of
    -setPreferredOutputNumberOfChannels:error: to set the preferred number of hardware channels.
*/
@property (readonly, getter=isSpatialAudioEnabled) BOOL spatialAudioEnabled API_AVAILABLE(ios(15.0), watchos(8.0), tvos(15.0)) API_UNAVAILABLE(macos);

@property (readonly, nonatomic, nullable) NSArray<AVAudioSessionChannelDescription *> *channels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Will be nil if there are no selectable data sources.
@property (readonly, nonatomic, nullable) NSArray<AVAudioSessionDataSourceDescription *> *dataSources API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// Will be nil if there are no selectable data sources. In all other cases, this property reflects
/// the currently selected data source.
@property (readonly, nonatomic, nullable) AVAudioSessionDataSourceDescription *selectedDataSource API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// This property reflects the application's preferred data source for the Port. Will be nil if
/// there are no selectable data sources or if no preference has been set.
@property (readonly, nonatomic, nullable) AVAudioSessionDataSourceDescription *preferredDataSource API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/*!
	@brief Select the preferred data source for this port. The input dataSource parameter must be
	one of the dataSources exposed by the dataSources property. Setting a nil value will clear the
	preference. Note: if the port is part of the active audio route, changing the data source will
	likely result in a route reconfiguration.  If the port is not part of the active route,
	selecting a new data source will not result in an immediate route reconfiguration.  Use
	AVAudioSession's -setPreferredInput:error: method to activate the port.
*/
- (BOOL)setPreferredDataSource:(nullable AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

@end // AVAudioSessionPortDescription

/// A description of the input and output ports which comprise a route.
API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionRouteDescription : NSObject {
@private
	void *_impl;
}

/// Flattened list of all input port descriptions associated with all the streams as part of the route.
@property (readonly, nonatomic) NSArray<AVAudioSessionPortDescription *> *inputs API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Flattened list of all output port descriptions associated with all the streams as part of the route.
@property (readonly, nonatomic) NSArray<AVAudioSessionPortDescription *> *outputs API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

@end // AVAudioSessionRouteDescription

NS_ASSUME_NONNULL_END

#endif // AudioSession_AVAudioSessionRoute_h
#else
#include <AudioSession/AVAudioSessionRoute.h>
#endif
