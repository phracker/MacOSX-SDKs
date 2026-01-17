//
//  AEAssessmentSession.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <AutomaticAssessmentConfiguration/AEVisibility.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AEAssessmentConfiguration;
@protocol AEAssessmentSessionDelegate;

API_AVAILABLE(ios(13.4), macos(10.15.4), macCatalyst(14))
@interface AEAssessmentSession : NSObject

@property (nonatomic, weak, nullable) id<AEAssessmentSessionDelegate> delegate;
@property (nonatomic, assign, readonly, getter=isActive) BOOL active;

- (instancetype)initWithConfiguration:(AEAssessmentConfiguration *)configuration;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (void)begin;
- (void)end;

@end

NS_ASSUME_NONNULL_END
