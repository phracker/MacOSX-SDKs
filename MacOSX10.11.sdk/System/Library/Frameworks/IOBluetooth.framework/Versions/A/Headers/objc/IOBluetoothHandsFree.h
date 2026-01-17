/*
 File:		BluetoothHandsFree.h
 Copyright:	(c) 2010 by Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/objc/IOBluetoothDevice.h>
#import <IOBluetooth/objc/IOBluetoothSDPServiceRecord.h>

#import <CoreAudio/AudioHardware.h>

/*!
 @header
 @abstract	Hands free superclass. Superclass of IOBluetoothHandsFreeDevice or IOBluetoothHandsFreeAudioGateway.
 			Contains the common code used to support the Bluetoooth hands free profile.
 @copyright	(c) 2010 by Apple Inc. All rights reserved.
 */

// HFP spec 5.3
enum  {
	IOBluetoothHandsFreeDeviceFeatureNone					= (0),
	IOBluetoothHandsFreeDeviceFeatureECAndOrNRFunction		= (1<<0),
	IOBluetoothHandsFreeDeviceFeatureThreeWayCalling		= (1<<1),
	IOBluetoothHandsFreeDeviceFeatureCLIPresentation		= (1<<2),
	IOBluetoothHandsFreeDeviceFeatureVoiceRecognition		= (1<<3),
	IOBluetoothHandsFreeDeviceFeatureRemoteVolumeControl	= (1<<4),
	IOBluetoothHandsFreeDeviceFeatureEnhancedCallStatus		= (1<<5),
	IOBluetoothHandsFreeDeviceFeatureEnhancedCallControl	= (1<<6)
};

typedef NSUInteger IOBluetoothHandsFreeDeviceFeatures;

//HFP spec 5.3
enum {
	IOBluetoothHandsFreeAudioGatewayFeatureNone						= (0),
	IOBluetoothHandsFreeAudioGatewayFeatureThreeWayCalling			= (1<<0),
	IOBluetoothHandsFreeAudioGatewayFeatureECAndOrNRFunction		= (1<<1),
	IOBluetoothHandsFreeAudioGatewayFeatureVoiceRecognition			= (1<<2),
	IOBluetoothHandsFreeAudioGatewayFeatureInBandRingTone			= (1<<3),
	IOBluetoothHandsFreeAudioGatewayFeatureAttachedNumberToVoiceTag	= (1<<4),
	IOBluetoothHandsFreeAudioGatewayFeatureRejectCallCapability		= (1<<5),
	IOBluetoothHandsFreeAudioGatewayFeatureEnhancedCallStatus		= (1<<6),
	IOBluetoothHandsFreeAudioGatewayFeatureEnhancedCallControl		= (1<<7),
	IOBluetoothHandsFreeAudioGatewayFeatureExtendedErrorResultCodes	= (1<<8)
};

typedef NSUInteger IOBluetoothHandsFreeAudioGatewayFeatures;

// HFP spec 4.33.2
enum {
	IOBluetoothHandsFreeCallHoldMode0	= 1<<0,		// Releases all held calls or sets User Determined User Busy for a waiting call
	IOBluetoothHandsFreeCallHoldMode1	= 1<<1,		// Releases all active calls (if any exist) and accepts the other (held or waiting) call
	IOBluetoothHandsFreeCallHoldMode1idx= 1<<2,		// Releases specified active call only (<idx>)
	IOBluetoothHandsFreeCallHoldMode2	= 1<<3,		// Places all active calls (if any exist) on hold and accepts the other (held or waiting) call
	IOBluetoothHandsFreeCallHoldMode2idx= 1<<4,		// Request private consultation mode with specified call (<idx>). Place all calls on hold EXCEPT the call indicated by <idx>
	IOBluetoothHandsFreeCallHoldMode3	= 1<<5,		// Adds a held call to the conversation
	IOBluetoothHandsFreeCallHoldMode4	= 1<<6		// Connectes the two calls and disconnects the subscriber from both calls (Explicit call transfer).
};

typedef NSUInteger IOBluetoothHandsFreeCallHoldModes;

