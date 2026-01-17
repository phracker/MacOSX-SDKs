#if !__has_include(<AVFCore/AVTime.h>)
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

+ (NSValue *)valueWithCMTime:(CMTime)time API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
@property (readonly) CMTime CMTimeValue API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

+ (NSValue *)valueWithCMTimeRange:(CMTimeRange)timeRange API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
@property (readonly) CMTimeRange CMTimeRangeValue API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

+ (NSValue *)valueWithCMTimeMapping:(CMTimeMapping)timeMapping API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
@property (readonly) CMTimeMapping CMTimeMappingValue API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

@end

// utilities for encoding and decoding CoreMedia time structures for NSCoding

@interface NSCoder (AVTimeCoding)

- (void)encodeCMTime:(CMTime)time forKey:(NSString *)key API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
- (CMTime)decodeCMTimeForKey:(NSString *)key API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

- (void)encodeCMTimeRange:(CMTimeRange)timeRange forKey:(NSString *)key API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
- (CMTimeRange)decodeCMTimeRangeForKey:(NSString *)key API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

- (void)encodeCMTimeMapping:(CMTimeMapping)timeMapping forKey:(NSString *)key API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
- (CMTimeMapping)decodeCMTimeMappingForKey:(NSString *)key API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVTime.h>
#endif
