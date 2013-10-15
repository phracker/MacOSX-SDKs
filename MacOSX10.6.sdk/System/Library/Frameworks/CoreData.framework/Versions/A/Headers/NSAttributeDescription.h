/*
    NSAttributeDescription.h
    Core Data
    Copyright (c) 2004-2009 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <CoreData/NSPropertyDescription.h>

@class NSEntityDescription;
@class NSString;

// types explicitly distinguish between bit sizes to ensure data store independence of the underlying operating system
 enum {
    NSUndefinedAttributeType = 0,
    NSInteger16AttributeType = 100,
    NSInteger32AttributeType = 200,
    NSInteger64AttributeType = 300,
    NSDecimalAttributeType = 400,
    NSDoubleAttributeType = 500,
    NSFloatAttributeType = 600,
    NSStringAttributeType = 700,
    NSBooleanAttributeType = 800,
    NSDateAttributeType = 900,
    NSBinaryDataAttributeType = 1000
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
    // If your attribute is of NSTransformableAttributeType, the attributeValueClassName 
    // must be set or attribute value class must implement NSCopying.
    , NSTransformableAttributeType = 1800    
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
	 , NSObjectIDAttributeType = 2000    
#endif
 };

typedef NSUInteger NSAttributeType;

// Attributes represent individual values like strings, numbers, dates, etc.
@interface NSAttributeDescription : NSPropertyDescription {
@private
	Class _attributeValueClass;
	NSString *_valueTransformerName;
    NSAttributeType _type;
    NSString *_attributeValueClassName;
    struct __attributeDescriptionFlags {
        unsigned int _useForLocking:1;
        unsigned int _reservedAttributeDescription:31;
    } _attributeDescriptionFlags;
    id _defaultValue;
}

// NSUndefinedAttributeType is valid for transient properties - Core Data will still track the property as an id value and register undo/redo actions, etc. NSUndefinedAttributeType is illegal for non-transient properties.
- (NSAttributeType)attributeType;
- (void)setAttributeType:(NSAttributeType)type;

- (NSString *)attributeValueClassName;

- (id)defaultValue;
- (void)setDefaultValue:(id)value;    // value is retained and not copied

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Sets the value class for the attribute (when using transient properties.)
*/
- (void)setAttributeValueClassName:(NSString *)className;

/* Returns the version hash for the attribute.  This value includes the versionHash information from the NSPropertyDescription superclass, and the attribute type.
*/
- (NSData *)versionHash;

/* The name of the transformer used to convert a NSTransformedAttributeType.  The transformer must output NSData from transformValue and allow reverse transformation.  If this value is not set, or set to nil, Core Data will default to using a transformer which uses NSCoding to archive/unarchive the attribute value.
*/
- (NSString *)valueTransformerName;
- (void)setValueTransformerName:(NSString *)string;

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

@end

#endif
