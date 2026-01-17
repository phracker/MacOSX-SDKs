//
//  SHCustomCatalog.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHSignature.h>
#import <ShazamKit/SHMediaItem.h>
#import <ShazamKit/SHCatalog.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object for storing the reference signatures for custom audio recordings and their associated metadata.
///
/// Create a custom catalog by adding reference signatures that you generate from audio that you provide. You also add the associated metadata for each signature. Save your custom catalog and share it with others. You can also load a saved catalog.
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHCustomCatalog : SHCatalog

/// The data representation of this file, it can be written to disk
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSData *dataRepresentation API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
 
/// Adds a reference signature and its associated metadata to a catalog.
///
///
/// > Note:
/// > This system ignores calls to `addReferenceSignature(_:representing:)` after adding the catalog to an `SHSession`.
///
/// - Parameters:
///   - signature: The reference signature for the audio recording.
///   - mediaItems: The metadata for the recording.
- (BOOL)addReferenceSignature:(SHSignature *)signature representingMediaItems:(NSArray<SHMediaItem *> *)mediaItems error:(NSError **)error;

/// Loads a saved custom catalog from a file.
///
/// - Parameters:
///  - customCatalogURL: The file URL for a custom catalog.
///  - error: An output value in Objective-C that indicates the type of error; otherwise, `nil`.
- (BOOL)addCustomCatalogFromURL:(NSURL *)customCatalogURL error:(NSError **)error;

/// Saves the custom catalog to a local file.
///
/// If `destinationURL` is a directory, the system creates a `Signatures.shazamcatalog` file.
///
/// - Parameters:
///   - destinationURL: A URL for the saved custom catalog file.
///   - error: An output value in Objective-C that indicates the type of error; otherwise, `nil`.
///
/// - Returns: `YES` if the catalog writes to the file; otherwise, `NO`.
- (BOOL)writeToURL:(NSURL *)destinationURL error:(NSError **)error API_DEPRECATED("Use dataRepresentation", macos(12.0, 15.0), ios(15.0, 18.0), tvos(15.0, 18.0), watchos(8.0, 11.0));

/// Creates a new custom catalog object for storing reference audio signatures and their associated metadata.
///
/// - Returns: A new custom catalog for storing processed reference audio recordings and their associated metadata.
+ (instancetype)new API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_SWIFT_UNAVAILABLE("Use init in Swift");

/// Creates a new custom catalog object for storing reference audio signatures and their associated metadata.
- (instancetype)init API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// Load a @c SHCustomCatalog from data
/// @param dataRepresentation The data representation of the @c SHCustomCatalog
/// @param error Error populated if not a valid data representation
- (nullable instancetype)initWithDataRepresentation:(NSData *)dataRepresentation error:(NSError **)error API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
