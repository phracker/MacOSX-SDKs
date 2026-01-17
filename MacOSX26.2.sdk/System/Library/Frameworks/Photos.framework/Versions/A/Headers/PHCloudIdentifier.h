//
//  PHCloudIdentifier.h
//  Photos
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <Photos/PHPhotoLibrary.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE_BEGIN(macos(10.13), ios(15), tvos(15))


OS_EXPORT
NS_SWIFT_SENDABLE
@interface PHCloudIdentifier : NSObject <NSSecureCoding>

/// DEPRECATED: If there is a failure to determine the global identifier for a local identifier, the notFoundIdentifier is provided in that array slot.
@property (class, nonatomic, readonly) PHCloudIdentifier *notFoundIdentifier

API_DEPRECATED_WITH_REPLACEMENT("Check for PHPhotosErrorIdentifierNotFound in PHCloudIdentifierMapping.error", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);


@property (nonatomic, readonly) NSString *stringValue; /// For use in serialization

- (instancetype)initWithStringValue:(NSString *)stringValue; /// Deserialization

@end

API_AVAILABLE_END
API_AVAILABLE_BEGIN(macos(12), ios(15), tvos(15))

/// Contains the cloud identifier result from looking up a local identifier via \c cloudIdentifierMappingsForLocalIdentifiers, or an \c error indicating why the lookup failed
OS_EXPORT NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface PHCloudIdentifierMapping : NSObject
@property (nonatomic, readonly, nullable) PHCloudIdentifier *cloudIdentifier; /// The cloud identifier of the resource found for this local identifier
@property (nonatomic, readonly, nullable) NSError *error; /// error An error indicating why the \c cloudIdentifier is nil. \c PHPhotosErrorIdentifierNotFound if no resource could be found for the provided local identifier.
@end

/// Contains the local identifier result from looking up a cloud identifier via \c localIdentifierMappingsForCloudIdentifiers, or an \c error indicating why the lookup failed
OS_EXPORT NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface PHLocalIdentifierMapping : NSObject
@property (nonatomic, readonly, nullable) NSString *localIdentifier; /// The \c NSString representing the local identifier of the resource found for this cloud identifier, or nil if the match was not found.
@property (nonatomic, readonly, nullable) NSError *error; /// An error indicating why the \c localIdentifier is nil. \c PHPhotosErrorIdentifierNotFound if no resource could be found for the provided cloud identifier. \c PHPhotosErrorMultipleLocalIdentifiersFound if the cloud identifier matched more than one photo library resource, so there were multiple local identifiers found. The array of matching local identifiers can be retrieved from the error's user info via the \c PHLocalIdentifiersErrorKey
@end

@interface PHCloudIdentifier () <NSCopying>
@end

API_AVAILABLE_END

API_AVAILABLE_BEGIN(macos(10.13), ios(15), tvos(15))


@interface PHPhotoLibrary (CloudIdentifiers)


/**
 @abstract Returns a dictionary that maps each cloud identifier from the provided array to a PLLocalIdentifierMapping result containing the local identifier found for that cloud identifier.
 @discussion This method can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.  If the attempt to lookup a local identifier for a given cloud identifier fails, the error parameter will indicate the reason.
 @param cloudIdentifiers The array of \c PHCloudIdentifier instances whose local identifiers are to being requested.
 */
- (NSDictionary <PHCloudIdentifier *, PHLocalIdentifierMapping *> *)localIdentifierMappingsForCloudIdentifiers:(NSArray<PHCloudIdentifier *> *)cloudIdentifiers API_AVAILABLE(macos(12), ios(15), tvos(15)) NS_REFINED_FOR_SWIFT;

/**
 @abstract Returns a dictionary that maps each local identifier from the provided array to a PLCloudIdentifierMapping result containing the cloud identifier found for that local identifier
 @discussion This method can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.  If the attempt to lookup a cloud identifier for a given local identifier fails, the error parameter will indicate the reason.
 @param localIdentifiers The array of \c NSString instances whose cloud identifiers are to being requested.
 */
- (NSDictionary <NSString *, PHCloudIdentifierMapping *> *)cloudIdentifierMappingsForLocalIdentifiers:(NSArray<NSString *> *)localIdentifiers API_AVAILABLE(macos(12), ios(15), tvos(15)) NS_REFINED_FOR_SWIFT;

/// DEPRECATED: These two methods can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.
- (NSArray<NSString *> *)localIdentifiersForCloudIdentifiers:(NSArray<PHCloudIdentifier *> *)cloudIdentifiers

API_DEPRECATED_WITH_REPLACEMENT("-localIdentifierMappingsForCloudIdentifiers:", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);

- (NSArray<PHCloudIdentifier *> *)cloudIdentifiersForLocalIdentifiers:(NSArray<NSString *> *)localIdentifiers

API_DEPRECATED_WITH_REPLACEMENT("-cloudIdentifierMappingsForLocalIdentifiers:", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);


@end

/// DEPRECATED: If the local object cannot be resolved from a global identifier, PHLocalIdentifierNotFound is provided in that array slot.
extern NSString * const PHLocalIdentifierNotFound

API_DEPRECATED_WITH_REPLACEMENT("Check for PHPhotosErrorIdentifierNotFound in PHLocalIdentifierMapping.error", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);


API_AVAILABLE_END
NS_ASSUME_NONNULL_END
