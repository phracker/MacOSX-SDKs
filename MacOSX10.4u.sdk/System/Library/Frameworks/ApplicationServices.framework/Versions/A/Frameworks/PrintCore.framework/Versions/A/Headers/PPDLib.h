/*
     File Name:  PPDLib.h

     Contains:   Deprecated PPDLib Interfaces.  Use routines in libcups instead.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 2001-2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PPDLIB__
#define __PPDLIB__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif

#ifndef __PMTICKET__
#include <PrintCore/PMTicket.h>
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

/*** Constants ***/

#define		kDoManual		4051

enum {
	ppdErrForbidden = -2,
	ppdErrNotFound = -1
};

/*	The following constant, 'kPPDInvalidIndex' is returned from ppdGetMainIndex()
	and ppdGetOptionIndex() when a PPD string has no index. This means
	that the string does not appear in the PPD.
*/

#define kPPDInvalidIndex	0

/*** Variable Types ***/

/*	Index types.
 *	 Each option keyword and each main keyword is given an index value when
 *	 it is recognized. Some have fixed values, as defined in resources.
 *	 Index values are always >=1. 0 indicates no index (or not found).
 *	 The different index types are because the strings are stored in different tables.
 */

typedef short	Mindex;		/* main keyword index */
typedef short	Oindex;		/* option keyword index */
typedef short	Tindex;		/* translation string index */
typedef short	Pindex;		/* invocation string (Postscript) index */


/*	UI constraint structure */
struct UIConstraint {
	Mindex			mainKeyIndex;
	Oindex			optionKeyIndex;
	Mindex			invalMainKeyIndex;
	Oindex			invalOptionKeyIndex;
};
typedef struct UIConstraint UIConstraint, *UIConstraintP;

struct UIConstraintList {
	short			numConstraints;
	UIConstraint	constraint[1];
};
typedef struct UIConstraintList UIConstraintList, *UIConstraintListP, **UIConstraintListH;

typedef struct{
	Str255 msg;			// The error that occurred.
	Str255 file;		// The file containing the error.
	long line;			// The line containing the error.
}PPDParseErr;


typedef struct PPDContextViel *PPDContext;

struct xUIHeader {						/* The primary structure for most UI keys */
#define kUIHeaderVersion (1)
	long		version;				/* in/out */
	Mindex		mainKeyIndex;			/* out: main key */
	Tindex		mainKeyTranslation;		/* out: translation for group */
	Oindex		groupKeyIndex;			/* out: group identifier, if grouped */
	Pindex		queryInvocation;		/* out: Query invocation code */
	Oindex		defaultOption;			/* out: OptionKeyIndex of default option */
	Oindex		pickConstraint;			/* out: OptionKeyIndex: PickOne, PickMany, Boolean */
	short		numOptions;				/* out: number of options */
};
typedef struct xUIHeader xUIHeader, *xUIHeaderP;

struct InvocationLocator {
	Fixed		order;
	Oindex		orderSection;			/* OptionKeyIndex: ExitServer, Prolog, DocumentSetup, PageSetup, AnySetup */
	short		invocationType;			/* 0:Pindex, -1:Oindex, >0:fileindex */
	long		invocationLoc;			/* index value or file offset */
	long		invocationSize;			/* number of bytes in invocation string */
};
typedef struct InvocationLocator InvocationLocator;

struct xUIOption {					/* Structure of one option of a UI */
#define kUIOptionVersion (1)
	long		version;				/* in/out */
	Oindex		optionKeyIndex;			/* out: fully qualified option */
	Tindex		optionTranslation;		/* out: translation for option */
	Boolean		forbidden;				/* out: Constraint handling */
	Boolean		chosen;					/* out: true if option is chosen */
	InvocationLocator		invocation;	/* out: identifies invocation code */
};
typedef struct xUIOption xUIOption, *xUIOptionP;

typedef OSErr (*recordOptionPairProc)(PPDContext ppdContext, Mindex mainKey, Oindex optionKey, long refCon);

struct PPDFileSpec {
	FSSpec			fs;
	short			refNum;
	long			lastModDate;
	Str63			volumeName;			/* Poor Man's alias (used with System 6) */
	AliasHandle		alias;
};
typedef struct PPDFileSpec PPDFileSpec;

