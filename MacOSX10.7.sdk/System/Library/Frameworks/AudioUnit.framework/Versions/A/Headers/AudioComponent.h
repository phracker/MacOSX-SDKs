/*
     File:      AudioUnit/AudioComponent.h
 
     Contains:  API for finding and opening audio components
  
     Copyright: (c) 2007 - 2010 by Apple, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

#ifndef __AUDIOCOMPONENT_H__
#define __AUDIOCOMPONENT_H__

//=====================================================================================================================
#pragma mark Overview

/*!
    @header AudioComponent

    @discussion
    
    This file defines a collection of APIs that are designed to be used when finding and opening
    audio components (such as audio units, audio codecs, and audio file components).
    
    Traditionally, the Component Manager has been used for the registration, discovery, and
    packaging of these loadable code modules. However, this may not always be the case. In order
    to provide an API that will be supported going forward from SnowLeopard (10.6) and iPhone
    2.0, it is advised that applications use the Audio Component APIs to find and load (open)
    audio components such as audio units.

    The type "AudioComponent" or "AudioComponentInstance" should be seen and used as a distinct
    type from the Component Manager types of "Component" and "ComponentInstance". It is not the
    case that it is safe to assume a direct cast is compatible between this type and the other.

    The AudioComponent APIs provide a general, and mostly complete service for doing the basic
    task of finding and using audio components. If however, you find that you need functionality
    that is not provided by this API that was previously supported by the Component Manager then
    you should use the ComponentMgr APIs exclusively to find and open the Component Manager
    components. In other words, you should not assume that an audio component instance is always
    interchangeable with the existing ComponentInstance type.
    
    
    Beginning with Mac OS X 10.7, AudioComponents can be registered and used directly without
    involving the Component Manager. The system scans certain directories for bundles with names
    ending in ".audiocomp" or ".component" (the latter permits registering plug-ins in a single
    bundle with both the Component Manager and the Audio Component system). These directories
    are scanned non-recursively:
    
        ~/Library/Audio/Plug-Ins/Components
        /Library/Audio/Plug-Ins/Components
        /System/Library/Components

    Bundles' Info.plist dictionaries should contain an "AudioComponents" item whose value
    is an array of dictionaries, e.g.

        <key>AudioComponents</key>
        <array>
            <dict>
                <key>type</key>
                <string>aufx</string>
                <key>subtype</key>
                <string>XMPL</string>
                <key>manufacturer</key>
                <string>ACME</string>
                <key>flags</key>   <!-- this key is optional -->
                <integer>0</integer>
        
                <key>name</key>
                <string>AUExample</string>
                <key>version</key>
                <integer>12345</integer>
                <key>factoryFunction</key>
                <string>AUExampleFactory</string>
            </dict>
        </array>

    The type, subtype and manufacturer keys correspond to the OSType fields of the 
    AudioComponentDescription structure. They can be strings if they are 4 ASCII characters; 
    otherwise they must be 32-bit integers.
    
    The "factoryFunction" is the name of a AudioComponentFactoryFunction in the bundle's binary.
*/

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
    #include <CoreAudio/CoreAudioTypes.h>
    #include <CoreFoundation/CoreFoundation.h>
#else
    #include <CoreAudioTypes.h>
    #include <CoreFoundation.h>
#endif

//=====================================================================================================================
#pragma mark Constants

/*!
	@constant	kAudioComponentFlag_Unsearchable

	When this bit in AudioComponentDescription's componentFlags is set, AudioComponentFindNext
	will only return this component when performing a specific, non-wildcard search for the
	component, i.e. with non-zero values of componentType, componentSubType, and
	componentManufacturer. This can be useful when privately registering a component.
	Available starting in Mac OS X 10.7.
*/
enum {
	kAudioComponentFlag_Unsearchable = 1
};

//=====================================================================================================================
#pragma mark Data Types

/*!
    @struct         AudioComponentDescription
    @discussion     A structure used to describe the unique and identifying IDs of an audio component 
    @field          componentType
                        A unique 4-byte code identifying the generic type of an audio component
    @field          componentSubType
                        the particular flavor of this instance
    @field          componentManufacturer
                        vendor identification
    @field          componentFlags
                        must be set to zero unless a known specific value is requested
    @field          componentFlagsMask
                        must be set to zero unless a known specific value is requested
*/
#pragma pack(push, 4)
typedef struct AudioComponentDescription {
    OSType              componentType;
    OSType              componentSubType;
    OSType              componentManufacturer;
    UInt32              componentFlags;
    UInt32              componentFlagsMask;
} AudioComponentDescription;
#pragma pack(pop)

