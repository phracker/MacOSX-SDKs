/*
    File:       CMIOHardwareControl.h

    Contains:   API for communicating with CoreMediaIO hardware

    Copyright:  © 2005-2011 by Apple Inc., all rights reserved.
*/


#if !defined(__CMIOHardwareControl_h__)
#define __CMIOHardwareControl_h__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Overview
/*!
    @header CMIOHardwareControl
    A CMIOControl provides properties that describe/manipulate a particular aspect of the object such as hue, staturation, data source selection, etc.
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Includes

#include <CoreMediaIO/CMIOHardwareObject.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOControl Types

/*!
    @typedef        CMIOControlID
    @abstract       CMIOControl is the base class for all objects that represent a Control of data on a CMIO device or CMIO stream.
    @discussion     CMIOControl is a subclass of CMIOObject.
*/

typedef CMIOObjectID CMIOControlID;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOControl Constants

/*!
    @enum           CMIOControl Base Class IDs
    @abstract       The CMIOClassIDs that identify the various CMIOControl base classes.
    @discussion     
    @constant       kCMIOControlClassID
                        The CMIOClassID that identifies the CMIOControl class.
    @constant       kCMIOBooleanControlClassID
                        The CMIOClassID that identifies the CMIOBooleanControl class which is a subclass of CMIOControl. CMIOBooleanControls manipulate on/off switches in the
                        hardware.
    @constant       kCMIOSelectorControlClassID
                        The CMIOClassID that identifies the CMIOSelectorControl class which is a subclass of CMIOControl. CMIOSelectorControls manipulate controls that have
                        multiple, but discreet values.
    @constant       kCMIOFeatureControlClassID
                        The CMIOClassID that identifies the CMIOFeatureControl class which is a subclass of CMIOControl. CMIOFeatureControls manipulate various features that
                        might be present on a device, such as hue, saturation, zoom, etc.
*/
enum
{
    kCMIOControlClassID             = 'actl',
    kCMIOBooleanControlClassID      = 'togl',
    kCMIOSelectorControlClassID     = 'slct',
    kCMIOFeatureControlClassID      = 'ftct',
};

/*!
    @enum           CMIOBooleanControl Subclass IDs
    @abstract       The four char codes that identify the various standard subclasses of CMIOBooleanControl.
    @discussion     
    @constant       kCMIOJackControlClassID
                        A CMIOBooleanControl where a true value means something is plugged into that element.
    @constant       kCMIODirectionControlClassID
                        A CMIOBooleanControl where a true value means the element is operating in input mode, and false means the element is operating in output mode.
                        This control is only needed for devices which can do input and output, but not at the same time.
*/
enum
{
    kCMIOJackControlClassID         = 'jack',
    kCMIODirectionControlClassID    = 'dire'
};

/*!
    @enum           CMIOSelectorControl Subclass IDs
    @abstract       The four char codes that identify the various standard subclasses of CMIOSelectorControl.
    @discussion     
    @constant       kCMIODataSourceControlClassID
                        A CMIOSelectorControl that identifies where the data for the element is coming from.
    @constant       kCMIODataDestinationControlClassID
                        A CMIOSelectorControl that identifies where the data for the element is going.
*/
enum
{
    kCMIODataSourceControlClassID       = 'dsrc',
    kCMIODataDestinationControlClassID  = 'dest'
};

