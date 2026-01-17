//
//  PHAdjustmentData.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_11) @interface PHAdjustmentData : NSObject

- (instancetype)initWithFormatIdentifier:(NSString *)formatIdentifier formatVersion:(NSString *)formatVersion data:(NSData *)data;

// Used to identify the format of the data blob (e.g. identifier "com.apple.myapp" and version "1.0")
@property (readonly, copy) NSString *formatIdentifier;
@property (readonly, copy) NSString *formatVersion;

// Binary blob that describes the adjustments applied to the asset.
@property (readonly, strong) NSData *data;

@end

NS_ASSUME_NONNULL_END