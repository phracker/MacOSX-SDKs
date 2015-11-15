//
//  ABPerson.h
//  AddressBook Framework
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#ifndef __ABPERSON__
#define __ABPERSON__

#import <AddressBook/ABRecord.h>
#import <AddressBook/ABTypedefs.h>

@class ABSearchElement;

// ================================================================================
//      interface ABPerson
// ================================================================================
// ABPerson is a subclass of ABRecord and represents a person. See ABGlobals.h for
// a list of built-in properties.

@interface ABPerson : ABRecord

- (NSArray *)parentGroups;
    // Returns an array of ABGroup this person belongs to.
    // Returns an empty array if this person doesn't belong to any groups

- (NSArray *)linkedPeople AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
    // Returns an array of all linked people, including this person.
    // Returns an array of only this person if this person is not linked.

@end

// ================================================================================
//      interface ABPerson(ABPerson_Properties)
// ================================================================================
// This section deals with adding/removing properties on people

@interface ABPerson (ABPerson_Properties)

+ (NSInteger)addPropertiesAndTypes:(NSDictionary *)properties;
    // Adds properties to all people records. The dictionary must be of the form:
    //          key: property name
    //          value: property type
    // Property name must be unique
    // Returns the number of properties successfully added (-1 if an error occurred)

+ (NSInteger)removeProperties:(NSArray *)properties;
    // Removes properties from all people
    // Returns the number of properties successfully removed (-1 if an error occurred)

+ (NSArray *)properties;
    // Returns an array of property names

+ (ABPropertyType)typeOfProperty:(NSString*)property;
    // Returns the type of a given property.
    // Returns kABErrorInProperty if the property is not known
@end

// ================================================================================
//      interface ABPerson(ABPerson_Searching)
// ================================================================================
// This section deals with creating search elements to search groups

@interface ABPerson (ABPerson_Searching)
+ (ABSearchElement *)searchElementForProperty:(NSString*)property
                                        label:(NSString*)label
                                          key:(NSString*)key
                                        value:(id)value
                                   comparison:(ABSearchComparison)comparison;
    // Returns a search element that will search people
    //          property: the name of the property to search on (cannot be nil)
    //          label: for multi-value properties an optional label (can be nil)
    //          key: for dictionary values an optional key (can be nil)
    //          value: value to match (can be nil)
    //          comparison: the type of search (see ABTypedefs.h)
    //
    // if the value is nil then the only supported comparisons are kABEqual or kABNotEqual.
    // Note: Support for nil values was added to Mac OS X version 10.2.4
@end

// ================================================================================
//      interface ABPerson(ABPerson_vCard)
// ================================================================================
// This section deals with vCards

@interface ABPerson (ABPerson_vCard)
- (id)initWithVCardRepresentation:(NSData *)vCardData;
    // Create a person from a vCard
    // Returns nil if vCardData is nil or not a valid vCard

- (NSData *)vCardRepresentation;
    // Returns the vCard representation of a person
@end

#endif // __ABPERSON__
