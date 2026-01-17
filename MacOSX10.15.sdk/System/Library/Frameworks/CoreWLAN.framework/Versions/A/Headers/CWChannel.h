/*!
 * @header CWChannel.h
 * @copyright 2010-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_CHANNEL_H_
#define _CORE_WLAN_CHANNEL_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

/*!
 * @class
 *
 * @abstract
 * Represents an IEEE 802.11 channel.
 *
 * @discussion
 * The CWChannel class is used by both CWInterface and CWNetwork as a representation of an IEEE 802.11 Wi-Fi channel.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_MAC(10_7)
@interface CWChannel : NSObject <NSCopying, NSSecureCoding>
{
    @private
    
        NSDictionary *_info;
}

/*!
 * @property
 *
 * @abstract 
 * The channel number represented as an integer value.
 */
@property(readonly) NSInteger channelNumber NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * The channel width as indicated by the CWChannelWidth type.
 */
@property(readonly) CWChannelWidth channelWidth NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract
 * The channel band as indicated by the CWChannelBand type.
 */
@property(readonly) CWChannelBand channelBand NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Comparing Wi-Fi Channels */

/*!
 * @method
 *
 * @param channel
 * The CWChannel with which to compare the receiver.
 *
 * @result 
 * YES if the objects are equal, otherwise NO.
 *
 * @abstract 
 * Determine CWChannel equality.
 *
 * @discussion 
 * CWChannel objects are considered equal if all their corresponding properties are equal.
 */
- (BOOL)isEqualToChannel:(CWChannel *)channel NS_AVAILABLE_MAC(10_7);

@end
NS_ASSUME_NONNULL_END

#endif /* _CORE_WLAN_CHANNEL_H_ */
