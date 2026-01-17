/*
 * Copyright 2002 Sun Microsystems, Inc. All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */

/*
 *   Java Virtual Machine Debug Interface
 *
 *   Defines debugging functionality that a VM should provide.  
 *
 *   Should not overlap functionality in jni.h
 */

#ifndef _JAVASOFT_JVMDI_H_
#define _JAVASOFT_JVMDI_H_

#include "jni.h"

#define JVMDI_VERSION_1 0x20010000

#ifdef __cplusplus
extern "C" {
#endif

typedef jobject jthread;

typedef jobject jthreadGroup;

struct _jframeID;
typedef struct _jframeID *jframeID;

  /* specifies program location "pc" - often byte code index */
typedef jlong jlocation;

  /*
   *  Errors
   */

typedef jint jvmdiError;

  /* no error */
#define JVMDI_ERROR_NONE                 ((jvmdiError)0)

  /*
   * Errors on thread operations
   */

  /* invalid thread */
#define JVMDI_ERROR_INVALID_THREAD       ((jvmdiError)10)
  /* invalid thread group */
#define JVMDI_ERROR_INVALID_THREAD_GROUP ((jvmdiError)11)
  /* invalid thread priority */
#define JVMDI_ERROR_INVALID_PRIORITY     ((jvmdiError)12)
  /* thread not suspended */
#define JVMDI_ERROR_THREAD_NOT_SUSPENDED ((jvmdiError)13)
  /* thread already suspended */
#define JVMDI_ERROR_THREAD_SUSPENDED     ((jvmdiError)14)

  /* 
   * Errors on object and class operations
   */

  /* invalid object (implementation not required to gracefully catch) */
#define JVMDI_ERROR_INVALID_OBJECT       ((jvmdiError)20)
  /* invalid class (implementation not required to gracefully catch) */
#define JVMDI_ERROR_INVALID_CLASS        ((jvmdiError)21)
  /* class not prepared */
#define JVMDI_ERROR_CLASS_NOT_PREPARED   ((jvmdiError)22)
  /* invalid methodID (implementation not required to gracefully catch) */
#define JVMDI_ERROR_INVALID_METHODID     ((jvmdiError)23)
  /* invalid location */
#define JVMDI_ERROR_INVALID_LOCATION     ((jvmdiError)24)
  /* invalid fieldID (implementation not required to gracefully catch) */
#define JVMDI_ERROR_INVALID_FIELDID      ((jvmdiError)25)

  /*
   * Errors on frame operations
   */

  /* invalid frameID (implementation not required to gracefully catch) */
#define JVMDI_ERROR_INVALID_FRAMEID      ((jvmdiError)30)
  /* there are no more frames on the stack */
#define JVMDI_ERROR_NO_MORE_FRAMES       ((jvmdiError)31)
  /* operation cannot be performed on this frame */
#define JVMDI_ERROR_OPAQUE_FRAME         ((jvmdiError)32)
  /* operation can only be performed on current frame */
#define JVMDI_ERROR_NOT_CURRENT_FRAME    ((jvmdiError)33)
  /* type mismatch (implementation not required to gracefully catch) */
#define JVMDI_ERROR_TYPE_MISMATCH        ((jvmdiError)34)
  /* invalid slot */
#define JVMDI_ERROR_INVALID_SLOT         ((jvmdiError)35)

  /*
   * Errors on set/clear/find operations
   */

  /* item already present */
#define JVMDI_ERROR_DUPLICATE            ((jvmdiError)40)
  /* item not found */
#define JVMDI_ERROR_NOT_FOUND            ((jvmdiError)41)

  /*
   * Errors on monitor operations
   */

  /* invalid monitor */
#define JVMDI_ERROR_INVALID_MONITOR      ((jvmdiError)50)
  /* wait, notify, notify all tried without entering monitor  */
#define JVMDI_ERROR_NOT_MONITOR_OWNER    ((jvmdiError)51)
  /* waiting thread interrupted */
#define JVMDI_ERROR_INTERRUPT            ((jvmdiError)52)
  
  /*
   * Class redefinition / operand stack errors
   */

  /* The equivalent of ClassFormatError */
#define JVMDI_ERROR_INVALID_CLASS_FORMAT          ((jvmdiError)60)
  /* The equivalent of ClassCircularityError */
#define JVMDI_ERROR_CIRCULAR_CLASS_DEFINITION     ((jvmdiError)61)
  /* The class bytes fail verification */
#define JVMDI_ERROR_FAILS_VERIFICATION            ((jvmdiError)62)
  /* Cannot add new methods to an existing class */
#define JVMDI_ERROR_ADD_METHOD_NOT_IMPLEMENTED    ((jvmdiError)63)
  /* Cannot change fields of an existing class */
#define JVMDI_ERROR_SCHEMA_CHANGE_NOT_IMPLEMENTED ((jvmdiError)64)
  /* bci/operand stack/local var combination is not verifiably type safe */
#define JVMDI_ERROR_INVALID_TYPESTATE             ((jvmdiError)65)

  /*
   * Miscellaneous errors
   */

  /* Not yet implemented */
#define JVMDI_ERROR_NOT_IMPLEMENTED      ((jvmdiError)99)
  /* null pointer */
#define JVMDI_ERROR_NULL_POINTER         ((jvmdiError)100)
  /* information is absent */
#define JVMDI_ERROR_ABSENT_INFORMATION   ((jvmdiError)101)
  /* invalid event type  */
#define JVMDI_ERROR_INVALID_EVENT_TYPE   ((jvmdiError)102)
  /* invalid argument  */
#define JVMDI_ERROR_ILLEGAL_ARGUMENT     ((jvmdiError)103)

  /*
   * Universal errors. These errors may be returned by
   * any JVMDI function, not just the ones for which they are listed
   * below.
   */

  /* no more memory available for allocation */
#define JVMDI_ERROR_OUT_OF_MEMORY        ((jvmdiError)110)
  /* debugging has not been enabled in this VM */
#define JVMDI_ERROR_ACCESS_DENIED        ((jvmdiError)111)
  /* VM is dead (implementation not required to gracefully catch) */
#define JVMDI_ERROR_VM_DEAD              ((jvmdiError)112)
  /* internal error  */
#define JVMDI_ERROR_INTERNAL             ((jvmdiError)113)
  /* Thread calling JVMDI function not attached to VM */
#define JVMDI_ERROR_UNATTACHED_THREAD    ((jvmdiError)115)


  /*
   *  Threads
   */

  /* Thread status is unknown */
#define JVMDI_THREAD_STATUS_UNKNOWN      ((jint)-1)
  /* Thread is waiting to die */
#define JVMDI_THREAD_STATUS_ZOMBIE       ((jint)0)
  /* Thread is runnable */
#define JVMDI_THREAD_STATUS_RUNNING      ((jint)1)
  /* Thread is sleeping - Thread.sleep() or JVM_Sleep() was called */
#define JVMDI_THREAD_STATUS_SLEEPING     ((jint)2)
  /* Thread is waiting on a java monitor */
#define JVMDI_THREAD_STATUS_MONITOR      ((jint)3)
  /* Thread is waiting - Thread.wait() or JVM_MonitorWait() was called */
#define JVMDI_THREAD_STATUS_WAIT         ((jint)4)

  /* Thread is suspended - Thread.suspend(), JVM_Suspend() or
   * JVMDI_Suspend was called */
#define JVMDI_SUSPEND_STATUS_SUSPENDED   ((jint)0x1)
  /* Thread is at a breakpoint */
#define JVMDI_SUSPEND_STATUS_BREAK       ((jint)0x2)


  /* Thread priority constants */
#define JVMDI_THREAD_MIN_PRIORITY   ((jint)1)
#define JVMDI_THREAD_NORM_PRIORITY  ((jint)5)
#define JVMDI_THREAD_MAX_PRIORITY   ((jint)10)

typedef struct {
    char *name;
    jint  priority;
    jboolean is_daemon;
    jthreadGroup thread_group;
    jobject context_class_loader;
} JVMDI_thread_info;

typedef struct {
    jthreadGroup parent;
    char *name;
    jint  max_priority;
    jboolean is_daemon;
} JVMDI_thread_group_info;

#define JVMDI_DISABLE ((jint) 0)
#define JVMDI_ENABLE  ((jint) 1)

/*
 * Initial function for debug threads created through JVMDI
 */
typedef void (*JVMDI_StartFunction)(void *);

/*
 * Type for debug monitors created through JVMDI
 */
typedef void *JVMDI_RawMonitor;

#define JVMDI_MONITOR_WAIT_FOREVER ((jlong)(0))

/*
 * Monitor information
 */
typedef struct {
    jthread owner;
    jint entry_count;
    jint waiter_count;
    jthread *waiters;
} JVMDI_monitor_info;

typedef struct {
    jint owned_monitor_count;
    jobject *owned_monitors;
} JVMDI_owned_monitor_info;

  /*
   *  Events
   */

    /* kind = JVMDI_EVENT_SINGLE_STEP */
    typedef struct { 
        jthread thread;
        jclass clazz;
        jmethodID method;
        jlocation location;
    } JVMDI_single_step_event_data;
			
    /* kind = JVMDI_EVENT_BREAKPOINT */
    typedef struct { 
        jthread thread;
        jclass clazz;
        jmethodID method;
        jlocation location;
    } JVMDI_breakpoint_event_data;
    
    /* kind = JVMDI_EVENT_FIELD_ACCESS */
    typedef struct { 
        jthread thread;
        jclass clazz;
        jmethodID method;
        jlocation location;
        jclass field_clazz;
        jobject object;
        jfieldID field;
    } JVMDI_field_access_event_data;
    
    /* kind = JVMDI_EVENT_FIELD_MODIFICATION */
    typedef struct { 
        jthread thread;
        jclass clazz;
        jmethodID method;
        jlocation location;
        jclass field_clazz;
        jobject object;
        jfieldID field;
        char signature_type;
        jvalue new_value;
    } JVMDI_field_modification_event_data;
    
    /* kind = JVMDI_EVENT_FRAME_POP */
    /* kind = JVMDI_EVENT_METHOD_ENTRY */
    /* kind = JVMDI_EVENT_METHOD_EXIT */
    typedef struct { 
        jthread thread;
        jclass clazz;
        jmethodID method;
        jframeID frame;
    } JVMDI_frame_event_data;
    
    /* kind = JVMDI_EVENT_EXCEPTION */
    typedef struct { 
        jthread thread;
        jclass clazz;
        jmethodID method;
        jlocation location;
        jobject exception;
        jclass catch_clazz;
        jmethodID catch_method;
        jlocation catch_location;
    } JVMDI_exception_event_data;
    
    /* kind = JVMDI_EVENT_EXCEPTION_CATCH */
    typedef struct { 
        jthread thread;
        jclass clazz;
        jmethodID method;
        jlocation location;
        jobject exception;
    } JVMDI_exception_catch_event_data;
    
    /* kind = JVMDI_EVENT_USER_DEFINED */
    typedef struct { 
        jobject object;
        jint key;
    } JVMDI_user_event_data;
    
    /* kind = JVMDI_EVENT_THREAD_END or */
    /* JVMDI_EVENT_THREAD_START */
    typedef struct { 
        jthread thread;
    } JVMDI_thread_change_event_data;
    
    /* kind = JVMDI_EVENT_CLASS_LOAD, */
    /* JVMDI_EVENT_CLASS_UNLOAD, or */
    /* JVMDI_EVENT_CLASS_PREPARE */
    typedef struct { 
        jthread thread;
        jclass clazz;
    } JVMDI_class_event_data;
    
/* This stucture passes information about the event.
 * location is the index of the last instruction executed. 
 */
typedef struct {
    jint kind;		/* the discriminant */

    union {
	/* kind = JVMDI_EVENT_SINGLE_STEP */
        JVMDI_single_step_event_data single_step;
			
        /* kind = JVMDI_EVENT_BREAKPOINT */
        JVMDI_breakpoint_event_data breakpoint;

        /* kind = JVMDI_EVENT_FRAME_POP */
        /* kind = JVMDI_EVENT_METHOD_ENTRY */
        /* kind = JVMDI_EVENT_METHOD_EXIT */
        JVMDI_frame_event_data frame;

        /* kind = JVMDI_EVENT_FIELD_ACCESS */
        JVMDI_field_access_event_data field_access;

        /* kind = JVMDI_EVENT_FIELD_MODIFICATION */
        JVMDI_field_modification_event_data field_modification;

        /* kind = JVMDI_EVENT_EXCEPTION */
        JVMDI_exception_event_data exception;

        /* kind = JVMDI_EVENT_EXCEPTION_CATCH */
        JVMDI_exception_catch_event_data exception_catch;

        /* kind = JVMDI_EVENT_USER_DEFINED */
        JVMDI_user_event_data user;
			
        /* kind = JVMDI_EVENT_THREAD_END or */
        /* JVMDI_EVENT_THREAD_START */
        JVMDI_thread_change_event_data thread_change;
			
        /* kind = JVMDI_EVENT_CLASS_LOAD, */
        /* JVMDI_EVENT_CLASS_UNLOAD, or */
        /* JVMDI_EVENT_CLASS_PREPARE */
        JVMDI_class_event_data class_event;
			
        /* kind = JVMDI_EVENT_VM_DEATH, JVMDI_EVENT_VM_INIT */
        /* no additional fields */		
    } u;
} JVMDI_Event;

	/*** event kinds ***/
#define JVMDI_EVENT_SINGLE_STEP   ((jint)1)
#define JVMDI_EVENT_BREAKPOINT    ((jint)2)
#define JVMDI_EVENT_FRAME_POP     ((jint)3)
#define JVMDI_EVENT_EXCEPTION     ((jint)4)
#define JVMDI_EVENT_USER_DEFINED  ((jint)5)
#define JVMDI_EVENT_THREAD_START  ((jint)6)
#define JVMDI_EVENT_THREAD_END    ((jint)7)
#define JVMDI_EVENT_CLASS_PREPARE ((jint)8)
#define JVMDI_EVENT_CLASS_UNLOAD  ((jint)9)
#define JVMDI_EVENT_CLASS_LOAD    ((jint)10)
#define JVMDI_EVENT_FIELD_ACCESS       ((jint)20)
#define JVMDI_EVENT_FIELD_MODIFICATION ((jint)21)
#define JVMDI_EVENT_EXCEPTION_CATCH    ((jint)30)
#define JVMDI_EVENT_METHOD_ENTRY       ((jint)40)
#define JVMDI_EVENT_METHOD_EXIT        ((jint)41)
#define JVMDI_EVENT_VM_INIT            ((jint)90)
#define JVMDI_EVENT_VM_DEATH           ((jint)99)

#define JVMDI_MAX_EVENT_TYPE_VAL       ((jint)99)



/* event handler hook */
typedef void (*JVMDI_EventHook)(JNIEnv *env, JVMDI_Event *event);

typedef jvmdiError (*JVMDI_AllocHook) (jlong size, jbyte** memPtr);
typedef jvmdiError (*JVMDI_DeallocHook) (jbyte* buffer);

/*
 * Class states used in JVMDI_GetClassStatus
 */
#define JVMDI_CLASS_STATUS_VERIFIED          ((jint)0x01)
#define JVMDI_CLASS_STATUS_PREPARED          ((jint)0x02)
#define JVMDI_CLASS_STATUS_INITIALIZED       ((jint)0x04)
 /* Error prevents initialization */
#define JVMDI_CLASS_STATUS_ERROR             ((jint)0x08) 

/* structure for returning line number information 
 */
typedef struct {
    jlocation start_location;
    jint line_number;
} JVMDI_line_number_entry;


/* structure for returning local variable information 
 */
typedef struct {
    jlocation start_location;   /* variable valid start_location */
    jint length;                /* upto start_location+length */ 
    char *name;                 /* name in UTF8 */
    char *signature;            /* type signature in UTF8 */
    jint slot;                  /* variable slot, see JVMDI_GetLocal*()  */
} JVMDI_local_variable_entry;

/* structure for returning exception handler information 
 */
typedef struct {
    jlocation start_location;
    jlocation end_location;
    jlocation handler_location;
    jclass exception;           /* if null, all exceptions */
} JVMDI_exception_handler_entry;

#define JVMDI_OPERAND_TYPE_REFERENCE      ((jint)1)
#define JVMDI_OPERAND_TYPE_INT            ((jint)2)
#define JVMDI_OPERAND_TYPE_FLOAT          ((jint)3)
#define JVMDI_OPERAND_TYPE_LONG0          ((jint)4) /* least sig. 32 bits */
#define JVMDI_OPERAND_TYPE_LONG1          ((jint)5) /* most sig. 32 bits */
#define JVMDI_OPERAND_TYPE_DOUBLE0        ((jint)6) /* least sig. 32 bits */
#define JVMDI_OPERAND_TYPE_DOUBLE1        ((jint)7) /* most sig. 32 bits */
#define JVMDI_OPERAND_TYPE_RETURN_ADDRESS ((jint)8)

typedef struct {
    jint word;                 /* 32 bit operand stack quantities */
    jint type;                 /* type encoding of the operand word */
                               /* one of JVMDI_OPERAND_TYPE_* */
} JVMDI_operand_stack_element;

typedef struct { 
    jint instance_field_count; /* number of instance fields referencing obj */
    struct JVMDI_instance_field {
        jobject instance;      /* instance referencing obj */
        jfieldID field;        /* field holding reference */
    } *instance_fields;        /* instanceField_count of them */
     
    jint static_field_count;   /* number of static fields referencing obj */
    struct JVMDI_static_field {
        jclass clazz;          /* class referencing obj */
        jfieldID static_field; /* field holding reference */
    } *static_fields;          /* static_field_count of them */
    
    jint array_element_count;  /* number of array elements referencing obj */
    struct JVMDI_array_element {
        jobjectArray array;    /* array referencing obj */
        jint index;            /* index holding reference */
    } *array_elements;         /* array_element_count of them */
    
    jint frame_slot_count;     /* number of frame slots referencing obj */
    struct JVMDI_frame_slot {
        jthread thread;        /* thread of the frame */
        jframeID frame;        /* frame referencing obj */
        jint slot;             /* slot holding reference */
    } *frame_slots;            /* frame_slot_count of them */
} JVMDI_object_reference_info;

/* structure for defining a class
*/
typedef struct {
    jclass clazz;              /* Class object for this class */
    jint class_byte_count;     /* number of bytes defining class (below) */
    jbyte *class_bytes;        /* bytes defining class (in JVM spec */
                               /* Class File Format) */
} JVMDI_class_definition;


typedef struct {
    unsigned int can_watch_field_modification      : 1;
    unsigned int can_watch_field_access            : 1;
    unsigned int can_get_bytecodes                 : 1;
    unsigned int can_get_synthetic_attribute       : 1;
    unsigned int can_get_owned_monitor_info        : 1;
    unsigned int can_get_current_contended_monitor : 1;
    unsigned int can_get_monitor_info              : 1;
    unsigned int can_get_heap_info                 : 1;
    unsigned int can_get_operand_stack             : 1;
    unsigned int can_set_operand_stack             : 1;
    unsigned int can_pop_frame                     : 1;
    unsigned int can_get_class_definition          : 1;
    unsigned int can_redefine_classes              : 1; 
    unsigned int can_add_method                    : 1;
    unsigned int can_change_schema                 : 1;
} JVMDI_capabilities;

typedef struct JVMDI_Interface_1_ {
    jvmdiError (JNICALL *SetEventHook)
      (JVMDI_EventHook hook);
    jvmdiError (JNICALL *SetEventNotificationMode)
      (jint mode, jint eventType, jthread thread, ...);

    jvmdiError (JNICALL *GetThreadStatus)
      (jthread thread,
       jint *threadStatusPtr, jint *suspendStatusPtr);
    jvmdiError (JNICALL *GetAllThreads)
      (jint *threadsCountPtr, jthread **threadsPtr);
    jvmdiError (JNICALL *SuspendThread)
      (jthread thread); 
    jvmdiError (JNICALL *ResumeThread)
      (jthread thread);
    jvmdiError (JNICALL *StopThread)
      (jthread thread, jobject exception);
    jvmdiError (JNICALL *InterruptThread)
      (jthread thread);
    jvmdiError (JNICALL *GetThreadInfo)
      (jthread thread, JVMDI_thread_info *infoPtr);
    jvmdiError (JNICALL *GetOwnedMonitorInfo)
      (jthread thread, JVMDI_owned_monitor_info *infoPtr);
    jvmdiError (JNICALL *GetCurrentContendedMonitor)
      (jthread thread, jobject *monitor);
    jvmdiError (JNICALL *RunDebugThread)
      (jthread thread, JVMDI_StartFunction proc, void *arg,
       int priority);

    jvmdiError (JNICALL *GetTopThreadGroups)
      (jint *groupCountPtr, jthreadGroup **groupsPtr);
    jvmdiError (JNICALL *GetThreadGroupInfo)
      (jthreadGroup group, JVMDI_thread_group_info *infoPtr);
    jvmdiError (JNICALL *GetThreadGroupChildren)
      (jthreadGroup group, 
       jint *threadCountPtr, jthread **threadsPtr,
       jint *groupCountPtr, jthreadGroup **groupsPtr);

    jvmdiError (JNICALL *GetFrameCount)
      (jthread thread, jint *countPtr);
    jvmdiError (JNICALL *GetCurrentFrame)
      (jthread thread, jframeID *framePtr);
    jvmdiError (JNICALL *GetCallerFrame)
      (jframeID called, jframeID *framePtr);
    jvmdiError (JNICALL *GetFrameLocation)
      (jframeID frame, jclass *classPtr, jmethodID *methodPtr,
       jlocation *locationPtr);
    jvmdiError (JNICALL *NotifyFramePop)
      (jframeID frame); 
    jvmdiError (JNICALL *GetLocalObject)
      (jframeID frame, jint slot, jobject *valuePtr);
    jvmdiError (JNICALL *GetLocalInt)
      (jframeID frame, jint slot, jint *valuePtr);
    jvmdiError (JNICALL *GetLocalLong)
      (jframeID frame, jint slot, jlong *valuePtr);
    jvmdiError (JNICALL *GetLocalFloat)
      (jframeID frame, jint slot, jfloat *valuePtr);
    jvmdiError (JNICALL *GetLocalDouble)
      (jframeID frame, jint slot, jdouble *valuePtr);
    jvmdiError (JNICALL *SetLocalObject)
      (jframeID frame, jint slot, jobject value);
    jvmdiError (JNICALL *SetLocalInt)
      (jframeID frame, jint slot, jint value);
    jvmdiError (JNICALL *SetLocalLong)
      (jframeID frame, jint slot, jlong value);
    jvmdiError (JNICALL *SetLocalFloat)
      (jframeID frame, jint slot, jfloat value);
    jvmdiError (JNICALL *SetLocalDouble)
      (jframeID frame, jint slot, jdouble value);

    jvmdiError (JNICALL *CreateRawMonitor)
      (char *name, JVMDI_RawMonitor *monitorPtr);
    jvmdiError (JNICALL *DestroyRawMonitor)
      (JVMDI_RawMonitor monitor);
    jvmdiError (JNICALL *RawMonitorEnter)
      (JVMDI_RawMonitor monitor);
    jvmdiError (JNICALL *RawMonitorExit)
      (JVMDI_RawMonitor monitor);
    jvmdiError (JNICALL *RawMonitorWait)
      (JVMDI_RawMonitor monitor, jlong millis);
    jvmdiError (JNICALL *RawMonitorNotify)
      (JVMDI_RawMonitor monitor);
    jvmdiError (JNICALL *RawMonitorNotifyAll)
      (JVMDI_RawMonitor monitor);

    jvmdiError (JNICALL *SetBreakpoint)
      (jclass clazz, jmethodID method, jlocation location);
    jvmdiError (JNICALL *ClearBreakpoint)
      (jclass clazz, jmethodID method, jlocation location);
    jvmdiError (JNICALL *ClearAllBreakpoints)
      ();

    jvmdiError (JNICALL *SetFieldAccessWatch)
      (jclass clazz, jfieldID field);
    jvmdiError (JNICALL *ClearFieldAccessWatch)
      (jclass clazz, jfieldID field);
    jvmdiError (JNICALL *SetFieldModificationWatch)
      (jclass clazz, jfieldID field);
    jvmdiError (JNICALL *ClearFieldModificationWatch)
      (jclass clazz, jfieldID field);

    jvmdiError (JNICALL *SetAllocationHooks)
      (JVMDI_AllocHook ahook, JVMDI_DeallocHook dhook);
    jvmdiError (JNICALL *Allocate)
      (jlong size, jbyte** memPtr);
    jvmdiError (JNICALL *Deallocate)
      (jbyte* mem);

    jvmdiError (JNICALL *GetClassSignature)
      (jclass clazz, char **sigPtr);
    jvmdiError (JNICALL *GetClassStatus)
      (jclass clazz, jint *statusPtr);
    jvmdiError (JNICALL *GetSourceFileName)
      (jclass clazz, char **sourceNamePtr);
    jvmdiError (JNICALL *GetClassModifiers)
      (jclass clazz, jint *modifiersPtr);
    jvmdiError (JNICALL *GetClassMethods)
      (jclass clazz, jint *methodCountPtr, jmethodID **methodsPtr);
    jvmdiError (JNICALL *GetClassFields)
       (jclass clazz, jint *fieldCountPtr, jfieldID **fieldsPtr);
    jvmdiError (JNICALL *GetImplementedInterfaces)
      (jclass clazz, jint *interfaceCountPtr, jclass **interfacesPtr);
    jvmdiError (JNICALL *IsInterface)
      (jclass clazz, jboolean *isInterfacePtr);
    jvmdiError (JNICALL *IsArrayClass)
      (jclass clazz, jboolean *isArrayClassPtr);
    jvmdiError (JNICALL *GetClassLoader)
      (jclass clazz, jobject *classloaderPtr);

    jvmdiError (JNICALL *GetObjectHashCode)
      (jobject object, jint *hashCodePtr);
    jvmdiError (JNICALL *GetMonitorInfo)
      (jobject object, JVMDI_monitor_info *infoPtr);

    jvmdiError (JNICALL *GetFieldName)
      (jclass clazz, jfieldID field, char **namePtr, char **signaturePtr);
    jvmdiError (JNICALL *GetFieldDeclaringClass)
      (jclass clazz, jfieldID field, jclass *declaringClassPtr);
    jvmdiError (JNICALL *GetFieldModifiers)
      (jclass clazz, jfieldID field, jint *modifiersPtr);
    jvmdiError (JNICALL *IsFieldSynthetic)
      (jclass clazz, jfieldID field, jboolean *isSyntheticPtr);

    jvmdiError (JNICALL *GetMethodName)
      (jclass clazz, jmethodID method, 
       char **namePtr, char **signaturePtr);
    jvmdiError (JNICALL *GetMethodDeclaringClass)
      (jclass clazz, jmethodID method, jclass *declaringClassPtr);
    jvmdiError (JNICALL *GetMethodModifiers)
      (jclass clazz, jmethodID method, jint *modifiersPtr);
    jvmdiError (JNICALL *GetMaxStack)
      (jclass clazz, jmethodID method, jint *maxPtr);
    jvmdiError (JNICALL *GetMaxLocals)
      (jclass clazz, jmethodID method, jint *maxPtr);
    jvmdiError (JNICALL *GetArgumentsSize)
      (jclass clazz, jmethodID method, jint *sizePtr);
    jvmdiError (JNICALL *GetLineNumberTable)
      (jclass clazz, jmethodID method,
       jint *entryCountPtr, JVMDI_line_number_entry **tablePtr);
    jvmdiError (JNICALL *GetMethodLocation)
      (jclass clazz, jmethodID method,
       jlocation *startLocationPtr, jlocation *endLocationPtr);
    jvmdiError (JNICALL *GetLocalVariableTable)
      (jclass clazz, jmethodID method,
       jint *entryCountPtr, JVMDI_local_variable_entry **tablePtr);
    jvmdiError (JNICALL *GetExceptionHandlerTable)
      (jclass clazz, jmethodID method,
       jint *entryCountPtr, JVMDI_exception_handler_entry **tablePtr);
    jvmdiError (JNICALL *GetThrownExceptions)
      (jclass clazz, jmethodID method,
       jint *exceptionCountPtr, jclass **exceptionsPtr);
    jvmdiError (JNICALL *GetBytecodes)
      (jclass clazz, jmethodID method,
       jint *bytecodeCountPtr, jbyte **bytecodesPtr);
    jvmdiError (JNICALL *IsMethodNative)
      (jclass clazz, jmethodID method, jboolean *isNativePtr);
    jvmdiError (JNICALL *IsMethodSynthetic)
      (jclass clazz, jmethodID method, jboolean *isSyntheticPtr);

    jvmdiError (JNICALL *GetLoadedClasses)
      (jint *classCountPtr, jclass **classesPtr);
    jvmdiError (JNICALL *GetClassLoaderClasses)
      (jobject initiatingLoader, jint *classesCountPtr, 
       jclass **classesPtr);

    jvmdiError (JNICALL *PopFrame)
      (jthread thread);
    jvmdiError (JNICALL *SetFrameLocation)
      (jframeID frame, jlocation location);
    jvmdiError (JNICALL *GetOperandStack)
      (jframeID frame, jint *operandStackSizePtr, 
       JVMDI_operand_stack_element **operandStackPtr);
    jvmdiError (JNICALL *SetOperandStack)
      (jframeID frame, jint operandStackSize, 
       JVMDI_operand_stack_element *operandStack);
    jvmdiError (JNICALL *AllInstances)
      (jclass clazz, jint *instanceCountPtr, jobject **instancesPtr);
    jvmdiError (JNICALL *References)
      (jobject obj, JVMDI_object_reference_info *refs);
    jvmdiError (JNICALL *GetClassDefinition)
      (jclass clazz, JVMDI_class_definition *classDefPtr);
    jvmdiError (JNICALL *RedefineClasses)
      (jint classCount, JVMDI_class_definition *classDefs);

    jvmdiError (JNICALL *GetVersionNumber)
      (jint *versionPtr);
    jvmdiError (JNICALL *GetCapabilities)
      (JVMDI_capabilities *capabilitiesPtr);
} JVMDI_Interface_1;
  
#ifndef NO_JVMDI_MACROS

#define JVMDI_ERROR_DUPLICATE_BREAKPOINT JVMDI_ERROR_DUPLICATE
#define JVMDI_ERROR_NO_SUCH_BREAKPOINT   JVMDI_ERROR_NOT_FOUND
#define JVMDI_ERROR_DUPLICATE_FRAME_POP  JVMDI_ERROR_DUPLICATE


static JVMDI_Interface_1 *jvmdi_interface = NULL;
static JavaVM *j_vm;

#ifdef __cplusplus
#define SetJVMDIfromJNIEnv(a_env) ( (jvmdi_interface == NULL)?  \
              ((a_env)->GetJavaVM(&j_vm),  \
               (j_vm)->GetEnv((void **)&jvmdi_interface,  \
                               JVMDI_VERSION_1)):0)