struct StrList {
	short			numStrings;
	unsigned char	str[1];			/* start of first string in the list */
};
typedef struct StrList StrList, *StrListPtr, **StrListHdl;

struct PPDPrinterDesc {
	StringPtr product;
	StringPtr version;
	StringPtr revision;
        Boolean matchModel;
};
typedef struct PPDPrinterDesc PPDPrinterDesc;

typedef struct {
	unsigned short count;
	FSSpec file[1];
} PPDMatch, *PPDMatchPtr, **PPDMatchHandle;

/*	The invocation for the *ImageableArea keyword is returned as an LAxis
	structure rather than as the text from the PPD. Similarly, the invocation
	for *PaperDimension is returned as a LPaper structure.
*/
typedef struct LAxis{
	Fixed llx;
	Fixed lly;
	Fixed urx;
	Fixed ury;
}LAxis;

typedef struct LPaper{
	Fixed width;
	Fixed height;
}LPaper;

/*	'PPDGetGenericPPDNameProc' is a function pointer suitable to call
	ppdGetGenericPPDName() through.
*/
	
typedef OSErr (*PPDGetGenericPPDNameProc)(StringPtr genericPPDName) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
typedef OSErr (*InfoButtonProcPtr)(void *infoRefConP) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;;
typedef OSStatus (*WebSearchDlgFilter)(EventRecord *event, void *refcon) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;;
typedef OSStatus (*WebSearchProgressProc)(ConstStr255Param status, int percentDone, void *refcon) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;;

/*	A PPDEventFilter function pointer can be passed to ppdNavSelectFile() so that the caller
	can receive update, idle, and other useful events while the Navigation Choose file is
	being displayed.
*/
typedef OSStatus (*PPDEventFilter)(EventRecord *event, void *filterData) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;;

/*** Prototypes ***/

#if PRAGMA_IMPORT_SUPPORTED
#pragma import on
#endif


OSErr ppdParseFile (const FSSpec *ppdFileSpec, short compiledRef, short compiledResFRef, PPDParseErr *errInfoP) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Parse a PPD file, and all its includes.
	FSSpecPtr will be closed upon exit.
	The PPD is parsed into the open file with the file reference 'compiledRef'.
	If compiledResFRef is not -1, the resource fork of the ppd file is copied into it.
	If 'errInfoP' is not NULL, then any error information is returned in
	*'errInfoP'.
*/

OSErr ppdParseHandle (Handle ppdHandle, short compiledRef, short compiledResFRef, PPDParseErr *errInfoP) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Parse a PPD file, and all its includes.
	Parse from a resource Handle.  We will Release the handle when we are through.
	The PPD is parsed into the open file with the file reference 'compiledRef'.
	If compiledResFRef is not -1, the resource fork of the ppd file is copied into it.
	If 'errInfoP' is not NULL, then any error information is returned in
	*'errInfoP'.
*/

// removed ppdOpen macro

OSErr ppdOpenContext(short compiledPPDRef, PPDContext *ppdContext) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Prepare to reference the compiled PPD information in the
	open file with reference 'compiledPPDRef'. If this function
	doesn't return an error, then *'ppdContext' is filled in
	with a value that can be used in other ppd calls.
*/

void ppdCloseContext(PPDContext ppdContext);
/*	Free up the memory used to access the PPD file
	referenced by 'ppdContext' (returned from ppdOpen())
	After this call, 'ppdContext' is no longer valid.
*/

OSStatus PPDAddFeatureEntries(PMTicketRef jobTicket, CFMutableDictionaryRef psContextDictRef) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 Obsolete. Returns kPMNotImplemented.
*/

OSStatus PPDAddFeatureEntriesFromPPDContext(PMTicketRef jobTicket, PPDContext ppdContext, 
							CFMutableDictionaryRef psContextDictRef) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
    Obsolete. Returns kPMNotImplemented.
*/

OSStatus ppdGetCompiledPPDData(PMTicketRef printerInfoTicket, CFDataRef *ppdData) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
From the printerInfoTicket passed in, get the parsed PPD data. Upon return
ppdData contains a reference to the PPD data.
*/

//BGMARK
OSStatus ppdCreateInstallableOptionsData(FSSpec ppdSpec, char ** data, CFMutableArrayRef optionKeyWords) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