// HandsFreeIndicators (AT+CIND?) HFP spec 4.33.2
// Hands free indicator constants
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeIndicatorService;	/* 0 if no service; 1 otherwise */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeIndicatorCall;		/* 0 if no call active; 1 otherwise */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeIndicatorCallSetup;	/* 0 if no call in setup, 1 for incoming, 2 for outgoing, 3 remote party is being alerted */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeIndicatorCallHeld;	/* 0 if no call is held, 1 if a call is held and an active call exists, 2 if a call is held and no active call */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeIndicatorSignal;	/* 0-5 0 represents a weak signal */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeIndicatorRoam;		/* 0 if not roaming; 1 otherwise */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeIndicatorBattChg;	/* 0-5 0 represents a low battery charge */

// Hands free current call dictionary keys
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallIndex;			/* Index of the call starting with 1 - Calls hold their index and new calls get the lowest index */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallDirection;		/* 0 if outgoing, 1 if incoming */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallStatus;			/* 0 if active, 1 if held, 2 if dialing (outgoing), 3 if alerting (outgoing), 4 if incoming, 5 if waiting (incoming) */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallMode;			/* 0 if voice, 1 for data, 2 for fax */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallMultiparty;		/* 0 if not multiparty, 1 if multiparty */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallNumber;			/* Optional - the remote number */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallType;			/* Optional - the format of the number */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothHandsFreeCallName;			/* Optional - the remote caller's name */

enum {
	IOBluetoothSMSModePDU,
	IOBluetoothSMSModeText
};

typedef NSUInteger IOBluetoothSMSMode;

// 3GPP TS 07.05 v7.0.1
// +CSMS
enum {
	IOBluetoothHandsFreePhase2SMSSupport				= 1<<0,
	IOBluetoothHandsFreePhase2pSMSSupport				= 1<<1,
	IOBluetoothHandsFreeManufactureSpecificSMSSupport	= 1<<2
};

typedef NSUInteger IOBluetoothHandsFreeSMSSupport;

enum {
	IOBluetoothHandsFreePDUStatusRecUnread	= 0,
	IOBluetoothHandsFreePDUStatusRecRead	= 1,
	IOBluetoothHandsFreePDUStatusStoUnsent	= 2,
	IOBluetoothHandsFreePDUStatusStoSent	= 3,
	IOBluetoothHandsFreePDUStatusAll		= 4
};

typedef NSUInteger IOBluetoothHandsFreePDUMessageStatus;

// Hands free SMS dictionary keys
// 3GPP TS 03.40 9.2.2.1 and 9.2.3
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUServicCenterAddress;		/* Service Center's number */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUServiceCenterAddressType;	/* Format of the service center number */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUType;						/* TP-MTI TP-MMS TP-RP TP-UDHI TP-SRI */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUOriginatingAddress;		/* Sender's number */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUOriginatingAddressType;	/* Format of sender's number */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUProtocolID;				/* Protocol of the message content */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUTimestamp;				/* Time the PDU was sent */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUEncoding;					/* How the PDU is encoded */
IOBLUETOOTH_EXPORT NSString * const IOBluetoothPDUUserData;					/* PDU's payload */


@class IOBluetoothRFCOMMChannel;
@class IOBluetoothHandsFreeExpansion;

@protocol IOBluetoothHandsFreeDelegate;

/*!
 @class IOBluetoothHandsFree
 @abstract Hands free profile class.
 @discussion Superclass of IOBluetoothHandsFreeDevice and IOBluetoothHandsFreeAudioGateway classes.
			 Contains the common code used to support the bluetoooth hands free profile.
 @coclass IOBluetoothHandsFreeDevice
 @coclass IOBluetoothHandsFreeAudioGateway
 */
NS_CLASS_AVAILABLE(10_7, NA)
@interface IOBluetoothHandsFree : NSObject {
    IOBluetoothRFCOMMChannel *		_rfcommChannel;
	IOBluetoothUserNotification *	_rfcommChannelNotification;
    
	uint32_t						_supportedFeatures;
	
	void *							_reserved1;
    
	float							_previousInputVolume;
	float							_previousOutputVolume;
	BOOL							_previousOutputMuted;
    
	IOBluetoothDevice *				_device;
	BluetoothRFCOMMChannelID		_deviceRFCOMMChannelID;
	uint32_t						_deviceSupportedFeatures;
	uint32_t						_deviceCallHoldModes;
	uint32_t						_deviceSupportedSMSServices;
	
	NSMutableArray *				_statusIndicators;
	int								_handsFreeState;
	IOBluetoothSMSMode				_SMSMode;
	BOOL							_SMSEnabled;
    
    BOOL							_connectSCOAfterSLCConnected;

    IOBluetoothHandsFreeExpansion *	_reserved;
}


