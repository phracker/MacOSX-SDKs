//
//  CXSetHeldCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), watchos(9.0))  API_UNAVAILABLE(macos, tvos)
@interface CXSetHeldCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID onHold:(BOOL)onHold NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

@property (nonatomic, getter=isOnHold) BOOL onHold;

@end

NS_ASSUME_NONNULL_END
