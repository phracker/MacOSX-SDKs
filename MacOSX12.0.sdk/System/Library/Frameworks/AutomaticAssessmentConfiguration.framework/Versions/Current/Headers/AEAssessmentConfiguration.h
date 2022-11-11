//
//  AEAssessmentConfiguration.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <AutomaticAssessmentConfiguration/AEVisibility.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AEAssessmentApplication;
@class AEAssessmentParticipantConfiguration;

API_AVAILABLE(ios(13.4), macos(10.15.4), macCatalyst(14.0))
@interface AEAssessmentConfiguration: NSObject <NSCopying>

API_AVAILABLE(ios(14.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef NS_OPTIONS(NSUInteger, AEAutocorrectMode) {
    AEAutocorrectModeNone = 0,
    AEAutocorrectModeSpelling = 1 << 0,
    AEAutocorrectModePunctuation = 1 << 1,
} NS_SWIFT_NAME(AEAssessmentConfiguration.AutocorrectMode);
                   
@property (nonatomic, assign) AEAutocorrectMode autocorrectMode API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

@property (nonatomic, assign) BOOL allowsSpellCheck API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);
@property (nonatomic, assign) BOOL allowsPredictiveKeyboard API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);
@property (nonatomic, assign) BOOL allowsKeyboardShortcuts API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);
@property (nonatomic, assign) BOOL allowsActivityContinuation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);
@property (nonatomic, assign) BOOL allowsDictation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);
@property (nonatomic, assign) BOOL allowsAccessibilitySpeech API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);
@property (nonatomic, assign) BOOL allowsPasswordAutoFill API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);
@property (nonatomic, assign) BOOL allowsContinuousPathKeyboard API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

@property (nonatomic, strong, readonly) AEAssessmentParticipantConfiguration *mainParticipantConfiguration API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);
@property (nonatomic, copy, readonly) NSDictionary<AEAssessmentApplication *, AEAssessmentParticipantConfiguration *> *configurationsByApplication API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);

- (void)setConfiguration:(AEAssessmentParticipantConfiguration *)configuration forApplication:(AEAssessmentApplication *)application API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);
- (void)removeApplication:(AEAssessmentApplication *)application API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END
