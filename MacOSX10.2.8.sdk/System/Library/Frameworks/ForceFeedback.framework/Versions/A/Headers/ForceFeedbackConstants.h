//-----------------------------------------------------------------------------
//      File:           ForceFeedbackConstants.h
//      Contains:       Public interfaces for ForceFeedback technology.
//      Copyright:      © 2002 by Apple Computer, Inc. All rights reserved.
//
//-----------------------------------------------------------------------------

#ifndef _FORCEFEEDBACKCONSTANTS_H_
#define _FORCEFEEDBACKCONSTANTS_H_

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!	@header		ForceFeedbackConstants.h
	@abstract	Constants used in the public interfaces to the Force Feedback implementation in Mac OS X.
	@discussion	This header file contains the Effect type UUIDs, type definitions used in the API, force feedback
                        constants and error values used by the API.

*/

//-----------------------------------------------------------------------------
// General defines
//-----------------------------------------------------------------------------
#if !defined( DWORD )
typedef UInt32 DWORD;
typedef DWORD* LPDWORD;
#endif
#if !defined( LONG )
typedef SInt32 LONG;
typedef LONG* LPLONG;
#endif

#define FF_INFINITE                 0xFFFFFFFF

#define FF_DEGREES                  100
#define FF_FFNOMINALMAX             10000
#define FF_SECONDS                  1000000


//-----------------------------------------------------------------------------
// Effect type UUIDs
//-----------------------------------------------------------------------------

// E559C460-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_ConstantForce_ID
    @discussion UUID for a constant force effect type
 */
#define kFFEffectType_ConstantForce_ID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0xE5, 0x59, 0xC4, 0x60, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)

// E559C461-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_RampForce_ID
    @discussion UUID for a ramp force effect type
 */
#define kFFEffectType_RampForce_ID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0xE5, 0x59, 0xC4, 0x61, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C462-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_Square_ID
    @discussion UUID for a square wave effect type
 */
#define kFFEffectType_Square_ID CFUUIDGetConstantUUIDWithBytes(NULL, 		\
    0xE5, 0x59, 0xC4, 0x62, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C463-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_Sine_ID
    @discussion UUID for a sine wave effect type
 */
#define kFFEffectType_Sine_ID CFUUIDGetConstantUUIDWithBytes(NULL, 		\
    0xE5, 0x59, 0xC4, 0x63, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C464-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_Sine_ID
    @discussion UUID for a sine wave effect type
 */
#define kFFEffectType_Triangle_ID CFUUIDGetConstantUUIDWithBytes(NULL, 		\
    0xE5, 0x59, 0xC4, 0x64, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C465-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_SawtoothUp_ID
    @discussion UUID for a upwards sawtooth wave effect type
 */
#define kFFEffectType_SawtoothUp_ID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0xE5, 0x59, 0xC4, 0x65, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C466-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_SawtoothDown_ID
    @discussion UUID for a downwards sawtooth wave effect type
 */
#define kFFEffectType_SawtoothDown_ID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0xE5, 0x59, 0xC4, 0x66, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C467-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_Spring_ID
    @discussion UUID for a spring effect type
 */
#define kFFEffectType_Spring_ID CFUUIDGetConstantUUIDWithBytes(NULL, 		\
    0xE5, 0x59, 0xC4, 0x67, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C468-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_Damper_ID
    @discussion UUID for a damper effect type
 */
#define kFFEffectType_Damper_ID CFUUIDGetConstantUUIDWithBytes(NULL, 		\
    0xE5, 0x59, 0xC4, 0x68, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C469-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_Inertia_ID
    @discussion UUID for an inertia effect type
 */
#define kFFEffectType_Inertia_ID CFUUIDGetConstantUUIDWithBytes(NULL, 		\
    0xE5, 0x59, 0xC4, 0x69, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
// E559C46A-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_Friction_ID
    @discussion UUID for a friction effect type
 */
#define kFFEffectType_Friction_ID CFUUIDGetConstantUUIDWithBytes(NULL, 		\
    0xE5, 0x59, 0xC4, 0x6A, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)

