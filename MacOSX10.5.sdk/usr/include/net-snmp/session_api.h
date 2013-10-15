#ifndef NET_SNMP_SESSION_API_H
#define NET_SNMP_SESSION_API_H

    /**
     *  Library API routines concerned with specifying and using SNMP "sessions"
     *    including sending and receiving requests.
     */

#include <net-snmp/types.h>

    /*
     *  For the initial release, this will just refer to the
     *  relevant UCD header files.
     *    In due course, the routines relevant to this area of the
     *  API will be identified, and listed here directly.
     *
     *  But for the time being, this header file is a placeholder,
     *  to allow application writers to adopt the new header file names.
     */

#include <net-snmp/library/snmp_api.h>
#include <net-snmp/library/snmp_client.h>
#include <net-snmp/library/asn1.h>
#include <net-snmp/library/callback.h>

#include <net-snmp/library/snmp_transport.h>
#include <net-snmp/library/snmp_service.h>
#include <net-snmp/library/snmpCallbackDomain.h>
#ifdef NETSNMP_TRANSPORT_UNIX_DOMAIN
#include <net-snmp/library/snmpUnixDomain.h>
#endif
#ifdef NETSNMP_TRANSPORT_UDP_DOMAIN
#include <net-snmp/library/snmpUDPDomain.h>
#endif
#ifdef NETSNMP_TRANSPORT_TCP_DOMAIN
#include <net-snmp/library/snmpTCPDomain.h>
#endif
#ifdef NETSNMP_TRANSPORT_UDPIPV6_DOMAIN
#include <net-snmp/library/snmpUDPIPv6Domain.h>
#endif
#ifdef NETSNMP_TRANSPORT_TCPIPV6_DOMAIN
#include <net-snmp/library/snmpTCPIPv6Domain.h>
#endif
#ifdef NETSNMP_TRANSPORT_IPX_DOMAIN
#include <net-snmp/library/snmpIPXDomain.h>
#endif
#ifdef NETSNMP_TRANSPORT_AAL5PVC_DOMAIN
#include <net-snmp/library/snmpAAL5PVCDomain.h>
#endif

#include <net-snmp/library/ucd_compat.h>

#endif                          /* NET_SNMP_SESSION_API_H */
