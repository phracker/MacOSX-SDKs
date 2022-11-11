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

API_AVAILABLE(ios(13.4), macos(10.15.4), macCatalyst(14.0))
@interface AEAssessmentSession : NSObject

@property (nonatomic, weak, nullable) id<AEAssessmentSessionDelegate> delegate;
@property (nonatomic, copy, readonly) AEAssessmentConfiguration *configuration API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(12.0));
@property (nonatomic, assign, readonly, getter=isActive) BOOL active;

- (instancetype)initWithConfiguration:(AEAssessmentConfiguration *)configuration;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (void)begin;
- (void)end;
- (void)updateToConfiguration:(AEAssessmentConfiguration *)configuration API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END