OSStatus ppdOpenCompiledPPDFromTicket(PMTicketRef printerInfoTicket, PPDContext *ppdContextP, FSSpec *tempFSSpecP) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
From the printerInfoTicket passed in, create a temp file containing the parsed PPD data and open that
file, returning in *ppdContextP the PPDContext corresponding to the open, parsed PPD file. Upon return
*tempFSSpecP contains the FSSpec of the temp file which needs to be passed in to ppdCloseCompiledPPDFromTicket
in order to delete that temp file.
*/

OSStatus ppdCloseCompiledPPDFromTicket(PPDContext ppdContext, FSSpec *tempPPDFileSpecP) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
Call ppdClose for the ppdContext and delete the file corresponding to *tempPPDFileSpecP.
*/


Mindex ppdGetMainIndex(PPDContext ppdContext, const StringPtr keyword) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Given Pascal string reprentation of a PPD main keyword, 'keyword',
	this routine returns a main key index (Mindex) that can be passed to other PPD
	routines. A Mindex is an integer representation of a main keyword.
	The Mindex for a given keyword is not constant across PPDs; in other words,
	the Mindex to keyword mapping is not defined across compiled PPDs.
*/

Oindex ppdGetOptionIndex(PPDContext ppdContext, const StringPtr keyword) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Given a Pascal string reprentation of a PPD option keyword, 'keyword'
	this routine returns an option key index (Oindex) that can be passed to other PPD
	routines. An Oindex is an integer representation of an option keyword.
	The Oindex for a given keyword is not constant across PPDs; in other words,
	the Oindex to keyword mapping is not defined across compiled PPDs.
*/

short ppdGetUIKeyType(PPDContext ppdContext, Mindex mainkey) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Once a Mindex has been found for a main keyword, the existence of the keyword
	in a compiled PPD can be checked with ppdGetUIkeyType (). If the keyword exists,
	ppdGetUIkeyType() will also indicate whether the keyword is a UI type keyword or not.
	UI keywords in the PPD file have the form:
		mainkey optionkey: "some PS code"
	If the keyword does not exist then 0 is returned. If the keyword exists and
	is a UI keyword, then 1 is returned. If the keyword exists but is not a UI
	key, then -1 is returned.
*/

Boolean ppdGetUIHeader(PPDContext ppdContext, Mindex mainkey, xUIHeaderP p) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Once a Mindex for a UI keyword has been found, ppdGetUIHeader() can be used
	to get information about the UI main keyword. The structure pointed to by the
	UIHeaderP parameter will be filled in with information about the main keywords
	group, its query code, its default option key, and the number of options.
*/

Boolean ppdGetUIOption(PPDContext ppdContext, Mindex mainkey, Oindex optionkey, xUIOptionP p) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Given a Mindex and Oindex pair, a caller can use the function ppdGetUIOption()
	to get information about the pair. ppdGetUIOption() provides information about
	a main keyword, option keyword pair¹s translation string, constraints, and
	any invocation code.
*/

short ppdCountUIHeaders(PPDContext ppdContext) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Used with ppdGetIndUIHeader(), ppdCountUIHeaders () allows a caller to
	enumerate the list of UI main keywords in a compiled PPD.
*/

Boolean ppdGetIndUIHeader(PPDContext ppdContext, short index, xUIHeaderP p) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Once the number of UI headers has been found using  ppdCountUIHeaders (),
	the caller uses ppdGetIndUIHeader() to enumerate the UI main keywords.
*/

short ppdCountUIOptions(PPDContext ppdContext, Mindex mainkey) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Used with the function ppdGetIndUIOption(), ppdCountUIOptions() can be
	used to enumerate the option keywords associated with a UI main keyword.
	ppdCountUIOptions() returns the number of option keywords associated with
	a UI main keyword.
*/

Boolean ppdGetIndUIOption(PPDContext ppdContext, Mindex mainKey, short index, xUIOptionP p) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	After the caller uses ppdCountUIOptions() to find the number of option
	keywords for a given main keyword, ppdGetIndUIOption() can be used to
	enumerate the options.
*/

OSErr ppdSetSelection(PPDContext ppdContext, Mindex mainKey, Oindex optionKey, Boolean setOrClear) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	The PPD code can help the caller track user selections and 
	certain selections are constrained by the PPD or not. The ppdSetSelection()
	function can be used by a caller to indicate that a user has selected or deselected
	a main keyword, option keyword pair.
*/

