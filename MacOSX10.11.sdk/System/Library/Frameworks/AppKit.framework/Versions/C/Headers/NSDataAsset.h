/*
	NSDataAsset.h
	Application Kit
	Copyright (c) 2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/* An NSDataAsset instance provides access to a data entry in an asset catalog such as Images.xcassets. Data entries and image entries in asset catalogs do not share the same namespace. For example, if an asset catalog contains an image entry named @"foo" but no data entry named @"foo", [[NSDataAsset alloc] initWithName:@"foo"] will return nil.
*/

NS_CLASS_AVAILABLE_MAC(10_11) @interface NSDataAsset : NSObject<NSCopying> {
    void *_namedData;
}

- (instancetype)init NS_UNAVAILABLE;

/// Equivalent to -initWithName:name bundle:[NSBundle mainBundle];
- (nullable instancetype)initWithName:(NSString *)name;
/// Create a data asset with the given name from the given bundle. Returns nil if the asset was not found.
- (nullable instancetype)initWithName:(NSString *)name bundle:(NSBundle *)bundle NS_DESIGNATED_INITIALIZER;

/// The name used to reference the data asset
@property (readonly, copy) NSString *name;
/// The data for this asset, as stored in the asset catalog
@property (readonly, copy) NSData *data;
/// The Uniform Type Identifier for this data object.
@property (readonly, copy) NSString *typeIdentifier;

@end

NS_ASSUME_NONNULL_END
