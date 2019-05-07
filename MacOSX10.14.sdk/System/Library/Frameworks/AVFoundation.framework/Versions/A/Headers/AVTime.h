/*
	File:  AVTime.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

/*
	Utilities for carriage of CoreMedia time structures in NSValues
	
	Notes for archiving NSValues created with CMTime / CMTimeRange / CMTimeMapping.
	We recommend that on macOS Sierra, iOS 10, and later you use NSKeyedArchiver to serialize NSValues created with a CMTime, CMTimeRange, or CMTimeMapping. This will ensure that before and after archiving, use of such values with -isEqual:, with -[NSDictionary objectForKey:], and with other facilities that depend on hashing or equality, will have correct results.
	Should it be necessary to write a value in a way that is readable pre-Sierra or pre-iOS 10, you can re-encode the values using [NSValue valueWithBytes:objCType:] before handing it to the NSArchiver. If you are reading serialized values produced with an NSArchiver, it will still successfully produce NSValues. If in this scenario you require the use of such values with -isEqual:, with -[NSDictionary objectForKey:], and with other facilities that depend on hashing or equality to have correct results, we recommend that you immediately re-create a new NSValue via the NSValue utilities provided here and use the new NSValue in place of the unarchived one.
*/

@interface NSValue (NSValueAVFoundationExtensions)

+ (NSValue *)valueWithCMTime:(CMTime)time NS_AVAILABLE(10_7, 4_0);
@property (readonly) CMTime CMTimeValue NS_AVAILABLE(10_7, 4_0);

+ (NSValue *)valueWithCMTimeRange:(CMTimeRange)timeRange NS_AVAILABLE(10_7, 4_0);
@property (readonly) CMTimeRange CMTimeRangeValue NS_AVAILABLE(10_7, 4_0);

+ (NSValue *)valueWithCMTimeMapping:(CMTimeMapping)timeMapping NS_AVAILABLE(10_7, 4_0);
@property (readonly) CMTimeMapping CMTimeMappingValue NS_AVAILABLE(10_7, 4_0);

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

NS_ASSUME_NONNULL_END
