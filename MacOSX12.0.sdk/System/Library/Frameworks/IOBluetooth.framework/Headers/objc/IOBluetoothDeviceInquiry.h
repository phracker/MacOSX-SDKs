/*
	Contains:	A way to find bluetooth devices.
	Copyright:	(c) 2008 by Apple Computer, Inc., all rights reserved.
*/

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>

//===========================================================================================================================
//	Forward Declarations
//===========================================================================================================================

@class NSMutableArray;
@class IOBluetoothDevice;
@protocol IOBluetoothDeviceInquiryDelegate;

//===========================================================================================================================
//	IOBluetoothDeviceInquiry
//===========================================================================================================================

//---------------------------------------------------------------------------------------------------------------------------
/*!	@class			IOBluetoothDeviceInquiry
	@abstract		Object representing a device inquiry that finds Bluetooth devices in-range of the computer,
					and (optionally) retrieves name information for them.
	@discussion		You should only use this object if your application needs to know about in-range devices and cannot
					use the GUI provided by the IOBluetoothUI framework. It will not let you perform unlimited back-to-back
					inquiries, but will instead throttle the number of attempted inquiries if too many are attempted within
					a small window of time.
					Important Note: DO NOT perform remote name requests on devices from delegate methods or while this
					object is in use. If you wish to do your own remote name requests on devices, do them after you have
					stopped this object. If you do not heed this warning, you could potentially deadlock your process.
*/

API_UNAVAILABLE(ios, watchos, tvos)
@interface IOBluetoothDeviceInquiry : NSObject
{
@private
	
	void *							_nameRequestHintType;
	IOBluetoothDeviceSearchAttributes *_searchAttributes;
	void *							_deviceAttributes;

    id                              _mReserved;
    id                              _mUnused000;
    id                              _mUnused001;
    id                              _mUnused002;

	BluetoothServiceClassMajor		_serviceClassMajor;
	BluetoothDeviceClassMajor		_deviceClassMajor;
	BluetoothDeviceClassMinor		_deviceClassMinor;
	
    uint8_t							_inquiryLength;
	BluetoothHCIResponseCount		_inquiryMaxItems;

    NSMutableArray  *				_deviceResults;
    NSMutableArray	*				_devicesPendingNames;
	
	uint8_t							_currentActivity;
	BOOL							_remoteNameRequestInProgress;
	BOOL							_infSearch;
	BOOL							_sendDuplicates;
	BOOL							_aborted;
	BOOL							_updateNewDeviceNames;
	
}

@property (assign, nullable) id delegate;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		inquiryWithDelegate
	@abstract	Class method to create an inquiry object.
	@param		delegate		A delegate object that wishes to receive messages from the inquiry object. Delegate methods are listed below, under IOBluetoothDeviceInquiryDelegate.
	@result		A pointer to the created IOBluetoothDeviceInquiry object.
	@discussion The inquiry is NOT automatically started. You musts call -start on it to start the search for in-range devices.
*/

+ (instancetype)inquiryWithDelegate:(id)delegate;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		initWithDelegate
	@abstract	Initializes an alloc'd inquiry object, and sets the delegate object, as if -setDelegate: were called on it.
	@param		delegate		A delegate object that wishes to receive messages from the inquiry object. Delegate methods are listed below, under IOBluetoothDeviceInquiryDelegate.
	@result		A pointer to the initialized IOBluetoothDeviceInquiry object.
*/

- (instancetype)initWithDelegate:(id)delegate;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		start
	@abstract	Tells inquiry object to begin the inquiry and name updating process, if specified.
	@result		Returns kIOReturnSuccess if start was successful. Returns kIOReturnBusy if the object is already in process. May return other IOReturn values, as appropriate.
	@discussion Calling start multiple times in rapid succession or back-to-back will probably not produce the intended
				results. Inquiries are throttled if they are called too quickly in succession.
*/

- (IOReturn)start;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		stop
	@abstract   Halts the inquiry object. Could either stop the search for new devices, or the updating of found device names.
	@result		Returns kIOReturnSuccess if the inquiry is successfully stopped. Returns kIOReturnNotPermitted if the inquiry object is already stopped. May return other IOReturn values, as appropriate.
*/

- (IOReturn)stop;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setInquiryLength
	@abstract   Set the length of the inquiry that is performed each time -start is used on an inquiry object. 
	@param		seconds			Number of seconds the inquiry will search for in-range devices before refreshing device names, if specified.
	@result		Number of seconds the search will be performed.
	@discussion A default of 10 seconds is used, unless a different value is specified using this method.  Note that if you
				have called -start again too quickly, your inquiry may actually take much longer than what length you
				specify, as inquiries are throttled in the system. Also note that if you have the inquiry object updating
				device names for you, the whole inquiry process could be much longer than the specified length, depending
				on the number of devices found and how responsive to name requests they are. If you -must- have a strict
				inquiry length, disable name updates. In other words, this "length" only refers to the actual device discovery
				portion of the whole inquiry process.
*/

@property(assign) uint8_t inquiryLength;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setSearchType
	@abstract   Set the devices that are found. 
	@param		searchType		Bluetooth versions the search will discover.
	@discussion A default of kIOBluetoothDeviceSearchClassic is used, unless a different value is specified using this method.
