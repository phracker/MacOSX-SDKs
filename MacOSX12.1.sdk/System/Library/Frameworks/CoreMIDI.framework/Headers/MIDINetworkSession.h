/*
    File:       CoreMIDI/MIDINetworkSession.h
 
    Contains:   Routines for MIDI networking
 
 	Copyright:  (c) 2010 by Apple Inc., all rights reserved.
 
    Bugs?:      For bug reports, consult the following page on
                the World Wide Web:
 
                    http://feedbackassistant.apple.com/
 
*/

#ifndef __MIDINetworkSession_h__
#define __MIDINetworkSession_h__

#if defined(__OBJC__)
#import <CoreMIDI/MIDIServices.h>
#import <Foundation/Foundation.h>

#define MIDINETWORKSESSION_AVAILABLE API_AVAILABLE(macos(10.15), ios(4.2)) API_UNAVAILABLE(watchos, tvos)

NS_ASSUME_NONNULL_BEGIN

/* This is the Bonjour service type. */
OS_EXPORT NSString *const MIDINetworkBonjourServiceType MIDINETWORKSESSION_AVAILABLE;

/*
	These are NSNotifications posted by MIDINetworkSession objects. 

	MIDINetworkNotificationContactsDidChange signifies that the list of contacts changed.
	MIDINetworkNotificationSessionDidChange signifies that other aspects of the session changed,
	such as the connection list, connection policy, etc.
*/
OS_EXPORT NSString *const MIDINetworkNotificationContactsDidChange MIDINETWORKSESSION_AVAILABLE;
OS_EXPORT NSString *const MIDINetworkNotificationSessionDidChange MIDINETWORKSESSION_AVAILABLE;


/* __________________________________________________________________________________________________
	These are the values of connectionPolicy
*/
typedef NS_ENUM(NSUInteger, MIDINetworkConnectionPolicy) {
	MIDINetworkConnectionPolicy_NoOne				= 0,
	MIDINetworkConnectionPolicy_HostsInContactList	= 1,
	MIDINetworkConnectionPolicy_Anyone				= 2
};

/* __________________________________________________________________________________________________
	MIDINetworkHost
	
	Represents a network address.
	name: the user's tag for this object.
	Representations are either:
	-	address (IP address or hostname) and UDP port
	-	netServiceName and netServiceDomain
*/
OS_EXPORT MIDINETWORKSESSION_AVAILABLE
@interface MIDINetworkHost : NSObject {
@private
    void *_imp;
}
+ (instancetype)hostWithName: (NSString *)name address: (NSString *)address port: (NSUInteger)port;
+ (instancetype)hostWithName: (NSString *)name netService: (NSNetService *)netService;
+ (instancetype)hostWithName: (NSString *)name netServiceName: (NSString *)netServiceName netServiceDomain: (NSString *)netServiceDomain;
- (BOOL)hasSameAddressAs: (MIDINetworkHost *)other;

@property(nonatomic,readonly) NSString *name;				/* user's tag */
@property(nonatomic,readonly) NSString *address;			/* IP address or hostname */
@property(nonatomic,readonly) NSUInteger port;						/* UDP port */
@property(nonatomic,readonly,nullable) NSString *netServiceName;	/* NSNetService name */
@property(nonatomic,readonly,nullable) NSString *netServiceDomain;	/* NSNetService domain */
@end

/*__________________________________________________________________________________________________
	MIDINetworkConnection

	Add a connection to a session to connect to the remote host; remove it to disconnect.
*/
OS_EXPORT MIDINETWORKSESSION_AVAILABLE
@interface MIDINetworkConnection : NSObject {
@private
    void *_imp;
}
+ (instancetype)connectionWithHost: (MIDINetworkHost *)host;
@property(nonatomic,readonly) MIDINetworkHost *host;
@end

/* __________________________________________________________________________________________________
	MIDINetworkSession
	
	A network session represents one CoreMIDI entity (source/destination pair). One session can
	have any number of connections. Output is broadcast to all connections; input from multiple
	connections is merged.
*/
OS_EXPORT MIDINETWORKSESSION_AVAILABLE
@interface MIDINetworkSession : NSObject {
@private
    void *_imp;
}

+ (MIDINetworkSession *)defaultSession; /* returns the singleton. */

/* Basic attributes of a session */
@property(nonatomic,getter=isEnabled) BOOL enabled;			/* disabled sessions do not appear on the network and cannot initiate or receive connections. default is NO (disabled). */
@property(nonatomic,readonly) NSUInteger networkPort;		/* UDP port */
@property(nonatomic,readonly) NSString *networkName;		/* name by which this session is advertised via Bonjour */
@property(nonatomic,readonly) NSString *localName;			/* name of this session's CoreMIDI entity (inherited by its endpoints) */
@property(nonatomic) MIDINetworkConnectionPolicy connectionPolicy;	/* who can connect to this session? see constants above. */

/*	The driver maintains a directory of MIDINetworkHosts, "contacts," for user convenience in initiating 
	connections, and for controlling incoming connection requests. */
- (NSSet<MIDINetworkHost *> *)contacts;
- (BOOL)addContact: (MIDINetworkHost *)contact;
- (BOOL)removeContact: (MIDINetworkHost *)contact;

- (NSSet<MIDINetworkConnection *> *)connections;
- (BOOL)addConnection: (MIDINetworkConnection *)connection;
- (BOOL)removeConnection: (MIDINetworkConnection *)connection;

- (MIDIEndpointRef)sourceEndpoint;
- (MIDIEndpointRef)destinationEndpoint;
@end

NS_ASSUME_NONNULL_END

#endif // defined(__OBJC__)

#endif /* __MIDINetworkSession_h__ */
