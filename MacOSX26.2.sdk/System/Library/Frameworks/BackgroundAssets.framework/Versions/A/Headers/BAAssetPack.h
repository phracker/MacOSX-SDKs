//
//  BAAssetPack.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 3/10/25.
//

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An archive of assets that the system downloads together.
///
/// An instance of this class can be invalidated when the asset pack that it represents is updated on the server.
API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26))
API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
NS_REFINED_FOR_SWIFT
@interface BAAssetPack : NSObject

/// A unique identifier for the asset pack.
@property (readonly, copy) NSString* identifier NS_SWIFT_NAME(id);

/// The size of the download file containing the asset pack in bytes.
///
/// This is different than the installation size, which could be larger.
@property (readonly, assign) NSInteger downloadSize;

/// The asset pack’s version number
@property (readonly, assign) NSInteger version;

/// JSON-encoded custom information that’s associated with the asset pack.
///
/// This property is `nil` for Apple-hosted asset packs.
@property (nullable, readonly, copy) NSData* userInfo;

- (null_unspecified instancetype)init NS_UNAVAILABLE;

+ (null_unspecified instancetype)new NS_UNAVAILABLE;

/// Creates a download object for the asset pack that you schedule using a download manager.
/// - Remark: Use this method in your main app; use ``BAAssetPack/downloadForContentRequest:`` instead in your downloader extension.
- (BADownload*)download;

/// Creates a download object for the asset pack that you schedule using a download manager.
/// - Parameter contentRequest: The content request for the current extension invocation.
/// - Returns: A download object.
/// - Remark: Use this method in your downloader extension; use ``BAAssetPack/download`` instead in your main app.
- (BADownload*)downloadForContentRequest:(BAContentRequest)contentRequest;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
