/*
 JNFThread.h
 Java Native Foundation
 Copyright (c) 2008-2010, Apple Inc.
 All rights reserved.

 Functions to help obtain a JNIEnv pointer in places where one cannot be passed
 though (callbacks, catagory functions, etc). Use sparingly.
 */

#import <os/availability.h>
#import <JavaNativeFoundation/JNFJNI.h>

__BEGIN_DECLS

// Options only apply if thread was not already attached to the JVM.
enum {
    JNFThreadDetachImmediately = (1 << 1),
    JNFThreadDetachOnThreadDeath = (1 << 2),
    JNFThreadSetSystemClassLoaderOnAttach = (1 << 3),
    JNFThreadAttachAsDaemon = (1 << 4)
};

typedef jlong JNFThreadContext;


/*
 * Attaches the current thread to the Java VM if needed, and obtains a JNI environment
 * to interact with the VM. Use a provided JNIEnv pointer for your current thread 
 * whenever possible, since this method is particularly expensive to the Java VM if 
 * used repeatedly.
 *
 * Provide a pointer to a JNFThreadContext to pass to JNFReleaseEnv().
 */
JNF_EXPORT extern JNIEnv *JNFObtainEnv(JNFThreadContext *context) API_DEPRECATED("This functionality is no longer supported and may stop working in a future version of macOS.", macos(10.10, 11.0));

/*
 * Release the JNIEnv for this thread, and detaches the current thread from the VM if
 * it was not already attached.
 */
JNF_EXPORT extern void JNFReleaseEnv(JNIEnv *env, JNFThreadContext *context) API_DEPRECATED("This functionality is no longer supported and may stop working in a future version of macOS.", macos(10.10, 11.0));


#if __BLOCKS__

/*
 * Performs the same attach/detach as JNFObtainEnv() and JNFReleaseEnv(), but executes a
 * block that accepts the obtained JNIEnv.
 */
typedef void (^JNIEnvBlock)(JNIEnv *);
JNF_EXPORT extern void JNFPerformEnvBlock(JNFThreadContext context, JNIEnvBlock block) API_DEPRECATED("This functionality is no longer supported and may stop working in a future version of macOS.", macos(10.10, 11.0));

#endif

__END_DECLS