/*!
    @enum           CMIOFeatureControl Subclass IDs
    @abstract       The four char codes that identify the various standard subclasses of CMIOFeatureControl.
    @discussion     
    @constant       kCMIOBlackLevelControlClassID
                        A CMIOFeatureControl that controls the black level offset. The units for the control's absolute value are percetage (%).
    @constant       kCMIOWhiteLevelControlClassID
                        A CMIOFeatureControl that controls the white level offset. The units for the control's absolute value are percentage (%).
    @constant       kCMIOHueControlClassID
                        A CMIOFeatureControl that controls the hue offset. Positive values mean counterclockwise, negative values means clockwise on a vector scope. The units for the
                        control's absolute value are degrees (°).
    @constant       kCMIOSaturationControlClassID
                        A CMIOFeatureControl that controls color intensity. For example, at high saturation levels, red appears to be red; at low saturation, red appears as pink. The
                        unit for the control's absolute value is a percentage (%).
    @constant       kCMIOContrastControlClassID
                        A CMIOFeatureControl that controls a the distance bewtween the whitest whites and blackest blacks. The units for the control's absolute value are percentage (%).
    @constant       kCMIOSharpnessControlClassID
                        A CMIOFeatureControl that controls the sharpness of the picture. The units for the control's absolute value are undefined.
    @constant       kCMIOBrightnessControlClassID
                        A CMIOFeatureControl that controls the intensity of the video level. The units for the control's absolute value are percetage (%).
    @constant       kCMIOGainControlClassID
                        A CMIOFeatureControl that controls the amplification of the signal. The units for the control's absolute value are decibels (dB).
    @constant       kCMIOIrisControlClassID
                        A CMIOFeatureControl that controls a mechanical lens iris. The units for the control's absolute value are an F number (F).
    @constant       kCMIOShutterControlClassID
                        A CMIOFeatureControl that controls the integration time of the incoming light. The units for the control's absolute value are seconds (s).
    @constant       kCMIOExposureControlClassID
                        A CMIOFeatureControl that controls a the total amount of light accumulated. The units for the control's absolute value are exposure value (EV).
    @constant       kCMIOWhiteBalanceUControlClassID
                        A CMIOFeatureControl that controls the adjustment of the white color of the picture. The units for the control's absolute value are kelvin (K).
    @constant       kCMIOWhiteBalanceVControlClassID
                        A CMIOFeatureControl that controls a adjustment of the white color of the picture. The units for the control's absolute value are kelvin (K).
    @constant       kCMIOWhiteBalanceControlClassID
                        A CMIOFeatureControl that controls a adjustment of the white color of the picture. The units for the control's absolute value are kelvin (K).
    @constant       kCMIOGammaControlClassID
                        A CMIOFeatureControl that defines the function between incoming light level and output picture level. The units for the control's absolute value are undefined.
    @constant       kCMIOTemperatureControlClassID
                        A CMIOFeatureControl that controls the temperature inside of the device and/or controlling temperature. The units for the control's absolute value are undefined.
    @constant       kCMIOZoomControlClassID
                        A CMIOFeatureControl that controls the zoom. The units for the control's absolute value are power where 1 is the wide end.
    @constant       kCMIOFocusControlClassID
                        A CMIOFeatureControl that controls a focus mechanism. The units for the control's absolute value are meters (m).
    @constant       kCMIOPanControlClassID
                        A CMIOFeatureControl that controls a panning mechanism. Positive values mean clockwise, negative values means counterclockwise. The units for the control's
                        absolute value are degrees (°).
    @constant       kCMIOTiltControlClassID
                        A CMIOFeatureControl that controls a tilt mechanism. Positive values mean updwards, negative values means downwards. The units for the control's absolute value are
                        degrees (°).
    @constant       kCMIOOpticalFilterClassID
                        A CMIOFeatureControl that controls changing the optical filter of camera lens function. The units for the control's absolute value are undefined.
    @constant       kCMIOBacklightCompensationControlClassID
                        A CMIOFeatureControl that controls the amount of backlight compensation to apply. A low number indicates the least amount of backlight compensation. The units for the
                        control's absolute value are undefined.
    @constant       kCMIOPowerLineFrequencyControlClassID
                        A CMIOFeatureControl to specify the power line frequency to properly implement anti-flicker processing. The units for the contorl's absolute value are hertz (Hz).
	@constant		kCMIONoiseReductionControlClassID
						A CMIOFeatureControl that controls the noise reduction strength. The units for the control's absolute value are undefined.
*/
enum
{
    kCMIOBlackLevelControlClassID               = 'bklv',
    kCMIOWhiteLevelControlClassID               = 'whlv',
    kCMIOHueControlClassID                      = 'hue ',
    kCMIOSaturationControlClassID               = 'satu',
    kCMIOContrastControlClassID                 = 'ctst',
    kCMIOSharpnessControlClassID                = 'shrp',
    kCMIOBrightnessControlClassID               = 'brit',
    kCMIOGainControlClassID                     = 'gain',
    kCMIOIrisControlClassID                     = 'iris',
    kCMIOShutterControlClassID                  = 'shtr',
    kCMIOExposureControlClassID                 = 'xpsr',
    kCMIOWhiteBalanceUControlClassID            = 'whbu',
    kCMIOWhiteBalanceVControlClassID            = 'whbv',
    kCMIOWhiteBalanceControlClassID             = 'whbl',
    kCMIOGammaControlClassID                    = 'gmma',
    kCMIOTemperatureControlClassID              = 'temp',
    kCMIOZoomControlClassID                     = 'zoom',
    kCMIOFocusControlClassID                    = 'fcus',
    kCMIOPanControlClassID                      = 'pan ',
    kCMIOTiltControlClassID                     = 'tilt',
    kCMIOOpticalFilterClassID                   = 'opft',
    kCMIOBacklightCompensationControlClassID    = 'bklt',
    kCMIOPowerLineFrequencyControlClassID       = 'pwfq',
	kCMIONoiseReductionControlClassID			= 's2nr',
};

