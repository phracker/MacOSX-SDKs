//
//  NSFileProviderModifyItemOptions.h
//
//  Copyright © 2019-2022 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>

/// Options for modifying items.
typedef NS_OPTIONS(NSUInteger, NSFileProviderModifyItemOptions) {
    /// An option that indicates the changes may already exist in your remote storage.
    ///
    /// This option applies when moving the item to a location where it may refer to an item that already exists.
    /// This situation may occur when merging two directories together.
    NSFileProviderModifyItemMayAlreadyExist = 1 << 0,
    /// An option to fail an upload in the event of a version conflict.
    ///
    /// If you adopt this option, and an uploaded item's base version doesn't match the version on the server, fail and return ``NSFileProviderError/localVersionConflictingWithServer`` (Swift) or ``NSFileProviderErrorCode/NSFileProviderErrorLocalVersionConflictingWithServer`` (Objective-C) in your implementation of `modifyItem`.
    ///
    /// To support the fail-on-conflict behavior in your file provider, indicate the support by adding the following key/value pair to the extension's Info pane.
    ///
    /// ```
    /// <key>NSExtension</key>
    /// <dict>
    ///     <key>NSExtensionFileProviderSupportsFailingUploadOnConflict</key>
    ///     <true/>
    /// </dict>
    /// ```
    NSFileProviderModifyItemFailOnConflict FILEPROVIDER_API_AVAILABILITY_SYNC_CONTROLS = 1 << 1,
    /// An option to require the upload to complete before calling the completion handler.
    ///
    /// This option allows the calling application to know when the uploaded version of the file is on the server.
    NSFileProviderModifyItemIsImmediateUploadRequestByPresentingApplication FILEPROVIDER_API_AVAILABILITY_SYNC_CONTROLS = 1 << 2,
} FILEPROVIDER_API_AVAILABILITY_V3_IOS;
