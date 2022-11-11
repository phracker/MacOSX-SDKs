//
//  VSAccountManagerResult.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents an in-flight request to an account manger.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(macCatalyst)
@interface VSAccountManagerResult : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// Advise the account manager that the app no longer needs the requested work to be done.
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
