/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEOnDemandRule.h
 * @discussion This file declares the family of NEOnDemandRule classes. NEOnDemandRule objects are used to create VPN configurations that are started "On Demand", or automatically when certain conditions specified by the rules are satisfied.
 *
 * This API is part of NetworkExtension.framework.
 *
 * When the network state of the system changes, the active On Demand rules are evaluated. The matching rule's action is saved by the system as the "current" action. When applications running on the system open network connections, the current On Demand action is checked to determine if the network connection should cause the associated NetworkExtension session to be started (or stopped). If the On Demand action is "evaluate connection", then further evaluation of the network connection's properties is performed before making the decision about whether or not the NetworkExtension session should be started.
 */

@class NEEvaluateConnectionRule;

/*!
 * @typedef NEOnDemandRuleAction
 * @abstract On Demand rule actions
 */
typedef NS_ENUM(NSInteger, NEOnDemandRuleAction) {
	/*! @const NEOnDemandRuleActionConnect Start the VPN connection */
	NEOnDemandRuleActionConnect = 1,
	/*! @const NEOnDemandRuleActionDisconnect Do not start the VPN connection, and disconnect the VPN connection if it is not currently disconnected */
	NEOnDemandRuleActionDisconnect = 2,
	/*! @const NEOnDemandRuleActionEvaluateConnection Start the VPN after evaluating the destination host being accessed against the rule's connection rules */
	NEOnDemandRuleActionEvaluateConnection = 3,
	/*! @const NEOnDemandRuleActionIgnore Do not start the VPN connection, and leave the VPN connection in its current state */
	NEOnDemandRuleActionIgnore = 4,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEOnDemandRuleInterfaceType
 * @abstract On Demand rule network interface types
 */
typedef NS_ENUM(NSInteger, NEOnDemandRuleInterfaceType) {
	/*! @const NEOnDemandRuleInterfaceTypeAny */
	NEOnDemandRuleInterfaceTypeAny API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos) = 0,
	/*! @const NEOnDemandRuleInterfaceTypeEthernet Wired Ethernet */
	NEOnDemandRuleInterfaceTypeEthernet API_AVAILABLE(macos(10.11), tvos(17.0)) API_UNAVAILABLE(ios, watchos) = 1,
	/*! @const NEOnDemandRuleInterfaceTypeWiFi WiFi */
	NEOnDemandRuleInterfaceTypeWiFi API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos) = 2,
	/*! @const NEOnDemandRuleInterfaceTypeCellular Cellular */
	NEOnDemandRuleInterfaceTypeCellular API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos) = 3,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @interface NEOnDemandRule
 * @discussion The NEOnDemandRule class declares the programmatic interface for an object that defines an On Demand rule. 
 *
 * NEOnDemandRule is an abstract base class from which other action-specific rule classes are derived.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEOnDemandRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property action
 * @discussion The rule's action
 */
@property (readonly) NEOnDemandRuleAction action API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property DNSSearchDomainMatch
 * @discussion An array of NSString objects. If the current default search domain is equal to one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the current default search domain does not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *DNSSearchDomainMatch API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property DNSServerAddressMatch
 * @discussion An array of DNS server IP addresses represented as NSString objects. If each of the current default DNS servers is equal to one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the default DNS servers do not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *DNSServerAddressMatch API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property interfaceTypeMatch
 * @discussion The type of interface that this rule matches. If the current primary network interface is of this type and all of the other conditions in the rule match, then the rule matches. If this property is 0 (the default), then the current primary interface type does not factor into the rule match.
 */
@property NEOnDemandRuleInterfaceType interfaceTypeMatch API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property SSIDMatch
 * @discussion An array of NSString objects. If the Service Set Identifier (SSID) of the current primary connected network matches one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the current primary connected network SSID does not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *SSIDMatch API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property probeURL
 * @discussion An HTTP or HTTPS URL. If a request sent to this URL results in a HTTP 200 OK response and all of the other conditions in the rule match, then then rule matches. If this property is nil (the default), then an HTTP request does not factor into the rule match.
 */
