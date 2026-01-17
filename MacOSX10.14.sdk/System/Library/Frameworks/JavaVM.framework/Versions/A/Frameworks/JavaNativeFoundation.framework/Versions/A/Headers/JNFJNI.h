/*
 JNFJNI.h
 Java Native Foundation
 Copyright (c) 2008, Apple Inc.
 All rights reserved.
 
 The basic building blocks of writing Java JNI code that interacts with Objective-C.
 
 All JNI functions should call JNF_COCOA_ENTER()/JNF_COCOA_EXIT() to properly
 catch thrown NSExceptions and periodically flush the autorelease pool for the
 current thread. JNF_COCOA_DURING()/JNF_COCOA_HANDLE() should only be used when
 AppKit is known to not be initialized yet.
 
 JNF_CLASS_CACHE()/JNF_MEMBER_CACHE()/JNF_STATIC_MEMBER_CACHE()/JNF_CTOR_CACHE()
 all cache references to Java classes, methods, and variables for use by the
 GET/SET/CALL functions. These functions check for Java exceptions, immediately
 re-throwing them as JNFExceptions, and are simpler than their pure JNI equivalents.
 */

#import <JavaVM/jni.h>

#if !defined(JNF_EXPORT)
	#ifdef __cplusplus
		#define JNF_EXPORT extern "C"
	#else
		#define JNF_EXPORT extern
	#endif
#endif

#import <JavaNativeFoundation/JNFException.h>
#import <JavaNativeFoundation/JNFAutoreleasePool.h>


// from jlong.h
// All pointers in and out of JNI functions should be expressed as jlongs
// to accomodate for both 32-bit and 64-bit pointer sizes
#ifndef jlong_to_ptr
#define jlong_to_ptr(a) ((void *)(uintptr_t)(a))
#endif

#ifndef ptr_to_jlong
#define ptr_to_jlong(a) ((jlong)(uintptr_t)(a))
#endif

// JNF_COCOA_DURING - Outermost exception scope for a JNI native method
//
// Use this macro only if you don't want any autorelease pool set or
// other JNFThreadContext setup (ie, if the AppKit isn't running
// yet).  Usually, you want to use JNF_COCOA_ENTER & JNF_COCOA_EXIT
#define JNF_COCOA_DURING(env)									\
@try {


// JNF_COCOA_HANDLE - Close of JNF_COCOA_DURING
//
// Use this macro to match an JNF_COCOA_DURING
// This macro ensures that no NSException is thrown into
// the VM.  It turns NSExceptions into Java exceptions.
#define JNF_COCOA_HANDLE(env)									\
} @catch(NSException *localException) {							\
	[JNFException throwToJava:env exception:localException];	\
}																\


// JNF_COCOA_ENTER - Place at the beginning of every JNI method
//
// Sets up an exception handler and an autorelease pool if one is
// not already setup.
//
// Note: if the native method executes before AppKit is
// initialized, use JNF_COCOA_DURING.
#define JNF_COCOA_ENTER(env)									\
{																\
    JNFAutoreleasePoolToken* _token = JNFNativeMethodEnter();	\
	JNF_COCOA_DURING(env)


// JNF_COCOA_EXIT - Place at the end of every JNI method
//
// Catches NSExceptions and re-throws them as Java exceptions.
// Use this macro to match JNF_COCOA_ENTER.
#define JNF_COCOA_EXIT(env)										\
	JNF_COCOA_HANDLE(env)										\
	@finally {													\
		if (_token) JNFNativeMethodExit(_token);				\
	}															\
}

// JNF_CHECK_AND_RETHROW_EXCEPTION - rethrows exceptions from Java
//
// Takes an exception thrown from Java, and transforms it into an
// NSException. The NSException should bubble up to the upper-most
// JNF_COCOA_ENTER/JNF_COCOA_EXIT pair, and then be re-thrown as
// a Java exception when returning from JNI. This check should be
// done after raw JNI operations which could cause a Java exception
// to be be thrown. The JNF{Get/Set/Call}  macros below do this
// check automatically.
#define JNF_CHECK_AND_RETHROW_EXCEPTION(env)							\
	{																	\
		jthrowable _exception = (*env)->ExceptionOccurred(env);			\
		if (_exception) [JNFException raise:env throwable:_exception];	\
	}


// Use JNF_CLASS_CACHE, JNF_MEMBER_CACHE, JNF_STATIC_MEMBER_CACHE
// and JNF_CTOR_CACHE as convenient ways to create
// JNFClassInfo and JNFMemberInfo records that can
// be passed to the utility functions that follow.

// JNF_CLASS_CACHE - Create a JNFClassInfo struct
//
// Use this macro to define a JNFClassInfo struct.
// For example:
// JNF_CLASS_CACHE(jc_java_awt_Font, "java/awt/Font");
// defines the symbol jc_java_awt_Font to point to the
// appropriately initialized JNFClassInfo struct.
// The "jc_" prefix is short for "java class."
#define JNF_CLASS_CACHE(cache_symbol, name) \
JNFClassInfo cache_symbol = {name, NULL}

