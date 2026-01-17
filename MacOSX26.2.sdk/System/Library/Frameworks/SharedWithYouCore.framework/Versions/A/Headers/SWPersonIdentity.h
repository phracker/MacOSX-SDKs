#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
     @class SWPersonIdentity
     @abstract Represents an opaque Merkle tree where the root hash of the tree can uniquely identify the individual by all of their devices. The individual's devices can prove themselves to be part of this identity, and can then be used for cryptographic signatures for that individual.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
NS_SWIFT_NAME(SWPerson.Identity)
SW_EXTERN @interface SWPersonIdentity : NSObject <NSSecureCoding, NSCopying>

/*!
    @abstract The root hash of the tree that represents this individual's identity.
    @discussion The data contains a SHA256 hash of the user's combined public identities.
*/
@property (nonatomic, readonly, copy) NSData *rootHash;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @abstract An initializer
    @param rootHash The root hash of the tree that represents this individual's identity.
    @discussion The data contains a SHA256 hash of the user's combined public identities.
 */
- (instancetype)initWithRootHash:(NSData *)rootHash;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
