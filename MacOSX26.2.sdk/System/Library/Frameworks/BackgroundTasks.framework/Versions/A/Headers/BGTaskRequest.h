//
//  BGTaskRequest.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BackgroundTasks/BGDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An abstract class that represents a request for the app to be launched in the background to perform work.
/// Do not instantiate instances of this class directly. Instead, use one of its concrete subclasses.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface BGTaskRequest : NSObject <NSCopying>

/// The identifier of the task associated with the request.
@property (readonly, copy) NSString *identifier;

/// The earliest date and time at which to run the task.
///
/// Specify `nil` for no start delay.
///
/// Setting the property indicates that the background task shouldn’t start any
/// earlier than this date. However, the system doesn’t guarantee launching the
/// task at the specified date, but only that it won’t begin sooner.
@property (copy, nullable) NSDate *earliestBeginDate;

- (instancetype)init NS_UNAVAILABLE; // This is an abstract type and should not be directly instantiated
+ (instancetype)new NS_UNAVAILABLE; // This is an abstract type and should not be directly instantiated
@end

#pragma mark -

/// A request to launch your app in the background to execute a short refresh task.
///
/// Schedule a refresh task request to ask that the system launch your app briefly so that you can download data and
/// keep your app's contents up-to-date. The system will fulfill this request intelligently based on system conditions
/// and app usage.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface BGAppRefreshTaskRequest : BGTaskRequest

/// Return a new refresh task request for the specified identifier.
///
/// - Parameters:
///     - identifier: The string identifier of the refresh task associated with the request.
- (instancetype)initWithIdentifier:(NSString *)identifier;

@end

#pragma mark -

/// A request to launch your app in the background to execute a processing task that can take minutes to complete.
///
/// Schedule a processing task request to ask that the system launch your app when conditions are favorable for battery
/// life to handle deferrable, longer-running processing, such as syncing, database maintenance, or similar tasks. The
/// system will attempt to fulfill this request to the best of its ability within the next two days as long as the user
/// has used your app within the past week.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface BGProcessingTaskRequest : BGTaskRequest

/// Return a new processing task request for the specified identifier.
///
/// - Parameters:
///     - identifier: The string identifier of the processing task associated with the request.
- (instancetype)initWithIdentifier:(NSString *)identifier;

/// A Boolean specifying if the processing task requires network connectivity.
///
/// If this property is set to YES, the system will only launch your app to fulfill this request when the device has a
/// network connection. If this is set to NO, your app may not have network access.
/// - Note: The default value is `NO`.
@property (assign) BOOL requiresNetworkConnectivity;

/// Whether the background task represented by this request should only be done while the device is connected to
/// external power.
///
/// If this property is set to `YES`, the system will launch your app to fulfill this request only while the device is
/// connected to external power. Setting this to `YES` will also disable the CPU Monitor feature. Specify `YES` if this
/// task is resource intensive to minimize impact to battery life. Please note that, even if this value is `NO`, the
/// system will not necessarily schedule this task while the device is on battery power, depending on the type of
/// device and system conditions.
/// - Note: The default value is `NO`.
@property (assign) BOOL requiresExternalPower;

@end

#pragma mark -

/// A request to launch your app in the background to execute a health research task for studies a user has opted into
/// and that can take minutes to complete.
BG_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface BGHealthResearchTaskRequest : BGProcessingTaskRequest

/// A String indicating file protection availability required for processing.
///
/// Update this property to indicate what type of data needs to be accessible when the task is run. The default value
/// is `NSFileProtectionCompleteUntilFirstUserAuthentication`
@property (assign) NSFileProtectionType protectionTypeOfRequiredData;

@end

#pragma mark -

