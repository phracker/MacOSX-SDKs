/*
	NSTreeController.h
	Application Kit
	Copyright (c) 2003-2005, Apple Computer, Inc.
	All rights reserved.
 */

#import <AppKit/NSObjectController.h>
#import <Foundation/NSIndexPath.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@interface NSTreeController : NSObjectController {
    void *reserved1;
    NSArray *_modeObservingKeyPaths;
    void *_observedIndexPathHint;
    id _arrangedObjects;
    id _arrayControllerTree;
    id _selectionIndexPaths;
    struct __treeControllerFlags {
        unsigned int _avoidsEmptySelection:1;
        unsigned int _preservesSelection:1;
        unsigned int _selectsInsertedObjects:1;
        unsigned int _explicitlyCannotInsert:1;
        unsigned int _explicitlyCannotInsertChild:1;
        unsigned int _explicitlyCannotAddChild:1;
        unsigned int _alwaysUsesMultipleValuesMarker:1;
        unsigned int _reservedTreeController:25;
    } _treeControllerFlags;
    NSMutableArray *_selectedObjects;
    NSString *_childrenKeyPath;
    NSString *_countKeyPath;
    NSString *_leafKeyPath;
    NSArray *_sortDescriptors;
}

- (void)rearrangeObjects; // triggers rearranging the content objects for the user interface, including sorting (and filtering if provided by subclasses); subclasses can invoke this method if any parameter that affects the arranged objects changes

- (id)arrangedObjects; // opaque root node representation of all displayed objects. This is just for binding to or passing around. At this time, developers should not make any assumption about what methods this object responds to.

- (void)setChildrenKeyPath:(NSString *)keyPath; // key used to find the children of a model object.
- (NSString *)childrenKeyPath;
- (void)setCountKeyPath:(NSString *)keyPath; // optional for performance
- (NSString *)countKeyPath;
- (void)setLeafKeyPath:(NSString *)keyPath; // optional. inserting/adding children disabled for leaf nodes
- (NSString *)leafKeyPath;

- (void)setSortDescriptors:(NSArray *)sortDescriptors;
- (NSArray *)sortDescriptors;

- (id)content;
- (void)setContent:(id)content;

- (void)add:(id)sender;    // adds a new sibling node to the end of the selected objects
- (void)remove:(id)sender; 	//removes the currently selected objects from the tree
- (void)addChild:(id)sender;    // adds a new child node to the end of the selected objects
- (void)insert:(id)sender;    // inserts a peer in front of first selected node
- (void)insertChild:(id)sender;    // inserts a new first child into the children array of the first selected node

- (BOOL)canInsert;
- (BOOL)canInsertChild;
- (BOOL)canAddChild;

- (void)insertObject:(id)object atArrangedObjectIndexPath:(NSIndexPath *)indexPath;
- (void)insertObjects:(NSArray *)objects atArrangedObjectIndexPaths:(NSArray *)indexPaths;
- (void)removeObjectAtArrangedObjectIndexPath:(NSIndexPath *)indexPath;
- (void)removeObjectsAtArrangedObjectIndexPaths:(NSArray *)indexPaths;

	// functionality here is parallel to what is in array controller
- (void)setAvoidsEmptySelection:(BOOL)flag;    // default: YES
- (BOOL)avoidsEmptySelection;
- (void)setPreservesSelection:(BOOL)flag;    // default: YES
- (BOOL)preservesSelection;
- (void)setSelectsInsertedObjects:(BOOL)flag;    // default: YES
- (BOOL)selectsInsertedObjects;
- (void)setAlwaysUsesMultipleValuesMarker:(BOOL)flag;
- (BOOL)alwaysUsesMultipleValuesMarker;

	/* All selection modification methods returning a BOOL indicate through that flag whether changing the selection was successful (changing the selection might trigger a commitEditing call which fails and thus deny's the selection change).
	*/
- (NSArray *)selectedObjects;

- (BOOL)setSelectionIndexPaths:(NSArray *)indexPaths;
- (NSArray *)selectionIndexPaths;
- (BOOL)setSelectionIndexPath:(NSIndexPath *)indexPath;
- (NSIndexPath *)selectionIndexPath;
- (BOOL)addSelectionIndexPaths:(NSArray *)indexPaths;
- (BOOL)removeSelectionIndexPaths:(NSArray *)indexPaths;

@end

#endif
