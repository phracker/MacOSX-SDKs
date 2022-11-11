//
//  PKAddSecureElementPassConfiguration.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddSecureElementPassConfiguration : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy, nullable) NSString *issuerIdentifier;
@property (nonatomic, copy, nullable) NSString *localizedDescription;

@end

NS_ASSUME_NONNULL_END

