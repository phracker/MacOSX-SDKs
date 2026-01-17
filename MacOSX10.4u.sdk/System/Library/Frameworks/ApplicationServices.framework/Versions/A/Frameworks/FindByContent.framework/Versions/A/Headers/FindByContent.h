/*
     File:       FindByContent/FindByContent.h
 
     Contains:   Public search interface for the Find by Content shared library
 
     Version:    FindByContent-110~1145
 
     Copyright:  © 1997-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FINDBYCONTENT__
#define __FINDBYCONTENT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k


/*
   ***************************************************************************
   Language constants used with FBCIndexItemsInLanguages: these numbers are bits
   in a 64-bit array that consists of two UInt32 words.  In the current implementation
   the low word is always 0, so values for the high word are given.  If both UInt32
   words are 0, the default value of kDefaultLanguagesHighWord is used.
   ***************************************************************************
*/

/* These are the new names for the language constants*/
enum {
                                        /* languages that use the Roman character mapping*/
  kFBCenglishHighWord           = (long)0x80000000,
  kFBCdutchHighWord             = 0x40000000, /* also Afrikaans*/
  kFBCgermanHighWord            = 0x20000000,
  kFBCswedishHighWord           = 0x10000000, /* also Norwegian*/
  kFBCdanishHighWord            = 0x08000000,
  kFBCspanishHighWord           = 0x04000000, /* also Catalan*/
  kFBCportugueseHighWord        = 0x02000000,
  kFBCitalianHighWord           = 0x01000000,
  kFBCfrenchHighWord            = 0x00800000,
  kFBCromanHighWord             = 0x00400000, /* other languages using Roman alphabet*/
                                        /* Languages that use other mappings*/
  kFBCicelandicHighWord         = 0x00200000, /* also Faroese*/
  kFBChebrewHighWord            = 0x00100000, /* also Yiddish*/
  kFBCarabicHighWord            = 0x00080000, /* also Farsi, Urdu*/
  kFBCcenteuroHighWord          = 0x00040000, /* Central European languages not using Cyrillic*/
  kFBCcroatianHighWord          = 0x00020000,
  kFBCturkishHighWord           = 0x00010000,
  kFBCromanianHighWord          = 0x00008000,
  kFBCgreekHighWord             = 0x00004000,
  kFBCcyrillicHighWord          = 0x00002000, /* all languages using Cyrillic*/
  kFBCdevanagariHighWord        = 0x00001000,
  kFBCgujuratiHighWord          = 0x00000800,
  kFBCgurmukhiHighWord          = 0x00000400,
  kFBCjapaneseHighWord          = 0x00000200,
  kFBCkoreanHighWord            = 0x00000100,
  kFBCdefaultLanguagesHighWord  = (long)0xFF800000 /* sum of first 9*/
};

/*A new error, needs to be moved to MacErrors.h*/
enum {
  kFBCnotAllFoldersSearchable   = -30533
};


/*
   ***************************************************************************
   Phase values
   These values are passed to the client's callback function to indicate what
   the FBC code is doing.  They are meaningless in OS X.
   ***************************************************************************
*/
enum {
                                        /* indexing phases*/
  kFBCphIndexing                = 0,
  kFBCphFlushing                = 1,
  kFBCphMerging                 = 2,
  kFBCphMakingIndexAccessor     = 3,
  kFBCphCompacting              = 4,
  kFBCphIndexWaiting            = 5,    /* access phases*/
  kFBCphSearching               = 6,
  kFBCphMakingAccessAccessor    = 7,
  kFBCphAccessWaiting           = 8,    /* summarization*/
  kFBCphSummarizing             = 9,    /* indexing or access*/
  kFBCphIdle                    = 10,
  kFBCphCanceling               = 11
};

enum {
  kFBCsummarizationFailed       = -30533
};


/*
   ***************************************************************************
   Pointer types
   These point to memory allocated by the FBC shared library, and must be deallocated
   by calls that are defined below.
   ***************************************************************************
*/

