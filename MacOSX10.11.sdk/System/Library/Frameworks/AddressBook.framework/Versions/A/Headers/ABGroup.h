//
//  ABGroup.h
//  AddressBook Framework
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#ifndef __ABGROUP__
#define __ABGROUP__

#import <AddressBook/ABRecord.h>
#import <AddressBook/ABTypedefs.h>

@class ABPerson;
@class ABSearchElement;

// ================================================================================
//      interface ABGroup
// ================================================================================
// ABGroup is a subclass of ABRecord. It represents a group of people or other groups
// No recursions allowed

@interface ABGroup : ABRecord
{
@private
    id _groupReserved1 __unused;
    id _groupReserved2 __unused;
}

- (NSArray *)members;
    // Returns an array of ABPerson.
    // Returns an empty array if this group doesn't contain any people

- (BOOL)addMember:(ABPerson *)person;
    // Adds person to this group. Does nothing if person is already part of this group (returns NO)
    // Raises if person is nil
    // Returns YES if successful

- (BOOL)removeMember:(ABPerson *)person;
    // Removes person from this group. Does nothing if person is not part of this group (returns NO)
    // Raises if person is nil
    // Returns YES if successful

- (NSArray *)subgroups;
    // Returns an array of ABGroup
    // Returns an empty array if this group doesn't contain any other groups

- (BOOL)addSubgroup:(ABGroup *)group;
    // Add group to this group. Does nothing if group is already part of this group (returns NO)
    // Recursions are not allowed (returns NO)
    // Raises if group is nil
    // Returns YES if successful

- (BOOL)removeSubgroup:(ABGroup *)group;
    // Removes group from this group. Does nothing if group is not part of this group (returns NO)
    // Raises if group is nil
    // Returns YES if successful

- (NSArray *)parentGroups;
    // Returns an array of ABGroup this group belongs to.
    // Returns an empty array if this group doesn't belong to any groups.

- (BOOL)setDistributionIdentifier:(NSString *)identifier forProperty:(NSString *)property person:(ABPerson *)person;
    // Allows groups to be used as distribution lists (mailing list in the case of the email property)
    // Example: For group "Football team" I want to use John's home email and Paul's work email
    // The default distribution identifier is the property's primary identifier
    // Use nil for the identifer to reset the distribution identifier to the default (e.g. primary)
    // Raises if property or person is nil
    // Returns YES if successful

- (NSString *)distributionIdentifierForProperty:(NSString *)property person:(ABPerson *)person;
    // Returns the distribution identifier for a given property and person. If not set then returns the property primary identifier
    // Raises if property or person is nil
    // Returns the distribution identifier or nil if not successful
@end


// ================================================================================
//      interface ABGroup(ABGroup_Properties)
// ================================================================================
// This section deals with adding/removing properties on groups

@interface ABGroup (ABGroup_Properties)

+ (NSInteger)addPropertiesAndTypes:(NSDictionary *)properties;
    // Add properties to all groups. The dictionary must be of the form:
    //          key: propety name
    //          value: property type
    // Property name must be unique
    // Returns the number of properties successfuly added (-1 if an error occured)

+ (NSInteger)removeProperties:(NSArray *)properties;
    // Removes properties from all groups
    // Returns the number of properties successfuly removed (-1 if an error occured)

+ (NSArray *)properties;
    // Returns an array of property names

+ (ABPropertyType)typeOfProperty:(NSString*)property;
    // Returns the type of a given property.
    // Returns kABErrorInProperty if the property is not known

@end

// ================================================================================
//      interface ABGroup(ABGroup_Searching)
// ================================================================================
// This section deals with creating search elements to search groups

@interface ABGroup (ABGroup_Searching)
+ (ABSearchElement *)searchElementForProperty:(NSString*)property
                                        label:(NSString*)label
                                          key:(NSString*)key
                                        value:(id)value
                                   comparison:(ABSearchComparison)comparison;
    // Returns a search element that will search on groups
    //          property: the name of the property to search on (cannot be nil)
    //          label: for multi-value properties an optional label (can be nil)
    //          key: for dictionary values an optional key (can be nil)
    //          value: value to match (can be nil)
    //          comparison: the type of search (see ABTypedefs.h)
    //
    // if the value is nil the only supported comparisons are kABEqual or kABNotEqual
    // Note: Support for nil values was added to Mac OS X version 10.2.4
@end

#endif // __ABGROUP__
