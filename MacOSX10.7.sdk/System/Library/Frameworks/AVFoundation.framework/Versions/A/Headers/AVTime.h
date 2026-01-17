/*
	File:  AVTime.h

	Framework:  AVFoundation
 
	Copyright 2010 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>


// utilities for carriage of CoreMedia time structures in NSValues

@interface NSValue (NSValueAVFoundationExtensions)

+ (NSValue *)valueWithCMTime:(CMTime)time NS_AVAILABLE(10_7, 4_0);

- (CMTime)CMTimeValue NS_AVAILABLE(10_7, 4_0);

+ (NSValue *)valueWithCMTimeRange:(CMTimeRange)timeRange NS_AVAILABLE(10_7, 4_0);
- (CMTimeRange)CMTimeRangeValue NS_AVAILABLE(10_7, 4_0);

+ (NSValue *)valueWithCMTimeMapping:(CMTimeMapping)timeMapping NS_AVAILABLE(10_7, 4_0);
- (CMTimeMapping)CMTimeMappingValue NS_AVAILABLE(10_7, 4_0);

@end

// utilities for encoding and decoding CoreMedia time structures for NSCoding

@interface NSCoder (AVTimeCoding)

- (void)encodeCMTime:(CMTime)time forKey:(NSString *)key NS_AVAILABLE(10_7, 4_0);
- (CMTime)decodeCMTimeForKey:(NSString *)key NS_AVAILABLE(10_7, 4_0);

- (void)encodeCMTimeRange:(CMTimeRange)timeRange forKey:(NSString *)key NS_AVAILABLE(10_7, 4_0);
- (CMTimeRange)decodeCMTimeRangeForKey:(NSString *)key NS_AVAILABLE(10_7, 4_0);

- (void)encodeCMTimeMapping:(CMTimeMapping)timeMapping forKey:(NSString *)key NS_AVAILABLE(10_7, 4_0);
- (CMTimeMapping)decodeCMTimeMappingForKey:(NSString *)key NS_AVAILABLE(10_7, 4_0);

@end

