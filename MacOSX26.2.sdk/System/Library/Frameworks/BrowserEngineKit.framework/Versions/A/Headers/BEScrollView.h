//
//  BEScrollView.h
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW

#import <UIKit/UIKit.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class BEScrollView, BEScrollViewScrollUpdate;


BROWSERENGINE_EXPORT API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol BEScrollViewDelegate <UIScrollViewDelegate>

@optional

// If implemented, scroll updates will be passed to this delegate method before being handled by
// the scroll view. The delegate may do some work, then must asynchronously call the completion block on the main queue.
// This method will be called multiple times, and the delegate must call the completions in order.
//
// Extract information from `scrollUpdate` immediately, since its properties may change later,
// and it's only safe to access on the main queue.
//
// Call the completion with `handled` = YES to indicate that you handled the scroll event and
// don't want BEScrollView to react to the scroll event.
// Pass `handled` = NO to have the event be handled in the normal way (just delayed).
- (void)scrollView:(BEScrollView *)scrollView handleScrollUpdate:(BEScrollViewScrollUpdate *)scrollUpdate completion:(void (^)(BOOL handled))completion;

// In order to implement CSS rendering, it may be necessary to make two scroll views siblings in the view tree that are nested in the DOM.
// This method may be used to specify that a sibling scroll view should be considered the parent of another, for the purpose of gesture interaction and scroll transfer.
// The parent is expected to be earlier in an in-order traversal of the view tree, since a parent would normally be visually underneath its child.
// Return nil for the default behavior of traversing up the view tree to find a parent scroll view.
- (nullable BEScrollView *)parentScrollViewForScrollView:(BEScrollView *)scrollView;

@end


// A scroll view with features specific to browsers.
BROWSERENGINE_EXPORT API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface BEScrollView : UIScrollView

@property (nonatomic, weak, nullable) id<BEScrollViewDelegate> delegate;

@end


// Phases of a BEScrollViewScrollUpdate.
typedef NS_ENUM(NSInteger, BEScrollViewScrollUpdatePhase) {
    BEScrollViewScrollUpdatePhaseBegan,     // Whenever a gesture scroll has physically started.
    BEScrollViewScrollUpdatePhaseChanged,   // Whenever a gesture scroll has changed.
    BEScrollViewScrollUpdatePhaseEnded,     // Whenever a gesture scroll physically ends.
    BEScrollViewScrollUpdatePhaseCancelled, // Whenever a gesture scroll doesn't end but the system stops tracking.
} NS_SWIFT_NAME(BEScrollViewScrollUpdate.Phase) API_AVAILABLE(ios(17.4));


// An update from a scroll view issued during a scroll event (e.g. trackpad or mouse wheel) or deceleration after a scroll event.
BROWSERENGINE_EXPORT API_AVAILABLE(ios(17.4)) NS_SWIFT_UI_ACTOR
@interface BEScrollViewScrollUpdate : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// The time when the update occurred, in seconds since system startup.
@property (nonatomic, readonly) NSTimeInterval timestamp;

// The phase of the update.
@property (nonatomic, readonly) BEScrollViewScrollUpdatePhase phase;

// The location of the pointer where the scroll occurred in the coordinate space of the specified view. Specify nil to indicate the window.
- (CGPoint)locationInView:(nullable UIView *)view;

// The scroll delta in the coordinate space of the specified view. Specify nil to indicate the window.
- (CGPoint)translationInView:(nullable UIView *)view;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // BROWSERENGINEKIT_HAS_UIVIEW
