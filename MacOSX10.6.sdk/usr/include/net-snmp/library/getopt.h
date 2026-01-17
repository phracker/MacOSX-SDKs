#ifndef _GETOPT_H_
#define _GETOPT_H_ 1

#ifdef __cplusplus
extern          "C" {
#endif

NETSNMP_IMPORT int   getopt(int, char *const *, const char *);
NETSNMP_IMPORT char *optarg;
NETSNMP_IMPORT int   optind, opterr, optopt, optreset;

#ifdef __cplusplus
}
#endif
#endif
