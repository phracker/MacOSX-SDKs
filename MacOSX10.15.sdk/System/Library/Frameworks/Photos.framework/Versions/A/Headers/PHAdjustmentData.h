//
//  PHAdjustmentData.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.11), ios(8), tvos(10))

OS_EXPORT
@interface PHAdjustmentData : NSObject

- (instancetype)initWithFormatIdentifier:(NSString *)formatIdentifier formatVersion:(NSString *)formatVersion data:(NSData *)data;

// Used to identify the format of the data blob (e.g. identifier "com.apple.myapp" and version "1.0")
@property (readonly, copy) NSString *formatIdentifier;
@property (readonly, copy) NSString *formatVersion;

// Binary blob that describes the adjustments applied to the asset.
@property (readonly, strong) NSData *data;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
