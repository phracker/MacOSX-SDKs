//
//  PHASETypes.h
//  PHASE
//
//  Copyright © 2021 Apple. All rights reserved.
//

#ifndef PHASETypes_h
#define PHASETypes_h

#import <Foundation/Foundation.h>

/*!
    @enum PHASEUpdateMode
    @abstract Update mode for the engine.
    @discussion
        The engine update mode determines the rate at which the engine consumes client commands, performs internal updates, and calls any registered handlers.
        All API calls to the engine are queued until the engine updates.
        The engine update mode determines if the engine or the application triggers the consumption of API commands.
    @note
        The update mode does not affect the Audio IO Thread or rendering, in general. The Audio IO Thread always runs in the background, independent of the update mode.
    @constant PHASEUpdateModeAutomatic
        The engine will internally consume client commands at a rate opaque to the client.
        In general, automatic update mode is meant for simpler applications that just want to play sounds, without having to maintain a strict update loop.
        Due to the fact that the engine consumes client commands at its own internal rate, the client is never guaranteed that two independent commands will synchronize.
    @constant PHASEUpdateModeManual
        When an application requires precise synchronization of API calls with the main update, manual mode is the best choice.
        In this mode, clients will need to call [PHASEEngine update] periodically to process new commands, perform internal updates, and receive callbacks.
        The rate at which the client calls update should at least match the rate at which other time-critical subsystems are updated, such graphics rendering etc.
        API calls between calls to [PHASEEngine update] are guaranteed to be synchronized.
        For example, the client can move two sources into place, request to start two sound events (one per source), then call [PHASEEngine update].
        These calls will be guaranteed to be processed at the same time.
*/

typedef NS_ENUM(NSInteger, PHASEUpdateMode) {
    PHASEUpdateModeAutomatic = 0,
    PHASEUpdateModeManual = 1,
}
NS_SWIFT_NAME(PHASEEngine.UpdateMode);

/*!
    @enum PHASERenderingState
    @abstract Rendering state for sound events.
    @constant PHASERenderingStateStopped
        The sound event is stopped.
    @constant PHASERenderingStateStarted
        The sound event is playing back.
    @constant PHASERenderingStatePaused
        The sound event is paused.
*/
typedef NS_ENUM(NSInteger, PHASERenderingState) {
    PHASERenderingStateStopped = 0,
    PHASERenderingStateStarted = 1,
    PHASERenderingStatePaused = 2,
}
NS_SWIFT_NAME(PHASESoundEvent.RenderingState);

/*!
    @enum PHASESpatializationMode
    @abstract Spatialization mode.
    @constant PHASESpatializationModeAutomatic
        Automatically select the spatialization mode based on the current output device.
    @constant PHASESpatializationModeAlwaysUseBinaural
        Always use binaural rendering, whether playing back on headphones or speakers.
        Note that when rendering binaural over speakers, special filters are applied to achieve the expected behavior.
    @constant PHASESpatializationModeAlwaysUseChannelBased
        Always use the appropriate channel-based panning algorithm for the output layout.
        Note that when rendering channel-based over headphones, the sound will play back in stereo.
*/
typedef NS_ENUM(NSInteger, PHASESpatializationMode) {
    PHASESpatializationModeAutomatic = 0,
    PHASESpatializationModeAlwaysUseBinaural = 1,
    PHASESpatializationModeAlwaysUseChannelBased = 2,
};

/*!
    @enum PHASEReverbPreset
    @abstract Reverb preset
*/
typedef NS_ENUM(NSInteger, PHASEReverbPreset) {
    PHASEReverbPresetNone = 'rNon',
    PHASEReverbPresetSmallRoom = 'rSRm',
    PHASEReverbPresetMediumRoom = 'rMRm',
    PHASEReverbPresetLargeRoom = 'rLR1',
    PHASEReverbPresetLargeRoom2 = 'rLR2',
    PHASEReverbPresetMediumChamber = 'rMCh',
    PHASEReverbPresetLargeChamber = 'rLCh',
    PHASEReverbPresetMediumHall = 'rMH1',
    PHASEReverbPresetMediumHall2 = 'rMH2',
    PHASEReverbPresetMediumHall3 = 'rMH3',
    PHASEReverbPresetLargeHall = 'rLH1',
    PHASEReverbPresetLargeHall2 = 'rLH2',
    PHASEReverbPresetCathedral = 'rCth',
};

/*!
    @const PHASEErrorDomain
    @abstract The NSErrorDomain for general PHASE errors
 */
OS_EXPORT NSErrorDomain const PHASEErrorDomain;

/*!
    @enum PHASEError
    @abstract General PHASE error codes
 */
