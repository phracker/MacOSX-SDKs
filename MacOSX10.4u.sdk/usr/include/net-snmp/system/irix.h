/*
 * irix.h
 * 
 * Date Created: Mon Feb 16 22:19:39 1998
 * Author:       Simon Leinen  <simon@switch.ch>
 */

#include <net-snmp/system/generic.h>

#undef TCP_TTL_SYMBOL
#define TCP_TTL_SYMBOL "tcp_ttl"

#undef IPSTAT_SYMBOL
#define NO_DOUBLE_ICMPSTAT
#undef ICMPSTAT_SYMBOL
#undef TCPSTAT_SYMBOL
#undef UDPSTAT_SYMBOL

#define _KMEMUSER 1

/*
 * don't define _KERNEL before including sys/unistd.h 
 */
#define IFNET_NEEDS_KERNEL_LATE  1

/*
 * configure fails to detect these properly because they're broken headers 
 */
#define HAVE_NETINET_TCP_H 1
#define HAVE_NETINET_IP_H 1

/*
 * don't use this on irix 
 * it has a prototype of inet_addr() which conflicts
 * with <netinet/in.h>
 */
#undef HAVE_ARPA_INET_H

/*
 * We need a prototype of inet_ntoa() then.
 */
extern const char *inet_ntoa();

#define STREAM_NEEDS_KERNEL_ISLANDS

#ifndef __GNUC__
#  undef NETSNMP_ENABLE_INLINE
#  define NETSNMP_ENABLE_INLINE 0
#endif
