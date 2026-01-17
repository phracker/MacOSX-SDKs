//
//  SHMatchedMediaItem.h
//  ShazamKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <ShazamKit/SHMediaItem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// How far in seconds is this match from the start of the reference audio
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemMatchOffset;

/// How much the match differs in frequency from reference material
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemFrequencySkew;

/// The value ranges from 0.0 to 1.0, where 1.0 indicates the highest level of confidence.
API_AVAILABLE(macos(15.4), ios(18.4), tvos(18.4), watchos(11.4), visionos(2.4))
SH_EXPORT SHMediaItemProperty const SHMediaItemConfidence;

/// An object that represents the metadata for a matched reference signature.
///
/// To access properties for custom media items, use subscripting. For more information, see ``SHMediaItem``.
SH_EXPORT NS_SWIFT_SENDABLE API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHMatchedMediaItem : SHMediaItem <NSSecureCoding>

/// A multiple for the difference in frequency between the matched audio and the query audio.
///
/// A value of `0.0` indicates that the query and matched audio are at the same frequency. Other values indicate that the query audio is playing at a different frequency. For example, if the original recording plays at `100` Hz, a value of `0.05` indicates that the query recording plays at `105` Hz.
///
/// No match returns if the frequency skew is too large.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) float frequencySkew;

/// The timecode in the reference recording that matches the start of the query, in seconds.
///
/// The value can be negative if the query signature contains unrecognizable data before the data that corresponds to the start of the matched reference item.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) NSTimeInterval matchOffset;

/// The updated timecode in the reference recording that matches the current playback position of the query audio, in seconds.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) NSTimeInterval predictedCurrentMatchOffset;

/// The level of confidence in the match result.
///
/// The value ranges from 0.0 to 1.0, where 1.0 indicates the highest level of confidence.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) float confidence API_AVAILABLE(macos(15.4), ios(18.4), tvos(18.4), watchos(11.4), visionos(2.4));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