/*!
 @method		supportedFeatures
 @abstract		Return supported features
 @discussion	Returns the supported features bitmap. The values are described in “IOBluetoothHandsFreeDeviceFeatures and IOBluetoothHandsFreeAudioGatewayFeatures.”
 @result		The supported features bitmap
 */
/*!
 @method		setSupportedFeatures:featuresBitmap
 @abstract		Set the supported features
 @discussion	Sets the supported features bitmap. The values are described in “IOBluetoothHandsFreeDeviceFeatures and IOBluetoothHandsFreeAudioGatewayFeatures.”
 @param			featuresBitmap The features bitmap
 */
@property (assign)				uint32_t					supportedFeatures NS_AVAILABLE_MAC(10_7);

/*!
 @method		inputVolume
 @abstract		Return the input volume
 @discussion	Returns the input volume between 0 and 1. 0 is the same as mute.
 @result		The input volume
 */
/*!
 @method		setInputVolume:newVolume
 @abstract		Set the input volume
 @discussion	Sets the input volume between 0 and 1. 0 is the same as mute.
 @param			newVolume The new input volume
 */
@property (assign)				float						inputVolume NS_AVAILABLE_MAC(10_7);

/*!
 @method		isInputMuted
 @abstract		Return the input mute state.
 @discussion	Returns the inputs mute state.
 @result		YES if muted; otherwise NO.
 */
/*!
 @method		setInputMuted:muted
 @abstract		Set the input mute state.
 @discussion	Sets the inputs mute state.
 @param			muted YES if muted; otherwise NO.
 */
@property (assign, getter=isInputMuted)	BOOL				inputMuted NS_AVAILABLE_MAC(10_7);

/*!
 @method		outputVolume
 @abstract		Return the output volume
 @discussion	Returns the output volume between 0 and 1. 0 is the same as mute.
 @result		The output volume
 */
/*!
 @method		setOutputVolume:newVolume
 @abstract		Set the output volume
 @discussion	Sets the output volume between 0 and 1. 0 is the same as mute.
 @param			newVolume The new output volume
 */
@property (assign)				float						outputVolume NS_AVAILABLE_MAC(10_7);

/*!
 @method		isOutputMuted
 @abstract		Return the output mute state.
 @discussion	Returns the outputs mute state.
 @result		YES if muted; otherwise NO.
 */
/*!
 @method		setOutputMuted:muted
 @abstract		Set the output mute state.
 @discussion	Sets the outputs mute state.
 @param			muted YES if muted; otherwise NO.
 */
@property (assign, getter=isOutputMuted)	BOOL			outputMuted NS_AVAILABLE_MAC(10_7);

/*!
 @method		device
 @abstract		Return the IOBluetoothDevice.
 @discussion	Returns the IOBluetoothDevice to connect with.
 @result		The IOBluetoothDevice object
 */
@property (retain, readonly)	IOBluetoothDevice * 		device NS_AVAILABLE_MAC(10_7);

/*!
 @method		deviceSupportedFeatures
 @abstract		Return the device's supported features.
 @discussion	Returns the device's supported features bitmap. The values are described in “IOBluetoothHandsFreeDeviceFeatures and IOBluetoothHandsFreeAudioGatewayFeatures.”
 @result		The device features bitmap
 */
@property (readonly)			uint32_t					deviceSupportedFeatures NS_AVAILABLE_MAC(10_7);

/*!
 @method		deviceSupportedSMSServices
 @abstract		Return the device's supported SMS services.
 @discussion	Returns the device's supported SMS services bitmap. The values are described in “IOBluetoothHandsFreeSMSSupport.”
 @result		The SMS services supported
 */
@property (readonly)			uint32_t					deviceSupportedSMSServices NS_AVAILABLE_MAC(10_7);

/*!
 @method		deviceCallHoldModes
 @abstract		Return the device's supported call hold modes.
 @discussion	Returns the device's supported call hold modes bitmap. The values are described in “IOBluetoothHandsFreeCallHoldModes.”
 @result		The SMS services supported
 */
@property (readonly)			uint32_t					deviceCallHoldModes NS_AVAILABLE_MAC(10_7);

/*!
 @method		SMSMode
 @abstract		Return the device's SMS mode.
 @discussion	Returns the device's SMS mode. The values are described in “IOBluetoothSMSMode.”
 @result		The SMS mode
 */
@property (readonly)			IOBluetoothSMSMode			SMSMode NS_AVAILABLE_MAC(10_7);

