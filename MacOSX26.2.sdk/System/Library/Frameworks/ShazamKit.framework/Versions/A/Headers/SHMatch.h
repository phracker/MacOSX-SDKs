//
//  SHMatch.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHSignature.h>
#import <ShazamKit/SHMatchedMediaItem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that represents the catalog media items that match a query.
///
/// A single query signature may match more than one reference signature. In addition, one reference signature may map to many media items.
SH_EXPORT NS_SWIFT_SENDABLE API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHMatch : NSObject <NSSecureCoding>

/// An array of the media items in the catalog that match the query signature, in order of the quality of the match.
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSArray<SHMatchedMediaItem *> *mediaItems;

/// The query signature for the match.
@property (NS_NONATOMIC_IOSONLY, strong, readonly) SHSignature *querySignature;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