*/

@property(assign) IOBluetoothDeviceSearchTypes searchType;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setUpdateNewDeviceNames
	@abstract   Sets whether or not the inquiry object will retrieve the names of devices found during the search.
	@param		inValue		Pass TRUE if names are to be updated, otherwise pass FALSE.
	@discussion The default value for the inquiry object is TRUE, unless this method is used to change it.
*/

@property(assign) BOOL updateNewDeviceNames;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		foundDevices
	@abstract   Returns found IOBluetoothDevice objects as an array.
	@result		Returns an NSArray of IOBluetoothDevice objects.
	@discussion Will not return nil. If there are no devices found, returns an array with length of 0.
*/

- (NSArray*)foundDevices;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		clearFoundDevices
	@abstract   Removes all found devices from the inquiry object.
*/

- (void)clearFoundDevices;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setSearchCriteria
	@abstract   Use this method to set the criteria for the device search.
	@param		inServiceClassMajor		Set the major service class for found devices. Set to kBluetoothServiceClassMajorAny for all devices. See BluetoothAssignedNumbers.h for possible values.
	@param		inMajorDeviceClass		Set the major device class for found devices. Set to kBluetoothDeviceClassMajorAny for all devices. See BluetoothAssignedNumbers.h for possible values.
	@param		inMinorDeviceClass		Set the minor device class for found devices. Set to kBluetoothDeviceClassMinorAny for all devices. See BluetoothAssignedNumbers.h for possible values.
	@discussion The default inquiry object will search for all types of devices. If you wish to find only keyboards, for example, you might use this method like this:
	
				[myInquiryObject		setSearchCriteria:kBluetoothServiceClassMajorAny
										majorDeviceClass:kBluetoothDeviceClassMajorPeripheral
										minorDeviceClass:kBluetoothDeviceClassMinorPeripheral1Keyboard];
										
				However, we recommend only using this if you are certain of the device class you are looking for, as some
				devices may report a different/unexpected device class, and the search may miss the device you are interested in.
*/

- (void)setSearchCriteria:(BluetoothServiceClassMajor)inServiceClassMajor
				majorDeviceClass:(BluetoothDeviceClassMajor)inMajorDeviceClass
				minorDeviceClass:(BluetoothDeviceClassMinor)inMinorDeviceClass;
				
@end

/*!
    @category 		IOBluetoothDeviceInquiryDelegate
    @discussion		This category on NSObject describes the delegate methods for the IOBluetoothDeviceInquiry object. All
					methods are optional, but it is highly recommended you implement them all. Do NOT invoke remote name
					requests on found IOBluetoothDevice objects unless the inquiry object has been stopped. Doing so may
					deadlock your process.
*/

API_UNAVAILABLE(ios, watchos, tvos)
@protocol IOBluetoothDeviceInquiryDelegate <NSObject>
@optional
//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			deviceInquiryStarted
	@discussion 	This message will be delivered when the inquiry actually starts. Since the inquiry could be throttled, this
					message may not be received immediately after called -start.
	@param			sender				Inquiry object that sent this delegate message.
*/

- (void)	deviceInquiryStarted:(IOBluetoothDeviceInquiry*)sender;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			deviceInquiryDeviceFound
	@discussion 	A new device has been found. You do not need to retain the device - it will be held in the internal
					storage of the inquiry, and can be accessed later using -foundDevices.
	@param			sender				Inquiry object that sent this delegate message.
	@param			device				IOBluetoothDevice that was found.
*/

- (void)	deviceInquiryDeviceFound:(IOBluetoothDeviceInquiry*)sender	device:(IOBluetoothDevice*)device;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			deviceInquiryUpdatingDeviceNamesStarted
	@discussion 	The inquiry has begun updating device names that were found during the search.
	@param			sender				Inquiry object that sent this delegate message.
	@param			devicesRemaining	Number of devices remaining to update.
*/

- (void)	deviceInquiryUpdatingDeviceNamesStarted:(IOBluetoothDeviceInquiry*)sender	devicesRemaining:(uint32_t)devicesRemaining;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			deviceInquiryDeviceNameUpdated
	@discussion 	A device name has been retrieved. Also indicates how many devices are left to be updated.
	@param			sender				Inquiry object that sent this delegate message.
	@param			device				IOBluetoothDevice that was updated.
	@param			devicesRemaining	Number of devices remaining to update.
*/

- (void)	deviceInquiryDeviceNameUpdated:(IOBluetoothDeviceInquiry*)sender	device:(IOBluetoothDevice*)device devicesRemaining:(uint32_t)devicesRemaining;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			deviceInquiryComplete
	@discussion 	When the inquiry is completely stopped, this delegate method will be invoked. It will supply an error
					code value, kIOReturnSuccess if the inquiry stopped without problem, otherwise a non-kIOReturnSuccess
					error code will be supplied.
	@param			sender				Inquiry object that sent this delegate message.
	@param			error				Error code. kIOReturnSuccess if the inquiry completed without incident.
	@param			aborted				TRUE if user called -stop on the inquiry.
*/

- (void)	deviceInquiryComplete:(IOBluetoothDeviceInquiry*)sender	error:(IOReturn)error	aborted:(BOOL)aborted;

@end
