//
//  PHProjectChangeRequest.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

@class PHProject;
@class PHAsset;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, NA)
@interface PHProjectChangeRequest : NSObject

- (instancetype)initWithProject:(PHProject *)project;

@property (nonatomic, copy, readwrite) NSString *title;

/**
 The projectExtensionData property is intended for storage of compressed, project specific data
 only. Do not include things like rasterized images that can be locally cached in this data. The
 total size of stored data is limited to 1 MB. Attempting to store more data than allowed will result
 in an error.
 */
@property (nonatomic, copy, readwrite) NSData *projectExtensionData;

- (void)setKeyAsset:(PHAsset * _Nullable)keyAsset;

@end

NS_ASSUME_NONNULL_END
