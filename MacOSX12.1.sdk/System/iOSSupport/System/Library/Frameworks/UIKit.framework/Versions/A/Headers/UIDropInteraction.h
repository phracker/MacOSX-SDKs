#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDropInteraction.h>)
//
//  UIDropInteraction.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIInteraction.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIDragAnimating, UIDropInteractionDelegate, UIDropSession;
@class UIDragItem, UITargetedDragPreview;


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIDropInteraction : NSObject <UIInteraction>

- (instancetype)initWithDelegate:(id<UIDropInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, nullable, readonly, weak) id<UIDropInteractionDelegate> delegate;

/* Whether to allow this interaction to handle more than one drop session
 * at the same time. A well-behaved delegate can handle this correctly,
 * but many will find it challenging, so the default value is false.
 * If false, then after one session has entered the view, other sessions will
 * be ignored until the first session exits and the other session enters again.
 */
@property (nonatomic, assign) BOOL allowsSimultaneousDropSessions;

@end


/* The UIDropInteraction's delegate uses a UIDropOperation to tell the system
 * what operation it will perform if the user drops.
 */
typedef NS_ENUM(NSUInteger, UIDropOperation) {
    /* Operations that do NOT cause data transfer.
     *
     * If the user drops here, the UIDropInteraction's -dropInteraction:performDrop:
     * method will NOT be called.
     */

    /* The drag will be cancelled.
     */
    UIDropOperationCancel   = 0,

    /* The drag will be cancelled.
     * Use this operation to signal that this interaction would *normally* perform
     * a different operation, but that it explicitly forbids a drop at this specific
     * time and place.
     * This may cause a special symbol to be displayed on the drag image.
     */
    UIDropOperationForbidden = 1,

    /* Operations that cause data transfer.
     *
     * If the user drops here, the UIDropInteraction's -dropInteraction:performDrop:
     * method will be called.
     */

    /* The data represented by the drag item(s) will be copied.
     * This is the most common operation to use.
     */
    UIDropOperationCopy      = 2,

    /* The data represented by the drag item(s) will be moved.
     *
     * You may use this only if UIDropSession's allowsMoveOperation is true.
     * Otherwise it will be treated as UIDropOperationCancel.
     *
     * Note that the system does not give any special meaning to this operation.
     * The delegates of both the UIDragInteraction and UIDropInteraction must
     * cooperate to produce the correct result. For instance, the UIDropInteraction's
     * delegate might insert the data in the new location, and the UIDragInteraction's
     * delegate might remove the data from the old location.
     */
    UIDropOperationMove      = 3,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIDropProposal : NSObject <NSCopying>

- (instancetype)initWithDropOperation:(UIDropOperation)operation NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/* The operation that this interaction proposes to perform.
 */
@property (nonatomic, readonly) UIDropOperation operation;

/* Set `precise` to true to specify that this drop interaction wants to handle the drop
 * in a precise way, e.g. dropping into text. The drag system may move the drag point
 * away from the touch in order to make it easier to hit a small target.
 */
@property (nonatomic, getter=isPrecise) BOOL precise;

/* Signals that this drop interaction wants the preview to be shown
 * at its full original size, not scaled smaller, while this proposal is in effect.
 * For instance, you might set this to true if the items are being moved from some
 * other nearby view, and scaling them smaller would be distracting.
 * This only applies to drags that started in the same app.
 */
@property (nonatomic) BOOL prefersFullSizePreview;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIDropInteractionDelegate <NSObject>

@optional

/* Return whether the delegate is interested in the given session.
 * If this method is not implemented, or if it returns true, then the
 * other delegate methods will be called, starting with `-dropInteraction:sessionDidEnter:`.
 * If it returns false, this interaction will ignore this session. (We may ask again
 * if something significant about the session changes, like the items in it.)
 *
 * Note that returning true does not mean that the delegate definitely *will* accept this drop,
 * just that it *might* want to accept the drop.
 * To accept it, you must also implement `-dropInteraction:sessionDidUpdate:` and return a
 * UIDropProposal with an appropriate operation.
 *
 * This method is commonly used to check whether the session contains any
 * items that this delegate can consume. Use `UIDropSession`'s convenience methods
 * `-hasItemsConformingToTypeIdentifiers:`, `-canLoadObjectsOfClass:`, etc.
 */
- (BOOL)dropInteraction:(UIDropInteraction *)interaction canHandleSession:(id<UIDropSession>)session;

/* Called when a drag enters the view.
 */
- (void)dropInteraction:(UIDropInteraction *)interaction sessionDidEnter:(id<UIDropSession>)session;

/* Called when the drag enters the interaction's view, or when when the drag 
 * moves while inside the view, or if items are added to the drag while inside the view.
 *
 * You *must* implement this method to accept a drop.
 * Return a `UIDropProposal` that contains the operation that the delegate
 * would like to perform. (Note that you may use `UIDropOperationMove` only if
 * session.allowsMoveOperation is true.)
 *
 * You may also set other properties on the `UIDropProposal` to change the appearance
 * of the drag over this view.
 *
 * Use the session's `-locationInView:` to get a point to use for hit testing.
 */
- (UIDropProposal *)dropInteraction:(UIDropInteraction *)interaction sessionDidUpdate:(id<UIDropSession>)session;

/* Called when the drag has exited the interaction's view.
 */
- (void)dropInteraction:(UIDropInteraction *)interaction sessionDidExit:(id<UIDropSession>)session;

/* Called when the user drops onto this interaction's view.
 * The delegate should now request data from the session's
 * items' item providers. Data may be requested *only* during
 * the scope of this method.
 */
- (void)dropInteraction:(UIDropInteraction *)interaction performDrop:(id<UIDropSession>)session;

/* Called when the user has dropped onto this interaction's view,
 * after `-dropInteraction:performDrop:` has been called,
 * and all resulting drop animations have completed.
 *
 * The delegate should cause the interaction's view to draw in its final post-drop state.
 */
- (void)dropInteraction:(UIDropInteraction *)interaction concludeDrop:(id<UIDropSession>)session;

/* When the drag session ends, for any reason, this method will be called
 * for *every* interaction that ever received `-dropInteraction:sessionDidEnter:`,
 * `-dropInteraction:sessionDidUpdate:`, or `-dropInteraction:sessionDidExit:`.
 *
 * If you were keeping track of the session for any reason, you may now forget it.
 */
- (void)dropInteraction:(UIDropInteraction *)interaction sessionDidEnd:(id<UIDropSession>)session;

/* Drop animation. */

/* Called when the drop happens, after `-dropInteraction:performDrop:`, once for each visible item.
 * Provide a preview to animate the item to where it belongs.
 * We provide `defaultPreview` which would leave the current preview where the item was dropped.
 * You may return:
 * - defaultPreview, to use it as-is
 * - nil, to fade and shrink the drag item in place
 * - [defaultPreview retargetedPreviewWithTarget:] to move the preview to a different target
 * - a UITargetedDragPreview that you create however you like
 */
- (nullable UITargetedDragPreview *)dropInteraction:(UIDropInteraction *)interaction previewForDroppingItem:(UIDragItem *)item withDefault:(UITargetedDragPreview *)defaultPreview;

/* Called when the drop animation is about to start, once for each item,
 * whether it is visible or not.
 * Use the animator to animate your own changes alongside the system animation.
 */
- (void)dropInteraction:(UIDropInteraction *)interaction item:(UIDragItem *)item willAnimateDropWithAnimator:(id<UIDragAnimating>)animator;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDropInteraction.h>
#endif
