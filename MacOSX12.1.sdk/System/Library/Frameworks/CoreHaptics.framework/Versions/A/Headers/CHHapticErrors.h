/*==================================================================================================
 File:       CHHapticErrors.h
 
 Contains:   Definitions for error codes returned by the CoreHaptics API.
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#define CH_EXPORT __attribute__((visibility("default"))) extern

#import <Foundation/NSError.h>

/*! @enum CHHapticErrorCode
	@abstract
		Error codes that may be returned from CHHapticEngine methods,
		e.g. `initAndReturnError:`, `startAndReturnError:` and others.
	@discussion
		Note that this is not a comprehensive list, and the underlying components could
		return other error codes (e.g. see kAudioUnitErr_* in AudioToolbox/AUComponent.h) from these
		methods as applicable.
 
	@constant	CHHapticErrorCodeEngineNotRunning
		Pattern playback was requested when the CHHapticEngine was not running.
 
	@constant	CHHapticErrorCodeOperationNotPermitted
		The requested operation cannot be performed in the current state.
 
	@constant	CHHapticErrorCodeEngineStartTimeout
		The haptic engine timed out while starting.
 
	@constant	CHHapticErrorCodeNotSupported
		The haptic engine is not supported by this hardware.
 
	@constant	CHHapticErrorCodeServerInitFailed
		The haptic server failed to initialize.
 
	@constant	CHHapticErrorCodeServerInterrupted
		The connection to the haptic server was lost.
 
	@constant	CHHapticErrorCodeInvalidPatternPlayer
		The current pattern player is invalid due to a server error.
 
	@constant	CHHapticErrorCodeInvalidPatternData
		The data handed to the pattern player was corrupt.

	@constant	CHHapticErrorCodeInvalidPatternDictionary
		The pattern dictionary handed to the pattern player was corrupt.

 	@constant	CHHapticErrorCodeInvalidAudioSession
		The AVAudioSession used to initialize the engine was invalid.

	@constant	CHHapticErrorCodeInvalidEngineParameter
		A configuration parameter used to initialize the engine was invalid.

 	@constant	CHHapticErrorCodeInvalidParameterType
 		A pattern dictionary or parameter array contained an unknown or invalid parameter type.

	@constant	CHHapticErrorCodeInvalidEventType
		A pattern dictionary or event array contained an unknown or invalid event type.

	@constant	CHHapticErrorCodeInvalidEventTime
		A pattern dictionary or event array contained an invalid event time.

	@constant	CHHapticErrorCodeInvalidEventDuration
		A pattern dictionary or event array contained an invalid event duration.
 
 	@constant	CHHapticErrorCodeInvalidAudioResource
 		A pattern dictionary or event array contained a reference to an invalid audio resource.
 
 	@constant	CHHapticErrorCodeResourceNotAvailable
 		The requested operation could not be completed due to a limit on available resources.
 
 	@constant	CHHapticErrorCodeBadEventEntry
 		A pattern dictionary or event array contained a reference to an invalid event entry.
 
 	@constant	CHHapticErrorCodeBadParameterEntry
 		A pattern dictionary or event array contained a reference to an invalid parameter or parameter curve entry.
 
    @constant   CHHapticErrorCodeInvalidTime
        An invalid (e.g., negative) time was passed to a method requiring an NSTimeInterval.
 
    @constant   CHHapticErrorCodeFileNotFound
        An audio or haptic asset could not be found.
 
	@constant	CHHapticErrorCodeInsufficientPower
		The operation failed due to power restrictions.

 	@constant	CHHapticErrorCodeUnknownError
 		An uncategorized error occurred.

	@constant	CHHapticErrorCodeMemoryError
		The operation failed due to lack of memory.
 */

static NSErrorDomain CoreHapticsErrorDomain = @"com.apple.CoreHaptics";
typedef NS_ERROR_ENUM(CoreHapticsErrorDomain, CHHapticErrorCode)
{
	CHHapticErrorCodeEngineNotRunning			= -4805,
	CHHapticErrorCodeOperationNotPermitted		= -4806,
	CHHapticErrorCodeEngineStartTimeout			= -4808,
	CHHapticErrorCodeNotSupported				= -4809,
	CHHapticErrorCodeServerInitFailed			= -4810,
	CHHapticErrorCodeServerInterrupted			= -4811,
    CHHapticErrorCodeInvalidPatternPlayer		= -4812,
	CHHapticErrorCodeInvalidPatternData			= -4813,
	CHHapticErrorCodeInvalidPatternDictionary	= -4814,
	CHHapticErrorCodeInvalidAudioSession		= -4815,
	CHHapticErrorCodeInvalidEngineParameter		= -4816,

    CHHapticErrorCodeInvalidParameterType       = -4820,
    CHHapticErrorCodeInvalidEventType           = -4821,
    CHHapticErrorCodeInvalidEventTime           = -4822,
    CHHapticErrorCodeInvalidEventDuration       = -4823,
	CHHapticErrorCodeInvalidAudioResource		= -4824,
	CHHapticErrorCodeResourceNotAvailable		= -4825,

    CHHapticErrorCodeBadEventEntry              = -4830,
    CHHapticErrorCodeBadParameterEntry          = -4831,
    
    CHHapticErrorCodeInvalidTime                = -4840,
    
    CHHapticErrorCodeFileNotFound               = -4851,
    
	CHHapticErrorCodeInsufficientPower			= -4897,
	CHHapticErrorCodeUnknownError				= -4898,
	CHHapticErrorCodeMemoryError				= -4899
} API_AVAILABLE(ios(13.0), macos(10.15),tvos(14.0));
