#include "bsd.h"

#define PCB_TABLE 1
#undef TCP_SYMBOL
#define TCP_SYMBOL "tcbtable"
#undef TCP_TTL_SYMBOL
#define TCP_TTL_SYMBOL "ip_defttl"
#undef UDB_SYMBOL
#define UDB_SYMBOL "udbtable"
#undef NPROC_SYMBOL
#undef PROC_SYMBOL

#define MBPOOL_SYMBOL	"mbpool"
#define MCLPOOL_SYMBOL	"mclpool"

/*
 * inp_next symbol 
 */
#undef INP_NEXT_SYMBOL
#define INP_NEXT_SYMBOL inp_queue.cqe_next
#undef INP_PREV_SYMBOL
#define INP_PREV_SYMBOL inp_queue.cqe_prev
#define HAVE_INPCBTABLE 1

#define UTMP_FILE _PATH_UTMP

#ifndef netbsd1
# define netbsd1 1
#endif

/*
 * fixups for broken AC_CHECK_IFNET_FOR() 
 */
/*
 * XXX - Remove when fixed in configure.in 
 */
#undef STRUCT_IFNET_HAS_IF_BAUDRATE
#define STRUCT_IFNET_HAS_IF_BAUDRATE 1
#undef STRUCT_IFNET_HAS_IF_TYPE
#define STRUCT_IFNET_HAS_IF_TYPE 1
#undef STRUCT_IFNET_HAS_IF_IMCASTS
#define STRUCT_IFNET_HAS_IF_IMCASTS 1
#undef STRUCT_IFNET_HAS_IF_IQDROPS
#define STRUCT_IFNET_HAS_IF_IQDROPS 1
#undef STRUCT_IFNET_HAS_IF_NOPROTO
#define STRUCT_IFNET_HAS_IF_NOPROTO 1
#undef STRUCT_IFNET_HAS_IF_OMCASTS
#define STRUCT_IFNET_HAS_IF_OMCASTS 1
#undef STRUCT_IFNET_HAS_IF_IBYTES
#define STRUCT_IFNET_HAS_IF_IBYTES 1
#undef STRUCT_IFNET_HAS_IF_OBYTES
#define STRUCT_IFNET_HAS_IF_OBYTES 1
