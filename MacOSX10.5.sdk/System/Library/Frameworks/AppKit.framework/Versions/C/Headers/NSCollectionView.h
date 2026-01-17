/*
	NSCollectionView.h
	Application Kit
	Copyright (c) 2005-2007, Apple Inc.
	All rights reserved.
 */

#import <AppKit/NSAnimation.h>
#import <AppKit/NSView.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSData.h>
#import <Foundation/NSSet.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class NSCollectionView;

@interface NSCollectionViewItem : NSObject <NSCopying, NSCoding> {
@private
    void *_reserved[2];
    NSMutableData *_archive;
    NSCollectionView *_ownerView;    // not retained
    id _representedObject;
    NSView *_view;
    struct __collectionViewItemFlags {
        unsigned int _selected:1;
        unsigned int _removalNeeded:1;
        unsigned int _suppressSelectionChangeNotification:1;
        unsigned int _reservedAnimationContainer:29;
    } _itemFlags;
    NSRect _targetViewFrameRect;
    NSRect _appliedViewFrameRect;
    NSUInteger _containerReferenceCounter;
}

- (NSCollectionView *)collectionView;

- (void)setRepresentedObject:(id)object;
- (id)representedObject;

- (void)setView:(NSView *)view;
- (NSView *)view;

- (void)setSelected:(BOOL)flag;
- (BOOL)isSelected;

@end

@interface NSCollectionView : NSView {
@private
    void *_reserved[9];
    NSMutableArray *_backgroundLayers;
    NSArray *_content;
    NSMutableIndexSet *_selectionIndexes;
    NSCollectionViewItem *_itemPrototype;
    NSSize _minGridSize;
    NSSize _maxGridSize;
    NSUInteger _minGridRows;
    NSUInteger _maxGridRows;
    NSUInteger _minGridColumns;
    NSUInteger _maxGridColumns;
    NSArray *_backgroundColors;
    struct __animationContainerFlags {
        unsigned int _ignoreFrameSizeChanges:1;
        unsigned int _selectable:1;
        unsigned int _allowsMultipleSelection:1;
        unsigned int _avoidsEmptySelection:1;
        unsigned int _superviewIsClipView:1;
        unsigned int _gridParametersReadFromPrototype:1;
        unsigned int _isFirstResponder:1;
        unsigned int _reservedAnimationContainer:25;
    } _animationContainerFlags;
    NSSize _targetFrameSize;
    NSSize _targetGridSize;
    NSSize _targetUnfilledViewSpace;
    NSUInteger _targetNumberOfGridRows;
    NSUInteger _targetNumberOfGridColumns;
    NSMutableArray *_targetItems;
    NSSize _appliedFrameSize;
    NSSize _appliedGridSize;
    NSSize _appliedUnfilledViewSpace;
    NSUInteger _appliedNumberOfGridRows;
    NSUInteger _appliedNumberOfGridColumns;
    NSMutableArray *_appliedItems;
    NSMutableSet *_appliedItemsAsSet;
    NSMutableSet *_appliedRemovedItemsAsSet;
    NSTimeInterval _animationDuration;
    NSViewAnimation *_animation;
    NSMutableArray *_hideItems;
    NSMutableArray *_showItems;
}

- (BOOL)isFirstResponder;    // fully KVO compliant - can be used determine different selection colors, etc.

- (void)setContent:(NSArray *)content;
- (NSArray *)content;
- (void)setSelectable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setAllowsMultipleSelection:(BOOL)flag;    // default: YES
- (BOOL)allowsMultipleSelection;
- (void)setSelectionIndexes:(NSIndexSet *)indexes;
- (NSIndexSet *)selectionIndexes;

- (NSCollectionViewItem *)newItemForRepresentedObject:(id)object;    // override if item should not be generated from prototype (or if view needs to be customized) - the returned object should not be autoreleased

- (void)setItemPrototype:(NSCollectionViewItem *)prototype;
- (NSCollectionViewItem *)itemPrototype;

- (void)setMaxNumberOfRows:(NSUInteger)number;    // default: 0, which means no limit 
- (NSUInteger)maxNumberOfRows;
- (void)setMaxNumberOfColumns:(NSUInteger)number;    // default: 0, which means no limit 
- (NSUInteger)maxNumberOfColumns;
- (void)setMinItemSize:(NSSize)size;    // default: (0; 0)
- (NSSize)minItemSize;
- (void)setMaxItemSize:(NSSize)size;    // default: (0; 0), which means no limit
- (NSSize)maxItemSize;

- (void)setBackgroundColors:(NSArray *)colors;    // passing nil or an empty array resets the background colors back to the default
- (NSArray *)backgroundColors;

@end

#endif
