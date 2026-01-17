#ifndef _SNMP_TRANSPORT_H
#define _SNMP_TRANSPORT_H

#include <sys/types.h>
#include <net-snmp/library/asn1.h>

#ifdef __cplusplus
extern          "C" {
#endif

/*  Some transport-type constants.  */

#ifndef NETSNMP_STREAM_QUEUE_LEN
#define	NETSNMP_STREAM_QUEUE_LEN	5
#endif

/*  Some transport-type flags.  */

#define		NETSNMP_TRANSPORT_FLAG_STREAM	0x01
#define		NETSNMP_TRANSPORT_FLAG_LISTEN	0x02

/*  The standard SNMP domains.  */

extern oid      netsnmpUDPDomain[]; 	/*      = { 1, 3, 6, 1, 6, 1, 1 };  */
extern oid      netsnmpCLNSDomain[];    /*      = { 1, 3, 6, 1, 6, 1, 2 };  */
extern oid      netsnmpCONSDomain[];    /*      = { 1, 3, 6, 1, 6, 1, 3 };  */
extern oid      netsnmpDDPDomain[]; 	/*      = { 1, 3, 6, 1, 6, 1, 4 };  */
extern oid      netsnmpIPXDomain[]; 	/*      = { 1, 3, 6, 1, 6, 1, 5 };  */
extern size_t   netsnmpUDPDomain_len;
extern size_t   netsnmpCLNSDomain_len;
extern size_t   netsnmpCONSDomain_len;
extern size_t   netsnmpDDPDomain_len;
extern size_t   netsnmpIPXDomain_len;

/*  Structure which defines the transport-independent API.  */

typedef struct netsnmp_transport_s {
    /*  The transport domain object identifier.  */

    const oid      *domain;
    int             domain_length;  /*  In sub-IDs, not octets.  */

    /*  Local transport address (in relevant SNMP-style encoding).  */
    
    unsigned char  *local;
    int             local_length;   /*  In octets.  */

    /*  Remote transport address (in relevant SNMP-style encoding).  */

    unsigned char  *remote;
    int             remote_length;  /*  In octets.  */

    /*  The actual socket.  */
    
    int             sock;

    /*  Flags (see #definitions above).  */

    unsigned int    flags;

    /*  Protocol-specific opaque data pointer.  */

    void           *data;
    int             data_length;

    /*  Maximum size of PDU that can be sent/received by this transport.  */

    size_t          msgMaxSize;

    /*  Callbacks.  Arguments are:
     *		
     *              "this" pointer, fd, buf, size, *opaque, *opaque_length  
     */

    int             (*f_recv)   (struct netsnmp_transport_s *, void *,
				 int, void **, int *);
    int             (*f_send)   (struct netsnmp_transport_s *, void *,
				 int, void **, int *);
    int             (*f_close)  (struct netsnmp_transport_s *);

    /*  This callback is only necessary for stream-oriented transports.  */

    int             (*f_accept) (struct netsnmp_transport_s *);

    /*  Optional callback to format a transport address.  */

    char           *(*f_fmtaddr)(struct netsnmp_transport_s *, void *,
				 int);
} netsnmp_transport;

typedef struct netsnmp_transport_list_s {
    netsnmp_transport *transport;
    struct netsnmp_transport_list_s *next;
} netsnmp_transport_list;

typedef struct netsnmp_tdomain_s {
    const oid      *name;
    size_t          name_length;
    const char    **prefix;
    netsnmp_transport *(*f_create_from_tstring) (const char *, int);
    netsnmp_transport *(*f_create_from_ostring) (const u_char *,  size_t, int);

    struct netsnmp_tdomain_s *next;
} netsnmp_tdomain;


/*  Some utility functions.  */

int netsnmp_transport_add_to_list(netsnmp_transport_list **transport_list,
				  netsnmp_transport *transport);
int netsnmp_transport_remove_from_list(netsnmp_transport_list **transport_list,
				       netsnmp_transport *transport);


/*
 * Return an exact (deep) copy of t, or NULL if there is a memory allocation
 * problem (for instance).
 */

netsnmp_transport *netsnmp_transport_copy(netsnmp_transport *t);


/*  Free an netsnmp_transport.  */

void            netsnmp_transport_free(netsnmp_transport *t);


/*
 * If the passed oid (in_oid, in_len) corresponds to a supported transport
 * domain, return 1; if not return 0.  If out_oid is not NULL and out_len is
 * not NULL, then the "internal" oid which should be used to identify this
 * domain (e.g. in pdu->tDomain etc.) is written to *out_oid and its length to
 * *out_len.
 */

int             netsnmp_tdomain_support(const oid *in_oid, size_t in_len,
					const oid **out_oid, size_t *out_len);

int             netsnmp_tdomain_register(netsnmp_tdomain *domain);
    
int             netsnmp_tdomain_unregister(netsnmp_tdomain *domain);

void            netsnmp_clear_tdomain_list(void);

void            netsnmp_tdomain_init(void);

netsnmp_transport *netsnmp_tdomain_transport(const char *string,
					     int local,
					     const char
					     *default_domain);

netsnmp_transport *netsnmp_tdomain_transport_oid(const oid * dom,
						 size_t dom_len,
						 const u_char * o,
						 size_t o_len,
						 int local);

#ifdef __cplusplus
}
#endif
#endif/*_SNMP_TRANSPORT_H*/
