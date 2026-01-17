//
//  HKScoredAssessment.h
//  HealthKit
//
//  Copyright © 2023-2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKScoredAssessment
 @abstract      An abstract HKSample subclass representing the results of a scored assessment.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKScoredAssessment : HKSample <NSSecureCoding, NSCopying>

/// The score determined by the answers on an assessment
@property (nonatomic, assign, readonly) NSInteger score;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
