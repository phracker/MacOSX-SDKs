//
//  BAAssetPackManifest.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 3/10/25.
//

#import <BackgroundAssets/BAAssetPack.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A representation of a manifest that lists asset packs that are available to download.
///
/// This class applies only when you want to manage your asset packs manually. Don’t use this class if you want to opt in to automatic management of asset packs.
API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26))
API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
NS_REFINED_FOR_SWIFT
@interface BAAssetPackManifest : NSObject

/// The asset packs that are available to download.
@property (readonly, copy) NSSet<BAAssetPack*>* assetPacks;

- (null_unspecified instancetype)init NS_UNAVAILABLE;

/// Initializes a representation of a manifest in memory given a URL to the manifest’s representation as a JSON file on disk.
/// - Parameters:
///   - URL: A URL to a local JSON file.
///   - applicationGroupIdentifier: The identifier of the application group in which to store unmanaged asset packs that are downloaded from the manifest.
///   - error: A pointer to an error that will be set if an error occurs.
- (nullable instancetype)initWithContentsOfURL:(NSURL*)URL
                    applicationGroupIdentifier:(NSString*)applicationGroupIdentifier
                                         error:(NSError* _Nullable * _Nullable)error
NS_SWIFT_NAME(init(contentsOf:appGroupID:));

/// Initializes a representation of a manifest in memory from JSON-encoded data.
/// - Parameters:
///   - data: JSON-encoded data.
///   - applicationGroupIdentifier: The identifier of the application group in which to store unmanaged asset packs that are downloaded from the manifest.
///   - error: A pointer to an error that will be set if an error occurs.
- (nullable instancetype)initFromData:(NSData*)data
           applicationGroupIdentifier:(NSString*)applicationGroupIdentifier
                                error:(NSError* _Nullable * _Nullable)error
NS_SWIFT_NAME(init(from:appGroupID:));

+ (null_unspecified instancetype)new NS_UNAVAILABLE;

/// Creates download objects for every asset pack in this manifest.
///
/// The returned download objects can be scheduled with the download manager.
/// - Returns: A collection of download objects.
/// - Remark: Use this method in your main app; use `-allDownloadsForContentRequest:` in your downloader extension.
- (NSSet<BADownload*>*)allDownloads;

/// Creates download objects for every asset pack in this manifest.
///
/// The returned download objects can be scheduled with the download manager.
/// - Parameter contentRequest: The content request for the current extension invocation.
/// - Returns: A collection of download objects.
/// - Remark: Use this method in your downloader extension; use `-allDownloads` instead in your main app.
- (NSSet<BADownload*>*)allDownloadsForContentRequest:(BAContentRequest)contentRequest;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