// E559C46B-C5CD-11D6-8A1C-00039353BD00
/*!
    @defined kFFEffectType_CustomForce_ID
    @discussion UUID for a custom force effect type
 */
#define kFFEffectType_CustomForce_ID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0xE5, 0x59, 0xC4, 0x6B, 0xC5, 0xCD, 0x11, 0xD6, 				\
    0x8A, 0x1C, 0x00, 0x03, 0x93, 0x53, 0xBD, 0x00)
    
//-----------------------------------------------------------------------------
// Effect definition constants
//-----------------------------------------------------------------------------

// FFEFFECT.dwFlags constants
// IMPORTANT NOTE:  OBJECT IDS cannot be used to identify trigger buttons
// in FFEFFECT.dwTriggerButton, and output axes in FFEFFECT.rgdwAxes[n].
// Please use object offsets (FFJOFS_* constants), the only supported method.
// #define FFEFF_OBJECTIDS             0x00000001
#define FFEFF_OBJECTOFFSETS         0x00000002

typedef UInt32		FFCoordinateSystemFlag;
enum
{
    FFEFF_CARTESIAN             = 0x00000010,
    FFEFF_POLAR                 = 0x00000020,
    FFEFF_SPHERICAL             = 0x00000040
};

// Effect Parameter flags for use in calls to FFEffectGetParameters() and FFEffectSetParameters()
//
typedef UInt32		FFEffectParameterFlag;
enum
{
    FFEP_DURATION               = 0x00000001,
    FFEP_SAMPLEPERIOD           = 0x00000002,
    FFEP_GAIN                   = 0x00000004,
    FFEP_TRIGGERBUTTON          = 0x00000008,
    FFEP_TRIGGERREPEATINTERVAL  = 0x00000010,
    FFEP_AXES                   = 0x00000020,
    FFEP_DIRECTION              = 0x00000040,
    FFEP_ENVELOPE               = 0x00000080,
    FFEP_TYPESPECIFICPARAMS     = 0x00000100,
    FFEP_STARTDELAY            	= 0x00000200,
    FFEP_ALLPARAMS              = 0x000003FF,
    FFEP_START                  = 0x20000000,
    FFEP_NORESTART              = 0x40000000,
    FFEP_NODOWNLOAD             = 0x80000000,
    FFEB_NOTRIGGER              = 0xFFFFFFFF
};

// Effect Parameter flags for use in calls to FFEffectStart()
//
typedef UInt32		FFEffectStartFlag;
enum
{
    FFES_SOLO                   = 0x00000001,
    FFES_NODOWNLOAD             = 0x80000000
};

// Effect Parameter flags for use in calls to FFEffectGetEffectStatus()
//
typedef UInt32		FFEffectStatusFlag;
enum
{
    FFEGES_NOTPLAYING           = 0x00000000,
    FFEGES_PLAYING              = 0x00000001,
    FFEGES_EMULATED             = 0x00000002
};

// command flags for FFDeviceSendForceFeedbackCommand()
//
typedef UInt32		FFCommandFlag;
enum
{
     FFSFFC_RESET            = 0x00000001,
     FFSFFC_STOPALL          = 0x00000002,
     FFSFFC_PAUSE            = 0x00000004,
     FFSFFC_CONTINUE         = 0x00000008,
     FFSFFC_SETACTUATORSON   = 0x00000010,
     FFSFFC_SETACTUATORSOFF  = 0x00000020
};

// device state flags returned by FFDeviceGetForceFeedbackState()
//
typedef UInt32		FFState;
enum
{
     FFGFFS_EMPTY            = 0x00000001,
     FFGFFS_STOPPED          = 0x00000002,
     FFGFFS_PAUSED           = 0x00000004,
     FFGFFS_ACTUATORSON      = 0x00000010,
     FFGFFS_ACTUATORSOFF     = 0x00000020,
     FFGFFS_POWERON          = 0x00000040,
     FFGFFS_POWEROFF         = 0x00000080,
     FFGFFS_SAFETYSWITCHON   = 0x00000100,
     FFGFFS_SAFETYSWITCHOFF  = 0x00000200,
     FFGFFS_USERFFSWITCHON   = 0x00000400,
     FFGFFS_USERFFSWITCHOFF  = 0x00000800,
     FFGFFS_DEVICELOST       = 0x80000000
};


