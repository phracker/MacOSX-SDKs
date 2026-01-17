//
//  DCAppAttestService.h
//  DeviceCheck
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//


#import <DeviceCheck/DeviceCheck.h>

#if TARGET_OS_IOS || TARGET_OS_OSX

NS_ASSUME_NONNULL_BEGIN

DC_EXPORT
API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface DCAppAttestService : NSObject

/**
 * The shared service instance
 */
@property (class, readonly) DCAppAttestService *sharedService;

/**
 * Check if this API is supported on the current device for this application instance
 */
@property (getter=isSupported, readonly) BOOL supported;

/**
 * Generate a new unattested key.  This call generates a new
 * key every time.  the key identifier keyId is returned.
 *
 * @param completionHandler
 *        The key identifier (KeyId) for the newly generated unattested key upon success, or an error
 */
- (void)generateKeyWithCompletionHandler:(void (^)(NSString * _Nullable keyId, NSError * _Nullable error))completionHandler;

/**
 * Attest the key by keyId.  The same key may be attested more than once, provided that the key has
 * not been used for generating assertions.
 *
 * @param keyId
 *        The key identifier to be attested
 * @param clientDataHash
 *        An arbitrary byte (up to 32 bytes) to be supplied by caller.  It will be used to compute a nonce to be embedded into the certificate that certifies the key.
 * @param completionHandler
 *        The completion callback, returning the attestationObject upon success, or an error
 */
- (void)attestKey:(NSString *)keyId clientDataHash:(NSData *)clientDataHash completionHandler:(void (^)(NSData * _Nullable attestationObject, NSError * _Nullable error))completionHandler;

/**
 * Attest the key by keyId.  The same key may be attested more than once, provided that the key has
 * not been used for generating assertions.
 *
 * @param keyId
 *        The key identifier to the key to generate assertions with
 * @param clientDataHash
 *        An arbitrary byte (up to 32 bytes) to be supplied by caller.  It will be used to compute a nonce to be embedded into the certificate that certifies the key.
 * @param completionHandler
 *        The completion callback, returning the assertionObject upon success, or an error
 */
- (void)generateAssertion:(NSString *)keyId clientDataHash:(NSData *)clientDataHash completionHandler:(void (^)(NSData * _Nullable assertionObject, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END


#endif // TARGET_OS_IOS || TARGET_OS_OSX
