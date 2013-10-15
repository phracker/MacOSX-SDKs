//-----------------------------------------------------------------------------
//      File:           IOForceFeedbackLib.h
//      Contains:       Public interfaces for the Force Feedback PlugIn architecture .
//      Copyright:      © 2002-2003 by Apple Computer, Inc. All rights reserved.
//
//-----------------------------------------------------------------------------

#ifndef _IOFORCEFEEDBACKLIB_H
#define _IOFORCEFEEDBACKLIB_H

#if PRAGMA_ONCE
#pragma once
#endif

/*!	@header		IOForceFeedbackLib.h
	@abstract	Public Interfaces and constants used to develop Force Feedback plugIns.
	@discussion	A force feedback device manufacturer might need to implement a plugIn
                to allow the Force Feedback Library to control the device.  This header
                file describes the functions that need to be implemented.  This interface definition 
                follows Microsoft Windows IDirectInputEffectDriver definition wherever it makes sense
                to do so. This plugIn architecture uses the CFPlugIn model (COM).  The Force Feedback
                Framework will find available plugIns and will use this interface to communicate with
                the hardware.<br><br>
                Certain functions may contain more or fewer parameters than the corresponding Windows
                IDirectInputEffectDriver version.

*/
#include <sys/cdefs.h>

__BEGIN_DECLS
#include <CoreFoundation/CoreFoundation.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif

#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#include <IOKit/IOTypes.h>
#include <ForceFeedback/ForceFeedback.h>

//====================================================================================================================
// The Version of the FF PlugIn API
//====================================================================================================================
//
    /*!
    @enum Force Feedback PlugIn API Version
     @discussion This refers the Force Feedback PlugIn API (and not the Framework API).
     */
enum {
    kFFPlugInAPIMajorRev = 1,
    kFFPlugInAPIMinorAndBugRev = 0,
    kFFPlugInAPIStage = finalStage,
    kFFPlugInAPINonRelRev = 0
};

//====================================================================================================================
//	Defines
//====================================================================================================================
//

/*!
    @defined FFDEVICESTATE & PFFDEVICESTATE
    @discussion Mac OS versions of these definitions 
    */
    #define FFDEVICESTATE	ForceFeedbackDeviceState
	#define PFFDEVICESTATE  ForceFeedbackDeviceStatePtr


// F4545CE5-BF5B-11D6-A4BB-0003933E3E3E
#define kIOForceFeedbackLibTypeID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0xF4, 0x54, 0x5C, 0xE5, 0xBF, 0x5B, 0x11, 0xD6, 					\
    0xA4, 0xBB, 0x00, 0x03, 0x93, 0x3E, 0x3E, 0x3E)

// 1C7C5850-BB6A-11D6-B75F-003065FBE6B0
#define kIOForceFeedbackDeviceInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0x1C, 0x7C, 0x58, 0x50, 0xBB, 0x6A, 0x11, 0xD6, 							\
    0xB7, 0x5F, 0x00, 0x30, 0x65, 0xFB, 0xE6, 0xB0)


