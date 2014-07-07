//-----------------------------------------------------------------------------
//      File:           ForceFeedback.h
//      Contains:       Public interfaces for ForceFeedback technology.
//      Copyright:      © 2002 by Apple Computer, Inc. All rights reserved.
//
//-----------------------------------------------------------------------------

#ifndef _FORCEFEEDBACK_H_
#define _FORCEFEEDBACK_H_

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!	@header		ForceFeedback.h
	@abstract	Public Interfaces to the Force Feedback implementation in Mac OS X.
	@discussion	The Force Feedback API allows developers to control Force Feedback devices attached to the system.  It is a distilled version of the Force Feedback functionality found in Microsoft's DirectInput API.  Developers familiar with that API should find this API to be similar.

*/

#include <CoreFoundation/CoreFoundation.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif

#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#include <IOKit/IOTypes.h>
#include <ForceFeedback/ForceFeedbackConstants.h>

//-----------------------------------------------------------------------------
// The Version of the FF API
//-----------------------------------------------------------------------------

enum {
    kFFAPIMajorRev = 1,
    kFFAPIMinorAndBugRev = 0,
    kFFAPIStage = finalStage,
    kFFAPINonRelRev = 0
};

//-----------------------------------------------------------------------------
// Effect definition structures
//-----------------------------------------------------------------------------

struct FFCONSTANTFORCE
{
    LONG  lMagnitude;
};
typedef struct FFCONSTANTFORCE 		FFCONSTANTFORCE;
typedef FFCONSTANTFORCE *		PFFCONSTANTFORCE;

struct FFRAMPFORCE
{
    LONG  lStart;
    LONG  lEnd;

};
typedef struct	FFRAMPFORCE		FFRAMPFORCE;
typedef FFRAMPFORCE *			PFFRAMPFORCE;

struct FFPERIODIC
{
    DWORD dwMagnitude;
    LONG  lOffset;
    DWORD dwPhase;
    DWORD dwPeriod;

};
typedef struct FFPERIODIC		FFPERIODIC;
typedef FFPERIODIC *			PFFPERIODIC;

struct FFCONDITION
{
    LONG  lOffset;
    LONG  lPositiveCoefficient;
    LONG  lNegativeCoefficient;
    DWORD dwPositiveSaturation;
    DWORD dwNegativeSaturation;
    LONG  lDeadBand;

};
typedef struct FFCONDITION 		FFCONDITION;
typedef FFCONDITION *			PFFCONDITION;

struct FFCUSTOMFORCE
{
    DWORD cChannels;
    DWORD dwSamplePeriod;
    DWORD cSamples;
    LPLONG rglForceData;

};
typedef struct FFCUSTOMFORCE		FFCUSTOMFORCE;
typedef FFCUSTOMFORCE *			PFFCUSTOMFORCE;

struct FFENVELOPE
{
    DWORD dwSize;                   /* sizeof(FFENVELOPE)   */
    DWORD dwAttackLevel;
    DWORD dwAttackTime;             /* Microseconds         */
    DWORD dwFadeLevel;
    DWORD dwFadeTime;               /* Microseconds         */

};
typedef struct FFENVELOPE		FFENVELOPE;
typedef FFENVELOPE *			PFFENVELOPE;

// IMPORTANT NOTE:  OBJECT IDS cannot be used to identify trigger buttons
// in FFEFFECT.dwTriggerButton, and output axes in FFEFFECT.rgdwAxes[n].
// Please use object offsets (FFJOFS_* constants), the only supported method.
struct FFEFFECT
{
    DWORD dwSize;                   /* sizeof(FFEFFECT)     */
    DWORD dwFlags;                  /* FFEFF_*              */
    DWORD dwDuration;               /* Microseconds         */
    DWORD dwSamplePeriod;           /* Microseconds         */
    DWORD dwGain;
    DWORD dwTriggerButton;          /* or FFEB_NOTRIGGER    */
    DWORD dwTriggerRepeatInterval;  /* Microseconds         */
    DWORD cAxes;                    /* Number of axes       */
    LPDWORD rgdwAxes;               /* Array of axes        */
    LPLONG rglDirection;            /* Array of directions  */
    PFFENVELOPE lpEnvelope;         /* Optional             */
    DWORD cbTypeSpecificParams;     /* Size of params       */
    void* lpvTypeSpecificParams;    /* Pointer to params    */
    DWORD dwStartDelay;             /* Microseconds         */

};
typedef struct FFEFFECT			FFEFFECT;
typedef FFEFFECT *			PFFEFFECT;

