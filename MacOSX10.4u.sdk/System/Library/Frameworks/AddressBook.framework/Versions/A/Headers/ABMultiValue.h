//
//  ABMultiValue.h
//  AddressBook Framework
//
//  Copyright (c) 2002-2003 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AddressBook/ABTypedefs.h>

// ================================================================================
//	interface ABMutableMultiValue
// ================================================================================
// Represents values of type ABMultiXXXXXProperty. All values in an ABMultiValue must be of the same type
// (kABMultiStringProperty: all values must be strings....)
//
// In case your application needs to store away a reference to a specific value/label pair, use the identifier.
// Index won't work in this case because any client can add/remove/reorder a multivalue making your index
// point to the wrong pair. Identifiers are unique Ids.
//

@interface ABMultiValue : NSObject <NSCopying, NSMutableCopying>
{
@protected
    NSMutableArray      *_identifiers;
    NSMutableArray      *_labels;
    NSMutableArray      *_values;
    NSString            *_primaryIdentifier;
}

- (unsigned int)count;
    // Returns the number of value/label pairs

- (id)valueAtIndex:(unsigned int)index;
    // Returns a value at a given index
    // Raises if index is out of bounds

- (NSString *)labelAtIndex:(unsigned int)index;
    // Returns a label at a given index
    // Raises if index is out of bounds

- (NSString *)identifierAtIndex:(unsigned int)index;
    // Returns an identifier at a given index
    // Raises if index is out of bounds

- (unsigned int)indexForIdentifier:(NSString *)identifier;
    // Returns the index of a given identifier
    // Returns NSNotFound if not found

- (NSString *)primaryIdentifier;
    // Identifier for the primary value

- (ABPropertyType)propertyType;
    // Type of this multivalue (kABMultiXXXXProperty)
    // Returns kABErrorInProperty if this multi-value is empty or not all values have
    // the same type.
@end

// ================================================================================
//	interface ABMutableMultiValue
// ================================================================================
// Mutable variant of ABMultiValue

@interface ABMutableMultiValue : ABMultiValue

- (NSString *)addValue:(id)value withLabel:(NSString *)label;
    // Adds a value with its label
    // Returns the identifier if successful. nil otherwise
    // Raises if value or label are nil
    // Note: No type checking is made when adding a value. But trying to set a multivalue property
    // with a multivalue that doesn't have all its values of the same type will return an error

- (NSString *)insertValue:(id)value withLabel:(NSString *)label atIndex:(unsigned int)index;
    // Insert a value/label pair at a given index
    // Returns the identifier if successful. nil otherwise
    // Raises if value or label are nil or the index is out of bounds
    // Note: No type checking is made when adding a value. But trying to set a multivalue property
    // with a multivalue that doesn't have all its values of the same type will return an error

- (BOOL)removeValueAndLabelAtIndex:(unsigned int)index;
    // Removes a value/label pair at a given index
    // Raises if the index is out of bounds

- (BOOL)replaceValueAtIndex:(unsigned int)index withValue:(id)value;
    // Replaces a value at a given index
    // Raises if the index is out of bounds or the value is nil

- (BOOL)replaceLabelAtIndex:(unsigned int)index withLabel:(NSString*)label;
    // Replaces a label at a given index
    // Raises if the index is out of bounds or the label is nil

- (BOOL)setPrimaryIdentifier:(NSString *)identifier;
    // Sets the primary value given its identifier.
    // Raises if identifier is nil
    // Returns YES if successful

@end
