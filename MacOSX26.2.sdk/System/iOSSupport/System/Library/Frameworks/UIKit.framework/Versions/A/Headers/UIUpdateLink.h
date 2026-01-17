#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIUpdateLink.h>)
//
//  UIUpdateLink.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKitDefines.h>

@class UIUpdateInfo;
@class UIUpdateActionPhase;
@class UIWindowScene;
@class UIView;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Allows to formally participate in UI updates and influence UI update behavior.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, macCatalyst)
@interface UIUpdateLink: NSObject

+(instancetype)new NS_UNAVAILABLE;
-(instancetype)init NS_UNAVAILABLE;

+(UIUpdateLink *)updateLinkForWindowScene:(UIWindowScene *)windowScene NS_SWIFT_NAME(init(windowScene:));
+(UIUpdateLink *)updateLinkForView:(UIView *)view NS_SWIFT_NAME(init(view:));

-(void)addActionToPhase:(UIUpdateActionPhase *)phase
                handler:(void(^)(UIUpdateLink *updateLink, UIUpdateInfo *updateInfo))handler NS_SWIFT_NAME(addAction(to:handler:));
-(void)addActionToPhase:(UIUpdateActionPhase *)phase
                 target:(id)target selector:(SEL)selector NS_SWIFT_NAME(addAction(to:target:selector:));

/// It's required to enable the Update Link for it to have effect and for its actions to be invoked.
@property(nonatomic, getter=isEnabled) BOOL enabled;

/// By default, `UIUpdateLink` is a passive UI update observer. Its actions will only be called when UI update is being
/// produced. When this property is set to `YES`, `UIUpdateLink` will request continuous UI updates by itself.
@property(nonatomic) BOOL requiresContinuousUpdates;

/// Request dispatch of low-latency eligible events in `LowLatencyEventDispatch` phase. Low latency eligible events are
/// dispatch in the middle of the UI update, meaning that to handle them application has half the time, compared to
/// events dispatched normally. Consult `-[UIUpdateInfo completionDeadlineTime]` for exact completion deadline time.
@property(nonatomic) BOOL wantsLowLatencyEventDispatch;

/// Request immediate frame presentation. When enabled, system will request immediate rendering of the display frame
/// after last `CATransaction` commit for the current UI update. This allows to reduce input to display latency, as
/// rendered display frame will be presented one frame duration sooner. However, for this to happen amount of work
/// submitted to render server should be minimal, otherwise it will not be able to submit frame for presentation in
/// time. This capability is primarily useful for pencil drawing applications where low input to display latency is
/// critical for good user experience. Applications that request immediate presentation must be profiled thoroughly to
/// ensure that amount of application and render server work is adequate. When application requests immediate
/// presentation, but fails to keep work complexity at minimum, user will experience on screen judder, as frames will
/// not be presented at their intended time.
@property(nonatomic) BOOL wantsImmediatePresentation;

/// Preferred frame rate range. Even when not forcing periodic updates, this will still express intention to the system.
/// Use `CAFrameRateRangeDefault` (default value) to not request any specific frame rate range.
@property(nonatomic) CAFrameRateRange preferredFrameRateRange;

/// During UI update, returns `UIUpdateInfo` instance describing current UI update state. Returns `nil` outside of UI
/// update.
-(nullable UIUpdateInfo *)currentUpdateInfo;

@end

@interface UIUpdateLink(Convenience)

/// Adds action to `UIUpdateActionPhase.beforeCADisplayLinkDispatch` phase.
-(void)addActionWithHandler:(void(^)(UIUpdateLink *updateLink, UIUpdateInfo *updateInfo))handler NS_SWIFT_NAME(addAction(handler:));
/// Adds action to `UIUpdateActionPhase.beforeCADisplayLinkDispatch` phase.
-(void)addActionWithTarget:(id)target selector:(SEL)selector NS_SWIFT_NAME(addAction(target:selector:));

/// Adds action to `UIUpdateActionPhase.beforeCADisplayLinkDispatch` phase.
+(UIUpdateLink *)updateLinkForWindowScene:(UIWindowScene *)windowScene
                            actionHandler:(void(^)(UIUpdateLink *updateLink, UIUpdateInfo *updateInfo))handler NS_SWIFT_NAME(init(windowScene:actionHandler:));
/// Adds action to `UIUpdateActionPhase.beforeCADisplayLinkDispatch` phase.
+(UIUpdateLink *)updateLinkForWindowScene:(UIWindowScene *)windowScene
                             actionTarget:(id)target selector:(SEL)selector NS_SWIFT_NAME(init(windowScene:actionTarget:selector:));

/// Adds action to `UIUpdateActionPhase.beforeCADisplayLinkDispatch` phase.
+(UIUpdateLink *)updateLinkForView:(UIView *)view
                     actionHandler:(void(^)(UIUpdateLink *updateLink, UIUpdateInfo *updateInfo))handler NS_SWIFT_NAME(init(view:actionHandler:));
/// Adds action to `UIUpdateActionPhase.beforeCADisplayLinkDispatch` phase.
+(UIUpdateLink *)updateLinkForView:(UIView *)view
                      actionTarget:(id)target selector:(SEL)selector NS_SWIFT_NAME(init(view:actionTarget:selector:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIUpdateLink.h>
#endif
