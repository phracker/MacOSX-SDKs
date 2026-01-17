/*
     File:       DiscRecordingEngine/DRBurn.h
 
     Contains:   Handles burning and obtaining status about a burn.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Foundation/Foundation.h>

#import <DiscRecordingEngine/DRCoreBurn.h>

#import <DiscRecordingEngine/DRDevice.h>
#import <DiscRecordingEngine/DRTrack.h>

#import <AvailabilityMacros.h>
	
/*!
	@class			DRBurn
	@abstract		Handles the process of burning a CD or DVD disc.
	@discussion		Each time you want to burn to a disc, an instance of this class needs to be created. 
					
					When an instance is created, you pass in an instance of DRDevice to let the DRBurn object know 
					what device to use. This object is retained for the life of the DRBurn instance. Before burning, 
					you can set several options that control (1) the behavior of the burn, and (2) the handling 
					of the disc once the burn completes.
					
					A DRBurn object will send out notifications through the DRNotificationCenter mechanism to 
					broadcast the burn state to any interested observers. However, if for some reason you don't want
					to use notifications, you can poll the burn object at any time for the current status using
					<b>status</b>. This is not recommended in any application using a run loop, because it involves polling.

					Here's an example that shows you how to use this class:
					
					<code>
					- (void) doBurn
					{
						DRDevice*       device;
						DRTrack*        track;
						DRBurn*         burn;
					
						<i>...determine correct device to burn to...</i>
						
						<i>...create track...</i>
						
						burn = [[DRBurn alloc] initWithDevice:device];
							
						<i>...set options appropriate to this burn...</i>
						
						// register to receive notification about the burn status.
						[[DRNotificationCenter currentRunLoopCenter] addObserver:self 
																		selector:&#x40;selector(burnNotification:) 
																			name:DRBurnStatusChangedNotification 
																		  object:burn];
						// start the burn
						[burn writeLayout:track];
					}
					
					- (void) burnNotification:(NSNotification*)notification
					{
						DRBurn*         burn = [notification object];
						NSDictionary*   status = [notification userInfo];
						
						<i>...do what you wish with the notification...</i>
					}
					</code>
*/
@interface DRBurn : NSObject 
{ 
@private
	void*	_ref;
}

/*! 
   	@method 		burnForDevice:
   	@abstract		Creates a burn object.
	@discussion		Once a burn is created with this method, the object is ready to write data to the disc.
   	@param 			device	Device to use for the burn
    @result  		An autoreleased DRBurn object.
*/
+ (DRBurn*) burnForDevice:(DRDevice*)device;

/*! 
   	@method 		initWithDevice:
   	@abstract		Initializes the burn object.
	@discussion		Once a burn is initialized with this method, the object is ready to write data to the disc.
   	@param 			device	Device to use for the burn
    @result  		A DRBurn object.
*/
- (id) initWithDevice:(DRDevice*)device;

/*! 
   	@method 		writeLayout:
   	@abstract		Begin the process of burning a disc layout.
 	@discussion		This method only begins the burning process. Once the burn
					has been started, control returns to the caller and it is up to the caller to 
					monitor the progress of the burn (by listening for DRBurnStatusChangedNotification
					or polling <b>status</b>) to know when the burn completes (either successfully 
					or with an error).
   	@param 			layout	The data to be burned to disc.
   	
   					There are three configurations of the object passed in:
	
					<ol>
					<li>For a multi-session burn, layout must be a valid NSArray containing 
						 one or more NSArrays, each of which contains one or more valid DRTrack objects.</li>
					<li>For a single-session multi-track burn, layout must be a valid NSArray 
						 containing one or more valid DRTrack objects.</li>
					<li>For a single-session single-track burn, layout must be a valid DRTrack object.</li>
					</ol>
					If none of these configurations are met or the leaf values contained in
					layout are not valid DRTrack objects, an exception is thrown.
*/
- (void) writeLayout:(id)layout;

/*! 
   	@method 		status
   	@abstract		Returns a dictionary describing the status of the burn.
	@discussion		The same dictionary is returned through the DRBurnStatusChangedNotification notification
    @result  		An NSDictionary	reporting the status of the burn.	
*/
- (NSDictionary*) status;

