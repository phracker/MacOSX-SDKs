// Copyright © 2020 Apple Inc. All rights reserved.

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
typedef NSInteger ASCOSEAlgorithmIdentifier NS_TYPED_EXTENSIBLE_ENUM;

/*! @abstract The COSE algorithm identifier representing ECDSA with SHA-256.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
static ASCOSEAlgorithmIdentifier const ASCOSEAlgorithmIdentifierES256 = -7;

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
typedef NSInteger ASCOSEEllipticCurveIdentifier NS_TYPED_EXTENSIBLE_ENUM;

/*! @abstract The COSE curve identifier representing the P-256 elliptic curve.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
static ASCOSEEllipticCurveIdentifier const ASCOSEEllipticCurveIdentifierP256 = 1;
