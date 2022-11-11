//
//  NIConfiguration.h
//  NearbyInteraction
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A type used to uniquely discover and identify a device in a nearby interaction session.
*/
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@interface NIDiscoveryToken : NSObject <NSCopying, NSSecureCoding>

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 An object to describe and configure parameters to be used in a nearby interaction session.
*/
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@interface NIConfiguration : NSObject <NSCopying, NSSecureCoding>

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 An object to describe and configure parameters to be used in a nearby interaction session for mutual relative positional measurements.
 @discussion Devices engaged in a session run with an NINearbyPeerConfiguration are able to continuously generate positional measurements relative to one another.
*/
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@interface NINearbyPeerConfiguration : NIConfiguration

/**
 The discovery token identifiying the peer device for this session configuration.
*/
@property (nonatomic, copy, readonly) NIDiscoveryToken *peerDiscoveryToken;

/**
 Initializes a new configuration with the provided peer token.
 @param peerToken A discovery token received from the peer for this session.
 */
- (instancetype)initWithPeerToken:(NIDiscoveryToken *)peerToken;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A session configuration that enables interaction with supported accessories.
*/
API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos)
NI_EXPORT
@interface NINearbyAccessoryConfiguration : NIConfiguration

/**
 The discovery token identifying the accessory device for this session configuration.
 @discussion NINearbyObject updates for this accessory will contain this discovery token.
*/
@property (nonatomic, copy, readonly) NIDiscoveryToken *accessoryDiscoveryToken;

/**
Create a new nearby accessory configuration using data received from the accessory.

@param data Configuration data received from the accessory.
@param error An optional out error parameter that will be populated with an error if the provided data is invalid or unsupported.
*/
- (nullable instancetype)initWithData:(NSData *)data error:(NSError **)error;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end



NS_ASSUME_NONNULL_END