UIConstraintListH getUIConstraintListH(PPDContext ppdContext) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Returns the UIConstraintListH so that the user can determine whether
	certain selections are constrained by the PPD or not by searching the list.
*/

void ppdClearOptions(PPDContext ppdContext, Mindex mainKey) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	When running a user interface, it is often useful to clear a users selections
	for a given main keyword. The function ppdClearOptions() does this.
*/

void ppdSetDefaultOptions(PPDContext ppdContext, Oindex groupIndex) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	To set all the main keyword, option keyword UI pairs of a particular
	group to their default settings use ppdSetDefaultOptions().
	This function is most useful when setting the installable options
	group of key pairs to their default settings.
*/

OSErr ppdGetAllOptions(PPDContext ppdContext, recordOptionPairProc addPair, long refCon) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	When a user has finished running a user interface built upon the PPD code,
	the caller may desire to retrieve the user¹s final PPD selections.
	The function ppdGetAllOptions() will enumerate through the main keyword,
	option keyword selections of the user, and for each pair the function addPair
	will be invoked.
*/

Boolean ppdGetMainString(PPDContext ppdContext, Mindex mainkey, StringPtr buffer) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	In order to get a string representation of a Mindex, use the function
	ppdGetMainString (). ppdGetMainString () is the inverse function of
	ppdMainIndexGet().
*/

Boolean ppdGetMainAlias(PPDContext ppdContext, Mindex mainkey, StringPtr buffer) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Similar to ppdGetMainString () except that it returns the translation string
	for a main keyword. If the keyword has no translation string then the Pascal
	string representation of the main keyword is returned.Use this function to
	build user interface strings.
*/

Boolean ppdGetOptionString(PPDContext ppdContext, Oindex optionkey, StringPtr buffer) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	In order to get a string representation of an Oindex, use the function
	ppdGetOptionString (). ppdGetOptionString () is the inverse function
	of ppdOptionIndexGet().
*/

Boolean ppdGetOptionAlias(PPDContext ppdContext, Mindex mainkey, Oindex optionkey, StringPtr buffer) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	ppdGetOptionAlias() is similar to ppdGetOptionString () except that it
	returns the translation string for an option keyword. If the keyword
	has no translation string then the Pascal string representation of
	the option keyword is returned.Use this function to build user interface strings.
*/

Boolean ppdGetGroupAlias(PPDContext ppdContext, Oindex groupKeyIndex, Byte *buf) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Returns the translation string for a group keyword. If the keyword
	has no translation string then the Pascal string representation of
	the group keyword is returned. Use this function to build user interface strings.
*/

OSErr ppdGetInvocationLocator(PPDContext ppdContext, Mindex mainkey, Oindex optionkey, InvocationLocator *invocation) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	At some point after a user has selected a main key, option key pair, the
	caller may need to determine the PostScript invocation string associated with
	the user¹s choice. The function ppdGetInvocationLocator() provides information
	about the PostScript invocation string that can be used to call ppdGetInvocationString(),
	ppdGetInvocation(), ppdGetInvocationStruct(), or ppdGetInvocationFile().
*/

OSErr ppdGetInvocation(PPDContext ppdContext, InvocationLocator *invocation, long *offset, long *count, Ptr buffer) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	ppdGetInvocation() is the most general routine for retrieving the PostScript
	invocation string. It can be used to retrieve invocations that are very large.
	ppdGetInvocation() fills a caller supplied buffer with as much of the invocation
	as possible. The user can make successive calls to ppdGetInvocation() to get
	the rest of the data if it does not fit in the caller¹s buffer.
*/

OSErr ppdGetInvocationString(PPDContext ppdContext, Mindex mindex, Oindex oindex, StringPtr data, short maxLength) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	ppdGetInvocationString() will directly return the invocation string from a main key,
	option key pair as a Pascal style string. Because ppdGetInvocationString() is
	built upon ppdGetInvocation(), the same conversions as noted in the description
	of ppdGetInvocation() are performed here.
*/

Boolean ppdCheckConstraints(PPDContext ppdContext, Mindex *mainkey1, Oindex *optkey1, Mindex *mainkey2, Oindex *optkey2) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	ppdCheckConstraints() goes through its list of selected items
	and returns the first pair chosen that is illegal.
*/

