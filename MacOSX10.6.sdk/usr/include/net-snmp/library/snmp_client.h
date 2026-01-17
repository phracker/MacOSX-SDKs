/*
 * snmp_client.h
 */
/***********************************************************
	Copyright 1988, 1989 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of CMU not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

CMU DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
CMU BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************/

#ifndef SNMP_CLIENT_H
#define SNMP_CLIENT_H

#ifdef __cplusplus
extern          "C" {
#endif


    struct snmp_pdu;
    struct snmp_session;
    struct variable_list;

    struct synch_state {
        int             waiting;
        int             status;
        /*
         * status codes 
         */
#define STAT_SUCCESS	0
#define STAT_ERROR	1
#define STAT_TIMEOUT 2
        int             reqid;
        netsnmp_pdu    *pdu;
    };

    int             snmp_set_var_value(netsnmp_variable_list *,
                                       const u_char *, size_t);
    int             snmp_set_var_objid(netsnmp_variable_list * vp,
                                       const oid * objid,
                                       size_t name_length);
    int             snmp_set_var_typed_value(netsnmp_variable_list *
                                             newvar, u_char type,
                                             const u_char * val_str,
                                             size_t val_len);
    int             snmp_set_var_typed_integer(netsnmp_variable_list * newvar,
                                               u_char type, long val);
    void            snmp_replace_var_types(netsnmp_variable_list * vbl,
                                           u_char old_type,
                                           u_char new_type);
    void            snmp_reset_var_buffers(netsnmp_variable_list * var);
    void            snmp_reset_var_types(netsnmp_variable_list * vbl,
                                         u_char new_type);
    int             count_varbinds(netsnmp_variable_list * var_ptr);
    int             count_varbinds_of_type(netsnmp_variable_list * var_ptr,
                                           u_char type);
    netsnmp_variable_list *find_varbind_of_type(netsnmp_variable_list *
                                                var_ptr, u_char type);
    netsnmp_variable_list *find_varbind_in_list(netsnmp_variable_list *vblist,
                                                oid *name, size_t len);

    netsnmp_variable_list *snmp_add_null_var(netsnmp_pdu *, const oid *, size_t);
    netsnmp_pdu    *snmp_pdu_create(int);
    netsnmp_pdu    *snmp_fix_pdu(netsnmp_pdu *, int);
    netsnmp_pdu    *snmp_clone_pdu(netsnmp_pdu *);
    netsnmp_pdu    *snmp_split_pdu(netsnmp_pdu *, int skipCount,
                                   int copyCount);

    unsigned long   snmp_varbind_len(netsnmp_pdu *pdu);
    int             snmp_clone_var(netsnmp_variable_list *,
                                   netsnmp_variable_list *);
    netsnmp_variable_list *snmp_clone_varbind(netsnmp_variable_list *);
    const char     *snmp_errstring(int);
    int             snmp_synch_response(netsnmp_session *, netsnmp_pdu *,
                                        netsnmp_pdu **);
    int             snmp_synch_response_cb(netsnmp_session *,
                                           netsnmp_pdu *, netsnmp_pdu **,
                                           snmp_callback);
    int             snmp_clone_mem(void **, void *, unsigned);

    /*
     * single session API - see snmp_api.h for full details 
     */
    int             snmp_sess_synch_response(void *, netsnmp_pdu *,
                                             netsnmp_pdu **);

void              netsnmp_query_set_default_session(netsnmp_session *);
netsnmp_session * netsnmp_query_get_default_session( void );
int netsnmp_query_get(     netsnmp_variable_list *, netsnmp_session *);
int netsnmp_query_getnext( netsnmp_variable_list *, netsnmp_session *);
int netsnmp_query_walk(    netsnmp_variable_list *, netsnmp_session *);
int netsnmp_query_set(     netsnmp_variable_list *, netsnmp_session *);

#ifdef __cplusplus
}
#endif
#endif                          /* SNMP_CLIENT_H */
