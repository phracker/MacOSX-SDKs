/*
     File:       CarbonCore/Debugging.h
 
     Contains:   Macros to handle exceptions and assertions.
 
     Version:    Technology: Carbon
                 Release:    CarbonCore-317~6
 
     Copyright:  © 1989-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DEBUGGING__
#define __DEBUGGING__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif


/*
  ______________________________________________________________________________________
                                                                                        
    This file defines standard exception handling and assertion macros for              
    system-level programming in C.  Originally used in QuickDraw GX, and heavily        
    modified since, these macros are used extensively throughout Mac OS system          
    software.  Now *you* can look and feel like a system software engineer.             
                                                                                        
    To activate debugger breaks, #define DEBUG to 1 (one) before including this file.   
    Five further levels of debugging are available, selected by #defining one           
    of the following conditionals to 1 after DEBUG is defined to 1.                     
                                                                                        
        DEBUG_INTERNAL      the default; includes file and line number information      
                                                                                        
        DEBUG_EXTERNAL      used for code which must ship to developers outside         
                            your organization; no file or line number information is    
                            included in asserts                                         
                                                                                        
        DEBUG_BREAK_ONLY    where an assertion would normally be sent to the debugger,      
                            send an empty string instead.                               
                                                                                        
        PRODUCTION          used for shipping code; no debugger breaks are emitted      
                                                                                        
        PERFORMANCE         same as PRODUCTION                                          
                                                                                        
    #defining DEBUG to 0 is equivalent to #defining PRODUCTION 1 when DEBUG is 1.       
    (No code for debugger breaks is emitted in either case.)                            
                                                                                        
    Of the multitude of macros, the preferred ones are:                                 
                                                                                        
    debug_string(c-string)                                                              
        If debugging is on, c-string is printed in the debugger.                        
        In production builds, debug_string() does nothing.                              
                                                                                        
    check(expression)                                                                   
    check_noerr(error)                                                                  
        If (expression) evaluates to false, break into the debugger.                    
        In production builds, check() does nothing.                                     
        Code inside check() statements is not compiled into production builds.          
                                                                                        
    require(expression, label)                                                          
    require_noerr(expression, label)                                                    
        If (expression) evaluates to false, announce this fact via the                  
        debugger and then goto label.  In production builds, does not call              
        the debugger but still goes to label if expression is false.                    
                                                                                        
    require_action(expression, label, action)                                           
    require_noerr_action(expression, label, action)                                     
        Same as require, but executes (action) before jumping to label.                 
                                                                                        
    check_string(expression, c-string)                                                  
    require_string(expression, label, c-string)                                         
    require_noerr_string(expression, label, c-string)                                   
        If expression evaluates to false, print string and then proceed as in           
        a normal check/require statement                                                
                                                                                        
    verify(expression)                                                                  
    verify_noerr(error)                                                                 
        If debugging is on, verify is the same as check(expression).                    
        If debugging is off, verify still evaluates (expression)                        
        but ignores the result.  Code inside verify() statements                        
        is executed in both production and debug builds.                                
                                                                                        
    Common usage:                                                                       
                                                                                        
        // my pixmap is not purgeable, so locking it should never fail                  
        verify( LockPixels(myPixMap) );                                                 
        verify_noerr( DisposeThread(myThread, &threadResult, true) );                   
  ______________________________________________________________________________________
*/


/*
  ______________________________________________________________________________________
                                                                                        
   Before including this file, #define kComponentSignatureString to a C-string          
   containing the name of your client.                                                  
                                                                                        
   example: #define kComponentSignatureString "SurfWriter"                              
  ______________________________________________________________________________________
*/



#ifndef kComponentSignatureString
#define kComponentSignatureString "Third Party Client"
#endif



#define DEBUG_LEVEL_PRODUCTION 0
#define DEBUG_LEVEL_BREAK_ONLY    1
#define DEBUG_LEVEL_EXTERNAL  3
#define DEBUG_LEVEL_INTERNAL  4
#define DEBUGFULL             DEBUG_LEVEL_INTERNAL
#define DEBUG_NO_OPTIONS       0



