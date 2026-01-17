//
//  ARCollaborationData.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ARKit/ARSession.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A value describing the priority of the collaboration data.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARCollaborationDataPriority) {
    
    /// The data is important for establishing or continuing a collaborative session. For best results, use network transmission mechanisms that ensure delivery, such as MCSessionSendDataModeReliable.
    ARCollaborationDataPriorityCritical,
    
    /// The data is time-sensitive but not important to collaborative session quality. Timely synchronization of this data between participants produces a smoother shared session, but the session can continue if the data is not received.
    /// For best results, use network transmission mechanisms that prioritize speed over delivery guarantees, such as MCSessionSendDataModeUnreliable.
    ARCollaborationDataPriorityOptional,
} NS_SWIFT_NAME(ARCollaborationData.Priority);

/**
 Object representing data for collaborative session.
 
 @discussion This data needs to be sent to each participants in the collaborative session.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_NAME(ARSession.CollaborationData)
@interface ARCollaborationData : NSObject <NSSecureCoding>

/**
 Network priority of the data.
 @discussion The network implementation should respect this flag and choose the appropriate protocol.
 */
@property (nonatomic, readonly) ARCollaborationDataPriority priority;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
