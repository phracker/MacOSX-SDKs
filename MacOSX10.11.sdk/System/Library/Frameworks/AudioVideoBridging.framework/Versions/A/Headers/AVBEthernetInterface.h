//
//  AVBEthernetInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/*!
	@class		AVBEthernetInterface
	@abstract	AVBEthernetInterface is a concrete subclass of AVBInterface providing access to the AVB services of the interface.
	@discussion	AVBEthernetInterface is a concrete subclass of AVBInterface providing access to the AVB services of the interface.
				AVBEthernetInterface objects should be created for an IEEE 802.3 ethernet based interface on which AVB functionality 
				is being used.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVBEthernetInterface : AVBInterface
{
@private
	io_object_t _notification;
}

@end