#if DEBUG
 #if     PRODUCTION
     #define DEBUGLEVEL DEBUG_LEVEL_PRODUCTION
  #elif   DEBUG_EXTERNAL
     #define DEBUGLEVEL DEBUG_LEVEL_EXTERNAL
    #elif   DEBUG_INTERNAL
     #define DEBUGLEVEL DEBUG_LEVEL_INTERNAL
    #elif   PERFORMANCE
        #define DEBUGLEVEL DEBUG_LEVEL_PRODUCTION
  #elif   DEBUG_BREAK_ONLY
       #define DEBUGLEVEL DEBUG_LEVEL_BREAK_ONLY
  #else
      #define DEBUGLEVEL DEBUG_LEVEL_INTERNAL
    #endif
#endif

#ifndef  DEBUGLEVEL
#define DEBUGLEVEL DEBUG_LEVEL_PRODUCTION
#endif


#ifndef COMPONENT_SIGNATURE
#define COMPONENT_SIGNATURE '?*?*'
#endif



#define QuoteExceptionString(x) #x


/*
  ______________________________________________________________________________________
                                                                                        
    DEBUGASSERTMSG - all error reporting is routed through this macro, which calls the  
    system routine DebugAssert().  If you wish to use your own assertion/debugger break 
    routine, you can override DEBUGASSERTMSG by defining it before including this file. 
  ______________________________________________________________________________________
*/



#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/*
 *  DebugAssert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern void 
DebugAssert(
  OSType        componentSignature,
  UInt32        options,
  const char *  assertionString,
  const char *  exceptionString,
  const char *  errorString,
  const char *  fileName,
  long          lineNumber,
  void *        value);



#ifndef DEBUGASSERTMSG
#if DEBUGLEVEL == DEBUG_LEVEL_BREAK_ONLY
#define DEBUGASSERTMSG(componentSignature, options, assertionString, exceptionString, errorString, fileName, lineNumber, value ) \
    Debugger()
#elif DEBUGLEVEL == DEBUG_LEVEL_EXTERNAL
/* exclude code structure information */
#if (applec && (!__powerc))
#define DEBUGASSERTMSG(componentSignature, options, assertionString, exceptionString, errorString, fileName, lineNumber, value ) \
    DebugAssert(componentSignature, options, kComponentSignatureString, assertionString, NULL, NULL, 0, value )
#else
#define DEBUGASSERTMSG(componentSignature, options, assertionString, exceptionString, errorString, fileName, lineNumber, value ) \
   DebugAssert(componentSignature, options, kComponentSignatureString ": " assertionString, NULL, NULL, NULL, 0, value )
#endif
#elif DEBUGLEVEL == DEBUG_LEVEL_INTERNAL
/* include all info */
#if (applec && (!__powerc))
#define DEBUGASSERTMSG(componentSignature, options, assertionString, exceptionString, errorString, fileName, lineNumber, value ) \
    DebugAssert(componentSignature, options, kComponentSignatureString, assertionString, NULL, NULL, 0, value )
#else
#define DEBUGASSERTMSG(componentSignature, options, assertionString, exceptionString, errorString, fileName, lineNumber, value ) \
   DebugAssert(componentSignature, options, kComponentSignatureString ": " assertionString, exceptionString, errorString, fileName, lineNumber, value )
#endif
#else
/* no debugger message */
#define DEBUGASSERTMSG(componentSignature, options, assertionString, exceptionString, errorString, fileName, lineNumber, value )
#endif
#endif

/*
    kBlessedBusErrorBait is an address that will never be mapped
    by Mac OS 8 or 9. It is close to the middle of the 64K range from
    0x68F10000 to 0x68F1FFFF that is unmapped and cannot be accessed 
    without causing an exception. Thus, it's a good value to use for
    filling uninitialized pointers, etc.
*/
enum {
  kBlessedBusErrorBait          = 0x68F168F1
};


/*  TaskLevel masks*/
enum {
  k68kInterruptLevelMask        = 0x00000007,
  kInVBLTaskMask                = 0x00000010,
  kInDeferredTaskMask           = 0x00000020,
  kInSecondaryIntHandlerMask    = 0x00000040,
  kInNestedInterruptMask        = 0x00000080
};

enum {
  kComponentDebugOption         = 0     /* optionSelectorNum to turn breaks for component on/off*/
};

enum {
  kGetDebugOption               = 1,    /* get current debug option setting*/
  kSetDebugOption               = 2     /* set debug option*/
};

