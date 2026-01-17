//
//  PHCollection.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//
//

#import <Photos/PHObject.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, 8_0) @interface PHCollection : PHObject
@property (nonatomic, strong, readonly, nullable) NSString *localizedTitle;

@end


NS_CLASS_AVAILABLE(10_13, 8_0) @interface PHAssetCollection : PHCollection

@end

NS_CLASS_AVAILABLE(10_13, 8_0) @interface PHCollectionList : PHCollection

@end

NS_ASSUME_NONNULL_END
