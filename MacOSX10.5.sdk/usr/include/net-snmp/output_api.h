#ifndef NET_SNMP_LOGGING_API_H
#define NET_SNMP_LOGGING_API_H

    /**
     *  Library API routines concerned with logging and message output
     *    (including error handling and debugging).
     */

#include <net-snmp/types.h>

    /*
     *  For the initial release, this will just refer to the
     *  relevant UCD header files.
     *    In due course, the routines relevant to this area of the
     *  API will be identified, and listed here directly.
     *
     *  But for the time being, this header file is a placeholder,
     *  to allow application writers to adopt the new header file names.
     */

#include <net-snmp/library/snmp_client.h>
#include <net-snmp/library/snmp_debug.h>
#include <net-snmp/library/snmp_logging.h>

#ifndef ERROR_MSG
#define ERROR_MSG(string)	snmp_set_detail(string)
#endif

#endif                          /* NET_SNMP_LOGGING_API_H */