// axis and button "field offsets",
// used in
//	FFEFFECT.dwTriggerButton
//	FFEFFECT.rgdwAxes[n]
#define FFJOFS_X            0
#define FFJOFS_Y            4
#define FFJOFS_Z            8
#define FFJOFS_RX           12
#define FFJOFS_RY           16
#define FFJOFS_RZ           20
#define FFJOFS_SLIDER(n)   (24 + (n) * sizeof(LONG))
#define FFJOFS_POV(n)      (32 + (n) * sizeof(DWORD))
#define FFJOFS_BUTTON(n)   (48 + (n))
#define FFJOFS_BUTTON0      FFJOFS_BUTTON(0)
#define FFJOFS_BUTTON1      FFJOFS_BUTTON(1)
#define FFJOFS_BUTTON2      FFJOFS_BUTTON(2)
#define FFJOFS_BUTTON3      FFJOFS_BUTTON(3)
#define FFJOFS_BUTTON4      FFJOFS_BUTTON(4)
#define FFJOFS_BUTTON5      FFJOFS_BUTTON(5)
#define FFJOFS_BUTTON6      FFJOFS_BUTTON(6)
#define FFJOFS_BUTTON7      FFJOFS_BUTTON(7)
#define FFJOFS_BUTTON8      FFJOFS_BUTTON(8)
#define FFJOFS_BUTTON9      FFJOFS_BUTTON(9)
#define FFJOFS_BUTTON10     FFJOFS_BUTTON(10)
#define FFJOFS_BUTTON11     FFJOFS_BUTTON(11)
#define FFJOFS_BUTTON12     FFJOFS_BUTTON(12)
#define FFJOFS_BUTTON13     FFJOFS_BUTTON(13)
#define FFJOFS_BUTTON14     FFJOFS_BUTTON(14)
#define FFJOFS_BUTTON15     FFJOFS_BUTTON(15)
#define FFJOFS_BUTTON16     FFJOFS_BUTTON(16)
#define FFJOFS_BUTTON17     FFJOFS_BUTTON(17)
#define FFJOFS_BUTTON18     FFJOFS_BUTTON(18)
#define FFJOFS_BUTTON19     FFJOFS_BUTTON(19)
#define FFJOFS_BUTTON20     FFJOFS_BUTTON(20)
#define FFJOFS_BUTTON21     FFJOFS_BUTTON(21)
#define FFJOFS_BUTTON22     FFJOFS_BUTTON(22)
#define FFJOFS_BUTTON23     FFJOFS_BUTTON(23)
#define FFJOFS_BUTTON24     FFJOFS_BUTTON(24)
#define FFJOFS_BUTTON25     FFJOFS_BUTTON(25)
#define FFJOFS_BUTTON26     FFJOFS_BUTTON(26)
#define FFJOFS_BUTTON27     FFJOFS_BUTTON(27)
#define FFJOFS_BUTTON28     FFJOFS_BUTTON(28)
#define FFJOFS_BUTTON29     FFJOFS_BUTTON(29)
#define FFJOFS_BUTTON30     FFJOFS_BUTTON(30)
#define FFJOFS_BUTTON31     FFJOFS_BUTTON(31)

// defines for FFDeviceGetForceFeedbackProperty() and FFDeviceSetForceFeedbackProperty()
//
typedef UInt32		FFProperty;
enum
{
    FFPROP_FFGAIN           = 1,
    FFPROP_AUTOCENTER       = 3
};

// flags for FFDeviceSetCooperativeLevel()
//
typedef UInt32		FFCooperativeLevelFlag;
enum
{
    FFSCL_EXCLUSIVE     = 0x00000001,
    FFSCL_NONEXCLUSIVE  = 0x00000002,
    FFSCL_FOREGROUND    = 0x00000004,
    FFSCL_BACKGROUND    = 0x00000008
};

