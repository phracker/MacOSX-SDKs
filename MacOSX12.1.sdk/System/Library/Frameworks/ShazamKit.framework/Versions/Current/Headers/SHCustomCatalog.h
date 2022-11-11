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

NS_ASSUME_NONNULL_BEGIN

/// @brief Configure a custom catalog of @c SHSignature objects to match against
/// @discussion Use a custom catalog if you intend to search against reference signatures that you have provided yourself. All matches will be performed locally on the device against the signatures added to this Catalog.
/// @c SHMediaItem can be built using custom data that will be returned when a match is made.
/// Once this catalog has been built it can be written to disk and loaded again at a later date.
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHCustomCatalog : SHCatalog

/// Add a reference @c SHSignature and its associated @c SHMediaItem for matching
/// @param signature The reference to match against
/// @param mediaItems The metadata associated with the @c SHSignature
/// @discussion Once the @c SHCatalog had been added to a @c SHSession further calls to this method will be ignored
- (BOOL)addReferenceSignature:(SHSignature *)signature representingMediaItems:(NSArray<SHMediaItem *> *)mediaItems error:(NSError **)error;

/// Load a pre made Custom catalog from disk
/// @param customCatalogURL The path to the assets
/// @param error An error if the bundle could not be loaded
- (BOOL)addCustomCatalogFromURL:(NSURL *)customCatalogURL error:(NSError **)error;

/// Write this Catalog to disk
/// @discussion A Catalog can safely be shared among devices
/// @note If the `destinationURL` is a directory, a file named Signatures.shazamcatalog will be created
/// @param destinationURL The location to write to
/// @param error populated on error, otherwise nil
/// @return YES on success, NO on failure with a populated error parameter
- (BOOL)writeToURL:(NSURL *)destinationURL error:(NSError **)error;

+ (instancetype)new API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_SWIFT_UNAVAILABLE("Use init in Swift");
- (instancetype)init API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end


NS_ASSUME_NONNULL_END
