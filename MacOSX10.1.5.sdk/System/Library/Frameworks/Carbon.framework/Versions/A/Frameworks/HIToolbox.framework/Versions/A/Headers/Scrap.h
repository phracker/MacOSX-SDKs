/*
     File:       HIToolbox/Scrap.h
 
     Contains:   Scrap Manager Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SCRAP__
#define __SCRAP__

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif




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
    ________________________________________________________________
    UNIVERSAL SCRAP MANAGER INTERFACES
    ________________________________________________________________
    The following interfaces are available when compiling for BOTH
    Carbon AND Mac OS 8.
    ________________________________________________________________
*/
/*
    While were in here mucking about, we defined a new type to
    to put some confusion to rest. The old calls, as well as the
    new calls, use the new type. Existing clients should be
    blissfully ignorant.
*/

typedef FourCharCode                    ScrapFlavorType;
/*
    Newsflash! After 15 years of arduous toil, it's finally possible
    for specially trained typists wielding advanced text editing
    technology to define symbolic names for commonly used scrap
    flavor type constants! Apple triumphs again!
*/
enum {
  kScrapFlavorTypePicture       = 'PICT', /* contents of a PicHandle*/
  kScrapFlavorTypeText          = 'TEXT', /* stream of characters*/
  kScrapFlavorTypeTextStyle     = 'styl', /* see TEGetStyleScrapHandle*/
  kScrapFlavorTypeMovie         = 'moov', /* reference to a movie*/
  kScrapFlavorTypeSound         = 'snd ', /* see SndRecord and SndPlay*/
  kScrapFlavorTypeUnicode       = 'utxt', /* stream of UTF16 characters*/
  kScrapFlavorTypeUnicodeStyle  = 'ustl' /* ATSUI defines; Textension uses*/
};

/*
    If you are a Carbon client and you need to run on Mac OS 8,
    you may still need to load and unload the scrap. Under Mac OS
    X, the scrap is held by the pasteboard server instead of in a
    handle in your app's heap, so LoadScrap and UnloadScrap do
    nothing when called under Mac OS X.
*/

/*
 *  LoadScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSStatus 
LoadScrap(void);


/*
 *  UnloadScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSStatus 
UnloadScrap(void);


#if CALL_NOT_IN_CARBON
/*
    ________________________________________________________________
    MAC OS 8 SCRAP MANAGER INTERFACES
    ________________________________________________________________
    The following interfaces are available only when compiling for
    plain vanilla Mac OS 8. We didn't add comments to them because
    Inside Mac covers them in detail.
    ________________________________________________________________
*/
struct ScrapStuff {
  SInt32              scrapSize;
  Handle              scrapHandle;
  SInt16              scrapCount;
  SInt16              scrapState;
  StringPtr           scrapName;
};
typedef struct ScrapStuff               ScrapStuff;
typedef ScrapStuff *                    PScrapStuff;
typedef ScrapStuff *                    ScrapStuffPtr;
#endif  /* CALL_NOT_IN_CARBON */

/*
 *  InfoScrap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetScrap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ZeroScrap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PutScrap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
    ________________________________________________________________
    CARBON SCRAP MANAGER INTERFACES
    ________________________________________________________________
    The following interfaces are available only when compiling for
    Carbon.
    ________________________________________________________________
*/

/*
    When promising a scrap flavor, it's OK if you
    don't yet know how big the flavor data will be.
    In this case, just pass kScrapFlavorSizeUnknown
    for the flavor data size.
*/

enum {
  kScrapFlavorSizeUnknown       = -1
};

/*
    kScrapReservedFlavorType is a flavor type which is reserved
    for use by Scrap Manager. If you pass it to Scrap Manager,
    it will be rejected.
*/

enum {
  kScrapReservedFlavorType      = 'srft'
};

/*
    We've added scrap flavor flags ala Drag Manager.

    kScrapFlavorMaskNone means you want none of the flags.

    kScrapFlavorSenderOnlyMask means only the process which
    put the flavor on the scrap can see it. If some other
    process put a flavor with this flag on the scrap,
    your process will never see the flavor, so there's
    no point in testing for this flag.

    kScrapFlavorTranslated means the flavor was translated
    from some other flavor in the scrap by Translation Manager.
    Most callers should not care about this bit.
*/
enum {
  kScrapFlavorMaskNone          = 0x00000000,
  kScrapFlavorMaskSenderOnly    = 0x00000001,
  kScrapFlavorMaskTranslated    = 0x00000002
};

