#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <SharedWithYouCore/SWAction.h>
#import <SharedWithYouCore/SWCollaborationMetadata.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWStartCollaborationAction : SWAction <NSSecureCoding, NSCopying>

@property (nonatomic, readonly) SWCollaborationMetadata *collaborationMetadata;

- (void)fulfillUsingURL:(NSURL *)url collaborationIdentifier:(SWCollaborationIdentifier)collaborationIdentifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
