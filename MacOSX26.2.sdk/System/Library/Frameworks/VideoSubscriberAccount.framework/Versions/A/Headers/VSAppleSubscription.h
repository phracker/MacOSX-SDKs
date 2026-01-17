//
//  VSAppleSubscription.h
//  VideoSubscriberAccountFramework
//
//  Created by Joao on 11/6/23.
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

VS_EXPORT API_AVAILABLE(ios(17.4), tvos(17.4), macos(14.4), visionos(1.1)) API_UNAVAILABLE(watchos, macCatalyst)
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_SENDABLE
    @interface VSAppleSubscription : NSObject

// The identifier of the customer as previously reported to Apple.
@property (nonatomic, strong) NSString *customerID;

// List of product codes for Apple services the customer is subscribed to.
@property (nonatomic, strong) NSArray<NSString *> *productCodes;

- (instancetype)initWithCustomerID:(NSString *)customerID productCodes:(NSArray<NSString *> *)productCodes;

// Use - initWithCustomerID: productCodes: instead.
VS_INIT_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
