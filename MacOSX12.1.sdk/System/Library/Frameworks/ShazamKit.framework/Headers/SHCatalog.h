//
//  SHCatalog.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief An abstract base class for storing signatures
///
/// @discussion You should not create instances of this class directly, instead use subclasses to provide the
/// functionality that you need
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHCatalog : NSObject

/// @brief The minimum @c SHSignature duration that can be used to perform searches against this Catalog
///
/// @discussion A @c SHSignature that contains less than the minimum duration in seconds will be discarded without matching.
/// @note A @c SHSignature under this duration does not have enough entropy to provide accurate matches.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) NSTimeInterval minimumQuerySignatureDuration;

/// @brief The maximum @c SHSignature duration that can be used to perform searches against this Catalog
///
/// @discussion A @c SHSignature over this duration will be rejected without matching. A well scoped @c SHSignature
/// is more likely to provide accurate matches.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) NSTimeInterval maximumQuerySignatureDuration;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
