/*
 * Copyright (c) 2022 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NERelayManager.h
 * @discussion This file declares the NERelayManager API. The NERelayManager API is used to directly configure relay settings on the system.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to configure relay settings on the system.
 */

#if defined(__cplusplus)
#define NERELAY_EXPORT extern "C"
#else
#define NERELAY_EXPORT extern
#endif

@class NERelay;
@class NEOnDemandRule;

/*!
 * @typedef NERelayManagerError
 * @abstract NERelay Manager error codes
 */
typedef NS_ENUM(NSInteger, NERelayManagerError) {
	/*! @const NERelayManagerErrorConfigurationInvalid The relay manager is invalid */
	NERelayManagerErrorConfigurationInvalid = 1,
	/*! @const NERelayManagerErrorConfigurationDisabled The relay manager is not enabled. */
	NERelayManagerErrorConfigurationDisabled = 2,
	/*! @const NERelayManagerErrorConfigurationStale The relay manager needs to be loaded. */
	NERelayManagerErrorConfigurationStale = 3,
	/*! @const NERelayManagerErrorConfigurationCannotBeRemoved The relay manager cannot be removed. */
	NERelayManagerErrorConfigurationCannotBeRemoved = 4,
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @const NERelayErrorDomain The NERelay error domain */
NERELAY_EXPORT NSString * const NERelayErrorDomain API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NERelayManagerClientError
 * @abstract NERelay Manager error codes detected by the client while trying to use this relay
 */
typedef NS_ENUM(NSInteger, NERelayManagerClientError) {
	/*! @const NERelayManagerClientErrorNone The client did not have an error on the last connection */
	NERelayManagerClientErrorNone = 1,
	/*! @const NERelayManagerClientErrorDNSFailed DNS resolution of the relay server failed */
	NERelayManagerClientErrorDNSFailed = 2,
	/*! @const NERelayManagerClientErrorServerUnreachable The relay server was unreachable */
	NERelayManagerClientErrorServerUnreachable = 3,
	/*! @const NERelayManagerClientErrorServerDisconnected The relay server prematurely disconnected the connection  */
	NERelayManagerClientErrorServerDisconnected = 4,
	/*! @const NERelayManagerClientErrorCertificateMissing The certificate needed to connect to the relay server could not be accessed or was not provided */
	NERelayManagerClientErrorCertificateMissing = 5,
	/*! @const NERelayManagerClientErrorCertificateInvalid The certificate needed to connect to the relay server was invalid. */
	NERelayManagerClientErrorCertificateInvalid = 6,
	/*! @const NERelayManagerClientErrorCertificateExpired The certificate needed to connect to the relay server was expired. */
	NERelayManagerClientErrorCertificateExpired = 7,
	/*! @const NERelayManagerClientErrorServerCertificateInvalid The relay server certificate was invalid. */
	NERelayManagerClientErrorServerCertificateInvalid = 8,
	/*! @const NERelayManagerClientErrorServerCertificateExpired The relay server certificate was expired. */
	NERelayManagerClientErrorServerCertificateExpired = 9,
	/*! @const NERelayManagerClientErrorOther The client detected an error that has not yet been enumerated */
	NERelayManagerClientErrorOther = 10,
} API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

/*! @const NERelayClientErrorDomain The NERelay error domain as detected by the client*/
NERELAY_EXPORT NSString * const NERelayClientErrorDomain API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

/*! @const NERelayConfigurationDidChangeNotification Name of the NSNotification that is posted when the relay configuration changes. */
NERELAY_EXPORT NSString * const NERelayConfigurationDidChangeNotification API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @interface NERelayManager
 * @discussion The NERelayManager class declares the programmatic interface for an object that manages relay configurations.
 *
 * NERelayManager declares methods and properties for configuring and controlling relay settings on the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NERelayManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NERelayManager object for the calling process.
 */
+ (NERelayManager *)sharedManager;

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current relay configuration from the caller's relay preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler;

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the relay configuration from the caller's relay preferences. If the relay is enabled, the relay becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler;

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the relay configuration in the caller's relay preferences. If the relay are enabled, they will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler;

/*!
 * @method getLastClientErrors
 * @discussion This function will get errors that the client detected while using this relay configuration within the specified time period.  Errors will be from the NERelayClientErrorDomain and the NERelayManagerClientErrorNone value will be set for successful connections.
 * @param seconds A NSTimeInterval that specifies how many seconds to report errors for.  The maximum supported value is 24 hours and any larger values will be automatically reduced to 24 hours.
 * @param completionHandler A block that will be called when once the errors have been collected. The NSArray will contain a list of NERelayManagerClientError values detected within the last number of seconds as specified by the "seconds" parameter.  The values will be ordered from the error most recently detected to the oldest.  The error value of NERelayManagerClientErrorNone indicates the last successful use of the relay without error.  The NSArray will be empty if there are no values detected within the specified time period or nil if there was a problem in retrieving the errors.
 */
- (void)getLastClientErrors:(NSTimeInterval)seconds completionHandler:(void (^)(NSArray<NSError *> * __nullable errors))completionHandler API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the relay.
 */
@property (copy, nullable) NSString *localizedDescription;

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the relay. */
@property (getter=isEnabled) BOOL enabled;

/*!
 * @property uiToggleEnabled
 * @discussion Determines if the user will have the ability to enable and disable the relay */
@property (getter=isUIToggleEnabled) BOOL UIToggleEnabled;

/*!
 * @property allowDNSFailover
 * @discussion Determines if DNS queries that fail over relay can fallback to default DNS */
@property (getter=isDNSFailoverAllowed) BOOL allowDNSFailover API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos);

/*!
 * @property relays
 * @discussion An array of relay configurations describing one or more relay hops.
 */
@property (strong, nullable) NSArray<NERelay *> *relays;

/*!
 * @property matchDomains
 * @discussion An array of strings containing domain names. If this property is non-nil, the relay will be used to access hosts within the specified domains. If this and the match FQDNs property is nil, the relay will be used for all domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains;

/*!
 * @property matchFQDNs
 * @discussion An array of strings containing Fully Qualified Domain Names (FQDNs). If this property is non-nil, the relay will be used to access the specified hosts.  If this and the matchDomains property is nil, the relay will be used for all domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchFQDNs;

/*!
 * @property excludedDomains
 * @discussion An array of strings containing domain names. If the destination host name of a connection shares a suffix with one of these strings then the relay will not be used.
 */
@property (copy, nullable) NSArray<NSString *> *excludedDomains;

/*!
 * @property excludedFQDNs
 * @discussion An array of strings containing Fully Qualified Domain Names (FQDNs). If the destination host matches one of these strings then the relay will not be used.  An excluded FQDN takes priority over the matchDomain property.  This means the relay will not be used if the hostname matches an FQDN in this array even if the matchDomains contains a domain that would have been considered a match.
 */
@property (copy, nullable) NSArray<NSString *> *excludedFQDNs;

/*!
 * @property onDemandRules
 * @discussion An array of NEOnDemandRule objects. If nil, the associated relay will always apply. If non-nil, the array describes the networks on which the relay should be used or not.
 */
@property (copy, nullable) NSArray<NEOnDemandRule *> *onDemandRules;

/*!
 * @method loadAllManagersFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NERelay configurations created by the calling app that have previously been saved to disk and returns them as NERelayManager objects.
 * @param completionHandler A block that takes an array NERelayManager objects. The array passed to the block may be empty if no NERelay configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllManagersFromPreferencesWithCompletionHandler:(void (^)(NSArray<NERelayManager *> *managers, NSError * __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
