/*==================================================================================================
 File:       CHHapticEngine.h
 
 Contains:   API for CHHapticEngine
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSObjCRuntime.h>
#import <CoreHaptics/CHHapticEvent.h>
#import <CoreHaptics/CHHapticPatternPlayer.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

/*! @define CHHapticTimeImmediate
    @abstract
        A floating point constant representing the time "as soon as possible". This time value should be used
        whenever an app wishes to schedule a command at the soonest possible moment without the need to
        synchronize with other media.
 */
#define CHHapticTimeImmediate (NSTimeInterval)0.0f

@class CHHapticPattern;
@class AVAudioSession;
@protocol CHHapticDeviceCapability;

/*!	@typedef CHHapticCompletionHandler
	@abstract
		A block which is called asynchronously when a call to start or stop the haptic engine completes.
	@param error
		If the call fails, this is set to a valid NSError describing the error.
	@discussion
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef void (^CHHapticCompletionHandler)(NSError *_Nullable error);

/*!	@enum CHHapticEngineFinishedAction
	@abstract
		Constants indicating what the engine should do in response to the finished handler being called.

	@constant	CHHapticEngineFinishedActionStopEngine
 		Stop the engine.  This is useful if the client knows that the client is about to go inactive.
 
	@constant	CHHapticEngineFinishedActionLeaveEngineRunning
 		Do not stop the engine.  This is useful if the client expects more activity.
 */
typedef NS_ENUM(NSInteger, CHHapticEngineFinishedAction) {
	CHHapticEngineFinishedActionStopEngine	= 1,
	CHHapticEngineFinishedActionLeaveEngineRunning	= 2
};

/*!	@typedef CHHapticEngineFinishedHandler
	@abstract
		A block which is called asynchronously when the engine detects that all active pattern players have finished.  The
 		return value tells the system what action to take as a result of this (see `CHHapticEngineFinishedAction`).
	@param error
		If the engine detects the players have stopped due to an error, this is set to a valid NSError describing the error.
	@discussion
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef CHHapticEngineFinishedAction (^CHHapticEngineFinishedHandler)(NSError *_Nullable error) CF_SWIFT_BRIDGED_TYPEDEF;

/*!	@enum CHHapticEngineStoppedReason
 	@abstract
 		Constants indicating the reason why the CHHapticEngine has stopped.
 
 	@constant	CHHapticEngineStoppedReasonAudioSessionInterrupt
		The AVAudioSession bound to this engine has been interrupted.
 
 	@constant	CHHapticEngineStoppedReasonApplicationSuspended
 		The application owning this engine has been suspended (i.e., put into the background).
 
	@constant	CHHapticEngineStoppedReasonIdleTimeout
		The engine has stopped due to an idle timeout when the engine's `autoShutdownEnabled` property was set to YES.
 
	@constant	CHHapticEngineStoppedReasonNotifyWhenFinished
 		The engine has stopped due to a call to a `CHHapticEngineFinishedHandler` returning `CHHapticEngineFinishedActionStopEngine`.
 
    @constant    CHHapticEngineStoppedReasonEngineDestroyed
        The engine has stopped because the CHHapticEngine instance was destroyed.

    @constant    CHHapticEngineStoppedReasonGameControllerDisconnect
        The engine has stopped because the Game Controller associated with this engine disconnected.

 	@constant	CHHapticEngineStoppedReasonSystemError
 		An error has occurred.
 */

typedef NS_ENUM(NSInteger, CHHapticEngineStoppedReason) {
	CHHapticEngineStoppedReasonAudioSessionInterrupt	= 1,
	CHHapticEngineStoppedReasonApplicationSuspended		= 2,
	CHHapticEngineStoppedReasonIdleTimeout				= 3,
	CHHapticEngineStoppedReasonNotifyWhenFinished		= 4,
    CHHapticEngineStoppedReasonEngineDestroyed          = 5,
    CHHapticEngineStoppedReasonGameControllerDisconnect = 6,
	CHHapticEngineStoppedReasonSystemError				= -1
};

