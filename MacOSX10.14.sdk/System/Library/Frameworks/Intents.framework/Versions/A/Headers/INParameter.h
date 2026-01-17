//
//  INParameter.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INInteraction.h>

@class INParameter;

NS_ASSUME_NONNULL_BEGIN

@interface INInteraction ()

- (nullable id)parameterValueForParameter:(INParameter *)parameter API_AVAILABLE(ios(11.0));

@end

API_AVAILABLE(ios(11.0))
@interface INParameter : NSObject <NSSecureCoding, NSCopying>

+ (instancetype)parameterForClass:(Class)aClass keyPath:(NSString *)keyPath;

@property (nonatomic, readonly) Class parameterClass;
@property (nonatomic, copy, readonly) NSString *parameterKeyPath;

- (BOOL)isEqualToParameter:(INParameter *)parameter;

- (void)setIndex:(NSUInteger)index forSubKeyPath:(NSString *)subKeyPath;
- (NSUInteger)indexForSubKeyPath:(NSString *)subKeyPath;

@end

NS_ASSUME_NONNULL_END
