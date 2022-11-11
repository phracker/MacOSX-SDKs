//
//  INSearchForNotebookItemsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

#import <Intents/INSortType.h>

@class INNote;
@class INTask;
@class INTaskList;

typedef NS_ENUM(NSInteger, INSearchForNotebookItemsIntentResponseCode) {
    INSearchForNotebookItemsIntentResponseCodeUnspecified = 0,
    INSearchForNotebookItemsIntentResponseCodeReady,
    INSearchForNotebookItemsIntentResponseCodeInProgress,
    INSearchForNotebookItemsIntentResponseCodeSuccess,
    INSearchForNotebookItemsIntentResponseCodeFailure,
    INSearchForNotebookItemsIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INSearchForNotebookItemsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForNotebookItemsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForNotebookItemsIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INNote *> *notes;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INTaskList *> *taskLists;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INTask *> *tasks;

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INSortType sortType;

@end

NS_ASSUME_NONNULL_END