#pragma mark -
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOControl Properties

/*!
    @enum           CMIOControl Properties
    @abstract       CMIOObjectPropertySelector values that apply to all CMIOControls.
    @discussion     CMIOControl is a subclass of CMIOObject and has only the single scope, kCMIOObjectPropertyScopeGlobal, and only a master element.
    @constant       kCMIOControlPropertyScope
                        The CMIOObjectPropertyScope in the owning CMIOObject that contains the CMIOControl.
    @constant       kCMIOControlPropertyElement
                        The CMIOObjectPropertyElement in the owning CMIOObject that contains the CMIOControl.
    @constant       kCMIOControlPropertyVariant
                        A UInt32 that identifies the specific variant of a CMIOControl. This allows the owning CMIOObject to support controls that are of the same basic class (that is,
                        the values of kCMIOObjectPropertyClass are the same) but may control a part of the object for which the standard controls do not control.
*/
enum
{
    kCMIOControlPropertyScope   = 'cscp',
    kCMIOControlPropertyElement = 'celm',
    kCMIOControlPropertyVariant = 'cvar'
};

#pragma mark BooleanControl Properties
/*!
    @enum           CMIOBooleanControl Properties
    @abstract       CMIOObjectPropertySelector values that apply to all CMIOBooleanControls.
    @discussion     CMIOBooleanControl is a subclass of CMIOControl and has only the single scope, kCMIOObjectPropertyScopeGlobal, and only a master element.
    @constant       kCMIOBooleanControlPropertyValue
                        A UInt32 where 0 means false and 1 means true.
*/
enum
{
    kCMIOBooleanControlPropertyValue    = 'bcvl'
};

#pragma mark SelectorControl Properties
/*!
    @enum           CMIOSelectorControl Properties
    @abstract       CMIOObjectPropertySelector values that apply to all CMIOSelectorControls.
    @discussion     CMIOSelectorControl is a subclass of CMIOControl and has only the single scope, kCMIOObjectPropertyScopeGlobal, and only a master element.
    @constant       kCMIOSelectorControlPropertyCurrentItem
                        A UInt32 that is the ID of the item currently selected.
    @constant       kCMIOSelectorControlPropertyAvailableItems
                        An array of UInt32s that represent the IDs of all the items available.
    @constant       kCMIOSelectorControlPropertyItemName
                        This property translates the given item ID into a human readable name. The qualifier contains the ID of the item to be translated and name is returned as a CFString as
                        the property data. The caller is responsible for releasing the returned CFObject.
*/
enum
{
    kCMIOSelectorControlPropertyCurrentItem     = 'scci',
    kCMIOSelectorControlPropertyAvailableItems  = 'scai',
    kCMIOSelectorControlPropertyItemName        = 'scin'
};

#pragma mark FeatureControl Properties
/*!
    @enum           CMIOFeatureControl Properties
    @abstract       CMIOObjectPropertySelector values that apply to all CMIOFeatureControls.
    @discussion     CMIOFeatureControl is a subclass of CMIOControl and has only the single scope, kCMIOObjectPropertyScopeGlobal, and only a master element.
    @constant       kCMIOFeatureControlPropertyOnOff
                        A UInt32 where 1 corresponds to a the feature being on, and 0 corresponds to the feature being off.
    @constant       kCMIOFeatureControlPropertyAutomaticManual
                        A UInt32 where 1 corresponds to a the feature being under automatic control, and 0 corresponds to the feature being under manual control.
    @constant       kCMIOFeatureControlPropertyAbsoluteNative
                        A UInt32 where 1 corresponds to a the feature being programmed with 'absolute' values, and 0 corresponds to the feature being programmed with 'native' values.
    @constant       kCMIOFeatureControlPropertyTune
                        A UInt32 where 1 corresponds to a the feature being tuned, and 0 corresponds to the feature not being tuned. Upon completion of the tuning, the value
                        will automatically revert back to 0.
    @constant       kCMIOFeatureControlPropertyNativeValue
                        A Float32 that represents the value of the feature. Native values are unitless and their the meaning can vary from device to device.
    @constant       kCMIOFeatureControlPropertyAbsoluteValue
                        A Float32 that represents the value of the value of the feature. Absolute values have units associated with them, i.e. Gain has dB, Hue has degrees, etc.
    @constant       kCMIOFeatureControlPropertyNativeRange
                        A AudioValueRange that contains the minimum and maximum native values the feature control can have.
    @constant       kCMIOFeatureControlPropertyAbsoluteRange
                        A AudioValueRange that contains the minimum and maximum absolute values the feature control can have.
    @constant       kCMIOFeatureControlPropertyConvertNativeToAbsolute
                        A Float32 that on input contains a native value for the feature control and on exit contains the equivalent absolute value.
    @constant       kCMIOFeatureControlPropertyConvertAbsoluteToNative
                        A Float32 that on input contains a an abolute value for the feature control and on exit contains the equivalent native value.
    @constant       kCMIOFeatureControlPropertyAbsoluteUnitName
                        A CFString that contains a human readable name for the units associated with the absolute values. The caller is responsible for releasing the returned CFObject.
*/
enum
{
    kCMIOFeatureControlPropertyOnOff                    = 'fcoo',
    kCMIOFeatureControlPropertyAutomaticManual          = 'fcam',
    kCMIOFeatureControlPropertyAbsoluteNative           = 'fcna',
    kCMIOFeatureControlPropertyTune                     = 'fctn',
    kCMIOFeatureControlPropertyNativeValue              = 'fcnv',
    kCMIOFeatureControlPropertyAbsoluteValue            = 'fcav',
    kCMIOFeatureControlPropertyNativeRange              = 'fcnr',
    kCMIOFeatureControlPropertyAbsoluteRange            = 'fcar',
    kCMIOFeatureControlPropertyConvertNativeToAbsolute  = 'fn2a',
    kCMIOFeatureControlPropertyConvertAbsoluteToNative  = 'fa2n',
    kCMIOFeatureControlPropertyAbsoluteUnitName         = 'fcun'
};

