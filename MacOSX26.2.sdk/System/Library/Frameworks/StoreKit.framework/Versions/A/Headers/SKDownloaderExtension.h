//
//  SKDownloaderExtension.h
//  StoreKit
//
//  Created by Gabriel Jacoby-Cooper on 3/20/25.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#if __has_include(<BackgroundAssets/BackgroundAssets.h>)
#import <BackgroundAssets/BackgroundAssets.h>

/// An application extension that uses the system implementation to schedule Apple-hosted asset-pack downloads automatically.
///
/// You can optionally implement the inherited `BAManagedDownloaderExtension` requirements, but don’t implement any of the inherited `BADownloaderExtension` requirements. For more information, see <doc://com.apple.documentation/documentation/backgroundassets>.
API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@protocol SKDownloaderExtension <BAManagedDownloaderExtension>

@end
#endif
