/*
    NSRelationshipDescription.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <CoreData/NSPropertyDescription.h>

@class NSEntityDescription;

typedef enum {
    NSNoActionDeleteRule,
    NSNullifyDeleteRule,
    NSCascadeDeleteRule,
    NSDenyDeleteRule
} NSDeleteRule;

// Relationships represent references to other objects. They usually come in pairs, where the reference back is called the "inverse".
@interface NSRelationshipDescription : NSPropertyDescription {
@private
	void *_reserved5;
	void *_reserved6;
    NSEntityDescription *_destinationEntity;
    NSString *_lazyDestinationEntityName;
    NSRelationshipDescription *_inverseRelationship;
    NSString *_lazyInverseRelationshipName;
    unsigned int _maxCount;
    unsigned int _minCount;
    NSDeleteRule _deleteRule;
}

- (NSEntityDescription *)destinationEntity;
- (void)setDestinationEntity:(NSEntityDescription *)entity;
- (NSRelationshipDescription *)inverseRelationship;
- (void)setInverseRelationship:(NSRelationshipDescription *)relationship;

// Min and max count indicate the number of objects referenced (1/1 for a to-one relationship, 0 for the max count means undefined) - note that the counts are only enforced if the relationship value is not nil/"empty" (so as long as the relationship value is optional, there might be zero objects in the relationship, which might be less than the min count)
- (unsigned int)maxCount;
- (void)setMaxCount:(unsigned int)maxCount;
- (unsigned int)minCount;
- (void)setMinCount:(unsigned int)minCount;

- (NSDeleteRule)deleteRule;
- (void)setDeleteRule:(NSDeleteRule)rule;

- (BOOL)isToMany;    // convenience method to test whether the relationship is to-one or to-many

@end

#endif
