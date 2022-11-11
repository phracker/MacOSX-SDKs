//
//  AVB17221Entity.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2020 Apple Inc. All rights reserved.
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
API_AVAILABLE(macos(10.8))
@interface AVB17221Entity : NSObject


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
	@property	entityID
	@abstract	The Unique Identifier (entity_id) of the entity.
 */
@property (assign) uint64_t entityID API_AVAILABLE(macos(10.9));
/*!
	@property	entityModelID
	@abstract	The Entity Model Unique Identifier (entity_model_id) of the entity.
 */
@property (assign) uint64_t entityModelID API_AVAILABLE(macos(10.9));
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
	@property	gPTPGrandmasterID
	@abstract	The clock identifier of the IEEE Std 802.1AS-2011 grandmaster of the entity.
 */
@property (assign) uint64_t gPTPGrandmasterID API_AVAILABLE(macos(10.9));
/*!
	@property	gPTPDomainNumber
	@abstract	The domain number of the IEEE Std 802.1AS-2011 grandmaster of the entity.
 */
@property (assign) uint8_t gPTPDomainNumber API_AVAILABLE(macos(10.9));
/*!
	@property	identifyControlIndex
	@abstract	The descriptor_index of the CONTROL which implements the IDENTIFY for the entity if supported.
 */
@property (assign) uint16_t identifyControlIndex API_AVAILABLE(macos(10.9));
/*!
	@property	interfaceIndex
	@abstract	The descriptor_index of the AVB_INTERFACE descriptor which is associated with this entity.
 */
@property (assign) uint16_t interfaceIndex API_AVAILABLE(macos(10.9));
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
@property (weak, nullable) AVB17221EntityDiscovery *entityDiscovery;

@end

NS_ASSUME_NONNULL_END
