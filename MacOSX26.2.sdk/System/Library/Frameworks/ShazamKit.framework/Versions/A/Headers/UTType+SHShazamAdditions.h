//
//  UTType+SHShazamAdditions.h
//  ShazamKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <ShazamKit/SHDefines.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

NS_HEADER_AUDIT_BEGIN(nullability)

SH_EXPORT API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0))
@interface UTType (SHShazamAdditions)

/// A type representing the @c SHSignature file format with the .shazamsignature extension
@property (NS_NONATOMIC_IOSONLY, strong, readonly, class) UTType *SHSignatureContentType  NS_REFINED_FOR_SWIFT;

/// A type representing the @c SHCustomCatalog file format with the .shazamcatalog extension
@property (NS_NONATOMIC_IOSONLY, strong, readonly, class) UTType *SHCustomCatalogContentType NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability)

