#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYouCore/SWCollaborationMetadata.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationMetadata (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>

@end

NS_ASSUME_NONNULL_END

SW_EXTERN NSString * const SWCollaborationMetadataTypeIdentifier API_AVAILABLE(ios(16.0), macos(13.0));

#endif // !TARGET_OS_TV