#pragma mark ExposureControl Properties
/*!
    @enum           CMIOExposureControl Properties
    @abstract       CMIOObjectPropertySelector values that apply to all CMIOExposureControls.
    @discussion     CMIOExposureControl is a subclass of CMIOFeatureControl and has only the single scope, kCMIOObjectPropertyScopeGlobal, and only a master element.
    @constant       kCMIOExposureControlPropertyRegionOfInterest
                        A CGRect with origin and size coordinates in the 0. to 1. space indicating what portion of the image should be used when auto-exposing.
    @constant       kCMIOExposureControlPropertyLockThreshold
                        A Float32 indicating a threshold that is treated as the minimum change (in either direction) that the average Y value of the image needs to stay within for 
                        the AutoExposure state machine to enter the locked state. A higher number creates more hysteresis.
    @constant       kCMIOExposureControlPropertyUnlockThreshold
                        A Float32 indicating a threshold that is treated as the minimum change (in either direction) that the average Y value of the image needs to exceed for the 
                        AutoExposure state machine to leave the locked state. A higher number creates more hysteresis.
    @constant       kCMIOExposureControlPropertyTarget
                        A Float32 indicating the exposure target, which is typically represented as the average Y value of the image that the firmware auto exposure control tries to achieve.
						Higher numbers indicate a more exposed image.
	@constant       kCMIOExposureControlPropertyConvergenceSpeed
						A Float32 indicating how fast an auto exposure converges to the AE target. Higher numbers are faster.
	@constant		kCMIOExposureControlPropertyStability
						A Float32 to tune the stability of the autoexposure algorithm, indicating how much flicker will be tolerated prior to adjusting the sensor gain.
    @constant       kCMIOExposureControlPropertyStable
                        A Boolean indicating whether the camera has the autoexposure function locked due to sufficient stability. This result is only valid when the autoexposure function
						has not been disabled.
    @constant       kCMIOExposureControlPropertyIntegrationTime
                        A Float32 to limit the maximum integration-time for the sensor, in milliseconds. The maximum integration time is also limited by the framerate. Setting the value to
						0.0 indicates no limiting is applied.
    @constant       kCMIOExposureControlPropertyMaximumGain
                        A Float32 to limit the maximum allowable gain that the autoexposure algorithm will attempt to use. Setting the value to 0.0 indicates no limiting is applied.
*/
enum
{
    kCMIOExposureControlPropertyRegionOfInterest	= 'eroi',
    kCMIOExposureControlPropertyLockThreshold		= 'elck',
    kCMIOExposureControlPropertyUnlockThreshold		= 'eulk',
    kCMIOExposureControlPropertyTarget				= 'etgt',
    kCMIOExposureControlPropertyConvergenceSpeed	= 'ecsp',
	kCMIOExposureControlPropertyStability			= 'esty',
    kCMIOExposureControlPropertyStable				= 'estb',
    kCMIOExposureControlPropertyIntegrationTime		= 'eint',
    kCMIOExposureControlPropertyMaximumGain			= 'emax',
};
    
#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif
