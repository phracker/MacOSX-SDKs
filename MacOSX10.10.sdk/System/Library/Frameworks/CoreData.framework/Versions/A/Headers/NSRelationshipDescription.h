/*
    NSRelationshipDescription.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreData/NSPropertyDescription.h>

@class NSEntityDescription;



typedef NS_ENUM(NSUInteger, NSDeleteRule) {
    NSNoActionDeleteRule,
    NSNullifyDeleteRule,
    NSCascadeDeleteRule,
    NSDenyDeleteRule
} ;

// Relationships represent references to other objects. They usually come in pairs, where the reference back is called the "inverse".
NS_CLASS_AVAILABLE(10_4,3_0)
@interface NSRelationshipDescription : NSPropertyDescription {
@private
	void *_reserved5;
	void *_reserved6;
    __weak NSEntityDescription *_destinationEntity;
    NSString *_lazyDestinationEntityName;
    NSRelationshipDescription *_inverseRelationship;
    NSString *_lazyInverseRelationshipName;
    unsigned long _maxCount;
    unsigned long _minCount;
    NSDeleteRule _deleteRule;
}

@property (nonatomic, assign) NSEntityDescription *destinationEntity;
@property (nonatomic, assign) NSRelationshipDescription *inverseRelationship;

// Min and max count indicate the number of objects referenced (1/1 for a to-one relationship, 0 for the max count means undefined) - note that the counts are only enforced if the relationship value is not nil/"empty" (so as long as the relationship value is optional, there might be zero objects in the relationship, which might be less than the min count)
@property () NSUInteger maxCount;
@property () NSUInteger minCount;

@property () NSDeleteRule deleteRule;

@property (getter=isToMany, readonly) BOOL toMany;    // convenience method to test whether the relationship is to-one or to-many

// Returns the version hash for the relationship.  This value includes the versionHash information from the NSPropertyDescription superclass, the name of the destination entity and the inverse relationship, and the min and max count.
@property (readonly, copy) NSData *versionHash NS_AVAILABLE(10_5,3_0);

@property (getter=isOrdered) BOOL ordered NS_AVAILABLE(10_7,  5_0);

@end
