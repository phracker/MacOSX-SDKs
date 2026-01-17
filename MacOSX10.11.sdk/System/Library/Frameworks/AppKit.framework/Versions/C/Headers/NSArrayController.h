/*
	NSArrayController.h
	Application Kit
	Copyright (c) 2002-2015, Apple Inc.
	All rights reserved.
 */

#import <AppKit/NSObjectController.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSPredicate.h>


NS_ASSUME_NONNULL_BEGIN

@class NSIndexSet, NSMutableIndexSet, NSSortDescriptor;

@interface NSArrayController : NSObjectController {
@private
    void *_reserved4;
    id _rearrangementExtensions;
    NSMutableArray *_temporaryWorkObjects;
    struct __arrayControllerFlags {
        unsigned int _avoidsEmptySelection:1;
        unsigned int _preservesSelection:1;
        unsigned int _selectsInsertedObjects:1;
        unsigned int _alwaysUsesMultipleValuesMarker:1;
        unsigned int _refreshesAllModelObjects:1;
        unsigned int _filterRestrictsInsertion:1;
        unsigned int _overridesArrangeObjects:1;
        unsigned int _overridesDidChangeArrangementCriteria:1;
        unsigned int _explicitlyCannotInsert:1;
        unsigned int _generatedEmptyArray:1;
        unsigned int _isObservingKeyPathsThroughArrangedObjects:1;
        unsigned int _arrangedObjectsIsMutable:1;
        unsigned int _clearsFilterPredicateOnInsertion:1;
        unsigned int _skipSortingAfterFetch:1;
        unsigned int _automaticallyRearrangesObjects:1;
        unsigned int _reservedArrayController:17;
    } _arrayControllerFlags;
    NSUInteger _observedIndexHint;
    NSMutableIndexSet *_selectionIndexes;
    NSMutableArray *_objects;
    NSIndexSet *_cachedSelectedIndexes;
    NSArray *_cachedSelectedObjects;
    NSArray *_arrangedObjects;
}

- (void)rearrangeObjects;    // triggers rearranging the content objects for the user interface, including sorting and filtering; subclasses can override and invoke this method if any parameter that affects the arranged objects changes

@property BOOL automaticallyRearrangesObjects NS_AVAILABLE_MAC(10_5);   // default: NO

@property (nullable, readonly, copy) NSArray<NSString *> *automaticRearrangementKeyPaths NS_AVAILABLE_MAC(10_5);    // computes the array of key paths that trigger automatic rearranging from the sort descriptors and filter predicates; subclasses may override this method to customize the default behavior (for example if additional arrangement criteria are used in custom implementations of -rearrangeObjects)
- (void)didChangeArrangementCriteria NS_AVAILABLE_MAC(10_5);    // invoked by the controller itself when any criteria for arranging objects change (sort descriptors or filter predicates) to reset the key paths for automatic rearranging; subclasses should invoke this method if additional arrangement criteria are used in custom implementations of -rearrangeObjects and those criteria change

@property (copy) NSArray<NSSortDescriptor *> *sortDescriptors;

@property (nullable, strong) NSPredicate *filterPredicate;

/* Indicates whether the controller should nil out its filter predicate before inserting (or adding) new objects. When set to yes, this eliminates the problem of inserting a new object into the array that would otherwise immediately be filtered out of the array of arranged objects.
*/
@property BOOL clearsFilterPredicateOnInsertion; // default: YES

- (NSArray *)arrangeObjects:(NSArray *)objects;    // returns objects to be arranged in the user interface for the content object array objects - method can be overridden to use a different kind of sort mechanism or to filter the display objects
@property (readonly, strong) id arrangedObjects;     // array of all displayed objects (after sorting and potentially filtering)

@property BOOL avoidsEmptySelection;   // default: YES
@property BOOL preservesSelection;   // default: YES
@property BOOL selectsInsertedObjects;    // default: YES

/* Indicates whether the controller should indicate all multiple selections through the NSMultipleValuesMarker, whether the selected values are equal or not (by default, the controller will only use the NSMultipleValuesMarker if the selected objects actually have different values) - this may act as a performance enhancement in certain applications.
*/
@property BOOL alwaysUsesMultipleValuesMarker;

/* All selection modification methods returning a BOOL indicate through that flag whether changing the selection was successful (changing the selection might trigger an commitEditing call which fails and thus deny's the selection change).
*/
- (BOOL)setSelectionIndexes:(NSIndexSet *)indexes;    // to deselect all: empty index set, to select all: index set with indexes [0...count - 1]
@property (readonly, copy) NSIndexSet *selectionIndexes;
- (BOOL)setSelectionIndex:(NSUInteger)index;
@property (readonly) NSUInteger selectionIndex;
- (BOOL)addSelectionIndexes:(NSIndexSet *)indexes;
- (BOOL)removeSelectionIndexes:(NSIndexSet *)indexes;

- (BOOL)setSelectedObjects:(NSArray *)objects;
@property (null_unspecified, readonly, copy) NSArray *selectedObjects;
- (BOOL)addSelectedObjects:(NSArray *)objects;
- (BOOL)removeSelectedObjects:(NSArray *)objects;

- (void)add:(nullable id)sender;    // overridden to add a new object to the content objects and to the arranged objects
- (void)remove:(nullable id)sender;    // overridden to remove the selected objects
- (void)insert:(nullable id)sender;
@property (readonly) BOOL canInsert;    // can be used in bindings controlling the enabling of buttons, for example
- (void)selectNext:(nullable id)sender;
- (void)selectPrevious:(nullable id)sender;
@property (readonly) BOOL canSelectNext;
@property (readonly) BOOL canSelectPrevious;

- (void)addObject:(id)object;    // overridden to add to the content objects and to the arranged objects if all filters currently applied are matched
- (void)addObjects:(NSArray *)objects;
- (void)insertObject:(id)object atArrangedObjectIndex:(NSUInteger)index;    // inserts into the content objects and the arranged objects (as specified by index in the arranged objects) - will raise an exception if the object does not match all filters currently applied
- (void)insertObjects:(NSArray *)objects atArrangedObjectIndexes:(NSIndexSet *)indexes;
- (void)removeObjectAtArrangedObjectIndex:(NSUInteger)index;    // removes from the content objects and the arranged objects (as specified by index in the arranged objects)
- (void)removeObjectsAtArrangedObjectIndexes:(NSIndexSet *)indexes;
- (void)removeObject:(id)object;    // removes from the content objects and the arranged objects (if currently contained)
- (void)removeObjects:(NSArray *)objects;

@end

NS_ASSUME_NONNULL_END

