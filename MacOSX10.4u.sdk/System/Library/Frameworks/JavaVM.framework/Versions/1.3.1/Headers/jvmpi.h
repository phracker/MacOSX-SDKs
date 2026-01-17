/*
 * Copyright 2002 Sun Microsystems, Inc. All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */

#ifndef _JAVASOFT_JVMPI_H_
#define _JAVASOFT_JVMPI_H_

#include "jni.h"

#define JVMPI_VERSION_1   ((jint)0x10000001)  /* implied 0 for minor version */
#define JVMPI_VERSION_1_1 ((jint)0x10000002)

#ifdef __cplusplus
extern "C" {
#endif
  typedef void (*jvmpi_void_function_of_void)(void *);
#ifdef __cplusplus
}
#endif

/****************************************************************
 * Profiler interface data structures.
 ****************************************************************/
/* identifier types. */
struct _jobjectID;
typedef struct _jobjectID * jobjectID;       /* type of object ids */ 

/* raw monitors */
struct _JVMPI_RawMonitor;
typedef struct _JVMPI_RawMonitor * JVMPI_RawMonitor;

/* call frame */
typedef struct {
    jint lineno;                      /* line number in the source file */
    jmethodID method_id;              /* method executed in this frame */
} JVMPI_CallFrame;

/* call trace */
typedef struct {
    JNIEnv *env_id;                   /* Env where trace was recorded */
    jint num_frames;                  /* number of frames in this trace */
    JVMPI_CallFrame *frames;          /* frames */
} JVMPI_CallTrace;

/* method */
typedef struct {
    char *method_name;                /* name of method */
    char *method_signature;           /* signature of method */
    jint start_lineno;                /* -1 if native, abstract .. */
    jint end_lineno;                  /* -1 if native, abstract .. */
    jmethodID method_id;              /* id assigned to this method */
} JVMPI_Method;

/* Field */
typedef struct {
    char *field_name;                 /* name of field */
    char *field_signature;            /* signature of field */
} JVMPI_Field;

/* line number info for a compiled method */
typedef struct {
    jint offset;                      /* offset from beginning of method */
    jint lineno;                      /* lineno from beginning of src file */
} JVMPI_Lineno;