/*!	@typedef CHHapticEngineStoppedHandler
	@abstract
		A block which is called asynchronously when the engine has stopped due to external causes such as
 		an audio session interruption or autoShutdown.
	@param stoppedReason
		This constant indicates the reason why the engine stopped.
	@discussion
		This handler is NOT called if the client directly calls stopWithCompletionHandler:.
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef void (^CHHapticEngineStoppedHandler)(CHHapticEngineStoppedReason stoppedReason);

/*!	@typedef CHHapticEngineResetHandler
	@abstract
		A block which is called asynchronously if the haptic engine has reset itself due a server failure.
	@discussion
		In response to this handler, the app must reload all custom audio resources and recreate all necessary
		pattern players.  The engine must of course be restarted.  CHHapticPatterns do not need to be re-created.
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef void (^CHHapticEngineResetHandler)(void);

/*!	@class CHHapticEngine
	@abstract
		Represents the connection with the haptic server.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos)
@interface CHHapticEngine : NSObject

/*! @method capabilitiesForHardware
 	@abstract
 		Get the protocol that describes haptic and audio capabilities on this device.
 	@discussion
 		Detailed description on the capability protocol is in CHHapticDeviceCapability.h.
 */
+ (id<CHHapticDeviceCapability>)capabilitiesForHardware;

/*!	@property currentTime
		The absolute time from which all current and future event times may be calculated.
		The units are seconds.
 */
@property (readonly) NSTimeInterval currentTime;

/*!	@property stoppedHandler
	@abstract
		The engine will call this block when it has stopped due to external causes (such as
		an audio session interruption or the app going into the background).  It will NOT be called
 		if the client calls stopWithCompletionHandler:.
	@discussion
		In general, callbacks arrive on a non-main thread and it is the client's responsibility to handle
		it in a thread-safe manner.
 */

@property (readwrite,atomic) CHHapticEngineStoppedHandler stoppedHandler;

/*!	@property resetHandler
	@abstract
		This block will called asynchronously if the haptic engine has to reset itself after a server failure.
	@discussion
 		In response to this handler being called, the client must release all haptic pattern players
 		and recreate them.  All CHHapticPattern objects and CHHapticEngine properties will have been preserved.
 		In general, callbacks arrive on a non-main thread and it is the client's responsibility to handle
		it in a thread-safe manner.
 */
@property (readwrite,atomic) CHHapticEngineResetHandler resetHandler;

/*!	@property playsHapticsOnly
		If set to YES, the CHHapticEngine will ignore all events of type CHHapticEventTypeAudio and play only haptic events.
	@discussion
		This behavior change will only take effect after the engine is stopped and restarted.
		The default is NO.
 */
@property (readwrite,nonatomic) BOOL playsHapticsOnly;

/*!	@property isMutedForAudio
 		When set to YES, the CHHapticEngine mutes audio playback from its players.
 	@discussion
 		Default is NO.
 */
@property (readwrite,nonatomic) BOOL isMutedForAudio;

/*!	@property isMutedForHaptics
 		When set to YES, the CHHapticEngine mutes haptic playback from its players.
 	@discussion
 		Default is NO.
 */
@property (readwrite,nonatomic) BOOL isMutedForHaptics;

/*! @property autoShutdownEnabled
	@abstract
		When auto shutdown is enabled, the haptic engine can start and stop the hardware dynamically,
		to conserve power.
	@discussion
		To conserve power, it is advised that the client stop the haptic engine when not in use.
		But when auto shutdown is enabled, the haptic engine will stop the hardware if it was running
		idle for a certain duration, and restart it later when required.
		Note that, because this operation is dynamic, it may affect the start times of the pattern players
		(e.g. `CHHapticPatternplayer`), if the engine has to resume from its shutdown state.

		This feature is disabled by default, but the client can enable it if needed.
 */
@property (nonatomic, getter=isAutoShutdownEnabled) BOOL autoShutdownEnabled;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initAndReturnError:
	@abstract
		Create an instance of the CHHapticEngine.
	@discussion
		More than one instance may exist within a process.  Each will function independently of the others.
 		CHHapticEngines created using this method will be associated with the device's internal haptics hardware system,
 		if one exists.  For systems without internal haptics, this method will fail with the error `CHHapticErrorCodeNotSupported`.
 		To access engine instances associated with external game controllers, see the GameController framework documentation
 		for the `hapticEngines` property on the GCController class.
 */
- (nullable instancetype)initAndReturnError:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*! @method initWithAudioSession:error
	@abstract
		Create an instance of an CHHapticEngine and associate it with an audio session.  If 'audioSession' is nil,
 		the engine will create its own.
	@discussion
		More than one instance may exist within a process.  Each will function independently of the others, but all
 		CHHapticEngines which share an audio session will have identical audio behavior with regard to interruptions, etc.
 		CHHapticEngines created using this method will be associated with the device's internal haptics hardware system,
 		if one exists.  For systems without internal haptics, this method will fail with the error `CHHapticErrorCodeNotSupported`.
 		To access engine instances associated with external game controllers, see the GameController framework documentation
 		for the `hapticEngines` property on the GCController class.
 */
