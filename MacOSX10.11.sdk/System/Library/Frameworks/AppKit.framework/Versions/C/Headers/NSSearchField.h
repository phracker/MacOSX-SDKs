/*
    NSSearchField.h
    Application Kit
    Copyright (c) 2003-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSTextField.h>

NS_ASSUME_NONNULL_BEGIN

@class NSSearchField;

@protocol NSSearchFieldDelegate <NSTextFieldDelegate>
@optional
- (void)searchFieldDidStartSearching:(NSSearchField *)sender NS_AVAILABLE_MAC(10_11);
- (void)searchFieldDidEndSearching:(NSSearchField *)sender NS_AVAILABLE_MAC(10_11);
@end

@interface NSSearchField : NSTextField {
  @private
    struct {
        unsigned int _inTransition:1;
        unsigned int _reselecting:1;
        unsigned int _isSearching:1;
        unsigned int _reserved:29;
    } _sfFlags;
    unsigned int _reserved2;
    unsigned int _reserved3;
    unsigned int _reserved4;
}

/* The rectangle for the search text-field within the bounds of the search field. Subclasses can override this method for custom layout purposes. The isCentered parameter is YES when centersPlaceholder is YES and the caller is interested in the centered appearance. It is NO either when centersPlaceholder is NO or when centersPlaceholder is YES and the caller is interested in the non-centered appearance. Use this instead of -[NSSearchFieldCell searchTextRectForBounds:].
 */
- (NSRect)rectForSearchTextWhenCentered:(BOOL)isCentered NS_AVAILABLE_MAC(10_11);

/* The rectangle for the search button within the bounds of the search field. Subclasses can override this method for custom layout purposes. The isCentered parameter is YES when centersPlaceholder is YES and the caller is interested in the centered appearance. It is NO either when centersPlaceholder is NO or when centersPlaceholder is YES and the caller is interested in the non-centered appearance. Use this instead of -[NSSearchFieldCell searchButtonRectForBounds:].
 */
- (NSRect)rectForSearchButtonWhenCentered:(BOOL)isCentered NS_AVAILABLE_MAC(10_11);

/* The rectangle for the cancel button within the bounds of the search field. Subclasses can override this method for custom layout purposes. The isCentered parameter is YES when centersPlaceholder is YES and the caller is interested in the centered appearance. It is NO either when centersPlaceholder is NO or when centersPlaceholder is YES and the caller is interested in the non-centered appearance. Use this instead of -[NSSearchFieldCell cancelButtonRectForBounds:].
 */
- (NSRect)rectForCancelButtonWhenCentered:(BOOL)isCentered NS_AVAILABLE_MAC(10_11);

/* if app wants to do custom search lists. will return empty array if no searches */
@property (copy) NSArray<NSString *> *recentSearches;

/* must be set to use. default is nil which means no autosave. */
@property (nullable, copy) NSString *recentsAutosaveName;

/* set/get search menu template. Menu can use custom tagged items to indicate special items. this menu isn't actually set but used to construct the dynamic search menu. if cleared, then we don't track recents. */
@property (nullable, strong) NSMenu *searchMenuTemplate NS_AVAILABLE_MAC(10_10);

/* if clear, send action on each key stroke (after sufficient amount of time so we don't interfere with typing). if set, send only on return/enter or clicking magnifying search button */
@property BOOL sendsWholeSearchString NS_AVAILABLE_MAC(10_10);

/* set/get limit max recents. allowable between 0 and 254. setting -1 will use default. */
@property NSInteger maximumRecents NS_AVAILABLE_MAC(10_10);

@property BOOL sendsSearchStringImmediately NS_AVAILABLE_MAC(10_10);

@property (nullable, assign) id<NSSearchFieldDelegate> delegate NS_AVAILABLE_MAC(10_11);

/* Defaults to YES. When set, the search field's components are centered within the control if the field is empty and does not have focus. When receiving focus, given the field is empty, the centered objects will animate to the edges of the control. When this property is set to NO, the components are always at the edge. When set ot YES, wantsLayer is also set to YES.
*/
@property BOOL centersPlaceholder NS_AVAILABLE_MAC(10_11);

@end

NS_ASSUME_NONNULL_END
