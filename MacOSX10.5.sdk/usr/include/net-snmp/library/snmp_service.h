#ifndef _SNMP_SERVICE_H
#define _SNMP_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Default port handling */

extern int
netsnmp_register_default_domain(const char* application, const char* domain);

extern const char*
netsnmp_lookup_default_domain(const char* application);

extern void
netsnmp_clear_default_domain(void);

extern int
netsnmp_register_default_target(const char* application, const char* domain,
				const char* target);

extern const char*
netsnmp_lookup_default_target(const char* application, const char* domain);

extern void
netsnmp_clear_default_target(void);

extern void
netsnmp_register_service_handlers(void);

#ifdef __cplusplus
}
#endif

#endif /* _SNMP_SERVICE_H */
