//
//  AEAssessmentParticipantConfiguration.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(12.0))
API_UNAVAILABLE(visionos)
@interface AEAssessmentParticipantConfiguration : NSObject <NSCopying>

@property (nonatomic, assign) BOOL allowsNetworkAccess API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));
@property (nonatomic, assign, getter=isRequired) BOOL required API_AVAILABLE(ios(26.0), macCatalyst(26.0), macos(26.0)) API_UNAVAILABLE(visionos);

@property (nonatomic, copy) NSDictionary<NSString *, id> *configurationInfo API_AVAILABLE(ios(18.0), macCatalyst(18.0), macos(15.0));

- (instancetype)init API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));
+ (instancetype)new API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

@end

NS_ASSUME_NONNULL_END
