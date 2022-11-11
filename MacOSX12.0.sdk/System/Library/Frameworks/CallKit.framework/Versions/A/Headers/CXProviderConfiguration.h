//
//  CXProviderConfiguration.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), macos(11.0))  API_UNAVAILABLE(watchos, tvos)
@interface CXProviderConfiguration : NSObject <NSCopying>

/// Localized name of the provider
@property (nonatomic, readonly, copy, nullable) NSString *localizedName API_DEPRECATED("No longer supported", ios(10.0, 14.0), macCatalyst(13.0, 14.0), macos(11.0, 11.0)) API_UNAVAILABLE(tvos, watchos);

/// Name of resource in app's bundle to play as ringtone for incoming call
@property (nonatomic, strong, nullable) NSString *ringtoneSound;

@property (nonatomic, copy, nullable) NSData *iconTemplateImageData; // Image should be a square with side length of 40 points
@property (nonatomic) NSUInteger maximumCallGroups; // Default 2
@property (nonatomic) NSUInteger maximumCallsPerCallGroup; // Default 5

/// Whether this provider's calls should be included in the system's Recents list at the end of each call.
/// Default: YES
@property (nonatomic) BOOL includesCallsInRecents API_AVAILABLE(ios(11.0), macCatalyst(13.0), macos(11.0)) API_UNAVAILABLE(watchos);

@property (nonatomic) BOOL supportsVideo; // Default NO

// Numbers are of type CXHandleType
@property (nonatomic, copy) NSSet<NSNumber *> *supportedHandleTypes;

- (instancetype)init NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(14.0), macCatalyst(14.0), macos(11.0))  API_UNAVAILABLE(watchos, tvos);
- (instancetype)initWithLocalizedName:(NSString *)localizedName API_DEPRECATED_WITH_REPLACEMENT("init", ios(10.0, 14.0), macCatalyst(13.0, 14.0), macos(11.0, 11.0)) API_UNAVAILABLE(tvos, watchos);


@end

NS_ASSUME_NONNULL_END
