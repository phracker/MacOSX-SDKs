#ifndef ROW_MERGE_H
#define ROW_MERGE_H

/*
 * This row_merge helper splits a whole bunch of requests into chunks
 * based on the row index that they refer to, and passes all requests
 * for a given row to the lower handlers.
 */

#ifdef __cplusplus
extern          "C" {
#endif

    netsnmp_mib_handler *netsnmp_get_row_merge_handler(int);
    int   netsnmp_register_row_merge(netsnmp_handler_registration *reginfo);
    void  netsnmp_init_row_merge(void);

    Netsnmp_Node_Handler netsnmp_row_merge_helper_handler;

#ifdef __cplusplus
}
#endif
#endif
