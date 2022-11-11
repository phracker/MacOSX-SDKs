#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSDiffableDataSourceSectionSnapshot.h>)
//
//  NSDiffableDataSourceSectionSnapshot.h
//  UIKit
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(14.0),tvos(14.0),watchos(7.0))
@interface NSDiffableDataSourceSectionSnapshot<ItemIdentifierType> : NSObject<NSCopying>

// creates an empty snapshot
- (instancetype)init;

// append items to Root
- (void)appendItems:(NSArray<ItemIdentifierType>*)items;

// append items into parent (creating a new Parent+Child relationship if not present; appends to existing children if present)
- (void)appendItems:(NSArray<ItemIdentifierType>*)items intoParentItem:(nullable ItemIdentifierType)parentItem;


// Insert Before will always match the level of the destination item.
//
//   Examples:
//
//                       +---------+
//                       |    0    |
//   +---------+         +-+-------+-+
//   |    0    |           |   INS   |
//   +-+-------+-+         +---------+
//     |    1    |         |    1    |
//     +---------+         +---------+
//     |    2    |         |    2    |
//   +-+-------+-+       +-+-------+-+
//   |    3    |         |    3    |
//   +---------+         +---------+
//
//  +--------------------------------+
//  |        insertBefore(1)         |
//  +--------------------------------+
//
//                       +---------+
//                       |   INS   |
//   +---------+         +---------+
//   |    0    |         |    0    |
//   +-+-------+-+       +-+-------+-+
//     |    1    |         |    1    |
//     +---------+         +---------+
//     |    2    |         |    2    |
//   +-+-------+-+       +-+-------+-+
//   |    3    |         |    3    |
//   +---------+         +---------+
//
//  +--------------------------------+
//  |        insertBefore(0)         |
//  +--------------------------------+

- (void)insertItems:(NSArray<ItemIdentifierType>*)items beforeItem:(ItemIdentifierType)beforeIdentifier;

// Insert After: respect any destination item's children and inserts the new items after them
//               at the same level as the destination item.
//
//
//                       +---------+
//                       |    0    |
//   +---------+         +-+-------+-+
//   |    0    |           |    1    |
//   +-+-------+-+         +---------+
//     |    1    |         |    2    |
//     +---------+       +-+-------+-+
//     |    2    |       |   INS   |
//   +-+-------+-+       +---------+
//   |    3    |         |    3    |
//   +---------+         +---------+
//
//  +--------------------------------+
//  | insertAfter(INS, after:0)      |
//  +--------------------------------+
//
//                     +---------+
//                     |    0    |
//   +---------+       +-+-------+-+
//   |    0    |         |    1    |
//   +-+-------+-+       +---------+
//     |    1    |       |    2    |
//     +---------+       +-+-------+-+
//     |    2    |         |    3    |
//     +-+-------+-+     +-+-------+-+
//       |    3    |     |   INS   |
//   +---+-----+---+   +-+-------+-+
//   |    4    |       |    4    |
//   +---------+       +---------+
//
//  +--------------------------------+
//  | insertAfter(INS, after:2)      |
//  +--------------------------------+

- (void)insertItems:(NSArray<ItemIdentifierType>*)items afterItem:(ItemIdentifierType)afterIdentifier;

- (void)deleteItems:(NSArray<ItemIdentifierType>*)items;          // will also delete children
- (void)deleteAllItems;

// Expand / Collapse state does not require children and persists along with the snapshot
//   This allows for simple restoration of visual state along with animating multiple expand/collapse updates per apply() call

- (void)expandItems:(NSArray<ItemIdentifierType>*)items;          // will log if item is not found
- (void)collapseItems:(NSArray<ItemIdentifierType>*)items;        // will log if item is not found

- (void)replaceChildrenOfParentItem:(ItemIdentifierType)parentItem withSnapshot:(NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshot;

// insert a subtree -- represented by a snapshot -- before/after a destination item
- (void)insertSnapshot:(NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshot beforeItem:(ItemIdentifierType)item;
- (ItemIdentifierType)insertSnapshot:(NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshot afterItem:(ItemIdentifierType)item;

// these methods are all O(1)
- (BOOL)isExpanded:(ItemIdentifierType)item;
- (BOOL)isVisible:(ItemIdentifierType)item;

- (BOOL)containsItem:(ItemIdentifierType)item;
- (NSInteger)levelOfItem:(ItemIdentifierType)item;   // NSNotFound if not present
- (NSInteger)indexOfItem:(ItemIdentifierType)item;

- (NSArray<ItemIdentifierType>*)items;
- (NSArray<ItemIdentifierType>*)expandedItems;

- (nullable ItemIdentifierType)parentOfChildItem:(ItemIdentifierType)childItem;  // nil == root node

// Returned snapshot represents the children of the specified item (recursively)
//   1. If item has no children, the snapshot is empty.
//   2. Level starts at 0
- (NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshotOfParentItem:(ItemIdentifierType)parentItem;        // snapshot will not include parentItem
- (NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshotOfParentItem:(ItemIdentifierType)parentItem includingParentItem:(BOOL)includingParentItem;

@property(nonatomic,readonly,strong) NSArray<ItemIdentifierType> *items;
@property(nonatomic,readonly,strong) NSArray<ItemIdentifierType> *rootItems;
@property(nonatomic,readonly,strong) NSArray<ItemIdentifierType> *visibleItems;

// debugging; displays hierarchy
//    legend:
//       * == visible
//       + == expanded
//       - == collapsed
- (NSString*)visualDescription;


@end


NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/NSDiffableDataSourceSectionSnapshot.h>
#endif
