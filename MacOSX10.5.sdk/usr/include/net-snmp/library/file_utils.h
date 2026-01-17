#ifndef NETSNMP_FILE_UTILS_H
#define NETSNMP_FILE_UTILS_H

#ifdef _cplusplus
extern "C" {
#endif

    
    /*------------------------------------------------------------------
     *
     * structures
     *
     */
    typedef struct netsnmp_file_s {
        
        /*
         * file name
         */
        char                   *name;
        
        /*
         * file descriptor for the file
         */
        int                     fd;

        /*
         * filesystem flags
         */
        int                     fs_flags;

        /*
         * open/create mode
         */
        mode_t                  mode;

        /*
         * netsnmp flags
         */
        u_int                   ns_flags;



        /*
         * future expansion
         */
        netsnmp_data_list      *extras;

    } netsnmp_file;


    
    /*------------------------------------------------------------------
     *
     * Prototypes
     *
     */
    netsnmp_file * netsnmp_file_create(void);
    netsnmp_file * netsnmp_file_fill(netsnmp_file * filei, const char* name,
                                     int fs_flags, mode_t mode, u_int ns_flags);
    int netsnmp_file_release(netsnmp_file * filei);

    int netsnmp_file_open(netsnmp_file * filei);
    int netsnmp_file_close(netsnmp_file * filei);

        

    /*------------------------------------------------------------------
     *
     * flags
     *
     */
#define NETSNMP_FILE_NO_AUTOCLOSE                         0x00000001
#define NETSNMP_FILE_                                     0x00000002

    /*------------------------------------------------------------------
     *
     * macros
     *
     */
#define NS_FI_AUTOCLOSE(x) (0 == (x & NETSNMP_FILE_NO_AUTOCLOSE))
#define NS_FI_(x) (0 == (x & NETSNMP_FILE_))

    
        
#ifdef _cplusplus
}
#endif

#endif /* NETSNMP_FILE_UTILS_H */
