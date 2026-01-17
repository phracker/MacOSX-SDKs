/*
     File:       DiscRecordingEngine/DRErase.h
 
     Contains:   Handles erasing a disc and obtaining status about that erasure.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!
	@header		DRErase.h
	@abstract	Perform and monitor the erasing a rewritable CD or DVD disc.
	@discussion	Each time you want to erase a disc, an instance of DRErase needs to be created.
	
				When an instance is created, you pass in an instance of @link //apple_ref/occ/cl/DRDevice DRDevice @/link to let the object 
				know what device to erase. This object is retained for the life of the DRErase instance. 
			
				A DRErase object will send out notifications through the @link //apple_ref/occ/cl/DRNotificationCenter DRNotificationCenter @/link mechanism to 
				broadcast the erase state to any interested observers. However, if for some reason you don't want
				to use notifications, you can poll the erase object at any time for the current status using
				@link //apple_ref/occ/instm/DRErase/status status @/link. This is not recommended in any 
				application using a run loop, because it involves polling.

				Here's an example that shows you how to use this class:
				
				<code>
				- (void) doErase																							<br/>
				{																											<br/>
					DRDevice*       device;																					<br/>
					DRErase*        erase;																					<br/>
				
					<i>...determine correct device to erase...</i>															<br/>
					
					erase = [[DRErase alloc] initWithDevice:device];														<br/>
					
					// we'll do a quick erase. It's typically all that's needed.											<br/>
					[erase setEraseType:DREraseTypeQuick];																	<br/>
					
					// register to receive notification about the erase status.												<br/>
					[[DRNotificationCenter currentRunLoopCenter] addObserver:self											<br/>
																	selector:&#x40;selector(eraseNotification:)				<br/>
																		name:DREraseStatusChangedNotification 				<br/>
																	  object:erase];										<br/>
								   
					 // start the erase                            															<br/>
					 [erase start];																							<br/>
				}
				
				- (void) eraseNotification:(NSNotification*)notification													<br/>
				{																											<br/>
					DRErase*        erase = [notification object];															<br/>
					NSDictionary*   status = [notification userInfo];														<br/>
					
					<i>...do what you wish with the notification...</i>														<br/>
				}
				</code>
*/
#import <Foundation/Foundation.h>

#import <DiscRecordingEngine/DRCoreErase.h>
#import <DiscRecordingEngine/DRDevice.h>

#import <AvailabilityMacros.h>


/*!
	@class		DRErase
	@abstract	A DRErase object handles the process of erasing a rewritable CD or DVD disc.
	@discussion	Each time you want to erase a disc, an instance of this class needs to be created.
	
				When an instance is created, you pass in an instance of @link //apple_ref/occ/cl/DRDevice DRDevice @/link to let the object 
				know what device to erase. This object is retained for the life of the DRErase instance. 
			
				A DRErase object will send out notifications through the @link //apple_ref/occ/cl/DRNotificationCenter DRNotificationCenter @/link mechanism to 
				broadcast the erase state to any interested observers. However, if for some reason you don't want
				to use notifications, you can poll the erase object at any time for the current status using
				@link //apple_ref/occ/instm/DRErase/status status @/link. This is not recommended in any 
				application using a run loop, because it involves polling.

				Here's an example that shows you how to use this class:
				
				<code>
				- (void) doErase																							<br/>
				{																											<br/>
					DRDevice*       device;																					<br/>
					DRErase*        erase;																					<br/>
				
					<i>...determine correct device to erase...</i>															<br/>
					
					erase = [[DRErase alloc] initWithDevice:device];														<br/>
					
					// we'll do a quick erase. It's typically all that's needed.											<br/>
					[erase setEraseType:DREraseTypeQuick];																	<br/>
					
					// register to receive notification about the erase status.												<br/>
					[[DRNotificationCenter currentRunLoopCenter] addObserver:self											<br/>
																	selector:&#x40;selector(eraseNotification:)				<br/>
																		name:DREraseStatusChangedNotification 				<br/>
																	  object:erase];										<br/>
								   
					 // start the erase                            															<br/>
					 [erase start];																							<br/>
				}
				
				- (void) eraseNotification:(NSNotification*)notification													<br/>
				{																											<br/>
					DRErase*        erase = [notification object];															<br/>
					NSDictionary*   status = [notification userInfo];														<br/>
					
					<i>...do what you wish with the notification...</i>														<br/>
				}
				</code>
*/
@interface DRErase : NSObject 
{ 
@private
	void*	_ref;
}