@property (copy, nullable) NSURL *probeURL API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

/*!
 * @interface NEOnDemandRuleConnect
 * @discussion The NEOnDemandRuleConnect class declares the programmatic interface for an object that defines an On Demand rule with the "Connect" action.
 *
 * When rules of this class match, the VPN connection is started whenever an application running on the system opens a network connection.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEOnDemandRuleConnect : NEOnDemandRule
@end

/*!
 * @interface NEOnDemandRuleDisconnect
 * @discussion The NEOnDemandRuleDisconnect class declares the programmatic interface for an object that defines an On Demand rule with the "Disconnect" action.
 *
 * When rules of this class match, the VPN connection is not started, and the VPN connection is disconnected if it is not currently disconnected.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEOnDemandRuleDisconnect : NEOnDemandRule
@end

/*!
 * @interface NEOnDemandRuleIgnore
 * @discussion The NEOnDemandRuleIgnore class declares the programmatic interface for an object that defines an On Demand rule with the "Ignore" action.
 *
 * When rules of this class match, the VPN connection is not started, and the current status of the VPN connection is left unchanged.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEOnDemandRuleIgnore : NEOnDemandRule
@end

/*!
 * @interface NEOnDemandRuleEvaluateConnection
 * @discussion The NEOnDemandRuleEvaluateConnection class declares the programmatic interface for an object that defines an On Demand rule with the "Evaluate Connection" action.
 *
 * When rules of this class match, the properties of the network connection being established are matched against a set of connection rules. The action of the matched rule (if any) is used to determine whether or not the VPN will be started.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEOnDemandRuleEvaluateConnection : NEOnDemandRule

/*!
 * @property connectionRules
 * @discussion An array of NEEvaluateConnectionRule objects. Each NEEvaluateConnectionRule object is evaluated in order against the properties of the network connection being established.
 */
@property (copy, nullable) NSArray<NEEvaluateConnectionRule *> *connectionRules API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

/*!
 * @typedef NEEvaluateConnectionRuleAction
 * @abstract Evaluate Connection rule actions
 */
typedef NS_ENUM(NSInteger, NEEvaluateConnectionRuleAction) {
	/*! @const NEEvaluateConnectionRuleActionConnectIfNeeded Start the VPN connection if the destination host is not accessible directly */
	NEEvaluateConnectionRuleActionConnectIfNeeded = 1,
	/*! @const NEEvaluateConnectionRuleActionNeverConnect Do not start the VPN connection */
	NEEvaluateConnectionRuleActionNeverConnect = 2,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @interface NEEvaluateConnectionRule
 * @discussion The NEEvaluateConnectionRule class declares the programmatic interface for an object that associates properties of network connections with an action.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEEvaluateConnectionRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithMatchDomains:andAction
 * @discussion Initialize an NEEvaluateConnectionRule instance with a list of destination host domains and an action
 */
- (instancetype)initWithMatchDomains:(NSArray<NSString *> *)domains andAction:(NEEvaluateConnectionRuleAction)action API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property action
 * @discussion The action to take if the properties of the network connection being established match the rule.
 */
@property (readonly) NEEvaluateConnectionRuleAction action API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property matchDomains
 * @discussion An array of NSString objects. If the host name of the destination of the network connection being established shares a suffix with one of the strings in this array, then the rule matches.
 */
@property (readonly) NSArray<NSString *> *matchDomains API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property useDNSServers
 * @discussion An array of NSString objects. If the rule matches the connection being established and the action is NEEvaluateConnectionRuleActionConnectIfNeeded, the DNS servers specified in this array are used to resolve the host name of the destination while evaluating connectivity to the destination. If the resolution fails for any reason, the VPN is started.
 */
@property (copy, nullable) NSArray<NSString *> *useDNSServers API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property probeURL
 * @discussion An HTTP or HTTPS URL. If the rule matches the connection being established and the action is NEEvaluateConnectionRuleActionConnectIfNeeded and a request sent to this URL results in a response with an HTTP response code other than 200, then the VPN is started.
 */
@property (copy, nullable) NSURL *probeURL API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

