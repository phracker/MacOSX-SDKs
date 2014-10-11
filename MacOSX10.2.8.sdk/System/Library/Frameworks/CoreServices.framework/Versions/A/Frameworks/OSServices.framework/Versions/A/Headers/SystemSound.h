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
  kSystemSoundUnspecifiedError  = -1500
};

/* ================================================================================ */
/* Types                                                                            */
/* ================================================================================ */
typedef UInt32                          SystemSoundActionID;
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
 *    SystemSoundActionID, which can be passed to SystemSoundPlay(),
 *    will be returned .
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



#ifdef __cplusplus
}
#endif

#endif /* __SYSTEMSOUND__ */

