//
//  CXSetGroupCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), macos(11.0))  API_UNAVAILABLE(watchos, tvos)
@interface CXSetGroupCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID callUUIDToGroupWith:(nullable NSUUID *)callUUIDToGroupWith NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

/// The UUID of another call to group with.
///
/// - If the call for this action's UUID is already in a group, it should leave that group if necessary.
/// - If nil, leave any group the call is currently in.
@property (nonatomic, copy, nullable) NSUUID *callUUIDToGroupWith;

@end

NS_ASSUME_NONNULL_END
