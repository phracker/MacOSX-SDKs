//
//  CPImageSet.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)

@interface CPImageSet : NSObject <NSSecureCoding>

- (instancetype)initWithLightContentImage:(UIImage *)lightImage darkContentImage:(UIImage *)darkImage;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) UIImage *lightContentImage;
@property (nonatomic, readonly) UIImage *darkContentImage;

@end

NS_ASSUME_NONNULL_END
