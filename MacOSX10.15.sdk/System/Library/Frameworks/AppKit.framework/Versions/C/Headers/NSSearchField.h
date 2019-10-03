/*
    NSSearchField.h
    Application Kit
    Copyright (c) 2003-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSTextField.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

typedef NSString * NSSearchFieldRecentsAutosaveName NS_SWIFT_BRIDGED_TYPEDEF;

@class NSSearchField;

@protocol NSSearchFieldDelegate <NSTextFieldDelegate>
@optional
- (void)searchFieldDidStartSearching:(NSSearchField *)sender API_AVAILABLE(macos(10.11));
- (void)searchFieldDidEndSearching:(NSSearchField *)sender API_AVAILABLE(macos(10.11));
@end

@interface NSSearchField : NSTextField

/* The rectangle for the search text-field within the bounds of the search field. Subclasses can override this method for custom layout purposes. The isCentered parameter is YES when centersPlaceholder is YES and the caller is interested in the centered appearance. It is NO either when centersPlaceholder is NO or when centersPlaceholder is YES and the caller is interested in the non-centered appearance. Use this instead of -[NSSearchFieldCell searchTextRectForBounds:].
 */
- (NSRect)rectForSearchTextWhenCentered:(BOOL)isCentered API_AVAILABLE(macos(10.11));

/* The rectangle for the search button within the bounds of the search field. Subclasses can override this method for custom layout purposes. The isCentered parameter is YES when centersPlaceholder is YES and the caller is interested in the centered appearance. It is NO either when centersPlaceholder is NO or when centersPlaceholder is YES and the caller is interested in the non-centered appearance. Use this instead of -[NSSearchFieldCell searchButtonRectForBounds:].
 */
- (NSRect)rectForSearchButtonWhenCentered:(BOOL)isCentered API_AVAILABLE(macos(10.11));

/* The rectangle for the cancel button within the bounds of the search field. Subclasses can override this method for custom layout purposes. The isCentered parameter is YES when centersPlaceholder is YES and the caller is interested in the centered appearance. It is NO either when centersPlaceholder is NO or when centersPlaceholder is YES and the caller is interested in the non-centered appearance. Use this instead of -[NSSearchFieldCell cancelButtonRectForBounds:].
 */
- (NSRect)rectForCancelButtonWhenCentered:(BOOL)isCentered API_AVAILABLE(macos(10.11));

/* if app wants to do custom search lists. will return empty array if no searches */
@property (copy) NSArray<NSString *> *recentSearches;

/* must be set to use. default is nil which means no autosave. */
@property (nullable, copy) NSSearchFieldRecentsAutosaveName recentsAutosaveName;

/* set/get search menu template. Menu can use custom tagged items to indicate special items. this menu isn't actually set but used to construct the dynamic search menu. if cleared, then we don't track recents. */
@property (nullable, strong) NSMenu *searchMenuTemplate API_AVAILABLE(macos(10.10));

/* if clear, send action on each key stroke (after sufficient amount of time so we don't interfere with typing). if set, send only on return/enter or clicking magnifying search button */
@property BOOL sendsWholeSearchString API_AVAILABLE(macos(10.10));

/* set/get limit max recents. allowable between 0 and 254. setting -1 will use default. */
@property NSInteger maximumRecents API_AVAILABLE(macos(10.10));

@property BOOL sendsSearchStringImmediately API_AVAILABLE(macos(10.10));

@property (nullable, weak) id<NSSearchFieldDelegate> delegate API_AVAILABLE(macos(10.11));

/* Defaults to YES. When set, the search field's components are centered within the control if the field is empty and does not have focus. When receiving focus, given the field is empty, the centered objects will animate to the edges of the control. When this property is set to NO, the components are always at the edge. When set ot YES, wantsLayer is also set to YES.
*/
@property BOOL centersPlaceholder API_AVAILABLE(macos(10.11));

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
