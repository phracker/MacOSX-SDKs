//
//  BAManagedError.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 4/14/25.
//

#import <BackgroundAssets/BackgroundAssets.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The error domain for managed asset packs.
BA_EXPORT NSErrorDomain const BAManagedErrorDomain API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/// The `-[NSError userInfo]` key for an asset pack’s identifier.
///
/// This key is relevant when the error code is ``BAManagedErrorCode/BAManagedErrorCodeAssetPackNotFound``.
BA_EXPORT NSErrorUserInfoKey const BAAssetPackIdentifierErrorKey API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/// An error code for a managed asset pack.
typedef NS_ENUM(NSInteger, BAManagedErrorCode) {
    
    /// An error code that indicates the system can’t find an asset pack with the given identifier.
    ///
    /// Refer to the value in `-[NSError userInfo]` for the key `BAAssetPackIdentifierErrorKey` for the asset pack’s identifier.
    BAManagedErrorCodeAssetPackNotFound,
    
    /// An error code that indicates the system can’t find a file at the specified path.
    ///
    /// Refer to the value in `-[NSError userInfo]` for the key `NSFilePathErrorKey` for the file path.
    BAManagedErrorCodeFileNotFound
    
} API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

NS_HEADER_AUDIT_END(nullability, sendability)