/*
    DebugComponentCallback
    DebugComponentCallback is the callback into a component that registers with DebugLib.
    It is called to get the debug option setting, or to turn a debug option on or off.
        Inputs:
            optionSelectorNum   The component debug option to set
            command             The command:
                                    kGetDebugOption     - get current debug option setting
                                    kSetDebugOption     - set debug option
        Outputs:
            optionSetting       The current setting if kGetDebugOption;
                                the new debug option if kSetDebugOption
*/
typedef CALLBACK_API( void , DebugComponentCallbackProcPtr )(SInt32 optionSelectorNum, UInt32 command, Boolean *optionSetting);
typedef STACK_UPP_TYPE(DebugComponentCallbackProcPtr)           DebugComponentCallbackUPP;
/*
    TaskLevel
    TaskLevel returns 0 if we're (probably) running at non-interrupt time.
    There's no way to make this perfect, but this is as close as we can get.
    If TaskLevel doesn't return 0, then the following masks can be used to learn more:
        k68kInterruptLevelMask      = 0x00000007
        kInVBLTaskMask              = 0x00000010
        kInDeferredTaskMask         = 0x00000020
        kInSecondaryIntHandlerMask  = 0x00000040
        kInNestedInterruptMask      = 0x00000080
*/
/*
 *  TaskLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern UInt32 
TaskLevel(void);



#define    ATTASKLEVEL0()  ( TaskLevel() == 0 )

/*
    NewDebugComponent
    NewDebugComponent registers a component with DebugLib.
        Inputs:
            componentSignature  The unique signature of component
            componentName       The displayable string naming the component
            componentCallback   The callback into component for working with options
        Result:
            noErr                           no error
            memFullErr                      could not allocate memory
            debuggingExecutionContextErr    routine cannot be called at this time
            debuggingDuplicateSignatureErr  componentSignature already registered
            debuggingInvalidNameErr         componentName is invalid (NULL)
*/
/*
 *  NewDebugComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern OSStatus 
NewDebugComponent(
  OSType                      componentSignature,
  ConstStr255Param            componentName,
  DebugComponentCallbackUPP   componentCallback);



/*
    NewDebugOption
    NewDebugOption registers a debug option with DebugLib.
        Inputs:
            componentSignature  The signature of component to register a debug option for
            optionSelectorNum   The selector number of this debug option
            optionName          The displayable string naming this debug option
        Result:
            noErr                           no error
            memFullErr                      could not allocate memory
            debuggingExecutionContextErr    called at interrupt time
            debuggingDuplicateOptionErr     optionSelectorNum already registered
            debuggingInvalidSignatureErr    componentSignature not registered
            debuggingInvalidNameErr         optionName is invalid (NULL)
            debuggingNoCallbackErr          debugging component has no callback
*/
/*
 *  NewDebugOption()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern OSStatus 
NewDebugOption(
  OSType             componentSignature,
  SInt32             optionSelectorNum,
  ConstStr255Param   optionName);



/*
    DisposeDebugComponent
    DisposeDebugComponent removes a component registration and all related debug options from DebugLib.
        Input:
            componentSignature  The unique signature of a component
        Result:
            noErr                           no error
            debuggingExecutionContextErr    called at interrupt time
            debuggingInvalidSignatureErr    componentSignature not registered
*/
/*
 *  DisposeDebugComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern OSStatus 
DisposeDebugComponent(OSType componentSignature);



/*
    GetDebugComponentInfo
    GetDebugComponentInfo returns a component registered with DebugLib.
        Inputs:
            index               The index into the list of registered components (1-based)
        Outputs:
            componentSignature  The unique signature of a component
            componentName       The displayable string naming a component
        Result:
            noErr                           no error
            debuggingNoMatchErr             debugging component not found at this index
*/
/*
 *  GetDebugComponentInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern OSStatus 
GetDebugComponentInfo(
  UInt32    index,
  OSType *  componentSignature,
  Str255    componentName);



/*
    GetDebugOptionInfo
    GetDebugOptionInfo returns a debug option registered with DebugLib.
        Inputs:
            index               The index into the list of registered debug options (0-based);
                                    0 = kComponentDebugOption 
            componentSignature  The unique signature of a component
        Outputs:
            optionSelectorNum   The selector number of this debug option
            optionName          The displayable string naming this debug option
            optionSetting       The current debug option setting
        Result:
            noErr                           no error
            debuggingInvalidSignatureErr    componentSignature not registered
            debuggingNoMatchErr             option not found at this index
*/
/*
 *  GetDebugOptionInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern OSStatus 
GetDebugOptionInfo(
  UInt32     index,
  OSType     componentSignature,
  SInt32 *   optionSelectorNum,
  Str255     optionName,
  Boolean *  optionSetting);



/*
    SetDebugOptionValue
    SetDebugOptionValue sets a debug option registered with DebugLib.
        Inputs:
            componentSignature  The unique signature of a component
            optionSelectorNum   The selector number of this debug option
            newOptionSetting    The new debug option setting
        Result:
            noErr                           no error
            debuggingInvalidSignatureErr    componentSignature not registered
            debuggingInvalidOptionErr       optionSelectorNum is not registered
*/
/*
 *  SetDebugOptionValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern OSStatus 
SetDebugOptionValue(
  OSType    componentSignature,
  SInt32    optionSelectorNum,
  Boolean   newOptionSetting);


/*
    DebugAssertOutputHandler
    DebugAssertOutputHandler is the callback that registers with DebugLib to handle the
    output from DebugAssert.
        Inputs:
            "componentSignature" through "value" are the raw values passed to DebugAssert
                when an exception occurs.
            outputMsg is the string DebugAssert build which would normally be passed to
                DebugStr if a DebugAssertOutputHandler isn't installed.
*/
typedef CALLBACK_API( void , DebugAssertOutputHandlerProcPtr )(OSType componentSignature, UInt32 options, const char *assertionString, const char *exceptionString, const char *errorString, const char *fileName, long lineNumber, void *value, ConstStr255Param outputMsg);
typedef STACK_UPP_TYPE(DebugAssertOutputHandlerProcPtr)         DebugAssertOutputHandlerUPP;
/*
    InstallDebugAssertOutputHandler
    InstallDebugAssertOutputHandler installs a DebugAssertOutputHandler which DebugAssert calls
    instead of DebugStr.
        Inputs:
            handler     the DebugAssertOutputHandler to install or NULL to switch back to
                        the default handler (DebugStr).
*/
/*
 *  InstallDebugAssertOutputHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DebugLib 1.0 and later
 */
