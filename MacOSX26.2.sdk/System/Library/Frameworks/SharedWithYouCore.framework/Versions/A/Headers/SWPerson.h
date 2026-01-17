#import <TargetConditionals.h>
#if !TARGET_OS_TV
//
//  SWPerson.h
//  SocialLayer
//
//  Created by Andrew Whitehead on 1/31/22.
//

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class SWPersonIdentity;

API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWPerson : NSObject <NSSecureCoding>

/*!
    @abstract An initializer
    @param handle The phone number or email address for this person.
    @param identity The identity of this person.
    @param displayName The name of this person.
    @param thumbnailImageData Optional thumbnail image data for this person. If nil, this will be inferred by the system.
 */
- (instancetype)initWithHandle:(nullable NSString *)handle identity:(nullable SWPersonIdentity *)identity displayName:(NSString *)displayName thumbnailImageData:(nullable NSData *)thumbnailImageData;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
