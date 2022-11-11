//
//  VZAudioInputStreamSource.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for an audio input stream source.
 @discussion
    An audio input stream source defines how audio input data for a guest is produced on the host system.

    VZAudioInputStreamSource should not be instantiated directly. One of its subclasses should be used instead.

 @see VZHostAudioInputStreamSource
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZAudioInputStreamSource : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
