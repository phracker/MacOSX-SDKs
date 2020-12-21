//
//  PKAddCarKeyPassConfiguration.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <PassKit/PKAddSecureElementPassConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddCarKeyPassConfiguration : PKAddSecureElementPassConfiguration

- (instancetype)init;

@property (nonatomic, copy) NSString *password;

@end

NS_ASSUME_NONNULL_END
