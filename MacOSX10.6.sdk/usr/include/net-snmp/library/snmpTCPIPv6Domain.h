#ifndef _SNMPTCPIPV6DOMAIN_H
#define _SNMPTCPIPV6DOMAIN_H

#ifdef __cplusplus
extern          "C" {
#endif

#include <net-snmp/library/snmp_transport.h>
#include <net-snmp/library/asn1.h>

/*
 * The SNMP over TCP over IPv6 transport domain is identified by
 * transportDomainTcpIpv4 as defined in RFC 3419.
 */

#define TRANSPORT_DOMAIN_TCP_IPV6	1,3,6,1,2,1,100,1,6
NETSNMP_IMPORT oid      netsnmp_TCPIPv6Domain[];

netsnmp_transport *netsnmp_tcp6_transport(struct sockaddr_in6 *addr, 
					  int local);

/*
 * "Constructor" for transport domain object.  
 */

void            netsnmp_tcp6_ctor(void);

#ifdef __cplusplus
}
#endif
#endif/*_SNMPTCPIPV6DOMAIN_H*/
