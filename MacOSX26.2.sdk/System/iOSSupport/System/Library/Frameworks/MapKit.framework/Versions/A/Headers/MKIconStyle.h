//
//  MKIconStyle.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MKIconStyle : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) UIColor *backgroundColor;
@property (nonatomic, readonly) UIImage *image;

@end

NS_ASSUME_NONNULL_END
