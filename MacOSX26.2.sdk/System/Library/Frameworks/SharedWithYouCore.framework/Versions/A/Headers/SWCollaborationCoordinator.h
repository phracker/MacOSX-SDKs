#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWCollaborationActionHandler.h>
#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYouCore/SWAction.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationCoordinator : NSObject

@property (class, nonatomic, strong, readonly) SWCollaborationCoordinator *sharedCoordinator;
@property (nonatomic, weak, readwrite) id<SWCollaborationActionHandler> actionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