struct FFEFFESCAPE
{
    DWORD   dwSize;
    DWORD   dwCommand;
    void*   lpvInBuffer;
    DWORD   cbInBuffer;
    void*   lpvOutBuffer;
    DWORD   cbOutBuffer;

};
typedef struct FFEFFESCAPE		FFEFFESCAPE;
typedef FFEFFESCAPE *			PFFEFFESCAPE;

// NOTE:  this structure has no DirectInput equivalent
struct FFCAPABILITIES
{
    NumVersion	ffSpecVer;				// Version of specification supported by the driver
    UInt32		supportedEffects;		// FFCAP_ET_*; including emulated effects
    UInt32		emulatedEffects;		// FFCAP_ET_*; driver-emulated effects
    UInt32		subType;				// FFCAP_TYPE_*
    UInt32		numFfAxes;
    UInt8		ffAxes[32];
    UInt32		storageCapacity;		// number of effects that can be stored 
                                    // by the driver/device
    UInt32		playbackCapacity;		// number of effects that can be _simultaneously_
                                    // played back by the driver/device
    NumVersion	firmwareVer;			// device firmware version, vendor-defined
    NumVersion	hardwareVer;			// hardware version, vendor-defined
    NumVersion	driverVer;				// driver version, vendor-defined

};
typedef struct FFCAPABILITIES		FFCAPABILITIES;
typedef FFCAPABILITIES *			PFFCAPABILITIES;



//-----------------------------------------------------------------------------
// Object reference pointers
//-----------------------------------------------------------------------------

// FFDeviceObjectReference and FFEffectObjectReference are opaque handles
// to objects created and maintained by the FF API.
// A FFDeviceObjectReference is obtained through a call to FFCreateDevice and
// refers to a specific attached device supporting force feedback.  This 
// reference may be passed to any of the "FFDevice" functions (below).  When
// you are through with it, call FFReleaseDevice to release the memory.
// Similarly, a FFEffectObjectReference is obtained through a call to 
// FFDeviceCreateEffect and refers to a created force feedback effect on a
// particular device.  This reference may be passed to any of the "FFEffect"
// functions.  Call FFDeviceReleaseEffect to unload the effect and clean up
// its memory.  - Jeff Mallett 9/25/02
//
typedef struct {} __FFDHIDDEN,     * FFDeviceObjectReference;
typedef struct {} __FFEHIDDEN,     * FFEffectObjectReference;


//-----------------------------------------------------------------------------
// FF (general) function prototypes
//-----------------------------------------------------------------------------

/*!	@function	FFCreateDevice
	@abstract	Creates a new API device object from an OS object in preparation to use the device for force feedback.
	@param		hidDevice		Pointer to a HID device object.
	@param		pdeviceReference	Address of a variable to receive an opaque reference handle to a new device object.  This reference can be used in subsequent calls to FFDevice* functions
	@result		If the method succeeds, and the device supports FF, the return value is FF_OK.
If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOINTERFACE
<br>	FFERR_OUTOFMEMORY
<br>	FFERR_INTERNAL 
<br>	
	@discussion	When you are finished with the device, FFReleaseDevice must be called on the reference received in this function to dispose of the API device object.
*/

extern HRESULT
FFCreateDevice(
    io_service_t		hidDevice,
    FFDeviceObjectReference *	pDeviceReference
    );
                

/*!	@function	FFReleaseDevice
	@abstract	Disposes of an API device object created with FFCreateDevice.
	@param		deviceReference		An opaque reference handle to the device object that is be disposed of.  This handle is obtained from a previous call to FFCreateDevice.
	@result		If the method succeeds, and the device supports FF, the return value is FF_OK.
If the method fails, the return value can be one of the following error values:
<br>
<br>	FFERR_INVALIDPARAM 
<br>	FFERR_NOINTERFACE
<br>	FFERR_OUTOFMEMORY
<br>
	@discussion	
*/

extern HRESULT
FFReleaseDevice(
    FFDeviceObjectReference	deviceReference
    );


/*!	@function	FFIsForceFeedback
	@abstract	Used to determine if a particular device provided by HID Manager is a force feedback device.
	@param		hidDevice		Pointer to a HID device object to be tested for force feedback support.
	@result		If the method succeeds, and the device supports FF, the return value is FF_OK. If the method succeeds, and the device does not support FF, the return value is FFERR_NOINTERFACE. If the method fails, the return value is FFERR_INVALIDPARAM 
	@discussion	When you are finished with the device, FFReleaseDevice must be called on the reference received in this function to dispose of the API device object.
*/