/* event */
typedef struct {
    jint event_type;                  /* event_type */
    JNIEnv *env_id;                   /* env where this event occured */
  
    union {
        struct {
	    const char *class_name;   /* class name */
	    char *source_name;        /* name of source file */
	    jint num_interfaces;      /* number of interfaces implemented */
  	    jint num_methods;         /* number of methods in the class */
	    JVMPI_Method *methods;    /* methods */
	    jint num_static_fields;   /* number of static fields */
	    JVMPI_Field *statics;     /* static fields */
	    jint num_instance_fields; /* number of instance fields */
	    JVMPI_Field *instances;   /* instance fields */
	    jobjectID class_id;       /* id of the class object */
	} class_load;

        struct {
	    jobjectID class_id;       /* id of the class object */
	} class_unload;

        struct {
	    unsigned char *class_data;        /* content of class file */
	    jint class_data_len;              /* class file length */
	    unsigned char *new_class_data;    /* instrumented class file */
	    jint new_class_data_len;          /* new class file length */
	    void * (*malloc_f)(unsigned int); /* memory allocation function */
	} class_load_hook;

        struct {
            jint arena_id;
	    jobjectID class_id;       /* id of object class */
	    jint is_array;            /* JVMPI_NORMAL_OBJECT, ... */
	    jint size;                /* size in number of bytes */
	    jobjectID obj_id;         /* id assigned to this object */
        } obj_alloc;

        struct {
	    jobjectID obj_id;         /* id of the object */
	} obj_free;

        struct {
	    jint arena_id;            /* cur arena id */
	    jobjectID obj_id;         /* cur object id */
	    jint new_arena_id;        /* new arena id */
	    jobjectID new_obj_id;     /* new object id */	  
	} obj_move;

        struct {
	    jint arena_id;            /* id of arena */
	    const char *arena_name;   /* name of arena */
	} new_arena;

        struct {
	    jint arena_id;            /* id of arena */
	} delete_arena;

        struct {
	    char *thread_name;        /* name of thread */
	    char *group_name;         /* name of group */
	    char *parent_name;        /* name of parent */
	    jobjectID thread_id;      /* id of the thread object */
	    JNIEnv *thread_env_id;
        } thread_start;

        struct {
	    int dump_level;           /* level of the heap dump info */
	    char *begin;              /* where all the root records begin,
					 please see the heap dump buffer 
				         format described below */
	    char *end;                /* where the object records end. */
	    jint num_traces;          /* number of thread traces, 
				         0 if dump level = JVMPI_DUMP_LEVEL_0 */
	    JVMPI_CallTrace *traces;  /* thread traces collected during 
					 heap dump */ 
	} heap_dump;

        struct {
	    jobjectID obj_id;         /* object id */
	    jobject ref_id;           /* id assigned to the globalref */
	} jni_globalref_alloc;
      
        struct {
	    jobject ref_id;           /* id of the global ref */
	} jni_globalref_free;

        struct {
	    jmethodID method_id;      /* method */
	} method;

        struct {
	    jmethodID method_id;      /* id of method */
	    jobjectID obj_id;         /* id of target object */
	} method_entry2;

        struct {
	    jmethodID method_id;        /* id of compiled method */
	    void *code_addr;            /* code start addr. in memory */
	    jint code_size;             /* code size */
	    jint lineno_table_size;     /* size of lineno table */
	    JVMPI_Lineno *lineno_table; /* lineno info */
	} compiled_method_load;
        
        struct {
	    jmethodID method_id;        /* id of unloaded compiled method */
	} compiled_method_unload;

	struct {
	    jmethodID method_id; /* id of the method the instruction belongs to */
	    jint offset;         /* instruction offset in the method's bytecode */
	    union {
		struct {
		    jboolean is_true; /* whether true or false branch is taken  */
		} if_info;
		struct {
		    jint key; /* top stack value used as an index */
		    jint low; /* min value of the index           */
		    jint hi;  /* max value of the index           */
		} tableswitch_info;
		struct {
		    jint chosen_pair_index; /* actually chosen pair index (0-based)
                                             * if chosen_pair_index == pairs_total then
                                             * the 'default' branch is taken
                                             */
		    jint pairs_total;       /* total number of lookupswitch pairs */
		} lookupswitch_info;
	    } u;
	} instruction;
	
        struct {
	    char *begin;                /* beginning of dump buffer, 
					   see below for format */
	    char *end;                  /* end of dump buffer */
	    jint num_traces;            /* number of traces */
	    JVMPI_CallTrace *traces;    /* traces of all threads */
	    jint *threads_status;       /* status of all threads */
	} monitor_dump;

        struct {
	    const char *name;           /* name of raw monitor */
	    JVMPI_RawMonitor id;        /* id */
	} raw_monitor;

        struct {
	    jobjectID object;           /* Java object */
	} monitor;

        struct {
	    jobjectID object;           /* Java object */
	    jlong timeout;              /* timeout period */
	} monitor_wait;

        struct {
	    jlong used_objects;
	    jlong used_object_space;
	    jlong total_object_space;
	} gc_info;

        struct {
	    jint data_len;
	    char *data;
	} object_dump;
    } u;
} JVMPI_Event;

