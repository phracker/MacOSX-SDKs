#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "@(#)jmm.h	1.18 04/03/21 23:24:58 JVM"
#endif
/*
 *
 * Copyright 2004 Sun Microsystems, Inc. All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */

#ifndef _JAVA_JMM_H_
#define _JAVA_JMM_H_

/*
 * This is a private interface used by JDK for JVM monitoring
 * and management.
 *
 * Bump the version number when either of the following happens:
 *
 * 1. There is a change in functions in JmmInterface.
 *
 * 2. There is a change in the contract between VM and Java classes.
 */

#include "jni.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  JMM_VERSION_1   = 0x20010000,
  JMM_VERSION_1_0 = 0x20010000
};

typedef struct {
  unsigned int isLowMemoryDetectionSupported : 1;
  unsigned int isCompilationTimeMonitoringSupported : 1;
  unsigned int isThreadContentionMonitoringSupported : 1;
  unsigned int isCurrentThreadCpuTimeSupported : 1;
  unsigned int isOtherThreadCpuTimeSupported : 1;
  unsigned int isBootClassPathSupported : 1;
  unsigned int : 26;
} jmmOptionalSupport;

typedef enum {
  JMM_CLASS_LOADED_COUNT             = 1,    /* Total number of loaded classes */
  JMM_CLASS_UNLOADED_COUNT           = 2,    /* Total number of unloaded classes */
  JMM_THREAD_TOTAL_COUNT             = 3,    /* Total number of threads that have been started */
  JMM_THREAD_LIVE_COUNT              = 4,    /* Current number of live threads */
  JMM_THREAD_PEAK_COUNT              = 5,    /* Peak number of live threads */
  JMM_THREAD_DAEMON_COUNT            = 6,    /* Current number of daemon threads */
  JMM_JVM_INIT_DONE_TIME_MS          = 7,    /* Time when the JVM finished initialization */
  JMM_COMPILE_TOTAL_TIME_MS          = 8,    /* Total accumulated time spent in compilation */
  JMM_GC_TIME_MS                     = 9,    /* Total accumulated time spent in collection */
  JMM_GC_COUNT                       = 10,   /* Total number of collections */

  JMM_INTERNAL_ATTRIBUTE_INDEX       = 100,
  JMM_CLASS_LOADED_BYTES             = 101,  /* Number of bytes loaded instance classes */
  JMM_CLASS_UNLOADED_BYTES           = 102,  /* Number of bytes unloaded instance classes */
  JMM_TOTAL_CLASSLOAD_TIME_MS        = 103,  /* Accumulated VM class loader time (TraceClassLoadingTime) */
  JMM_VM_GLOBAL_COUNT                = 104,  /* Number of VM internal flags */
  JMM_SAFEPOINT_COUNT                = 105,  /* Total number of safepoints */
  JMM_TOTAL_SAFEPOINTSYNC_TIME_MS    = 106,  /* Accumulated time spent getting to safepoints */
  JMM_TOTAL_STOPPED_TIME_MS          = 107,  /* Accumulated time spent at safepoints */
  JMM_TOTAL_APP_TIME_MS              = 108,  /* Accumulated time spent in Java application */
  JMM_VM_THREAD_COUNT                = 109,  /* Current number of VM internal threads */
  JMM_CLASS_INIT_TOTAL_COUNT         = 110,  /* Number of classes for which initializers were run */
  JMM_CLASS_INIT_TOTAL_TIME_MS       = 111,  /* Accumulated time spent in class initializers */
  JMM_METHOD_DATA_SIZE_BYTES         = 112,  /* Size of method data in memory */
  JMM_CLASS_VERIFY_TOTAL_TIME_MS     = 113,  /* Accumulated time spent in class verifier */
  JMM_SHARED_CLASS_LOADED_COUNT      = 114,  /* Number of shared classes loaded */
  JMM_SHARED_CLASS_UNLOADED_COUNT    = 115,  /* Number of shared classes unloaded */
  JMM_SHARED_CLASS_LOADED_BYTES      = 116,  /* Number of bytes loaded shared classes */
  JMM_SHARED_CLASS_UNLOADED_BYTES    = 117,  /* Number of bytes unloaded shared classes */

  JMM_OS_ATTRIBUTE_INDEX             = 200,
  JMM_OS_PROCESS_ID                  = 201,  /* Process id of the JVM */
  JMM_OS_MEM_TOTAL_PHYSICAL_BYTES    = 202,  /* Physical memory size */

  JMM_GC_EXT_ATTRIBUTE_INFO_SIZE     = 401   /* the size of the GC specific attributes for a given GC memory manager */
} jmmLongAttribute;

