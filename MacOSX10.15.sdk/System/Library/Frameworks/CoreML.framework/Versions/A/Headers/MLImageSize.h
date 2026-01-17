//
//  MLImageSize.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLImageSize : NSObject <NSSecureCoding>

@property (readonly) NSInteger pixelsWide;

@property (readonly) NSInteger pixelsHigh;

@end

NS_ASSUME_NONNULL_END
