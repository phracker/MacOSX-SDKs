//
//  PHASEEngine.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//


#import <PHASE/PHASESoundEventNodes.h>
#import <PHASE/PHASEAssetRegistry.h>
#import <PHASE/PHASEDucker.h>
#import <PHASE/PHASEGroupPreset.h>
#import <PHASE/PHASEMedium.h>
#import <PHASE/PHASEObject.h>
#import <PHASE/PHASESoundEvent.h>
#import <PHASE/PHASETypes.h>
#import <AVFAudio/AVAudioFormat.h>

NS_ASSUME_NONNULL_BEGIN


/****************************************************************************************************/
/*!
    @interface PHASEEngine
    @abstract PHASE engine instance.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEEngine : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithUpdateMode:
    @abstract Initialize a new engine with an update mode.
    @param updateMode
        Defines how the engine will be updated.
*/
- (instancetype)initWithUpdateMode:(PHASEUpdateMode)updateMode NS_DESIGNATED_INITIALIZER;

/*!
    @method startAndReturnError:
    @abstract Start or resume the engine.
    @return
        YES for success.
*/
- (BOOL)startAndReturnError:(NSError**)error;

/*!
    @method pause
    @abstract Pause the engine.
*/
- (void)pause;

/*!
    @method stop
    @abstract Stop the engine.
*/
- (void)stop;

/*!
    @method update:
    @abstract Manually update the engine instance on the calling thread.
    @discussion
        This will kick off all of the API commands called since the last call to update,
        update any systems and objects that need to be kept current, and call any registered handlers.
    @note
        This function has no effect if the engine's update mode is PHASEUpdateModeAutomatic.
*/
- (void)update;

/*!
    @property outputSpatializationMode
    @discussion
        When set to a value other than PHASESpatializationModeAutomatic,
        overrides the default output spatializer and uses the specified one instead.
*/
@property(nonatomic, assign) PHASESpatializationMode outputSpatializationMode;

/*!
    @property renderingState
    @abstract The engine's current rendering state.
*/
@property(nonatomic, readonly) PHASERenderingState renderingState;

/*!
    @property rootObject
    @abstract The root object of the engine's scene graph.
    @discussion
        Attach objects to the engine's rootObject or one of its children to make them active within the engine's scene graph.
        This will ensure they take part in the simulation.
    @note
        The rootObject is created and owned by the engine.
        The rootObject may not be set as the child of another object. This will cause an error to be thrown.
        The rootObject's transform may not be changed. This will cause an error to be thrown.
        The rootObject may not be copied. This will cause an error to be thrown.
 */
@property(nonatomic, readonly, strong) PHASEObject* rootObject;

/*!
    @property defaultMedium
    @abstract The default medium in the engine.
    @discussion
        The default value is PHASEMediumPresetAir.
*/
@property(nonatomic, strong) PHASEMedium* defaultMedium;

/*!
    @property defaultReverbPreset
    @abstract The default reverb preset in the engine.
    @discussion
        The default value is PHASEReverbPresetNone.
*/
@property(nonatomic, assign) PHASEReverbPreset defaultReverbPreset;

/*!
    @property unitsPerSecond
    @abstract The number of units in a second.
    @discussion
        The unitsPerSecond is used internally to scale time/duration values passed to the API.
        This allows clients to pass time/duration values in their own native time scale.
    @note
        Values are clamped to the range (0, inf]. Default value is 1.
*/
@property(nonatomic, assign) double unitsPerSecond;

/*!
    @property unitsPerMeter
    @abstract The number of units in a meter.
    @discussion
        The unitsPerMeter is used internally to scale metric values passed to the API.
        This allows clients to pass metric values in their own native spatial scale.
    @note
        Values are clamped to the range (0, inf]. Default value is 1.
*/
@property(nonatomic, assign) double unitsPerMeter;

/*!
    @property assetRegistry
    @abstract A registry for assets available to the engine
*/
@property(nonatomic, readonly, strong) PHASEAssetRegistry* assetRegistry;

/*!
    @property soundEvents
    @abstract An array of the active sound event objects in the system
    @discussion Returns a dictionary of the sound events at the time it is retrieved. This includes all sound events that are registered with the engine, including those that are preparing, playing, paused or stopping.
*/
@property(nonatomic, readonly, copy) NSArray<PHASESoundEvent*>* soundEvents;

/*!
    @property groups
    @abstract A dictionary of the groups in the system
    @discussion Returns a dictionary of the groups at the time it is retrieved.
*/
@property(nonatomic, readonly, copy) NSDictionary<NSString*, PHASEGroup*>* groups;

/*!
    @property duckers
    @abstract An array of the ducker objects in the system
    @discussion Returns a dictionary of the ducker objects at the time it is retrieved.
*/
@property(nonatomic, readonly, copy) NSArray<PHASEDucker*>* duckers;

/*!
    @property activeGroupPreset
    @abstract The active group mixer preset in the system
    @discussion Returns nil if there are no active group presets in the engine. Activate or Deactivate the preset via [PHASEGroupPreset activate] and [PHASEGroupPreset deactivate]
*/
@property(nonatomic, readonly, strong, nullable) PHASEGroupPreset* activeGroupPreset;

@end  // PHASEEngine

NS_ASSUME_NONNULL_END