/*!
    @typedef        AudioComponent
    @abstract       The type used to represent a class of particular audio components
    @discussion     An audio component is usually found through a search and is then uniquely
                    identified by the triple of an audio component's type, subtype and
                    manufacturer.
                    
                    It can have properties associated with it (such as a name, a version).
                    
                    It is then used as a factory (like a class in an object-oriented programming
                    language) from which to create particular instances. The instances are used
                    to do the actual work.
                    
                    For example:
                    'aufx', 'dely', 'appl' describes the digital delay, audio unit effect from
                    Apple, Inc. You can find this component through searching explicitly for the
                    audio component that matches this pattern (this is an unique identifier -
                    there is only one match to this triple ID). Then once found, the Apple delay
                    effect audio unit can be created from its audio component and used to apply
                    that effect to an audio signal. While the audio component is a singleton,
                    you can of course create as many instances of a given audio component that
                    you need to do the work you need to do.
*/
typedef struct OpaqueAudioComponent *   AudioComponent;

/*!
    @typedef        AudioComponentInstance
    @abstract       The type used to represent an instance of a particular audio component
    @discussion     An audio component instance is created from its factory/producer audio
                    component. It is the body of code that does the work.
    
                    A special note: While on the desktop this is typedef'd to a
                    ComponentInstanceRecord *, you should not assume that this will always be
                    compatible and usable with Component Manager calls.
*/
#if TARGET_OS_IPHONE
    typedef struct OpaqueAudioComponentInstance *   AudioComponentInstance;
#else
    typedef struct ComponentInstanceRecord *        AudioComponentInstance;
#endif

typedef OSStatus (*AudioComponentMethod) (void *self,...);

/*!
*/
typedef struct AudioComponentPlugInInterface {
	OSStatus						(*Open)(void *self, AudioComponentInstance mInstance);
	OSStatus						(*Close)(void *self);
	AudioComponentMethod			(*Lookup) (SInt16 selector);
	void *							reserved; // set to NULL
} AudioComponentPlugInInterface;

/*!
    @typedef        AudioComponentFactoryFunction
    @abstract       A function that creates AudioComponentInstances.
    @discussion
                    Authors of AudioComponents may register them from bundles as described
                    above in the discussion of this header file, or dynamically within a single
                    process, using AudioComponentRegister.
    
    @param          inDesc
                        The AudioComponentDescription specifying the component to be instantiated.
    @result         A pointer to a structure whose first member is a pointer to an
                    AudioComponentPlugInInterface. Thus the return type could be considered
                    AudioComponentPlugInInterface **, but since in practice it is never
                    this basic type, but rather, AudioUnitPlugInInterface, AudioCodecPlugInInterface,
                    etc., it is declared void * for simplicity.
*/
typedef AudioComponentPlugInInterface *  (*AudioComponentFactoryFunction)(const AudioComponentDescription *inDesc);

//=====================================================================================================================
#pragma mark Functions

