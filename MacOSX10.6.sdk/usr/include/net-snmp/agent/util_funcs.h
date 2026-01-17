/*
 *  util_funcs.h:  utilitiy functions for extensible groups.
 */
#ifndef _MIBGROUP_UTIL_FUNCS_H
#define _MIBGROUP_UTIL_FUNCS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "struct.h"

void            Exit(int);
int             shell_command(struct extensible *);
int             exec_command(struct extensible *);
struct extensible *get_exten_instance(struct extensible *, size_t);
int             get_exec_output(struct extensible *);
int             get_exec_pipes(char *cmd, int *fdIn, int *fdOut, int *pid);
WriteMethod     clear_cache;
RETSIGTYPE      restart_doit(int);
WriteMethod     restart_hook;
void            print_mib_oid(oid *, size_t);
void            sprint_mib_oid(char *, oid *, size_t);
int             header_simple_table(struct variable *, oid *, size_t *,
                                    int, size_t *,
                                    WriteMethod ** write_method, int);
int             header_generic(struct variable *, oid *, size_t *, int,
                               size_t *, WriteMethod **);
int             checkmib(struct variable *, oid *, size_t *, int, size_t *,
                         WriteMethod ** write_method, int);
char           *find_field(char *, int);
int             parse_miboid(const char *, oid *);
void            string_append_int(char *, int);
void            wait_on_exec(struct extensible *);
const char     *make_tempfile(void);

#define     satosin(x)      ((struct sockaddr_in *) &(x))
#define     SOCKADDR(x)     (satosin(x)->sin_addr.s_addr)
#ifndef MIB_STATS_CACHE_TIMEOUT
#define MIB_STATS_CACHE_TIMEOUT 5
#endif

typedef void   *mib_table_t;
typedef int     (RELOAD) (mib_table_t);
typedef int     (COMPARE) (const void *, const void *);
mib_table_t     Initialise_Table(int, int, RELOAD*, COMPARE*);
int             Search_Table(mib_table_t, void *, int);
int             Add_Entry(mib_table_t, void *);
void           *Retrieve_Table_Data(mib_table_t, int *);

#ifdef __cplusplus
}
#endif

#endif                          /* _MIBGROUP_UTIL_FUNCS_H */
