//
//  PHPersistentChange.h
//  Photos
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class PHPersistentChangeToken;
@class PHPersistentObjectChangeDetails;

API_AVAILABLE(macosx(13), ios(16), tvos(16))
NS_SWIFT_SENDABLE
@interface PHPersistentChange : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) PHPersistentChangeToken *changeToken;

- (nullable PHPersistentObjectChangeDetails *)changeDetailsForObjectType:(PHObjectType)objectType error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
