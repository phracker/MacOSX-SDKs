#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFindInteraction.h>)
//
//  UIFindInteraction.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIFindSession.h>
#import <UIKit/UIInteraction.h>

@class UIFindInteraction;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIFindInteractionDelegate <NSObject>

/// Called when a find session is requested to begin by the user. Return an instance of a UIFindSession implementation to allow the
/// find session to begin, otherwise return nil to prevent the system find panel from appearing.
- (nullable UIFindSession *)findInteraction:(UIFindInteraction *)interaction sessionForView:(UIView *)view;

@optional

/// Called when the search operation begins (and the system search UI appears).
/// This would be a good time to decorate your view to indicate that a search operation is about to occur.
/// System text elements will apply a dimming view around all non-highlighted search results, for instance.
- (void)findInteraction:(UIFindInteraction *)interaction didBeginFindSession:(UIFindSession *)session;

/// Called when the current search session has changed or ended. This would be a good time to remove all
/// decorations applied to found search results, and any decorations added when the search operation began
/// (such as a dimming view).
- (void)findInteraction:(UIFindInteraction *)interaction didEndFindSession:(UIFindSession *)session;

@end

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIFindInteraction : NSObject <UIInteraction>

/// Returns YES if the find navigator panel is currently visible.
@property (nonatomic, readonly, getter=isFindNavigatorVisible) BOOL findNavigatorVisible;

/// If there's a currently active find session (implying isFindNavigatorVisible is true), returns the active find session.
@property (nonatomic, readonly, nullable) UIFindSession *activeFindSession;

/// Assign this property to pre-populate the system find panel's search text field with a search query.
@property (nonatomic, copy, nullable) NSString *searchText;

/// If replacement is supported, assign this property to pre-populate the system find panel's replace text field with a replacement string.
@property (nonatomic, copy, nullable) NSString *replacementText;

/// This provider is consulted when the search options menu is being populated. A default set of search options is provided, representing the options
/// available in @c UITextSearchOptions, which can be either modified, augmented, or omitted.
@property (nonatomic, readwrite, copy, nullable) UIMenu *_Nullable (^optionsMenuProvider)(NSArray<UIMenuElement *> *defaultOptions);

/// See UIFindInteractionDelegate above.
@property (nonatomic, weak, readonly) id<UIFindInteractionDelegate> delegate;

/// Creates a find interaction object with the specified delegate.
- (instancetype)initWithSessionDelegate:(id<UIFindInteractionDelegate>)sessionDelegate NS_DESIGNATED_INITIALIZER;

/// Shows the find navigator panel, if not already visible.
///
/// @param replaceVisible If the delegate supports text replacement, will make the replace text field
///                       visible on first appearance.
- (void)presentFindNavigatorShowingReplace:(BOOL)showingReplace NS_SWIFT_NAME(presentFindNavigator(showingReplace:));

/// Dismisses the find navigator panel.
- (void)dismissFindNavigator;

/// Jump to the next found result in the document, relative to the currently highlighted result.
- (void)findNext;

/// Jump to the previous found result in the document, relative to the currently highlighted result.
- (void)findPrevious;

/// Calling this triggers an update of the UI to reflect changes to the currently shown result count or result index, as defined by UIFindSession. 
- (void)updateResultCount;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFindInteraction.h>
#endif
