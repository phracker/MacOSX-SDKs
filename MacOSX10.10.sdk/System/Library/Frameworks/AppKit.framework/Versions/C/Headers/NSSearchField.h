/*
    NSSearchField.h
    Application Kit
    Copyright (c) 2003-2014, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSTextField.h>


@interface NSSearchField : NSTextField {
  @private
    struct {
        unsigned int _inTransition:1;
        unsigned int _reselecting:1;
        unsigned int _reserved:30;
    } _sfFlags;
    unsigned int _reserved2;
    unsigned int _reserved3;
    unsigned int _reserved4;
}

@property (copy) NSArray *recentSearches;
// if app wants to do custom search lists. will return empty array if no searches

@property (copy) NSString *recentsAutosaveName;
// must be set to use. default is nil which means no autosave.

@property (strong) NSMenu *searchMenuTemplate NS_AVAILABLE_MAC(10_10);
// set/get search menu template. Menu can use custom tagged items to indicate special items. this menu isn't actually set but used to construct the dynamic search menu. if cleared, then we don't track recents.

@property BOOL sendsWholeSearchString NS_AVAILABLE_MAC(10_10);
// if clear, send action on each key stroke (after sufficient amount of time so we don't interfere with typing). if set, send only on return/enter or clicking magnifying search button

@property NSInteger maximumRecents NS_AVAILABLE_MAC(10_10);
// set/get limit max recents. allowable between 0 and 254. setting -1 will use default.

@property BOOL sendsSearchStringImmediately NS_AVAILABLE_MAC(10_10);

@end


