#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
     @class SWPersonIdentityProof
     @abstract Represents an opaque Merkle tree proof of inclusion. Inclusion hashes are provided to verify that the individual device has access to the document.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
NS_SWIFT_NAME(SWPerson.IdentityProof)
SW_EXTERN @interface SWPersonIdentityProof : NSObject <NSSecureCoding, NSCopying>

/*!
    @abstract Hashes of missing Merkle tree nodes that can provide proof of inclusion.
    @discussion The data contains an array of SHA256 hash of the user's combined public identities.
*/
@property (nonatomic, readonly, copy) NSArray<NSData *> *inclusionHashes;

/*!
    @abstract Public key of local device
*/
@property (nonatomic, readonly, copy) NSData *publicKey;

/*!
    @abstract Index of local public key in the Merkle tree
    @discussion This data can be used to determine if the node is the left or the right child
*/
@property (nonatomic, readonly, assign) NSUInteger publicKeyIndex;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(16.0), macos(13.0))
NS_SWIFT_NAME(SWPerson.SignedIdentityProof)
SW_EXTERN @interface SWSignedPersonIdentityProof : SWPersonIdentityProof

- (instancetype)initWithPersonIdentityProof:(SWPersonIdentityProof *)personIdentityProof signatureData:(NSData *)data;

/*!
    @abstract The signature created by signing the data with this identity.
*/
@property (nonatomic, readonly, copy) NSData *signatureData;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