extern void 
InstallDebugAssertOutputHandler(DebugAssertOutputHandlerUPP handler);


/*
    dprintf() takes a variable argument list and 'prints' that to the debugging output
    handler.  Calling dprintf() from anything but C or C++ is tricky.
*/
/*
 *  dprintf()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DebugLib 1.1 and later
 */




/*  vdprintf() takes a va_args list and 'prints' that to the debugging output handler.*/
/*
 *  vdprintf()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DebugLib 1.1 and later
 */



   
   #if DEBUG
      /*  For debug builds, you can use DPRINTF as a dprintf which goes away in non-debug
         *  builds.  To use it, double-parenthesize the argument - ie, use
      *
      *  DPRINTF(("formatString %d", 5 ));
       *
      *  This is sadly necessary because a macro can not have a variable number of arguments.
        *
      */

       #define DPRINTF(x)  dprintf x
  #else
      #define DPRINTF(x)  { }
    #endif

/*
 *  NewDebugComponentCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebugComponentCallbackUPP
NewDebugComponentCallbackUPP(DebugComponentCallbackProcPtr userRoutine);

/*
 *  NewDebugAssertOutputHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebugAssertOutputHandlerUPP
NewDebugAssertOutputHandlerUPP(DebugAssertOutputHandlerProcPtr userRoutine);

/*
 *  DisposeDebugComponentCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebugComponentCallbackUPP(DebugComponentCallbackUPP userUPP);

/*
 *  DisposeDebugAssertOutputHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebugAssertOutputHandlerUPP(DebugAssertOutputHandlerUPP userUPP);

/*
 *  InvokeDebugComponentCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDebugComponentCallbackUPP(
  SInt32                     optionSelectorNum,
  UInt32                     command,
  Boolean *                  optionSetting,
  DebugComponentCallbackUPP  userUPP);

/*
 *  InvokeDebugAssertOutputHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDebugAssertOutputHandlerUPP(
  OSType                       componentSignature,
  UInt32                       options,
  const char *                 assertionString,
  const char *                 exceptionString,
  const char *                 errorString,
  const char *                 fileName,
  long                         lineNumber,
  void *                       value,
  ConstStr255Param             outputMsg,
  DebugAssertOutputHandlerUPP  userUPP);

/* no-op asserts for production code*/

