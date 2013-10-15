/*
     File:       JavaEmbedding/JavaApplet.h
 
     Contains:   interface to embedding a Java Applet in a Carbon Control
 
     Version:    JavaEmbedding-34~361
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __JAVAAPPLET__
#define __JAVAAPPLET__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __JAVACONTROL__
#include <JavaEmbedding/JavaControl.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint on
#endif


/*
 *  AppletDescriptor
 *  
 *  Discussion:
 *    The structure for describing applet. This is used as the
 *    definition of the applet to create when you call CreateJavaApplet.
 */
struct AppletDescriptor {
  CFURLRef            docBase;
  CFURLRef            codeBase;

  /*
   * The attributes found in the <applet ...> tag formatted as a
   * CFDictionary of CFStrings. For attributes like height and width
   * they should be in screen coordinates. some Applets define them as
   * % (for example 90%) and should be converted to pixels before put
   * into the dictionary.
   */
  CFDictionaryRef     htmlAttrs;

  /*
   * The parameters to the applet formatted as a CFDictionary of
   * CFStrings. These are typically found in <param ...> tags inside of
   * the applet tag.
   */
  CFDictionaryRef     appletParams;
};
typedef struct AppletDescriptor         AppletDescriptor;

/*
 *  AppletArena
 *  
 *  Discussion:
 *    This is an opaque type that represents an AppletArena - an applet
 *    arena represents a single classloader, so all applets that share
 *    an arena share a common classloader.
 */
typedef struct OpaqueAppletArena*       AppletArena;
/*    
    kUniqueArena is the value to pass to CreateJavaApplet if you want the applet to be created
    in a unique arena. A unique arena is one which is guaranteed not to be shared with
    any other applet running in this Java VM. This is the appropriate default value to
    pass to CreateJavaApplet.
*/
#define kUniqueArena                    ((AppletArena)NULL)

/*
 *  JE_ShowDocumentCallback
 *  
 *  Discussion:
 *    Type of a callback function used for show document (link) message
 *    from an applet.
 *  
 *  Parameters:
 *    
 *    applet:
 *      The applet which sent this show document message.
 *    
 *    url:
 *      The url to load.
 *    
 *    windowName:
 *      A string definition of where to open the url. Null means open
 *      in place, other strings are defined in the HTML spec, like
 *      "_top" means the parent window of the applet if it happens to
 *      be in a frame, etc.
 *    
 *    userData:
 *      Data specified when this callback was registered using
 *      RegisterShowDocumentCallback.
 */
typedef CALLBACK_API_C( void , JE_ShowDocumentCallback )(jobject applet, CFURLRef url, CFStringRef windowName, void *userData);

/*
 *  JE_SetStatusCallback
 *  
 *  Discussion:
 *    Type of a callback function used for a status message from an
 *    applet.
 *  
 *  Parameters:
 *    
 *    applet:
 *      The applet which sent this status message.
 *    
 *    statusMessage:
 *      The message to be displayed.
 *    
 *    userData:
 *      Data specified when this callback was registered using
 *      RegisterStatusCallback.
 */
typedef CALLBACK_API_C( void , JE_SetStatusCallback )(jobject applet, CFStringRef statusMessage, void *userData);
/*
 *  GetEmbeddingVMParams()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The JavaEmbedding framework is deprecated. Use the Java
 *    Applet.plugin instead (in /Library/Internet Plug-Ins)
 *  
 *  Discussion:
 *    Gets a set of VM params that can be passed to JNI_CreateJavaVM.
 *    These params are optimized for Java embedding, and also contain
 *    all user-specified options.
 *  
 *  Parameters:
 *    
 *    ioJavaVMInitArgs:
 *      A Java VM initialization argument structure that you create.
 *      This function will clear any fields set in the structure and
 *      filled in with new data on completion.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in JavaEmbedding.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetEmbeddingVMParams(JavaVMInitArgs * ioJavaVMInitArgs)       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  CreateAppletArena()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The JavaEmbedding framework is deprecated. Use the Java
 *    Applet.plugin instead (in /Library/Internet Plug-Ins)
 *  
 *  Discussion:
 *    Create an applet arena. By default each applet you create will
 *    have its own "arena". By creating an applet arena, and passing
 *    that arena into two or more CreateJavaApplet calls, those applets
 *    will share a single classloader and thus be able to communicate
 *    with each other through static objects.
 *  
 *  Parameters:
 *    
 *    outNewArena:
 *      The newly created applet arena.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in JavaEmbedding.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateAppletArena(AppletArena * outNewArena)                  AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  CreateJavaApplet()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The JavaEmbedding framework is deprecated. Use the Java
 *    Applet.plugin instead (in /Library/Internet Plug-Ins)
 *  
 *  Discussion:
 *    Creates a java applet from a descriptor.
 *  
 *  Parameters:
 *    
 *    env:
 *      The JNI environment for the current thread.
 *    
 *    applet:
 *      A full descriptor of the applet being loaded. See
 *      AppletDescriptor.
 *    
 *    trusted:
 *      Whether this applet should be loaded as trusted.
 *    
 *    arena:
 *      The arena for this applet. If this is set to null then a new
 *      arena will be created. This is the typcial case for applets.
 *    
 *    outJavaFrame:
 *      Returns JNI global ref. Used for registering callbacks and
 *      creating controls.  Call env->DeleteGlobalRef() on it when done.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in JavaEmbedding.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateJavaApplet(
  JNIEnv *           env,
  AppletDescriptor   applet,
  Boolean            trusted,
  AppletArena        arena,              /* can be NULL */
  jobject *          outJavaFrame)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  AppletState
 *  
 *  Summary:
 *    Constants that are passed to SetJavaAppletState.
 */