typedef NS_ERROR_ENUM(PHASEErrorDomain, PHASEError) {
    PHASEErrorInitializeFailed = 'PHEa',
};

/*!
    @const PHASESoundEventErrorDomain
    @abstract The NSErrorDomain for PHASE sound event errors.
 */
OS_EXPORT NSErrorDomain const PHASESoundEventErrorDomain;

/*!
    @enum PHASESoundEventError
    @abstract Sound event error.
 */
typedef NS_ERROR_ENUM(PHASESoundEventErrorDomain, PHASESoundEventError) {
    PHASESoundEventErrorNotFound = 'PHta',
    PHASESoundEventErrorBadData = 'PHtb',
    PHASESoundEventErrorInvalidInstance = 'PHtc',
    PHASESoundEventErrorAPIMisuse = 'PHtd',
    PHASESoundEventErrorSystemNotInitialized = 'PHte',
    PHASESoundEventErrorOutOfMemory = 'PHtf',
};

/*!
    @const PHASEAssetErrorDomain
    @abstract The NSErrorDomain for PHASE Asset errors
 */
OS_EXPORT NSErrorDomain const PHASEAssetErrorDomain;

/*!
    @enum PHASEAssetError
    @abstract Asset error
 */
typedef NS_ERROR_ENUM(PHASEAssetErrorDomain, PHASEAssetError) {
    PHASEAssetErrorFailedToLoad = 'PHaa',
    PHASEAssetErrorInvalidEngineInstance = 'PHab',
    PHASEAssetErrorBadParameters = 'PHac',
    PHASEAssetErrorAlreadyExists = 'PHad',
    PHASEAssetErrorGeneralError = 'PHae',
    PHASEAssetErrorMemoryAllocation = 'PHaf',
};

/*!
    @enum PHASESoundEventPrepareHandlerReason
    @abstract Sound event prepare handler reason
 */
typedef NS_ENUM(NSInteger, PHASESoundEventPrepareHandlerReason) {
    PHASESoundEventPrepareHandlerReasonFailure = 0,
    PHASESoundEventPrepareHandlerReasonPrepared = 1,
    PHASESoundEventPrepareHandlerReasonTerminated = 2,
}
NS_SWIFT_NAME(PHASESoundEvent.PrepareHandlerReason);

/*!
    @enum PHASESoundEventStartHandlerReason
    @abstract Sound event start handler reason
 */
typedef NS_ENUM(NSInteger, PHASESoundEventStartHandlerReason) {
    PHASESoundEventStartHandlerReasonFailure = 0,
    PHASESoundEventStartHandlerReasonFinishedPlaying = 1,
    PHASESoundEventStartHandlerReasonTerminated = 2,
}
NS_SWIFT_NAME(PHASESoundEvent.StartHandlerReason);

/*!
    @enum PHASESoundEventSeekHandlerReason
    @abstract Sound event seek handler reason
 */
typedef NS_ENUM(NSInteger, PHASESoundEventSeekHandlerReason) {
    PHASESoundEventSeekHandlerReasonFailure = 0,
    PHASESoundEventSeekHandlerReasonFailureSeekAlreadyInProgress = 1,
    PHASESoundEventSeekHandlerReasonSeekSuccessful = 2,
}
NS_SWIFT_NAME(PHASESoundEvent.SeekHandlerReason);

/*!
    @enum PHASESoundEventPrepareState
    @abstract Sound event prepare state
 */
typedef NS_ENUM(NSInteger, PHASESoundEventPrepareState) {
    PHASESoundEventPrepareStatePrepareNotStarted = 0,
    PHASESoundEventPrepareStatePrepareInProgress = 1,
    PHASESoundEventPrepareStatePrepared = 2,
}
NS_SWIFT_NAME(PHASESoundEvent.PrepareState);

/*!
    @enum PHASEAssetType
    @abstract Asset types.
    @discussion
        Determines how assets are loaded into memory and prepared for playback.
        'Preparing' an asset for playback may include decompression and/or format conversion,
        depending on the type of the underlying asset data.
    @constant PHASEAssetTypeResident
        If the asset is on disk, it is loaded into memory and prepared for playback.
        If the asset is in memory, it is prepared for playback.
    @constant PHASEAssetTypeStreamed
        If the asset is on disk, it is streamed from disk into memory and prepared during playback.
        If the asset is in memory, it is streamed from memory and prepared during playback.
*/
typedef NS_ENUM(NSInteger, PHASEAssetType) {
    PHASEAssetTypeResident = 0,
    PHASEAssetTypeStreamed = 1,
}
NS_SWIFT_NAME(PHASEAsset.AssetType);

