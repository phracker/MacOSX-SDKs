#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFindSession.h>)
//
//  UIFindSession.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UITextSearching.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos)
typedef NS_ENUM(NSInteger, UIFindSessionSearchResultDisplayStyle) {
    /// Displays the total number of reported results, and which result index is currently highlighted (i.e., "1 of 5").
    UIFindSessionSearchResultDisplayStyleCurrentAndTotal,
    
    /// Displays only the total number of reported results (i.e., "5 results").
    UIFindSessionSearchResultDisplayStyleTotal,
    
    /// Do not display number of reported results.
    UIFindSessionSearchResultDisplayStyleNone,
} NS_SWIFT_NAME(UIFindSession.SearchResultDisplayStyle) API_UNAVAILABLE(watchos);

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos)
typedef NS_ENUM(NSInteger, UITextSearchMatchMethod) {
    /// Word contains search string.
    UITextSearchMatchMethodContains,
    
    /// Word contains the search string as a prefix.
    UITextSearchMatchMethodStartsWith,
    
    /// Word is an exact match for the search string.
    UITextSearchMatchMethodFullWord,
} NS_SWIFT_NAME(UITextSearchOptions.WordMatchMethod) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UITextSearchOptions : NSObject
/// See UITextSearchMatchMethod above.
@property (nonatomic, readonly) UITextSearchMatchMethod wordMatchMethod;

/// Comparison options to use when searching for strings.
@property (nonatomic, readonly) NSStringCompareOptions stringCompareOptions;
@end

/// @class  UIFindSession
/// @abstract An abstract base class for managing a find session.
/// @discussion A UIFindSession instance is returned by UIFindInteractionDelegate when a find session is initiated
///             by the user. You can choose to implement a subclass of UIFindSession to handle all state, decoration,
///             and behavior yourself. This would be the preferred choice if the view your find interaction is attached to
///             is very custom in the way it handles the presentation of found results. Other clients are encouraged to
///             instead use UISearchableObjectFindSession and the UITextSearching protocol, which manages the
///             state of a find session automatically using behavior consistent with the rest of the system.
UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIFindSession : NSObject

/// Returns the total number of results.
/// You may call UIFindInteraction's @c updateResultCount to update the system find panel's UI if already visible.
@property (nonatomic, readonly) NSInteger resultCount;

/// Returns the index of the currently highlighted result, out of @c resultCount.
/// If no result is currently highlighted, return NSNotFound.
/// You may call UIFindInteraction's @c updateResultCount to update the system find panel's UI if already visible.
@property (nonatomic, readonly) NSInteger highlightedResultIndex;

/// Defines how results are reported through the find panel's UI. The default style is @c CurrentAndTotal.
@property (nonatomic, readwrite) UIFindSessionSearchResultDisplayStyle searchResultDisplayStyle;

/// Return YES if replacement is supported. This gates the appearance of replace UI in the find navigator panel. Default is NO.
@property (nonatomic, readonly) BOOL supportsReplacement;

/// Return YES if replacement is allowed for the currently highlighted item. This property controls the enabled state
/// of the "replace" button in the find navigator, as well as various hardware keyboard shortcuts involving replacement.
/// Default is YES, if supportsReplacement is YES. 
@property (nonatomic, readonly) BOOL allowsReplacementForCurrentlyHighlightedResult;

/// Called when the user requests a search to be performed for @c query, using @c options.
///
/// @param query    The search string entered into the search text field in the system find panel.
/// @param options  Object representing all configured search options for this search.
- (void)performSearchWithQuery:(NSString *)query options:(nullable UITextSearchOptions *)options
    NS_SWIFT_NAME(performSearch(query:options:));

/// Called when the user requests a single replacement to occur given @c searchQuery and @c replacementString.
///
/// @param searchQuery  The search string entered into the search text field in the system find panel.
/// @param replacementString    The replacement string entered into the replace text field in the system find panel.
/// @param options  Object representing all configured search options for this replacement.
- (void)performSingleReplacementWithSearchQuery:(NSString *)searchQuery
                              replacementString:(NSString *)replacementString
                                        options:(nullable UITextSearchOptions *)options
    NS_SWIFT_NAME(performSingleReplacement(query:replacementString:options:));

/// Called when the user requests a document-wide replacement to occur.
///
/// @param searchQuery  The search string entered into the search text field in the system find panel.
/// @param replacementString    The replacement string entered into the replace text field in the system find panel.
/// @param options  Object representing all configured search options for this replacement.
- (void)replaceAllInstancesOfSearchQuery:(NSString *)searchQuery
                   withReplacementString:(NSString *)replacementString
                                 options:(nullable UITextSearchOptions *)options
    NS_SWIFT_NAME(replaceAll(searchQuery:replacementString:options:));

/// Called when either the next or previous button is activated, or when return or shift+return is pressed in the search field.
///
/// @param direction    Which direction the user intends to move, either forward or backward.
- (void)highlightNextResultInDirection:(UITextStorageDirection)direction;

/// This method will be called whenever the current find session's found/highlighted results are to be invalidated. For instance,
/// when the search query is cleared, options changed, or any other event where we may not perform another search right away.
- (void)invalidateFoundResults;

@property (nonatomic, readonly) BOOL allowsReplacement API_DEPRECATED_WITH_REPLACEMENT("supportsReplacement", ios(16.0, 16.0), visionos(1.0, 1.0));

@end

/// @class UITextSearchingFindSession
/// @abstract   A @c UIFindSession implementation for clients who adopt the @c UITextSearching protocol.
/// @discussion @c UITextSearchingFindSession is a concrete implementation of @c UIFindSession which manages
///             all of the state associated with a find session (i.e., the way results are presented to the user, the
///             order in which they are cycled through, etc.). A @c UITextSearchingFindSession would be ideal
///             for clients who already implement the @c UITextInput protocol, since many of the concepts defined there are
///             compatible with this class.
UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UITextSearchingFindSession : UIFindSession

/// The object responsible for actually performing the search operation and decorating found text results.
/// See `UITextSearching.h` for more information.
@property (nonatomic, readonly, weak) id<UITextSearching> searchableObject;

- (instancetype)initWithSearchableObject:(id<UITextSearching>)searchableObject NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFindSession.h>
#endif