// types used in FFCAPABILITIES structure
//
typedef UInt32		FFCapabilitiesEffectType;
enum
{
    FFCAP_ET_CONSTANTFORCE	= 0x00000001,
    FFCAP_ET_RAMPFORCE		= 0x00000002,
    FFCAP_ET_SQUARE		= 0x00000004,
    FFCAP_ET_SINE		= 0x00000008,
    FFCAP_ET_TRIANGLE		= 0x00000010,
    FFCAP_ET_SAWTOOTHUP		= 0x00000020,
    FFCAP_ET_SAWTOOTHDOWN	= 0x00000040,
    FFCAP_ET_SPRING		= 0x00000080,
    FFCAP_ET_DAMPER		= 0x00000100,
    FFCAP_ET_INERTIA		= 0x00000200,
    FFCAP_ET_FRICTION		= 0x00000400,
    FFCAP_ET_CUSTOMFORCE	= 0x00000800
};

typedef UInt32		FFCapabilitiesEffectSubType;
enum
{
    FFCAP_ST_KINESTHETIC	= 1,
    FFCAP_ST_VIBRATION		= 2
};


//-----------------------------------------------------------------------------
// Error return values
//-----------------------------------------------------------------------------

/*!
    @defined FF_OK
    @discussion The operation completed successfully.
*/
#define FF_OK                           S_OK

/*!
    @defined FF_FALSE
    @discussion The operation did not complete successfully.
*/
#define FF_FALSE                           S_FALSE

/*!
    @defined FF_DOWNLOADSKIPPED
 *  @discussion 
 *  The parameters of the effect were successfully updated by
 *  FFEffectSetParameters, but the effect was not
 *  downloaded because the FFEP_NODOWNLOAD flag was passed.
 */
#define FF_DOWNLOADSKIPPED              ((HRESULT)0x00000003L)

/*!
    @defined FF_EFFECTRESTARTED
 *  @discussion 
 *  The parameters of the effect were successfully updated by
 *  FFEffectSetParameters, but in order to change
 *  the parameters, the effect needed to be restarted.
 */
#define FF_EFFECTRESTARTED              ((HRESULT)0x00000004L)

/*!
    @defined FF_TRUNCATED
 *  @discussion 
 *  The parameters of the effect were successfully updated by
 *  FFEffectSetParameters, but some of them were
 *  beyond the capabilities of the device and were truncated.
 */
#define FF_TRUNCATED                    ((HRESULT)0x00000008L)

/*!
    @defined FF_TRUNCATEDANDRESTARTED
 *  @discussion 
 *  Equal to FF_EFFECTRESTARTED | FF_TRUNCATED.
 */
#define FF_TRUNCATEDANDRESTARTED        ((HRESULT)0x0000000CL)

/*!
    @defined FFERR_DEVICENOTREG
 *  @discussion 
 * The device or device instance or effect is not registered.
 */
#define FFERR_DEVICENOTREG              REGDB_E_CLASSNOTREG

/*!
    @defined FFERR_INVALIDPARAM
 *  @discussion 
 * An invalid parameter was passed to the returning function,
 * or the object was not in a state that admitted the function
 * to be called.
 */
#define FFERR_INVALIDPARAM              E_INVALIDARG

/*!
    @defined FFERR_NOINTERFACE
 *  @discussion 
 * The specified interface is not supported by the object
 */
#define FFERR_NOINTERFACE               E_NOINTERFACE

/*!
    @defined FFERR_GENERIC
 *  @discussion 
 * An undetermined error occurred.
 */
#define FFERR_GENERIC                   E_FAIL

/*!
    @defined FFERR_OUTOFMEMORY
 *  @discussion 
 * Couldn't allocate sufficient memory to complete the caller's request.
 */
#define FFERR_OUTOFMEMORY               E_OUTOFMEMORY