/* interface functions */
typedef struct {
    jint version;   /* JVMPI version */
    
    /* ------interface implemented by the profiler------ */

    /**
     * Function called by the JVM to notify an event. 
     */
    void (*NotifyEvent)(JVMPI_Event *event);
  
    /* ------interface implemented by the JVM------ */
    
    /**
     * Function called by the profiler to enable/disable/send notification 
     * for a particular event type.  
     * 
     * event_type - event_type
     * arg - event specific arg
     *
     * return JVMPI_NOT_AVAILABLE, JVMPI_SUCCESS or JVMPI_FAIL
     */
    jint (*EnableEvent)(jint event_type, void *arg);
    jint (*DisableEvent)(jint event_type, void *arg);
    jint (*RequestEvent)(jint event_type, void *arg);
  
    /**
     * Function called by the profiler to get a stack
     * trace from the JVM.
     *
     * trace - trace data structure to be filled
     * depth - maximum depth of the trace.
     */
    void (*GetCallTrace)(JVMPI_CallTrace *trace, jint depth);

    /**
     * Function called by profiler when it wants to exit/stop.
     */
    void (*ProfilerExit)(jint);

    /**
     * Utility functions provided by the JVM.
     */
    JVMPI_RawMonitor (*RawMonitorCreate)(char *lock_name);
    void (*RawMonitorEnter)(JVMPI_RawMonitor lock_id);
    void (*RawMonitorExit)(JVMPI_RawMonitor lock_id);
    void (*RawMonitorWait)(JVMPI_RawMonitor lock_id, jlong ms);
    void (*RawMonitorNotifyAll)(JVMPI_RawMonitor lock_id);
    void (*RawMonitorDestroy)(JVMPI_RawMonitor lock_id);

    /**
     * Function called by the profiler to get the current thread's CPU time.
     *
     * return time in nanoseconds;
     */
    jlong (*GetCurrentThreadCpuTime)(void);

    void (*SuspendThread)(JNIEnv *env);
    void (*ResumeThread)(JNIEnv *env);
    jint (*GetThreadStatus)(JNIEnv *env);
    jboolean (*ThreadHasRun)(JNIEnv *env);

    /* This function can be called safely only after JVMPI_EVENT_VM_INIT_DONE
       notification by the JVM. */
    jint (*CreateSystemThread)(char *name, jint priority, void (*f)(void *));

    /* thread local storage access functions to avoid locking in time 
       critical functions */
    void (*SetThreadLocalStorage)(JNIEnv *env_id, void *ptr);
    void * (*GetThreadLocalStorage)(JNIEnv *env_id);

    /* control GC */
    void (*DisableGC)(void);
    void (*EnableGC)(void);
    void (*RunGC)(void);

    jobjectID (*GetThreadObject)(JNIEnv *env);
    jobjectID (*GetMethodClass)(jmethodID mid);

    /* JNI <-> jobject conversions */
    jobject   (*jobjectID2jobject)(jobjectID jid);
    jobjectID (*jobject2jobjectID)(jobject jobj);

} JVMPI_Interface;

/* type of argument passed to RequestEvent for heap dumps */
typedef struct {
    jint heap_dump_level;
} JVMPI_HeapDumpArg;

/**********************************************************************
 * Constants and formats used in JVM Profiler Interface.
 **********************************************************************/
/*
 * Event type constants.
 */
#define JVMPI_EVENT_METHOD_ENTRY            ((jint)1) 
#define JVMPI_EVENT_METHOD_ENTRY2           ((jint)2) 
#define JVMPI_EVENT_METHOD_EXIT             ((jint)3) 

#define JVMPI_EVENT_OBJECT_ALLOC            ((jint)4) 
#define JVMPI_EVENT_OBJECT_FREE             ((jint)5) 
#define JVMPI_EVENT_OBJECT_MOVE             ((jint)6) 

#define JVMPI_EVENT_COMPILED_METHOD_LOAD    ((jint)7) 
#define JVMPI_EVENT_COMPILED_METHOD_UNLOAD  ((jint)8) 

#define JVMPI_EVENT_INSTRUCTION_START       ((jint)9) 

#define JVMPI_EVENT_THREAD_START           ((jint)33) 
#define JVMPI_EVENT_THREAD_END             ((jint)34) 

#define JVMPI_EVENT_CLASS_LOAD_HOOK        ((jint)35) 

