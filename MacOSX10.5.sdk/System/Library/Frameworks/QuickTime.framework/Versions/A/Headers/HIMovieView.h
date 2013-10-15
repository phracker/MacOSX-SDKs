/*
     File:       QuickTime/HIMovieView.h
 
     Contains:   HIView-based movie playback
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 2004-2006 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __HIMOVIEVIEW__
#define __HIMOVIEVIEW__

#ifndef __HIVIEW__
#include <HIToolbox/HIView.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* QuickTime is not available to 64-bit clients */

#if !__LP64__


/*
 *  kHIMovieViewClassID
 *  
 *  Summary:
 *    Class ID for HIMovieView
 */
#define kHIMovieViewClassID             CFSTR("com.apple.quicktime.HIMovieView")

/*
 *  Summary:
 *    HIMovieView Event class
 */
enum {

  /*
   * Events related to movie views.
   */
  kEventClassMovieView          = 'moov'
};


/*
 *  kEventClassMovieView / kEventMovieViewOptimalBoundsChanged
 *  
 *  Summary:
 *    Sent when the movie size changes.
 *  
 *  Parameters:
 *    
 *    --> kEventParamDirectObject (in, typeControlRef)
 *          The movie view whose size is changing.
 *    
 *    --> kEventParamControlOptimalBounds (in, typeHIRect)
 *          The new optimal bounds.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 */
enum {
  kEventMovieViewOptimalBoundsChanged = 1
};



/*
 *  Summary:
 *    HIMovieView attributes
 */
enum {

  /*
   * No attributes
   */
  kHIMovieViewNoAttributes      = 0L,

  /*
   * Movie controller bar is visible below visual content
   */
  kHIMovieViewControllerVisibleAttribute = (1L << 0),

  /*
   * Automatically call MCIdle() at appropriate times
   */
  kHIMovieViewAutoIdlingAttribute = (1L << 1),

  /*
   * Accepts keyboard focus
   */
  kHIMovieViewAcceptsFocusAttribute = (1L << 2),

  /*
   * Movie editing enabled
   */
  kHIMovieViewEditableAttribute = (1L << 3),

  /*
   * Handles editing HI commands such as cut, copy and paste
   */
  kHIMovieViewHandleEditingHIAttribute = (1L << 4),

  /*
   * Combination of kHIMovieViewControllerVisibleAttribute,
   * kHIMovieViewAutoIdlingAttribute, and
   * kHIMovieViewAcceptsFocusAttribute
   */
  kHIMovieViewStandardAttributes = (kHIMovieViewControllerVisibleAttribute | kHIMovieViewAutoIdlingAttribute | kHIMovieViewAcceptsFocusAttribute)
};

/*
 *  HIMovieViewCreate()
 *  
 *  Summary:
 *    Creates an HIMovieView object
 *  
 *  Discussion:
 *    If successful, the created view will have a single retain count.
 *  
 *  Parameters:
 *    
 *    inMovie:
 *      [in]  Initial movie to view, may be NULL
 *    
 *    inAttributes:
 *      [in]  Initial HIMovieView attributes
 *    
 *    outMovieView:
 *      [out] Points to variable to receive new HIMovieView
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIMovieViewCreate(
  Movie        inMovie,
  OptionBits   inAttributes,
  HIViewRef *  outMovieView)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewGetMovie()
 *  
 *  Summary:
 *    Returns the view's current movie.
 *  
 *  Parameters:
 *    
 *    inView:
 *      [in]  The HIMovieView
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Movie 
HIMovieViewGetMovie(HIViewRef inView)                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewSetMovie()
 *  
 *  Summary:
 *    Sets the view's current movie.
 *  
 *  Parameters:
 *    
 *    inView:
 *      [in]  The HIMovieView
 *    
 *    inMovie:
 *      [in]  The new movie to display
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIMovieViewSetMovie(
  HIViewRef   inView,
  Movie       inMovie)                                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewGetAttributes()
 *  
 *  Summary:
 *    Returns the view's current attributes.
 *  
 *  Parameters:
 *    
 *    inView:
 *      [in]  The HIMovieView
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OptionBits 
HIMovieViewGetAttributes(HIViewRef inView)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewChangeAttributes()
 *  
 *  Summary:
 *    Changes the views attributes.
 *  
 *  Discussion:
 *    Setting an attribute takes precedence over clearing the attribute.
 *  
 *  Parameters:
 *    
 *    inView:
 *      [in]  The HIMovieView
 *    
 *    inAttributesToSet:
 *      [in]  Attributes to set
 *    
 *    inAttributesToClear:
 *      [in]  Attributes to clear
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIMovieViewChangeAttributes(
  HIViewRef    inView,
  OptionBits   inAttributesToSet,
  OptionBits   inAttributesToClear)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewGetMovieController()
 *  
 *  Summary:
 *    Returns the view's current movie controller.
 *  
 *  Parameters:
 *    
 *    inView:
 *      [in]  The HIMovieView
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern MovieController 
HIMovieViewGetMovieController(HIViewRef inView)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewGetControllerBarSize()
 *  
 *  Summary:
 *    Returns the size of the visible movie controller bar.
 *  
 *  Parameters:
 *    
 *    inView:
 *      [in]  The HIMovieView
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern HISize 
HIMovieViewGetControllerBarSize(HIViewRef inView)             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewPlay()
 *  
 *  Summary:
 *    Convenience routine to play the view's current movie.
 *  
 *  Discussion:
 *    If the movie is already playing, this function does nothing.
 *  
 *  Parameters:
 *    
 *    movieView:
 *      [in]  The movie view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIMovieViewPlay(HIViewRef movieView)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIMovieViewPause()
 *  
 *  Summary:
 *    Convenience routine to pause the view's current movie.
 *  
 *  Discussion:
 *    If the movie is already paused, this function does nothing.
 *  
 *  Parameters:
 *    
 *    movieView:
 *      [in]  The movie view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIMovieViewPause(HIViewRef movieView)                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



#endif // !__LP64__


#ifdef __cplusplus
}
#endif

#endif /* __HIMOVIEVIEW__ */

