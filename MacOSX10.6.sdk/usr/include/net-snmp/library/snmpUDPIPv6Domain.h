#ifndef _SNMPUDPIPV6DOMAIN_H
#define _SNMPUDPIPV6DOMAIN_H

#ifdef __cplusplus
extern          "C" {
#endif

#include <net-snmp/library/snmp_transport.h>
#include <net-snmp/library/asn1.h>

/*
 * The SNMP over UDP over IPv6 transport domain is identified by
 * transportDomainUdpIpv6 as defined in RFC 3419.
 */

#define TRANSPORT_DOMAIN_UDP_IPV6	1,3,6,1,2,1,100,1,2
NETSNMP_IMPORT oid      netsnmp_UDPIPv6Domain[];

netsnmp_transport *snmp_udp6_transport(struct sockaddr_in6 *addr,
                                       int local);


/*
 * Convert a "traditional" peername into a sockaddr_in6 structure which is
 * written to *addr.  Returns 1 if the conversion was successful, or 0 if it
 * failed.  
 */

int             netsnmp_sockaddr_in6(struct sockaddr_in6 *addr,
                                     const char *peername,
                                     int remote_port);

void            netsnmp_udp6_agent_config_tokens_register(void);
void            netsnmp_udp6_parse_security(const char *token,
                                            char *param);

int             netsnmp_udp6_getSecName(void *opaque, int olength,
                                        const char *community,
                                        int community_len, char **secname,
                                        char **contextName);

/*
 * "Constructor" for transport domain object.  
 */

void            netsnmp_udp6_ctor(void);

#ifdef __cplusplus
}
#endif
#endif/*_SNMPUDPIPV6DOMAIN_H*/
