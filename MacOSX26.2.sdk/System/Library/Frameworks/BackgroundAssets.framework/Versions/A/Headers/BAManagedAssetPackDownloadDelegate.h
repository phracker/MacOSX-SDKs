//
//  BAManagedAssetPackDownloadDelegate.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 3/10/25.
//

#import <BackgroundAssets/BAAssetPack.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that handles status updates when downloading an asset pack.
API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26))
API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
NS_REFINED_FOR_SWIFT
@protocol BAManagedAssetPackDownloadDelegate <NSObject>

@optional

/// Notifies the receiver that the download began or resumed after being paused.
/// - Parameter assetPack: The asset pack.
- (void)downloadOfAssetPackBegan:(BAAssetPack*)assetPack;

/// Notifies the receiver that the download paused.
/// - Parameter assetPack: The asset pack.
- (void)downloadOfAssetPackPaused:(BAAssetPack*)assetPack;

/// Notifies the receiver that the download is in progress.
/// - Parameters:
///   - assetPack: The asset pack.
///   - progress: The download progress.
- (void)downloadOfAssetPack:(BAAssetPack*)assetPack
                hasProgress:(NSProgress*)progress;

/// Notifies the receiver that the download completed and that the asset pack is available locally.
/// - Parameter assetPack: The asset pack.
- (void)downloadOfAssetPackFinished:(BAAssetPack*)assetPack;

/// Notifies the receiver that the download failed.
/// - Parameters:
///   - assetPack: The asset pack.
///   - error: The error that occurred.
- (void)downloadOfAssetPack:(BAAssetPack*)assetPack
            failedWithError:(NSError*)error;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
