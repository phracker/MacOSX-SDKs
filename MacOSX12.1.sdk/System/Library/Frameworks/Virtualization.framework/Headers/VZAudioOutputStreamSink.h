//
//  VZAudioOutputStreamSink.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for an audio output stream sink.
 @discussion
    An audio output stream sink defines how audio data from a guest is consumed on the host system.

    VZAudioOutputStreamSink should not be instantiated directly. One of its subclasses should be used instead.

 @see VZHostAudioOutputStreamSink
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZAudioOutputStreamSink : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
