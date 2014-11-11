/*
    NSAttributeDescription.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <CoreData/NSPropertyDescription.h>

@class NSEntityDescription;

// types explicitly distinguish between bit sizes to ensure data store independence of the underlying operating system


typedef NS_ENUM(NSUInteger, NSAttributeType) {
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
    NSBinaryDataAttributeType = 1000,
    NSTransformableAttributeType NS_ENUM_AVAILABLE(10_5,3_0) = 1800, // If your attribute is of NSTransformableAttributeType, the attributeValueClassName must be set or attribute value class must implement NSCopying.
    NSObjectIDAttributeType NS_ENUM_AVAILABLE(10_6,3_0) = 2000
 };

// Attributes represent individual values like strings, numbers, dates, etc.
NS_CLASS_AVAILABLE(10_4,3_0)
@interface NSAttributeDescription : NSPropertyDescription {
@private
	Class _attributeValueClass;
	NSString *_valueTransformerName;
    NSAttributeType _type;
    NSString *_attributeValueClassName;
    struct __attributeDescriptionFlags {
		unsigned int _hasMaxValueInExtraIvars:1;
		unsigned int _hasMinValueInExtraIvars:1;
		unsigned int _storeBinaryDataExternally:1;
        unsigned int _reservedAttributeDescription:29;
    } _attributeDescriptionFlags;
    id _defaultValue;
}

// NSUndefinedAttributeType is valid for transient properties - Core Data will still track the property as an id value and register undo/redo actions, etc. NSUndefinedAttributeType is illegal for non-transient properties.
@property () NSAttributeType attributeType;

@property (copy) NSString *attributeValueClassName;

@property (retain) id defaultValue;   // value is retained and not copied

/* Returns the version hash for the attribute.  This value includes the versionHash information from the NSPropertyDescription superclass, and the attribute type.*/
@property (readonly, copy) NSData *versionHash NS_AVAILABLE(10_5,3_0);

/* The name of the transformer used to convert a NSTransformedAttributeType.  The transformer must output NSData from transformValue and allow reverse transformation.  If this value is not set, or set to nil, Core Data will default to using a transformer which uses NSCoding to archive/unarchive the attribute value.*/
@property (copy) NSString *valueTransformerName NS_AVAILABLE(10_5,3_0);

@property () BOOL allowsExternalBinaryDataStorage NS_AVAILABLE(10_7, 5_0);

@end
