/*
    NSFetchIndexElementDescription.h
    Core Data
    Copyright (c) 2017-2018, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>

@class NSPropertyDescription;
@class NSFetchIndexDescription;


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSFetchIndexElementType) {
    NSFetchIndexElementTypeBinary,
    NSFetchIndexElementTypeRTree,
} API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSFetchIndexElementDescription : NSObject <NSCoding> {
#if (!__OBJC2__)
@private
    NSPropertyDescription *_property;
    NSString *_propertyName;
    NSFetchIndexElementType _collationType;
    NSFetchIndexDescription *_indexDescription;
    struct __indexElementDescriptionFlags {
        unsigned int _ascending:1;
        unsigned int _propertyIsRetained:1;
        unsigned int _unique:1;
        unsigned int _reservedEntityDescription:29;
    } _indexElementDescriptionFlags;
#endif
}

- (instancetype)initWithProperty:(NSPropertyDescription*)property collationType:(NSFetchIndexElementType)collationType;

/* This may be an NSExpressionDescription that expresses a function */
@property (readonly, nullable, retain) NSPropertyDescription *property;
@property (readonly, nullable, retain) NSString *propertyName;
/* Default NSIndexTypeBinary */
@property NSFetchIndexElementType collationType;
/* Default YES. Control whether this is an ascending or descending index for indexes which support direction. */

@property (getter=isAscending) BOOL ascending;

@property (readonly, nonatomic, nullable, assign) NSFetchIndexDescription *indexDescription;

@end

NS_ASSUME_NONNULL_END
