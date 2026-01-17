//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYouCore/SWAction.h>

@class SWCollaborationCoordinator;
@class SWStartCollaborationAction;
@class SWUpdateCollaborationParticipantsAction;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), macos(13.0))
@protocol SWCollaborationActionHandler <NSObject>
- (void)collaborationCoordinator:(SWCollaborationCoordinator *)coordinator handleStartCollaborationAction:(SWStartCollaborationAction *)action;
- (void)collaborationCoordinator:(SWCollaborationCoordinator *)coordinator handleUpdateCollaborationParticipantsAction:(SWUpdateCollaborationParticipantsAction *)action;
@end

NS_ASSUME_NONNULL_END