#if DEBUGLEVEL == DEBUG_LEVEL_PRODUCTION
#define check(assertion)
#define check_string( assertion, cstring )
#define check_noerr(err)
#define check_noerr_string( error, cstring )
#define debug_string( cstring )
#define require( assertion, label )                             do { if( !(assertion) ) goto label; } while(false)
#define require_string( assertion, label, string )                       require(assertion, label)
#define require_quiet( assertion, label )                     require( assertion, label )
#define require_noerr( error, label )                           do { if( (error) != noErr ) goto label; } while(false)
#define require_noerr_quiet( assertion, label )                  require_noerr( assertion, label )
#define require_noerr_action( error, label, action )          do { if( (error) != noErr ) { {action;}; goto label; } } while(false)
#define require_noerr_action_quiet( assertion, label, action )    require_noerr_action( assertion, label, action )
#define require_action( assertion, label, action )                     do { if( !(assertion) ) { {action;}; goto label; } } while(false)
#define require_action_quiet( assertion, label, action )      require_action( assertion, label, action )
#define require_action_string( assertion, label, action, cstring )                       do { if( !(assertion) ) { {action;}; goto label; } } while(false)

#else


/*______________________________________________________________________________________*/

#define debug_string(string)                                           \
  do {                                                                \
      DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,           \
                  QuoteExceptionString(string), NULL, NULL,           \
                  __FILE__, __LINE__, 0);                             \
  } while (false)

/*______________________________________________________________________________________*/

#define check(assertion)                                               \
  do {                                                                \
      if (!(assertion))                                               \
      {                                                               \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      QuoteExceptionString(assertion), NULL, NULL,    \
                      __FILE__, __LINE__, 0);                         \
      }                                                               \
  } while (false)

/*______________________________________________________________________________________*/



#define check_string(assertion, cstring)                               \
  do {                                                                \
      if (!(assertion))                                               \
      {                                                               \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      QuoteExceptionString(assertion), cstring, NULL, \
                      __FILE__, __LINE__, 0);                         \
      }                                                               \
  } while (false)



/*______________________________________________________________________________________*/

#define check_noerr(error)                                                         \
  do {                                                                        \
      OSStatus localError = error;                                            \
      if (localError != noErr)                                                \
      {                                                                       \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,               \
                      QuoteExceptionString(error) "== noErr", NULL, NULL, \
                      __FILE__, __LINE__, (void *)localError);                \
      }                                                                       \
  } while (false)

/*______________________________________________________________________________________*/

#define check_noerr_string(error, cstring)                                             \
  do {                                                                            \
      OSStatus localError = error;                                                \
      if (localError != noErr)                                                    \
      {                                                                           \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,                   \
                      QuoteExceptionString(error) "== noErr\n", cstring, NULL,    \
                      __FILE__, __LINE__, (void *)localError);                    \
      }                                                                           \
  } while (false)

/*______________________________________________________________________________________*/

#define require(assertion, exception)                                      \
  do {                                                                \
      if (!(assertion))                                               \
      {                                                               \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      QuoteExceptionString(assertion),                \
                      QuoteExceptionString(exception),                \
                      NULL, __FILE__, __LINE__, 0);                   \
          goto exception;                                             \
      }                                                               \
  } while (false)

/*______________________________________________________________________________________*/

#define require_noerr(error, exception)                                \
  do {                                                                \
      OSStatus localError = error;                                    \
      if (localError != noErr)                                        \
      {                                                               \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      QuoteExceptionString(error) "== noErr",         \
                      QuoteExceptionString(exception),                \
                      NULL, __FILE__, __LINE__, (void *)localError ); \
          goto exception;                                             \
      }                                                               \
  } while (false)

/*______________________________________________________________________________________*/

#define require_string(assertion, exception, string)                   \
  do {                                                                \
      if (!(assertion))                                               \
      {                                                               \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      string, QuoteExceptionString(assertion),        \
                      QuoteExceptionString(exception),                \
                      __FILE__, __LINE__, 0 );        \
          goto exception;                                             \
      }                                                               \
  } while (false)


