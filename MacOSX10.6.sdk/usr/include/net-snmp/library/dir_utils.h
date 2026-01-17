
#ifndef NETSNMP_DIR_UTILS_H
#define NETSNMP_DIR_UTILS_H

#ifdef _cplusplus
extern "C" {
#endif

    /*------------------------------------------------------------------
     *
     * Prototypes
     */
    netsnmp_container * netsnmp_directory_container_read(netsnmp_container *c,
                                                         const char *dir,
                                                         u_int flags);
    void netsnmp_directory_container_free(netsnmp_container *c);

        

    /*------------------------------------------------------------------
     *
     * flags
     */
#define NETSNMP_DIR_RECURSE                           0x1

    
        
#ifdef _cplusplus
}
#endif

#endif /* NETSNMP_DIR_UTILS_H */
