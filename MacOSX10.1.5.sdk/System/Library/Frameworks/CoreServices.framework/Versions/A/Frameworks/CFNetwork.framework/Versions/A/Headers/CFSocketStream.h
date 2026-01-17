/* CFSocketStream.h
   Copyright 2000, Apple, Inc.  All rights reserved.
*/

#if !defined(__CFNETWORK_CFSOCKETSTREAM__)
#define __CFNETWORK_CFSOCKETSTREAM__ 1

#include <CoreFoundation/CFStream.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern const int kCFStreamErrorDomainSSL;

typedef enum {
    kCFStreamSocketSecurityNone = 0,
    kCFStreamSocketSecuritySSLv2,
    kCFStreamSocketSecuritySSLv3,
    kCFStreamSocketSecuritySSLv23,    // Use SSLv3 if available; if not, try SSLv2
    kCFStreamSocketSecurityTLSv1
} CFStreamSocketSecurityProtocol;

CF_EXPORT
Boolean CFSocketStreamPairSetSecurityProtocol(CFReadStreamRef socketReadStream, CFWriteStreamRef socketWriteStream, CFStreamSocketSecurityProtocol securityProtocol);

#if defined(__cplusplus)
}
#endif

#endif /* ! __CFNETWORK_CFSOCKETSTREAM__ */
