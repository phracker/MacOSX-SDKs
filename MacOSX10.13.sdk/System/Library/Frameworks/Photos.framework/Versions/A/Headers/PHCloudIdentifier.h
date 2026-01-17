//
//  PHCloudIdentifier.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Photos/PHPhotoLibrary.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, NA) @interface PHCloudIdentifier : NSObject <NSSecureCoding>

/// If there is a failure to determine the global identifier for a local identifier, the notFoundIdentifier is provided in that array slot.
@property (class, nonatomic, readonly) PHCloudIdentifier *notFoundIdentifier;

@property (nonatomic, readonly) NSString *stringValue; /// For use in serialization

- (instancetype)initWithStringValue:(NSString *)stringValue; /// Deserialization

@end

@interface PHPhotoLibrary (CloudIdentifiers)

/// These two methods can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.
- (NSArray<NSString *> *)localIdentifiersForCloudIdentifiers:(NSArray<PHCloudIdentifier *> *)cloudIdentifiers API_AVAILABLE(macos(10.13));
- (NSArray<PHCloudIdentifier *> *)cloudIdentifiersForLocalIdentifiers:(NSArray<NSString *> *)localIdentifiers API_AVAILABLE(macos(10.13));

@end

/// If the local object cannot be resolved from a global identifier, PHLocalIdentifierNotFound is provided in that array slot.
extern NSString * const PHLocalIdentifierNotFound API_AVAILABLE(macos(10.13));

NS_ASSUME_NONNULL_END
