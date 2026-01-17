//
//  MXMetaData.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMetaData
 @abstract      A class that contains miscellaneous metadata about an associated payload.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMetaData : NSObject <NSSecureCoding>

/*!
 @property      regionFormat
 @abstract      An NSString designating the region format associated with the application.
 */
@property (readonly, strong, nonnull) NSString *regionFormat;

/*!
 @property      osVersion
 @abstract      An NSString designating the OS version associated with the device.
 */
@property (readonly, strong, nonnull) NSString *osVersion;

/*!
 @property      deviceType
 @abstract      An NSString designating the device type associated with this device.
 */
@property (readonly, strong, nonnull) NSString *deviceType;

/*!
 @property      applicationBuildVersion
 @abstract      An NSString designating the app build version.
 */
@property (readonly, strong, nonnull) NSString *applicationBuildVersion;

/*!
 @property      platformArchitecture
 @abstract      An NSString designating the current architecture.
 */
@property (readonly, strong, nonnull) NSString *platformArchitecture API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos);


/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this metadata.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        DictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this metadata.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)DictionaryRepresentation API_DEPRECATED_WITH_REPLACEMENT("Use dictionaryRepresentation", ios(13.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
@method        dictionaryRepresentation
@abstract      Convenience method to return a NSDictionary representation of this metadata.
@result        An NSDictionary object containing the dictionary representation
*/
- (NSDictionary *)dictionaryRepresentation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
