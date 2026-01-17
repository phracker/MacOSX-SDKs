/*
	NSTreeController.h
	Application Kit
	Copyright (c) 2003-2015, Apple Inc.
	All rights reserved.
 */

#import <AppKit/NSObjectController.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSIndexPath.h>

NS_ASSUME_NONNULL_BEGIN

@class NSSortDescriptor, NSTreeNode;


@interface NSTreeController : NSObjectController {
    id _treeControllerReserved1;
    NSArray *_modelObservingKeyPaths;
    id _treeStructureObservers;
    id _arrangedObjects;
    id _rootNode;
    id _selectionIndexPaths;
    struct __treeControllerFlags {
        unsigned int _avoidsEmptySelection:1;
        unsigned int _preservesSelection:1;
        unsigned int _selectsInsertedObjects:1;
        unsigned int _explicitlyCannotInsert:1;
        unsigned int _explicitlyCannotInsertChild:1;
        unsigned int _explicitlyCannotAddChild:1;
        unsigned int _alwaysUsesMultipleValuesMarker:1;
        unsigned int _observingThroughArrangedObjects:1;
        unsigned int _mutatingNodes:1;
        unsigned int _performingFetch:1;
        unsigned int _skipSortingAfterFetch:1;
	unsigned int _usesIdenticalComparisonOfModelObjects:1;
        unsigned int _reservedTreeController:20;
    } _treeControllerFlags;
    NSArray *_selectedObjects;
    NSString *_childrenKeyPath;
    NSString *_countKeyPath;
    NSString *_leafKeyPath;
    NSArray *_sortDescriptors;
}

- (void)rearrangeObjects; // triggers rearranging the content objects for the user interface, including sorting (and filtering if provided by subclasses); subclasses can invoke this method if any parameter that affects the arranged objects changes

// proxy for the root tree node responds to -childNodes and -descendantNodeAtIndexPath:(NSIndexPath *)indexPath
@property (readonly, strong) id arrangedObjects; 
@property (nullable, copy) NSString *childrenKeyPath; // key used to find the children of a model object.
@property (nullable, copy) NSString *countKeyPath; // optional for performance
@property (nullable, copy) NSString *leafKeyPath; // optional. inserting/adding children disabled for leaf nodes

@property (copy) NSArray<NSSortDescriptor *> *sortDescriptors;

@property (nullable, strong) id content;

- (void)add:(nullable id)sender;    // adds a new sibling node to the end of the selected objects
- (void)remove:(nullable id)sender; 	//removes the currently selected objects from the tree
- (void)addChild:(nullable id)sender;    // adds a new child node to the end of the selected objects
- (void)insert:(nullable id)sender;    // inserts a peer in front of first selected node
- (void)insertChild:(nullable id)sender;    // inserts a new first child into the children array of the first selected node

@property (readonly) BOOL canInsert;
@property (readonly) BOOL canInsertChild;
@property (readonly) BOOL canAddChild;

- (void)insertObject:(nullable id)object atArrangedObjectIndexPath:(NSIndexPath *)indexPath;
- (void)insertObjects:(NSArray *)objects atArrangedObjectIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
- (void)removeObjectAtArrangedObjectIndexPath:(NSIndexPath *)indexPath;
- (void)removeObjectsAtArrangedObjectIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

	// functionality here is parallel to what is in array controller
@property BOOL avoidsEmptySelection;   // default: YES
@property BOOL preservesSelection;   // default: YES
@property BOOL selectsInsertedObjects;   // default: YES
@property BOOL alwaysUsesMultipleValuesMarker;

	/* All selection modification methods returning a BOOL indicate through that flag whether changing the selection was successful (changing the selection might trigger a commitEditing call which fails and thus deny's the selection change).
	*/
@property (readonly, copy) NSArray *selectedObjects;

- (BOOL)setSelectionIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
@property (readonly, copy) NSArray<NSIndexPath *> *selectionIndexPaths;
- (BOOL)setSelectionIndexPath:(nullable NSIndexPath *)indexPath;
@property (nullable, readonly, copy) NSIndexPath *selectionIndexPath;
- (BOOL)addSelectionIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
- (BOOL)removeSelectionIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

@property (readonly, copy) NSArray<NSTreeNode *> *selectedNodes NS_AVAILABLE_MAC(10_5);

- (void)moveNode:(NSTreeNode *)node toIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_MAC(10_5);
- (void)moveNodes:(NSArray<NSTreeNode *> *)nodes toIndexPath:(NSIndexPath *)startingIndexPath NS_AVAILABLE_MAC(10_5);

- (nullable NSString *)childrenKeyPathForNode:(NSTreeNode *)node NS_AVAILABLE_MAC(10_5);
- (nullable NSString *)countKeyPathForNode:(NSTreeNode *)node NS_AVAILABLE_MAC(10_5);
- (nullable NSString *)leafKeyPathForNode:(NSTreeNode *)node NS_AVAILABLE_MAC(10_5);


@end

NS_ASSUME_NONNULL_END

