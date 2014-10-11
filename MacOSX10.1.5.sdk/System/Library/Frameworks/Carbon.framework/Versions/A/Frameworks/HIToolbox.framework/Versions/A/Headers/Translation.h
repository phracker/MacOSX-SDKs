/*
     File:       HIToolbox/Translation.h
 
     Contains:   Translation Manager (Macintosh Easy Open) Interfaces.
 
     Version:    Technology: Macintosh Easy Open 1.1
                 Release:    HIToolbox-79.9~1
 
     Copyright:  © 1991-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TRANSLATION__
#define __TRANSLATION__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __COMPONENTS__
#include <CarbonCore/Components.h>
#endif

#ifndef __TRANSLATIONEXTENSIONS__
#include <HIToolbox/TranslationExtensions.h>
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

/* enumerated types on how a document can be opened*/
typedef short                           DocOpenMethod;
enum {
  domCannot                     = 0,
  domNative                     = 1,
  domTranslateFirst             = 2,
  domWildcard                   = 3
};

/* 0L terminated array of OSTypes, or FileTypes*/
typedef OSType                          TypesBlock[64];
typedef OSType *                        TypesBlockPtr;
/* Progress dialog resource ID*/
enum {
  kTranslationScrapProgressDialogID = -16555
};

/* block of data that describes how to translate*/
struct FileTranslationSpec {
  OSType              componentSignature;
  const void *        translationSystemInfo;
  FileTypeSpec        src;
  FileTypeSpec        dst;
};
typedef struct FileTranslationSpec      FileTranslationSpec;
typedef FileTranslationSpec *           FileTranslationSpecArrayPtr;
typedef FileTranslationSpecArrayPtr *   FileTranslationSpecArrayHandle;

