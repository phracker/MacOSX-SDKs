//
//  AVBEthernetInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/*!
	@class		AVBEthernetInterface
	@abstract	AVBEthernetInterface is a concrete subclass of AVBInterface providing access to the AVB services of the interface.
	@discussion	AVBEthernetInterface is a concrete subclass of AVBInterface providing access to the AVB services of the interface.
				AVBEthernetInterface objects should be created for an IEEE 802.3 ethernet based interface on which AVB functionality 
				is being used.
 */
API_AVAILABLE(macos(10.8))
@interface AVBEthernetInterface : AVBInterface
{
}

@end
