//
//  SHSignature.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that contains the opaque data and other information for a signature.
///
/// Save your signature to a file and share it with others by writing the data to a file. You can use the saved signatures of reference recordings to populate a custom catalog.
///
/// Check whether your captured query signature is long enough to search for a match by comparing ``duration`` to the ``SHCatalog/minimumQuerySignatureDuration`` and ``SHCatalog/maximumQuerySignatureDuration`` of a catalog.
SH_EXPORT NS_SWIFT_SENDABLE API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHSignature : NSObject <NSSecureCoding, NSCopying>

/// The duration of the audio you use to generate the signature.
///
/// Audio that contains periods of silence may result in a duration value that's shorter than the full duration of the original audio track.
@property(NS_NONATOMIC_IOSONLY, assign, readonly) NSTimeInterval duration;

/// The raw data for the signature.
@property(NS_NONATOMIC_IOSONLY, strong, readonly) NSData *dataRepresentation;

/// Creates a signature object from raw data.
///
/// - Parameters:
///   - dataRepresentation: The raw data for the signature.
///   - error: The error that occurs; otherwise, `nil`.
///
/// - Returns: A signature if the raw data is a valid signature; otherwise, `nil`.
+ (nullable SHSignature *)signatureWithDataRepresentation:(NSData *)dataRepresentation error:(NSError **)error;

/// Creates a signature object from raw data.
///
/// - Parameters:
///   - dataRepresentation: The raw data for the signature.
///   - error: The error that occurs; otherwise, `nil`.
///
/// - Returns: A signature if the raw data is a valid signature; otherwise, `nil`.
- (nullable instancetype)initWithDataRepresentation:(NSData *)dataRepresentation error:(NSError **)error NS_DESIGNATED_INITIALIZER;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