int ppdCheckDates(PPDContext ppdContext) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Check mod dates on all PPD files that ppdContext is made up from.
	The purpose is to flag to the client that the PPD needs to be reparsed.
	Return:
		-1	if anyone is out of date.
		0	if resource is used (the Generic PPD)
		1	if all files are OK
	
	If ppdCheckDates() returns 0 the client has to make sure that the parsed
	Generic PPD is the parsed version of the current driver's Generic PPD.
*/

OSStatus setInstallableOptions(PPDContext ppdContext, PMTicketRef ticket) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Overrides any matching default constraints in PPDContext with printer 
        installed restraints.
*/

/* The following calls are not yet documented in the PPD library specs.
*/

OSErr ppdGetInvocationStruct(PPDContext ppdContext, Mindex mindex, Oindex oindex, void *data, short size) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Specialized version of GetInvocationString for returning a struct
*/

OSErr ppdGetInvocationFile(PPDContext ppdContext, short invocationType, PPDFileSpec *theFile) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Return a File Spec for a remote invocation file.
	Returns fnfErr if we can't find the file data or if the file data block
	is zero, indicating an unused file.
*/

Boolean ppdApplyConstraints(PPDContext ppdContext) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Check UI constraints and mark the UI entries to reflect the constraints.
	Returns true if some constraint is VIOLATED, false if everything is OK
*/

StrList** ppdGetMessageTranslateList(PPDContext ppdContext) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Get a Handle to the status and error message translations
*/

OSErr ppdGetFolder(FSSpec *ppdFolder) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	This routine fills *'ppdFolder' with the volume id and directory id
	of the PPD folder. 'ppdFolder->name' is not changed by this function.
	To open a PPD file, call this function so that it fills in the
	vRefNum and parID fields of the FSSpec and then put the PPD file's
	name into the name field.
*/

OSErr ppdGetParseFolder(FSSpecPtr parseFolder) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Fill in the FSSpec pointed to by 'parseFolder' with
	the 'vRefNum' and 'parID' of the parsed PPD folder.
	The client can place a parsed PPD file name into the
	FSSpec's 'name' field and then use the File Manager's
	Open call's to open a parsed PPD. Note that *parseFolder'
	is not the FSSpec of the parsed PPD folder.
*/

OSErr ppdFindFile(FSSpec *base, StringPtr name, Boolean useBase) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Find a PPD file. if 'useBase' is true, start searching in the directory
	referenced by *'base'.  If 'useBase' is false, or the ppd file is not
	found in the specified folder, search in other locations as follows until
	the ppd file is found.
	Search in the Printer Descriptions folder in the Extensions folder
	if the folder exists, then search directly in the Extensions folder.  Next
	search in the Printer Descriptions folder in the System folder if the
	folder exists, then search directly in the System folder.
*/

OSErr ppdMatchPrinter(PPDPrinterDesc *desc, PPDMatchHandle *matchesP) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	This routine takes information about a given printer and attempts
	to find one or more PPDs that are appropriate for the described device.
	*'desc' is a pointer to a structure that contains pointers to three
	Pascal strings.  These strings are the product name, the version and
	the revision of a printer.  If one or more of these strings are NULL,
	then htat field is assumed to be a wildcard and it will match any given
	This routine places into *'matchesP' a handle to a list of FSSPec's
	that satisfy the conditions set by 'desc'.  The list begins with
	a count of the number of matching FSSpecs. It is the caller's
	responsibility to free this handle when it is no longer needed. If 
    matchModel is true then the caller wants to match the model name of the
    printer in the place of the product name.
*/


OSErr ppdGetGenericPPDName(Str63 genericPPDName) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	This routine places the suggested name for the generic PPD into
	the buffer pointed to by 'genericPPDName'. New for 8.4.1.
*/

OSStatus ppdOpenAndParsePPDAutoSetup(Collection prInfo, 
									 PPDContext *ppdContextP, 
									 short *resFRefP, 
									 PPDParseErr *errInfoP, 
									 OSStatus *lastErr) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*	Same as ppdOpenAndParsePPD with the addition of lastErr to track the 
	ppd error (if any) generated prior to falling back to the generic ppd. 
	This will allow the autosetup code to notify the user that the selected
	ppd failed to parse while still falling back to the generic ppd.

*/

#if PRAGMA_IMPORT_SUPPORTED
#pragma import off
#endif


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

#endif	/* __PPDLIB__ */
