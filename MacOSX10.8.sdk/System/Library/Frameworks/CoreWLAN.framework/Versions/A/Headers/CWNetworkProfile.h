/*!
 * @header CWNetworkProfile.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_NETWORK_PROFILE_H_
#define _CORE_WLAN_NETWORK_PROFILE_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

@class CWNetwork;


#pragma mark -
/*!
 * @class
 * @abstract Encapsulates an immutable network profile entry.
 */
@interface CWNetworkProfile : NSObject <NSCopying, NSMutableCopying, NSCoding> {
@private
	NSDictionary *_info;
@protected
	NSData *_ssidData;
	NSString *_ssid;
	NSUInteger _securityType;
	BOOL _disabled;
	BOOL _systemMode;
	BOOL _hiddenNetwork;
	NSDate *_lastConnected;
	CWNetwork *_cachedNetwork;
	BOOL _captiveNetwork;
	BOOL _temporarilyDisabled;
    BOOL _autoLogin;
}

/*!
 * @property
 * @abstract The service set identifier (SSID) for the network profile, encoded as a string.
 * @discussion If the SSID can not be encoded as a valid UTF-8 or WinLatin1 string, this method returns <i>nil</i>.
 */
@property(readonly,copy) NSString *ssid NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The service set identifier (SSID) for the network profile, returned as data.
 * @discussion The SSID is 1-32 octets.
 */
@property(readonly, copy) NSData *ssidData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The security mode for the network profile. 
 */
@property(readonly, assign) CWSecurity security NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Getting a network profile */
/*!
 * @method
 * @result An CWNetworkProfile object.
 * @abstract Convenience method for getting a CWNetworkProfile object.
 */
+ (id)networkProfile NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @result An CWNetworkProfile object.
 * @abstract Creates and returns a CWNetworkProfile object.
 * @discussion This method is the designated initializer for the CWNetworkProfile class.
 */
- (id)init NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @param networkProfile The CWNetworkProfile object to use to initialize a new CWNetworkProfile object.
 * @result A CWNetworkProfile object.
 * @abstract Creates and returns a CWNetworkProfile object initialized with the given CWNetworkProfile object.
 */
- (id)initWithNetworkProfile:(CWNetworkProfile*)networkProfile NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @param networkProfile The CWNetworkProfile object to use to initialize a new CWNetworkProfile object.
 * @result A CWNetworkProfile object.
 * @abstract Convenience method for getting a CWNetworkProfile object initialized with the given CWNetworkProfile object.
 */
+ (id)networkProfileWithNetworkProfile:(CWNetworkProfile*)networkProfile NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Comparing network profiles */
/*!
 * @method
 * @param networkProfile The CWNetworkProfile object with which to compare the receiver.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Determine CWNetworkProfile object equality.
 * @discussion CWNetwork objects are considered equal if their corresponding <i>ssidData</i> and <i>securityType</i> properties are equal. 
 */
- (BOOL)isEqualToNetworkProfile:(CWNetworkProfile*)networkProfile NS_AVAILABLE_MAC(10_7);
@end

#pragma mark -
/*!
 * @class
 * @abstract Encapsulates a mutable network profile entry.
 */
@interface CWMutableNetworkProfile : CWNetworkProfile
@property(readwrite, copy) NSData *ssidData NS_AVAILABLE_MAC(10_7);
@property(readwrite, assign) CWSecurity security NS_AVAILABLE_MAC(10_7);
@end

#endif /* _CORE_WLAN_NETWORK_PROFILE_H_ */