#ifdef __cplusplus
extern "C" {
#endif

/*!
    @function       AudioComponentFindNext
    @abstract       Finds an audio component.
    @discussion     This function is used to find an audio component that is the closest match
                    to the provided values.
    @param          inComponent
                        If NULL, then the search starts from the beginning until an audio
                        component is found that matches the description provided by inDesc.
                        If non-NULL, then the search starts (continues) from the previously
                        found audio component specified by inComponent, and will return the next
                        found audio component.
    @param          inDesc
                        The type, subtype and manufacturer fields are used to specify the audio
                        component to search for. A value of 0 (zero) for any of these fields is
                        a wildcard, so the first match found is returned.
    @result         An audio component that matches the search parameters, or NULL if none found.
*/
extern AudioComponent 
AudioComponentFindNext (    AudioComponent                      inComponent, 
                            const AudioComponentDescription *   inDesc) 
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentCount
    @abstract       Counts audio components.
    @discussion     Returns the number of AudioComponents that match the specified
                    AudioComponentDescription.
    @param          inDesc
                        The type, subtype and manufacturer fields are used to specify the audio
                        components to count A value of 0 (zero) for any of these fields is a
                        wildcard, so will match any value for this field
    @result         a UInt32. 0 (zero) means no audio components were found that matched the
                    search parameters.
*/
extern UInt32
AudioComponentCount (   const AudioComponentDescription *       inDesc)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentCopyName
    @abstract       Retrieves the name of an audio component.
    @discussion     the name of an audio component
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outName
                        a CFString that is the name of the audio component. This string should
                        be released by the caller.
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentCopyName (    AudioComponent                      inComponent, 
                            CFStringRef *                       outName)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentGetDescription
    @abstract       Retrieve an audio component's description.
    @discussion     This will return the fully specified audio component description for the
                    provided audio component.
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outDesc
                        the audio component description for the specified audio component
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentGetDescription(   AudioComponent                  inComponent,
                                AudioComponentDescription *     outDesc)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentGetVersion
    @abstract       Retrieve an audio component's version.
    @discussion
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outVersion
                        the audio component's version in the form of 0xMMMMmmDD (Major, Minor, Dot)
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentGetVersion(   AudioComponent                      inComponent, 
                            UInt32 *                            outVersion)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentInstanceNew
    @abstract       Creates an audio component instance.
    @discussion     This function creates an instance of a given audio component. The audio
                    component instance is the object that does all of the work, whereas the
                    audio component is the way an application finds and then creates this object
                    to do this work. For example, an audio unit is a type of audio component
                    instance, so to use an audio unit, one finds its audio component, and then
                    creates a new instance of that component. This instance is then used to
                    perform the audio tasks for which it was designed (process, mix, synthesise,
                    etc.).
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outInstance
                        the audio component instance
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentInstanceNew(      AudioComponent                  inComponent, 
                                AudioComponentInstance *        outInstance)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentInstanceDispose
    @abstract       Disposes of an audio component instance.
    @discussion     This function will dispose the audio component instance that was created
                    with the New call. It will deallocate any resources that the instance was using.
    @param          inInstance
                        the audio component instance to dispose (must not be NULL)
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentInstanceDispose(  AudioComponentInstance          inInstance)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// retrieves the class object associated with the instance
/*!
    @function       AudioComponentInstanceGetComponent
    @abstract       Retrieve the audio component from its instance
    @discussion     Allows the application at any time to retrieve the audio component that is
                    the factory object of a given instance (i.e., the audio component that was
                    used to create the instance in the first place). This allows the application
                    to retrieve general information about a particular audio component (its
                    name, version, etc) when one just has an audio component instance to work
                    with
    @param          inInstance
                        the audio component instance (must not be NULL, and instance must be valid - that is, not disposed)
    @result         a valid audio component or NULL if no component was found.
*/
extern AudioComponent 
AudioComponentInstanceGetComponent (    AudioComponentInstance      inInstance)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentInstanceCanDo
    @discussion     Determines if an audio component instance implements a particular component
                    API call as signified by the specified selector identifier token.
    @param          inInstance
                        the audio component instance
    @param          inSelectorID
                        a number to signify the audio component API (component selector) as appropriate for the instance's component type.
    @result         a boolean
*/
extern Boolean 
AudioComponentInstanceCanDo (   AudioComponentInstance              inInstance, 
                                SInt16                              inSelectorID)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_3_0);


/*!
    @function       AudioComponentRegister
    @abstract       Dynamically registers an AudioComponent within the current process
    @discussion
        AudioComponents are registered either when found in appropriate bundles in the filesystem,
        or via this call. AudioComponents registered via this call are available only within
        the current process.
    
    @param          inDesc
                        the AudioComponentDescription
    @param          inName
                        the AudioComponent's name
    @param          inVersion
                        the AudioComponent's version
    @param          inFactory
                        an AudioComponentFactoryFunction which will create instances of your
                        AudioComponent
    @result         an AudioComponent object
*/
extern AudioComponent
AudioComponentRegister(     const AudioComponentDescription *   inDesc,
                            CFStringRef                         inName,
                            UInt32                              inVersion,
                            AudioComponentFactoryFunction       inFactory)
                                                    __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_NA);

#ifdef __cplusplus
}
#endif


#endif // __AUDIOCOMPONENT_H__
