//
//  INMessageLinkMetadata.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0))
API_UNAVAILABLE(tvos)
@interface INMessageLinkMetadata : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithSiteName:(nullable NSString *)siteName
                         summary:(nullable NSString *)summary
                           title:(nullable NSString *)title
                   openGraphType:(nullable NSString *)openGraphType
                         linkURL:(nullable NSURL *)linkURL NS_DESIGNATED_INITIALIZER;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *siteName;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *summary;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *title;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *openGraphType;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSURL *linkURL;

@end

NS_ASSUME_NONNULL_END
