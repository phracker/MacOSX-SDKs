/*
    NSPropertyDescription.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>

@class NSArray;
@class NSDictionary;
@class NSEntityDescription;
@class NSMutableArray;
@class NSMutableDictionary;
@class NSString;

// Properties describe values within a managed object. There are different types of properties, each of them represented by a subclass which encapsulates the specific property behavior.
@interface NSPropertyDescription : NSObject <NSCoding, NSCopying> {
@private
	void *_reserved;
	void *_reserved2;
	void *_reserved3;
	void *_reserved4;
    NSEntityDescription *_entity;
    NSString *_name;
    NSArray *_validationPredicates;
    NSArray *_validationWarnings;
    struct __propertyDescriptionFlags {
        unsigned int _isReadOnly:1;
        unsigned int _isTransient:1;
        unsigned int _isOptional:1;
        unsigned int _reservedPropertyDescription:29;
    } _propertyDescriptionFlags;    
    NSMutableDictionary *_mappings;
    NSMutableDictionary *_userInfo;
}

- (NSEntityDescription *)entity;

- (NSString *)name;
- (void)setName:(NSString *)name;

// The optional flag specifies whether a property's value can be nil or not (before an object can be persisted).
- (BOOL)isOptional;
- (void)setOptional:(BOOL)flag;

// The transient flag specifies whether a property's value is persisted or ignored when an object is persisted - transient properties are still managed for undo/redo, validation, etc.
- (BOOL)isTransient;
- (void)setTransient:(BOOL)flag;

// Instead of individual methods to set/get parameters like length, min and max values, formats, etc., there is a list of predicates evaluated against the managed objects and corresponding error messages (which can be localized).
- (NSArray *)validationPredicates;
- (NSArray *)validationWarnings;
- (void)setValidationPredicates:(NSArray *)validationPredicates withValidationWarnings:(NSArray *)validationWarnings;

- (NSDictionary *)userInfo;
- (void)setUserInfo:(NSDictionary *)dictionary;

@end

#endif
