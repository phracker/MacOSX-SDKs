/*
 File:		AVAudioUnitComponent.h
 Framework:	AVFoundation
 
 Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
 */

#if !0

#import <AVFAudio/AVAudioTypes.h>

#if __has_include(<AudioToolbox/AudioComponent.h>)
#define AVAUDIOUNITCOMPONENT_HAVE_AUDIOCOMPONENT 1
#import <AudioToolbox/AudioComponent.h>
#import <AudioToolbox/AUComponent.h>
#endif

NS_ASSUME_NONNULL_BEGIN

// Standard Audio Unit Types
AVF_EXPORT NSString * const AVAudioUnitTypeOutput				API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeMusicDevice			API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeMusicEffect			API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeFormatConverter		API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeEffect				API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeMixer				API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypePanner				API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeGenerator			API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeOfflineEffect		API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString * const AVAudioUnitTypeMIDIProcessor		API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

// Standard Audio Unit Manufacturers
AVF_EXPORT NSString * const AVAudioUnitManufacturerNameApple	API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

#pragma mark AVAudioUnitComponent

/*!
 @class AVAudioUnitComponent
 @discussion
	 AVAudioUnitComponent provides details about an audio unit such as type, subtype, manufacturer, 
	 location etc. User tags can be added to the AVAudioUnitComponent which can be queried later
 	 for display.
 */

OS_EXPORT API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioUnitComponent : NSObject
{
	void *_impl;
}
/*! @property name
	@abstract the name of an audio component
 */
@property (nonatomic, readonly) NSString		*name;

/*! @property typeName
	@abstract standard audio component types returned as strings
 */
@property (nonatomic, readonly) NSString		*typeName;

/*! @property typeName
	@abstract localized string of typeName for display
 */
@property (nonatomic, readonly) NSString		*localizedTypeName;

/*! @property manufacturerName
	@abstract the manufacturer name, extracted from the manufacturer key defined in Info.plist dictionary
 */
@property (nonatomic, readonly) NSString		*manufacturerName;

/*! @property version
	@abstract version number comprised of a hexadecimal number with major, minor, dot-release format: 0xMMMMmmDD
 */
@property (nonatomic, readonly) NSUInteger	version;

/*! @property versionString
	@abstract version number as string
 */
@property (nonatomic, readonly) NSString		*versionString;

/*! @property componentURL
	@abstract URL representing location of component
 */
@property (nonatomic, readonly, nullable) NSURL		*componentURL NS_DEPRECATED(10_10, 10_11, NA, NA);

/*! @property availableArchitectures
	@abstract NSArray of NSNumbers each of which corresponds to one of the constants in Mach-O Architecture in NSBundle Class Reference
 */
@property (nonatomic, readonly) NSArray<NSNumber *>		*availableArchitectures API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/*! @property sandboxSafe
	@abstract On OSX, YES if the AudioComponent can be loaded into a sandboxed process otherwise NO.
			  On iOS, this is always YES.
 */
@property (nonatomic, readonly, getter=isSandboxSafe) BOOL		sandboxSafe;

/*! @property hasMIDIInput
	@abstract YES if AudioComponent has midi input, otherwise NO
 */
@property (nonatomic, readonly) BOOL		hasMIDIInput;

/*! @property hasMIDIOutput
	@abstract YES if AudioComponent has midi output, otherwise NO
 */
@property (nonatomic, readonly) BOOL		hasMIDIOutput;

#if AVAUDIOUNITCOMPONENT_HAVE_AUDIOCOMPONENT
/*! @property audioComponent
	@abstract the audioComponent that can be used in AudioComponent APIs.
 */
@property (nonatomic, readonly) AudioComponent	audioComponent;
#endif

/*! @property userTagNames
	@abstract User tags represent the tags from the current user.
 */
@property (copy) NSArray<NSString *>		*userTagNames API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/*! @property allTagNames
	@abstract represent the tags from the current user and the system tags defined by AudioComponent.
 */
@property (nonatomic, readonly) NSArray<NSString *>		*allTagNames;

#if AVAUDIOUNITCOMPONENT_HAVE_AUDIOCOMPONENT
/*! @property audioComponentDescription
	@abstract description of the audio component that can be used in AudioComponent APIs.
 */
@property (nonatomic, readonly) AudioComponentDescription	audioComponentDescription;
#endif

/*! @property iconURL
	@abstract A URL that will specify the location of an icon file that can be used when presenting UI
 for this audio component.
 */
