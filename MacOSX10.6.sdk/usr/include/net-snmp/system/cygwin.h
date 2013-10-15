#include <net-snmp/system/generic.h>

/* got socklen_t? */
#define HAVE_SOCKLEN_T 1

#ifdef HAVE_STDINT_H
#include <stdint.h>	/* uint32_t */
#endif

#undef HAVE_WINSOCK_H
#undef bsdlike
#undef MBSTAT_SYMBOL
#undef TOTAL_MEMORY_SYMBOL

#define UDP_ADDRESSES_IN_HOST_ORDER 1
#define UDP_PORTS_IN_HOST_ORDER 1