/*! 
   	@method 		abort
   	@abstract		Stops the burn.
	@discussion		When this method returns the burn might not actually be fully stopped
					but it has been cancelled and only cleanup is going on. If a burn
					has not completed writing data to disc, you just made a coaster.
					
					Typically this method is only used as a result of the user hitting
					a cancel/stop button somewhere in the user interface.
*/
- (void) abort;

/*! 
   	@method 		properties
   	@abstract		Returns the properties dictionary of the burn.
    @result  		An NSDictionary containing the properties of the burn.
*/
- (NSDictionary*) properties;

/*! 
   	@method 		setProperties:
   	@abstract		Sets the properties dictionary of the burn.
   	@param 			properties	NSDictionary of the properties to set.
*/
- (void) setProperties:(NSDictionary*)properties;

/*! 
   	@method 		device
   	@abstract		Returns the device being used for the burn.
    @result  		The DRDevice the burn will use.
*/
- (DRDevice*) device;

@end

@interface DRBurn (PropertyConvenienceMethods)

/*! 
   	@method 		requestedBurnSpeed
   	@abstract		Returns the speed at which this burn will attempt to write data.
   	@discussion		The actual speed also depends on the capabilities of the bus the device is on, 
					the maximum speed of the device itself, and the media used.
    @result  		A float indicating the speed the burn should run at in kilobytes per second.
*/
- (float) requestedBurnSpeed;

/*! 
   	@method 		setRequestedBurnSpeed:
   	@abstract		Sets the speed at which the burn will be attempted to be performed at
   	@discussion		The actual speed also depends on the capabilities of the bus the device is on, 
					the maximum speed of the device itself, and the media used.
   	@param 			speed	The speed that the burn should run at in kilobytes per second.
*/
- (void) setRequestedBurnSpeed:(float)speed;

/*! 
   	@method 		appendable
   	@abstract		Indicates if the burn is appendable.
   	@discussion		When a burn completes, it can mark the disc so that no more data can be 
					written to it. This creates a closed or non-appendable disc (which is the
					most compatible with audio CD players). If this method returns <i>NO</i>, then 
					the disc will be marked as closed and no data can be appended to it. A
					return value of <i>YES</i> indicates further burns can be appended to 
					the disc.
    @result  		A BOOL indicating if the burn is appendable.
*/
- (BOOL) appendable;

/*! 
   	@method 		setAppendable:
   	@abstract		Sets the burn to be appendable or non-appendable.
   	@discussion		When a burn completes, it can mark the disc so that no more data can be 
					written to it. This creates a closed or non-appendable disc (which is the
					most compatible with audio CD players).
   	@param 			appendable	A BOOL indicating if the burn is appendable. Passing in <i>YES</i> 
   					indicates further burns can be appended to the disc, while passing in <i>NO</i>, 
   					marks the disc as closed and no data can be appended to it. 
*/
- (void) setAppendable:(BOOL)appendable;

/*! 
   	@method 		verifyDisc
   	@abstract		Indicates if the resulting disc will be verified.
   	@discussion		
    @result  		A BOOL indicating if the disc will be verified.
*/
- (BOOL) verifyDisc;

/*! 
   	@method 		setVerifyDisc:
   	@abstract		Sets the burn to verify or not verify the disc.
   	@param 			verify	A BOOL indicating if the disc is to be verified. Passing in <i>YES</i> 
   							(the default) indicates that the data written to disc will be verified 
   							against the source data once the burn complete. 
							Passing in <i>NO</i> indicates that no verification will take place.
*/
- (void) setVerifyDisc:(BOOL)verify;

/*! 
   	@method 		completionAction
   	@abstract		Returns the action to be performed at the end of the burn.
    @result  		An NSString
*/
- (NSString*) completionAction;

/*! 
   	@method 		setCompletionAction:
   	@abstract		Sets the action to be performed at the end of the burn.
   	@param 			action	An NSString for the action to perform.
*/
- (void) setCompletionAction:(NSString*)action;

