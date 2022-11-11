#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextPasteDelegate.h>)
//
//  UITextPasteDelegate.h
//  UIKit Framework
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UITextPasteConfigurationSupporting;
@protocol UITextPasteItem;

@class UITextRange;
@class NSTextAttachment;

/*
 * Defines a delegate to handle text paste handling through item providers.
 * UIKit will handle the state management for pasting several long during item providers
 * if necessary. While the pasting is ongoing, the state of the text control will not
 * be altered, and only at the end the resulting string will be pasted at the specified location.
 *
 * The location of the paste is referenced from the time the paste was initiated. If the
 * text changes in the mean time, this might not be at the same location as before.
 * If the old location is out of bounds of the new text, it will be clamped to the range of the
 * current state of the text when the paste actually occurs.
 *
 * The ranges passed to the 2 optional methods will reflect the actual correct range at the
 * time of actually pasting the resulting string.
 *
 * UITextView and UITextField do not have an explicit .pasteConfiguration set, but will
 * behave like they have one set implicitly depending on a few factors:
 *
 *  - if the view allows editing text attributes (.allowsEditingTextAttributes == YES),
 *    it accepts items that can be read as:
 *      - plain strings
 *      - attributed strings
 *      - images (but only for UITextView)
 *  - if the view does not allow editing text attributes (.allowsEditingTextAttributes == NO),
 *    it accepts items that can be read as:
 *      - plain strings
 *
 * If you modify your text control's pasteConfiguration, you should probably also use
 * this delegate to properly handle any custom items you have there.
 */

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UITextPasteDelegate <NSObject>

@optional

/*
 * Will be called for each item in the paste.
 * You *must* eventually call on of the result methods (`setFooResult:`
 * or `discardResult`) on the given UITextPasteItem.
 *
 * Note: It is not required to call these result methods in the
 * same scope as the transformPasteItem:. You can pass these on to any
 * async handling code (see: NSItemProvider), hold on to them through
 * a closure and/or invoke them in a completion block.
 *
 * Note: You can use this UITextPasteItem on any thread,
 * but textPasteConfigurationSupporting:transformPasteItem: will be called
 * on the main thread.
 */
- (void)textPasteConfigurationSupporting:(id<UITextPasteConfigurationSupporting>)textPasteConfigurationSupporting transformPasteItem:(id<UITextPasteItem>)item;

/*
 * When you want to alter how the different item strings are combined
 * into one string, you can implement this method.
 * By default, all strings will just be concatenated without any delimiters,
 * but you are free to do what you want here.
 * The target text range is provided so you can alter behavior here depending on
 * where the text will be dropped.
 */
- (NSAttributedString *)textPasteConfigurationSupporting:(id<UITextPasteConfigurationSupporting>)textPasteConfigurationSupporting combineItemAttributedStrings:(NSArray<NSAttributedString *> *)itemStrings forRange:(UITextRange*)textRange;

/*
 * Handle the pasting of the final string. This will be a combination of all pasted items.
 * It this is not implemented, the standard paste mechanism will be used.
 * The target range will be a zero length range for normal pastes, but might be
 * non-zero for text drops (see text drop API).
 * Please honor this range as doing something different here will be confusing
 * to the user.
 * Return the resulting text range from the method (or nil to indicate no changes to the range).
 * This might be used to select the range for text drops.
 */
- (UITextRange*)textPasteConfigurationSupporting:(id<UITextPasteConfigurationSupporting>)textPasteConfigurationSupporting performPasteOfAttributedString:(NSAttributedString*)attributedString toRange:(UITextRange*)textRange;

/* By default, the standard text controls will animate pasting or dropping text.
 * If you don't want this to happen for a certain paste or range, you can implement
 * this method and return false here.
 *
 * If you don't implement this, the default is true.
 */
- (BOOL)textPasteConfigurationSupporting:(id<UITextPasteConfigurationSupporting>)textPasteConfigurationSupporting shouldAnimatePasteOfAttributedString:(NSAttributedString*)attributedString toRange:(UITextRange*)textRange; // DEPRECATED IOS13

@end



UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UITextPasteItem <NSObject>

// This is the NSItemProvider for the item being pasted or dropped.
// You should set a result for this item using one of the methods below.
@property (nonatomic, readonly) __kindof NSItemProvider *itemProvider;

// This is nil for normal pastes, but might be filled with the
// UIDragItem's localObject for pastes from drops.
@property (nonatomic, readonly, nullable) id localObject;

// These will be the default attributes that will
// be applied to plain strings when they are provided.
// You can use these to make your own attributed string if you want.
@property (nonatomic, readonly) NSDictionary<NSAttributedStringKey, id> *defaultAttributes;

// provide a plain string representation result from this NSItemProvider's data
- (void)setStringResult:(NSString*)string;

// provide an attributed representation result from this NSItemProvider's data
- (void)setAttributedStringResult:(NSAttributedString*)string;

// provide an attachment result from this NSItemProvider's data
- (void)setAttachmentResult:(NSTextAttachment*)textAttachment;

// Use this to indicate that you don't want the data of this NSItemProvider
// included in the resulting string.
- (void)setNoResult;

// Use this to indicate that want the default transformation to happen.
// If the item data for the item provider is not supported, this action
// will be the same as `setNoResult`.
// You can use this as a fallback for any items you are not handling yourself.
- (void)setDefaultResult;

@end


NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITextPasteDelegate.h>
#endif
