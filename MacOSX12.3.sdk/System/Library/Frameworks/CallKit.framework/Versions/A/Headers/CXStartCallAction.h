//
//  CXStartCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

@class CXHandle;

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, tvos, watchos)
@interface CXStartCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID handle:(CXHandle *)handle NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

/// Handle for the party to call
@property (nonatomic, copy) CXHandle *handle;

@property (nonatomic, copy, nullable) NSString *contactIdentifier;

@property (nonatomic, getter=isVideo) BOOL video;

/// Normally, providers can just call -[CXAction fulfill] to indicate action fulfillment. Use this method to note a specific date that the call started if it is different from [NSDate date]. A call is considered started when its invitation has been sent to the remote callee.
- (void)fulfillWithDateStarted:(NSDate *)dateStarted;

@end

NS_ASSUME_NONNULL_END
