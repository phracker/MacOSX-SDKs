#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScribbleInteraction.h>)
//
//  UIScribbleInteraction.h
//  UIKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <UIKit/UIInteraction.h>
#import <UIKit/UITextInput.h>

@protocol UIScribbleInteractionDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
    @abstract An interaction that allows customizing the behavior of Scribble on text input views, or suppress it entirely in specific cases.
    By default, Scribble allows the user to enter text by handwriting directly into any view that implements UITextInput and is editable. In apps with customized text fields, you can use UIScribbleInteraction's delegate callbacks to optimize the UI for a better writing experience. For example, you might want to hide custom placeholders when writing begins, or request delaying focusing the field if it moves when gaining focus.
    In some cases it is necessary to suppress Scribble, for example if a text view also supports drawing with Apple Pencil. You may also need to suppress Scribble in views that handle Pencil events directly, like a drawing canvas, since nearby text fields could take over the Pencil events for writing.
 */
UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIScribbleInteraction : NSObject <UIInteraction>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithDelegate:(id<UIScribbleInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/*!
    @abstract The delegate for the interaction, specified on init.
 */
@property (nonatomic, weak, nullable, readonly) id<UIScribbleInteractionDelegate> delegate;

/*!
    @abstract: Indicates if the user is actively writing. It will be set to YES in between calls to scribbleInteractionWillBeginWriting: and scribbleInteractionDidFinishWriting:
*/
@property (nonatomic, readonly, getter=isHandlingWriting) BOOL handlingWriting;

/*!
    @abstract A readonly class property that indicates the user is likely to use Apple Pencil and Scribble to enter text instead of the keyboard. In this case it is recommended to adjust the layout of UI elements that are not optimal for direct handwriting input. For example, small or resizable text fields that expect more than a few words could be made taller and reserve some whitespace at the bottom.
 */
@property (nonatomic, readonly, class, getter=isPencilInputExpected) BOOL pencilInputExpected;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(visionos) NS_SWIFT_UI_ACTOR
@protocol UIScribbleInteractionDelegate <NSObject>

@optional
 
/*!
    @abstract Allows the delegate to prevent Scribble from starting at a specific location in the view. If not implemented, defaults to YES.
    You can use this callback to temporarily suppress Scribble in text input views if your app supports drawing over text or other special interaction when using Apple Pencil. In cases like this, it's recommended to provide a UI affordance for the user to toggle between drawing and handwriting.
    This callback can also return NO for views that handle Pencil events directly, like a drawing canvas, since nearby text fields could take over the Pencil events for writing.
    @param interaction The interaction asking if it can begin handling user input.
    @param location The location in the interaction's view coordinate system.
    @return Return NO to disallow writing at the specified location.
 */
- (BOOL)scribbleInteraction:(UIScribbleInteraction *)interaction shouldBeginAtLocation:(CGPoint)location NS_SWIFT_NAME(scribbleInteraction(_:shouldBeginAt:));

/*!
    @abstract Allow the delegate to delay focusing (making first responder) the text input view. Normally, Scribble will focus the target input as soon as the user begins writing, but if you return YES from this callback, it will wait until the user makes a brief pause. This is useful in cases where the text input view will shift or transform when becoming first responder, which can be disruptive to a user trying to handwrite into it.
    Wherever possible it is preferable to adjust the UI behavior to avoid the layout changes, and only use delayed focus as a last resort, since transcription will happen all at once instead of incrementally.
    @param interaction The interaction asking about delaying focus.
    @return Return YES to delay focusing the text input.
 */
- (BOOL)scribbleInteractionShouldDelayFocus:(UIScribbleInteraction *)interaction;

/*!
    @abstract Will be called when the user begins writing into the interaction's view. This call will always be paired with a corresponding call to scribbleInteractionDidFinishWriting:. It is recommended to use this call to hide custom placeholders or other UI elements that can interfere with writing.
    @param interaction The interaction notifying about writing state changes.
 */
- (void)scribbleInteractionWillBeginWriting:(UIScribbleInteraction *)interaction;

/*!
    @abstract Will be called when the user finished writing into the interaction's view, after the last word has been transcribed and committed.
    @param interaction The interaction notifying about writing state changes.
*/
- (void)scribbleInteractionDidFinishWriting:(UIScribbleInteraction *)interaction;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIScribbleInteraction.h>
#endif