/*!
    @defined FFERR_UNSUPPORTED
 *  @discussion 
 * The function called is not supported at this time
 */
#define FFERR_UNSUPPORTED               E_NOTIMPL

#ifndef E_PENDING
/*!
    @defined E_PENDING
 *  @discussion 
 * Data is not yet available.
 */
#define E_PENDING                       0x8000000AL
#endif

/*!
    @defined FFERR_DEVICEFULL
 *  @discussion 
 * The device is full.
 */
#define FFERR_DEVICEFULL                0x80040201L

/*!
    @defined FFERR_MOREDATA
 *  @discussion 
 * Not all the requested information fit into the buffer.
 */
#define FFERR_MOREDATA                  0x80040202L

/*!
    @defined FFERR_NOTDOWNLOADED
 *  @discussion 
 * The effect is not downloaded.
 */
#define FFERR_NOTDOWNLOADED             0x80040203L

/*!
    @defined FFERR_HASEFFECTS
 *  @discussion 
 *  The device cannot be reinitialized because there are still effects
 *  attached to it.
 */
#define FFERR_HASEFFECTS                0x80040204L

/*!
    @defined FFERR_INCOMPLETEEFFECT
 *  @discussion 
 *  The effect could not be downloaded because essential information
 *  is missing.  For example, no axes have been associated with the
 *  effect, or no type-specific information has been created.
 */
#define FFERR_INCOMPLETEEFFECT          0x80040206L

/*!
    @defined FFERR_EFFECTPLAYING
 *  @discussion 
 *  An attempt was made to modify parameters of an effect while it is
 *  playing.  Not all hardware devices support altering the parameters
 *  of an effect while it is playing.
 */
#define FFERR_EFFECTPLAYING             0x80040208L

/*!
    @defined FFERR_UNPLUGGED
 *  @discussion 
 *  The operation could not be completed because the device is not
 *  plugged in.
 */
#define FFERR_UNPLUGGED                 0x80040209L


//
// Mac OS X specific
//

/*!
    @defined FFERR_INVALIDDOWNLOADID
 *  @discussion 
 * The effect index provided by the API in downloadID is not recognized by the
 * IOForceFeedbackLib driver.
 */
#define FFERR_INVALIDDOWNLOADID         0x80040300
 
/*!
    @defined FFERR_DEVICEPAUSED
 *  @discussion 
 * When the device is paused via a call to FFDeviceSendForceFeedbackCommand(),
 * other operations such as modifying existing effect parameters and creating 
 * new effects are not allowed.
 */
#define FFERR_DEVICEPAUSED              0x80040301

/*!
    @defined FFERR_INTERNAL
 *  @discussion 
 * The IOForceFededbackLib driver has detected an internal fault.  Often this
 * occurs because of an unexpected internal code path.
 */
#define FFERR_INTERNAL                  0x80040302

/*!
    @defined FFERR_EFFECTTYPEMISMATCH
 *  @discussion 
 * The IOForceFededbackLib driver has received an effect modification request
 * whose basic type does not match the defined effect type for the given effect.
 */
#define FFERR_EFFECTTYPEMISMATCH        0x80040303

/*!
    @defined FFERR_UNSUPPORTEDAXIS
 *  @discussion 
 * The effect includes one or more axes that the device does not support.
 */
#define FFERR_UNSUPPORTEDAXIS           0x80040304

/*!
    @defined FFERR_NOTINITIALIZED
 *  @discussion 
 * This object has not been initialized
 */
#define FFERR_NOTINITIALIZED            0x80040305

/*!
    @defined FFERR_EFFECTTYPENOTSUPPORTED
 *  @discussion 
 * The effect type requested is not explicitly supported by the particular device.
 */
#define FFERR_EFFECTTYPENOTSUPPORTED    0x80040306

/*!
    @defined FFERR_DEVICERELEASED
 *  @discussion 
 * The device has been released.
 */
#define FFERR_DEVICERELEASED            0x80040307

#ifdef __cplusplus
}       
#endif

#endif // _FORCEFEEDBACKCONSTANTS_H_

