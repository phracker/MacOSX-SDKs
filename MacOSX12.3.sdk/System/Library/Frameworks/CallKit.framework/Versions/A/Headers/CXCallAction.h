//
//  CXCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, tvos, watchos)
@interface CXCallAction : CXAction

@property (nonatomic, readonly, copy) NSUUID *callUUID;

- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
