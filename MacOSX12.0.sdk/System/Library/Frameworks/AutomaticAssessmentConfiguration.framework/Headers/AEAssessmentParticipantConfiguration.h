//
//  AEAssessmentParticipantConfiguration.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(12.0))
@interface AEAssessmentParticipantConfiguration : NSObject <NSCopying>

@property (nonatomic, assign) BOOL allowsNetworkAccess API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);

- (instancetype)init API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);
+ (instancetype)new API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END