extern HRESULT
FFIsForceFeedback(
    io_service_t		hidDevice
    );
         
                       
//-----------------------------------------------------------------------------
// FFDevice (device related) function prototypes
//-----------------------------------------------------------------------------

/*!	@function	FFDeviceCreateEffect
	@abstract	Creates and initializes an instance of an effect identified by the effect UUID on the device.
	@param		deviceReference		An opaque reference handle to a device object.  This is obtained from a previous call to FFCreateDevice.
	@param		uuidRef			Reference to the UUID identifying the effect to be created. Only predefined effect UUIDs are accepted. The following standard effect UUIDs are defined: 
<br>
<br>	kFFEffectType_ConstantForce_ID 
<br>	kFFEffectType_RampForce_ID 
<br>	kFFEffectType_Square_ID 
<br>	kFFEffectType_Sine_ID 
<br>	kFFEffectType_Triangle_ID 
<br>	kFFEffectType_SawtoothUp_ID 
<br>	kFFEffectType_SawtoothDown_ID 
<br>	kFFEffectType_Spring_ID 
<br>	kFFEffectType_Damper_ID 
<br>	kFFEffectType_Inertia_ID 
<br>	kFFEffectType_Friction_ID 
<br>	kFFEffectType_CustomForce_ID 
<br>
<br>
        @param		pEffectDefinition	Pointer to FFEFFECT structure that provides parameters for the created effect. This parameter is optional. If it is NULL, the effect object is created without parameters. The application must then call the FFEffectSetParameters function to set the parameters of the effect before it can download the effect. 
	@param		pEffectReference	Address of a variable to receive an opaque reference handle to a new effect object.  This reference can be used in subsequent calls to FFEffect* functions.
	@result		If the method succeeds, the return value is FF_OK. If the method fails, the return value can be one of the following error values:
<br>
<br>	FFERR_INVALIDPARAM
<br>	FFERR_UNSUPPORTEDAXIS
<br>	FFERR_OUTOFMEMORY
<br>	FFERR_DEVICEPAUSED
<br>	FFERR_DEVICEFULL
<br>	FFERR_INVALIDDOWNLOADID
<br>	FFERR_INTERNAL
<br>	FFERR_EFFECTTYPEMISMATCH 
<br>
	@discussion	When you are finished with the effect, FFReleaseEffect must be called on the reference received in this function to dispose of the API effect object.
*/

extern HRESULT
FFDeviceCreateEffect(
    FFDeviceObjectReference	deviceReference,
    CFUUIDRef			uuidRef,
    FFEFFECT *			pEffectDefinition,
    FFEffectObjectReference *	pEffectReference
    );
                

/*!	@function	FFDeviceReleaseEffect
	@abstract	Disposes of an API effect object created with FFDeviceCreateEffect.
	@param		deviceReference		An opaque reference handle to the device object that is be disposed of.  This handle is obtained from a previous call to FFCreateDevice.
	@param		effectReference		An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect.
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOTDOWNLOADED
<br>	FFERR_GENERIC
<br>	FFERR_INTERNAL
<br>	FFERR_INVALIDDOWNLOADID
<br>	
	@discussion	
*/

extern HRESULT
FFDeviceReleaseEffect(
    FFDeviceObjectReference	deviceReference,
    FFEffectObjectReference	effectReference
    );
                
/*!	@function	FFDeviceEscape
	@abstract	Sends a hardware-specific command to the device.
	@param		deviceReference		An opaque reference handle to a device object.  This is obtained from a previous call to FFCreateDevice. 
	@param		pFFEffectEscape		Pointer to FFEFFESCAPE structure that describes the command to be sent. On success, the cbOutBuffer member contains the number of bytes of the output buffer used.
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_UNSUPPORTED
<br>	
	@discussion Because each driver implements different escapes, it is the application's responsibility to ensure that it is sending the escape to the correct driver.	
*/
extern HRESULT
FFDeviceEscape(
    FFDeviceObjectReference     deviceReference,
    FFEFFESCAPE *		pFFEffectEscape
    );
    
