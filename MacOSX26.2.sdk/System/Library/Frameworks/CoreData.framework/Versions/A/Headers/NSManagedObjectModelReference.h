/*
    NSManagedObjectModelReference.h
    Core Data
    Copyright (c) 2023-2025, Apple Inc.
    All rights reserved.
*/

#import <CoreData/NSManagedObjectModel.h>
#import <Foundation/NSBundle.h>
#import <Foundation/NSData.h>
#import <Foundation/NSString.h>
#import <Foundation/NSURL.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * NSManagedObjectModelReference represents a promise of an NSManagedObjectMOdel. During migration Core Data
 * will fulfill this promise. Every NSManagedObjectModelReference instance requires to be initialized with a
 * "version checksum". This is to validate the model hasn't changed. The checksum can be obtained from
 * the NSManagedObjectModel's versionChecksum property. Alternatively it can be retrieved from the Xcode build
 * log or a versioned model's VersionInfo.plist.
 */
API_AVAILABLE(macosx(14.0),ios(17.0),tvos(17.0),watchos(10.0))
@interface NSManagedObjectModelReference : NSObject

@property (readonly, strong) NSManagedObjectModel *resolvedModel;
@property (readonly, strong) NSString *versionChecksum;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithModel:(NSManagedObjectModel *)model
              versionChecksum:(NSString *)versionChecksum;
- (instancetype)initWithFileURL:(NSURL *)fileURL
                versionChecksum:(NSString *)versionChecksum;
- (instancetype)initWithEntityVersionHashes:(NSDictionary *)versionHash
                                   inBundle:(nullable NSBundle *)bundle
                            versionChecksum:(NSString *)versionChecksum;
- (instancetype)initWithName:(NSString *)modelName
                    inBundle:(nullable NSBundle *)bundle
             versionChecksum:(NSString *)versionChecksum;

@end

NS_ASSUME_NONNULL_END