/* A collection of state information for searching*/
typedef struct OpaqueFBCSearchSession*  FBCSearchSession;
/* An object containing summary information, from which summary text can be obtained*/
typedef struct OpaqueFBCSummaryRef*     FBCSummaryRef;
/* An ordinary C string (used for hit/doc terms)*/
typedef char *                          FBCWordItem;
/* An array of WordItems*/
typedef FBCWordItem *                   FBCWordList;
/*
   ***************************************************************************
   Callback function type for progress reporting and cancelation during
   searching and indexing.  The client's callback function should call
   WaitNextEvent; a "sleep" value of 1 is suggested.  If the callback function
   wants to cancel the current operation (indexing, search, or doc-terms
   retrieval) it should return true.
   ***************************************************************************
*/

typedef CALLBACK_API_C( Boolean , FBCCallbackProcPtr )(UInt16 phase, float percentDone, void *data);
typedef STACK_UPP_TYPE(FBCCallbackProcPtr)                      FBCCallbackUPP;
/*
 *  NewFBCCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern FBCCallbackUPP
NewFBCCallbackUPP(FBCCallbackProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeFBCCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeFBCCallbackUPP(FBCCallbackUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeFBCCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeFBCCallbackUPP(
  UInt16          phase,
  float           percentDone,
  void *          data,
  FBCCallbackUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
   ***************************************************************************
   Set the callback function for progress reporting and cancelation during
   searching and indexing.
   ***************************************************************************
*/

/*
 *  FBCSetSessionCallback()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
FBCSetSessionCallback(
  FBCSearchSession   searchSession,
  FBCCallbackUPP     fn,
  void *             data)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, use FBCSetSessionCallback*/
/*
 *  FBCSetCallback()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern void 
FBCSetCallback(
  FBCCallbackUPP   fn,
  void *           data)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Callback function type for hit testing during searching
   ***************************************************************************
*/

typedef CALLBACK_API_C( Boolean , FBCHitTestProcPtr )(const FSRef *theFile, void *data);
typedef STACK_UPP_TYPE(FBCHitTestProcPtr)                       FBCHitTestUPP;
/*
 *  NewFBCHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern FBCHitTestUPP
NewFBCHitTestUPP(FBCHitTestProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeFBCHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeFBCHitTestUPP(FBCHitTestUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeFBCHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeFBCHitTestUPP(
  const FSRef *  theFile,
  void *         data,
  FBCHitTestUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
   ***************************************************************************
   Set the hit-testing function for searches.
   ***************************************************************************
*/
/*
 *  FBCSetSessionHitTest()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern void 
FBCSetSessionHitTest(
  FBCSearchSession   theSession,
  FBCHitTestUPP      fn,
  void *             data)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Set the amount of heap space to reserve for the client's use when FBC
   allocates memory.
   ***************************************************************************
*/

/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCSetHeapReservation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern void 
FBCSetHeapReservation(UInt32 bytes)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Find out whether a volume is indexed.
   ***************************************************************************
*/

/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCVolumeIsIndexed()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern Boolean 
FBCVolumeIsIndexed(SInt16 theVRefNum)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Find out whether a volume is remote.
   ***************************************************************************
*/

/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCVolumeIsRemote()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern Boolean 
FBCVolumeIsRemote(SInt16 theVRefNum)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Find out the date & time of an index's last completed  update.
   ***************************************************************************
*/

/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCVolumeIndexTimeStamp()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCVolumeIndexTimeStamp(
  SInt16    theVRefNum,
  UInt32 *  timeStamp)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Find out the physical size of an index.
   ***************************************************************************
*/

/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCVolumeIndexPhysicalSize()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCVolumeIndexPhysicalSize(
  SInt16    theVRefNum,
  UInt32 *  size)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Create & configure a search session
   ***************************************************************************
*/

/*
 *  FBCCreateSearchSession()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCCreateSearchSession(FBCSearchSession * searchSession)      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCCloneSearchSession()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCCloneSearchSession(
  FBCSearchSession    original,
  FBCSearchSession *  clone)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCAddAllVolumesToSession()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCAddAllVolumesToSession(
  FBCSearchSession   theSession,
  Boolean            includeRemote)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCSetSessionVolumes()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCSetSessionVolumes(
  FBCSearchSession   theSession,
  const SInt16       vRefNums[],
  UInt16             numVolumes)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCAddVolumeToSession()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCAddVolumeToSession(
  FBCSearchSession   theSession,
  SInt16             vRefNum)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCRemoveVolumeFromSession()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCRemoveVolumeFromSession(
  FBCSearchSession   theSession,
  SInt16             vRefNum)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCGetSessionVolumeCount()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCGetSessionVolumeCount(
  FBCSearchSession   theSession,
  UInt16 *           count)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCGetSessionVolumes()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCGetSessionVolumes(
  FBCSearchSession   theSession,
  SInt16             vRefNums[],
  UInt16 *           numVolumes)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Execute a search
   ***************************************************************************
*/