/*!	@function	FFDeviceGetForceFeedbackState
	@abstract	Retrieves the state of the device's force feedback system.
	@param		deviceReference		An opaque reference handle to a device object.  This is obtained from a previous call to FFCreateDevice. 
	@param		pFFState		Location for flags that describe the current state of the device's force feedback system. 
The value is a combination of the following constants: 
<br>
<br>	FFGFFS_ACTUATORSOFF 
<br>	The device's force feedback actuators are disabled. 
<br>
<br>	FFGFFS_ACTUATORSON 
<br>	The device's force feedback actuators are enabled. 
<br>
<br>	FFGFFS_DEVICELOST 
<br>	The device suffered an unexpected failure and is in an indeterminate state. It must be reset either by unacquiring and reacquiring the device, or by sending a FFSFFC_RESET command. 
<br>
<br>	FFGFFS_EMPTY 
<br>	The device has no downloaded effects. 
<br>
<br>	FFGFFS_PAUSED 
<br>	Playback of all active effects has been paused. 
<br>
<br>	FFGFFS_POWEROFF 
<br>	The force feedback system is not currently available. If the device cannot report the power state, neither FFGFFS_POWERON nor FFGFFS_POWEROFF is returned. 
<br>
<br>	FFGFFS_POWERON 
<br>	Power to the force feedback system is currently available. If the device cannot report the power state, neither FFGFFS_POWERON nor FFGFFS_POWEROFF is returned. 
<br>
<br>	FFGFFS_SAFETYSWITCHOFF 
<br>	The safety switch is currently off; that is, the device cannot operate. If the device cannot report the state of the safety switch, neither FFGFFS_SAFETYSWITCHON nor FFGFFS_SAFETYSWITCHOFF is returned. 
<br>
<br>	FFGFFS_SAFETYSWITCHON 
<br>	The safety switch is currently on; that is, the device can operate. If the device cannot report the state of the safety switch, neither FFGFFS_SAFETYSWITCHON nor FFGFFS_SAFETYSWITCHOFF is returned. 
<br>
<br>	FFGFFS_STOPPED 
<br>	No effects are playing, and the device is not paused. 
<br>
<br>	FFGFFS_USERFFSWITCHOFF 
<br>	The user force feedback switch is currently off; that is, the device cannot operate. If the device cannot report the state of the user force feedback switch, neither FFGFFS_USERFFSWITCHON nor FFGFFS_USERFFSWITCHOFF is returned. 
<br>
<br>	FFGFFS_USERFFSWITCHON 
<br>	The user force feedback switch is currently on; that is, the device can operate. If the device cannot report the state of the user force feedback switch, neither FFGFFS_USERFFSWITCHON nor FFGFFS_USERFFSWITCHOFF is returned. 
<br>
<br>	Future versions can define additional flags. Applications should ignore any flags that are not currently defined. 
<br>
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	
	@discussion	
*/

extern HRESULT
FFDeviceGetForceFeedbackState(
    FFDeviceObjectReference 	deviceReference,
    FFState *			pFFState
    );
                
/*!	@function	FFDeviceSendForceFeedbackCommand
	@abstract	Sends a command to the device's force feedback system.
	@param		deviceReference		An opaque reference handle to the device object that is be disposed of.  This handle is obtained from a previous call to FFCreateDevice.
	@param		flags		Single value indicating the desired change in state. The value can be one of the following: 
<br>
<br>	FFSFFC_CONTINUE 
<br>	Paused playback of all active effects is to be continued. It is an error to send this command when the device is not in a paused state. 
<br>
<br>	FFSFFC_PAUSE 
<br>	Playback of all active effects is to be paused. This command also stops the clock-on effects so that they continue playing to their full duration when restarted. 
<br>
<br>	While the device is paused, new effects cannot be started, and existing ones cannot be modified. Doing so can cause the subsequent FFSFFC_CONTINUE command to fail to perform properly. 
<br>
<br>	To abandon a pause and stop all effects, use the FFSFFC_STOPALL or FFSFCC_RESET commands. 
<br>
<br>	FFSFFC_RESET 
<br>	The device's force feedback system is to be put in its startup state. All effects are removed from the device, are no longer valid, and must be recreated if they are to be used again. The device's actuators are disabled. 
<br>
<br>	FFSFFC_SETACTUATORSOFF 
<br>	The device's force feedback actuators are to be disabled. While the actuators are off, effects continue to play but are ignored by the device. Using the analogy of a sound playback device, they are muted, rather than paused. 
<br>
<br>	FFSFFC_SETACTUATORSON 
<br>	The device's force feedback actuators are to be enabled. 
<br>
<br>	FFSFFC_STOPALL 
<br>	Playback of any active effects is to be stopped. All active effects are reset, but are still being maintained by the device and are still valid. If the device is in a paused state, that state is lost. 
<br>
<br>	This command is equivalent to calling the FFEffect_Stop method for each effect playing. 
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_INTERNAL
<br>	
	@discussion	
*/

