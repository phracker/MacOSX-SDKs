#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIUpdateActionPhase.h>)
//
//  UIUpdateActionPhase.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Each UI update consists of several phases which run in order, one after another. There are two phase groups - normal
/// and low-latency. Normal phase group consists of phases from `EventDispatch` to `CATransactionCommit`. Low-latency
/// phase group consists of phases from `LowLatencyEventDispatch` to `LowLatencyCATransactionCommit`. When phase group
/// runs, all phases inside the group run. Phases run one after another in the specified order without exiting back into
/// the run loop. Spinning a nested run loop inside any of the phases is not supported. For each UI update, normal phase
/// group always runs. Low-latency phase group is optional and is off by default. It will run only when application
/// explicitly requests low-latency event delivery. Be aware that handling low-level events is extremely demanding and
/// only well profiled and optimized applications can benefit from it. Applications that were not designed to handle
/// low-latency events will most likely drop frames. Also not all event types are eligible for low-latency event
/// delivery. Currently only pencil events are low-latency eligible. This practically means that only pencil drawing
/// and writing applications should request it.
/// It's acceptable to block main thread in any of the phases to wait for things that are absolutely required to
/// proceed. When done properly, this will donate main thread priority to the thread being waited for, making it more
/// likely to get those things in time and meet the completion deadline. Of course, extreme caution should be exercised
/// when doing so - maximum wait time should have a hard limit on it that still allows to complete the remaining part
/// of the UI update before completion deadline. Use of `-[CAMetalLayer nextDrawable]` is of a particular note - it's
/// not advised to use it on the main thread of the UI application as it might block main thread for one or more frames.
/// Instead, consider calling `-[CAMetalLayer nextDrawable]` on the background thread and block main thread manually
/// in one of the phases. Use small timeout that allows for UI update to proceed without a new drawable and still finish
/// before the completion deadline.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, macCatalyst)
@interface UIUpdateActionPhase: NSObject

+(instancetype)new NS_UNAVAILABLE;
-(instancetype)init NS_UNAVAILABLE;

/// Phase that runs after UI update was scheduled and its timing information is know. This is a good place for things
/// that only rely on UI update timing and don't need user input events. Running at this stage allows to utilize time
/// that otherwise would be wasted waiting for user input events to arrive. Purely time driven client side animations or
/// non-interactive simulations should go here.
@property(class, nonatomic, readonly) UIUpdateActionPhase *afterUpdateScheduled;

/// Before `UIEvent` and `UIGestureRecognizer` handlers run. Use this phase to prepare resources and data structures
/// required to process user input events.
@property(class, nonatomic, readonly) UIUpdateActionPhase *beforeEventDispatch;

/// After `UIEvent` and `UIGestureRecognizer` handlers run. Past this point, there will be no new user input events sent
/// to the application. If low-latency event delivery was requested, more events might be dispatched in
/// `LowLatencyEventDispatch` phase. Use this phase to react on application state after processing all user input events
/// for the UI update, like starting a parallel rendering thread. Also, if your application uses extrapolation to smooth
/// out low-rate event stream, use this phase to detect that certain events were not received to extrapolate them.
@property(class, nonatomic, readonly) UIUpdateActionPhase *afterEventDispatch;

/// Before `CADisplayLink` callbacks run.
@property(class, nonatomic, readonly) UIUpdateActionPhase *beforeCADisplayLinkDispatch;

/// After `CADisplayLink` callbacks run.
@property(class, nonatomic, readonly) UIUpdateActionPhase *afterCADisplayLinkDispatch;

/// Before `CATransaction` is flushed.
@property(class, nonatomic, readonly) UIUpdateActionPhase *beforeCATransactionCommit;

/// After `CATransaction` is flushed. Any changes to CoreAnimation layer tree made here (or later) will not appear on
/// screen with the current UI update (they will go on screen with the next UI update). There are few exceptions to
/// this rule however:
/// - It's still possible to `+[CATransaction commit]` or `+[CATransaction flush]` manually which will send latest
///   CoreAnimation layer changes to render server immediately. Doing so is not recommended as in addition to intended
///   changes other potentially unrelated changes might be sent to the render server prematurely.
/// - If low-latency event dispatch will be performed, then all CoreAnimation layer tree changes that done before
///   or during `LowLatencyCATransactionCommit` phase will appear on screen with this UI update.
@property(class, nonatomic, readonly) UIUpdateActionPhase *afterCATransactionCommit;

/// Before `UIEvent` and `UIGestureRecognizer` handlers run for low-latency eligible events. This stage is
/// off by default (skipped) and must be requested explicitly.
@property(class, nonatomic, readonly) UIUpdateActionPhase *beforeLowLatencyEventDispatch;

/// After `UIEvent` and `UIGestureRecognizer` handlers run for low-latency eligible events. This stage is
/// off by default (skipped) and must be requested explicitly.
@property(class, nonatomic, readonly) UIUpdateActionPhase *afterLowLatencyEventDispatch;

/// Before `CATransaction` is flushed. Only runs when low-latency event dispatch was requested.
@property(class, nonatomic, readonly) UIUpdateActionPhase *beforeLowLatencyCATransactionCommit;

/// After `CATransaction` is flushed. Only runs when low-latency event dispatch was requested. Any changes to
/// CoreAnimation layer tree made here (or later) will not appear on screen with the current UI update.
@property(class, nonatomic, readonly) UIUpdateActionPhase *afterLowLatencyCATransactionCommit;

/// The very end of the UI update. If there's still time until `completionDeadlineTime`, it's generally safe to do any
/// idle opportunistic work here, like the one that was deferred from more time critical parts of the UI update. It's
/// also a good place to record last presented state, for things like on-screen velocity computations.
@property(class, nonatomic, readonly) UIUpdateActionPhase *afterUpdateComplete;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIUpdateActionPhase.h>
#endif
