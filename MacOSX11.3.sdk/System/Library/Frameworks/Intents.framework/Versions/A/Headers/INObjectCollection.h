//
//  INObjectCollection.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INObjectSection.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0))
API_UNAVAILABLE(tvos)
@interface INObjectCollection<ObjectType> : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, copy, readonly) NSArray<INObjectSection<ObjectType> *> *sections;
@property (nonatomic, copy, readonly) NSArray<ObjectType> *allItems;
@property (nonatomic) BOOL usesIndexedCollation;

- (instancetype)initWithSections:(NSArray<INObjectSection<ObjectType> *> *)sections NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithItems:(NSArray<ObjectType> *)items;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
