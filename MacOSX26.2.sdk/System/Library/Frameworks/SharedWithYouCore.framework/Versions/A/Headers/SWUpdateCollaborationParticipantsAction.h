#import <TargetConditionals.h>
#if !TARGET_OS_TV
//
//  SWUpdateCollaborationParticipantsAction.h
//  SharedWithYouCore
//
//  Created by Devin Clary on 3/23/22.
//

#import <Foundation/Foundation.h>

#import <SharedWithYouCore/SWAction.h>
#import <SharedWithYouCore/SWCollaborationMetadata.h>
#import <SharedWithYouCore/SWPersonIdentity.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWUpdateCollaborationParticipantsAction : SWAction <NSSecureCoding, NSCopying>

@property (nonatomic, readonly) SWCollaborationMetadata *collaborationMetadata;

@property (nonatomic, readonly) NSArray<SWPersonIdentity *> *addedIdentities;

@property (nonatomic, readonly) NSArray<SWPersonIdentity *> *removedIdentities;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
