//
//  PHPersistentObjectChangeDetails.h
//  Photos
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class PHObject;

API_AVAILABLE(macosx(13), ios(16), tvos(16))
NS_SWIFT_SENDABLE
@interface PHPersistentObjectChangeDetails : NSObject

@property (nonatomic, readonly) PHObjectType objectType;

@property (nonatomic, strong, readonly) NSSet<NSString *> *insertedLocalIdentifiers;
@property (nonatomic, strong, readonly) NSSet<NSString *> *updatedLocalIdentifiers;
@property (nonatomic, strong, readonly) NSSet<NSString *> *deletedLocalIdentifiers;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
