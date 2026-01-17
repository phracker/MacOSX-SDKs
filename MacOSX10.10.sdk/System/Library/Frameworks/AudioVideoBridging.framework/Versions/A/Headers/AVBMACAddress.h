//
//  AVBMACAddress.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE(10_8, NA)
@interface AVBMACAddress : NSObject <NSCopying>
{
	@private
	uint8_t _bytes[AVBMACAddressSize];
}

- (instancetype)initWithBytes:(uint8_t *)bytes;

@property (assign, readonly) const uint8_t *bytes;

@property (copy) NSData *dataRepresentation;

@property (copy) NSString *stringRepresentation;

@property (assign, getter=isMulticast) BOOL multicast;

@end