#else
#define SetJVMDIfromJNIEnv(a_env) ( (jvmdi_interface == NULL)?  \
              ((*a_env)->GetJavaVM(a_env, &j_vm), \
               (*j_vm)->GetEnv(j_vm, (void **)&jvmdi_interface, \
                               JVMDI_VERSION_1)):0)
#endif

#define JVMDI_SetEventHook(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetEventHook(a1) )
#define JVMDI_GetThreadStatus(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetThreadStatus(a1, a2, a3) )
#define JVMDI_GetAllThreads(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetAllThreads(a1, a2) )
#define JVMDI_SuspendThread(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SuspendThread(a1) )
#define JVMDI_ResumeThread(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->ResumeThread(a1) )
#define JVMDI_StopThread(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->StopThread(a1, a2) )
#define JVMDI_InterruptThread(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->InterruptThread(a1) )
#define JVMDI_SetSingleStep(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetEventNotificationMode( \
                                       (a2) ? JVMDI_ENABLE : JVMDI_DISABLE, \
                                        JVMDI_EVENT_SINGLE_STEP, a1) )
#define JVMDI_GetThreadInfo(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetThreadInfo(a1, a2) )
#define JVMDI_RunDebugThread(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->RunDebugThread(a1, a2, a3, a4) )
#define JVMDI_GetTopThreadGroups(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetTopThreadGroups(a1, a2) )
#define JVMDI_GetThreadGroupInfo(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetThreadGroupInfo(a1, a2) )
#define JVMDI_GetThreadGroupChildren(a_env, a1, a2, a3, a4, a5) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetThreadGroupChildren(a1, a2, a3, a4, a5) )
#define JVMDI_GetCurrentFrame(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetCurrentFrame(a1, a2) )
#define JVMDI_GetCallerFrame(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetCallerFrame(a1, a2) )
#define JVMDI_GetFrameLocation(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetFrameLocation(a1, a2, a3, a4) )
#define JVMDI_NotifyFramePop(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->NotifyFramePop(a1) )
#define JVMDI_GetLocalObject(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLocalObject(a1, a2, a3) )
#define JVMDI_GetLocalInt(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLocalInt(a1, a2, a3) )
#define JVMDI_GetLocalLong(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLocalLong(a1, a2, a3) )
#define JVMDI_GetLocalFloat(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLocalFloat(a1, a2, a3) )
#define JVMDI_GetLocalDouble(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLocalDouble(a1, a2, a3) )
#define JVMDI_SetLocalObject(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetLocalObject(a1, a2, a3) )
#define JVMDI_SetLocalInt(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetLocalInt(a1, a2, a3) )
#define JVMDI_SetLocalLong(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetLocalLong(a1, a2, a3) )
#define JVMDI_SetLocalFloat(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetLocalFloat(a1, a2, a3) )
#define JVMDI_SetLocalDouble(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetLocalDouble(a1, a2, a3) )
#define JVMDI_CreateRawMonitor(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->CreateRawMonitor(a1, a2) )
#define JVMDI_DestroyRawMonitor(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->DestroyRawMonitor(a1) )
#define JVMDI_RawMonitorEnter(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->RawMonitorEnter(a1) )
#define JVMDI_RawMonitorExit(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->RawMonitorExit(a1) )
#define JVMDI_RawMonitorWait(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->RawMonitorWait(a1, a2) )
#define JVMDI_RawMonitorNotify(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->RawMonitorNotify(a1) )
#define JVMDI_RawMonitorNotifyAll(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->RawMonitorNotifyAll(a1) )
#define JVMDI_SetBreakpoint(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetBreakpoint(a1, a2, a3) )
#define JVMDI_ClearBreakpoint(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->ClearBreakpoint(a1, a2, a3) )
#define JVMDI_ClearAllBreakpoints(a_env) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->ClearAllBreakpoints() )
#define JVMDI_SetAllocationHooks(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->SetAllocationHooks(a1, a2) )
#define JVMDI_Allocate(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->Allocate(a1, a2) )
#define JVMDI_Deallocate(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->Deallocate(a1) )
#define JVMDI_GetClassSignature(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetClassSignature(a1, a2) )
#define JVMDI_GetClassStatus(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetClassStatus(a1, a2) )
#define JVMDI_GetSourceFileName(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetSourceFileName(a1, a2) )
#define JVMDI_GetClassModifiers(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetClassModifiers(a1, a2) )
#define JVMDI_GetClassMethods(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetClassMethods(a1, a2, a3) )
#define JVMDI_GetClassFields(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetClassFields(a1, a2, a3) )
#define JVMDI_GetImplementedInterfaces(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetImplementedInterfaces(a1, a2, a3) )
#define JVMDI_IsInterface(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->IsInterface(a1, a2) )
#define JVMDI_IsArrayClass(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->IsArrayClass(a1, a2) )
#define JVMDI_ClassLoader(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetClassLoader(a1, a2) )
#define JVMDI_GetFieldName(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetFieldName(a1, a2, a3, a4) )
#define JVMDI_GetFieldDeclaringClass(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetFieldDeclaringClass(a1, a2, a3) )
#define JVMDI_GetFieldModifiers(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetFieldModifiers(a1, a2, a3) )
#define JVMDI_GetMethodName(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetMethodName(a1, a2, a3, a4) )
#define JVMDI_GetMethodDeclaringClass(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetMethodDeclaringClass(a1, a2, a3) )
#define JVMDI_GetMethodModifiers(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetMethodModifiers(a1, a2, a3) )
#define JVMDI_GetMaxStack(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetMaxStack(a1, a2, a3) )
#define JVMDI_GetMaxLocals(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetMaxLocals(a1, a2, a3) )
#define JVMDI_GetArgumentsSize(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetArgumentsSize(a1, a2, a3) )
#define JVMDI_GetLineNumberTable(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLineNumberTable(a1, a2, a3, a4) )
#define JVMDI_GetMethodLocation(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetMethodLocation(a1, a2, a3, a4) )
#define JVMDI_GetLocalVariableTable(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLocalVariableTable(a1, a2, a3, a4) )
#define JVMDI_GetExceptionHandlerTable(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetExceptionHandlerTable(a1, a2, a3, a4) )
#define JVMDI_GetThrownExceptions(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetThrownExceptions(a1, a2, a3, a4) )
#define JVMDI_GetBytecodes(a_env, a1, a2, a3, a4) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetBytecodes(a1, a2, a3, a4) )
#define JVMDI_IsMethodNative(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->IsMethodNative(a1, a2, a3) )
#define JVMDI_GetLoadedClasses(a_env, a1, a2) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetLoadedClasses(a1, a2) )
#define JVMDI_GetClassLoaderClasses(a_env, a1, a2, a3) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetClassLoaderClasses(a1, a2, a3) )
#define JVMDI_GetVersionNumber(a_env, a1) ( \
              SetJVMDIfromJNIEnv(a_env), \
              jvmdi_interface->GetVersionNumber(a1) )

#endif /* !NO_JVMDI_MACROS */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !_JAVASOFT_JVMDI_H_ */