/*
 *  FBCDoQuerySearch()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCDoQuerySearch(
  FBCSearchSession   theSession,
  char *             queryText,
  const FSSpec       targetDirs[],
  UInt32             numTargets,
  UInt32             maxHits,
  UInt32             maxHitWords)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCDoCFStringSearch()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FBCDoCFStringSearch(
  FBCSearchSession   theSession,
  CFStringRef        queryString,
  const FSSpec       targetDirs[],
  UInt32             numTargets,
  UInt32             maxHits,
  UInt32             maxHitWords)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCDoExampleSearch()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCDoExampleSearch(
  FBCSearchSession   theSession,
  const UInt32 *     exampleHitNums,
  UInt32             numExamples,
  const FSSpec       targetDirs[],
  UInt32             numTargets,
  UInt32             maxHits,
  UInt32             maxHitWords)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* OS X DEPRECATED, use FBCBlindExampleSearchWithCallback to be able to cancel*/
/*
 *  FBCBlindExampleSearch()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCBlindExampleSearch(
  const FSSpec        examples[],
  UInt32              numExamples,
  const FSSpec        targetDirs[],
  UInt32              numTargets,
  UInt32              maxHits,
  UInt32              maxHitWords,
  Boolean             allIndexes,
  Boolean             includeRemote,
  FBCSearchSession *  theSession)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCBlindExampleSearchWithCallback()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FBCBlindExampleSearchWithCallback(
  const FSSpec        examples[],
  UInt32              numExamples,
  const FSSpec        targetDirs[],
  UInt32              numTargets,
  UInt32              maxHits,
  UInt32              maxHitWords,
  Boolean             allIndexes,
  Boolean             includeRemote,
  FBCSearchSession *  theSession,
  FBCCallbackUPP      callback,
  void *              callbackData,
  FBCHitTestUPP       userHitTest,
  void *              userHitTestData)                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
   ***************************************************************************
   Get information about hits [wrapper for THitItem C++ API]
   ***************************************************************************
*/

/*
 *  FBCGetHitCount()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCGetHitCount(
  FBCSearchSession   theSession,
  UInt32 *           count)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCGetHitDocument()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCGetHitDocument(
  FBCSearchSession   theSession,
  UInt32             hitNumber,
  FSSpec *           theDocument)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCGetHitDocumentRef()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FBCGetHitDocumentRef(
  FBCSearchSession   theSession,
  UInt32             hitNumber,
  FSRef *            theDocument)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCGetHitScore()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCGetHitScore(
  FBCSearchSession   theSession,
  UInt32             hitNumber,
  float *            score)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
   ***************************************************************************
   Summarize text
   ***************************************************************************
*/

/*
 *  FBCSummarize()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCSummarize(
  const void *  inBuf,
  UInt32        inLength,
  void *        outBuf,
  UInt32 *      outLength,
  UInt32 *      numSentences)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCSummarizeCFString()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FBCSummarizeCFString(
  CFStringRef    inString,
  CFStringRef *  outString,
  UInt32 *       numSentences)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCGetSummaryOfCFString()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FBCGetSummaryOfCFString(
  CFStringRef      inString,
  FBCSummaryRef *  summary)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCGetSummarySentenceCount()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FBCGetSummarySentenceCount(
  FBCSummaryRef   summary,
  UInt32 *        numSentences)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCGetSummarySentences()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FBCGetSummarySentences(
  FBCSummaryRef   summary,
  CFStringRef *   outString,
  UInt32 *        numSentences,
  Boolean         paragraphs)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCDisposeSummary()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FBCDisposeSummary(FBCSummaryRef summary)                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
   ***************************************************************************
   Deallocate hit lists and search sessions
   ***************************************************************************
*/