/*!
 @method		isSMSEnabled
 @abstract		Return YES if the device has SMS enabled.
 @discussion	Returns YES if the device has SMS enabled (by responding to a CMGF command). NO if the device has not set an SMS mode or doesn't support SMS.
 @result		YES if the device has SMSEnabled; otherwise, NO.
 */
@property (readonly, getter=isSMSEnabled)	BOOL			SMSEnabled NS_AVAILABLE_MAC(10_7);

/*!
 @method		delegate
 @abstract		Return the delegate
 @discussion	Returns the hands free object's delegate.
 @result		The delegate for the hands free object or nil if it doesn't have a delegate.
 */
/*!
 @method		setDelegate:newDelegate
 @abstract		Sets the hands free object’s delegate to a given object or removes an existing delegate.
 @discussion	A IOBluetoothHandsFree delegate can optionally respond to any of the delegate methods in IOBluetoothHandsFreeDelegate and any subclasses delegates.
 @param			newDelegate The delegate for the hands free object. Pass nil to remove an existing delegate.
 */
@property (assign)	id <IOBluetoothHandsFreeDelegate>	delegate NS_AVAILABLE_MAC(10_7);


/*!
 @method		indicator:indicatorName
 @abstract		Return an indicator's value
 @discussion	Returns an indicator's value.
 @param			indicatorName  See  “Hands free indicator constants," for standard indicator names.
 */
- (int)indicator:(NSString *)indicatorName NS_AVAILABLE_MAC(10_7);

/*!
 @method		setIndicator:indicatorName:indicatorValue
 @abstract		Set an indicator's value
 @discussion	Sets an indicator's value.
 @param			indicatorName  See  “Hands free indicator constants," for standard indicator names.
 @param			indicatorValue Will set the indicator value as long as it is within the min and max values allowed.
 */
- (void)setIndicator:(NSString *)indicatorName value:(int)indicatorValue NS_AVAILABLE_MAC(10_7);

/*!
 @method		initWithDevice:delegate:
 @abstract		Create a new IOBluetoothHandsFree object
 @discussion	This method should be called on a subclass (IOBluetoothHandsFreeDevice or IOBluetoothHandsFreeAudioGateway) to get full functionality.
 @param			device An IOBluetoothDevice
 @param			inDelegate An object to act as delegate that implements the IOBluetoothHandsFreeDelegate protocol.
 @result		A newly created IOBluetoothHandsFreeAudioGateway object on success, nil on failure
 */
- (instancetype)initWithDevice:(IOBluetoothDevice *)device delegate:(id <IOBluetoothHandsFreeDelegate>)inDelegate NS_AVAILABLE_MAC(10_7);

/*!
 @method		connect
 @abstract		Connect to the device
 @discussion	Connects to the device and sets up a service level connection (RFCOMM channel).
 				Delegate methods will be called once the connection is complete or a failure occurs.
 */
- (void)connect NS_AVAILABLE_MAC(10_7);

/*!
 @method		disconnect
 @abstract		Disconnect from the device
 @discussion	Disconnects from the device, closes the SCO and service level connection if they are connected.
 				Delegate methods will be called once the disconnection is complete.
 */
- (void)disconnect NS_AVAILABLE_MAC(10_7);

/*!
 @method		isConnected
 @abstract		Determine if there is a serivice level connection to the device
 @discussion	Determines if there is a serivice level connection to the device.
 @result		YES if there is a serivice level connection to the device; otherwise, NO.
 */
- (BOOL)isConnected NS_AVAILABLE_MAC(10_7);

/*!
 @method		connectSCO
 @abstract		Open a SCO connection with the device
 @discussion	Opens a SCO connection with the device. The device must already have a service level connection or this will return immediately.
 				Delegate methods will be called once the connection is complete of a failure occurs.
 */
- (void)connectSCO NS_AVAILABLE_MAC(10_7);

/*!
 @method		disconnectSCO
 @abstract		Disconnect the SCO connection with the device
 @discussion	Disconnects the SCO connection with the device (if one exists).
 				Delegate methods will be called once the disconnection is complete.
 */
- (void)disconnectSCO NS_AVAILABLE_MAC(10_7);

/*!
 @method		isSCOConnected
 @abstract		Determine if there is a SCO connection to the device
 @discussion	Determines if there is a SCO connection to the device.
 @result		YES if there is a SCO connection to the device; otherwise, NO.
 */