@end

/* --------------------------------------- */
/* Burn properties */
#if 0
#pragma mark Burn Properties
#endif
/*!
	@const          DRBurnRequestedSpeedKey         
	@discussion     The burn property whose value is an NSNumber containing the speed at
					which the burn should run, expressed as a float value of kilobytes per second.
					If this key is not present, the speed will default to DRDeviceBurnSpeedMax.
*/
extern NSString* const DRBurnRequestedSpeedKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const          DRBurnAppendableKey
	@discussion     The burn property whose value is a BOOL indicating if the disc will still be 
					appendable after the burn. If this key is not present, the burn will default 
					to a value of <i>NO</i> and the disc will be marked as not appendable.
*/
extern NSString* const DRBurnAppendableKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const          DRBurnOverwriteDiscKey
	@discussion     The burn property whose value is a BOOL indicating if the disc will be overwritten
					from block zero for the burn. If this key is not present, the burn will default 
					to a value of <i>NO</i> and the disc will be appended.
*/
extern NSString* const DRBurnOverwriteDiscKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const			DRBurnVerifyDiscKey
	@discussion     The burn property whose value is a BOOL indicating if the disc will be verified 
					after being burned. If this key is not present, the burn will default to a
					value of <i>YES</i> and the disc will be verified.
*/
extern NSString* const DRBurnVerifyDiscKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const          DRBurnCompletionActionKey
	@discussion     The burn property whose value is an NSString containing one of the
					completion actions possible for the disc handling. If this key is not present,
					the burn will default to a value of <i>DRBurnCompletionActionEject</i> and the
					disc will be ejected.
*/
extern NSString* const DRBurnCompletionActionKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const			DRBurnUnderrunProtectionKey
	@discussion		The burn property whose value is a BOOL indicating if burn underrun protection 
					will be on or off for devices which support it.
	
					For those devices which support it, burn underrun protection is enabled 
					by default.
		
					If the device supports burn underrun protection and this key is not present,
					the burn will default to a value of <i>YES</i> and burn underrun protection 
					will be enabled.
*/
extern NSString* const DRBurnUnderrunProtectionKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const			DRBurnTestingKey
	@discussion		The burn property whose value is a BOOL indicating if the burn will run 
					as a test burn.

					When this is set and the burn object is sent <b>writeLayout:</b>,
					the entire burn process proceeds as if data would be 
					written to the disc, but the laser is not turned on to full power, so
					the physical disc is not modified.

                    If this key is not present or the selected burning device does not support test burning,
					the burn will default to a value of <tt>false</tt> and a normal burn will occur.
*/
extern NSString* const DRBurnTestingKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const			DRSynchronousBehaviorKey
	@discussion		The burn property whose value is a BOOL indicating if burn operations
					will behave synchronously.  If this key is not present, it will default
					to a value of <tt>false</tt> and burn operations will behave asynchronously.
					
					Synchronous operations do not post status notifications, and will not
					return until they are completed.  Status can still be queried at any time,
					and will remain valid even after the burn operation has finished.
*/
extern NSString* const DRSynchronousBehaviorKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const			DRBurnFailureActionKey
	@discussion		The burn property whose value is an NSString containing a one of the failure
					actions possible for the disc handling.
					
					If this key is not present, the burn will default to a value of
					<tt>DRBurnFailureActionEject</tt> and the disc will be ejected.
*/
extern NSString* const DRBurnFailureActionKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const			DRMediaCatalogNumberKey
	@discussion		The burn property whose value is an NSData containing exactly 13 bytes of
					data, which will be written to the disc as the Media Catalog Number.
					If this key is not present, it will default to all zeroes, indicating
					that a MCN is not supplied.
					
					This value is the UPC/EAN product number, and should conform to the
					specifications of the UCC and EAN.  See http://www.ean-int.org/ and
					http://www.uc-council.org/ for more details on the UPC/EAN standard.
