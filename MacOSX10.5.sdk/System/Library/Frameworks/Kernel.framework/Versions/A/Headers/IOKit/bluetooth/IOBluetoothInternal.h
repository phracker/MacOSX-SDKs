/*
	File:		BluetoothInternal.h
	Contains:	Internal types and macros needed by public kernel APIs.
	Copyright:	2003-2007 by Apple, Inc. All rights reserved.
*/

#pragma once

typedef enum IOBluetoothHCIControllerConfigState
{
	kIOBluetoothHCIControllerConfigStateOnline							= 0,	// Controller is configured and ready for clients
	kIOBluetoothHCIControllerConfigStateKernelSetupPending				= 1,	// New controller - kernel setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonSetupPending				= 2,	// New controller - daemon setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonSetupComplete				= 3,	// New controller - daemon setup complete
	kIOBluetoothHCIControllerConfigStateResetPending					= 4,	// HCI reset has been issued
	kIOBluetoothHCIControllerConfigStateKernelPostResetSetupPending		= 5,	// HCI reset complete - kernel setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonPostResetSetupPending		= 6,	// HCI reset complete - daemon setup in progress
	kIOBluetoothHCIControllerConfigStateDaemonPostResetSetupComplete	= 7,	// HCI reset complete - daemon setup complete
	kIOBluetoothHCIControllerConfigStateUninitialized					= 8
} IOBluetoothHCIControllerConfigState;

typedef UInt32 IOBluetoothHCIControllerPowerOptions;
enum
{
	kIOBluetoothHCIControllerPowerOptionPowerOffSupported					= 0x00000001,
	kIOBluetoothHCIControllerPowerOptionWakeFromExistingConnectionSupported	= 0x00000002,
	kIOBluetoothHCIControllerPowerOptionWakeFromNewConnectionSupported		= 0x00000004,
	kIOBluetoothHCIControllerPowerOptionIdleWithConnectionSupported			= 0x00000008	
};

enum IOBluetoothHCIControllerSleepOptions
{
	kIOBluetoothHCIControllerAllowWakeFromExistingConnection				= 0x00000001,
	kIOBluetoothHCIControllerAllowWakeFromNewConnection						= 0x00000002,
	kIOBluetoothHCIControllerTemporaryOnFromIdle							= 0x00000004
};

#define HCI_CONTROLLER_POWER_OFF_SUPPORTED( _controllerPowerOptions )	( ( _controllerPowerOptions & kIOBluetoothHCIControllerPowerOptionPowerOffSupported ) == kIOBluetoothHCIControllerPowerOptionPowerOffSupported )
#define HCI_CONTROLLER_SLEEP_SUPPORTED( _controllerPowerOptions )	\
	( ( _controllerPowerOptions &	\
		( kIOBluetoothHCIControllerPowerOptionWakeFromExistingConnectionSupported |	\
		  kIOBluetoothHCIControllerPowerOptionWakeFromNewConnectionSupported ) ) != 0 )

typedef enum IOBluetoothHCIControllerInternalPowerState
{
	kIOBluetoothHCIControllerInternalPowerStateOff		= 0,
	kIOBluetoothHCIControllerInternalPowerStateOn		= 1,
	kIOBluetoothHCIControllerInternalPowerStateSleep	= 2,
	kIOBluetoothHCIControllerInternalPowerStateIdle		= 3
} IOBluetoothHCIControllerInternalPowerState;

enum IOBluetoothHCIControllerPowerStateOrdinal
{
	kIOBluetoothHCIControllerPowerStateOrdinalOff		= 0,
	kIOBluetoothHCIControllerPowerStateOrdinalIdle		= 1,
	kIOBluetoothHCIControllerPowerStateOrdinalOn		= 2
};

typedef UInt32 IOBluetoothHCIControllerFeatureFlags;

enum
{
	kIOBluetoothHCIControllerFeatureFlagVendorCommandFlowControl	= 0x00000001,
	kIOBluetoothHCIControllerFeatureFlagSCOSupported				= 0x00000002,
	kIOBluetoothHCIControllerFeatureFlagSerializeCommands			= 0x10000000
};

//===========================================================================================================================
//	Private_UnifiedInquiryResult
//===========================================================================================================================

typedef struct	IOBluetoothHCIUnifiedInquiryResult	IOBluetoothHCIUnifiedInquiryResult;
struct	IOBluetoothHCIUnifiedInquiryResult
{
	BluetoothHCIInquiryResult			originalInquiryResult;

	// event code will be either:
	// kBluetoothHCIEventInquiryResult, kBluetoothHCIEventInquiryResultWithRSSI, or kBluetoothHCIEventExtendedInquiryResult

	BluetoothHCIEventCode eventCode;

	// kBluetoothHCIEventExtendedInquiryResult only

	BluetoothHCIExtendedInquiryResponse	extendedInquiryResponse;

	// kBluetoothHCIEventExtendedInquiryResult or kBluetoothHCIEventInquiryResultWithRSSI only

	UInt8								reserved;
	BluetoothHCIRSSIValue				RSSIValue;
};

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0

enum BluetoothHCIExtendedInquiryResponseDataTypesAppleSpecificInfo
{
	kBluetoothHCIExtendedInquiryResponseDataTypeAppleSpecificInfoReserved					=	0x00,
	kBluetoothHCIExtendedInquiryResponseDataTypeAppleSpecificInfoModelIdentifier			=	0x01	/* UTF8String char data */
};

// Move this to BluetoothAssignedNumbers.h, post Leopard