/*______________________________________________________________________________________*/

#define require_noerr_action(error, exception, action)                 \
  do {                                                                \
      OSStatus localError = error;                                    \
      if (localError != noErr)                                        \
      {                                                               \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      QuoteExceptionString(error) "== noErr",         \
                      QuoteExceptionString(exception),                \
                      NULL, __FILE__, __LINE__, (void *)localError ); \
          { action; }                                                 \
          goto exception;                                             \
      }                                                               \
  } while (false)

/*______________________________________________________________________________________*/

#define require_noerr_quiet(error, exception)                              \
  do {                                                                \
      if (error != noErr)                                             \
      {                                                               \
          goto exception;                                             \
      }                                                               \
  } while (false)


/*______________________________________________________________________________________*/

#define require_noerr_action_quiet(error, exception, action)           \
  do {                                                                \
      if (error != noErr)                                             \
      {                                                               \
          { action; }                                                 \
          goto exception;                                             \
      }                                                               \
  } while (false)


/*______________________________________________________________________________________*/

#define require_action(assertion, exception, action)               \
  do {                                                            \
      if (!(assertion))                                           \
      {                                                           \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      QuoteExceptionString(assertion),            \
                      QuoteExceptionString(exception),            \
                      NULL, __FILE__, __LINE__, 0);               \
          { action; }                                             \
          goto exception;                                         \
      }                                                           \
  } while (false)

/*______________________________________________________________________________________*/

#define require_action_string(assertion, exception, action, cstring)   \
  do {                                                                \
      if (!(assertion))                                               \
      {                                                               \
          DEBUGASSERTMSG(COMPONENT_SIGNATURE, DEBUG_NO_OPTIONS,       \
                      cstring ": " QuoteExceptionString(assertion),   \
                      QuoteExceptionString(exception),                \
                      NULL, __FILE__, __LINE__, 0);                   \
          { action; }                                                 \
          goto exception;                                             \
      }                                                               \
  } while (false)

/*______________________________________________________________________________________*/

#define require_quiet(assertion, exception)                        \
  do {                                                            \
      if (!(assertion))                                               \
      {                                                               \
          goto exception;                                         \
      }                                                           \
  } while (false)


/*______________________________________________________________________________________*/

#define require_action_quiet(assertion, exception, action)             \
  do {                                                            \
      if (!(assertion))                                               \
      {                                                               \
          { action; }                                             \
          goto exception;                                         \
      }                                                           \
  } while (false)



#endif /* DEBUG_LEVEL_PRODUCTION */

/*    Define these in terms of the check() and require macros.  In non-debug builds, the check calls
 go away and the require macros are mostly checks and jumps.
*/
#define check_tasklevel0( )                                          check( ATTASKLEVEL0() )
#define check_tasklevel0_string( string )                           check_string( ATTASKLEVEL0(), string )

#define require_tasklevel0( label )                                 require( ATTASKLEVEL0(), label )
#define require_tasklevel0_string( label, string )                 require_string( ATTASKLEVEL0(), label, string )
#define require_tasklevel0_action( label, string, action )          require_action( ATTASKLEVEL0(), label, action )
#define require_tasklevel0_action_string( label, string, action )   require_action_string( ATTASKLEVEL0(), label, action, string )


/*______________________________________________________________________________________*/

#if DEBUGLEVEL > DEBUG_LEVEL_PRODUCTION
   #define verify(assertion)       check(assertion)
   #define verify_noerr(assertion) check_noerr( (assertion) )
#else
   #define verify(assertion)       do { (void) (assertion); } while (0)
   #define verify_noerr(assertion) verify(assertion)
#endif



/*______________________________________________________________________________________*/

#define ncheck(assertion)                                      check( !(assertion) )
#define ncheck_string(assertion, cstring)                     check_string( !(assertion), cstring )
#define nrequire(assertion, exception)                            require( !(assertion), exception )
#define nrequire_action(assertion, exception, action)            require_action( !(assertion), exception, action )
#define nrequire_quiet(assertion, exception)                  require_quiet( !(assertion), exception )
#define nrequire_action_quiet(assertion, exception, action)        require_action_quiet( !(assertion), exception, action )
#define nrequire_string(assertion, exception, string)           require_string( !(assertion), exception, string )






#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DEBUGGING__ */

