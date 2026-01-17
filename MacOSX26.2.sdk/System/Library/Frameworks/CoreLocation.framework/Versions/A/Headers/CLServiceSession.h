//
//  CLServiceSession.h
//  CoreLocation
//
//  Created by Siraj Abidi on 04/11/24.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSInteger, CLServiceSessionAuthorizationRequirement) {
	CLServiceSessionAuthorizationRequirementNone = 0,
	CLServiceSessionAuthorizationRequirementWhenInUse,
	CLServiceSessionAuthorizationRequirementAlways API_UNAVAILABLE(tvos),
} NS_REFINED_FOR_SWIFT;

API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos) NS_REFINED_FOR_SWIFT
@interface CLServiceSessionDiagnostic : NSObject
/*
 *  authorizationDenied
 *
 *  Discussion:
 *      True if the session will be suspended while the app has been denied
 *      location authorization.
 *
 */
@property (nonatomic, readonly) BOOL authorizationDenied;

/*
 *  authorizationDeniedGlobally
 *
 *  Discussion:
 *      True if the session will be suspended while the user has disabled Location
 *      Services system-wide.
 *
 */
@property (nonatomic, readonly) BOOL authorizationDeniedGlobally;

/*
 *  authorizationRestricted
 *
 *  Discussion:
 *      True if session will be suspended while the app lacks authorization,
 *      and authorization changes are prevented by parental restrictions,
 *      MDM configuration, or other factors.
 *
 */
 @property (nonatomic, readonly) BOOL authorizationRestricted;

/*
 *  insufficientlyInUse
 *
 *  Discussion:
 *      True if the session will be suspended while the app is not sufficiently
 *      in-use.
 *
 */
@property (nonatomic, readonly) BOOL insufficientlyInUse;

/*
 *  serviceSessionRequired
 *
 *  Discussion:
 *      True if LocationServices are disabled because the app has adopted CLRequireExplicitServiceSession
 *      info.plist key but no CLServiceSession requiring authorization is outstanding yet.
 *
 */
@property (nonatomic, readonly) BOOL serviceSessionRequired;

/*
 *  fullAccuracyDenied
 *
 *  Discussion:
 *      True if a session requiring FullAccuracy has been denied full accuracy due to user decision.
 *
 */
@property (nonatomic, readonly) BOOL fullAccuracyDenied;

/*
*  alwaysAuthorizationDenied
*
*  Discussion:
*      True if a session requiring Always authorization has been denied Always due to user decision.
*
*/
@property (nonatomic, readonly) BOOL alwaysAuthorizationDenied;

/*
 *  authorizationRequestInProgress
 *
 *  Discussion:
 *      True if the system is requesting authorization from the user on behalf of the app, but no response has been received yet.
 *
 */
@property (nonatomic, readonly) BOOL authorizationRequestInProgress;

@end

CL_EXTERN
API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos) NS_REFINED_FOR_SWIFT
@interface CLServiceSession : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;


/*
 *  sessionRequiringAuthorization:
 *
 *  Discussion:
 *     Creates a CLServiceSession instance with specified authorization requirement.
 *
 *     authorizationRequirement: Passing None for authorization requirement
 *     creates a session object which does not seek authorization from the user,
 *     but meets a requested Explicit Service Session requirement if authorization
 *     has already been obtained.
 *
 *     Passing an authorization requirement other than .none will cause
 *     Location Services to seek the corresponding level of authorization
 *     from the user when possible.
 *
 *     Like a CLBackgroundActivitySession instance, a CLServiceSession
 *     instance should be created while in-use, or immediately when launched
 *     in the background if a matching session was held when previously
 *     running.  If an instance is created that does not meet either
 *     requirement, it will yield the .insufficientlyInUse diagnostic until
 *     the app returns to the foreground (off-course to receive updates use the below
 *     variant which specifies a handler)
 *
 *     Note: A CLServiceSession instance with an authorization requirement of
 *     .always must be held, and reporting no relevant diagnostic properties,
 *     whenever Always authorization is to be leveraged.  An app with Always
 *     authorization, but which is not holding such a CLServiceSession will
 *     not be able to receive CLLocationUpdate.liveUpdates() or CLMonitor.events()
 *     when it is not in-use.  So be careful to take one when the user
 *     configures always-operation, and retake it promptly during launch
 *     after background termination.
 *
 */
+ (CLServiceSession *)sessionRequiringAuthorization:(CLServiceSessionAuthorizationRequirement)authorizationRequirement API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

/* sessionRequiringAuthorization:queue:handler:
 *  Discussion:
 *     Creates a CLServiceSession instance with specified authorization requirement.
 *     Session behaves the same as decribed for sessionRequiringAuthorization:
 *
 *     queue: Specifies the queue to which the handler is submitted for receiving
 *            diagnostic updates
 *
 *     handler: Specifies the block that will be invoked with each diagnostic update.
 *
 */
+ (CLServiceSession *)sessionRequiringAuthorization:(CLServiceSessionAuthorizationRequirement)authorizationRequirement
											  queue:(dispatch_queue_t)queue
											handler:(void(^)(CLServiceSessionDiagnostic *diagnostic))handler API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);


/*
 *  sessionRequiringAuthorization:fullAccuracyPurposeKey:
 *
 *  Discussion:
 *     Creates a CLServiceSession instance with specified authorization requirement
 *     and fullAccuracy Purpose Key
 *
 *     authorizationRequirement:
 *       Same as applicable for sessionRequiringAuthorization:  i.e Passing an
 *       authorization requirement other than .none will cause Location Services
 *       to seek the corresponding level of authorization from the user when possible.
 *
 *     fullAccuracyPurposeKey:
 *       Names a string in the NSLocationTemporaryUsageDescriptionDictionary.
 *       Location Services will request temporary full accuracy authorization
 *       from the user using this string if necessary while this session is
 *       outstanding.
 *
 */
+ (CLServiceSession *)sessionRequiringAuthorization:(CLServiceSessionAuthorizationRequirement)authorizationRequirement
							 fullAccuracyPurposeKey:(nonnull NSString *)purposeKey API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);



/*
 *  sessionRequiringAuthorization:fullAccuracyPurposeKey:queue:handler:
 *
 *  Discussion:
 *     Creates a CLServiceSession instance with specified authorization requirement
 *     and fullAccuracy Purpose Key same as sessionRequiringAuthorization:fullAccuracyPurposeKey:
 *
 *     This variant allows to specify a queue to which specified callback handler
 *     will be submitted for receiving diagnostic updates.
 */
+ (CLServiceSession *)sessionRequiringAuthorization:(CLServiceSessionAuthorizationRequirement)authorizationRequirement
							 fullAccuracyPurposeKey:(nonnull NSString *)purposeKey
											  queue:(dispatch_queue_t)queue
											handler:(void(^)(CLServiceSessionDiagnostic *diagnostic))handler API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);


/*
 *  invalidate
 *
 *  Discussion:
 *      Ends the session immediately. Once the session is
 *      invalidated it cannot become active again.
 */
- (void)invalidate API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
