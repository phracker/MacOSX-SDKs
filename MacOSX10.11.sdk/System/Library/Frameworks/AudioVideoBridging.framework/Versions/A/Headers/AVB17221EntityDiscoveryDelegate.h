//
//  AVB17221EntityDiscoveryDelegate.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVB17221Entity;
@class AVB17221EntityDiscovery;


typedef NS_OPTIONS(NSUInteger, AVB17221EntityPropertyChanged)
{
/*!
	@constant	AVB17221EntityPropertyChangedTimeToLive
	@abstract	The time to live property of the entity has changed.
 */
	AVB17221EntityPropertyChangedTimeToLive =												0x00000001,
/*!
	@constant	AVB17221EntityPropertyChangedGUID
	@abstract	The GUID property of the entity has changed.
 */
	AVB17221EntityPropertyChangedGUID NS_ENUM_DEPRECATED(10_8, 10_9, NA, NA) =				0x00000002,
/*!
	@constant	AVB17221EntityPropertyChangedEntityID
	@abstract	The entityID property of the entity has changed.
 */
	AVB17221EntityPropertyChangedEntityID NS_ENUM_AVAILABLE(10_9, NA)	=					0x00000002,
/*!
	@constant	AVB17221EntityPropertyChangedVendorID
	@abstract	The vendor ID property of the entity has changed.
 */
	AVB17221EntityPropertyChangedVendorID =													0x00000004,
/*!
	@constant	AVB17221EntityPropertyChangedModelID
	@abstract	The model ID property of the entity has changed.
 */
	AVB17221EntityPropertyChangedModelID =													0x00000008,
/*!
	@constant	AVB17221EntityPropertyChangedEntityCapabilities
	@abstract	The entity capabilities property of the entity has changed.
 */
	AVB17221EntityPropertyChangedEntityCapabilities =										0x00000010,
/*!
	@constant	AVB17221EntityPropertyChangedTalkerStreamSources
	@abstract	The taler stream sources property of the entity has changed.
 */
	AVB17221EntityPropertyChangedTalkerStreamSources =										0x00000020,
/*!
	@constant	AVB17221EntityPropertyChangedTalkerCapabilities
	@abstract	The taler capabilities property of the entity has changed.
 */
	AVB17221EntityPropertyChangedTalkerCapabilities =										0x00000040,
/*!
	@constant	AVB17221EntityPropertyChangedListenerStreamSins
	@abstract	The listener stream sins property of the entity has changed.
 */
	AVB17221EntityPropertyChangedListenerStreamSinks =										0x00000080,
/*!
	@constant	AVB17221EntityPropertyChangedListenerCapabilities
	@abstract	The listener capabilities property of the entity has changed.
 */
	AVB17221EntityPropertyChangedListenerCapabilities =										0x00000100,
/*!
	@constant	AVB17221EntityPropertyChangedControllerCapabilities
	@abstract	The controller capabilities property of the entity has changed.
 */
	AVB17221EntityPropertyChangedControllerCapabilities =									0x00000200,
/*!
	@constant	AVB17221EntityPropertyChangedAvailableIndex
	@abstract	The available index property of the entity has changed.
 */
	AVB17221EntityPropertyChangedAvailableIndex =											0x00000400,
/*!
	@constant	AVB17221EntityPropertyChangedASGrandmasterID
	@abstract	The AS grandmaster ID property of the entity has changed.
 */
	AVB17221EntityPropertyChangedASGrandmasterID NS_ENUM_DEPRECATED(10_8, 10_9, NA, NA) =	0x00000800,
/*!
	@constant	AVB17221EntityPropertyChangedGPTPGrandmasterID
	@abstract	The gPTP grandmaster ID property of the entity has changed.
 */
	AVB17221EntityPropertyChangedGPTPGrandmasterID NS_ENUM_AVAILABLE(10_9, NA) =			0x00000800,
/*!
	@constant	AVB17221EntityPropertyChangedMACAddress
	@abstract	The MAC address property of the entity has changed.
 */
	AVB17221EntityPropertyChangedMACAddress =												0x00001000,
/*!
	@constant	AVB17221EntityPropertyChangedAssociationID
	@abstract	The association ID property of the entity has changed.
 */
	AVB17221EntityPropertyChangedAssociationID =											0x00008000,
/*!
	@constant	AVB17221EntityPropertyChangedEntityType
	@abstract	The entity type property of the entity has changed.
 */
	AVB17221EntityPropertyChangedEntityType =												0x00010000,
/*!
	@constant	AVB17221EntityPropertyChangedIdentifyControlIndex
	@abstract	The identify control index property of the entity has changed.
 */
	AVB17221EntityPropertyChangedIdentifyControlIndex NS_ENUM_AVAILABLE(10_9, NA) =			0x00020000,
/*!
	@constant	AVB17221EntityPropertyChangedInterfaceIndex
	@abstract	The interface index property of the entity has changed.
 */
	AVB17221EntityPropertyChangedInterfaceIndex NS_ENUM_AVAILABLE(10_9, NA) =				0x00040000,
/*!
	@constant	AVB17221EntityPropertyChangedGPTPDomainNumber
	@abstract	The gPTP domain property of the entity has changed.
 */
	AVB17221EntityPropertyChangedGPTPDomainNumber NS_ENUM_AVAILABLE(10_9, NA) =				0x00080000,
} NS_ENUM_AVAILABLE(10_8, NA);


/*!
	@constant	kAVB17221EntityPropertyChangedShouldntChangeMask
	@abstract	A bit mask of all of the properties of an entity which should never change during a property update.
 */
