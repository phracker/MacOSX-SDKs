/*!
 * @header CWChannel.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_CHANNEL_H_
#define _CORE_WLAN_CHANNEL_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

#pragma mark -
/*!
 * @class
 * @abstract Encapsulates an IEEE 802.11 channel.
 */
@interface CWChannel : NSObject <NSCopying, NSCoding> {
@private
	NSDictionary *_info;
}

/*!
 * @property
 * @abstract The channel number.
 */
@property(readonly) NSUInteger channelNumber NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The channel width.
 */
@property(readonly) CWChannelWidth channelWidth NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The channel band.
 */
@property(readonly) CWChannelBand channelBand NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Comparing channels */
/*!
 * @method
 * @param channel The CWChannel object with which to compare the receiver.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Determine CWChannel object equality.
 * @discussion CWChannel objects are considered equal if all their corresponding properties are equal. 
 */
- (BOOL)isEqualToChannel:(CWChannel*)channel NS_AVAILABLE_MAC(10_7);
@end

#endif /* _CORE_WLAN_CHANNEL_H_ */
