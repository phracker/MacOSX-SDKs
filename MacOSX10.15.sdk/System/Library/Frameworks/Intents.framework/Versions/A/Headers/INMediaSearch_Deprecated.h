//
//  INMediaSearch_Deprecated.h
//  Intents
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Intents/INMediaSearch.h>

NS_ASSUME_NONNULL_BEGIN

@interface INMediaSearch (Deprecated)

- (instancetype)initWithMediaType:(INMediaItemType)mediaType
                        sortOrder:(INMediaSortOrder)sortOrder
                        mediaName:(nullable NSString *)mediaName
                       artistName:(nullable NSString *)artistName
                        albumName:(nullable NSString *)albumName
                       genreNames:(nullable NSArray<NSString *> *)genreNames
                        moodNames:(nullable NSArray<NSString *> *)moodNames
                    activityNames:(nullable NSArray<NSString *> *)activityNames
                      releaseDate:(nullable INDateComponentsRange *)releaseDate
                        reference:(INMediaReference)reference
                  mediaIdentifier:(nullable NSString *)mediaIdentifier NS_REFINED_FOR_SWIFT API_DEPRECATED("Use the designated initializer instead", ios(13.0, 13.0), watchos(6.0, 6.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *activityNames API_DEPRECATED("Use `moodNames` property instead.", ios(13.0, 13.0), watchos(6.0, 6.0));

@end

NS_ASSUME_NONNULL_END