// JNF_MEMBER_CACHE - Create a JNFMemberInfo struct
//
// This macro creates and initializes a JNFMemberInfo
// struct, and defines a pointer to it.  Example:
// JNF_MEMBER_CACHE(jm_Font_isBold, jc_java_awt_Font, "isBold", "Z");
// This defines the symbol jm_Font_isBold to point to a
// JNFMemberInfo struct that represents the isBold method
// of the class java.awt.Font.  Use this macro for both
// fields and methods.
#define JNF_MEMBER_CACHE(cache_symbol, class_cache_symbol, name, sig) \
JNFMemberInfo _ ## cache_symbol = {name, sig, NO, &class_cache_symbol, {NULL}}, *cache_symbol=&_ ## cache_symbol

// JNF_STATIC_MEMBER_CACHE - Create a JNFMemberInfo struct for static members
//
// Same as JNF_MEMBER_CACHE, but used for static fields and mehods.
#define JNF_STATIC_MEMBER_CACHE(cache_symbol, class_cache_symbol, name, sig) \
JNFMemberInfo _ ## cache_symbol = {name, sig, YES, &class_cache_symbol, {NULL}}, *cache_symbol=&_ ## cache_symbol

// JNF_CTOR_CACHE - Create a JNFMemberInfo struct for a constructor
//
// Same as JNF_MEMBER_CACHE, but for constructors
#define JNF_CTOR_CACHE(cache_symbol, class_cache_symbol, sig) \
JNFMemberInfo _ ## cache_symbol = {"<init>", sig, NO, &class_cache_symbol, {NULL}}, *cache_symbol=&_ ## cache_symbol


// JNFClassInfo - struct for caching a java class reference
//
// Create one of these by using the JNF_CLASS_CACHE macro (below).
// The class ref is resolved lazily.
typedef struct _JNFClassInfo {
	const char *name;	// fully/qualified/ClassName
	jclass cls;			// The JNI global class reference.
} JNFClassInfo;

// JNFMemberInfo - struct for caching a field or method ID
//
// Create these by using the JNF_MEMBER_CACHE macro (below).
// The member ID is resolved lazily.
typedef struct _JNFMemberInfo {
    const char *name;			// The name of the member
    const char *sig;			// The signature of the member
    BOOL isStatic;				// Is this member declared static?
    JNFClassInfo *classInfo;	// points to the JNFClassInfo struct of 
	//   which this field/method is a member.
    union _j {
        jfieldID fieldID;		// If field, the JNI field ID
        jmethodID methodID;		// If method, the JNI method ID
    } j;
} JNFMemberInfo;


/*
 * JNI Utility Functions
 *
 * These functions make use of class and method ID caching, so they
 * are more efficient than simply calling their JNI equivalents directly.
 * They also detect Java exceptions and throw a corresponding
 * NSException when JNI returns with a Java exception.
 * Therefore, you should be prepared to handle exceptions
 * before they propagate either back to the VM or up
 * to the run loop.
 */

// JNFIsInstanceOf - returns whether obj is an instance of clazz
JNF_EXPORT BOOL JNFIsInstanceOf(JNIEnv *env, jobject obj, JNFClassInfo *clazz);

// Creating instances
JNF_EXPORT jobject JNFNewObject(JNIEnv *env, JNFMemberInfo *constructor, ...);

// Creating arrays
JNF_EXPORT jobjectArray		JNFNewObjectArray	(JNIEnv *env, JNFClassInfo *clazz, jsize length);
JNF_EXPORT jbooleanArray	JNFNewBooleanArray	(JNIEnv *env, jsize length);
JNF_EXPORT jbyteArray		JNFNewByteArray		(JNIEnv *env, jsize length);
JNF_EXPORT jcharArray		JNFNewCharArray		(JNIEnv *env, jsize length);
JNF_EXPORT jshortArray		JNFNewShortArray	(JNIEnv *env, jsize length);
JNF_EXPORT jintArray		JNFNewIntArray		(JNIEnv *env, jsize length);
JNF_EXPORT jlongArray		JNFNewLongArray		(JNIEnv *env, jsize length);
JNF_EXPORT jfloatArray		JNFNewFloatArray	(JNIEnv *env, jsize length);
JNF_EXPORT jdoubleArray		JNFNewDoubleArray	(JNIEnv *env, jsize length);