/*!
	@method			eraseForDevice:
	@abstract		Creates and returns an erase object.
	@discussion		An erase object created with this method is ready to erase media.
   	@param 			device	Device to use for the erase.
    @result  		An autoreleased DRErase object.
*/
+ (DRErase*) eraseForDevice:(DRDevice*)device;

/*!
	@method			initWithDevice:
	@abstract		Initializes an erase object.
	@discussion		An erase object created with this method is ready to erase media.
   	@param 			device	Device to use for the erase.
    @result  		A DRErase object.
*/
- (id) initWithDevice:(DRDevice*)device;

/*!
	@method			start
	@abstract		Begin the process of erasing media.
	@discussion		This method only kicks off the erase. Once the erasure starts,
					control returns to the caller. The caller can monitor the progress 
					of the erase by listening for a notification or by polling @link //apple_ref/occ/instm/DRErase/status status @/link.
*/
- (void) start;

/*!
	@method			status
	@abstract		Returns a dictionary containing the status of the erase.
	@discussion		The same dictionary is returned 
					through the @link //apple_ref/occ/data/DREraseStatusChangedNotification DREraseStatusChangedNotification @/link notification.
	@result			An NSDictionary containing the status of the erase.
*/
- (NSDictionary*) status;

/*! 
   	@method 		properties
   	@abstract		Returns the properties dictionary of the erase.
    @result  		An NSDictionary containing the properties of the erase.
*/
- (NSDictionary*) properties;

/*! 
   	@method 		setProperties:
   	@abstract		Sets the properties dictionary of the erase
   	@param 			properties	NSDictionary of the properties to set.
*/
- (void) setProperties:(NSDictionary*)properties;

/*! 
   	@method 		device
   	@abstract		Returns the device being used for the erase.
    @result  		The DRDevice the erase will use.
*/
- (DRDevice*) device;

@end

/*! 
	@category		DRErase (PropertyConvenienceMethods)
   	@discussion		This category on DRErase defines methods that make setting and retrieving
   					the various DRErase properties easier.
*/
@interface DRErase (PropertyConvenienceMethods)

/*!
	@method			eraseType
	@abstract		Returns the type of erase to be performed.
	@result			An NSString
*/
- (NSString*) eraseType;

/*!
	@method			setEraseType:
	@abstract		Sets the type of erase to perform.
	@param			type	The type of erase.
*/
- (void) setEraseType:(NSString*)type;

@end

#if 0
#pragma mark Erase Properties
#endif
/*!
	@const		DREraseTypeKey
	@discussion	The key for the erase's properties dictionary storing the type of 
				erase to perform 
*/
extern NSString* const DREraseTypeKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*" 
	@const		DREraseTypeQuick
	@discussion	An NString value for the @link DREraseTypeKey DREraseTypeKey @/link. 
				Configures the erase object to perform a quick erase, doing the minimal amount of work to make the 
				disc appear blank. This operation typically takes only a minute or two. 
				This is the default for an erase object.
*/
extern NSString* const DREraseTypeQuick			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	
	@const		DREraseTypeComplete	
	@discussion	An NString value for the @link DREraseTypeKey DREraseTypeKey @/link. 
				Configures the erase object to perform a complete erase, erasing every byte on the
				disk. This operation is slow (on the order of 30 minutes) to complete.
*/
extern NSString* const DREraseTypeComplete		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if 0
#pragma mark Erase State
#endif
/*
	@const		DREraseStatusChangedNotification
	@discussion	Posted by a @link //apple_ref/occ/cl/DRNotificationCenter DRNotificationCenter @/link when the status of the
				erase operation has changed. 
				
				 The object associated with this notification
				is the erase object sending it and the userInfo contains a dictionary
				detailing the status.
*/
extern NSString* const DREraseStatusChangedNotification	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