#define JVMPI_EVENT_HEAP_DUMP                     ((jint)37) 
#define JVMPI_EVENT_JNI_GLOBALREF_ALLOC           ((jint)38) 
#define JVMPI_EVENT_JNI_GLOBALREF_FREE            ((jint)39) 
#define JVMPI_EVENT_JNI_WEAK_GLOBALREF_ALLOC      ((jint)40) 
#define JVMPI_EVENT_JNI_WEAK_GLOBALREF_FREE       ((jint)41) 
#define JVMPI_EVENT_CLASS_LOAD                    ((jint)42) 
#define JVMPI_EVENT_CLASS_UNLOAD                  ((jint)43) 
#define JVMPI_EVENT_DATA_DUMP_REQUEST             ((jint)44) 
#define JVMPI_EVENT_DATA_RESET_REQUEST            ((jint)45) 

#define JVMPI_EVENT_JVM_INIT_DONE          ((jint)46) 
#define JVMPI_EVENT_JVM_SHUT_DOWN          ((jint)47) 

#define JVMPI_EVENT_ARENA_NEW              ((jint)48)
#define JVMPI_EVENT_ARENA_DELETE           ((jint)49)

#define JVMPI_EVENT_OBJECT_DUMP            ((jint)50)

#define JVMPI_EVENT_RAW_MONITOR_CONTENDED_ENTER   ((jint)51)
#define JVMPI_EVENT_RAW_MONITOR_CONTENDED_ENTERED ((jint)52)
#define JVMPI_EVENT_RAW_MONITOR_CONTENDED_EXIT    ((jint)53)
#define JVMPI_EVENT_MONITOR_CONTENDED_ENTER       ((jint)54)
#define JVMPI_EVENT_MONITOR_CONTENDED_ENTERED     ((jint)55)
#define JVMPI_EVENT_MONITOR_CONTENDED_EXIT        ((jint)56)
#define JVMPI_EVENT_MONITOR_WAIT                  ((jint)57)
#define JVMPI_EVENT_MONITOR_WAITED                ((jint)58)
#define JVMPI_EVENT_MONITOR_DUMP                  ((jint)59)

#define JVMPI_EVENT_GC_START                      ((jint)60)
#define JVMPI_EVENT_GC_FINISH                     ((jint)61)

#define JVMPI_MAX_EVENT_TYPE_VAL                  ((jint)61)

/* old definitions, to be removed */
#define JVMPI_EVENT_LOAD_COMPILED_METHOD          ((jint)7) 
#define JVMPI_EVENT_UNLOAD_COMPILED_METHOD        ((jint)8) 
#define JVMPI_EVENT_NEW_ARENA                     ((jint)48)
#define JVMPI_EVENT_DELETE_ARENA                  ((jint)49)
#define JVMPI_EVENT_DUMP_DATA_REQUEST             ((jint)44) 
#define JVMPI_EVENT_RESET_DATA_REQUEST            ((jint)45) 
#define JVMPI_EVENT_OBJ_ALLOC                     ((jint)4) 
#define JVMPI_EVENT_OBJ_FREE                      ((jint)5) 
#define JVMPI_EVENT_OBJ_MOVE                      ((jint)6) 

#define JVMPI_REQUESTED_EVENT                     ((jint)0x10000000)


 
/* 
 * enabling/disabling event notification.
 */
/* results */
#define JVMPI_SUCCESS                    ((jint)0)
#define JVMPI_NOT_AVAILABLE              ((jint)1)
#define JVMPI_FAIL                       ((jint)-1)

/*
 * Thread status
 */
enum {
    JVMPI_THREAD_RUNNABLE = 1,
    JVMPI_THREAD_MONITOR_WAIT,
    JVMPI_THREAD_CONDVAR_WAIT
};

#define JVMPI_THREAD_SUSPENDED        0x8000
#define JVMPI_THREAD_INTERRUPTED      0x4000

/*
 * Thread priority
 */
#define JVMPI_MINIMUM_PRIORITY	    1
#define JVMPI_MAXIMUM_PRIORITY	    10
#define JVMPI_NORMAL_PRIORITY	    5

/*
 * Object type constants.
 */
