/*
    NSAtomicStoreCacheNode.h
    Core Data
    Copyright (c) 2004-2010 Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreData/NSEntityDescription.h>
#import <CoreData/NSManagedObjectID.h>
#import <CoreData/NSManagedObject.h>

NS_CLASS_AVAILABLE(10_5,3_0)
@interface NSAtomicStoreCacheNode : NSObject {
    @private
    NSManagedObjectID *_objectID;
    uintptr_t __versionNumber;
	NSMutableDictionary *_propertyCache;
	void *_reserved1;
}

/* The designated initializer for the cache node. */
- (id)initWithObjectID:(NSManagedObjectID *)moid;

/* Returns the managed object ID for the cache node. */
- (NSManagedObjectID*)objectID;

/* Returns the property cache dictionary for the cache node.  This dictionary is used by -valueForKey: and -setValue:forKey: for property values.  The default implementation will return nil unless the companion -setPropertyCache: method is invoked, or -setValue:forKey: is invoked on the cache node with non-nil property values.
*/
- (NSMutableDictionary *)propertyCache;

/* Sets the property cache dictionary for the cache node.
*/
- (void)setPropertyCache:(NSMutableDictionary *)propertyCache;


/* Returns the value for the specified key.  Subclasses must return the appropriate object value for all property keys (as specified by the names of the NSPropertyDescriptions for the entity of this cache node.)  For attributes, these are instances of NSObject; for to-one relationships, the return value must be another cache node instance; for a to-many relationship, the return value must be an NSSet of the related cache nodes.  

The default implementation forwards the request to the -propertyCache dictionary if the key matches a property name of the entity for the cache node.  If the key does not represent a property, the standard -valueForKey: implementation will be used.
*/
- (id)valueForKey:(NSString*)key;

/* Sets the value for the specified key.  The default implementation forwards the request to the -propertyCache dictionary if the key matches a property name of the entity for this cache node.  If the key does not represent a  property, the standard -setValue:forKey: implementation will be used. 
*/
- (void)setValue:(id)value forKey:(NSString*)key;

@end
