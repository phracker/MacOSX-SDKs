/*
 * table_iterator.h 
 */
#ifndef _TABLE_DATA_SET_HANDLER_H_
#define _TABLE_DATA_SET_HANDLER_H_

#ifdef __cplusplus
extern          "C" {
#endif

    /*
     * This helper is designed to completely automate the task of storing
     * tables of data within the agent that are not tied to external data
     * sources (like the kernel, hardware, or other processes, etc).  IE,
     * all rows within a table are expected to be added manually using
     * functions found below.
     */

    void netsnmp_init_table_dataset(void);

#define TABLE_DATA_SET_NAME "netsnmp_table_data_set"

    /*
     * return SNMP_ERR_NOERROR or some SNMP specific protocol error id 
     */
    typedef int     (Netsnmp_Value_Change_Ok) (char *old_value,
                                               size_t old_value_len,
                                               char *new_value,
                                               size_t new_value_len,
                                               void *mydata);

    /*
     * stored within a given row 
     */
    typedef struct netsnmp_table_data_set_storage_s {
        unsigned int    column;

        /*
         * info about it? 
         */
        char            writable;
        Netsnmp_Value_Change_Ok *change_ok_fn;
        void           *my_change_data;

        /*
         * data actually stored 
         */
        u_char          type;
        union {                 /* value of variable */
            void           *voidp;
            long           *integer;
            u_char         *string;
            oid            *objid;
            u_char         *bitstring;
            struct counter64 *counter64;
#ifdef OPAQUE_SPECIAL_TYPES
            float          *floatVal;
            double         *doubleVal;
#endif                          /* OPAQUE_SPECIAL_TYPES */
        } data;
        u_long          data_len;

        struct netsnmp_table_data_set_storage_s *next;
    } netsnmp_table_data_set_storage;

    typedef struct netsnmp_table_data_set_s {
        netsnmp_table_data *table;
        netsnmp_table_data_set_storage *default_row;
        int             allow_creation; /* set to 1 to allow creation of new rows */
        unsigned int    rowstatus_column;
    } netsnmp_table_data_set;

    Netsnmp_Node_Handler netsnmp_table_data_set_helper_handler;

    /*
     * to set, add column, type, (writable) ? 1 : 0 
     */
    /*
     * default value, if not NULL, is the default value used in row
     * creation.  It is copied into the storage template (free your
     * calling argument). 
     */
    int            
        netsnmp_table_set_add_default_row(netsnmp_table_data_set *,
                                          unsigned int, int, int,
                                          void *default_value,
                                          size_t default_value_len);

    /*
     * to set, add column, type, (writable) ? 1 : 0, ... 
     */
#if HAVE_STDARG_H
    void           
        netsnmp_table_set_multi_add_default_row(netsnmp_table_data_set *,
                                                ...);
#else
    void            netsnmp_table_set_multi_add_default_row(va_alist);
#endif
    int             netsnmp_set_row_column(netsnmp_table_row *,
                                           unsigned int, int, const char *,
                                           size_t);
    netsnmp_table_data_set_storage
        *netsnmp_table_data_set_find_column(netsnmp_table_data_set_storage
                                            *, unsigned int);
    netsnmp_table_data_set_storage
       *netsnmp_extract_table_data_set_column(netsnmp_request_info *,
                                              unsigned int);
    int            
        netsnmp_register_table_data_set(netsnmp_handler_registration *,
                                        netsnmp_table_data_set *,
                                        netsnmp_table_registration_info *);
    netsnmp_mib_handler
        *netsnmp_get_table_data_set_handler(netsnmp_table_data_set *);
    netsnmp_table_data_set *netsnmp_create_table_data_set(const char *);
    int             netsnmp_mark_row_column_writable(netsnmp_table_row
                                                     *row, int column,
                                                     int writable);
    NETSNMP_INLINE netsnmp_table_data_set
        *netsnmp_extract_table_data_set(netsnmp_request_info *request);
    void            netsnmp_config_parse_table_set(const char *token,
                                                   char *line);
    void            netsnmp_config_parse_add_row(const char *token,
                                                 char *line);
    NETSNMP_INLINE void netsnmp_table_dataset_add_index(netsnmp_table_data_set
                                                    *table, u_char type);
    NETSNMP_INLINE void netsnmp_table_dataset_add_row(netsnmp_table_data_set
                                                  *table,
                                                  netsnmp_table_row *row);
    NETSNMP_INLINE void netsnmp_table_dataset_remove_row(netsnmp_table_data_set
                                                     *table,
                                                     netsnmp_table_row
                                                     *row);
    NETSNMP_INLINE void netsnmp_table_dataset_delete_row(netsnmp_table_row
                                                     *row);
    NETSNMP_INLINE void    
        netsnmp_table_dataset_remove_and_delete_row(netsnmp_table_data_set
                                                    *table,
                                                    netsnmp_table_row
                                                    *row);
    NETSNMP_INLINE void    
        netsnmp_table_dataset_delete_all_data
        (netsnmp_table_data_set_storage *data);
    NETSNMP_INLINE void    
        netsnmp_table_dataset_replace_row(netsnmp_table_data_set *table,
                                          netsnmp_table_row *origrow,
                                          netsnmp_table_row *newrow);
    netsnmp_table_row *netsnmp_table_data_set_clone_row(netsnmp_table_row
                                                        *row);
    void            netsnmp_register_auto_data_table(netsnmp_table_data_set
                                                     *table_set,
                                                     char
                                                     *registration_name);
    int netsnmp_table_data_num_rows(netsnmp_table_data *table);

#if HAVE_STDARG_H
    void           
        netsnmp_table_set_add_indexes(netsnmp_table_data_set *tset, ...);
#else
    void            netsnmp_table_helper_add_indexes(va_alist);
#endif

#ifdef __cplusplus
}
#endif

#define netsnmp_table_row_add_column(row, type, value, value_len) snmp_varlist_add_variable(&row->indexes, NULL, 0, type, (u_char *) value, value_len)

#endif                          /* _TABLE_DATA_SET_HANDLER_H_ */
