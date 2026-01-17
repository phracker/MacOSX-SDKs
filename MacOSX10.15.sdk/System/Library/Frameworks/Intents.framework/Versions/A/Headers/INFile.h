//
//  INFile.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Intents/INObject.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INFile : NSObject

+ (INFile *)fileWithData:(NSData *)data filename:(NSString *)filename typeIdentifier:(nullable NSString *)typeIdentifier;
+ (INFile *)fileWithFileURL:(NSURL *)fileURL filename:(nullable NSString *)filename typeIdentifier:(nullable NSString *)typeIdentifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSData *data;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *filename;
@property (nullable, readonly, copy, NS_NONATOMIC_IOSONLY) NSString *typeIdentifier;
@property (nullable, readonly, strong, NS_NONATOMIC_IOSONLY) NSURL *fileURL;

@end

NS_ASSUME_NONNULL_END
