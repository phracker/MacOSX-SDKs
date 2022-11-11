//
//  PHObject.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

@class PHPhotoLibrary;


OS_EXPORT
@interface PHObject : NSObject <NSCopying>

// Returns an identifier which persistently identifies the object on a given device
@property (nonatomic, copy, readonly) NSString *localIdentifier;

@end

// PHObjectPlaceholder represents a model object future , vended by change requests when creating a model object.  PHObjectPlaceholder is a read-only object and may be used as a proxy for the real object that will be created both inside and outside of the change block.  Will compare isEqual: to the fetched model object after the change block is performed.
OS_EXPORT API_AVAILABLE(macos(10.15))
@interface PHObjectPlaceholder : PHObject
@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
