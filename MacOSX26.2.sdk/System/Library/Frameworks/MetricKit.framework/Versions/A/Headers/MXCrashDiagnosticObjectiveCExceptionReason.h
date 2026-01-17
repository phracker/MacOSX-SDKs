//
//  MXCrashException.h
//  MetricKit
//
//  Created by Aditya Bhushan on 3/1/23.
//

#import <Foundation/Foundation.h>
#import <os/availability.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXCrashDiagnosticObjectiveCExceptionReason
 @abstract      A class that represents Crash exception reason.
 @discussion    Crash reports that are caused by an uncaught Objective-C NSException can in some cases contain detailed information about the type, name and description of the exception object.
                This information is captured in a structured way in a MXCrashDiagnosticObjectiveCExceptionReason object and may have some pieces redacted to avoid exposing sensitive user data.
 */

API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXCrashDiagnosticObjectiveCExceptionReason: NSObject <NSSecureCoding>
/*!
 @property      composedMessage
 @abstract      A human-readable message string summarizing the reason for the exception.
 */
@property (readonly, copy, nonnull) NSString *composedMessage;
/*!
 @property      formatString
 @abstract      A string representing the exception message before arguments are substituted into the message
 */
@property (readonly, copy, nonnull) NSString *formatString;
/*!
 @property      arguments
 @abstract      An NSArray of strings representing arguments passed to the formatString.
 */
@property (readonly, copy, nonnull) NSArray<NSString *>*arguments;
/*!
 @property      exceptionType
 @abstract      A human-readable string denoting type of the exception
 */
@property (readonly, copy, nonnull) NSString *exceptionType;
/*!
 @property      className
 @abstract      A string representing the class name of the exception, for example NSException.
 */
@property (readonly, copy, nonnull) NSString *className;
/*!
 @property      exceptionName
 @abstract      A string representing name of the exception
 @discussion    This will align with the "name" field of the NSException
 */
@property (readonly, copy, nonnull) NSString *exceptionName;

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this MXCrashDiagnosticObjectiveCExceptionReason object.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
@method        dictionaryRepresentation
@abstract      Convenience method to return a NSDictionary representation of this MXCrashDiagnosticObjectiveCExceptionReason object.
@result        An NSDictionary object containing the dictionary representation
*/
- (NSDictionary *)dictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