enum BluetoothCompanyIdentifers
{
	kBluetoothCompanyIdentiferEricssonTechnologyLicensing						=	0,
	kBluetoothCompanyIdentiferNokiaMobilePhones									=	1,
	kBluetoothCompanyIdentiferIntel												=	2,
	kBluetoothCompanyIdentiferIBM												=	3,
	kBluetoothCompanyIdentiferToshiba											=	4,
	kBluetoothCompanyIdentifer3Com												=	5,
	kBluetoothCompanyIdentiferMicrosoft											=	6,
	kBluetoothCompanyIdentiferLucent											=	7,
	kBluetoothCompanyIdentiferMotorola											=	8,
	kBluetoothCompanyIdentiferInfineonTechnologiesAG							=	9,
	kBluetoothCompanyIdentiferCambridgeSiliconRadio								=	10,
	kBluetoothCompanyIdentiferSiliconWave										=	11,
	kBluetoothCompanyIdentiferDigianswerAS										=	12,
	kBluetoothCompanyIdentiferTexasInstruments									=	13,
	kBluetoothCompanyIdentiferParthusTechnologies								=	14,
	kBluetoothCompanyIdentiferBroadcom											=	15,
	kBluetoothCompanyIdentiferMitelSemiconductor								=	16,
	kBluetoothCompanyIdentiferWidcomm											=	17,
	kBluetoothCompanyIdentiferZeevo												=	18,
	kBluetoothCompanyIdentiferAtmel												=	19,
	kBluetoothCompanyIdentiferMistubishiElectric								=	20,
	kBluetoothCompanyIdentiferRTXTelecom										=	21,
	kBluetoothCompanyIdentiferKCTechnology										=	22,
	kBluetoothCompanyIdentiferNewlogic											=	23,
	kBluetoothCompanyIdentiferTransilica										=	24,
	kBluetoothCompanyIdentiferRohdeandSchwarz									=	25,
	kBluetoothCompanyIdentiferTTPCom											=	26,
	kBluetoothCompanyIdentiferSigniaTechnologies								=	27,
	kBluetoothCompanyIdentiferConexantSystems									=	28,
	kBluetoothCompanyIdentiferQualcomm											=	29,
	kBluetoothCompanyIdentiferInventel											=	30,
	kBluetoothCompanyIdentiferAVMBerlin											=	31,
	kBluetoothCompanyIdentiferBandspeed											=	32,
	kBluetoothCompanyIdentiferMansella											=	33,
	kBluetoothCompanyIdentiferNEC												=	34,
	kBluetoothCompanyIdentiferWavePlusTechnology								=	35,
	kBluetoothCompanyIdentiferAlcatel											=	36,
	kBluetoothCompanyIdentiferPhilipsSemiconductor								=	37,
	kBluetoothCompanyIdentiferCTechnologies										=	38,
	kBluetoothCompanyIdentiferOpenInterface										=	39,
	kBluetoothCompanyIdentiferRFCMicroDevices									=	40,
	kBluetoothCompanyIdentiferHitachi											=	41,
	kBluetoothCompanyIdentiferSymbolTechnologies								=	42,
	kBluetoothCompanyIdentiferTenovis											=	43,
	kBluetoothCompanyIdentiferMacronixInternational								=	44,
	kBluetoothCompanyIdentiferGCTSemiconductor									=	45,
	kBluetoothCompanyIdentiferNorwoodSystems									=	46,
	kBluetoothCompanyIdentiferMewTelTechnology									=	47,
	kBluetoothCompanyIdentiferSTMicroelectronics								=	48,
	kBluetoothCompanyIdentiferSynopsys											=	49,
	kBluetoothCompanyIdentiferRedMCommunications								=	50,
	kBluetoothCompanyIdentiferCommil											=	51,
	kBluetoothCompanyIdentiferCATC												=	52,
	kBluetoothCompanyIdentiferEclipse											=	53,
	kBluetoothCompanyIdentiferRenesasTechnology									=	54,
	kBluetoothCompanyIdentiferMobilian											=	55,
	kBluetoothCompanyIdentiferTerax												=	56,
	kBluetoothCompanyIdentiferIntegratedSystemSolution							=	57,
	kBluetoothCompanyIdentiferMatsushitaElectricIndustrial						=	58,
	kBluetoothCompanyIdentiferGennum											=	59,
	kBluetoothCompanyIdentiferResearchInMotion									=	60,
	kBluetoothCompanyIdentiferIPextreme											=	61,
	kBluetoothCompanyIdentiferSystemsAndChips									=	62,
	kBluetoothCompanyIdentiferBluetoothSIG										=	63,
	kBluetoothCompanyIdentiferSeikoEpson										=	64,
	kBluetoothCompanyIdentiferIntegratedSiliconSolution							=	65,
	kBluetoothCompanyIdentiferCONWISETechnology									=	66,
	kBluetoothCompanyIdentiferParrotSA											=	67,
	kBluetoothCompanyIdentiferSocketCommunications								=	68,
	kBluetoothCompanyIdentiferAtherosCommunications								=	69,
	kBluetoothCompanyIdentiferMediaTek											=	70,
	kBluetoothCompanyIdentiferBluegiga											=	71,
	kBluetoothCompanyIdentiferMarvellTechnologyGroup							=	72,
	kBluetoothCompanyIdentifer3DSP												=	73,
	kBluetoothCompanyIdentiferAccelSemiconductor								=	74,
	kBluetoothCompanyIdentiferApple												=	76		//	<--- yes, this is correct. There is a 75 but we are not it, nor do I know what company it is.
};


#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0 */

