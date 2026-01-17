// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

GK_EXTERN_WEAK NSString * __nonnull GKErrorDomain API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

typedef NS_ENUM(NSInteger, GKErrorCode) {
    GKErrorUnknown                              = 1,
    GKErrorCancelled                            = 2,
    GKErrorCommunicationsFailure                = 3,
    GKErrorUserDenied                           = 4,
    GKErrorInvalidCredentials                   = 5,
    GKErrorNotAuthenticated                     = 6,
    GKErrorAuthenticationInProgress             = 7,
    GKErrorInvalidPlayer                        = 8,
    GKErrorScoreNotSet                          = 9,
    GKErrorParentalControlsBlocked              = 10,
    GKErrorPlayerStatusExceedsMaximumLength     API_AVAILABLE(ios(4.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0)) = 11,
    GKErrorPlayerStatusInvalid                  API_AVAILABLE(ios(4.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0)) = 12,
    GKErrorMatchRequestInvalid                  = 13,
    GKErrorUnderage                             API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 14,
    GKErrorGameUnrecognized                     API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 15,
    GKErrorNotSupported                         API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 16,
    GKErrorInvalidParameter                     API_AVAILABLE(ios(4.2), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 17,
    GKErrorUnexpectedConnection                 API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 18,
    GKErrorChallengeInvalid                     API_DEPRECATED_WITH_REPLACEMENT("Replaced by developer defined challenges, see ``GKChallengeDefinition``", ios(6.0,26.0), macos(10.8,26.0), tvos(9.0,26.0), visionos(1.0,26.0), watchos(3.0,26.0)) = 19,
    GKErrorTurnBasedMatchDataTooLarge           API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 20,
    GKErrorTurnBasedTooManySessions             API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 21,
    GKErrorTurnBasedInvalidParticipant          API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 22,
    GKErrorTurnBasedInvalidTurn                 API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 23,
    GKErrorTurnBasedInvalidState                API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0)) = 24,
    GKErrorInvitationsDisabled                  API_AVAILABLE(ios(7.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0)) = 25,
    GKErrorPlayerPhotoFailure                   API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0)) = 26,
    GKErrorUbiquityContainerUnavailable         API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0)) = 27,
    GKErrorMatchNotConnected                    API_AVAILABLE(ios(10.0), macos(10.12), tvos(10.0), visionos(1.0), watchos(3.0)) = 28,
    GKErrorGameSessionRequestInvalid            API_AVAILABLE(ios(10.0), macos(10.12), tvos(10.0), visionos(1.0), watchos(3.0)) = 29,
    GKErrorRestrictedToAutomatch                API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), visionos(1.0), watchos(6.0)) = 30,
    GKErrorAPINotAvailable                      API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), visionos(1.0), watchos(6.0)) = 31,
    GKErrorNotAuthorized                        API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0), watchos(7.0)) = 32,
    GKErrorConnectionTimeout                    API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0), watchos(7.0)) = 33,
    GKErrorAPIObsolete                          API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0), watchos(7.0)) = 34,
    GKErrorICloudUnavailable                    API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1), watchos(10.2)) = 35,
    GKErrorLockdownMode                         API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1), watchos(10.2)) = 36,
    GKErrorAppUnlisted                          API_AVAILABLE(ios(17.4), macos(14.4), tvos(17.4), visionos(1.1), watchos(10.4)) = 37,
    GKErrorDebugMode                            API_AVAILABLE(ios(18.4), macos(15.4), tvos(18.4), visionos(2.4), watchos(11.4)) = 38,

    GKErrorFriendListDescriptionMissing         API_AVAILABLE(ios(14.5), macos(11.3), tvos(14.5), visionos(1.0), watchos(7.4)) = 100,
    GKErrorFriendListRestricted                 API_AVAILABLE(ios(14.5), macos(11.3), tvos(14.5), visionos(1.0), watchos(7.4)) = 101,
    GKErrorFriendListDenied                     API_AVAILABLE(ios(14.5), macos(11.3), tvos(14.5), visionos(1.0), watchos(7.4)) = 102,
    GKErrorFriendRequestNotAvailable            API_AVAILABLE(ios(15.0), macos(12.0), tvos(15.0), visionos(1.0), watchos(8.0)) = 103,
} API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));