typedef UInt32                          ScrapFlavorFlags;
/*
    ScrapFlavorInfo describes a single flavor within
    a scrap.
*/
struct ScrapFlavorInfo {
  ScrapFlavorType     flavorType;
  ScrapFlavorFlags    flavorFlags;
};
typedef struct ScrapFlavorInfo          ScrapFlavorInfo;
typedef struct OpaqueScrapRef*          ScrapRef;
/*
    kScrapRefNone is guaranteed to be an invalid ScrapRef.  This 
    is convenient when initializing application variables.
*/
#define kScrapRefNone                   ((ScrapRef)NULL)
/*
    Defined Apple scrap names for GetScrapByName
    kScrapClipboardScrap    traditional clipboard scrap
    kScrapFindScrap         compatable with Cocoa's global find scrap
*/
#define kScrapClipboardScrap            CFSTR("com.apple.scrap.clipboard")
#define kScrapFindScrap                 CFSTR("com.apple.scrap.find")

/*  Enumerated options to be passed to GetScrapByName*/

enum {
  kScrapGetNamedScrap           = 0,    /* get current named scrap without bumping*/
  kScrapClearNamedScrap         = (1L << 0) /* aquire the named scrap, bumping and clearing*/
};

/*
    GetScrapByName allows access to an indefinite number of public or private
    scraps.  The constant kScrapClipboardScrap refers to the "current" scrap
    we've all come to know and love.  kScrapFindScrap allows Carbon apps to
    interact seamlessly with Cocoa's global find scrap.  Note that calling:

        GetScrapByName( kScrapClipboardScrap, kScrapGetNamedScrap, &scrap );

    is an exact match to the call:
    
        GetCurrentScrap( &scrap );

    Additionally, a call to:

        GetScrapByName( kScrapClipboardScrap, kScrapClearNamedScrap, &scrap );

    is a replacement for the sequence:
    
        ClearCurrentScrap();
        GetCurrentScrap( &scrap );

    You can use this API to generate your own private scraps to use as a high
    level interprocess communication between your main and helper apps.  The Java
    naming convention is suggested for your scraps ( ie. com.joeco.scrap.secret ).
*/
/*
 *  GetScrapByName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetScrapByName(
  CFStringRef   name,
  OptionBits    options,
  ScrapRef *    scrap);


/*
    GetCurrentScrap obtains a reference to the current scrap.
    The ScrapRef obtained via GetCurrentScrap will become
    invalid and unusable after the scrap is cleared.
*/

/*
 *  GetCurrentScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetCurrentScrap(ScrapRef * scrap);


/*
    GetScrapFlavorFlags tells you [a] whether the scrap contains
    data for a particular flavor and [b] some things about that
    flavor if it exists. This call never blocks, and is useful
    for deciding whether to enable the Paste item in your Edit
    menu, among other things.
*/

/*
 *  GetScrapFlavorFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetScrapFlavorFlags(
  ScrapRef            scrap,
  ScrapFlavorType     flavorType,
  ScrapFlavorFlags *  flavorFlags);


/*
    GetScrapFlavorSize gets the size of the data of the specified
    flavor. This function blocks until the specified flavor
    data is available. GetScrapFlavorSize is intended as a prelude
    to allocating memory and calling GetScrapFlavorData.
*/

/*
 *  GetScrapFlavorSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetScrapFlavorSize(
  ScrapRef          scrap,
  ScrapFlavorType   flavorType,
  Size *            byteCount);


/*
    GetScrapFlavorData gets the data from the specified flavor in the
    specified scrap. This function blocks until the specified flavor
    data is available. Specify the maximum size your buffer can contain;
    on output, this function produces the number of bytes that were
    available (even if this is more than you requested).
*/

/*
 *  GetScrapFlavorData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetScrapFlavorData(
  ScrapRef          scrap,
  ScrapFlavorType   flavorType,
  Size *            byteCount,
  void *            destination);


/*
    ClearCurrentScrap clears the current scrap. Call this
    first when the user requests a Copy or Cut operation --
    even if you maintain a private scrap! You should not wait
    until receiving a suspend event to call ClearCurrentScrap. Call
    it immediately after the user requests a Copy or Cut operation.
    You don't need to put any data on the scrap immediately (although
    it's perfectly fine to do so). You DO need to call GetCurrentScrap
    after ClearCurrentScrap so you'll have a valid ScrapRef to pass
    to other functions.
*/