@property (nonatomic, readonly, nullable) NSURL		*iconURL API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

#if TARGET_OS_OSX
/*! @property icon
	@abstract An icon representing the component.
    @discussion
        For a component originating in an app extension, the returned icon will be that of the
        application containing the extension.
        
        For components loaded from bundles, the icon will be that of the bundle.
 */
@property (nonatomic, readonly, nullable) NSImage *icon API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

/*! @property passesAUVal
	@abstract YES if the AudioComponent has passed the AU validation tests, otherwise NO
 */
@property (nonatomic, readonly) BOOL		passesAUVal API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/*! @property hasCustomView
	@abstract YES if the AudioComponent provides custom view, otherwise NO
 */
@property (nonatomic, readonly) BOOL		hasCustomView API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/*! @property configurationDictionary
	@abstract A NSDictionary that contains information describing the capabilities of the AudioComponent.
	The specific information depends on the type and the keys are defined in AudioUnitProperties.h
 */
@property (nonatomic, readonly) NSDictionary<NSString *, id>		*configurationDictionary API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/*! @property supportsNumberInputChannels: outputChannels:
	@abstract returns YES if the AudioComponent supports the input/output channel configuration
 */
- (BOOL)supportsNumberInputChannels:(NSInteger)numInputChannels outputChannels:(NSInteger)numOutputChannels API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

@end


#pragma mark AVAudioUnitComponentManager

/* The notification object is an AVAudioUnitComponent object */
AVF_EXPORT NSString * const AVAudioUnitComponentTagsDidChangeNotification API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @class AVAudioUnitComponentManager
 @discussion 
 		AVAudioUnitComponentManager is a singleton object that provides an easy way to find
 		audio components that are registered with the system. It provides methods to search and
 		query various information about the audio components without opening them.
 
 		Currently audio components that are audio units can only be searched.
 
 		The class also supports predefined system tags and arbitrary user tags. Each audio unit can be 
 		tagged as part of its definition. Refer to AudioComponent.h for more details. AudioUnit Hosts
 		such as Logic or GarageBand can present groupings of audio units based on the tags.
 
 		Searching for audio units can be done in various ways
 			- using a NSPredicate that contains search strings for tags or descriptions
 			- using a block to match on custom criteria 
			- using an AudioComponentDescription
 */

OS_EXPORT API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioUnitComponentManager : NSObject
{
	void *_impl;
}

/*! @discussion 
 		returns all tags associated with the current user as well as all system tags defined by 
		the audio unit(s).
 */
@property (nonatomic, readonly) NSArray<NSString *>		*tagNames;

/*! @discussion
		returns the localized standard system tags defined by the audio unit(s).
 */

@property (nonatomic, readonly) NSArray<NSString *>		*standardLocalizedTagNames;

/* returns singleton instance of AVAudioUnitComponentManager */
+ (instancetype)sharedAudioUnitComponentManager;

/*!
 @method componentsMatchingPredicate:
 @abstract	returns an array of AVAudioUnitComponent objects that match the search predicate.
 @discussion
 		AudioComponent's information or tags can be used to build a search criteria. 
 		For example, "typeName CONTAINS 'Effect'" or tags IN {'Sampler', 'MIDI'}"
 */
- (NSArray<AVAudioUnitComponent *> *)componentsMatchingPredicate:(NSPredicate *)predicate;

/*!
 @method componentsPassingTest:
 @abstract	returns an array of AVAudioUnitComponent objects that pass the user provided block method.
 @discussion
		For each AudioComponent found by the manager, the block method will be called. If the return
 		value is YES then the AudioComponent is added to the resulting array else it will excluded. 
 		This gives more control to the block provider to filter out the components returned.
 */
- (NSArray<AVAudioUnitComponent *> *)componentsPassingTest:(BOOL(^)(AVAudioUnitComponent *comp, BOOL *stop))testHandler;

#if AVAUDIOUNITCOMPONENT_HAVE_AUDIOCOMPONENT
/*!
 @method componentsMatchingDescription:
 @abstract	returns an array of AVAudioUnitComponent objects that match the description.
 @discussion
 		This method provides a mechanism to search for AudioComponents using AudioComponentDescription
		structure. The type, subtype and manufacturer fields are used to search for audio units. A 
 		value of 0 for any of these fields is a wildcard and returns the first match found.
 */
- (NSArray<AVAudioUnitComponent *> *)componentsMatchingDescription:(AudioComponentDescription)desc;
#endif

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_BRIDGE
