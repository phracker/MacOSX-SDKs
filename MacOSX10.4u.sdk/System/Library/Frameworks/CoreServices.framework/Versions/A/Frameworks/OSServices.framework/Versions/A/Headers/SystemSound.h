/*
     File:       OSServices/SystemSound.h
 
     Contains:   SystemSound include file
 
     Version:    OSServices-101.1~790
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SYSTEMSOUND__
#define __SYSTEMSOUND__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================================ */
/* Errors                                                                           */
/* ================================================================================ */
enum {
  kSystemSoundNoError           = 0,
  kSystemSoundUnspecifiedError  = -1500,
  kSystemSoundClientTimedOutError = -1501
};

/* ================================================================================ */
/* Types                                                                            */
/* ================================================================================ */
typedef UInt32                          SystemSoundActionID;
typedef CALLBACK_API_C( OSStatus , SystemSoundCompletionProcPtr )(SystemSoundActionID actionID, void *userData);
typedef STACK_UPP_TYPE(SystemSoundCompletionProcPtr)            SystemSoundCompletionUPP;
/*
 *  NewSystemSoundCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SystemSoundCompletionUPP
NewSystemSoundCompletionUPP(SystemSoundCompletionProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  DisposeSystemSoundCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSystemSoundCompletionUPP(SystemSoundCompletionUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  InvokeSystemSoundCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeSystemSoundCompletionUPP(
  SystemSoundActionID       actionID,
  void *                    userData,
  SystemSoundCompletionUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* ================================================================================ */
/* Public APIs                                                                      */
/* ================================================================================ */
/*
 *  AlertSoundPlay()
 *  
 *  Summary:
 *    Play an Alert Sound
 *  
 *  Discussion:
 *    Play the user's current alert sound, interrupting any previously
 *    playing alert sound.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern void 
AlertSoundPlay(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  AlertSoundPlayCustomSound()
 *  
 *  Summary:
 *    Play a User designated Alert Sound
 *  
 *  Discussion:
 *    Play a sound, designated by a SystemSoundActionID, with the
 *    behavior of AlertSoundPlay().
 *  
 *  Parameters:
 *    
 *    inAction:
 *      A SystemSoundActionID indicating the desired Sound to be played
 *      with AlertSound behavior.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern void 
AlertSoundPlayCustomSound(SystemSoundActionID inAction)       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  SystemSoundPlay()
 *  
 *  Summary:
 *    Play a System Sound
 *  
 *  Discussion:
 *    Immediately play the sound designated by actionID. Use for one
 *    time actions that do not require a duration or modification
 *    during playback. Sustain loops in the sound will be ignored.
 *  
 *  Parameters:
 *    
 *    inAction:
 *      A SystemSoundActionID indicating the desired System Sound to be
 *      played.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern void 
SystemSoundPlay(SystemSoundActionID inAction)                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SystemSoundGetActionID()
 *  
 *  Summary:
 *    Create a 'custom' System Sound by providing an audio file.
 *  
 *  Discussion:
 *    If the user wants to add a sound that can be played via
 *    SystemSoundPlay(), an FSRef for an audio file can be passed and a
 *    SystemSoundActionID, which can be passed to SystemSoundPlay() or
 *    AlertSoundPlayCustomSound(), will be returned. It is important
 *    that SystemSoundRemoveActionID() be called when the action is no
 *    longer needed by the client application so the System Sound
 *    Server can release any resources dedicated to the returned action
 *    id.
 *  
 *  Parameters:
 *    
 *    userFile:
 *      An const FSRef * for the audio file to be used as a System
 *      Sound. Any audio file supported by the AudioFile APIs in the
 *      AudioToolbox framework may be used.
 *    
 *    outAction:
 *      If successful, a SystemSoundActionID will be returned, which in
 *      turn can be passed to SystemSoundPlay().
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SystemSoundGetActionID(
  const FSRef *          userFile,
  SystemSoundActionID *  outAction)                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SystemSoundRemoveActionID()
 *  
 *  Summary:
 *    Remove a 'custom' System Sound.
 *  
 *  Discussion:
 *    If the user no longer needs to use the custom system sound that
 *    was created via SystemSoundGetActionID, this function should be
 *    called so the SystemSoundServer can release resources that are no
 *    longer needed.
 *  
 *  Parameters:
 *    
 *    inAction:
 *      A SystemSoundActionID indicating the desired System Sound to be
 *      removed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SystemSoundRemoveActionID(SystemSoundActionID inAction)       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SystemSoundSetCompletionRoutine()
 *  
 *  Summary:
 *    Call the provided Completion Routine when the provided
 *    SystemSoundActionID finishes playing in the server.
 *  
 *  Discussion:
 *    Once set, the System Sound Server will send a message to the
 *    System Sound Client indicating which SystemSoundActionID has
 *    finished playing.
 *  
 *  Parameters:
 *    
 *    inAction:
 *      The SystemSoundActionID that the completion routine will be
 *      associated with.
 *    
 *    inRunLoop:
 *      A CFRunLoopRef indicating the desired run loop the completion
 *      routine should be run on. Pass NULL for the main run loop.
 *    
 *    inRunLoopMode:
 *      A CFStringRef indicating the run loop mode for the runloop mode
 *      for the runloop where the completion routine will be executed.
 *      Pass NULL to use kCFRunLoopDefaultMode.
 *    
 *    inCompletionRoutine:
 *      A SystemSoundCompletionProc for the completion routine proc to
 *      be called when the provided SystemSoundActionID has completed
 *      playing in the server.
 *    
 *    inUserData:
 *      A void * to pass user data to the completion routine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SystemSoundSetCompletionRoutine(
  SystemSoundActionID        inAction,
  CFRunLoopRef               inRunLoop,
  CFStringRef                inRunLoopMode,
  SystemSoundCompletionUPP   inCompletionRoutine,
  void *                     inUserData)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  SystemSoundRemoveCompletionRoutine()
 *  
 *  Summary:
 *    Remove the Completion Routine being used for the provided
 *    SystemSoundActionID.
 *  
 *  Discussion:
 *    To be called when it is no longer desired for the Completion
 *    Routine to be called when a System Sound action has finished
 *    playing.
 *  
 *  Parameters:
 *    
 *    inAction:
 *      A SystemSoundActionID that currently has an associated
 *      completion routine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern void 
SystemSoundRemoveCompletionRoutine(SystemSoundActionID inAction) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __SYSTEMSOUND__ */

