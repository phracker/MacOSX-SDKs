/*
 * callback.c: A generic callback mechanism 
 */

#ifndef CALLBACK_H
#define CALLBACK_H

#ifdef __cplusplus
extern          "C" {
#endif

#define MAX_CALLBACK_IDS    2
#define MAX_CALLBACK_SUBIDS 16

    /*
     * Callback Major Types 
     */
#define SNMP_CALLBACK_LIBRARY     0
#define SNMP_CALLBACK_APPLICATION 1

    /*
     * SNMP_CALLBACK_LIBRARY minor types 
     */
#define SNMP_CALLBACK_POST_READ_CONFIG	        0
#define SNMP_CALLBACK_STORE_DATA	        1
#define SNMP_CALLBACK_SHUTDOWN		        2
#define SNMP_CALLBACK_POST_PREMIB_READ_CONFIG	3
#define SNMP_CALLBACK_LOGGING			4
#define SNMP_CALLBACK_SESSION_INIT		5

    typedef int     (SNMPCallback) (int majorID, int minorID,
                                    void *serverarg, void *clientarg);

    struct snmp_gen_callback {
        SNMPCallback   *sc_callback;
        void           *sc_client_arg;
        int             priority;
        struct snmp_gen_callback *next;
    };

    /*
     * function prototypes 
     */
    void            init_callbacks(void);

    int             netsnmp_register_callback(int major, int minor,
                                              SNMPCallback * new_callback,
                                              void *arg, int priority);
    int             snmp_register_callback(int major, int minor,
                                           SNMPCallback * new_callback,
                                           void *arg);
    int             snmp_call_callbacks(int major, int minor,
                                        void *caller_arg);
    int             snmp_callback_available(int major, int minor);      /* is >1 available */
    int             snmp_count_callbacks(int major, int minor); /* ret the number registered */
    int             snmp_unregister_callback(int major, int minor,
                                             SNMPCallback * new_callback,
                                             void *arg, int matchargs);
    void            clear_callback (void);
    struct snmp_gen_callback *snmp_callback_list(int major, int minor);

#ifdef __cplusplus
}
#endif
#endif                          /* CALLBACK_H */
