//
//  INObjectSection.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0))
API_UNAVAILABLE(tvos)
@interface INObjectSection<ObjectType> : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, copy, readonly, nullable) NSString *title;
@property (nonatomic, copy, readonly) NSArray<ObjectType> *items;

- (instancetype)initWithTitle:(nullable NSString *)title items:(NSArray<ObjectType> *)items NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
