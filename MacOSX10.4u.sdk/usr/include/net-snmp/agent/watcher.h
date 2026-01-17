/*
 * watcher.h 
 */
#ifndef NETSNMP_WATCHER_H
#define NETSNMP_WATCHER_H

#ifdef __cplusplus
extern "C" {
#endif

#define WATCHER_FIXED_SIZE    0x01
#define WATCHER_MAX_SIZE      0x02

typedef struct netsnmp_watcher_info_s {
    void     *data;
    size_t    data_size;
    size_t    max_size;
    u_char    type;
    int       flags;
} netsnmp_watcher_info;

int netsnmp_register_watched_instance( netsnmp_handler_registration *reginfo,
                                       netsnmp_watcher_info         *winfo);
int netsnmp_register_watched_scalar(   netsnmp_handler_registration *reginfo,
                                       netsnmp_watcher_info         *winfo);
int netsnmp_register_watched_timestamp(netsnmp_handler_registration *reginfo,
                                       marker_t timestamp);
int netsnmp_register_watched_spinlock(netsnmp_handler_registration *reginfo,
                                      int *spinlock);    

#define WATCHER_HANDLER_NAME "watcher"

netsnmp_mib_handler  *netsnmp_get_watcher_handler(void);
netsnmp_watcher_info *netsnmp_create_watcher_info(void *, size_t, u_char, int);
Netsnmp_Node_Handler  netsnmp_watcher_helper_handler;

netsnmp_mib_handler  *netsnmp_get_watched_timestamp_handler(void);
Netsnmp_Node_Handler  netsnmp_watched_timestamp_handler;

netsnmp_mib_handler  *netsnmp_get_watched_spinlock_handler(void);
Netsnmp_Node_Handler  netsnmp_watched_spinlock_handler;

#ifdef __cplusplus
}
#endif

#endif /** NETSNMP_WATCHER_H */
