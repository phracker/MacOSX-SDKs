//
//  CXSetMutedCallAction.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, tvos, watchos)
@interface CXSetMutedCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID muted:(BOOL)muted NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

@property (nonatomic, getter=isMuted) BOOL muted;

@end

NS_ASSUME_NONNULL_END
