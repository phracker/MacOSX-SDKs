//
//  INDomainHandling.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntents.h>

#if !TARGET_OS_TV
#if !TARGET_OS_WATCH
API_DEPRECATED("Please conform to INStartAudioCallIntentHandling, INStartVideoCallIntentHandling and INSearchCallHistoryIntentHandling instead", ios(11.0, 13.0))
API_UNAVAILABLE(macos, tvos)
@protocol INCallsDomainHandling <INStartAudioCallIntentHandling, INStartVideoCallIntentHandling, INSearchCallHistoryIntentHandling>
@end
#else
API_DEPRECATED("Please conform to INStartAudioCallIntentHandling and INSearchCallHistoryIntentHandling instead", ios(10.0, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INCallsDomainHandling <INStartAudioCallIntentHandling, INSearchCallHistoryIntentHandling>
@end
#endif // !TARGET_OS_WATCH

API_DEPRECATED("Please conform to INActivateCarSignalIntentHandling, INSetCarLockStatusIntentHandling, INGetCarLockStatusIntentHandling and INGetCarPowerLevelStatusIntentHandling instead", ios(10.3, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INCarCommandsDomainHandling <INActivateCarSignalIntentHandling, INSetCarLockStatusIntentHandling, INGetCarLockStatusIntentHandling, INGetCarPowerLevelStatusIntentHandling>
@end

API_DEPRECATED("Please conform to INSetAudioSourceInCarIntentHandling, INSetClimateSettingsInCarIntentHandling, INSetDefrosterSettingsInCarIntentHandling, INSetSeatSettingsInCarIntentHandling, INSetProfileInCarIntentHandling and INSaveProfileInCarIntentHandling instead", ios(10.0, 13.0))
API_UNAVAILABLE(macos, watchos)
@protocol INCarPlayDomainHandling <INSetAudioSourceInCarIntentHandling, INSetClimateSettingsInCarIntentHandling, INSetDefrosterSettingsInCarIntentHandling, INSetSeatSettingsInCarIntentHandling, INSetProfileInCarIntentHandling, INSaveProfileInCarIntentHandling>
@end

API_DEPRECATED("Please conform to INStartWorkoutIntentHandling, INPauseWorkoutIntentHandling, INEndWorkoutIntentHandling, INCancelWorkoutIntentHandling and INResumeWorkoutIntentHandling instead", ios(10.0, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INWorkoutsDomainHandling <INStartWorkoutIntentHandling, INPauseWorkoutIntentHandling, INEndWorkoutIntentHandling, INCancelWorkoutIntentHandling, INResumeWorkoutIntentHandling>
@end

API_DEPRECATED("Please conform to INSetRadioStationIntentHandling instead", ios(10.0, 13.0))
API_UNAVAILABLE(macos, watchos, tvos)
@protocol INRadioDomainHandling <INSetRadioStationIntentHandling>
@end

#if !TARGET_OS_WATCH
API_DEPRECATED("Please conform to INSendMessageIntentHandling, INSearchForMessagesIntentHandling and INSetMessageAttributeIntentHandling instead", ios(10.0, 13.0)) API_UNAVAILABLE(macos)
@protocol INMessagesDomainHandling <INSendMessageIntentHandling, INSearchForMessagesIntentHandling, INSetMessageAttributeIntentHandling>
@end
#else
API_DEPRECATED("Please conform to INSendMessageIntentHandling and INSearchForMessagesIntentHandling instead", ios(10.0, 13.0), watchos(3.2, 6.0)) API_UNAVAILABLE(macos)
@protocol INMessagesDomainHandling <INSendMessageIntentHandling, INSearchForMessagesIntentHandling>
@end
#endif // !TARGET_OS_WATCH

#if (TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 110000) || TARGET_OS_OSX

API_DEPRECATED("Please conform to INSendPaymentIntentHandling, INRequestPaymentIntentHandling, INPayBillIntentHandling, INSearchForBillsIntentHandling, INSearchForAccountsIntentHandling and INTransferMoneyIntentHandling instead", ios(11.0, 13.0), watchos(4.0, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling, INPayBillIntentHandling, INSearchForBillsIntentHandling, INSearchForAccountsIntentHandling, INTransferMoneyIntentHandling>
@end

#elif TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 100300

API_DEPRECATED("Please conform to INSendPaymentIntentHandling, INRequestPaymentIntentHandling, INPayBillIntentHandling and INSearchForBillsIntentHandling instead", ios(10.3, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling, INPayBillIntentHandling, INSearchForBillsIntentHandling>
@end

#else

API_DEPRECATED("Please conform to INSendPaymentIntentHandling and INRequestPaymentIntentHandling instead", ios(10.0, 13.0))
API_UNAVAILABLE(macos, tvos)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling>
@end

#endif // (TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 110000) || TARGET_OS_OSX

API_DEPRECATED("Please conform to INSearchForPhotosIntentHandling and INStartPhotoPlaybackIntentHandling instead", ios(10.0, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos)
API_UNAVAILABLE(tvos)
@protocol INPhotosDomainHandling <INSearchForPhotosIntentHandling, INStartPhotoPlaybackIntentHandling>
@end

#if !TARGET_OS_WATCH
#if (TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 110000) || TARGET_OS_OSX

API_DEPRECATED("Please conform to INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling, INCancelRideIntentHandling and INSendRideFeedbackIntentHandling instead", ios(11.0, 13.0), watchos(4.0, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling, INCancelRideIntentHandling, INSendRideFeedbackIntentHandling>
@end

#else

API_DEPRECATED("Please conform to INListRideOptionsIntentHandling, INRequestRideIntentHandling and INGetRideStatusIntentHandling instead", ios(10.0, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling>
@end

#endif // (TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 110000) || TARGET_OS_OSX
#else
API_DEPRECATED("Please conform to INListRideOptionsIntentHandling, INRequestRideIntentHandling and INGetRideStatusIntentHandling instead", ios(10.0, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling>
@end
#endif // !TARGET_OS_WATCH

API_DEPRECATED("Please conform to INCreateNoteIntentHandling, INAppendToNoteIntentHandling, INAddTasksIntentHandling, INCreateTaskListIntentHandling, INSetTaskAttributeIntentHandling and INSearchForNotebookItemsIntentHandling instead", ios(11.0, 13.0), watchos(4.0, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INNotebookDomainHandling <INCreateNoteIntentHandling, INAppendToNoteIntentHandling, INAddTasksIntentHandling, INCreateTaskListIntentHandling, INSetTaskAttributeIntentHandling, INSearchForNotebookItemsIntentHandling>
@end

API_DEPRECATED("Please conform to INGetVisualCodeIntentHandling instead", ios(11.0, 13.0), watchos(4.0, 6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INVisualCodeDomainHandling <INGetVisualCodeIntentHandling>
@end

#endif // !TARGET_OS_TV