- (nullable instancetype)initWithAudioSession:(nullable AVAudioSession *)audioSession error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*! @method startWithCompletionHandler:
	@abstract
		Asynchronously start the engine. The handler will be called when the operation completes.
 	@discussion
 		The handler is guaranteed to be called on either success or failure.
 */
- (void)startWithCompletionHandler:(CHHapticCompletionHandler _Nullable)completionHandler;

/*! @method startAndReturnError:
	@abstract
		Start the engine and block until the engine has started.
 	@discussion
 		This method will return NO upon failure, and outError will be set to a valid NSError describing the error.
 */
- (BOOL)startAndReturnError:(NSError **)outError;

/*! @method stopWithCompletionHandler:
	@abstract
		Asynchronously stop the engine.  The handler will be called when the operation completes.
	@discussion
		The handler is guaranteed to be called on either success or failure.
 */
- (void)stopWithCompletionHandler:(CHHapticCompletionHandler _Nullable)completionHandler;

/*!	@method notifyWhenPlayersFinished:
 	@abstract
 		Tell the engine to asynchronously call the passed-in handler when all active pattern players associated
 		with this engine have stopped.
 	@param finishedHandler
 		The block that will be called asynchronously.  The return value of this block determines the action the
 		engine will take when the block finishes (see `CHHapticEngineFinishedHandler`).
 	@discussion
 		If additional players are started after this call is made, they will delay the callback.
 		If no players are active or the engine is stopped, the callback will happen immediately.
 */
- (void)notifyWhenPlayersFinished:(CHHapticEngineFinishedHandler)finishedHandler;

/*! @method createPlayerWithPattern:error
	@abstract
		Factory method for creating a CHHapticPatternPlayer from a CHHapticPattern.
	@param pattern
		The pattern to be played.
 */
- (nullable id<CHHapticPatternPlayer>)createPlayerWithPattern:(CHHapticPattern *)pattern
																	error:(NSError **)outError;

/*! @method createAdvancedPlayerWithPattern:error
	@abstract
		Factory method for creating a CHHapticAdvancedPatternPlayer from a CHHapticPattern.
	@param pattern
		The pattern to be played.
 */
- (nullable id<CHHapticAdvancedPatternPlayer>)createAdvancedPlayerWithPattern:(CHHapticPattern *)pattern
																		error:(NSError **)outError;

/*! @method registerAudioResource:options:error
	@abstract
		Register an external audio file for use as a custom waveform.
	@param resourceURL
 		A URL referencing the location of the audio file to be registered.
 	@param options
 		A dictionary containing key/value pairs describing how this resource should be played.
 	@param outError
 		If register operation fails, this will be set to a valid NSError describing the error.
 */
- (CHHapticAudioResourceID)registerAudioResource:(NSURL *)resourceURL
										 options:(NSDictionary *)options
										   error:(NSError **)outError __attribute__((swift_error(zero_result)));

/*!	@method unregisterAudioResource:error
 	@abstract
 		Unregister and remove a previously-registered audio resource.
 	@param resourceID
 		The resource ID that was returned when the resource was registered.
 	@param outError
 		If the unregister operation fails, this will be set to a valid NSError describing the error.
 */
- (BOOL)unregisterAudioResource:(CHHapticAudioResourceID)resourceID
						  error:(NSError **)outError;

/*! @method playPatternFromURL:error
	@abstract
		Simple one-shot call to play a pattern specified by a URL.
 	@param fileURL
 		The URL of the file containing a haptic/audio pattern dictionary.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		The engine should be started prior to calling this method if low latency is desired. If this is not done,
 		this method will start it, which can cause a significant delay.
 */
- (BOOL)playPatternFromURL:(NSURL *)fileURL
					 error:(NSError **)outError;

/*! @method playPatternFromData:error
 	@abstract
 		Simple one-shot call to play a pattern specified by NSData.
	@param data
 		The NSData containing a haptic/audio pattern dictionary.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		The engine should be started prior to calling this method if low latency is desired. If this is not done,
 		this method will start it, which can cause a significant delay.
 */
- (BOOL)playPatternFromData:(NSData *)data
					  error:(NSError **)outError;

@end

NS_ASSUME_NONNULL_END
