//
//  INMediaSearch.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INMediaItemType.h>
#import <Intents/INMediaReference.h>
#import <Intents/INMediaSortOrder.h>

@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INMediaSearch : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithMediaType:(INMediaItemType)mediaType
                        sortOrder:(INMediaSortOrder)sortOrder
                        mediaName:(nullable NSString *)mediaName
                       artistName:(nullable NSString *)artistName
                        albumName:(nullable NSString *)albumName
                       genreNames:(nullable NSArray<NSString *> *)genreNames
                        moodNames:(nullable NSArray<NSString *> *)moodNames
                      releaseDate:(nullable INDateComponentsRange *)releaseDate
                        reference:(INMediaReference)reference
                  mediaIdentifier:(nullable NSString *)mediaIdentifier NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaItemType mediaType;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaSortOrder sortOrder;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *mediaName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *artistName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *albumName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *genreNames;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *moodNames;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *releaseDate;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaReference reference;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *mediaIdentifier;

@end

NS_ASSUME_NONNULL_END
