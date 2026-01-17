/*==================================================================================================
 File:       CHHapticPattern.h
 
 Contains:   API for creating haptic patterns
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

@class CHHapticEvent;
@class CHHapticDynamicParameter;
@class CHHapticParameterCurve;

/*! @enum CHHapticPatternKey
	@abstract
		Keys used to define a CHHapticPattern.
 
	@discussion
		A definition for a haptic pattern consists of a heirarchical set of key/value pairs, starting at the topmost level with
		a "Version" and a "Pattern" key.  This marks the beginning of an array of event (CHHapticPatternKeyEvent) and parameter
 		(CHHapticPatternKeyParameter) definitions.  Each of these has an associated time which indicates when the event or parameter
 		will be delivered to the haptic engine.
 
	@constant   CHHapticPatternKeyVersion
		Indicates the version of the system for which the pattern was authored.
 		Value type: Real.

	@constant   CHHapticPatternKeyPattern
		Indicates the beginning of a haptic pattern definition.
 		Value type: Array.
 
	@constant   CHHapticPatternKeyEvent
		Indicates the beginning of a haptic event definition, which will include an event type, a time, and an optional set
		of event parameters (CHHapticPatternKeyEventParameters).
 		Value type: Dictionary.
 
	@constant   CHHapticPatternKeyEventType
		The type of haptic or audio event.
 		Value type: NSString (CHHapticEventType).
 
 	@constant	CHHapticPatternKeyEventDuration
 		The duration in seconds for an event.
		Value type: Real.

	@constant   CHHapticPatternKeyEventParameters
		Indicates the beginning of an array of event parameter (CHHapticPatternKeyParameter) definitions for a specific event.
 		Value type: Array.
 
	@constant	CHHapticPatternKeyParameter
		Indicates the beginning of a parameter definition, which will include a parameter type and value, and a time.
 		Value type: Dictionary.
 
	@constant	CHHapticPatternKeyParameterID
		The ID of the parameter.
		Value type: NSString (CHHapticEventParameterID for event parameters and CHHapticDynamicParameterID for dynamic parameters).

	@constant	CHHapticPatternKeyParameterValue
		The value of the parameter.  The range will vary with the parameter.
		Value type: Real.

	@constant	CHHapticPatternKeyTime
		The relative time for any event or parameter.  Units are seconds.
		Value type: Real.

	@constant   CHHapticPatternKeyEventWaveformPath
		For events of type CHHapticEventTypeAudioCustom, the path to the local file containing the audio waveform.
		Value type: NSString.
 */

typedef NSString *CHHapticPatternKey NS_TYPED_ENUM;

CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyVersion API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyPattern API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEvent  API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventType API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventDuration API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventWaveformPath API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventParameters API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameter API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterID API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterValue API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterCurve API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterCurveControlPoints API_AVAILABLE(ios(13.0), macos(10.15));

/*!	@class CHHapticPattern
	@abstract
		A set of one or more haptic events and/or Dynamic parameters/parameter curves.
	@discussion
		The passed-in arrays' contents are not owned by the pattern object.  Changes made to those arrays
		after a CHHapticPattern object is created have no effect on that object.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticPattern : NSObject

/*!	@property duration
		Pattern duration is calculated as the start time of the pattern's last event or parameter, plus that event's duration if present.
 */
@property (readonly,nonatomic) NSTimeInterval duration;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithEvents:parameters:error
	@abstract
		Initialize a new CHHapticPattern.
	@param events
		An NSArray of CHHapticEvents.  Can be empty.
	@param parameters
		An NSArray of CHHapticDynamicParameters.  Can be empty.
 */
- (nullable instancetype) initWithEvents:(NSArray<CHHapticEvent *> *)events
							  parameters:(NSArray<CHHapticDynamicParameter *> *)parameters
								   error:(NSError **)outError;

/*! @method initWithEvents:parameterCurves:error
 	@abstract
 		Initialize a new CHHapticPattern with parameters modulated by parameter curves.
 	@param events
 		An NSArray of CHHapticEvents.  Can be empty.
 	@param parameterCurves
 		An NSArray of CHHapticParameterCurves.  Can be empty.
 */
- (nullable instancetype) initWithEvents:(NSArray<CHHapticEvent *> *)events
						 parameterCurves:(NSArray<CHHapticParameterCurve *> *)parameterCurves
								   error:(NSError **)outError;

/*! @method initWithDictionary:error
	@abstract
		Initialize a new CHHapticPattern using the passed-in NSDictionary.
	@param patternDict
		NSDictionary containing a pattern property list.
 */
- (nullable instancetype)initWithDictionary:(NSDictionary<CHHapticPatternKey, id> *)patternDict
									  error:(NSError **)outError;

/*! @method exportDictionaryAndReturnError:error
    @abstract
        Returns a NSDictionary representation of the contents of the pattern.
    @discussion
        Patterns containing custom audio resource IDs cannot be exported and will return nil
        with the error code set to CHHapticErrorCodeOperationNotPermitted.
 */
- (nullable NSDictionary<CHHapticPatternKey, id> *) exportDictionaryAndReturnError:(NSError **)outError  __attribute__((swift_error(null_result)));

@end

NS_ASSUME_NONNULL_END

