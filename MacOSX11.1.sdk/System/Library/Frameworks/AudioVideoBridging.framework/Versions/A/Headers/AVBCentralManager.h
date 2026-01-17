//
//  AVBCentralManager.h
//  AudioVideoBridging
//
//  Copyright (c) 2013-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVBInterface;

/*!
	@abstract	This NULL EUI-64. The IEEE defines this as FF-FF-FF-FF-FF-FF-FF-FF.
 */
FOUNDATION_EXTERN const uint64_t AVBNullEUI64;

/*!
	@class		AVBCentralManager
	@abstract	AVBCentralManager provides centralized management of AVBInterface objects for the network interfaces of the computer.
	@discussion	AVBCentralManager provides centralized management of the AVBInterface subclasses for the network interfaces of the computer.
				Subclasses override the <code>didAddInterface:</code> and <code>didRemoveInterface:</code> methods to be notified when an 
				interface is added to or removed from the computer. Addition and removal can happen for any interface but is typically associated
				with the Thunderbolt Ethernet Adapter.
 
 */
API_AVAILABLE(macos(10.10))
@interface AVBCentralManager : NSObject
{
}


/*!
	@abstract	This method triggers the IOKit matching for the network controllers.
	@discussion	This is usually called by a subclass as the last thing in it's init method. This call is broken out of the AVBCentralManager's init method so that 
				subclasses can finish their setup before calling it.
 */
- (void)startControllerMatching;

/*!
	@abstract	This method is called when an AVBInterface object is created for a NIC, either when the central manager is first started up or when the NIC is added later.
	@param		interface	An instance of an AVBInterface subclass (as appropriate for the NIC) which has been added for the discovered NIC.
	@discussion	The AVBCentralManager maintains it's own internal reference to the interface object until <code>didRemoveInterface:<code> is called with the same interface object,
				subclasses do not need to maintain another reference to this. A subclass does not need to call the AVBCentralManager implementation. 
				Note this method is not called on the main thread and is not safe for performing UI actions.
 */
- (void)didAddInterface:(AVBInterface *)interface;
/*!
	@abstract	This method is called when a NIC has been removed from the system and the central manager is cleaning it up.
	@param		interface	An instance of an AVBInterface subclass (as appropriate for the NIC) which is being removed for the discovered NIC.
	@discussion	Note this method is not called on the main thread and is not safe for performing UI actions.
 */
- (void)didRemoveInterface:(AVBInterface *)interface;


/*!
	@abstract	This method is used to control if the central manager will create and process AVBInterface objects for non streaming interfaces.
	@result		YES for only AVB Enabled interfaces or NO for all interfaces.
	@discussion	The default value returned is YES and as such didAddInterface: will be called for all AVB Enabled network interfaces only.
 */
- (BOOL)streamingEnabledInterfacesOnly;




/*!
	@abstract	This method is used to allocate a dynamic Entity ID .
	@result		The allocated dynamic entity ID or AVBNullEUI64 if allocation failed.
	@discussion	The entity ID allocated by this call can be used for both publishing an Entity with the AVB17221EntityDiscovery class or as a controllerID for the AVB17221ACMPMessage and AVB17221AECPMessage.
 */
+ (uint64_t)nextAvailableDynamicEntityID;

/*!
	@abstract	This method is used to release a previously allocated dynamic Entity ID.
	@param		entityID	The entity ID to release that was previously allocated by <code>+nextAvailableDynamicEntityID</code>.
 */
+ (void)releaseDynamicEntityID:(uint64_t)entityID;

/*!
	@abstract	This method is used to allocate a dynamic Entity Model ID .
	@result		The allocated dynamic entity model ID or AVBNullEUI64 if allocation failed.
	@discussion	The entity model ID allocated by this call can be used for publishing an Entity with the AVB17221EntityDiscovery class when using a dynamically generated or modified model.
 */
+ (uint64_t)nextAvailableDynamicEntityModelID;

/*!
	@abstract	This method is used to release a previously allocated dynamic Entity Model ID.
	@param		entityModelID	The entity ID to release that was previously allocated by <code>+nextAvailableDynamicEntityModelID</code>.
 */
+ (void)releaseDynamicEntityModelID:(uint64_t)entityModelID;

@end

NS_ASSUME_NONNULL_END
