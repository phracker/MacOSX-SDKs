//
//  CPTripPreviewTextConfiguration.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTripPreviewTextConfiguration : NSObject <NSSecureCoding>

- (instancetype)initWithStartButtonTitle:(nullable NSString *)startButtonTitle
             additionalRoutesButtonTitle:(nullable NSString *)additionalRoutesButtonTitle
                     overviewButtonTitle:(nullable NSString *)overviewButtonTitle;

@property (nonatomic, copy, readonly, nullable) NSString *startButtonTitle;
@property (nonatomic, copy, readonly, nullable) NSString *additionalRoutesButtonTitle;
@property (nonatomic, copy, readonly, nullable) NSString *overviewButtonTitle;

@end

NS_ASSUME_NONNULL_END
