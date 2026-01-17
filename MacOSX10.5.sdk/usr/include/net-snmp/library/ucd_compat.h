/*
 *  UCD compatability definitions & declarations
 *
 */

#ifndef NET_SNMP_UCD_COMPAT_H
#define NET_SNMP_UCD_COMPAT_H

#ifdef __cplusplus
extern          "C" {
#endif

        /*
         * from snmp_api.h 
         */
void            snmp_set_dump_packet(int);
int             snmp_get_dump_packet(void);
void            snmp_set_quick_print(int);
int             snmp_get_quick_print(void);
void            snmp_set_suffix_only(int);
int             snmp_get_suffix_only(void);
void            snmp_set_full_objid(int);
int             snmp_get_full_objid(void);
void            snmp_set_random_access(int);
int             snmp_get_random_access(void);

        /*
         * from parse.h 
         */
void            snmp_set_mib_warnings(int);
void            snmp_set_mib_errors(int);
void            snmp_set_save_descriptions(int);
void            snmp_set_mib_comment_term(int);
void            snmp_set_mib_parse_label(int);

#ifdef __cplusplus
}
#endif
#endif                          /* NET_SNMP_UCD_COMPAT_H */
