#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextSearching.h>)
//
//  UITextSearching.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UITextInput.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UITextSearchOptions;

typedef id<NSObject, NSCopying> UITextSearchDocumentIdentifier API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UITextSearchFoundTextStyle) {
    /// No style.
    UITextSearchFoundTextStyleNormal,
    
    /// "Found" style. Used to indicate matches that have been found, but not currently highlighted.
    UITextSearchFoundTextStyleFound,
    
    /// Highlighted style, used to indicate a match that is found and currently highlighted.
    UITextSearchFoundTextStyleHighlighted,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);


UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UITextSearchAggregator <NSObject>

/// Returns all currently reported found ranges via @c foundRange:forSearchString:.
@property (nonatomic, readonly) NSOrderedSet<UITextRange *> *allFoundRanges;

/// Call this method when a range of text is found in your document.
///
/// @param range    The range of text that was found.
/// @param string   The query string that was used to locate this range of text.
/// @param document (Optional) A developer-defined document identifier, later provided when this range
///                 needs to be styled.
- (void)foundRange:(UITextRange *)range forSearchString:(NSString *)string inDocument:(nullable UITextSearchDocumentIdentifier)document;

/// Call this method when a found @c range is no longer in @c document . This will cause the system find
/// panel to update it's current state, and if the range provided is the currently highlighted range, will advance
/// to the next found result.
///
/// @param range    The range that is now invalid.
/// @param document (Optional) If multiple documents are used, the document identifier for the range provided.
- (void)invalidateFoundRange:(UITextRange *)range inDocument:(nullable UITextSearchDocumentIdentifier)document;

/// Call this method to invalidate all currently shown ranges. This will cause the system find panel to update
/// it's current state, and may trigger a new search using `performTextSearchWithQueryString:` immediately after.
- (void)invalidate;

/// Call this method after all documents have been searched.
- (void)finishedSearching;

@end


UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UITextSearching <NSObject>

/// Overlap from UITextInput: Returns the currently selected text range, if applicable. Nil otherwise.
@property (nullable, readonly) UITextRange *selectedTextRange;

/// Provide a comparison result comparing developer-provided @c fromRange to @c toRange . This is used by
/// the system find panel to know which @c UITextRange to highlight next when the user taps the "next" or "previous"
/// result buttons.
///
/// @param foundRange    Developer-provided range to compare from.
/// @param toRange  Developer-provided range to compare to.
/// @param document If multiple documents are used, a document identifier will be provided here. Ranges are only
///                compared between other ranges of the same document.
- (NSComparisonResult)compareFoundRange:(UITextRange *)foundRange
                                toRange:(UITextRange *)toRange
                             inDocument:(nullable UITextSearchDocumentIdentifier)document;

/// Perform a text search (across all available searchable documents) using @c string. When results are found,
/// provide the results to @c aggregator.
///
/// @param string     The query string to search for
/// @param options    Search options provided by the user.
/// @param aggregator When results are found, provide them to the aggregator. The aggregator is thread-safe,
///                   so you may send it messages on other threads.
- (void)performTextSearchWithQueryString:(NSString *)string
                            usingOptions:(UITextSearchOptions *)options
                        resultAggregator:(id<UITextSearchAggregator>)aggregator;

/// Given a found @c range , decorate this text appropriately using the provided @c style type.
///
/// @param range    The range of text to decorate.
/// @param document If multiple documents are used, the relevant document identifier is provided here.
///                 Otherwise nil.
/// @param style    A style hint for how to decorate the text. This is ultimately up to the developer, but developers are
///               encouraged to match the system's appearance (i.e., UITextView) as close as possible. 
- (void)decorateFoundTextRange:(UITextRange *)range
                    inDocument:(nullable UITextSearchDocumentIdentifier)document
                    usingStyle:(UITextSearchFoundTextStyle)style;

/// Called when the current search session has changed or ended, with the expectation that all decorations
/// applied via @c decorateFoundTextRange:usingStyle: are cleared.
- (void)clearAllDecoratedFoundText;

@optional

/// Return YES if your searchable item also supports replacement. If this method is unimplemented, it is
/// assumed that text replacement is not supported.
@property (nonatomic, readonly) BOOL supportsTextReplacement;

/// Optionally return NO to disallow the replacement of a particular result @c range . This will disable the "replace"
/// button in the UI. If this method is unimplemented, it is assumed that all results are replaceable.
///
/// @param range    Range to replace.
/// @param document If multiple documents are used, the document from which range originates.
/// @param replacementText  Text that the user intends to replace with.
- (BOOL)shouldReplaceFoundTextInRange:(UITextRange *)range
                           inDocument:(nullable UITextSearchDocumentIdentifier)document
                             withText:(NSString *)replacementText;

/// If you return YES for `-supportsTextReplacement`, this method will be called whenever the user intends to
/// replace a range of text.
///
/// @param range            The range of text requesting to be replaced.
/// @param document         If multiple search documents are used, the relevant document identifier is provided
///                    here. Otherwise nil.
/// @param replacementText  The replacement string.
- (void)replaceFoundTextInRange:(UITextRange *)range
                     inDocument:(nullable UITextSearchDocumentIdentifier)document
                       withText:(NSString *)replacementText;

/// When replacing all occurrences at once, this method is called instead of the one above.
///
/// @param queryString             The search term to replace.
/// @param options                      Search options provided by the find panel UI.
/// @param replacementText    The string to replace it with.
- (void)replaceAllOccurrencesOfQueryString:(NSString *)queryString
                              usingOptions:(UITextSearchOptions *)options
                                  withText:(NSString *)replacementText;

/// Called when the highlighted search result is about to change to @c range .
- (void)willHighlightFoundTextRange:(UITextRange *)range inDocument:(nullable UITextSearchDocumentIdentifier)document;

/// If scrolling is supported, implement this to know when the document should be scrolled to a particular
/// search result.
///
/// @param range    The text range to scroll to.
/// @param document (Optional) If multiple documents are used, the document identifier to scroll to.
- (void)scrollRangeToVisible:(UITextRange *)range inDocument:(nullable UITextSearchDocumentIdentifier)document;

/// Multiple Document Support
/// If your application supports multiple documents (i.e., a search session which aggregates results across
/// multiple searchable items like text views or web views), optionally implement the methods below.

/// Returns the current search document, if applicable. Nil otherwise.
@property (nullable, readonly) UITextSearchDocumentIdentifier selectedTextSearchDocument;

/// Returns the visible ordering from `fromDocument` to `toDocument`. If your document identifiers
/// are index paths, for example, this would yield the same result as `-[NSIndexPath compare:]`.
- (NSComparisonResult)compareOrderFromDocument:(UITextSearchDocumentIdentifier)fromDocument
                                    toDocument:(UITextSearchDocumentIdentifier)toDocument;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextSearching.h>
#endif
