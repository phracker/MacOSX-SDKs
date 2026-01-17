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
API_AVAILABLE(ios(13.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
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
@property (readonly, strong, nonnull) NSString *platformArchitecture API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @property      lowPowerModeEnabled
 @abstract      A boolean representing low power mode enablement on device
 */

@property (readonly) bool lowPowerModeEnabled API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @property      isTestFlightApp
 @abstract      A boolean representing if the app is registered as a testFlightApp
 */

@property (readonly) bool isTestFlightApp API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @property      pid
 @abstract      pid of the process
 @note          A value of -1 indicates that the PID was unavailable for the containing payload.
 */

@property (readonly) pid_t pid API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @property      bundleIdentifier
 @abstract      String representation of the bundle ID of the process.
 */

@property (readonly) NSString* bundleIdentifier API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(tvos, watchos);


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
- (NSDictionary *)DictionaryRepresentation API_DEPRECATED_WITH_REPLACEMENT("Use dictionaryRepresentation", ios(13.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos, tvos, watchos) NS_REFINED_FOR_SWIFT;

/*!
@method        dictionaryRepresentation
@abstract      Convenience method to return a NSDictionary representation of this metadata.
@result        An NSDictionary object containing the dictionary representation
*/
- (NSDictionary *)dictionaryRepresentation API_AVAILABLE(ios(13.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
