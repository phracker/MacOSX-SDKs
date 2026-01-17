#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextDropping.h>)
//
//  UITextDropping.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UITextDropProposal.h>
#import <UIKit/UITextPasteConfigurationSupporting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIDropInteraction;
@protocol UITextDropDelegate;

/* Defines a text droppable control.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UITextDroppable <UITextInput, UITextPasteConfigurationSupporting>

@property (nonatomic, weak, nullable) id<UITextDropDelegate> textDropDelegate;

/* The text drop interaction that UIKit installs on the text control.
 * Use this to explicitly disable drop interactions on system text controls,
 * if desired.
 */
@property (nonatomic, readonly, nullable) UIDropInteraction *textDropInteraction;

/* Returns whether this control currently has at least one active drag session.
 */
@property (nonatomic, readonly, getter=isTextDropActive) BOOL textDropActive;

@end


typedef NS_ENUM(NSUInteger, UITextDropEditability) {
    /* A non-editable control will remain non-editable and
     * the drop will not be allowed.
     */
    UITextDropEditabilityNo = 0,

    /* A non-editable control will become editable for the drop
     * only, but will be restored to non-editable afterwards.
     */
    UITextDropEditabilityTemporary,

    /* A non-editable control will become editable and remain
     * editable after the drop concludes.
     */
    UITextDropEditabilityYes,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);


@protocol UITextDropRequest;


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UITextDropDelegate <NSObject>

@optional

/* By default, when the text control is not editable, drops will not occur.
 * However, there might be scenarios where dropping into a non-editable text control
 * is desirable.
 * If not implemented, uses UITextDropEditabilityNo.
 */
- (UITextDropEditability)textDroppableView:(UIView<UITextDroppable> *)textDroppableView willBecomeEditableForDrop:(id<UITextDropRequest>)drop;

/* Defines whether a text control can accept a drag.
 * Return a UITextDropProposal here to change the drag behavior.
 * This will get called:
 * - when the drag enters the text control,
 * - when the *text position* changes while the drag moves over the text control
 * - when the drag session changes (e.g. items were added)
 *
 * Note: this is called frequently, so try to do minimal work.
 */
- (UITextDropProposal*)textDroppableView:(UIView<UITextDroppable> *)textDroppableView proposalForDrop:(id<UITextDropRequest>)drop;

/* Indicates that the drop is about to be performed.
 * To modify the result of the items to be dropped, provide a pasteHandler on
 * the text control, which will handle the conversion and pasting of the text.
 */
- (void)textDroppableView:(UIView<UITextDroppable> *)textDroppableView willPerformDrop:(id<UITextDropRequest>)drop;

/* Provide a custom preview for dropping text into the text control.
 *
 * Only one preview is used, regardless of the number of items being dropped.
 * Becase we're animating into one range of text, there is no need for individual
 * previews.
 *
 * The defaultPreview is the preview that the control would normally use
 * to animate the drop. It is based on the (ordered) combination of text
 * representations for each item. (See UITextPasteDelegate to customize it.)
 * It resembles the text that will be inserted into the view.
 *
 * If any of the items have not finished loading, this will be an animation into the
 * location of the caret when the drop was being performed.
 *
 * Return nil to use the default preview of the underlying drop interaction.
 */
- (nullable UITargetedDragPreview *)textDroppableView:(UIView<UITextDroppable> *)textDroppableView previewForDroppingAllItemsWithDefault:(UITargetedDragPreview *)defaultPreview;

/* Called when a drag has entered the text view.
 */
- (void)textDroppableView:(UIView<UITextDroppable> *)textDroppableView dropSessionDidEnter:(id<UIDropSession>)session;

/* Called when the drag has updated. This is often, but not always, preceded by a call
 * to -textDroppableView:proposalForDrop:.
 *
 * Note: this is called *very* frequently, so try to do minimal work.
 */
- (void)textDroppableView:(UIView<UITextDroppable> *)textDroppableView dropSessionDidUpdate:(id<UIDropSession>)session;

/* Called when the drag has left the view.
 */
- (void)textDroppableView:(UIView<UITextDroppable> *)textDroppableView dropSessionDidExit:(id<UIDropSession>)session;

/* Called when the drag has ended.
 */
- (void)textDroppableView:(UIView<UITextDroppable> *)textDroppableView dropSessionDidEnd:(id<UIDropSession>)session;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UITextDropRequest <NSObject>

/* The text position that the drag is over.
 */
@property (nonatomic, readonly) UITextPosition *dropPosition;

/* The suggested proposal by the text control.
 */
@property (nonatomic, readonly) UITextDropProposal *suggestedProposal;

/* Returns whether the drop is a local drop
 * (that is, the drag and drop are in the same text control).
 */
@property (nonatomic, readonly, getter=isSameView) BOOL sameView;

/* The current drop session. Use this to get the location of the
 * session in the view, for example.
 */
@property (nonatomic, readonly) id<UIDropSession> dropSession;

@end


NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITextDropping.h>
#endif