typedef enum {
  JMM_VERBOSE_GC                     = 21,
  JMM_VERBOSE_CLASS                  = 22,
  JMM_THREAD_CONTENTION_MONITORING   = 23,
  JMM_THREAD_CPU_TIME                = 24
} jmmBoolAttribute;


typedef enum {
  JMM_THREAD_STATE_UNKNOWN        = -1,
  JMM_THREAD_STATE_ZOMBIE         = 0,
  JMM_THREAD_STATE_RUNNING        = 1,
  JMM_THREAD_STATE_SLEEP          = 2,
  JMM_THREAD_STATE_MONITOR        = 3,
  JMM_THREAD_STATE_WAIT           = 4,
  JMM_THREAD_STATE_TIMED_WAIT     = 5,
  JMM_THREAD_STATE_SUSPENDED      = 6,
  JMM_THREAD_STATE_TERMINATED     = 7,
  JMM_THREAD_STATE_RUNNING_NATIVE = 8,
  JMM_THREAD_STATE_NEW            = 9
} jmmThreadState;

enum {
  JMM_THREAD_STATE_FLAG_SUSPENDED = (1 << 8),
  JMM_THREAD_STATE_FLAG_NATIVE    = (16 << 8)
};

typedef enum {
  JMM_STAT_PEAK_THREAD_COUNT         = 801,
  JMM_STAT_THREAD_CONTENTION_COUNT   = 802,
  JMM_STAT_THREAD_CONTENTION_TIME    = 803,
  JMM_STAT_THREAD_CONTENTION_STAT    = 804,
  JMM_STAT_PEAK_POOL_USAGE           = 805,
  JMM_STAT_GC_STAT                   = 806
} jmmStatisticType;

typedef enum {
  JMM_USAGE_THRESHOLD_HIGH	      = 901,
  JMM_USAGE_THRESHOLD_LOW	      = 902,
  JMM_COLLECTION_USAGE_THRESHOLD_HIGH = 903,
  JMM_COLLECTION_USAGE_THRESHOLD_LOW  = 904
} jmmThresholdType;

/* Should match what is allowed in globals.hpp */
typedef enum {
  JMM_VMGLOBAL_TYPE_UNKNOWN  = 0,
  JMM_VMGLOBAL_TYPE_JBOOLEAN = 1,
  JMM_VMGLOBAL_TYPE_JSTRING  = 2,
  JMM_VMGLOBAL_TYPE_JLONG    = 3
} jmmVMGlobalType;

typedef enum {
  JMM_VMGLOBAL_SOURCE_DEFAULT = 1,   /* Default value */
  JMM_VMGLOBAL_SOURCE_WASSET  = 2    /* Non default   */
} jmmVMGlobalSource;

typedef struct {
  jstring           name;
  jvalue            value;
  jmmVMGlobalType   type;       /* Data type */
  jmmVMGlobalSource source;     /* Default or non-default value */
  jboolean          writeable;  /* can be set */
  void *reserved1;
  void *reserved2;
} jmmVMGlobal;

typedef struct {
  const char*  name;
  char         type;
  const char*  description;
} jmmExtAttributeInfo;

