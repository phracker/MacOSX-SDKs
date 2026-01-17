//
//  INMediaItem.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INMediaItemType.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INMediaItem : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                             title:(nullable NSString *)title
                              type:(INMediaItemType)type
                           artwork:(nullable INImage *)artwork
                            artist:(nullable NSString *)artist NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(13.0), watchos(6.0));

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                             title:(nullable NSString *)title
                              type:(INMediaItemType)type
                           artwork:(nullable INImage *)artwork;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *title;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaItemType type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *artwork;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *artist API_AVAILABLE(ios(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END