//====================================================================================================================
//	Structs
//====================================================================================================================
//
/*!
@typedef ForceFeedbackDeviceState
@abstract Returns information about the state of a force feedback device.
@discussion
@field dwSize Specifies the size of the structure in bytes. This member must be initialized before the structure is used.
@field dwState Indicates various aspects of the device state. Can indicate zero, one, or more of the following: 
<br><br>FFGFFS_EMPTY 
<br><br>Indicates that the force feedback device is devoid of any downloaded effects. 
<br><br>FFGFFS_STOPPED 
<br><br>Indicates that no effects are currently playing and the device is not paused. 
<br><br>FFGFFS_PAUSED 
<br><br>Indicates that playback of effects has been paused by a previous FFSFFC_PAUSE command. 
<br><br>FFGFFS_ACTUATORSON 
<br><br>Indicates that the device's force-feedback actuators are enabled. 
<br><br>FFGFFS_ACTUATORSOFF 
<br><br>Indicates that the device's force-feedback actuators are disabled. 
<br><br>FFGFFS_POWERON 
<br><br>Indicates that power to the force-feedback system is currently available. If the device cannot report the power state, then neither FFGFFS_POWERON nor FFGFFS_POWEROFF should be returned. 
<br><br>FFGFFS_POWEROFF 
Indicates that power to the force-feedback system is not currently available. If the device cannot report the power state, then neither FFGFFS_POWERON nor FFGFFS_POWEROFF should be returned. 
<br><br>FFGFFS_SAFETYSWITCHON 
<br><br>Indicates that the safety switch (dead-man switch) is currently on, meaning that the device can operate. If the device cannot report the state of the safety switch, then neither FFGFFS_SAFETYSWITCHON nor FFGFFS_SAFETYSWITCHOFF should be returned. 
<br><br>FFGFFS_SAFETYSWITCHOFF 
<br><br>Indicates that the safety switch (dead-man switch) is currently off, meaning that the device cannot operate. If the device cannot report the state of the safety switch, then neither FFGFFS_SAFETYSWITCHON nor FFGFFS_SAFETYSWITCHOFF should be returned. 
<br><br>FFGFFS_USERFFSWITCHON 
<br><br>Indicates that the user force-feedback switch is currently on, meaning that the device can operate. If the device cannot report the state of the user force-feedback switch, then neither FFGFFS_USERFFSWITCHON nor FFGFFS_USERFFSWITCHOFF should be returned. 
<br><br>FFGFFS_USERFFSWITCHOFF 
<br><br>Indicates that the user force-feedback switch is currently off, meaning that the device cannot operate. If the device cannot report the state of the user force-feedback switch, then neither FFGFFS_USERFFSWITCHON nor FFGFFS_USERFFSWITCHOFF should be returned. 
<br><br>FFGFFS_DEVICELOST 
<br><br>Indicates that the device suffered an unexpected failure and is in an indeterminate state. It must be reset either by unacquiring and reacquiring the device, or by explicitly sending a FFSFFC_RESET command. For example, the device may be lost if the user suspends the computer, causing on-board memory on the device to be lost. 
@field dwLoad A value indicating the percentage of device memory in use. A value of zero indicates that the device memory is completely available. A value of 100 indicates that the device is full
*/
struct ForceFeedbackDeviceState
{
    UInt32   dwSize;
    UInt32   dwState;
    UInt32   dwLoad;

};
typedef struct ForceFeedbackDeviceState ForceFeedbackDeviceState;
typedef ForceFeedbackDeviceState * 	ForceFeedbackDeviceStatePtr;


/*!
@typedef ForceFeedbackVersion
@abstract Used to return plugIn version information.
@discussion
@field apiVersion The version of the plugIn API that is implemented by this driver
@field plugInVersion Vendor-determined version of the plugIn.
*/
struct ForceFeedbackVersion
{
    NumVersion	apiVersion;
    NumVersion	plugInVersion;
};

typedef struct ForceFeedbackVersion ForceFeedbackVersion;
typedef ForceFeedbackVersion * 	ForceFeedbackVersionPtr;

//====================================================================================================================
//	Types
//====================================================================================================================
//
/*!
    @typedef FFEffectDownloadID
    @abstract Unique identification for an effect.
*/
typedef UInt32		FFEffectDownloadID;


//====================================================================================================================
//
// ForceFeedback Device Interface Functions available in version 1.0 of architecture
//
//====================================================================================================================
//
#define IOFORCEFEEDBACKDEVICE_FUNCS_100												\
																					\
	HRESULT	(*ForceFeedbackGetVersion)(		void *					self, 			\
											ForceFeedbackVersion *	version); 		\
																					\
	HRESULT	(*InitializeTerminate)(			void *			self,					\
											NumVersion		forceFeedbackAPIVersion,\
											io_object_t		hidDevice,				\
											boolean_t			begin );				\
																					\
	HRESULT	(*DestroyEffect)(				void *				self,				\
											FFEffectDownloadID	downloadID );		\
																					\
	HRESULT	(*DownloadEffect)(				void *					self,			\
											CFUUIDRef   			effectType,		\
											FFEffectDownloadID *    pDownloadID,	\
                                            FFEFFECT *   			pEffect,		\
											FFEffectParameterFlag	flags );		\
																					\
	HRESULT	(*Escape)(						void *				self,				\
											FFEffectDownloadID	downloadID,			\
											FFEFFESCAPE *   	pEscape	);			\
 																					\
	HRESULT	(*GetEffectStatus)(				void *					self,			\
											FFEffectDownloadID  	downloadID,		\
											FFEffectStatusFlag *	pStatusCode );	\
																					\
	HRESULT	(*GetForceFeedbackCapabilities)(	void *		self,					\
												FFCAPABILITIES * pCapabilities );	\
																					\
	HRESULT	(*GetForceFeedbackState)(		void *						self,				\
											ForceFeedbackDeviceState *	pDeviceState );		\
																					\
	HRESULT	(*SendForceFeedbackCommand)(	void *			self,					\
											FFCommandFlag  	state );				\
																					\
	HRESULT	(*SetProperty)(					void *			self,					\
											FFProperty		property,				\
											void *  		pValue );				\
																					\
	HRESULT	(*StartEffect)(					void *				self,				\
											FFEffectDownloadID  downloadID,			\
											FFEffectStartFlag	mode,				\
											UInt32  		iterations );			\
																					\
	HRESULT	(*StopEffect)(					void *				self,				\
											FFEffectDownloadID  downloadID );

