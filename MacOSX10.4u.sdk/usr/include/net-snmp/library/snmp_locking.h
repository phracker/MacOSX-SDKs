
/*
 * snmp_locking.h - multi-thread resource locking support declarations 
 */
/*
 * Author: Markku Laukkanen
 * Created: 6-Sep-1999
 * History:
 *  8-Sep-1999 M. Slifcak method names changed;
 *                        use array of resource locking structures.
 *  3-Jan-2001 R. Story   copy mt_resource.h to snmp_locking.h
 */

#ifndef SNMP_LOCKING_H
#define SNMP_LOCKING_H

#ifdef __cplusplus
extern          "C" {
#endif

#ifdef NS_REENTRANT

#if HAVE_PTHREAD_H
#include <pthread.h>
typedef pthread_mutex_t mutex_type;
#ifdef pthread_mutexattr_default
#define MT_MUTEX_INIT_DEFAULT pthread_mutexattr_default
#else
#define MT_MUTEX_INIT_DEFAULT 0
#endif

#elif defined(WIN32) || defined(cygwin)
#include <windows.h>
typedef CRITICAL_SECTION mutex_type;
#else
                    error "There is no re-entrant support as defined."
#endif  /*  HAVE_PTHREAD_H  */

int	netsnmp_mutex_init(mutex_type *);
int     netsnmp_mutex_lock(mutex_type *);
int     netsnmp_mutex_unlock(mutex_type *);
int     netsnmp_mutex_destroy_mutex(mutex_type *);

#else                           /* !NS_REENTRANT */

#define netsnmp_mutex_init(x) do {} while (0)
#define netsnmp_mutex_lock(x) do {} while (0)
#define netsnmp_mutex_unlock(x) do {} while (0)
#define netsnmp_mutex_destroy_mutex(x) do {} while (0)

#endif                          /* !NS_REENTRANT */

#ifdef __cplusplus
}
#endif
#endif /*  SNMP_LOCKING_H  */
