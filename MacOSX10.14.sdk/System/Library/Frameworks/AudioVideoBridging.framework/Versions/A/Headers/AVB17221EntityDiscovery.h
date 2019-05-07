//
//  AVB17221EntityDiscovery.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <IOKit/IOKitLib.h>

NS_ASSUME_NONNULL_BEGIN

@class AVB17221Entity;
@class AVBInterface;

/*!
	@class		AVB17221EntityDiscovery
	@abstract	AVB17221EntityDiscovery provides access to the IEEE Std 1722.1™-2013 AVDECC Discovery Protocol (ADP) interface.
	@discussion	AVB17221EntityDiscovery provides access to the IEEE Std 1722.1™-2013 AVDECC Discovery Protocol (ADP) interface.
				It provides a delegate with callbacks whenever an entity is added or removed, 
				either locally or remotely. AVB17221EntityDiscovery objects are typically not created 
				directly but are created indirectly and accessed via the entityDiscovery property of 
				the AVBInterface object.
				
				The AVBInterface object does not register a delegate with the AVB17221EntityDiscovery object
				which is allocated. Immediately after obtaining the entityDiscovery value for the first time,
				the discoveryDelegate should be set and the primeIterators method should be called. Until 
				primeIterators is called, no entities will be discovered.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB17221EntityDiscovery : NSObject
{
	@private
	io_connect_t connection;
	
#if AVB_LEGACY_OBJC_RUNTIME
	NSString *interfaceName;
	AVBInterface *interface;
	
	id <AVB17221EntityDiscoveryDelegate> discoveryDelegate;
#endif
	
	IONotificationPortRef notificationPort;
	
	dispatch_queue_t callbackQueue;
	
	io_iterator_t localArrivalIterator;
	io_iterator_t localDepartureIterator;
	io_iterator_t remoteArrivalIterator;
	io_iterator_t remoteDepartureIterator;
	
	NSMutableDictionary *localEntities;
	NSMutableDictionary *remoteEntities;
	
	io_object_t notification;
}

/*!
	@property	interfaceName
	@abstract	The BSD interface name for the interface that discovery is being performed on.
 */
@property (copy) NSString *interfaceName;

/*!
	@property	interface
	@abstract	The AVBInterface object which owns this object. This may be nil if it was not created by an instance of AVBInterface
 */
@property (readonly, assign, nullable) AVBInterface *interface;

/*!
	@property	discoveryDelegate
	@abstract	The delegate, implementing the AVB17221EntityDiscoveryDelegate protocol, which will handle entities arriving, departing and changing properties.
 */
@property (assign, nullable) id <AVB17221EntityDiscoveryDelegate> discoveryDelegate;

/*!
	@method		initWithInterfaceName:
	@abstract	Initializes the receiver with a particular interface name.
	@param		anInterfaceName	The BSD interface name for the interface to perform discovery on.
	@result		The initialized receiver.
 */
- (instancetype)initWithInterfaceName:(NSString *)anInterfaceName;

/*!
	@method		primeIterators
	@abstract	Prepares the IOIterators for receiving entity arrival, departure and property change notifications.
	@discussion	This method primes the iterators by iterating over any already available entities. This may be called once, at any time after object creation,
				but if the discoveryDelegate property has not been set, any already discovered entity notifications will be lost.
 */
- (void)primeIterators;

/*!
	@method		discoverEntities
	@abstract	Triggers the IEEE Std 1722.1™-2013 ADP service to perform an ENTITY_DISCOVER for all entities (an entity_id of 0).
	@result		A boolean indicating if the call succedded.
 */
- (BOOL)discoverEntities;
/*!
	@method		discoverEntity:
	@abstract	Triggers the IEEE Std 1722.1™-2013 ADP service to perform an ENTITY_DISCOVER for a specified entity.
	@param		entityID	The entity_id of the entity to look for.
	@result		A boolean indicating if the call succedded.
 */
- (BOOL)discoverEntity:(uint64_t)entityID;

/*!
	@method		addLocalEntity:error:
	@abstract	Publishes a entity as being available on the interface. The in kernel portion creates an IOAVB17221LocalEntity and maintains the ADP messaging.
	@param		anEntity	The entity to be published.
	@param		error		If the request couldn't be completed, on return it contains an instance of NSError that describes the reason why.
	@result		A boolean indicating if the entity was added.
 */
- (BOOL)addLocalEntity:(AVB17221Entity *)anEntity error:(NSError **)error;

/*!
	@method		removeLocalEntity:
	@abstract	Removes a published local entity with the given GUID.
	@param		guid	The GUID of the local entity to remove.
	@param		error		If the request couldn't be completed, on return it contains an instance of NSError that describes the reason why.
	@result		A boolean indicating if the entity was removed.
 */
- (BOOL)removeLocalEntity:(uint64_t)guid error:(NSError **)error;

/*!
	@method		changeEntityWithGUID:toNewASGrandmasterID:
	@abstract	Change the as_grandmaster_id value of the entity when the grandmaster changes.
	@param		entityGUID		The GUID of the entity to change.
	@param		asGrandmasterID	The new IEEE Std 802.1AS grandmaster ID.
	@param		error			If the request couldn't be completed, on return it contains an instance of NSError that describes the reason why.
	@result		A boolean indicating if the entity was updated.
 */
- (BOOL)changeEntityWithGUID:(uint64_t)entityGUID toNewASGrandmasterID:(uint64_t)asGrandmasterID error:(NSError **)error NS_DEPRECATED(10_8, 10_9, NA, NA);

/*!
	@method		changeEntityWithEntityID:toNewGPTPGrandmasterID:
	@abstract	Change the gptp_grandmaster_id value of the entity when the grandmaster changes.
	@param		entityID		The entity_id of the entity to change.
	@param		gPTPGrandmasterID	The new IEEE Std 802.1AS grandmaster ID.
	@param		error			If the request couldn't be completed, on return it contains an instance of NSError that describes the reason why.
	@result		A boolean indicating if the entity was updated.
 */
- (BOOL)changeEntityWithEntityID:(uint64_t)entityID toNewGPTPGrandmasterID:(uint64_t)gPTPGrandmasterID error:(NSError **)error NS_AVAILABLE(10_9, NA);

@end

NS_ASSUME_NONNULL_END
