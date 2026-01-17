/*
    NSCompositeAttributeDescription.h
    Core Data
    Copyright (c) 2023-2025, Apple Inc.
    All rights reserved.
*/

#import <CoreData/NSAttributeDescription.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(14.0), ios(17.0), tvos(17.0), watchos(10.0))
@interface NSCompositeAttributeDescription : NSAttributeDescription {
}

/*  Elements expects an Attribute or an Array of Attributes
    Will throw if the new value is invalid (ie includes NSRelationshipDescription).
*/
@property (copy) NSArray<__kindof NSAttributeDescription *> *elements;

@end

NS_ASSUME_NONNULL_END