/*
 *  ClearCurrentScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ClearCurrentScrap(void);


/*
        ClearScrap will clear the scrap passed in and return the bumped
        ScrapRef value. ClearScrap behaves similarly to GetScrapByName
        when called with the kScrapClearNamedScrap option with the
        benefit of not requiring a name in the event one is not available.
*/
/*
 *  ClearScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ClearScrap(ScrapRef * inOutScrap);


/*
        PutScrapFlavor is a lot like PutScrap, with two differences:
        we added a ScrapRef parameter at the beginning and you can
        "promise" various aspects of a flavor. If you pass a NIL
        data pointer, this is a promise that in the future you
        will provide data for this flavor. Provide the data
        through a subsequent call to PutScrapFlavor, either later
        in the same code flow or during a scrap promise keeper proc.
        If you know how big the data is, you can pass the size as
        well, and this may allow subsequent callers of GetScrapFlavorInfo
        to avoid blocking. If you don't know the size, pass -1.
        If you pass a 0 size, you are telling Scrap Manager not to
        expect any data for this flavor. In this case, the flavor
        data pointer is ignored. NOTE: the last time you can provide
        scrap flavor data is when your scrap promise keeper gets
        called. It is NOT possible to call PutScrapFlavor while
        handling a suspend event; suspend events under Carbon
        simply don't work the way they do under Mac OS 8.

        The method for setting Scrap Manager promises differs from that for Drag Manger promises.
        This chart describes the method for setting scrap promises via PutScrapFlavor().
    
        dataPtr         dataSize                                result
     pointer value  actual data size    The data of size dataSize pointed to by dataPtr is added to the scrap.
           0        actual data size    A promise for data of size dataSize is placed on the scrap.
           0               -1           A promise for data of an undetermined size is placed on the scrap.
        ignored             0           A flavor with no data expected is placed on the scrap.  This is not a promise.
*/
/*
 *  PutScrapFlavor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PutScrapFlavor(
  ScrapRef           scrap,
  ScrapFlavorType    flavorType,
  ScrapFlavorFlags   flavorFlags,
  Size               flavorSize,
  const void *       flavorData);       /* can be NULL */


/*
    ScrapPromiseKeeper is a function you write which is called by
    Scrap Manager as needed to keep your earlier promise of a
    particular scrap flavor. When your function is called, deliver
    the requested data by calling PutScrapFlavor.
*/

typedef CALLBACK_API( OSStatus , ScrapPromiseKeeperProcPtr )(ScrapRef scrap, ScrapFlavorType flavorType, void *userData);
typedef STACK_UPP_TYPE(ScrapPromiseKeeperProcPtr)               ScrapPromiseKeeperUPP;
/*
 *  NewScrapPromiseKeeperUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ScrapPromiseKeeperUPP
NewScrapPromiseKeeperUPP(ScrapPromiseKeeperProcPtr userRoutine);

/*
 *  DisposeScrapPromiseKeeperUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeScrapPromiseKeeperUPP(ScrapPromiseKeeperUPP userUPP);

/*
 *  InvokeScrapPromiseKeeperUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeScrapPromiseKeeperUPP(
  ScrapRef               scrap,
  ScrapFlavorType        flavorType,
  void *                 userData,
  ScrapPromiseKeeperUPP  userUPP);

/*
    SetScrapPromiseKeeper associates a ScrapPromiseKeeper with a
    scrap. You can remove a ScrapPromiseKeeper from a scrap by
    passing a NIL ScrapPromiseKeeper to SetScrapPromiseKeeper.
    Pass whatever you like in the last parameter; its value will
    be passed to your ScrapPromiseKeeper, which can do whatever
    it likes with the value. You might choose to pass a pointer
    or handle to some private scrap data which the
    ScrapPromiseKeeper could use in fabricating one or more
    promised flavors.
*/
/*
 *  SetScrapPromiseKeeper()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetScrapPromiseKeeper(
  ScrapRef                scrap,
  ScrapPromiseKeeperUPP   upp,
  const void *            userData);


/*
    GetScrapFlavorCount produces the number of
    items which can be obtained by GetScrapFlavorInfoList.
*/

/*
 *  GetScrapFlavorCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetScrapFlavorCount(
  ScrapRef   scrap,
  UInt32 *   infoCount);


/*
    GetScrapFlavorInfoList fills a list (array)
    of items which each describe the corresponding
    flavor in the scrap. It fills no more array
    elements as are specified. On exit, it produces
    the count of elements it filled (which may be
    smaller than the count requested). Yes, YOU
    must provide the memory for the array.
*/

/*
 *  GetScrapFlavorInfoList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetScrapFlavorInfoList(
  ScrapRef          scrap,
  UInt32 *          infoCount,
  ScrapFlavorInfo   info[]);



/*
    CallInScrapPromises forces all promises to be kept.
    If your application promises at least one flavor
    AND it does NOT adopt the new event model, you
    should call this function when your application
    is about to quit. If your app promises no flavors,
    there is no need to call this function, and if
    your app adopts the new event model, this function
    will be called automagically for you. It doesn't
    hurt to call this function more than once, though
    promise keepers may be asked to keep promises
    they already tried and failed.
*/

/*
 *  CallInScrapPromises()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CallInScrapPromises(void);



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

#endif /* __SCRAP__ */

