/*	NSPortNameServer.h
	Copyright 1993-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSPort;

@interface NSPortNameServer : NSObject

+ (NSPortNameServer *)systemDefaultPortNameServer;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;

- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

- (BOOL)removePortForName:(NSString *)name;

@end

#if defined(__MACH__)

@interface NSMachBootstrapServer : NSPortNameServer
	// This port name server actually takes and
	// returns instances of NSMachPort

+ (id)sharedInstance;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;
	// the bootstrap server is a local-only server;
	// host parameter must be emptry string or nil

- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

// removePortForName: functionality is not supported in
// the bootstrap server; if you want to cancel a service,
// you have to destroy the port (invalidate the NSMachPort
// given to registerPort:name:).

@end

#endif

@interface NSMessagePortNameServer : NSPortNameServer
	// This port name server actually takes and
	// returns instances of NSMessagePort

+ (id)sharedInstance;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;
	// this name server is a local-only server;
	// host parameter must be emptry string or nil

// removePortForName: functionality is not supported in
// this name server; if you want to cancel a service,
// you have to destroy the port (invalidate the
// NSMessagePort given to registerPort:name:).

@end

@interface NSSocketPortNameServer : NSPortNameServer
	// This port name server actually takes and
	// returns instances of NSSocketPort

+ (id)sharedInstance;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host nameServerPortNumber:(unsigned short)portNumber;
    // this name server supports remote lookup
- (BOOL)registerPort:(NSPort *)port name:(NSString *)name nameServerPortNumber:(unsigned short)portNumber;

- (BOOL)removePortForName:(NSString *)name;
     // removePortForName: is supported, and should be used

- (void)setDefaultNameServerPortNumber:(unsigned short)portNumber;
- (unsigned short)defaultNameServerPortNumber;
     // controls the port number used to contact the name server,
     // if none is specified
@end


