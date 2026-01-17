//
//  INMediaItem.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INMediaItemType.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0))
API_UNAVAILABLE(macosx)
@interface INMediaItem : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                             title:(nullable NSString *)title
                              type:(INMediaItemType)type
                           artwork:(nullable INImage *)artwork NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *title;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaItemType type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *artwork;

@end

NS_ASSUME_NONNULL_END
