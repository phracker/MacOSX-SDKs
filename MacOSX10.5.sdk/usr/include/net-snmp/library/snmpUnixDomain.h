#ifndef _SNMPUNIXDOMAIN_H
#define _SNMPUNIXDOMAIN_H

#ifdef NETSNMP_TRANSPORT_UNIX_DOMAIN

#ifdef __cplusplus
extern          "C" {
#endif

#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if HAVE_SYS_UN_H
#include <sys/un.h>
#endif

#include <net-snmp/library/snmp_transport.h>
#include <net-snmp/library/asn1.h>

/*
 * The SNMP over local socket transport domain is identified by
 * transportDomainLocal as defined in RFC 3419.
 */

#define TRANSPORT_DOMAIN_LOCAL	1,3,6,1,2,1,100,1,13
NETSNMP_IMPORT oid netsnmp_UnixDomain[];

netsnmp_transport *netsnmp_unix_transport(struct sockaddr_un *addr,
                                          int local);
void netsnmp_unix_agent_config_tokens_register(void);
void netsnmp_unix_parse_security(const char *token, char *param);
int netsnmp_unix_getSecName(void *opaque, int olength,
                            const char *community,
                            size_t community_len, char **secName,
                            char **contextName);


/*
 * "Constructor" for transport domain object.  
 */

void            netsnmp_unix_ctor(void);

#ifdef __cplusplus
}
#endif
#endif                          /*NETSNMP_TRANSPORT_UNIX_DOMAIN */

#endif/*_SNMPUNIXDOMAIN_H*/
