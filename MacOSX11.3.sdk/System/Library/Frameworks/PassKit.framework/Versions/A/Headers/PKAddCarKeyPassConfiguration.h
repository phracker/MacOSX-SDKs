//
//  PKAddCarKeyPassConfiguration.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKAddSecureElementPassConfiguration.h>
#import <PassKit/PKConstants.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddCarKeyPassConfiguration : PKAddSecureElementPassConfiguration

- (instancetype)init;

@property (nonatomic, copy) NSString *password;
@property (nonatomic, assign) PKRadioTechnology supportedRadioTechnologies API_AVAILABLE(ios(14.5), watchos(7.3));

@end

NS_ASSUME_NONNULL_END