/*!
    @enum PHASECurveType
    @abstract Curve types.
    @constant PHASECurveTypeLinear
        A curve of the form y = x.
    @constant PHASECurveTypeSquared
        A curve of the form y = x^2.
    @constant PHASECurveTypeInverseSquared
        A curve of the form y = 1 / x^2.
    @constant PHASECurveTypeCubed
        A curve of the form y = x^3.
    @constant PHASECurveTypeInverseCubed
        A curve of the form y = 1 / x^3.
    @constant PHASECurveTypeSine
        A sine curve.
    @constant PHASECurveTypeInverseSine
        An inverse sine curve.
    @constant PHASECurveTypeSigmoid
        A sigmoid curve.
        Also known as an s-curve, slow at the ends and quick in the middle.
    @constant PHASECurveTypeInverseSigmoid
        An inverse sigmoid curve.
        Also known as an inverse s-curve, quick at the ends and slow in the middle.
 */
typedef NS_ENUM(NSInteger, PHASECurveType) {
    PHASECurveTypeLinear = 'crLn',
    PHASECurveTypeSquared = 'crSq',
    PHASECurveTypeInverseSquared = 'crIQ',
    PHASECurveTypeCubed = 'crCu',
    PHASECurveTypeInverseCubed = 'crIC',
    PHASECurveTypeSine = 'crSn',
    PHASECurveTypeInverseSine = 'crIS',
    PHASECurveTypeSigmoid = 'crSg',
    PHASECurveTypeInverseSigmoid = 'crIG',
};

/*!
    @enum PHASECullOption
    @abstract Cull option.
    @discussion Determines what the engine should do when a sound asset becomes cullable.
    @constant PHASECullOptionTerminate
        If cullable, the sound asset will stop. Note that this can occur before or during playback.
    @constant PHASECullOptionSleepWakeAtZero
        If cullable, the sound asset will be put to sleep. Upon waking, start playback at the beginning.
    @constant PHASECullOptionSleepWakeAtRandomOffset
        If cullable, the sound asset will be put to sleep. Upon waking, start playback at random offset.
    @constant PHASECullOptionSleepWakeAtRealtimeOffset
        If cullable, the sound asset will be put to sleep. Upon waking, start playback at realtime offset.
    @constant PHASECullOptionDoNotCull
        If cullable, continue playback, even if the sound is inaudible.
*/
typedef NS_ENUM(NSInteger, PHASECullOption) {
    PHASECullOptionTerminate = 0,
    PHASECullOptionSleepWakeAtZero = 1,
    PHASECullOptionSleepWakeAtRandomOffset = 2,
    PHASECullOptionSleepWakeAtRealtimeOffset = 3,
    PHASECullOptionDoNotCull = 4,
};

/*!
    @enum PHASEPlaybackMode
    @abstract Playback mode.
    @constant PHASEPlaybackModeOneShot
        Play the sound asset once, then stop.
    @constant PHASEPlaybackModeLooping
        Loop the sound asset indefinitely.
*/
typedef NS_ENUM(NSInteger, PHASEPlaybackMode) {
    PHASEPlaybackModeOneShot = 0,
    PHASEPlaybackModeLooping = 1,
};

/*!
   @enum PHASENormalizationMode
   @abstract Normalization mode
   @discussion Determines how sound assets are normalized for calibrated loudness on the output device.
   @note In general, clients are advised to normalize sound assets (and streams).
        This will make it easier to mix the content once assigned to a generator with a specified calbration mode and level.
   @constant PHASENormalizationModeNone
        No normalization is applied. In this case, it's advised that the client perform custom normalization.
   @constant PHASENormalizationModeDynamic
        Dynamic Normalization is applied.
 */
typedef NS_ENUM(NSInteger, PHASENormalizationMode) {
    PHASENormalizationModeNone = 0,
    PHASENormalizationModeDynamic = 1,
};

/*!
    @enum PHASECalibrationMode
    @abstract Calibration mode.
    @note In general, clients are advised use a calibrated input mode. Setting the value to PHASECalibrationModeNone is not advised.
    @constant PHASECalibrationModeNone
        Linear gain with no reference (uncailbrated).
    @constant PHASECalibrationModeRelativeSpl
        SPL relative to a device-tuned SPL (when available).
    @constant PHASECalibrationModeAbsoluteSpl
        Absolute SPL. The system will hit the value 'if it can' (depending on the capabilities of the current output device).
*/
typedef NS_ENUM(NSInteger, PHASECalibrationMode) {
    PHASECalibrationModeNone = 0,
    PHASECalibrationModeRelativeSpl = 1,
    PHASECalibrationModeAbsoluteSpl = 2,
};

#endif /* PHASETypes_h */

