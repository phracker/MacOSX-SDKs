/*
 File: ASIdentifierManager.h
 
 Framework: AdSupport
 
 Copyright (c) 2012, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(6), macosx(10.14), tvos(6))
@interface ASIdentifierManager : NSObject

+ (ASIdentifierManager *)sharedManager;

@property (nonatomic, readonly) NSUUID *advertisingIdentifier;
@property (nonatomic, readonly, getter=isAdvertisingTrackingEnabled) BOOL advertisingTrackingEnabled API_DEPRECATED("This has been replaced by functionality in AppTrackingTransparency's ATTrackingManager class.", ios(6, 14), macosx(10.14, 11.0), tvos(6, 14));

- (void)clearAdvertisingIdentifier API_UNAVAILABLE(ios, macos, tvos);

@end

NS_ASSUME_NONNULL_END
