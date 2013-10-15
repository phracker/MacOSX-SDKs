/*
    NSAttributeDescription.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <CoreData/NSPropertyDescription.h>

@class NSEntityDescription;
@class NSString;

// types explicitly distinguish between bit sizes to ensure data store independence of the underlying operating system
typedef enum {
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
} NSAttributeType;

// Attributes represent individual values like strings, numbers, dates, etc.
@interface NSAttributeDescription : NSPropertyDescription {
@private
	void *_reserved5;
	void *_reserved6;
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

@end

#endif
