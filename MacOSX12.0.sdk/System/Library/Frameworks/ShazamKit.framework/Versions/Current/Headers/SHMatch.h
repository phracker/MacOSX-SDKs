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

NS_ASSUME_NONNULL_BEGIN

/// @brief A @c SHMatch indicates that a Signature matched a reference Signature in the target @c SHCatalog
/// @discussion A @c SHSignature can match many reference Signatures in a catalog and in turn a Signature can map to
/// many @c SHMediaItem. Therefore a match encapsulates the query signature and all of the various @c SHMediaItem it matched
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHMatch : NSObject <NSSecureCoding>

/// @brief The @c SHMatchedMediaItem belonging to the instance of @c SHSignature that we matched
///
/// @discussion One signature may match multiple @c SHMediaItem, especially in the case of audio that uses samples. The @c SHMatchedMediaItem
/// are ordered by  the quality of the match. Use the first @c SHMediaItem if you intend to only show one result
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSArray<SHMatchedMediaItem *> *mediaItems;

/// The @c SHSignature used to search the @c SHCatalog
/// @note This is Signature is the query Signature, not the reference signature contained in the @c SHCatalog
@property (NS_NONATOMIC_IOSONLY, strong, readonly) SHSignature *querySignature;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
