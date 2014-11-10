/*
 File:		AVAudioUnitComponent.h
 Framework:	AVFoundation
 
 Copyright (c) 2014 Apple Inc. All Rights Reserved.
 */

#import <AVFoundation/AVAudioTypes.h>
#import <AudioUnit/AudioComponent.h>
#import <AudioUnit/AUComponent.h>

// Standard Audio Unit Types
AVF_EXPORT NSString * const AVAudioUnitTypeOutput		NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeMusicDevice	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeMusicEffect	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeFormatConverter	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeEffect	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeMixer	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypePanner	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeGenerator	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeOfflineEffect	NS_AVAILABLE(10_10, NA);
AVF_EXPORT NSString * const AVAudioUnitTypeMIDIProcessor	NS_AVAILABLE(10_10, NA);

// Standard Audio Unit Manufacturers
AVF_EXPORT NSString * const AVAudioUnitManufacturerNameApple	NS_AVAILABLE(10_10, NA);

#pragma mark AVAudioUnitComponent

/*!
 @class AVAudioUnitComponent
 @discussion
	 AVAudioUnitComponent provides details about an audio unit such as type, subtype, manufacturer, 
	 location etc. User tags can be added to the AVAudioUnitComponent which can be queried later
 	 for display.
 */

NS_CLASS_AVAILABLE_MAC(10_10)
@interface AVAudioUnitComponent : NSObject
{
	void* impl_;
}

@property(nonatomic,readonly) NSString		*name;

/* standard audio unit types as strings */
@property(nonatomic,readonly) NSString		*typeName;
/* localized string of typeName for display */
@property(nonatomic,readonly) NSString		*localizedTypeName;

@property(nonatomic,readonly) NSString		*manufacturerName;
/* version number comprised of a hexadecimal number with major, minor, dot-release format: 0xMMMMmmDD */
@property(nonatomic,readonly) NSUInteger	version;
@property(nonatomic,readonly) NSString		*versionString;
@property(nonatomic,readonly) NSURL			*iconURL;
/* URL representing location of component */
@property(nonatomic,readonly) NSURL			*componentURL;

/* NSSArray of NSNumbers each of which corresponds to one of the constants in Mach-O Architecture in NSBundle Class Reference */
@property(readonly)			  NSArray		*availableArchitectures;
@property(nonatomic,readonly) BOOL			hasCustomView;
@property(nonatomic,readonly) BOOL			passesAUVal;
/* only applies to the current process */
@property(nonatomic,readonly,getter=isSandboxSafe) BOOL	sandboxSafe;

@property(readonly)			  BOOL			hasMIDIInput;
@property(readonly)			  BOOL			hasMIDIOutput;

@property(nonatomic,readonly) AudioComponent	audioComponent;
@property(nonatomic,readonly) NSDictionary		*configurationDictionary;

/* User tags represent the tags from the current user.  */
@property(copy)				  NSArray		*userTagNames;
/* allTagNames represent the tags from the current user plus the tags defined by the manufacturer. */
@property(nonatomic,readonly) NSArray		*allTagNames;

@property(nonatomic,readonly) AudioComponentDescription	audioComponentDescription;

- (BOOL)supportsNumberInputChannels:(NSInteger)numInputChannels outputChannels:(NSInteger)numOutputChannels;

@end


#pragma mark AVAudioUnitComponentManager

/* The notification object is an AVAudioUnitComponent object */
AVF_EXPORT NSString * const AVAudioUnitComponentTagsDidChangeNotification NS_AVAILABLE(10_10, NA);

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

NS_CLASS_AVAILABLE_MAC(10_10)
@interface AVAudioUnitComponentManager : NSObject
{
	void* impl_;
}

/*! @discussion 
 		returns all tags associated with the current user as well as all system tags defined by 
		the audio unit(s).
 */
@property(nonatomic,readonly) NSArray	*tagNames;

/*! @discussion
		returns the localized standard system tags defined by the audio unit(s).
 */

@property(nonatomic,readonly) NSArray	*standardLocalizedTagNames;

/* returns singleton instance of AVAudioUnitComponentManager */
+ (instancetype)sharedAudioUnitComponentManager;

/*!
 @method componentsMatchingPredicate
 @abstract	returns an array of AVAudioComponent objects that matches the search predicate
 @discussion
 		AudioComponent's information or tags can be used to build a search criteria. 
 		For example, "typeName CONTAINS 'Effect'" or tags IN {'Sampler', 'MIDI'}"
 */
- (NSArray *)componentsMatchingPredicate:(NSPredicate *)predicate;

/*!
 @method componentsPassingTest
 @abstract	returns an array of AVAudioComponent objects that passes the user provided block method.
 @discussion
		For each AudioComponent found by the manager, the block method will be called. If the return
 		value is YES then the AudioComponent is added to the resulting array else it will excluded. 
 		This gives more control to the block provider to filter out the components returned.
 */
- (NSArray *)componentsPassingTest:(BOOL(^)(AVAudioUnitComponent *comp, BOOL *stop))testHandler;

/*!
 @method componentsMatchingDescription
 @abstract	returns an array of AVAudioComponent objects that matches the description
 @discussion
 		This method provides a mechanism to search for AudioComponents using AudioComponentDescription
		structure. The type, subtype and manufacturer fields are used to search for audio units. A 
 		value of 0 for any of these fields is a wildcard and returns the first match found.
 */
- (NSArray *)componentsMatchingDescription:(AudioComponentDescription)desc;

@end
