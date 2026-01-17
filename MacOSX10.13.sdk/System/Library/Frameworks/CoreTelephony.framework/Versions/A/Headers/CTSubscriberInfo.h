/*
 *  CTSubscriberInfo.h
 *  CFTelephony
 *
 *  Copyright 2012 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

#import "CTSubscriber.h"

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(6_0)
@interface CTSubscriberInfo : NSObject

+ (CTSubscriber*) subscriber;

@end

NS_ASSUME_NONNULL_END
