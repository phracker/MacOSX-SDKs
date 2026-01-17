//
//  BAAssetPackStatus.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 3/10/25.
//

/// The status of an asset pack.
typedef NS_OPTIONS(NSUInteger, BAAssetPackStatus) {
    
    /// A status value that indicates that the asset pack is available to download.
    BAAssetPackStatusDownloadAvailable = 1 << 0,
    
    /// A status value that indicates that an update to the asset pack is available to download.
    BAAssetPackStatusUpdateAvailable = 1 << 1,
    
    /// A status value that indicates that the downloaded asset pack is up to date.
    BAAssetPackStatusUpToDate = 1 << 2,
    
    /// A status value that indicates that the downloaded asset pack is out of date.
    ///
    /// The presence of this status value doesn’t necessarily imply that an update to the asset pack can be downloaded over the current network connection. Check for the presence of ``BAAssetPackStatus/updateAvailable`` to determine whether an update can currently be downloaded.
    BAAssetPackStatusOutOfDate = 1 << 3,
    
    /// A status value that indicates that the asset pack is no longer available to download.
    ///
    /// Obsolete asset packs can’t be updated, and they also can’t be redownloaded once removed.
    BAAssetPackStatusObsolete = 1 << 4,
    
    /// A status value that indicates that the system is currently downloading the asset pack.
    BAAssetPackStatusDownloading = 1 << 5,
    
    /// A status value that indicates that the system finished downloading the asset pack.
    BAAssetPackStatusDownloaded = 1 << 6
    
} API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;