// Caller has to set the following fields before calling GetLastGCStat
//   o usage_before_gc               - array of MemoryUsage objects
//   o usage_after_gc                - array of MemoryUsage objects
//   o gc_ext_attribute_values_size - size of gc_ext_atttribute_values array
//   o gc_ext_attribtue_values      - array of jvalues
//
typedef struct {
  jlong        gc_index;                       // Index of the collections
  jlong        start_time;                     // Start time of the GC
  jlong        end_time;                       // End time of the GC
  jobjectArray usage_before_gc;                // Memory usage array before GC
  jobjectArray usage_after_gc;                 // Memory usage array after GC
  jint         gc_ext_attribute_values_size;   // set by the caller of GetGCStat
  jvalue*      gc_ext_attribute_values;        // Array of jvalue for GC extension attributes
  jint         num_gc_ext_attributes;          // number of GC extension attribute values s are filled
                                               // -1 indicates gc_ext_attribute_values is not big enough
} jmmGCStat;

typedef struct jmmInterface_1_ {
  void*        reserved1;
  void*        reserved2;

  jint         (JNICALL *GetVersion)             (JNIEnv *env);

  jint         (JNICALL *GetOptionalSupport)     (JNIEnv *env, 
                                                  jmmOptionalSupport* support_ptr);

  jobject      (JNICALL *GetInputArguments)      (JNIEnv *env);

  jint         (JNICALL *GetThreadInfo)          (JNIEnv *env, 
                                                  jlongArray ids, 
                                                  jint maxDepth,
                                                  jobjectArray infoArray); 
  void*        reserved3;

  jobjectArray (JNICALL *GetMemoryPools)         (JNIEnv* env, jobject mgr);

  jobjectArray (JNICALL *GetMemoryManagers)      (JNIEnv* env, jobject pool);

  jobject      (JNICALL *GetMemoryPoolUsage)     (JNIEnv* env, jobject pool);
  jobject      (JNICALL *GetPeakMemoryPoolUsage) (JNIEnv* env, jobject pool);

  void*        reserved4;

  jobject      (JNICALL *GetMemoryUsage)         (JNIEnv* env, jboolean heap);

  jlong        (JNICALL *GetLongAttribute)       (JNIEnv *env, jobject obj, jmmLongAttribute att);
  jboolean     (JNICALL *GetBoolAttribute)       (JNIEnv *env, jmmBoolAttribute att);
  jboolean     (JNICALL *SetBoolAttribute)       (JNIEnv *env, jmmBoolAttribute att, jboolean flag);

  jint         (JNICALL *GetLongAttributes)      (JNIEnv *env, 
                                                  jobject obj, 
                                                  jmmLongAttribute* atts, 
                                                  jint count, 
                                                  jlong* result);

  jobjectArray (JNICALL *FindCircularBlockedThreads) (JNIEnv *env);
  jlong        (JNICALL *GetThreadCpuTime)       (JNIEnv *env, jlong thread_id);

  jobjectArray (JNICALL *GetVMGlobalNames)       (JNIEnv *env);
  jint         (JNICALL *GetVMGlobals)           (JNIEnv *env, 
                                                  jobjectArray names,
                                                  jmmVMGlobal *globals,
                                                  jint count);

  jint         (JNICALL *GetInternalThreadTimes) (JNIEnv *env,
						  jobjectArray names,
						  jlongArray times);

  jboolean     (JNICALL *ResetStatistic)         (JNIEnv *env,
                                                  jvalue obj,
                                                  jmmStatisticType type);

  void         (JNICALL *SetPoolSensor)          (JNIEnv *env, 
                                                  jobject pool, 
						  jmmThresholdType type,
                                                  jobject sensor);

  jlong        (JNICALL *SetPoolThreshold)       (JNIEnv *env, 
                                                  jobject pool, 
						  jmmThresholdType type,
                                                  jlong threshold);
  jobject      (JNICALL *GetPoolCollectionUsage) (JNIEnv* env, jobject pool);

  jint         (JNICALL *GetGCExtAttributeInfo)  (JNIEnv *env, 
                                                  jobject mgr, 
                                                  jmmExtAttributeInfo *ext_info,
                                                  jint count);
  void         (JNICALL *GetLastGCStat)          (JNIEnv *env, 
                                                  jobject mgr,
                                                  jmmGCStat *gc_stat);
  jlong        (JNICALL *GetThreadCpuTimeWithKind) (JNIEnv *env, 
                                                    jlong thread_id, 
                                                    jboolean user_sys_cpu_time);
} JmmInterface;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !_JAVA_JMM_H_ */