extern HRESULT
FFDeviceSendForceFeedbackCommand(
    FFDeviceObjectReference 	deviceReference,
    FFCommandFlag		flags
    );
                
/*!	@function	FFDeviceSetForceFeedbackProperty
	@abstract	Retrieves the device's force feedback capabilities.
	@param		deviceReference		An opaque reference handle to the device object that is be disposed of.  This handle is obtained from a previous call to FFCreateDevice.
	@param		property		The following property values are defined for a FF device: 
<br>
<br>	FFPROP_AUTOCENTER 
<br>	Specifies whether the actuated FF axes are self-centering.  This property controls the device's "default centering spring".
<br>	The pValue member points to a UInt32 can be one of the following values. 
<br>	0 - OFF: The device should not automatically center when the user releases the device. An application that uses force feedback should disable autocentering before playing effects. 
<br>	1 - ON: The device should automatically center when the user releases the device.
<br>	Not all devices support the autocenter property. 
<br>
<br>	FFPROP_FFGAIN 
<br>	Sets the gain for the device.
<br>	The pValue member points to a UInt32 that contains a gain value that is applied to all effects created on the device. The value is an integer in the range from 0 through 10,000, specifying the amount by which effect magnitudes should be scaled for the device. For example, a value of 10,000 indicates that all effect magnitudes are to be taken at face value. A value of 9,000 indicates that all effect magnitudes are to be reduced to 90% of their nominal magnitudes. 
<br>	Setting a gain value is useful when an application wants to scale down the strength of all force feedback effects uniformly, based on user preferences.  
	@param		pValue			Address of the location where the property value is to be read.  SetForceFeedbackProperty will assume that the data is valid, and of the correct type.
	@result		If the method succeeds, the return value is FF_OK or  FFERR_UNSUPPORTED.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	
	@discussion	
*/

extern HRESULT
FFDeviceSetForceFeedbackProperty(
    FFDeviceObjectReference 	deviceReference,
    FFProperty  		property,
    void *   			pValue
    );
                
/*!	@function	FFDeviceGetForceFeedbackProperty
	@abstract	Gets properties that define the device behavior.
	@param		deviceReference		An opaque reference handle to the device object that is be disposed of.  This handle is obtained from a previous call to FFCreateDevice.
	@param		property		The following property values are defined for a FF device (see FFDeviceSetForceFeedbackProperty for details): 
<br>
<br>	FFPROP_AUTOCENTER 
<br>	FFPROP_FFGAIN 
<br>
	@param		pValue			Address of the location where the value associated with the property is to be stored.  GetForceFeedbackProperty assumes that the pointer is valid, although it will perform a size check before writing the data to pValue
        @param		valueSize		Size, in bytes, of data area pointed to by pValue.  Size is compared to expected property size, and the function fails if a mismatch occurs. 
        @result		If the method succeeds, the return value is FF_OK or  FFERR_UNSUPPORTED.
If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	
	@discussion	
*/
extern HRESULT
FFDeviceGetForceFeedbackProperty(
    FFDeviceObjectReference 	deviceReference,
    FFProperty  		property,
    void *   			pValue,
    IOByteCount			valueSize
    );
                
/*!	@function	FFDeviceSetCooperativeLevel
	@abstract	Function is unimplemented in version 1.0 of this API
	@discussion	
*/
extern HRESULT
FFDeviceSetCooperativeLevel( 
    FFDeviceObjectReference 	deviceReference,
    void *  			taskIdentifier,     
    FFCooperativeLevelFlag 	flags  
    );
                
/*!	@function	FFDeviceGetForceFeedbackCapabilities
	@abstract	Retrieves the device's force feedback capabilities.
	@param		deviceReference		An opaque reference handle to the device object that is be disposed of.  This handle is obtained from a previous call to FFCreateDevice.
	@param		pFFCapabilities		Pointer to a FFCAPABILITIES structure that is to be filled in by the this call. 
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	
	@discussion	
*/

extern HRESULT
FFDeviceGetForceFeedbackCapabilities(
    FFDeviceObjectReference 	deviceReference,
    FFCAPABILITIES *		pFFCapabilities
    );


//-----------------------------------------------------------------------------
// FFEffect (effect related) function prototypes
//-----------------------------------------------------------------------------

