//
//  INUIHostedViewSiriProviding.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos, tvos)
@protocol INUIHostedViewSiriProviding <NSObject>

@optional

@property (nonatomic, assign, readonly) BOOL displaysMap;
@property (nonatomic, assign, readonly) BOOL displaysMessage;
@property (nonatomic, assign, readonly) BOOL displaysPaymentTransaction;

@end

NS_ASSUME_NONNULL_END

