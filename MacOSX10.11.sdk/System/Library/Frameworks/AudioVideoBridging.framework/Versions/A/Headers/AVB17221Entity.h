//
//  AVB17221Entity.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <IOKit/IOKitLib.h>

#import <IOKit/network/IOEthernetController.h>

NS_ASSUME_NONNULL_BEGIN

@class AVB17221EntityDiscovery;
@class AVBMACAddress;

@protocol AVB17221EntityPublisher;

/*!
	@class		AVB17221Entity
	@abstract	AVB17221Entity class represents an entity that has been discovered on the network.
	@discussion	AVB17221Entity class represents an entity that has been discovered on the network.
				AVB17221Entity objects are created by the AVB17221EntityDiscovery object as they are discovered, 
				and passed around to the discovery delegates when notifying them of changes in the state of the network.
				Changes include an entity being added, removed or rediscovered. Entities register themselves to receive
				automatic updates when any of the discovery values change.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB17221Entity : NSObject
{
	@private
#if AVB_LEGACY_OBJC_RUNTIME
	BOOL localEntity;
	
	uint8_t timeToLive;
	uint64_t entityID;
	uint64_t entityModelID;
	AVB17221ADPEntityCapabilities entityCapabilities;
	uint16_t talkerStreamSources;
	AVB17221ADPTalkerCapabilities talkerCapabilities;
	uint16_t listenerStreamSinks;
	AVB17221ADPListenerCapabilities listenerCapabilities;
	AVB17221ADPControllerCapabilities controllerCapabilities;
	uint32_t availableIndex;
	uint64_t gPTPGrandmasterID;
	uint64_t associationID;
	
	NSArray *macAddresses;
	
	AVB17221EntityDiscovery *entityDiscovery;
	
	id<AVB17221EntityPublisher> entityPublisher;
	
	uint32_t lastAvailableIndex;
	
	uint16_t identifyControlIndex;
	uint8_t gPTPDomainNumber;
	uint16_t interfaceIndex;
#endif
	
	io_service_t service;
	io_object_t interestNotficiation;
	IONotificationPortRef notificationPort;
}

/*!
	@property	localEntity
	@abstract	YES if the entity is published locally on the machine and NO if the entity has been discovered on the network.
 */
@property (assign, getter = isLocalEntity) BOOL localEntity;

/*!
	@property	timeToLive
	@abstract	The number of seconds left until the entity registration times out.
 */
@property (assign) uint8_t timeToLive;
/*!
	@property	guid
	@abstract	The Globally Unique Identifier (entity_guid) of the entity.
 */
@property (assign) uint64_t guid NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@property	entityID
	@abstract	The Unique Identifier (entity_id) of the entity.
 */
@property (assign) uint64_t entityID NS_AVAILABLE(10_9, NA);
/*!
	@property	vendorID
	@abstract	The vendor_id of the entity. This is equivalent to the 32 most significant bits of <code>entityModelID</code>.
 */
@property (assign) uint32_t vendorID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@property	modelID
	@abstract	The model_id of the entity. This is equivalent to the 32 least significant bits of <code>entityModelID</code>.
 */
@property (assign) uint32_t modelID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@property	entityModelID
	@abstract	The Entity Model Unique Identifier (entity_model_id) of the entity.
 */
@property (assign) uint64_t entityModelID NS_AVAILABLE(10_9, NA);
/*!
	@property	entityCapabilities
	@abstract	The entity_capabilities of the entity.
 */
@property (assign) AVB17221ADPEntityCapabilities entityCapabilities;
/*!
	@property	talkerStreamSources
	@abstract	The number of stream sources the entity has.
 */
@property (assign) uint16_t talkerStreamSources;
/*!
	@property	talkerCapabilities
	@abstract	The talker_capabilities of the entity.
 */
@property (assign) AVB17221ADPTalkerCapabilities talkerCapabilities;
/*!
	@property	listenerStreamSinks
	@abstract	The number of stream sinks the entity has.
 */
@property (assign) uint16_t listenerStreamSinks;
/*!
	@property	listenerCapabilities
	@abstract	The listener_capabilities of the entity.
 */
@property (assign) AVB17221ADPListenerCapabilities listenerCapabilities;
/*!
	@property	controllerCapabilities
	@abstract	The controller_capabilities of the entity.
 */
@property (assign) AVB17221ADPControllerCapabilities controllerCapabilities;
/*!
	@property	availableIndex
	@abstract	The available_index of the entity.
 */
@property (assign) uint32_t availableIndex;
/*!
	@property	asGrandmasterID
	@abstract	The clock identifier of the IEEE Std 802.1AS-2011 grandmaster of the entity.
 */
@property (assign) uint64_t asGrandmasterID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@property	gPTPGrandmasterID
	@abstract	The clock identifier of the IEEE Std 802.1AS-2011 grandmaster of the entity.
 */
@property (assign) uint64_t gPTPGrandmasterID NS_AVAILABLE(10_9, NA);
/*!
	@property	gPTPDomainNumber
	@abstract	The domain number of the IEEE Std 802.1AS-2011 grandmaster of the entity.
 */
@property (assign) uint8_t gPTPDomainNumber NS_AVAILABLE(10_9, NA);
/*!
	@property	identifyControlIndex
	@abstract	The descriptor_index of the CONTROL which implements the IDENTIFY for the entity if supported.
 */
@property (assign) uint16_t identifyControlIndex NS_AVAILABLE(10_9, NA);
/*!
	@property	interfaceIndex
	@abstract	The descriptor_index of the AVB_INTERFACE descriptor which is associated with this entity.
 */
@property (assign) uint16_t interfaceIndex NS_AVAILABLE(10_9, NA);
/*!
	@property	associationID
	@abstract	The association_id of the entity.
 */
@property (assign) uint64_t associationID;

/*!
	@property	macAddresses
	@abstract	An array of AVBMACAddress objects containing the current MAC addresses of the entity.
 */
@property (copy) NSArray <AVBMACAddress *>*macAddresses;

/*!
	@property	entityDiscovery
	@abstract	The AVB17221EntityDiscovery object which discovered the entity.
 */
@property (assign, nullable) AVB17221EntityDiscovery *entityDiscovery;

@end

NS_ASSUME_NONNULL_END
