#import <TargetConditionals.h>
#if !TARGET_OS_TV
//
//  SWRemoveParticipantAlertController.h
//  SWRemoveParticipantAlertController
//
//  Copyright (c) 2022 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYouCore/SWPerson.h>

@class SWCollaborationHighlight;
@class SWPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0))
SW_EXTERN @interface SWRemoveParticipantAlertController : UIViewController

+ (instancetype)alertControllerWithParticipant:(SWPerson *)participant highlight:(SWCollaborationHighlight *)highlight;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