/*****************************************************************************************
* 
*   GetFileTypesThatAppCanNativelyOpen
* 
*  This routine returns a list of all FileTypes that an application can open by itself
* 
*  Enter:   appVRefNumHint      volume where application resides (can be wrong, and if is, will be used as a starting point)
*           appSignature        signature (creator) of application
*           nativeTypes         pointer to a buffer to be filled with up to 64 FileTypes
* 
*  Exit:    nativeTypes         zero terminated array of FileTypes that can be opened by app
*/
/*
 *  GetFileTypesThatAppCanNativelyOpen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
GetFileTypesThatAppCanNativelyOpen(
  short       appVRefNumHint,
  OSType      appSignature,
  FileType *  nativeTypes);


/*****************************************************************************************
* 
*  ExtendFileTypeList
* 
*  This routine makes a new list of file types that can be translated into a type in the given list
*  Used by StandardFile
* 
*  Enter:   originalTypeList        pointer to list of file types that can be opened
*           numberOriginalTypes     number of file types in orgTypeList
*           extendedTypeList        pointer to a buffer to be filled with file types
*           numberExtendedTypes     max number of file types that can be put in extendedTypeList
* 
*  Exit:    extendedTypeList        buffer filled in with file types that can be translated
*           numberExtendedTypes     number of file types put in extendedTypeList
*/
/*
 *  ExtendFileTypeList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
ExtendFileTypeList(
  const FileType *  originalTypeList,
  short             numberOriginalTypes,
  FileType *        extendedTypeList,
  short *           numberExtendedTypes);



/*****************************************************************************************
* 
* 
*  This routine checks if a file can be opened by a particular application.
*  If so, it returns if it needs to be translated first, and if so then how.
*  The FileTypes that the app can open are specified by nativelyOpenableTypes,
*  or if it is NULL, GetFileTypesThatAppCanNativelyOpen is called.
* 
*  Enter:   targetDocument      document to check if it can be opened
*           appVRefNumHint      vRefNum of application to open doc ( can be wrong, and if is, will be used as a starting point)
*           appSignature        signature (creator) of application to open doc
*           nativeTypes         zero terminated list of FileTypes app can open natively, or NULL to use default list
*           onlyNative          whether to consider if document can be translated before opening
*           howToOpen           pointer to buffer in which to put how the document can be opened
*           howToTranslate      pointer to buffer in which to put a FileTranslationSpec record
* 
*  Exit:    howToOpen           whether file needs to be translated to be read
*           howToTranslate      if file can be translated, buffer filled in with how to translate
*           returns             noErr, noPrefAppErr
*/
/*
 *  CanDocBeOpened()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
CanDocBeOpened(
  const FSSpec *         targetDocument,
  short                  appVRefNumHint,
  OSType                 appSignature,
  const FileType *       nativeTypes,
  Boolean                onlyNative,
  DocOpenMethod *        howToOpen,
  FileTranslationSpec *  howToTranslate);



/*****************************************************************************************
* 
*  GetFileTranslationPaths
* 
*  This routine returns a list of all ways a translation can occure to or from a FileType.
*  The app is checked to exist.  The hint for each app is the VRefNum and DTRefNum
* 
*  Enter:   srcDoc          source file or NULL for all matches
*           dstDoc          destination FileType or 0 for all matches
*           maxResultCount
*           resultBuffer
*  Exit:    number of paths
*/
/*
 *  GetFileTranslationPaths()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern short 
GetFileTranslationPaths(
  FSSpec *                      srcDocument,
  FileType                      dstDocType,
  unsigned short                maxResultCount,
  FileTranslationSpecArrayPtr   resultBuffer);


/*****************************************************************************************
* 
*  GetPathFromTranslationDialog
* 
*  This routine, with a given document, application, and a passed typelist will display the
*  Macintosh Easy Open translation dialog allowing the user to make a choice.  The choice
*  made will be written as a preference (so the next call to CanDocBeOpened() will work).
*  The routine returns the translation path information.
* 
*  Enter:   theDocument         FSSpec to document to open
*           theApplication      FSSpec to application to open document
*           typeList            Nil terminated list of FileType's (e.g. SFTypeList-like) of types
*                               you would like the documented translated to.  Order most perferred
*                               to least.
* 
*  Exit:    howToOpen           Translation method needed to open document
*           howToTranslate      Translation specification
*           returns             Any errors that might occur.
*/
/*
 *  GetPathFromTranslationDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
GetPathFromTranslationDialog(
  const FSSpec *         theDocument,
  const FSSpec *         theApplication,
  TypesBlockPtr          typeList,
  DocOpenMethod *        howToOpen,
  FileTranslationSpec *  howToTranslate);



/*****************************************************************************************
* 
*   TranslateFile
* 
*  This routine reads a file of one format and writes it to another file in another format. 
*  The information on how to translated is generated by the routine CanDocBeOpened.
*  TranslateFile calls through to the TranslateFile Extension's DoTranslateFile routine.  
*  The destination file must not exist.  It is created by this routine.  
* 
*  Enter:   sourceDocument          input file to translate
*           destinationDocument     output file of translation
*           howToTranslate          pointer to info on how to translate
*  Exit:    returns                 noErr, badTranslationSpecErr 
*/
/*
 *  TranslateFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
TranslateFile(
  const FSSpec *               sourceDocument,
  const FSSpec *               destinationDocument,
  const FileTranslationSpec *  howToTranslate);


/*****************************************************************************************
* 
*   GetDocumentKindString
* 
*  This routine returns the string the Finder should show for the "kind" of a document
*  in the GetInfo window and in the kind column of a list view.  
* 
*  Enter:   docVRefNum      The volume containing the document
*           docType         The catInfo.fdType of the document
*           docCreator      The catInfo.fdCreator of the document
*           kindString      pointer to where to return the string
* 
*  Exit:    kindString      pascal string.  Ex: "\pSurfCalc spreadsheet"
*           returns         noErr, or afpItemNoFound if kind could not be determined
*/
/*
 *  GetDocumentKindString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
GetDocumentKindString(
  short    docVRefNum,
  OSType   docType,
  OSType   docCreator,
  Str63    kindString);


/*****************************************************************************************
* 
*  GetTranslationExtensionName
* 
*  This routine returns the translation system name from a specified TranslationSpec
* 
*  Enter:   translationMethod   The translation path to get the translation name from
* 
*  Exit:    extensionName       The name of the translation system
*           returns             Any errors that might occur
*/
/*
 *  GetTranslationExtensionName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
GetTranslationExtensionName(
  const FileTranslationSpec *  translationMethod,
  Str31                        extensionName);



/*****************************************************************************************
* 
*  GetScrapDataProcPtr
* 
*  This is a prototype for the function you must supply to TranslateScrap. It is called to 
*  get the data to be translated.  The first call TranslateScrap will make to this is to
*  ask for the 'fmts' data.  That is a special.   You should resize and fill in the handle
*  with a list all the formats that you have available to be translated, and the length of each.
*  (See I.M. VI 4-23 for details of 'fmts').  It will then be called again asking for one of  
*  the formats that 'fmts' list said was available.
* 
*  Enter:   requestedFormat         Format of data that TranslateScrap needs.
*           dataH                   Handle in which to put the requested data
*           srcDataGetterRefCon     Extra parameter for you passed to TranslateScrap
*           
*  Exit:    dataH                   Handle is resized and filled with data in requested format
*/
typedef CALLBACK_API( OSErr , GetScrapDataProcPtr )(ScrapType requestedFormat, Handle dataH, void *srcDataGetterRefCon);
typedef STACK_UPP_TYPE(GetScrapDataProcPtr)                     GetScrapDataUPP;
/*
 *  NewGetScrapDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern GetScrapDataUPP
NewGetScrapDataUPP(GetScrapDataProcPtr userRoutine);

/*
 *  DisposeGetScrapDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeGetScrapDataUPP(GetScrapDataUPP userUPP);

/*
 *  InvokeGetScrapDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeGetScrapDataUPP(
  ScrapType        requestedFormat,
  Handle           dataH,
  void *           srcDataGetterRefCon,
  GetScrapDataUPP  userUPP);

typedef GetScrapDataUPP                 GetScrapData;
/*****************************************************************************************
* 
*  TranslateScrap
* 
*  This routine resizes the destination handle and fills it with data of the requested format.
*  The data is generated by translated one or more source formats of data supplied by
*  the procedure srcDataGetter.  
*  This routine is automatically called by GetScrap and ReadEdition.  You only need to call
*  this if you need to translated scrap style data, but are not using the ScrapMgr or EditionMgr.
* 
*  Enter:   sourceDataGetter            Pointer to routine that can get src data
*           sourceDataGetterRefCon      Extra parameter for dataGetter
*           destinationFormat           Format of data desired
*           destinationData             Handle in which to store translated data
*           
*  Exit:    dstData                     Handle is resized and filled with data in requested format
*/
/*
 *  TranslateScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Translation 1.0 and later
 */
extern OSErr 
TranslateScrap(
  GetScrapDataUPP   sourceDataGetter,
  void *            sourceDataGetterRefCon,
  ScrapType         destinationFormat,
  Handle            destinationData,
  short             progressDialogID);





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

#endif /* __TRANSLATION__ */

