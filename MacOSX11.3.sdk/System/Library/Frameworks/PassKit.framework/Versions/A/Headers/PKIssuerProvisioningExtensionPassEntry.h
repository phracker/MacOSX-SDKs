//
//  PKIssuerProvisioningExtensionPassEntry.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKIssuerProvisioningExtensionPassEntry : NSObject

- (nullable instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) CGImageRef art NS_RETURNS_INNER_POINTER CF_RETURNS_NOT_RETAINED;

@end

NS_ASSUME_NONNULL_END