/*!	@function	FFEffectDownload
	@abstract	Places the effect on the device. If the effect is already on the device, the existing effect is updated to match the values set by the FFEffectSetParameters method.
        @param		efffectRef	An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
	@result		If the method succeeds, the return value is FF_OK or S_FALSE.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_DEVICEPAUSED
<br>	FFERR_DEVICEFULL
<br>	FFERR_INVALIDDOWNLOADID
<br>	FFERR_INTERNAL
<br>	FFERR_EFFECTTYPEMISMATCH
<br>
<br>	If the method returns S_FALSE, the effect has already been downloaded to the device.
<br>	
	@discussion	It is valid to update an effect while it is playing. The semantics of such an operation are explained in the reference for FFEffectSetParameters.
*/

extern HRESULT
FFEffectDownload(
    FFEffectObjectReference	effectReference
    );
                
/*!	@function	FFEffectEscape
	@abstract	Sends a hardware-specific command to the driver.
        @param		effectReference		An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
        @param		pFFEffectEscape		FFEFFESCAPE structure that describes the command to be sent. On success, the cbOutBuffer member contains the number of bytes of the output buffer used. 
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOTDOWNLOADED
<br>	FFERR_UNSUPPORTED
<br>
<br>	Other device-specific error codes are also possible. Ask the hardware manufacturer for details
<br>
	@discussion	Because each driver implements different escapes, it is the application's responsibility to ensure that it is sending the escape to the correct driver.
*/

extern HRESULT
FFEffectEscape(
    FFEffectObjectReference 	effectReference,
    FFEFFESCAPE *		pFFEffectEscape
    );
    
/*!	@function	FFEffectGetEffectStatus
	@abstract	Sends a hardware-specific command to the driver.
        @param		effectReference		An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
        @param		pFlags			Pointer to status flags for the effect. The value can be 0 or one or more of the following constants: 
<br>
<br>	FFEGES_PLAYING 
<br>	The effect is playing. 
<br>
<br>	FFEGES_EMULATED 
<br>	The effect is emulated. 
<br>
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOTDOWNLOADED
<br>
	@discussion	
*/

extern HRESULT
FFEffectGetEffectStatus(
    FFEffectObjectReference	effectReference,
    FFEffectStatusFlag *	pFlags  
    );
    
/*!	@function	FFEffectGetParameters
	@abstract	Retrieves information about an effect.
        @param		efffectRef	An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
        @param		pFFEffect	Address of a FFEFFECT structure that receives effect information. The dwSize member must be filled in by the application before calling this method. 
        @param		flags		Flags that specify which parts of the effect information are to be retrieved. The value can be 0 or one or more of the following constants: 
<br>
<br>	FFEP_ALLPARAMS 
<br>	The union of all other FFEP_* flags, indicating that all members of the FFEFFECT structure are being requested. 
<br>
<br>	FFEP_AXES 
<br>	The cAxes and rgdwAxes members should receive data. The cAxes member on entry contains the size (in DWORDs) of the buffer pointed to by the rgdwAxes member. If the buffer is too small, the method returns FFERR_MOREDATA and sets cAxes to the necessary size of the buffer. 
<br>
<br>	FFEP_DIRECTION 
<br>	The cAxes and rglDirection members should receive data. The cAxes member on entry contains the size (in DWORDs) of the buffer pointed to by the rglDirection member. If the buffer is too small, the GetParameters method returns FFERR_MOREDATA and sets cAxes to the necessary size of the buffer. 
<br>	The dwFlags member must include at least one of the coordinate system flags (FFEFF_CARTESIAN, FFEFF_POLAR, or FFEFF_SPHERICAL). The API returns the direction of the effect in one of the coordinate systems you specified, converting between coordinate systems as necessary. On exit, exactly one of the coordinate system flags is set in the dwFlags member, indicating which coordinate system the FF API used. In particular, passing all three coordinate system flags retrieves the coordinates in exactly the same format in which they were set. 
<br>
<br>	FFEP_DURATION 
<br>	The dwDuration member should receive data. 
<br>
<br>	FFEP_ENVELOPE 
<br>	The lpEnvelope member points to a FFENVELOPE structure that should receive data. If the effect does not have an envelope associated with it, the lpEnvelope member is set to NULL. 
<br>
<br>	FFEP_GAIN 
<br>	The dwGain member should receive data. 
<br>
<br>	FFEP_SAMPLEPERIOD 
<br>	The dwSamplePeriod member should receive data. 
<br>
<br>	FFEP_STARTDELAY 
<br>	The dwStartDelay member should receive data. 
<br>
<br>	FFEP_TRIGGERBUTTON 
<br>	The dwTriggerButton member should receive data. 
<br>
<br>	FFEP_TRIGGERREPEATINTERVAL 
<br>	The dwTriggerRepeatInterval member should receive data. 
<br>
<br>	FFEP_TYPESPECIFICPARAMS 
<br>	The lpvTypeSpecificParams member points to a buffer whose size is specified by the cbTypeSpecificParams member. On return, the buffer is filled in with the type-specific data associated with the effect, and the cbTypeSpecificParams member contains the number of bytes copied. If the buffer supplied by the application is too small to contain all the type-specific data, the method returns FFERR_MOREDATA, and the cbTypeSpecificParams member contains the required size of the buffer in bytes. 
<br>
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOTDOWNLOADED
<br>	FFERR_MOREDATA
<br>
	@discussion	Common errors resulting in a FFERR_INVALIDPARAM error include not setting the dwSize member of the FFEFFECT structure, passing invalid flags, or not setting up the members in the FFEFFECT structure properly in preparation for receiving the effect information.
*/

