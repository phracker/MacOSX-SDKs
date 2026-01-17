//
//  AEErrors.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <AutomaticAssessmentConfiguration/AEVisibility.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AE_VISIBLE NSErrorDomain const AEAssessmentErrorDomain API_AVAILABLE(ios(13.4), macos(10.15.4), macCatalyst(14.0)) API_UNAVAILABLE(visionos);

API_AVAILABLE(ios(13.4), macos(10.15.4), macCatalyst(14.0))
API_UNAVAILABLE(visionos)
typedef NS_ERROR_ENUM(AEAssessmentErrorDomain, AEAssessmentErrorCode) {
    AEAssessmentErrorUnknown = 1,
    AEAssessmentErrorUnsupportedPlatform API_AVAILABLE(ios(16.0), macos(13.0), macCatalyst(16.0)) = 2,
    AEAssessmentErrorMultipleParticipantsNotSupported API_AVAILABLE(ios(17.5), macos(14.5), macCatalyst(17.5)) = 3,
    AEAssessmentErrorConfigurationUpdatesNotSupported API_AVAILABLE(ios(17.5), macos(14.5), macCatalyst(17.5)) = 4,
    AEAssessmentErrorRequiredParticipantsNotAvailable API_AVAILABLE(ios(26.0), macCatalyst(26.0), macos(26.0)) = 5
};

AE_VISIBLE NSString * AENotInstalledParticipantsKey NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0), macCatalyst(26.0), macos(26.0)) API_UNAVAILABLE(visionos);
AE_VISIBLE NSString * AERestrictedSystemParticipantsKey NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0), macCatalyst(26.0), macos(26.0)) API_UNAVAILABLE(visionos);

NS_ASSUME_NONNULL_END
