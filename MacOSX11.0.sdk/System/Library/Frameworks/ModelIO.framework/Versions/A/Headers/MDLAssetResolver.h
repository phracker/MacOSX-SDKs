/*!
 @header MDLAssetResolver.h
 @framework ModelIO
 @abstract Structures for representing contents of 3d model files
 @copyright Copyright © 2017 Apple, Inc. All rights reserved.
 */

#import <ModelIO/ModelIOExports.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@protocol MDLAssetResolver <NSObject>

- (BOOL)canResolveAssetNamed:(NSString*)name;
- (NSURL*)resolveAssetNamed:(NSString*)name;

@end

@class MDLAsset;

/*!
 @class MDLRelativeAssetResolver
 
 @abstract The relative asset resolver searches for referenced files
 by checking the location of the asset for sibling files
 satisfying the requested name.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLRelativeAssetResolver : NSObject <MDLAssetResolver>

- (instancetype)initWithAsset:(MDLAsset*)asset;

@property (nonatomic, readwrite, weak) MDLAsset *asset;

@end

/*!
 @class MDLPathAssetResolver
 
 @abstract The path asset resolver searches for referenced files
 by prepending path.
 
 @discussion Path should resolve to a well formed URI. A file system
 path might take the form @"file:///path/to/all/assets/
 
 A trailing slash is automatically appended to path if
 not provided.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLPathAssetResolver : NSObject <MDLAssetResolver>

- (instancetype)initWithPath:(NSString*)path;

@property (nonatomic, readwrite, copy) NSString *path;

@end


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLBundleAssetResolver : NSObject <MDLAssetResolver>

- (instancetype)initWithBundle:(NSString*)path;

@property (nonatomic, readwrite, copy) NSString *path;

@end

NS_ASSUME_NONNULL_END