extern HRESULT
FFEffectGetParameters(
    FFEffectObjectReference	effectReference,
    FFEFFECT	*		pFFEffect,  
    FFEffectParameterFlag	flags     
    );
    
/*!	@function	FFEffectSetParameters
	@abstract	Sets the characteristics of an effect.
        @param		efffectRef	An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
        @param		pFFEffect	Address of a FFEFFECT structure that contains effect information. The dwSize member must be filled in by the application before calling this method, as well as any members specified by corresponding bits in the flags parameter. 
        @param		flags	Flags that specify which portions of the effect information are to be set and how the downloading of the parameters should be handled. The value can be 0 or one or more of the following constants: 
<br>
<br>	FFEP_AXES 
<br>	The cAxes and rgdwAxes members contain data. 
<br>
<br>	FFEP_DIRECTION 
<br>	The cAxes and rglDirection members contain data. The dwFlags member specifies (with FFEFF_CARTESIAN or FFEFF_POLAR) the coordinate system in which the values should be interpreted. 
<br>
<br>	FFEP_DURATION 
<br>	The dwDuration member contains data. 
<br>
<br>	FFEP_ENVELOPE 
<br>	The lpEnvelope member points to a FFENVELOPE structure that contains data. To detach any existing envelope from the effect, pass this flag and set the lpEnvelope member to NULL. 
<br>
<br>	FFEP_GAIN 
<br>	The dwGain member contains data. 
<br>
<br>	FFEP_NODOWNLOAD 
<br>	Suppress the automatic FFEffect_Download that is normally performed after the parameters are updated. 
<br>
<br>	FFEP_NORESTART 
<br>	Suppress the stopping and restarting of the effect to change parameters. See Remarks. 
<br>
<br>	FFEP_SAMPLEPERIOD 
<br>	The dwSamplePeriod member contains data. 
<br>
<br>	FFEP_START 
<br>	The effect is to be started (or restarted if it is currently playing) after the parameters are updated. By default, the play state of the effect is not altered. 
<br>
<br>	FFEP_STARTDELAY 
<br>	The dwStartDelay member contains data. 
<br>
<br>	FFEP_TRIGGERBUTTON 
<br>	The dwTriggerButton member contains data. 
<br>
<br>		 
<br>		The dwTriggerRepeatInterval member contains data. 
<br>
<br>	FFEP_TYPESPECIFICPARAMS 
<br>	The lpvTypeSpecificParams and cbTypeSpecificParams members of the FFEFFECT structure contain the address and size of type-specific data for the effect. 
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_UNSUPPORTEDAXIS
<br>	FFERR_OUTOFMEMORY
<br>	FFERR_DEVICEPAUSED
<br>	FFERR_DEVICEFULL
<br>	FFERR_INVALIDDOWNLOADID
<br>	FFERR_INTERNAL
<br>	FFERR_EFFECTTYPEMISMATCH
<br>
	@discussion	The FFEffectSetParameters method automatically downloads the effect, but this behavior can be suppressed by setting the FFEP_NODOWNLOAD flag. If automatic download has been suppressed, you can manually download the effect by invoking the FFEffectDownload method.
<br>
<br>	If the effect is playing while the parameters are changed, the new parameters take effect as if they were the parameters when the effect started.
<br>
<br>	For example, suppose a periodic effect with a duration of three seconds is started. After two seconds, the direction of the effect is changed. The effect then continues for one additional second in the new direction. The envelope, phase, amplitude, and other parameters of the effect continue smoothly, as if the direction had not changed.
<br>
<br>	In the same situation, if after two seconds the duration of the effect were changed to 1.5 seconds, the effect would stop.
<br>
<br>	Normally, if the driver cannot update the parameters of a playing effect, the driver is permitted to stop the effect, update the parameters, and then restart the effect. Passing the FFEP_NORESTART flag suppresses this behavior. If the driver cannot update the parameters of an effect while it is playing, the error code FFERR_EFFECTPLAYING is returned, and the parameters are not updated.
<br>
<br>	No more than one of the FFEP_NODOWNLOAD, FFEP_START, and FFEP_NORESTART flags should be set. (It is also valid to pass none of them.)
<br>
<br>	These three flags control download and playback behavior as follows:
<br>
<br>	If FFEP_NODOWNLOAD is set, the effect parameters are updated but not downloaded to the device.
<br>
<br>	If the FFEP_START flag is set, the effect parameters are updated and downloaded to the device, and the effect is started just as if the FFEffect_Start method had been called with the dwIterations parameter set to 1 and with no flags. (Combining the update with FFEP_START is slightly faster than calling Start separately, because it requires less information to be transmitted to the device.)
<br>
<br>	If neither FFEP_NODOWNLOAD nor FFEP_START is set and the effect is not playing, the parameters are updated and downloaded to the device.
<br>
<br>	If neither FFEP_NODOWNLOAD nor FFEP_START is set and the effect is playing, the parameters are updated if the device supports on-the-fly updating. Otherwise the behavior depends on the state of the FFEP_NORESTART flag. If it is set, the error code FFERR_EFFECTPLAYING is returned. If it is clear, the effect is stopped, the parameters are updated, and the effect is restarted.

*/