*/				
extern NSString* const DRMediaCatalogNumberKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const			DRBurnStrategyKey
	@discussion		The burn property whose value is an NSString, or NSArray or NSStrings,
					indicating the burn strategy or strategies that are suggested.  If this
					key is not present, the burn engine picks an appropriate burn strategy
					automatically. Most clients will not need to specify a specific burn
					strategy.
					
					When more than one strategy is suggested, the burn engine will attempt
					to use the first strategy in the list which is available. A burn strategy
					will never be used if it cannot write the required data: for example, TAO
					cannot be used to write CD-Text.
					
					The presence of this key by itself is just a suggestion, and if the burn
					engine cannot fulfill the request it will burn using whatever strategy is
					available.  To make the suggestion into a requirement, add
					DRBurnStrategyIsRequired with a value of YES.
*/
extern NSString* const DRBurnStrategyKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const			DRBurnStrategyIsRequiredKey
	@discussion		The burn property whose value is a BOOL indicating whether the burn
					strategy/strategies listed for kDRBurnStrategyKey are
					the only strategies allowed.  If this key is not present,
					the burn will default to a value of <tt>false</tt>.
					
					If this value is set to <tt>true</tt>, and the device does
					not support the type(s) of burn requested, the burn
					will fail with kDRDeviceBurnStrategyNotAvailableErr.
					
					If this value is set to <tt>false</tt>, and the device does
					not support the type(s) of burn requested, the engine
					will choose an alternate burn strategy automatically - one
					that will provide an equivalent disc.
*/
extern NSString* const DRBurnStrategyIsRequiredKey	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* --------------------------------------- */
/* Completion actions */
/*!
	@const			DRBurnCompletionActionEject
	@discussion		An NSString value for DRBurnCompletionActionKey indicating that the burn
					object should eject the disc from the drive when the burn completes.
*/
extern NSString* const DRBurnCompletionActionEject	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const			DRBurnCompletionActionMount
	@discussion		An NSString value for DRBurnCompletionActionKey indicating that the burn
					object should mount the disc on the desktop when the burn completes.
*/
extern NSString* const DRBurnCompletionActionMount	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* ---------------------------------- */
/* Failure actions */
/*! 
	@const			DRBurnFailureActionEject	
	@discussion		An NSString value for DRBurnCompletionActionKey indicating that the burn
					object should eject the disc from the drive if the burn fails.
*/
extern NSString* const DRBurnFailureActionEject		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*! 
	@const			DRBurnFailureActionNone	
	@discussion		An NSString value for DRBurnCompletionActionKey indicating that the burn
					object should do nothing with the disc if the burn fails.
*/
extern NSString* const DRBurnFailureActionNone		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* --------------------------------------- */
/* Burn strategies */
/*!
	@const			DRBurnStrategyCDTAO
	@discussion		An NSString value for DRBurnStrategyKey representing the TAO (track-at-once)
					burn strategy for CD.
*/
extern NSString* const DRBurnStrategyCDTAO			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const			DRBurnStrategyCDSAO
	@discussion		An NSString value for DRBurnStrategyKey representing the SAO (session-at-once)
					burn strategy for CD.
*/
extern NSString* const DRBurnStrategyCDSAO			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const			DRBurnStrategyCDRaw
	@discussion		An NSString value for DRBurnStrategyKey representing the raw mode
					burn strategy for CD.  Raw mode is sometimes incorrectly called DAO (disc-at-once).
*/
extern NSString* const DRBurnStrategyCDRaw			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const			DRBurnStrategyDVDDAO
	@discussion		An NSString value for DRBurnStrategyKey representing the DAO (disc-at-once)
					burn strategy for DVD.  This strategy applies <b>only</b> to DVDs; it is
					invalid when burning to CD media.
*/
extern NSString* const DRBurnStrategyDVDDAO			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#if 0
#pragma mark Burn Notifications
#endif
/* --------------------------------------- */
/* Notifications */
/*!
	@const		DRBurnStatusChangedNotification 
	@discussion	Posted by a DRNotificationCenter when the status of the
				burn operation has changed. 
	
				The object associated with this notification
				is the burn object sending it and the userInfo contains a dictionary
				detailing the status. 
*/
extern NSString* const DRBurnStatusChangedNotification	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

