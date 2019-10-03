//
//  CXProviderConfiguration.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXProviderConfiguration : NSObject <NSCopying>

/// Localized name of the provider
@property (nonatomic, readonly, copy) NSString *localizedName;

/// Name of resource in app's bundle to play as ringtone for incoming call
@property (nonatomic, strong, nullable) NSString *ringtoneSound;

@property (nonatomic, copy, nullable) NSData *iconTemplateImageData; // Image should be a square with side length of 40 points
@property (nonatomic) NSUInteger maximumCallGroups; // Default 2
@property (nonatomic) NSUInteger maximumCallsPerCallGroup; // Default 5

/// Whether this provider's calls should be included in the system's Recents list at the end of each call.
/// Default: YES
@property (nonatomic) BOOL includesCallsInRecents API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE(macos, watchos);

@property (nonatomic) BOOL supportsVideo; // Default NO

// Numbers are of type CXHandleType
@property (nonatomic, copy) NSSet<NSNumber *> *supportedHandleTypes;

- (instancetype)initWithLocalizedName:(NSString *)localizedName NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