extern HRESULT
FFEffectSetParameters(
    FFEffectObjectReference	effectReference,
    FFEFFECT *			pFFEffect,  
    FFEffectParameterFlag    	flags      
    );
                
/*!	@function	FFEffectStart
	@abstract	Begins playing an effect. If the effect is already playing, it is restarted from the beginning. If the effect has not been downloaded or has been modified since its last download, it is downloaded before being started. This default behavior can be suppressed by passing the FFES_NODOWNLOAD flag.
        @param		efffectReference	An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
        @param		iterations		Number of times to play the effect in sequence. The envelope is re-articulated with each iteration. 
<br>
<br>	To play the effect exactly once, pass 1. To play the effect repeatedly until explicitly stopped, pass INFINITE. To play the effect until explicitly stopped without re-articulating the envelope, modify the effect parameters with the FFEffect_SetParameters method, and change the dwDuration member to INFINITE. 
        @param		flags			Flags that describe how the effect should be played by the device. The value can be 0 or one or more of the following values: 
<br>
<br>	FFES_SOLO 
<br>	All other effects on the device should be stopped before the specified effect is played. If this flag is omitted, the effect is mixed with existing effects already started on the device. 
<br>
<br>	FFES_NODOWNLOAD 
<br>	Do not automatically download the effect.  
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_DEVICEPAUSED
<br>	FFERR_DEVICEFULL
<br>	FFERR_INVALIDDOWNLOADID
<br>	FFERR_INTERNAL
<br>	FFERR_EFFECTTYPEMISMATCH
<br>	FFERR_GENERIC
<br>
	@discussion	Not all devices support multiple iterations.
*/

extern HRESULT
FFEffectStart(
    FFEffectObjectReference	effectReference,
    UInt32			iterations,  
    FFEffectStartFlag		flags        
    );
                
/*!	@function	FFEffectStop
	@abstract	Stops playing an effect.
        @param		effectReference		An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOTDOWNLOADED
<br>	FFERR_GENERIC
<br>	FFERR_INTERNAL
<br>	FFERR_INVALIDDOWNLOADID
<br>
	@discussion
*/

extern HRESULT
FFEffectStop(
    FFEffectObjectReference	effectReference
    );
                
/*!	@function	FFEffectUnload
	@abstract	Removes the effect from the device. If the effect is playing, it is automatically stopped before it is unloaded.
        @param		effectReference		An opaque reference handle to an effect object.  This is obtained from a previous call to FFDeviceCreateEffect. 
	@result		If the method succeeds, the return value is FF_OK.  If the method fails, the return value can be one of the following error values:
<br>	
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOTDOWNLOADED
<br>	FFERR_GENERIC
<br>	FFERR_INTERNAL
<br>	FFERR_INVALIDDOWNLOADID
<br>
	@discussion
*/
extern HRESULT
FFEffectUnload(
    FFEffectObjectReference	effectReference
    );


#ifdef __cplusplus
}       
#endif

#endif // _FORCEFEEDBACK_H_







