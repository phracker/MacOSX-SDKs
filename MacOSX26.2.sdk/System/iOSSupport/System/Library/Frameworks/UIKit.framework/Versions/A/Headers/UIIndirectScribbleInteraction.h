#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIIndirectScribbleInteraction.h>)
//
//  UIIndirectScribbleInteraction.h
//  UIKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <UIKit/UIInteraction.h>
#import <UIKit/UITextInput.h>

@protocol UIIndirectScribbleInteractionDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
    @abstract An interaction that allows using Scribble to enter text by handwriting on a view that is not formally a text input. Use UIIndirectScribbleInteraction if your app has a view that looks to the user as a text input but does not implement UITextInput. It makes the view act as a container of one or more virtual "Text Input Elements", each of which defines an area the user can write into without having to tap first.
    Some examples of when UIIndirectScribbleInteraction can be used:
      - A view that looks like a search field or a text field that in reality is a button, but installs a real text field when tapped
      - A view that contains multiple virtual text fields which the user can normally tap and type into, but are not full blown text fields all the time
 */
UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@interface UIIndirectScribbleInteraction : NSObject <UIInteraction>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithDelegate:(id<UIIndirectScribbleInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/*!
    @abstract The delegate for the interaction, to supply and customize writable elements in the interaction's view.
 */
@property (nonatomic, weak, nullable, readonly) id<UIIndirectScribbleInteractionDelegate> delegate;

/*!
    @abstract: Indicates if the user is actively writing. It will be set to YES in between calls to -indirectScribbleInteraction:willBeginWritingInElement: and -indirectScribbleInteraction:didFinishWritingInElement: calls.
*/
@property (nonatomic, readonly, getter=isHandlingWriting) BOOL handlingWriting;

@end

/*!
    @abstract Element identifiers are used to identify writable elements in the interaction's view, and will be supplied in every delegate callback. Any object that conforms to NSCopying and that can be compared for equality can be used. It is recommended to use simple immutable values, like NSString, NSNumber, or NSUUID.
 */
typedef id<NSCopying, NSObject> UIScribbleElementIdentifier NS_REFINED_FOR_SWIFT API_UNAVAILABLE(watchos); 

/*!
    @abstract The protocol to be implemented by the delegate of UIIndirectScribbleInteraction. It will be responsible for supplying a list of writable elements, focusing them, and ultimately providing a real UITextInput that will handle text editing operations.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(visionos) NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@protocol UIIndirectScribbleInteractionDelegate <NSObject>

/*!
    @abstract This method will be called to request the text input elements in a certain rect of the view, each of which represents an area where the user can start writing even if it's not a text input field itself.
    @param interaction The interaction asking for the elements.
    @param rect The rect around the area where the user is trying to write, in the interaction's view coordinate system. Only elements intersecting this rect should be returned.
    @param completion  You must call the completion handler, synchronously or asynchronously, with an array of identifiers of the available elements, or an empty array if no elements are available.
 */
- (void)indirectScribbleInteraction:(UIIndirectScribbleInteraction *)interaction requestElementsInRect:(CGRect)rect completion:(void(^)(NSArray<UIScribbleElementIdentifier> *elements))completion;

/*!
    @abstract Asks the delegate if an element is currently focused, according to the internal state of the interaction's view.
    @param interaction The interaction asking for the focused state.
    @param elementIdentifier The identifier of the element the interaction is asking about.
    @return Return YES if the element is the one currently focused.
 */
- (BOOL)indirectScribbleInteraction:(UIIndirectScribbleInteraction *)interaction isElementFocused:(UIScribbleElementIdentifier)elementIdentifier;

/*!
    @abstract Asks the delegate to provide the frame of an element.
    @param interaction The interaction asking for the element's frame.
    @param elementIdentifier The identifier of the element the interaction is asking about.
    @return Frame for the element, in the interactions's view coordinate system.
 */
- (CGRect)indirectScribbleInteraction:(UIIndirectScribbleInteraction *)interaction frameForElement:(UIScribbleElementIdentifier)elementIdentifier;

/*!
    @abstract Asks the delegate to focus an element to handle text edits. In response, it should make the element the currently focused one, and make the corresponding UITextInput become first responder.
    If the element was not focused already, text selection should be set to the character location closest to focusReferencePoint, to avoid any scrolling or shifting of content.
    If the element was focused already, no changes in selection should be made and this call can be ignored, but you must still call the completion handler with a reference to the text input.
    @param interaction The interaction that is requesting to focus an element.
    @param elementIdentifier The identifier of the element that should be focused.
    @param completion You must always call the completion handler, either synchronously or asynchronously. On success, the first parameter should be the text input that became first responder and that will handle text operations for this element. On failure, call the completion with a nil parameter.
*/
 - (void)indirectScribbleInteraction:(UIIndirectScribbleInteraction *)interaction focusElementIfNeeded:(UIScribbleElementIdentifier)elementIdentifier referencePoint:(CGPoint)focusReferencePoint completion:(void(^)(UIResponder<UITextInput> * _Nullable focusedInput))completion;

@optional

/*!
    @abstract Allow the delegate to delay focusing an element. Normally, Scribble will focus the element as soon as the user begins writing, but if you return YES from this callback, it will wait until the user makes a brief pause. This is useful in cases where the element's frame will shift or transform when becoming focused, which can be disruptive to a user trying to handwrite into it.
    Wherever possible it is preferable to adjust the UI behavior to avoid the layout changes, and only use delayed focus as a last resort, since transcription will happen all at once instead of incrementally.
    @param interaction The interaction asking about delaying focus.
    @param elementIdentifier The identifier of the element the interaction is asking about.
    @return Return YES to delay focusing the element.
 */
- (BOOL)indirectScribbleInteraction:(UIIndirectScribbleInteraction *)interaction shouldDelayFocusForElement:(UIScribbleElementIdentifier)elementIdentifier;

/*!
    @abstract Will be called when the user begins writing into an element. This call will always be paired with a corresponding call to indirectScribbleInteraction:didFinishWritingInElement:. It is recommended to use this call to hide custom placeholders or other UI elements that can interfere with writing.
    @param interaction The interaction notifying about writing state changes.
    @param elementIdentifier The identifier of the element the user is writing into.
 */
- (void)indirectScribbleInteraction:(UIIndirectScribbleInteraction *)interaction willBeginWritingInElement:(UIScribbleElementIdentifier)elementIdentifier;

/*!
    @abstract Will be called when the user finished writing into an element, after the last word has been transcribed and committed.
    @param interaction The interaction notifying about writing state changes.
    @param elementIdentifier The identifier of the element the user finished writing into.
*/
- (void)indirectScribbleInteraction:(UIIndirectScribbleInteraction *)interaction didFinishWritingInElement:(UIScribbleElementIdentifier)elementIdentifier;
@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIIndirectScribbleInteraction.h>
#endif