#define kAVB17221EntityPropertyChangedShouldntChangeMask		(AVB17221EntityPropertyChangedEntityID | AVB17221EntityPropertyChangedVendorID | \
																AVB17221EntityPropertyChangedModelID | \
																AVB17221EntityPropertyChangedTalkerStreamSources |  AVB17221EntityPropertyChangedTalkerCapabilities | \
																AVB17221EntityPropertyChangedListenerStreamSinks |  AVB17221EntityPropertyChangedListenerCapabilities | \
																AVB17221EntityPropertyChangedControllerCapabilities |  AVB17221EntityPropertyChangedMACAddress | \
																AVB17221EntityPropertyChangedAssociationID | AVB17221EntityPropertyChangedEntityType | AVB17221EntityPropertyChangedIdentifyControlIndex | AVB17221EntityPropertyChangedInterfaceIndex)
																
/*!
	@constant	kAVB17221EntityPropertyChangedCanChangeMask
	@abstract	A bit mask of all of the properties of an entity which may change during a property update.
 */
#define kAVB17221EntityPropertyChangedCanChangeMask				(AVB17221EntityPropertyChangedTimeToLive | AVB17221EntityPropertyChangedAvailableIndex | \
																AVB17221EntityPropertyChangedGPTPGrandmasterID | AVB17221EntityPropertyChangedGPTPDomainNumber \
																AVB17221EntityPropertyChangedEntityCapabilities )



/*!
	@protocol	AVB17221EntityDiscoveryDelegate
	@abstract	AVB17221EntityDiscoveryDelegate is an objective-c protocol for classes acting as the discovery delegate of the AVB17221EntityDiscovery object.
	@discussion	AVB17221EntityDiscoveryDelegate is an objective-c protocol for classes acting as the discovery delegate of the AVB17221EntityDiscovery object.
				There is a separate callback for each phase of entity discover and property updates. Callbacks are separated between entities discovered on the 
				network and those published locally on the Mac.
 */
@protocol AVB17221EntityDiscoveryDelegate

@required

/*!
	@method		didAddRemoteEntity:on17221EntityDiscovery:
	@abstract	This method is called whenever a new IOAVB17221RemoteEntity is published.
	@param		newEntity		The entity which has been discovered.
	@param		entityDiscovery	The entity discovery service which discovered the entity.
 */
- (void)didAddRemoteEntity:(AVB17221Entity *)newEntity on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

/*!
	@method		didRemoveRemoteEntity:on17221EntityDiscovery:
	@abstract	This method is called whenever an IOAVB17221RemoteEntity is removed.
	@param		oldEntity		The entity which was removed.
	@param		entityDiscovery	The entity discovery service which discovered the entity.
 */
- (void)didRemoveRemoteEntity:(AVB17221Entity *)oldEntity on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

/*!
	@method		didRediscoverRemoteEntity:on17221EntityDiscovery:
	@abstract	This method is called whenever the entity discovery service detects an IOAVB17221RemoteEntity has been published but it hasn't been removed.
	@param		entity			The entity which was rediscovered.
	@param		entityDiscovery	The entity discovery service which discovered the entity.
 */
- (void)didRediscoverRemoteEntity:(AVB17221Entity *)entity on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

/*!
	@method		didUpdateRemoteEntity:changedProperties:on17221EntityDiscovery:
	@abstract	This method is called whenever the properties of the entity are updated and the kernel notifies user space.
	@param		entity				The entity which had the properties updated.
	@param		changedProperties	A bitfield indicating which fields had their values updated.
	@param		entityDiscovery		The entity discovery service which discovered the entity.
 */
- (void)didUpdateRemoteEntity:(AVB17221Entity *)entity changedProperties:(AVB17221EntityPropertyChanged)changedProperties on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

/*!
	@method		didAddLocalEntity:on17221EntityDiscovery:
	@abstract	This method is called whenever a new IOAVB17221LocalEntity is published.
	@param		newEntity		The entity which has been discovered.
	@param		entityDiscovery	The entity discovery service which discovered the entity.
 */
- (void)didAddLocalEntity:(AVB17221Entity *)newEntity on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

/*!
	@method		didRemoveLocalEntity:on17221EntityDiscovery:
	@abstract	This method is called whenever an IOAVB17221LocalEntity is removed.
	@param		oldEntity		The entity which was removed.
	@param		entityDiscovery	The entity discovery service which discovered the entity.
 */
- (void)didRemoveLocalEntity:(AVB17221Entity *)oldEntity on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

/*!
	@method		didRediscoverLocalEntity:on17221EntityDiscovery:
	@abstract	This method is called whenever the entity discovery service detects an IOAVB17221LocalEntity has been published but it hasn't been removed.
	@param		entity			The entity which was rediscovered.
	@param		entityDiscovery	The entity discovery service which discovered the entity.
 */
- (void)didRediscoverLocalEntity:(AVB17221Entity *)entity on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

/*!
	@method		didUpdateLocalEntity:changedProperties:on17221EntityDiscovery:
	@abstract	This method is called whenever the properties of the entity are updated and the kernel notifies user space.
	@param		entity				The entity which had the properties updated.
	@param		changedProperties	A bitfield indicating which fields had their values updated.
	@param		entityDiscovery		The entity discovery service which discovered the entity.
 */
- (void)didUpdateLocalEntity:(AVB17221Entity *)entity changedProperties:(AVB17221EntityPropertyChanged)changedProperties on17221EntityDiscovery:(AVB17221EntityDiscovery *)entityDiscovery;

@end

NS_ASSUME_NONNULL_END