- (BOOL)isSCOConnected NS_AVAILABLE_MAC(10_7);

@end

@protocol IOBluetoothHandsFreeDelegate <NSObject>

@optional

/*!
 @method		handsFree:connected
 @discussion	Tells the delegate that the hands free service level connection is complete.
 @param			device The IOBluetoothHandsFree object that was being connected
 @param			status The result of the connection attempt. An IOReturn result returned in an NSNumber object.
 */
- (void)handsFree:(IOBluetoothHandsFree *)device connected:(NSNumber *)status NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:disconnected
 @discussion	Tells the delegate that the hands free service level connection was disconnected.
 @param			device The IOBluetoothHandsFree object whose service level connection was disconnected
 @param			status The result of the disconnection attempt. An IOReturn result returned in an NSNumber object.
 */
- (void)handsFree:(IOBluetoothHandsFree *)device disconnected:(NSNumber *)status NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:scoConnectionOpened
 @discussion	Tells the delegate that the SCO connection is complete.
 @param			device The IOBluetoothHandsFree object that was being connected
 @param			status The result of the connection attempt. An IOReturn result returned in an NSNumber object.
 */
- (void)handsFree:(IOBluetoothHandsFree *)device scoConnectionOpened:(NSNumber *)status NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:scoConnectionClosed
 @discussion	Tells the delegate that the SCO connection was closed.
 @param			device The IOBluetoothHandsFree object whose SCO connection was closed
 @param			status The result of the disconnection attempt. An IOReturn result returned in an NSNumber object.
 */
- (void)handsFree:(IOBluetoothHandsFree *)device scoConnectionClosed:(NSNumber *)status NS_AVAILABLE_MAC(10_7);

@end

@interface IOBluetoothDevice ( HandsFreeDeviceAdditions )

/*!
 @method		handsFreeAudioGatewayDriverID
 @abstract		Return the hands free gateway driver ID
 @discussion	Returns the hands free gateway driver ID which is unique based on BT Address.
 @result		The hands free gateway driver ID
 */
- (NSString *)handsFreeAudioGatewayDriverID NS_DEPRECATED_MAC(10_7, 10_8);

/*!
 @method		handsFreeAudioGatewayServiceRecord
 @abstract		Return the hands free gateway SDP record
 @discussion	Returns the hands free gateway SDP record.
 @result		The hands free gateway SDP record
 */
- (IOBluetoothSDPServiceRecord *)handsFreeAudioGatewayServiceRecord NS_AVAILABLE_MAC(10_7);

/*!
 @method		isHandsFreeAudioGateway
 @abstract		Return the devices support for hands free gateway
 @discussion	Returns the devices support for hands free gateway (obtained from the devices SDP record).
 @result		YES if the device supports hands free gateway; otherwise, NO.
 */
@property (readonly, getter = isHandsFreeAudioGateway) BOOL handsFreeAudioGateway NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFreeDeviceDriverID
 @abstract		Return the hands free device driver ID
 @discussion	Returns the hands free device driver ID which is unique based on BT Address.
 @result		The hands free device driver ID
 */
- (NSString *)handsFreeDeviceDriverID NS_DEPRECATED_MAC(10_7, 10_8);

/*!
 @method		handsFreeDeviceServiceRecord
 @abstract		Return the hands free device SDP record
 @discussion	Returns the hands free device SDP record.
 @result		The hands free device SDP record
 */
- (IOBluetoothSDPServiceRecord *)handsFreeDeviceServiceRecord NS_AVAILABLE_MAC(10_7);

/*!
 @method		isHandsFreeDevice
 @abstract		Return the devices support for hands free device
 @discussion	Returns the devices support for hands free device (obtained from the devices SDP record).
 @result		YES if the device supports hands free device; otherwise, NO.
 */
@property (readonly, getter = isHandsFreeDevice) BOOL handsFreeDevice NS_AVAILABLE_MAC(10_7);

@end

@interface IOBluetoothSDPServiceRecord ( HandsFreeSDPServiceRecordAdditions )

/*!
 @method		handsFreeSupportedFeatures
 @abstract		Return the hands free supported features
 @discussion	Returns the hands free supported features bitmap stored in the SDP record. See “IOBluetoothHandsFreeDeviceFeatures and IOBluetoothHandsFreeAudioGatewayFeatures.”
 @result		The supported features bitmap.
 */
- (uint16_t)handsFreeSupportedFeatures NS_AVAILABLE_MAC(10_7);

@end