//====================================================================================================================
//
// END OF DeviceInterface Functions available in version 1.0 of this API
//
//====================================================================================================================
//
struct IOForceFeedbackDeviceInterface {
    IUNKNOWN_C_GUTS;
    IOFORCEFEEDBACKDEVICE_FUNCS_100
};

typedef struct IOForceFeedbackDeviceInterface IOForceFeedbackDeviceInterface;
typedef IOForceFeedbackDeviceInterface * IOForceFeedbackDeviceInterfacePtr;


//====================================================================================================================
//
//  •••••  The following is #ifdef out. It is here so that we can header doc this file without intruding in its 
//  •••••  readability.
//
//====================================================================================================================
//
#if 0

struct IOForceFeedbackDeviceInterface {
    IUNKNOWN_C_GUTS;
    
/*! @function ForceFeedbackGetVersion
    @abstract This function is used to determine driver and API version information.
    @discussion
    @param 	self		Pointer to the FFPlugInDriver implementation instance. 
    @param 	version		Pointer to ForceFeedbackVersion structure that is to receive the required info.  See the structure description for details. 
    @result Returns FF_OK if successful, or an error value otherwise. 
*/
	HRESULT	(*ForceFeedbackGetVersion) (void * self, ForceFeedbackVersion * version); 		
																					

/*! @function InitializeTerminate
    @abstract This function is used to "create and destroy" particular device instances.  It provides the FF plug-in driver with all the necessary start-up parameters.
    @discussion
    @param 	self					Pointer to the FFPlugInDriver implementation instance. 
    @param 	forceFeedbackAPIVersion	The version number of FF API that loaded the effect driver.  The plugIn should check that the major version of the forceFeedbackAPI version is the same as the major version of the API at the time the plugIn was compiled.  If the major versions are different, then the plugIn API has changed and the plugIn will NOT be compatible with it. 
<br>
If begin is false, this parameter is ignored. 
    @param 	hidDevice				A device object that can be used by the FF plug-in to establish a connection to and communicate with the device. The caller will release the hidDevice device object with a call to IOObjectRelease() once the FF plug-in completes its InitializeTerminate processing, so a FF plug-in implementation should not make a copy of the io_object_t variable with the intention of using it outside the context of this call.
<br>
If begin is false, this parameter is ignored.  (You can pass NULL.)
    @param 	begin					Nonzero if access to the device is beginning. Zero if the access to the device is ending.  The FF API will call InitializeTerminate( begin=TRUE) when a FF device is first selected for use, and InitializeTerminate( begin=false) when the FF device is no longer needed. 
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_INVALIDPARAM
<br>	FFERR_NOINTERFACE
<br>	FFERR_OUTOFMEMORY
<br> 
*/
	HRESULT	(*InitializeTerminate)(void * self, NumVersion forceFeedbackAPIVersion, io_object_t hidDevice, boolean_t begin );				
																					

/*! @function DestroyEffect
    @abstract This function commands the device to "destroy" a currently downloaded effect. The effect ID and any data that is associated with the effect are freed and available for reallocation.
    @discussion
    @param 	self			Pointer to the FFPlugInDriver implementation instance. 
    @param 	downloadID		Indicates the effect ID that was obtained from the device when the effect was downloaded.
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_INVALIDDOWNLOADID
<br>	FFERR_GENERIC
<br>    FFERR_INTERNAL 
<br> 
*/
	HRESULT	(*DestroyEffect)(void * self, FFEffectDownloadID downloadID );			
																					

/*! @function DownloadEffect
    @abstract This function sends an effect to the device.
    @discussion
    @param 	self			Pointer to the FFPlugInDriver implementation instance. 
    @param 	effectType		Indicates the type of effect being created.  Valid UUIDs are listed as kFFEffectType_* constants in the ForceFeedbackConstants.h file.  (Supported effect types include Sine, Square, Triangle, SawtoothUp, SawtoothDown, Constant, Spring, Damper, etc.).
    @param 	pDownloadID		On entry, this parameter points to the handle of the effect being downloaded. If the parameter points to a zero, then a new effect is downloaded. On exit, the FFEffectDownloadID pointed to by this parameter contains the new effect handle. On failure, the FFEffectDownloadID pointed to by this parameter is set to zero if the effect is lost, or left alone if the effect is still valid with its old parameters. Note that zero is never a valid effect handle.
    @param 	pEffect			The new parameters for the effect.
<br>
IMPORTANT NOTE:  Unlike the IDirectInputEffectDriver specification, the axis and button values are NOT converted to object identifiers before they are handed over to the driver.  In this case, the only supported method used to assign triggers and output axes is through object offsets, defined by the FFJOFS_* constants.  Therefore, if a button is assigned to trigger an effect, FFEFFECT.dwTriggerButton will contain a constant of the form FFJOFS_BUTTONn.  Similarly, output axes will be identified in FFEFFECT.rgdwAxes[n] as FFJOFS_X, FFJOFS_Y, etc.
    @param 	flags			Specifies which portions of the effect information have changed from the effect already on the device. This information is passed to drivers to allow for the optimization of effect modification. If an effect is being modified, a driver may be able to update the effect in its original position and transmit to the device only the information that has changed. Drivers are not, however, required to implement this optimization. All members of the FFEFFECT structure that are pointed to by the pEffect parameter are valid, and a driver may choose simply to update all parameters of the effect at each download.  There may be zero, one, or more of the following: 
<br>
<br>	FFEP_DURATION 
<br>	Indicates the dwDuration member of the FFEFFECT structure is being downloaded for the first time or has changed since its last download. 
<br>	
<br>	FFEP_SAMPLEPERIOD 
<br>	Indicates the dwSamplePeriod member of the FFEFFECT structure is being downloaded for the first time or has changed since its last download. 
<br>	
<br>	FFEP_GAIN 
<br>	Indicates the dwGain member of the FFEFFECT structure is being downloaded for the first time or has changed since its last download. 
<br>	
<br>	FFEP_TRIGGERBUTTON 
<br>	Indicates the dwTriggerButton member of the FFEFFECT structure is being downloaded for the first time or has changed since its last download. 
<br>	
<br>	FFEP_TRIGGERREPEATINTERVAL 
<br>	Indicates the dwTriggerRepeatInterval member of the FFEFFECT structure is being downloaded for the first time or has changed since its last download. 
<br>	
<br>	FFEP_AXES 
<br>	Indicates the cAxes and rgdwAxes members of the FFEFFECT structure are being downloaded for the first time or have changed since their last download. 
<br>	
<br>	FFEP_DIRECTION 
<br>	Indicates the cAxes and rglDirection members of the FFEFFECT structure are being downloaded for the first time or have changed since their last download. (The dwFlags member of the FFEFFECT structure specifies, through FFEFF_CARTESIAN or FFEFF_POLAR, the coordinate system in which the values should be interpreted.) 
<br>	
<br>	FFEP_ENVELOPE 
<br>	Indicates the lpEnvelope member of the FFEFFECT structure is being downloaded for the first time or has changed since its last download. If this flag is set and the lpEnvelope member is a NULL pointer, then the effect is being created with no envelope, or the existing envelope is being deleted. 
<br>	
<br>	FFEP_TYPESPECIFICPARAMS 
<br>	Indicates the cbTypeSpecificParams and lpTypeSpecificParams members of the FFEFFECT structure are being downloaded for the first time or have changed since their last download. 
<br>	
<br>	FFEP_STARTDELAY 
<br>	Indicates the dwStartDelay member of the FFEFFECT structure is being downloaded for the first time or has changed since its last download.
<br>	
<br>	FFEP_START 
<br>	Indicates that the effect is to be restarted from the beginning after the parameters of the effect have been updated. Note that the FFEP_NODOWNLOAD flag overrides the FFEP_START flag. 
<br>	
<br>	FFEP_NORESTART 
<br>	If this flag is not specified, the effect device driver is permitted to restart the effect if doing so is necessary to change the specified parameters. Note that the FFEP_NODOWNLOAD and FFEP_START flags override this flag. 
<br>	
<br>	FFEP_NODOWNLOAD 
<br>	Suppresses the automatic download that is normally performed after the parameters are updated. If this flag is set, the driver should validate parameters without performing an actual download. 
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_DEVICEPAUSED
<br>	FFERR_DEVICEFULL
<br>	FFERR_INVALIDDOWNLOADID
<br>	FFERR_INTERNAL
<br>	FFERR_EFFECTTYPEMISMATCH
<br> 
*/
	HRESULT	(*DownloadEffect)(  void * self, CFUUIDRef effectType, FFEffectDownloadID * pDownloadID,	 
FFEFFECT * pEffect, FFEffectParameterFlag flags ); 		
                                
                                                                								
/*! @function Escape
    @abstract This function escapes to the driver. This method is called in response to an application invoking the FFEffectEscape or FFDeviceEscape methods.
    @discussion
    @param 	self			Pointer to the FFPlugInDriver implementation instance. 
    @param 	downloadID		Specifies the effect at which the command is directed, or zero if the command is directed at the device itself and not any particular effect.
    @param 	pEscape			Pointer to a FFEFFESCAPE structure that describes the command to be sent. On success, the cbOutBuffer member contains the number of output buffer bytes actually used.
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_UNSUPPORTED
<br> 
*/
	HRESULT	(*Escape)( void * self, FFEffectDownloadID downloadID, FFEFFESCAPE * pEscape	);				
 																					

/*! @function GetEffectStatus
    @abstract This function returns the device effect's status.
    @discussion
    @param 	self			Pointer to the FFPlugInDriver implementation instance. 
    @param 	downloadID		Indicates the effect to be queried.
    @param 	pStatusCode		Receives the effect status. The FFEffectStatusFlag pointed to by this parameter should be filled in with one of the following values:
<br>
<br>	FFEGES_PLAYING 
<br>	The effect is still playing. 
<br>	
<br>	FFEGES_NOTPLAYING 
<br>	The effect is not playing. 
    @result Returns FF_OK.
*/
	HRESULT	(*GetEffectStatus)( void * self, FFEffectDownloadID downloadID, FFEffectStatusFlag * pStatusCode );			
																					

/*! @function GetForceFeedbackCapabilities
    @abstract This function escapes to the driver. This method is called in response to an application invoking the FFEffectEscape or FFDevicEscape methods.
    @discussion
    @param 	self				Pointer to the FFPlugInDriver implementation instance. 
    @param 	pCapabilities		Pointer to a FFCAPABILITIES structure that should be filled in with version information describing the hardware, firmware, and driver.
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_INTERNAL
<br>	FFERR_NOINTERFACE
<br> 
*/
	HRESULT	(*GetForceFeedbackCapabilities)( void * self, FFCAPABILITIES * pCapabilities );	
																					

/*! @function GetForceFeedbackState
    @abstract This function returns the state of the device.
    @discussion
    @param 	self				Pointer to the FFPlugInDriver implementation instance. 
    @param 	pDeviceState		Pointer to a ForceFeedbackDeviceState structure that receives the device state. FF API sets the dwSize member of the ForceFeedbackDeviceState structure to sizeof(ForceFeedbackDeviceState) before calling this method.
    @result Returns FF_OK.
*/
	HRESULT	(*GetForceFeedbackState)( void * self, ForceFeedbackDeviceState * pDeviceState );		
																					

/*! @function SendForceFeedbackCommand
    @abstract This function sends a command to the device.
    @discussion
    @param 	self		Pointer to the FFPlugInDriver implementation instance. 
    @param 	state		Indicates the command being sent. That command can be one of the following:
<br>
<br>	FFSFFC_RESET 
<br>	Indicates that playback of any active effects should be been stopped and that all effects should be removed from the device. Once the device has been reset, all effects are no longer valid and must be re-created. 
<br>	
<br>	FFSFFC_STOPALL 
<br>	Indicates that playback of all effects should be stopped. Sending the FFSFFC_STOPALL command is equivalent to invoking the FFEffect_Stop method on all effects that are playing. If the device is in a paused state, the device driver is permitted to lose the paused state. 
<br>	
<br>	FFSFFC_PAUSE 
<br>	Indicates that playback of all effects should be paused. When effects are paused, time "stops" until the FFSFFC_CONTINUE command is sent. For example, suppose an effect of five seconds' duration is started. After one second, all effects are paused. After two more seconds, all effects are continued. The effect should then play for four additional seconds. While a force-feedback device is paused, starting a new effect or modifying existing ones can cause the paused state to be lost. 
<br>	
<br>	FFSFFC_CONTINUE 
<br>	Indicates that playback should be resumed at the point at which it was interrupted for those effects that were paused by a previous FFSCFFC_PAUSE command. 
<br>	
<br>	FFSFFC_SETACTUATORSON 
<br>	Indicates that the device's force-feedback actuators should be enabled. 
<br>	
<br>	FFSFFC_SETACTUATORSOFF 
<br>	Indicates that the device's force-feedback actuators should be disabled. If successful, force-feedback effects are "muted". Note that time continues to elapse while actuators are off. For example, suppose an effect of five seconds' duration is started. After one second, actuators are turned off. After two more seconds, actuators are turned back on. The effect should then play for two additional seconds. 
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_INTERNAL
<br>	FFERR_INVALIDPARAM
<br> 
*/
	HRESULT	(*SendForceFeedbackCommand)( void * self, FFCommandFlag state ); 										


/*! @function SetProperty
    @abstract This function sets properties that define the device behavior.
    @discussion
    @param 	self			Pointer to the FFPlugInDriver implementation instance. 
    @param 	property		The following property values are defined for a FF device:
<br>
<br>	FFPROP_AUTOCENTER 
<br>	Specifies whether the actuated FF axes are self-centering.  This property controls the device’s “default centering spring”.
<br>	The pValue member points to a UInt32 and can be one of the following values. 
<br>	
<br>	0 - OFF: The device should not automatically center when the user releases the device. An application that uses force feedback should disable autocentering before playing effects. 
<br>	
<br>	1 - ON: The device should automatically center when the user releases the device. 
<br>	
<br>	Not all devices support the autocenter property. 
<br>	
<br>	FFPROP_FFGAIN 
<br>	Sets the gain for the device.
<br>	
<br>	The pValue member points to a UInt32 that contains a gain value that is applied to all effects created on the device. The value is an integer in the range from 0 through 10,000, specifying the amount by which effect magnitudes should be scaled for the device. For example, a value of 10,000 indicates that all effect magnitudes are to be taken at face value. A value of 9,000 indicates that all effect magnitudes are to be reduced to 90% of their nominal magnitudes. 
<br>	
<br>	Setting a gain value is useful when an application wants to scale down the strength of all force-feedback effects uniformly, based on user preferences.
    @param 	pValue			Address of the location where the property value is to be read.  This function will assume that the data is valid, and of the correct type. 
    @result If the method succeeds, the return value is FF_OK or FFERR_UNSUPPORTED.
If the method fails, the return value can be one of the following error values:
<br>
<br>	FFERR_INVALIDPARAM
<br> 
*/
	HRESULT	(*SetProperty)( void * self, FFProperty property, void * pValue ); 										


/*! @function StartEffect
    @abstract This function commands the device to play back an effect that was previously loaded.
    @discussion
    @param 	self			Pointer to the FFPlugInDriver implementation instance. 
    @param 	downloadID		Indicates the effect to be played.
    @param 	mode			Specifies how the effect is to affect other effects. Only the mode listed below can be used; all other modes are reserved. For example, the driver never receives the FFES_NODOWNLOAD flag because it is managed by the FF API and not the PlugIn driver. This parameter can be zero, one, or more of the following flags:
<br>
<br>	FFES_SOLO 
<br>	Indicates that all other effects on the device should be stopped before the specified effect is played. If this flag is omitted, the effect is mixed with existing effects that have already started on the device.
    @param 	iterations		Specifies the number of times to perform the effect. If the value is FF_INFINITE, then the effect should be repeated until explicitly stopped or paused.
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_INTERNAL
<br>	FFERR_DEVICEPAUSED
<br>	FFERR_DEVICEFULL
<br>	FFERR_GENERIC
<br>	FFERR_INVALIDDOWNLOADID
<br> 
*/
	HRESULT	(*StartEffect)( void * self, FFEffectDownloadID downloadID, FFEffectStartFlag mode, UInt32 iterations );			
																					
/*! @function StopEffect
    @abstract This function commands the device to stop an effect that was previously started.
    @discussion
    @param 	self			Pointer to the FFPlugInDriver implementation instance. 
    @param 	downloadID		Indicates the effect to be stopped.
    @result Returns FF_OK if successful, or an error value otherwise:
<br>
<br>	FFERR_INTERNAL
<br>	FFERR_GENERIC
<br>	FFERR_INVALIDDOWNLOADID
<br> 
*/
	HRESULT	(*StopEffect)( void * self, UInt32 downloadID );
};

#endif // #if 0 ••• Used for header doc'ing only

__END_DECLS

#endif /* ! _IOFORCEFEEDBACKLIB_H */
