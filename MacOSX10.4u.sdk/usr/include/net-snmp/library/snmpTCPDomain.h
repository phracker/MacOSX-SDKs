#ifndef _SNMPTCPDOMAIN_H
#define _SNMPTCPDOMAIN_H

#ifdef SNMP_TRANSPORT_TCP_DOMAIN

#ifdef __cplusplus
extern          "C" {
#endif

#include <net-snmp/library/snmp_transport.h>
#include <net-snmp/library/asn1.h>

#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

/*
 * The SNMP over TCP over IPv4 transport domain is identified by
 * transportDomainTcpIpv4 as defined in RFC 3419.
 */

#define TRANSPORT_DOMAIN_TCP_IP		1,3,6,1,2,1,100,1,5
extern oid netsnmp_snmpTCPDomain[];

netsnmp_transport *netsnmp_tcp_transport(struct sockaddr_in *addr, int local);

/*
 * "Constructor" for transport domain object.  
 */

void            netsnmp_tcp_ctor(void);

#ifdef __cplusplus
}
#endif
#endif                          /*SNMP_TRANSPORT_TCP_DOMAIN */

#endif/*_SNMPTCPDOMAIN_H*/