// Non-static getters
JNF_EXPORT jobject  JNFGetObjectField (JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jboolean JNFGetBooleanField(JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jbyte    JNFGetByteField   (JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jchar    JNFGetCharField   (JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jshort   JNFGetShortField  (JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jint     JNFGetIntField    (JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jlong    JNFGetLongField   (JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jfloat   JNFGetFloatField  (JNIEnv *env, jobject obj, JNFMemberInfo *field);
JNF_EXPORT jdouble  JNFGetDoubleField (JNIEnv *env, jobject obj, JNFMemberInfo *field);

// Static getters
JNF_EXPORT jobject  JNFGetStaticObjectField (JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jboolean JNFGetStaticBooleanField(JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jbyte    JNFGetStaticByteField   (JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jchar    JNFGetStaticCharField   (JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jshort   JNFGetStaticShortField  (JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jint     JNFGetStaticIntField    (JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jlong    JNFGetStaticLongField   (JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jfloat   JNFGetStaticFloatField  (JNIEnv *env, JNFMemberInfo *field);
JNF_EXPORT jdouble  JNFGetStaticDoubleField (JNIEnv *env, JNFMemberInfo *field);

// Non-static setters
JNF_EXPORT void JNFSetObjectField (JNIEnv *env, jobject obj, JNFMemberInfo *field, jobject val);
JNF_EXPORT void JNFSetBooleanField(JNIEnv *env, jobject obj, JNFMemberInfo *field, jboolean val);
JNF_EXPORT void JNFSetByteField   (JNIEnv *env, jobject obj, JNFMemberInfo *field, jbyte val);
JNF_EXPORT void JNFSetCharField   (JNIEnv *env, jobject obj, JNFMemberInfo *field, jchar val);
JNF_EXPORT void JNFSetShortField  (JNIEnv *env, jobject obj, JNFMemberInfo *field, jshort val);
JNF_EXPORT void JNFSetIntField    (JNIEnv *env, jobject obj, JNFMemberInfo *field, jint val);
JNF_EXPORT void JNFSetLongField   (JNIEnv *env, jobject obj, JNFMemberInfo *field, jlong val);
JNF_EXPORT void JNFSetFloatField  (JNIEnv *env, jobject obj, JNFMemberInfo *field, jfloat val);
JNF_EXPORT void JNFSetDoubleField (JNIEnv *env, jobject obj, JNFMemberInfo *field, jdouble val);

// Static setters
JNF_EXPORT void JNFSetStaticObjectField (JNIEnv *env, JNFMemberInfo *field, jobject val);
JNF_EXPORT void JNFSetStaticBooleanField(JNIEnv *env, JNFMemberInfo *field, jboolean val);
JNF_EXPORT void JNFSetStaticByteField   (JNIEnv *env, JNFMemberInfo *field, jbyte val);
JNF_EXPORT void JNFSetStaticCharField   (JNIEnv *env, JNFMemberInfo *field, jchar val);
JNF_EXPORT void JNFSetStaticShortField  (JNIEnv *env, JNFMemberInfo *field, jshort val);
JNF_EXPORT void JNFSetStaticIntField    (JNIEnv *env, JNFMemberInfo *field, jint val);
JNF_EXPORT void JNFSetStaticLongField   (JNIEnv *env, JNFMemberInfo *field, jlong val);
JNF_EXPORT void JNFSetStaticFloatField  (JNIEnv *env, JNFMemberInfo *field, jfloat val);
JNF_EXPORT void JNFSetStaticDoubleField (JNIEnv *env, JNFMemberInfo *field, jdouble val);

// Calling instance methods
JNF_EXPORT void     JNFCallVoidMethod   (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jobject  JNFCallObjectMethod (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jboolean JNFCallBooleanMethod(JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jbyte    JNFCallByteMethod   (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jchar    JNFCallCharMethod   (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jshort   JNFCallShortMethod  (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jint     JNFCallIntMethod    (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jlong    JNFCallLongMethod   (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jfloat   JNFCallFloatMethod  (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);
JNF_EXPORT jdouble  JNFCallDoubleMethod (JNIEnv *env, jobject obj, JNFMemberInfo *method, ...);

// Calling static methods
JNF_EXPORT void     JNFCallStaticVoidMethod   (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jobject  JNFCallStaticObjectMethod (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jboolean JNFCallStaticBooleanMethod(JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jbyte    JNFCallStaticByteMethod   (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jchar    JNFCallStaticCharMethod   (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jshort   JNFCallStaticShortMethod  (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jint     JNFCallStaticIntMethod    (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jlong    JNFCallStaticLongMethod   (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jfloat   JNFCallStaticFloatMethod  (JNIEnv *env, JNFMemberInfo *method, ...);
JNF_EXPORT jdouble  JNFCallStaticDoubleMethod (JNIEnv *env, JNFMemberInfo *method, ...);

// Global references
JNF_EXPORT jobject JNFNewGlobalRef(JNIEnv *env, jobject obj);
JNF_EXPORT void JNFDeleteGlobalRef(JNIEnv *env, jobject globalRef);
JNF_EXPORT jobject JNFNewWeakGlobalRef(JNIEnv *env, jobject obj);
JNF_EXPORT void JNFDeleteWeakGlobalRef(JNIEnv *env, jobject globalRef);
