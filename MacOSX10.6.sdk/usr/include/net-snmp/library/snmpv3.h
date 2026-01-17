/*
 * snmpv3.h
 */

#ifndef SNMPV3_H
#define SNMPV3_H

#ifdef __cplusplus
extern          "C" {
#endif

#define MAX_ENGINEID_LENGTH 128

#define ENGINEID_TYPE_IPV4    1
#define ENGINEID_TYPE_IPV6    2
#define ENGINEID_TYPE_MACADDR 3
#define ENGINEID_TYPE_TEXT    4
#define ENGINEID_TYPE_NETSNMP_RND 128

#define	DEFAULT_NIC "eth0"

    int             setup_engineID(u_char ** eidp, const char *text);
    void            engineID_conf(const char *word, char *cptr);
    void            engineBoots_conf(const char *, char *);
    void            engineIDType_conf(const char *, char *);
    void            engineIDNic_conf(const char *, char *);
    void            snmpv3_authtype_conf(const char *word, char *cptr);
    void            snmpv3_privtype_conf(const char *word, char *cptr);
    void            usm_parse_create_usmUser(const char *token,
                                             char *line);
    void            init_snmpv3(const char *);
    int             init_snmpv3_post_config(int majorid, int minorid,
                                            void *serverarg,
                                            void *clientarg);
    int             init_snmpv3_post_premib_config(int majorid,
                                                   int minorid,
                                                   void *serverarg,
                                                   void *clientarg);
    void            shutdown_snmpv3(const char *type);
    int             snmpv3_store(int majorID, int minorID, void *serverarg,
                                 void *clientarg);
    u_long          snmpv3_local_snmpEngineBoots(void);
    int             snmpv3_clone_engineID(u_char **, size_t *, u_char *,
                                          size_t);
    size_t          snmpv3_get_engineID(u_char * buf, size_t buflen);
    u_char         *snmpv3_generate_engineID(size_t *);
    u_long          snmpv3_local_snmpEngineTime(void);
    int             get_default_secLevel(void);
    const oid      *get_default_authtype(size_t *);
    const oid      *get_default_privtype(size_t *);
    void            snmpv3_set_engineBootsAndTime(int boots, int ttime);
    int             free_engineID(int majorid, int minorid, void *serverarg,
				  void *clientarg);
    int             parse_secLevel_conf(const char* word, char *cptr);

#ifdef __cplusplus
}
#endif
#endif                          /* SNMPV3_H */