/*
 *  FBCReleaseSessionHits()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCReleaseSessionHits(FBCSearchSession theSession)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCDestroySearchSession()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCDestroySearchSession(FBCSearchSession theSession)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   Index one or more files and/or folders
   ***************************************************************************
*/

/*      OS X DEPRECATED (will be removed from OS X exports in a future release)*/
/*
 *  FBCIndexItems()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   in FindByContent 9.0 and later
 */
extern OSErr 
FBCIndexItems(
  FSSpecArrayPtr   theItems,
  UInt32           itemCount)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FBCIndexItemsInLanguages()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FBCIndexItemsInLanguages(
  FSSpecArrayPtr   theItems,
  UInt32           itemCount,
  UInt32           languageHighBits,
  UInt32           languageLowBits)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   (OS X only) Given a folder, find the folder that contains the index file
   of the given index
   ***************************************************************************
*/

/*
 *  FBCFindIndexFileFolderForFolder()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FBCFindIndexFileFolderForFolder(
  const FSRef *  inFolder,
  FSRef *        outFolder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
   ***************************************************************************
   (OS X only) Given a folder, delete the index file that indexes it
   ***************************************************************************
*/

/*
 *  FBCDeleteIndexFileForFolder()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FBCDeleteIndexFileForFolder(const FSRef * folder)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
   ***************************************************************************
   The following are deprecated and obsolete for both OS X and OS 9
   ***************************************************************************
*/

/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCGetMatchedWords()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCGetMatchedWords(
  FBCSearchSession   theSession,
  UInt32             hitNumber,
  UInt32 *           wordCount,
  FBCWordList *      list)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCGetTopicWords()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCGetTopicWords(
  FBCSearchSession   theSession,
  UInt32             hitNumber,
  UInt32 *           wordCount,
  FBCWordList *      list)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*      OS X DEPRECATED, NO-OP (will be removed from OS X exports in a future release)*/
/*
 *  FBCDestroyWordList()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FindByContent 8.5 and later
 */
extern OSErr 
FBCDestroyWordList(
  FBCWordList   theList,
  UInt32        wordCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* These names are deprecated, use the new ones above*/
enum {
                                        /* languages that use the Roman character mapping*/
  englishHighWord               = kFBCenglishHighWord,
  dutchHighWord                 = kFBCdutchHighWord, /* also Afrikaans*/
  germanHighWord                = kFBCgermanHighWord,
  swedishHighWord               = kFBCswedishHighWord, /* also Norwegian*/
  danishHighWord                = kFBCdanishHighWord,
  spanishHighWord               = kFBCspanishHighWord, /* also Catalan*/
  portugueseHighWord            = kFBCportugueseHighWord,
  italianHighWord               = kFBCitalianHighWord,
  frenchHighWord                = kFBCfrenchHighWord,
  romanHighWord                 = kFBCromanHighWord, /* other languages using Roman alphabet*/
                                        /* Languages that use other mappings*/
  icelandicHighWord             = kFBCicelandicHighWord, /* also Faroese*/
  hebrewHighWord                = kFBChebrewHighWord, /* also Yiddish*/
  arabicHighWord                = kFBCarabicHighWord, /* also Farsi, Urdu*/
  centeuroHighWord              = kFBCcenteuroHighWord, /* Central European languages not using Cyrillic*/
  croatianHighWord              = kFBCcroatianHighWord,
  turkishHighWord               = kFBCturkishHighWord,
  romanianHighWord              = kFBCromanianHighWord,
  greekHighWord                 = kFBCgreekHighWord,
  cyrillicHighWord              = kFBCcyrillicHighWord, /* all languages using Cyrillic*/
  devanagariHighWord            = kFBCdevanagariHighWord,
  gujuratiHighWord              = kFBCgujuratiHighWord,
  gurmukhiHighWord              = kFBCgurmukhiHighWord,
  japaneseHighWord              = kFBCjapaneseHighWord,
  koreanHighWord                = kFBCkoreanHighWord,
  kDefaultLanguagesHighWord     = kFBCdefaultLanguagesHighWord /* sum of first 9*/
};


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __FINDBYCONTENT__ */