enum AppletState {
  kAppletStart                  = 1,    /* Starts the applet processing 3.*/
  kAppletStop                   = 2,    /* Halts the applet, but it can be started again.*/
  kAppletDestroy                = 4     /* Tears down the applet.*/
};
typedef enum AppletState AppletState;


/*
 *  SetJavaAppletState()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The JavaEmbedding framework is deprecated. Use the Java
 *    Applet.plugin instead (in /Library/Internet Plug-Ins)
 *  
 *  Discussion:
 *    Sets the state of the current applet as defined by the applet
 *    spec. Applets can be started and stopped many times, but
 *    destroying them is final.
 *  
 *  Parameters:
 *    
 *    env:
 *      The JNI environment for the current VM and thread.
 *    
 *    inAppletFrame:
 *      The applet to register the status callback (from
 *      CreateJavaApplet).
 *    
 *    inNewState:
 *      Host defined data passed into showStatusFunction.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in JavaEmbedding.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetJavaAppletState(
  JNIEnv *      env,
  jobject       inAppletFrame,
  AppletState   inNewState)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  RegisterStatusCallback()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The JavaEmbedding framework is deprecated. Use the Java
 *    Applet.plugin instead (in /Library/Internet Plug-Ins)
 *  
 *  Discussion:
 *    Registers your function that will be called to update the
 *    applet's status area. Status typically is put in a web browser as
 *    a text area at the bottom of the page. 
 *    
 *    Note that this callback will be called from a preemptive thread,
 *    and if the host application is using cooperative threads they
 *    will need to push this into their own event system in order to
 *    handle this correctly.
 *  
 *  Parameters:
 *    
 *    env:
 *      The JNI environment for the current VM and thread.
 *    
 *    inJavaFrame:
 *      The applet to register the status callback (from
 *      CreateJavaApplet).
 *    
 *    showStatusFunction:
 *      The function that will be called when the applet calls
 *      showStatus(...).
 *    
 *    userData:
 *      Host defined data passed into showStatusFunction.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in JavaEmbedding.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterStatusCallback(
  JNIEnv *               env,
  jobject                inJavaFrame,
  JE_SetStatusCallback   showStatusFunction,
  void *                 userData)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  RegisterShowDocumentCallback()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The JavaEmbedding framework is deprecated. Use the Java
 *    Applet.plugin instead (in /Library/Internet Plug-Ins)
 *  
 *  Discussion:
 *    Registers your function that will be called when the applet
 *    behaves like a hyperlink. This will be called to move an
 *    embedding host application to a new URL. 
 *    
 *    Note that this callback will be called from a preemptive thread,
 *    and if the host application is using cooperative threads they
 *    will need to push this into their own event system in order to
 *    handle this correctly.
 *  
 *  Parameters:
 *    
 *    env:
 *      The JNI environment for the current VM and thread.
 *    
 *    inJavaFrame:
 *      The applet to register the show document callback (from
 *      CreateJavaApplet).
 *    
 *    showDocumentFunction:
 *      The function that will be called when the applet calls
 *      showDocument().
 *    
 *    userData:
 *      Host defined data passed into showDocumentFunction.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in JavaEmbedding.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterShowDocumentCallback(
  JNIEnv *                  env,
  jobject                   inJavaFrame,
  JE_ShowDocumentCallback   showDocumentFunction,
  void *                    userData)                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;




#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __JAVAAPPLET__ */

