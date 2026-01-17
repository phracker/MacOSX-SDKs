/*==================================================================================================
 File:       CHHapticDeviceCapability.h
 
 Contains:   API for determining haptic and audio capabilities of the current device.
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <CoreHaptics/CHHapticParameter.h>
#import <CoreHaptics/CHHapticEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*!	@protocol CHHapticParameterAttributes
 	@abstract
 		A protocol for querying mininum, maximum, and default values for a CHHapticEventParameter or CHHapticDynamicParameter.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos)
@protocol CHHapticParameterAttributes <NSObject>

/*! @property minValue
 	@abstract
 		The minimum value for the parameter.
 */
@property (readonly) float minValue;

/*! @property maxValue
 	@abstract
 		The maximum value for the parameter.
 */
@property (readonly) float maxValue;

/*! @property maxValue
 	@abstract
 		The default value for the parameter.
 */
@property (readonly) float defaultValue;

@end

/*!	@protocol CHHapticDeviceCapability
	@abstract
		A protocol which defines properties describing haptics and audio capabilities for a particular device.
		These properties include limitations and ranges of parameters.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos)
@protocol CHHapticDeviceCapability

/*! @property supportsHaptics
	@abstract
		Returns YES if the hardware supports haptic event playback.
 */
@property (readonly) BOOL supportsHaptics;

/*! @property supportsAudio
	@abstract
		Returns YES if the hardware supports audio event playback.
 */
@property (readonly) BOOL supportsAudio;

/*! @method attributesForEventParameter:
 	@abstract
 		Return information about the given CHHapticEventParameter as it applies to the specified event type.
 	@param inParameter
 		A CHHapticEventParameter to be queried.
 	@param type
 		A CHHapticEventType to be queried.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		These values may vary across different device types.
 */
- (nullable id<CHHapticParameterAttributes>) attributesForEventParameter:(CHHapticEventParameterID)inParameter
															   eventType:(CHHapticEventType)type
																   error:(NSError**)outError;

/*! @method attributesForEventParameter:
 	@abstract
 		Return information about the given CHHapticDynamicParameter.
 	@param inParameter
 		A CHHapticDynamicParameter to be queried.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		These values may vary across different device types.
 */
- (nullable id<CHHapticParameterAttributes>) attributesForDynamicParameter:(CHHapticDynamicParameterID)inParameter
																	 error:(NSError**)outError;
@end

NS_ASSUME_NONNULL_END
