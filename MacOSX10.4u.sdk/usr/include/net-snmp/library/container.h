#ifndef NETSNMP_CONTAINER_H
#define NETSNMP_CONTAINER_H

/*
 * $Id: container.h,v 1.25 2004/09/14 02:29:16 rstory Exp $
 *
 * WARNING: This is a recently created file, and all of it's contents are
 *          subject to change at any time.
 *
 * A basic container template. A generic way for code to store and
 * retrieve data. Allows for interchangable storage algorithms.
 */
#ifndef NET_SNMP_CONFIG_H
#error "Please include <net-snmp/net-snmp-config.h> before this file"
#endif

#include <net-snmp/types.h>
#include <net-snmp/library/factory.h>
#include <net-snmp/library/snmp_logging.h>

#ifdef  __cplusplus
extern "C" {
#endif

    /*************************************************************************
     *
     * function pointer definitions
     *
     *************************************************************************/
    struct netsnmp_iterator_s; /** forward declare */
    struct netsnmp_container_s; /** forward declare */

    /*
     * function returning an int for an operation on a container
     */
    typedef int (netsnmp_container_rc)(struct netsnmp_container_s *);

    /*
     * function returning an int for an operation on a container
     */
    typedef struct netsnmp_iterator_s * (netsnmp_container_it)
        (struct netsnmp_container_s *);

    /*
     * function returning a size_t for an operation on a container
     */
    typedef size_t (netsnmp_container_size)(struct netsnmp_container_s *);

    /*
     * function returning an int for an operation on an object and
     * a container
     */
    typedef int (netsnmp_container_op)(struct netsnmp_container_s *,
                                       const void *data);

    /*
     * function returning an oject for an operation on an object and a
     * container
     */
    typedef void * (netsnmp_container_rtn)(struct netsnmp_container_s *,
                                           const void *data);

    /*
     * function with no return which acts on an object
     */
    typedef void (netsnmp_container_obj_func)(void *data, void *context);

    /*
     * function with no return which acts on an object
     */
    typedef void (netsnmp_container_func)(struct netsnmp_container_s *,
                                          netsnmp_container_obj_func *,
                                          void *context);

    /*
     * function returning an array of objects for an operation on an
     * ojbect and a container
     */
    typedef netsnmp_void_array * (netsnmp_container_set)
        (struct netsnmp_container_s *, void *data);

    /*
     * function returning an int for a comparison between two objects
     */
    typedef int (netsnmp_container_compare)(const void *lhs,
                                            const void *rhs);

    /*************************************************************************
     *
     * Basic container
     *
     *************************************************************************/
    typedef struct netsnmp_container_s {
       
       /*
        * pointer for container implementation
        */
       void *         container_data;

       /*
        * returns the number of items in a container
        */
       netsnmp_container_size  *get_size;
       
       /*
        * initialize a container
        */
       netsnmp_container_rc    *init;

       /*
        * release memory used by a container.
        *
        * Note: if your data structures contained allocated
        * memory, you are responsible for releasing that
        * memory before calling this function!
        */
       netsnmp_container_rc    *cfree;

       /*
        * add an entry to the container
        */
       netsnmp_container_op    *insert;

       /*
        * remove an entry from the container
        */
       netsnmp_container_op    *remove;

       /*
        * release memory for an entry from the container
        */
       netsnmp_container_op    *release;

       /*
        * Note: do not change the key!  If you need to
        * change a key, remove the entry, change the key,
        * and the re-add the entry.
        */

       /*
        * find the entry in the container with the same key
        *
        */
       netsnmp_container_rtn   *find;

       /*
        * find the entry in the container with the next highest key
        *
        * If the key is NULL, return the first item in the container.
        */
       netsnmp_container_rtn   *find_next;

       /*
        * find all entries in the container which match the partial key
        * returns allocated memory (netsnmp_void_array). User is responsible
        * for releasing this memory (free(array->array), free(array)).
        * DO NOT FREE ELEMENTS OF THE ARRAY, because they are the same pointers
        * stored in the container.
        */
       netsnmp_container_set            *get_subset;

       /*
        * function to return an iterator for the container
        */
       netsnmp_container_it           *get_iterator;

       /*
        * function to call another function for each object in the container
        */
       netsnmp_container_func         *for_each;

       /*
        * specialized version of for_each used to optimize cleanup.
        * clear the container, optionally calling a function for each item.
        */
       netsnmp_container_func         *clear;

       /*
        * function to compare two object stored in the container.
        *
        * Returns:
        *
        *   -1  LHS < RHS
        *    0  LHS = RHS
        *    1  LHS > RHS
        */
       netsnmp_container_compare        *compare;

       /*
        * same as compare, but RHS will be a partial key
        */
       netsnmp_container_compare        *ncompare;

       /*
        * unique name for finding a particular container in a list
        */
       char *container_name;

       /*
        * containers can contain other containers (additional indexes)
        */
       struct netsnmp_container_s *next, *prev;

    } netsnmp_container;

    /*
     * initialize/free a container of container factories. used by
     * netsnmp_container_find* functions.
     */
    void netsnmp_container_init_list(void);
    void netsnmp_container_free_list(void);

    /*
     * register a new container factory
     */
    int netsnmp_container_register(const char* name, netsnmp_factory *f);

    /*
     * search for and create a container from a list of types or a
     * specific type.
     */
    netsnmp_container * netsnmp_container_find(const char *type_list);
    netsnmp_container * netsnmp_container_get(const char *type);

    /*
     * utility routines
     */
    void netsnmp_container_add_index(netsnmp_container *primary,
                                     netsnmp_container *new_index);


    netsnmp_factory *netsnmp_container_get_factory(const char *type);

    /*
     * common comparison routines
     */
    /** first data element is a 'netsnmp_index' */
    int netsnmp_compare_netsnmp_index(const void *lhs, const void *rhs);
    int netsnmp_ncompare_netsnmp_index(const void *lhs, const void *rhs);

    /** first data element is a 'char *' */
    int netsnmp_compare_cstring(const void * lhs, const void * rhs);
    int netsnmp_ncompare_cstring(const void * lhs, const void * rhs);

    /** useful for octet strings */
    int netsnmp_compare_mem(const char * lhs, size_t lhs_len,
                            const char * rhs, size_t rhs_len);

    /** for_each callback to call free on data item */
    void  netsnmp_container_simple_free(void *data, void *context);

    /*
     * useful macros (x = container; k = key; c = user context)
     */
#define CONTAINER_FIRST(x)          (x)->find_next(x,NULL)
#define CONTAINER_FIND(x,k)         (x)->find(x,k)
#define CONTAINER_NEXT(x,k)         (x)->find_next(x,k)
/*
 * GET_SUBSET returns allocated memory (netsnmp_void_array). User is responsible
 * for releasing this memory (free(array->array), free(array)).
 * DO NOT FREE ELEMENTS OF THE ARRAY, because they are the same pointers
 * stored in the container.
 */
#define CONTAINER_GET_SUBSET(x,k)   (x)->get_subset(x,k)
#define CONTAINER_SIZE(x)           (x)->get_size(x)
#define CONTAINER_ITERATOR(x)       (x)->get_iterator(x)
#define CONTAINER_COMPARE(x,l,r)    (x)->compare(l,r)
#define CONTAINER_FOR_EACH(x,f,c)   (x)->for_each(x,f,c)

    /*
     * if you are getting multiple definitions of these three
     * inline functions, you most likely have optimizations turned off.
     * Either turn them back on, or define NETSNMP_NO_INLINE
     */
#ifndef NETSNMP_USE_INLINE /* default is to inline */
    /*
     * insert k into all containers
     */
    int CONTAINER_INSERT(netsnmp_container *x, const void *k);

    /*
     * remove k from all containers
     */
    int CONTAINER_REMOVE(netsnmp_container *x, const void *k);

    /*
     * clear all containers. When clearing the *first* container, and
     * *only* the first container, call the function f for each item.
     * After calling this function, all containers should be empty.
     */
    void CONTAINER_CLEAR(netsnmp_container *x, netsnmp_container_obj_func *f,
                        void *c);
    /*
     * free all containers
     */
    int CONTAINER_FREE(netsnmp_container *x);
#else
    /*------------------------------------------------------------------
     * These functions should EXACTLY match the function version in
     * container.c. If you change one, change them both.
     */
    NETSNMP_STATIC_INLINE /* gcc docs recommend static w/inline */
    int CONTAINER_INSERT(netsnmp_container *x, const void *k)
    {
        int rc2, rc = 0;
        
        /** start at first container */
        while(x->prev)
            x = x->prev;
        while(x) {
            rc2 = x->insert(x,k);
            if (rc2) {
                snmp_log(LOG_ERR,"error on subcontainer insert (%d)\n", rc2);
                rc = rc2;
            }
            x = x->next;
        }
        return rc;
    }
    
    /*------------------------------------------------------------------
     * These functions should EXACTLY match the function version in
     * container.c. If you change one, change them both.
     */
    NETSNMP_STATIC_INLINE /* gcc docs recommend static w/inline */
    int CONTAINER_REMOVE(netsnmp_container *x, const void *k)
    {
        int rc2, rc = 0;
        
        /** start at last container */
        while(x->next)
            x = x->next;
        while(x) {
            rc2 = x->remove(x,k);
            if (rc2) {
                snmp_log(LOG_ERR,"error on subcontainer remove (%d)\n", rc2);
                rc = rc2;
            }
            x = x->prev;
            
        }
        return rc;
    }
    
    /*------------------------------------------------------------------
     * These functions should EXACTLY match the function version in
     * container.c. If you change one, change them both.
     */
    NETSNMP_STATIC_INLINE /* gcc docs recommend static w/inline */
    int CONTAINER_FREE(netsnmp_container *x)
    {
	int  rc2, rc = 0;
        
        /** start at last container */
        while(x->next)
            x = x->next;
        while(x) {
            netsnmp_container *tmp;
            tmp = x->prev;
            if (NULL != x->container_name)
                SNMP_FREE(x->container_name);
            rc2 = x->cfree(x);
            if (rc2) {
                snmp_log(LOG_ERR,"error on subcontainer cfree (%d)\n", rc2);
                rc = rc2;
            }
            x = tmp;
        }
        return rc;
    }

    /*------------------------------------------------------------------
     * These functions should EXACTLY match the function version in
     * container.c. If you change one, change them both.
     */
    /*
     * clear all containers. When clearing the *first* container, and
     * *only* the first container, call the function f for each item.
     * After calling this function, all containers should be empty.
     */
    NETSNMP_STATIC_INLINE /* gcc docs recommend static w/inline */
    void CONTAINER_CLEAR(netsnmp_container *x, netsnmp_container_obj_func *f,
                        void *c)
    {
        /** start at last container */
        while(x->next)
            x = x->next;
        while(x->prev) {
            x->clear(x, NULL, c);
            x = x->prev;
        }
        x->clear(x, f, c);
    }

    /*------------------------------------------------------------------
     * These functions should EXACTLY match the function version in
     * container.c. If you change one, change them both.
     */
    /*
     * Find a sub-container with the given name
     */
    NETSNMP_STATIC_INLINE /* gcc docs recommend static w/inline */
    netsnmp_container *SUBCONTAINER_FIND(netsnmp_container *x,
                                         const char* name)
    {
        if ((NULL == x) || (NULL == name))
            return NULL;

        /** start at first container */
        while(x->prev)
            x = x->prev;
        while(x) {
            if ((NULL != x->container_name) &&
                (0 == strcmp(name,x->container_name)))
                break;
            x = x->next;
        }
        return x;
    }

#endif
    
    /*************************************************************************
     *
     * container iterator
     *
     *************************************************************************/
    /*
     * function returning an int for an operation on an iterator
     */
    typedef int (netsnmp_iterator_rc)(struct netsnmp_iterator_s *);

    /*
     * function returning an int for an operation on an iterator and
     * an object in the container.
     */
    typedef int (netsnmp_iterator_rc_op)(struct netsnmp_iterator_s *,
                                         void *data);

    /*
     * function returning an oject for an operation on an iterator
     */
    typedef void * (netsnmp_iterator_rtn)(struct netsnmp_iterator_s *);

    typedef struct netsnmp_iterator_s {

       netsnmp_container              *container;

       void                           *context;

       netsnmp_iterator_rc           *init;
       netsnmp_iterator_rc_op        *position;
       netsnmp_iterator_rtn          *first;
       netsnmp_iterator_rtn          *next;
       netsnmp_iterator_rtn          *last;

    } netsnmp_iterator;


#define ITERATOR_FIRST(x)  x->first(x)
#define ITERATOR_NEXT(x)   x->next(x)
#define ITERATOR_LAST(x)   x->last(x)


    /*************************************************************************
     *
     * Sorted container
     *
     *************************************************************************/
    typedef struct netsnmp_sorted_container_s {
       
       netsnmp_container                bc;
       
       /*
        * methods to manipulate container
        */

       netsnmp_container_rtn            *first;
       netsnmp_container_rtn            *next;
       netsnmp_container_set            *subset;
       
    } netsnmp_sorted_container;
    

    void
    netsnmp_init_sorted_container(netsnmp_sorted_container  *sc,
                                  netsnmp_container_rtn     *first,
                                  netsnmp_container_rtn     *next,
                                  netsnmp_container_set     *subset);
    
    
    
#ifdef  __cplusplus
}
#endif

#endif /** NETSNMP_CONTAINER_H */
