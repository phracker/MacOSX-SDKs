//
//  INFile.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INObject.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object that describes a piece of data and its associated name and uniform type identifier.
 This data can either be stored in a file on disk, or in memory.
 */
API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INFile : NSObject <NSSecureCoding>

+ (INFile *)fileWithData:(NSData *)data filename:(NSString *)filename typeIdentifier:(nullable NSString *)typeIdentifier;
+ (INFile *)fileWithFileURL:(NSURL *)fileURL filename:(nullable NSString *)filename typeIdentifier:(nullable NSString *)typeIdentifier;

/**
 The contents of the file.
 If the file was created with a URL, accessing this property will memory map the file contents.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSData *data;

/**
 The human-readable name of the file, which will be displayed to the user.
 */
@property (copy, NS_NONATOMIC_IOSONLY) NSString *filename;

/**
 The uniform type identifier of the file. (i.e. "public.json", "public.png", or any custom type)
 More information about uniform type identifiers can be found in <CoreServices/UTCoreTypes.h>
 */
@property (nullable, readonly, copy, NS_NONATOMIC_IOSONLY) NSString *typeIdentifier;

/**
 URL to the file on disk, if any.
 If the file isn't stored on disk, access the contents using the `data` property.
 
 If the file was created elsewhere on the system, make sure to surround access to file contents
 with `-[NSURL startAccessingSecurityScopedResource]` and `-[NSURL stopAccessingSecurityScopedResource]`.
 */
@property (nullable, readonly, strong, NS_NONATOMIC_IOSONLY) NSURL *fileURL;

@end

NS_ASSUME_NONNULL_END
