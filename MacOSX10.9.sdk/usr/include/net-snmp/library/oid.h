#ifndef NETSNMP_LIBRARY_OID_H
#define NETSNMP_LIBRARY_OID_H

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif

#ifndef EIGHTBIT_SUBIDS
typedef uint32_t oid;
#define MAX_SUBID   0xFFFFFFFF
#define NETSNMP_PRIo NETSNMP_PRI32
#else
typedef uint8_t oid;
#define MAX_SUBID   0xFF
#define NETSNMP_PRIo ""
#endif

#endif /* NETSNMP_LIBRARY_OID_H */