typedef NS_ENUM(NSInteger, BGContinuedProcessingTaskRequestSubmissionStrategy) {
    /// Fail the submission if there is no room for the task request, or if the system is under substantial load and is
    /// unable immediately run the task.
    BGContinuedProcessingTaskRequestSubmissionStrategyFail,
    /// Add the request to the back of a queue if there is no room for the submitted task or if the system is under
    /// substantial load and is unable to immediately run the task. Queued ``BGContinuedProcessingTaskRequest``s will be
    /// cancelled when the user removes your app from the app switcher.
    BGContinuedProcessingTaskRequestSubmissionStrategyQueue
} NS_SWIFT_NAME(BGContinuedProcessingTaskRequest.SubmissionStrategy) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, visionos, watchos, macCatalyst);

typedef NS_OPTIONS(NSInteger, BGContinuedProcessingTaskRequestResources) {
    /// No special system resources required.
    ///
    /// Unless informed otherwise, the scheduler assumes the default resources, allowing background CPU and network
    /// access.
    BGContinuedProcessingTaskRequestResourcesDefault = 0,
    /// Indicate to the scheduler that the workload will require background GPU utilization.
    ///
    /// Task submissions will be rejected if the submitting app does not have the correct entitlement. Background GPU
    /// execution is not supported on all devices. Additionally, if a device is experiencing heavy GPU contention
    /// backgrounded workloads are not guaranteed runtime.
    ///
    /// - Important: Applications must have the `com.apple.developer.background-tasks.continued-processing.gpu`  entitlement to submit a task request with this resource.
    BGContinuedProcessingTaskRequestResourcesGPU NS_SWIFT_NAME(gpu) = (1 << 0),
} NS_SWIFT_NAME(BGContinuedProcessingTaskRequest.Resources) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, visionos, watchos, macCatalyst);

#pragma mark -

/// A request to begin a workload immediately, or shortly after submission, which is allowed to continue running even if
/// the app is backgrounded.
BG_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, visionos, watchos, macCatalyst)
@interface BGContinuedProcessingTaskRequest : BGTaskRequest

/// The localized title displayed to the user.
@property (copy, nonnull) NSString *title;

/// The localized subtitle displayed to the user.
@property (copy, nonnull) NSString *subtitle;

/// The submission strategy for the scheduler to abide by.
///
/// Defaults to ``BGContinuedProcessingTaskRequestSubmissionStrategy/BGContinuedProcessingTaskRequestSubmissionStrategyQueue``.
@property (nonatomic) BGContinuedProcessingTaskRequestSubmissionStrategy strategy;

/// Inform the scheduler that the task will be requesting additional system resources.
///
/// Defaults to ``BGContinuedProcessingTaskRequestResources/BGContinuedProcessingTaskRequestResourcesDefault``.
@property (nonatomic) BGContinuedProcessingTaskRequestResources requiredResources;

/// Creates an instance on behalf of the currently foregrounded app.
///
/// Apps and their extensions should use this method to initialize any tasks due to the underlying association to the
/// currently foregrounded app. Please note that ``BGTaskRequest/earliestBeginDate`` will be outright ignored by the
/// scheduler in favor of `NSDate.now`.
///
/// The identifier ought to use wildcard notation, where the prefix of the identifier must at least contain the bundle
/// ID of the submitting application, followed by optional semantic context, and finally ending with `.*`. An example:
/// `<MainBundle>.<SemanticContext>.*` which would transform to `com.foo.MyApplication.continuedProcessingTask.*`. Thus,
/// a submitted identifier would be of the form `com.foo.MyApplication.continuedProcessingTask.HD830D`.
///
/// - Parameters:
///   - identifier: The task identifier.
///   - title: The localized title displayed to the user before the task begins running.
///   - subtitle: The localized subtitle displayed to the user before the task begins running.
/// - Warning: Successful creation of this object does not guarantee successful submission to the scheduler.
- (instancetype)initWithIdentifier:(NSString *)identifier
                             title:(NSString *)title
                          subtitle:(NSString *)subtitle;

@end

NS_ASSUME_NONNULL_END