#define JVMPI_NORMAL_OBJECT	         ((jint)0)
#define JVMPI_CLASS		         ((jint)2)
#define JVMPI_BOOLEAN	                 ((jint)4)
#define JVMPI_CHAR                       ((jint)5)
#define JVMPI_FLOAT                      ((jint)6)
#define JVMPI_DOUBLE                     ((jint)7)
#define JVMPI_BYTE                       ((jint)8)
#define JVMPI_SHORT                      ((jint)9)
#define JVMPI_INT                        ((jint)10)
#define JVMPI_LONG                       ((jint)11)    

/*
 * Monitor dump constants.
 */

#define JVMPI_MONITOR_JAVA          0x01
#define JVMPI_MONITOR_RAW           0x02

/*
 * Heap dump constants.
 */
#define JVMPI_GC_ROOT_UNKNOWN       0xff
#define JVMPI_GC_ROOT_JNI_GLOBAL    0x01
#define JVMPI_GC_ROOT_JNI_LOCAL     0x02
#define JVMPI_GC_ROOT_JAVA_FRAME    0x03
#define JVMPI_GC_ROOT_NATIVE_STACK  0x04
#define JVMPI_GC_ROOT_STICKY_CLASS  0x05
#define JVMPI_GC_ROOT_THREAD_BLOCK  0x06
#define JVMPI_GC_ROOT_MONITOR_USED  0x07
#define JVMPI_GC_ROOT_THREAD_OBJ    0x08

#define JVMPI_GC_CLASS_DUMP         0x20
#define JVMPI_GC_INSTANCE_DUMP      0x21 
#define JVMPI_GC_OBJ_ARRAY_DUMP     0x22
#define JVMPI_GC_PRIM_ARRAY_DUMP    0x23

/*
 * Dump levels
 */
#define JVMPI_DUMP_LEVEL_0    ((jint)0)
#define JVMPI_DUMP_LEVEL_1    ((jint)1)
#define JVMPI_DUMP_LEVEL_2    ((jint)2)

/* Types used in dumps -
 *
 * u1: 1 byte
 * u2: 2 bytes
 * u4: 4 bytes
 * u8: 8 bytes
 *
 * ty: u1 where:
 *     JVMPI_CLASS:   object
 *     JVMPI_BOOLEAN: boolean
 *     JVMPI_CHAR:    char
 *     JVMPI_FLOAT:   float
 *     JVMPI_DOUBLE:  double
 *     JVMPI_BYTE:    byte
 *     JVMPI_SHORT:   short
 *     JVMPI_INT:     int
 *     JVMPI_LONG:    long
 *
 * vl: values, exact type depends on the type of the value:
 *     JVMPI_BOOLEAN & JVMPI_BYTE:   u1
 *     JVMPI_SHORT & JVMPI_CHAR:     u2
 *     JVMPI_INT & JVMPI_FLOAT:      u4
 *     JVMPI_LONG & JVMPI_DOUBLE:    u8
 *     JVMPI_CLASS:                  jobjectID
 */

/* Format of the monitor dump buffer:
 *
 *               u1                          monitor type
 *
 *               JVMPI_MONITOR_JAVA          Java monitor
 *
 *                          jobjectID        object
 *                          JNIEnv *         owner thread
 *                          u4               entry count
 *                          u4               # of threads waiting to enter
 *                          [JNIEnv *]*      threads waiting to enter
 *                          u4               # of threads waiting to be notified
 *                          [JNIEnv *]*      threads waiting to be notified
 *
 *               JVMPI_MONITOR_RAW           raw monitor
 *
 *                          char *           name
 *                          JVMPI_RawMonitor raw monitor
 *                          JNIEnv *         owner thread
 *                          u4               entry count
 *                          u4               # of threads waiting to enter
 *                          [JNIEnv *]*      threads waiting to enter
 *                          u4               # of threads waiting to be notified
 *                          [JNIEnv *]*      threads waiting to be notified
 */

