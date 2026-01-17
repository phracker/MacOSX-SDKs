//
//  MXDiagnostic.h
//  MetricKit
//
//  Copyright (c) 2019 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetaData.h>
#import <MetricKit/MXSignpostRecord.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class         MXDiagnostic
@abstract      An abstract class that describes a diagnostic report vended by MetricKit.
@discussion    All supported diagnostics are subclasses of MXDiagnostic.
*/
API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXDiagnostic : NSObject <NSSecureCoding>

@property (readonly, strong, nonnull) MXMetaData* metaData;

/*!
 @property      applicationVersion
 @abstract      An NSString representation of the application version from which this diagnostic was generated.
 */
@property (readonly, strong, nonnull) NSString *applicationVersion;

/*!
 @property      signpostData
 @abstract      An NSArray representing the list of signpost records.
 */

@property (readonly, strong, nullable) NSArray<MXSignpostRecord *> *signpostData API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this diagnostic.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        dictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this diagnostic.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)dictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
