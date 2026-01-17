#ifndef _SNMPUDPDOMAIN_H
#define _SNMPUDPDOMAIN_H

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

netsnmp_transport *netsnmp_udp_transport(struct sockaddr_in *addr, int local);


/*
 * Convert a "traditional" peername into a sockaddr_in structure which is
 * written to *addr.  Returns 1 if the conversion was successful, or 0 if it
 * failed.  
 */

int             netsnmp_sockaddr_in(struct sockaddr_in *addr,
                                    const char *peername, int remote_port);


/*
 * Register any configuration tokens specific to the agent.  
 */

void            netsnmp_udp_agent_config_tokens_register(void);

void            netsnmp_udp_parse_security(const char *token, char *param);

int             netsnmp_udp_getSecName(void *opaque, int olength,
                                       const char *community,
                                       size_t community_len,
                                       char **secname,
                                       char **contextName);

/*
 * "Constructor" for transport domain object.  
 */

void            netsnmp_udp_ctor(void);

#ifdef __cplusplus
}
#endif
#endif/*_SNMPUDPDOMAIN_H*/
