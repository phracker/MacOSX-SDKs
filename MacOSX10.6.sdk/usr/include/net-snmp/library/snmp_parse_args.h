#ifndef SNMP_PARSE_ARGS_H
#define SNMP_PARSE_ARGS_H
#ifdef __cplusplus
extern "C" {
#endif

int
snmp_parse_args(int argc, char **argv, netsnmp_session *session,
		const char *localOpts, void (*proc)(int, char *const *, int));

void
snmp_parse_args_descriptions(FILE *);

void
snmp_parse_args_usage(FILE *);

#ifdef __cplusplus
}
#endif
#endif
