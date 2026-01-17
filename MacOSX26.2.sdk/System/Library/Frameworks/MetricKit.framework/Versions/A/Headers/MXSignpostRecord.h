//
//  MXSignpostRecord.h
//  MetricKit
//  Copyright (c) 2023 Apple Inc.
//  All rights reserved.
//
#import <Foundation/Foundation.h>
#import <os/availability.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXSignpostRecord
 @abstract      A class that represents a record of signpost instance.
 @discussion    Signpost instances are either Signpost intervals or events and MXSignpostRecord captures information reagarding such signpost instances
 */
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXSignpostRecord : NSObject <NSSecureCoding>

/*!
 @property      subsystem
 @abstract      An NSString representation of the subsystem of the signpost instance.
 */
@property (readonly, copy, nonnull) NSString *subsystem;
/*!
 @property      category
 @abstract      An NSString representation of the category of the signpost instance.
 */

@property (readonly, copy, nonnull) NSString *category;
/*!
 @property      name
 @abstract      An NSString representation of the name of the signpost instance.
 */

@property (readonly, copy, nonnull) NSString *name;
/*!
 @property      beginTimeStamp
 @abstract      An NSDate representation of the begin time stamp of the signpost instance.
 */

@property (readonly, copy, nonnull) NSDate *beginTimeStamp;
/*!
 @property      endTimeStamp
 @abstract      An NSDate representation of the end time stamp of the signpost instances which are intervals and will be nil for signpost events.
 */

@property (readonly, copy, nullable) NSDate *endTimeStamp;
/*!
 @property      duration
 @abstract      An NSMeasurement representing the duration in milliseconds of signpost instances which are intervals and will be nil for signpost events.
 */

@property (readonly, copy, nullable) NSMeasurement<NSUnitDuration *> *duration;

/*!
 @property      isInterval
 @abstract      A BOOL denoting whether the signpost instance is an interval or not..
 */

@property (readonly) BOOL isInterval;

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this SignpostRecord.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
@method        dictionaryRepresentation
@abstract      Convenience method to return a NSDictionary representation of this SignpostRecord.
@result        An NSDictionary object containing the dictionary representation
*/
- (NSDictionary *)dictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