/* Format of the heap dump buffer depends on the dump level 
 * specified in the JVMPI_HeapDumpArg passed to RequestEvent as arg. 
 * The default is JVMPI_DUMP_LEVEL_2.
 *
 * JVMPI_DUMP_LEVEL_0:
 * 
 *               u1                          object type (JVMPI_CLASS ...)
 *               jobjectID                   object
 *
 * JVMPI_DUMP_LEVEL_1 and JVMPI_DUMP_LEVEL_2 use the following format:  
 * In the case of JVMPI_DUMP_LEVEL_1 the values of primitive fields in object 
 * instance dumps , the values of primitive statics in class dumps and the 
 * values of primitive arrays are excluded.  JVMPI_DUMP_LEVEL_2 includes the
 * primitive values.
 *
 *               u1                          record type
 *
 *               JVMPI_GC_ROOT_UNKNOWN       unknown root
 *
 *                          jobjectID        object
 *
 *               JVMPI_GC_ROOT_JNI_GLOBAL    JNI global ref root
 *
 *                          jobjectID        object
 *                          jobject          JNI global reference
 *
 *               JVMPI_GC_ROOT_JNI_LOCAL     JNI local ref
 *
 *                          jobjectID        object
 *                          JNIEnv *         thread
 *                          u4               frame # in stack trace (-1 for empty)
 *
 *               JVMPI_GC_ROOT_JAVA_FRAME    Java stack frame
 *
 *                          jobjectID        object
 *                          JNIEnv *         thread
 *                          u4               frame # in stack trace (-1 for empty)
 *
 *               JVMPI_GC_ROOT_NATIVE_STACK  Native stack
 *
 *                          jobjectID        object
 *                          JNIEnv *         thread
 *
 *               JVMPI_GC_ROOT_STICKY_CLASS  System class
 *
 *                          jobjectID        class object
 *
 *               JVMPI_GC_ROOT_THREAD_BLOCK  Reference from thread block
 *
 *                          jobjectID        thread object
 *                          JNIEnv *         thread
 *
 *               JVMPI_GC_ROOT_MONITOR_USED  Busy monitor
 *
 *                          jobjectID        object
 *
 *               JVMPI_GC_CLASS_DUMP         dump of a class object
 *
 *                          jobjectID        class
 *                          jobjectID        super
 *                          jobjectID        class loader
 *                          jobjectID        signers
 *                          jobjectID        protection domain
 *                          jobjectID        class name
 *                          void *           reserved
 *
 *                          u4               instance size (in bytes)
 *
 *                          [jobjectID]*     interfaces
 *
 *                          u2               size of constant pool
 *                          [u2,             constant pool index,
 *                           ty,             type, 
 *                           vl]*            value
 *
 *                          [vl]*            static field values
 *
 *               JVMPI_GC_INSTANCE_DUMP      dump of a normal object
 *
 *                          jobjectID        object
 *                          jobjectID        class
 *                          u4               number of bytes that follow
 *                          [vl]*            instance field values (class, followed
 *                                           by super, super's super ...)
 *
 *               JVMPI_GC_OBJ_ARRAY_DUMP     dump of an object array
 *
 *                          jobjectID        array object
 *                          u4               number of elements
 *                          jobjectID        element class
 *                          [jobjectID]*     elements
 *
 *               JVMPI_GC_PRIM_ARRAY_DUMP    dump of a primitive array
 *
 *                          jobjectID        array object
 *                          u4               number of elements
 *                          ty               element type
 *                          [vl]*            elements
 *
 */

/* Format of the dump received in JVMPI_EVENT_OBJECT_DUMP:
 * All the records have JVMPI_DUMP_LEVEL_2 information.
 *
 *               u1                          record type
 *
 *                     followed by a:
 *
 *                          JVMPI_GC_CLASS_DUMP,
 *                          JVMPI_GC_INSTANCE_DUMP,
 *                          JVMPI_GC_OBJ_ARRAY_DUMP, or
 *                          JVMPI_GC_PRIM_ARRAY_DUMP record.
 */

#endif /* !_JAVASOFT_JVMPI_H_ */
