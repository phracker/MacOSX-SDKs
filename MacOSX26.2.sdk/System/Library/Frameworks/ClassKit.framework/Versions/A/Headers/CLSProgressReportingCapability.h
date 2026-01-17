//
//  CLSProgressReportingCapability.h
//  ClassKit
//
//  Copyright © 2020-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClassKit/CLSObject.h>

/*!
 @enum       CLSProgressReportingCapabilityKind
 @constant   CLSProgressReportingCapabilityKindDuration     Reports time spent. By default all CLSContexts have this capability. See CLSActivity for more information.
 @constant   CLSProgressReportingCapabilityKindPercent      Reports progress percentage. See CLSActivity for more information.
 @constant   CLSProgressReportingCapabilityKindBinary       Reports a binary value like true/false, pass/fail, yes/no or correct/incorrect. See CLSBinaryItem for more information.
 @constant   CLSProgressReportingCapabilityKindQuantity     Reports a discrete value. See CLSQuantityItem for more information.
 @constant   CLSProgressReportingCapabilityKindScore        Reports a score. See CLSScoreItem for more information.
 */
typedef NS_ENUM(NSInteger, CLSProgressReportingCapabilityKind) {
    CLSProgressReportingCapabilityKindDuration = 0,
    CLSProgressReportingCapabilityKindPercent,
    CLSProgressReportingCapabilityKindBinary,
    CLSProgressReportingCapabilityKindQuantity,
    CLSProgressReportingCapabilityKindScore
} NS_SWIFT_NAME(CLSProgressReportingCapability.Kind) API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

NS_ASSUME_NONNULL_BEGIN

/*!
@abstract   This class specifies progress reporting capability of a ClassKit client app
 */
API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface CLSProgressReportingCapability : CLSObject

/*!
 @abstract      Returns the kind of progress reporting capability
 */
@property (nonatomic, assign, readonly) CLSProgressReportingCapabilityKind kind;

/*!
 @abstract      Returns progress reporting details
 */
@property (nullable, nonatomic, copy, readonly) NSString *details;

/*!
@abstract       Initialize and configure the type of progress reporting capability
 @param         kind        The kind of progress reporting capability
 @param         details     An optional localized string describing the capability. For example: "Reports percentage of progress", "Reports overall score". Schoolwork will use an appropriate default string if one is not provided.
 */
- (instancetype)initWithKind:(CLSProgressReportingCapabilityKind)kind details:(nullable NSString *)details;

@end

NS_ASSUME_NONNULL_END
