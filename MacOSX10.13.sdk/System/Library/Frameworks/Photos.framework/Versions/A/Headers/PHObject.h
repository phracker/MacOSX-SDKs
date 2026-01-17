//
//  PHObject.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PHPhotoLibrary;


NS_CLASS_AVAILABLE(10_13, 8_0) @interface PHObject : NSObject <NSCopying>

// Returns an identifier which persistently identifies the object on a given device
@property (nonatomic, copy, readonly) NSString *localIdentifier;

@end

NS_ASSUME_NONNULL_END
