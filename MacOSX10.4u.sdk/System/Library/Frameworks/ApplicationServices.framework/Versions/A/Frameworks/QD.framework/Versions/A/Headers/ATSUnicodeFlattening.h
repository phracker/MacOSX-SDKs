/*
     File:       QD/ATSUnicodeFlattening.h
 
     Contains:   Public interfaces for Apple Type Services for Unicode Imaging
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 2002-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSUNICODEFLATTENING__
#define __ATSUNICODEFLATTENING__

#ifndef __ATSUNICODETYPES__
#include <QD/ATSUnicodeTypes.h>
#endif


/* ---------------------------------------------------------------------------- */
/* Constants                                                                    */
/* ---------------------------------------------------------------------------- */
/*
   ATSUFlattenedDataStreamFormat is used to inform the APIs which flatten and
   unflatten style runs exactly what type of data that they should be generating
   or parsing.
*/

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef UInt32 ATSUFlattenedDataStreamFormat;
enum {
  kATSUDataStreamUnicodeStyledText = 'ustl'
};


/*
   ATSUFlattenStyleRunOptions is a bitfield list of options that can be passed
   into the ATSUFlattenStyleRunsToStream API. Currently, there are no options. 
   This is here for future expansion.
*/
typedef UInt32 ATSUFlattenStyleRunOptions;
enum {
  kATSUFlattenOptionNoOptionsMask = 0x00000000
};

/*
   ATSUUnFlattenStyleRunOptions is a bitfield list of options that can be passed
   into the ATSUUnFlattenStyleRunsToStream API. Currently, there are no options. 
   This is here for future expansion.
*/
typedef UInt32 ATSUUnFlattenStyleRunOptions;
enum {
  kATSUUnFlattenOptionNoOptionsMask = 0x00000000
};


/* ---------------------------------------------------------------------------- */
/* Data Types                                                                   */
/* ---------------------------------------------------------------------------- */

/*
   ATSUStyleRunInfo is a structure that contains an index into an array of 
   unique ATSUStyle objects as well as the length of the run that the style run 
   object covers. This structure is utilized by ATSUUnflattenStyleRunsFromStream() 
   to return the style run info to the caller. 
*/
struct ATSUStyleRunInfo {
  UniCharCount        runLength;
  ItemCount           styleObjectIndex;
};
typedef struct ATSUStyleRunInfo         ATSUStyleRunInfo;
/* ---------------------------------------------------------------------------- */
/* 'ustl' structure data structures and definitions                             */
/* ---------------------------------------------------------------------------- */
/*
   The 'ustl' data structure follows this format:
   1. Main Data Structure Block Header
   2. Flattened Text Layout Data
   3. Flattened Style Run Data
   4. Flattened Style Data
   Per the 'ustl' spec, these structures should maintain four-byte alignment. 
   For things that are variable width (such as font names), padding bytes must
   be added to ensure that this alignment is always kept.
*/

/*
   structure versioning - the version of the 'ustl' that the ATSUI parsing
   and generating functions will handle is version 2 or greater. Earlier
   versions were not completly specified and have been obsoleted.
*/
enum {
  kATSFlatDataUstlVersion0      = 0,
  kATSFlatDataUstlVersion1      = 1,
  kATSFlatDataUstlVersion2      = 2,
  kATSFlatDataUstlCurrentVersion = kATSFlatDataUstlVersion2
};

/* ------------------ */
/* Block 1 Structures */
/* ------------------ */

/*
   This is the main data structure block header. It describes the rest
   of the data and how it is structured.
*/
struct ATSFlatDataMainHeaderBlock {

                                              /* the 'ustl' version number. This needs to be the first item in the*/
                                              /* data block do as not to confuse parsers of earlier (and possibly*/
                                              /* later) versions of the spec *|*/
  UInt32              version;

                                              /* the total size of the stream in bytes, including the four bytes in*/
                                              /* the version above*/
  ByteCount           sizeOfDataBlock;

                                              /* offset from the beginning of the stream to the flattened text layout data.*/
                                              /* This can be set to 0 if there are no text layouts stored in the stream.*/
  ByteCount           offsetToTextLayouts;

                                              /* offset from the beginning of the stream to the flattened style run data. */
                                              /* This can be set to 0 if there is no flattened style run data in the stream*/
  ByteCount           offsetToStyleRuns;

                                              /* offset to the flattened style list data. This can be set to 0 if there*/
                                              /* is no flattened style list data*/
  ByteCount           offsetToStyleList;
};
typedef struct ATSFlatDataMainHeaderBlock ATSFlatDataMainHeaderBlock;
/* ------------------ */
/* Block 2 Structures */
/* ------------------ */
/*
   The Block 2 Structures are not currently used by any of ATSUI's internal parsing
   or packing routines. They are, however, part of the 'ustl' standard and are put
   here for developer conveniance, as well as to properly define the standard.
*/

/*
   This is the header that is attached to each flattened text layout. The
   number of flattened text layouts in the stucture is specified by the
   ATSFlatDataTextLayoutHeader structure that is below.
*/
struct ATSFlatDataTextLayoutDataHeader {

                                              /* the total size of this particular flattened text layout, including any*/
                                              /* padding bytes and such. */
  ByteCount           sizeOfLayoutData;

                                              /* the number of characters covered by this flattened text layout*/
  ByteCount           textLayoutLength;

                                              /* the byte offset relative to the start of this structure to the flattened*/
                                              /* layout control data. This can be set to zero if there are no layout*/
                                              /* controls.*/
  ByteCount           offsetToLayoutControls;

                                              /* the byte offset, relative to the start of this structure to the*/
                                              /* flattened line info. This can be set to zero if there is no line info */
                                              /* in this layout.*/
  ByteCount           offsetToLineInfo;

                                              /* if the offsetToLayoutControls is non-zero, then following this block*/
                                              /* there will be a ATSFlattenedLayoutDataFlattenedLayoutControlsHeader*/
                                              /* followed by an array of ATSFlattenedLayoutDataFlattenedLayoutControls*/
                                              /* structures. If the offsetToLineInfo is non-zero, then following the*/
                                              /* flattened layout controls will be a ATSFlatDataLineInfoHeader*/
                                              /* structure.*/
};
typedef struct ATSFlatDataTextLayoutDataHeader ATSFlatDataTextLayoutDataHeader;
/*
   This is the the main header for block 2. If there is a block 2, then there
   needs to be one of these. This structure is what the offsetToTextLayouts
   points to in block 1.
*/
struct ATSFlatDataTextLayoutHeader {

                                              /* the total number of flattened text layouts stored in this block.*/
                                              /* This must be non-zero, as if there were no flattened text layouts, the*/
                                              /* entire block 2 would not exist*/
  ItemCount           numFlattenedTextLayouts;

                                              /* first of possibly many flattened text layouts. There should be one of*/
                                              /* these for each flattened text layout as determined by the*/
                                              /* numFlattenedTextLayouts above. */
  ATSFlatDataTextLayoutDataHeader  flattenedTextLayouts[1];
};
typedef struct ATSFlatDataTextLayoutHeader ATSFlatDataTextLayoutHeader;
/*
   This is the header for the flattened layout controls structure. This is
   the structure that a non-zero offsetToLayoutControls points to in the
   ATSFlatDataTextLayoutDataHeader
*/
struct ATSFlatDataLayoutControlsDataHeader {

                                              /* the number of flattened layout controls. It is suggested that there be*/
                                              /* at least one layout control to output the line direction for the layout*/
  ItemCount           numberOfLayoutControls;

                                              /* first of possibly many flattened layout controls. There should be one */
                                              /* of these for each layout control as determined by the*/
                                              /* numberOfLayoutControls above. Of course, if there are no layout controls,*/
                                              /* then this structure shouldn't even exist. Each attribute info structure*/
                                              /* in the array could be followed by additional padding bytes in order*/
                                              /* to maintain four-byte alignment. These padding bytes are not to be*/
                                              /* included in the fValueSize member of each structure. */
  ATSUAttributeInfo   controlArray[1];
};
typedef struct ATSFlatDataLayoutControlsDataHeader ATSFlatDataLayoutControlsDataHeader;
struct ATSFlatDataLineInfoData {

                                              /* the length of this particular line in UniChars*/
  UniCharCount        lineLength;

                                              /* the number of line controls applied to this line. This can be set*/
                                              /* to zero if there are no special line controls applied to this line.*/
  ItemCount           numberOfLineControls;

                                              /* the numberOfLineControls is non-zero, then following this structure*/
                                              /* must be an array of ATSUAttributeInfo structures. There must be one*/
                                              /* ATSUAttributeInfo structure for each numberOfLineControls above.*/
};
typedef struct ATSFlatDataLineInfoData  ATSFlatDataLineInfoData;
/*
   This structure is the main data header for the flattened line info data. This
   is what a non-zero offsetToLineInfo points to in the 
   ATSFlatDataTextLayoutDataHeader structure above.
*/
struct ATSFlatDataLineInfoHeader {

                                              /* the number of flattened line info structures that are stored in this*/
                                              /* block. This value should really be equal to the number of soft line*/
                                              /* breaks in the layout + 1. Of course if numberOfLines is zero, then*/
                                              /* this structure shouldn't even be used.*/
  ItemCount           numberOfLines;

                                              /* the first in a array of ATSFlatDataLineInfoData structures. There*/
                                              /* needs to be a ATSFlatDataLineInfoData for each numberOfLines*/
                                              /* specified above.*/
  ATSFlatDataLineInfoData  lineInfoArray[1];
};
typedef struct ATSFlatDataLineInfoHeader ATSFlatDataLineInfoHeader;
/* ------------------ */
/* Block 3 Structures */
/* ------------------ */
/*
   The block 3 structures are used by ATSUI style run flattening and parsing
   functions, ATSUFlattenStyleRunsToStream and ATSUUnflattenStyleRunsFromStream
   to represent flattened style run information. These structures go hand and
   hand with the block 4 structures.
*/

/*
   This is the data header that appears before the style run data structures.
   This structure is what a non-zero offsetToStyleRuns in the
   ATSFlatDataMainHeaderBlock points to in block 1.
*/
struct ATSFlatDataStyleRunDataHeader {

                                              /* the number of style run data structures stored in this block*/
  ItemCount           numberOfStyleRuns;

                                              /* the first in an array of ATSUStyleRunInfo structures. There needs to*/
                                              /* be a ATSUStyleRunInfo structure for each numberOfStyleRuns specified*/
                                              /* above. This structure is defined in ATSUnicode.h*/
  ATSUStyleRunInfo    styleRunArray[1];
};
typedef struct ATSFlatDataStyleRunDataHeader ATSFlatDataStyleRunDataHeader;
/* ------------------ */
/* Block 4 Structures */
/* ------------------ */
/*
   The block 4 structures store flattened ATSUStyle objects. This too, is
   currently used by the ATSUI style run flattening and parsing functions,
   ATSUFlattenStyleRunsToStream and ATSUUnflattenStyleRunsFromStream. 
*/

/*
   this structure forms the beginning of an individually flattened ATSUStyle
   object. 
*/
struct ATSFlatDataStyleListStyleDataHeader {

                                              /* the size of this flattened style object, including these four bytes and*/
                                              /* any padding bytes at the end of the structure. Basically, this can be*/
                                              /* used to determine where the next structure in the array begins.*/
  ByteCount           sizeOfStyleInfo;

                                              /* the number of attributes set in this flattened style object. This should */
                                              /* be at least one for the font data, although it can be 0 if this is to be*/
                                              /* unspecfied.*/
  ItemCount           numberOfSetAttributes;

                                              /* the number of font features set in the flattened style object. This can*/
                                              /* be set to 0 if there are no font features set in the style object. */
  ItemCount           numberOfSetFeatures;

                                              /* the number of font variations set in the flattened style object. This*/
                                              /* can be set to 0 if there are no font variations set in the style object.*/
  ItemCount           numberOfSetVariations;

                                              /* after this structure header, there is the following data in this block:*/

                                              /* 1. if the numberOfSetAttributes is non-zero, then there will be an*/
                                              /*       array of ATSUAttributeInfo structures immediately following the*/
                                              /*       above header data to store the style attributes. This is a variable*/
                                              /*       structure array. There must be one ATSUAttributeInfo for*/
                                              /*       for each numberOfSetAttributes. If numberOfSetAttributes is zero,*/
                                              /*       then skip to the next data section 2.*/

                                              /* 2. if the numberOfSetFeatures is non-zero, then there will be an array*/
                                              /*       of ATSFlatDataStyleListFeatureData structures immediately after*/
                                              /*       the ATSUAttributeInfo array above (if any). There must be one*/
                                              /*       ATSFlatDataStyleListFeatureData structure for each */
                                              /*       numberOfSetFeatures set in the header above. If numberOfSetFeatures*/
                                              /*       is zero, then skip to the next data section 3.*/

                                              /* 3. if the numberOfSetVariations is non-zero, then there will be an*/
                                              /*       array of ATSFlatDataStyleListVariationData immediately after the*/
                                              /*       ATSFlatDataStyleListFeatureData array above (if any). There must be*/
                                              /*       one ATSFlatDataStyleListVariationData structure for each */
                                              /*       numberOfSetVariations set in the header above.*/
};
typedef struct ATSFlatDataStyleListStyleDataHeader ATSFlatDataStyleListStyleDataHeader;
/*
   this structure is the main header for this block. This structure is what a
   non-zero offsetToStyleList in the ATSFlatDataMainHeaderBlock points to in
   block 1.
*/
struct ATSFlatDataStyleListHeader {

                                              /* the total number of flattened style objects stored in this block*/
  ItemCount           numberOfStyles;

                                              /* the first in an array of flattned style entries. The data stored*/
                                              /* in them is variably sized, so a simply array access won't do for*/
                                              /* iterating through these. However, there must be one of these*/
                                              /* ATSFlatDataStyleListStyleDataHeader structures for each */
                                              /* numberOfStyles above.*/
  ATSFlatDataStyleListStyleDataHeader  styleDataArray[1];

};
typedef struct ATSFlatDataStyleListHeader ATSFlatDataStyleListHeader;
/*
   this structure stores flattened font feature data. An array of these comes
   after the array of font data attributes (if any) if the numberOfSetFeatures is
   non-zero. There must be one of these structures for each numberOfSetFeatures.
*/
struct ATSFlatDataStyleListFeatureData {

                                              /* the font feature type*/
  ATSUFontFeatureType  theFeatureType;

                                              /* the font feature selector*/
  ATSUFontFeatureSelector  theFeatureSelector;
};
typedef struct ATSFlatDataStyleListFeatureData ATSFlatDataStyleListFeatureData;
/*
   this structure stores the flattened font variation data. An array of these 
   comes after the array of ATSFlatDataStyleListFeatureData structures (if any) 
   if the numberOfSetVariations is non-zero. There must be one of these
   structures for each numberOfSetFeatures.
*/
struct ATSFlatDataStyleListVariationData {

                                              /* the variation axis*/
  ATSUFontVariationAxis  theVariationAxis;

                                              /* the variation value*/
  ATSUFontVariationValue  theVariationValue;
};
typedef struct ATSFlatDataStyleListVariationData ATSFlatDataStyleListVariationData;
/* ------------------------ */
/* Flattened Font Data Info */
/* ------------------------ */
/*
   This is somewhat of an addendum to the 'ustl' structure above. These flattened 
   data structures are stored in block 4 as a font attribute with the attribute 
   tag of kATSUFontTag. They can store font data in a few different ways, such as
   by a FontSync reference or by simple raw font name data. Just as with the 
   'ustl' above, this structure must maintain four byte alignment.
*/


/* these are the currenly supported font specifiers. */
typedef UInt32 ATSFlatDataFontSpeciferType;
enum {
                                        /* this specifier allows the storage of font data based on name data. This*/
                                        /* uses the stuctures below to store the actual data itself.*/
  kATSFlattenedFontSpecifierRawNameData = 'namd'
};

/*
   this is the main header for the font data. It dictates what type of data
   is stored. The actual data stored must match the type specified by the
   nameSpecType. 
*/
struct ATSFlatDataFontNameDataHeader {

                                              /* the type of data that is flattened in this structure*/
  ATSFlatDataFontSpeciferType  nameSpecifierType;

                                              /* the size of the data that is flattened in this structre, not including */
                                              /* any padding bytes that may be necessary to achive the four byte */
                                              /* alignment of the data, unless they are specified as part of structure, */
                                              /* such as with the ATSFlatDataFontSpecRawNameData structure.*/
  ByteCount           nameSpecifierSize;

                                              /* after this header comes the flattened font name data which matches*/
                                              /* the type specified by the nameSpecifierType above. For instance, if */
                                              /* the nameSpecType is kATSFlattenedFontNameSpecifierRawNameData, the*/
                                              /* structure that immediately follows this would be a*/
                                              /* ATSFlatDataFontNameRawNameDataHeader structure. */

};
typedef struct ATSFlatDataFontNameDataHeader ATSFlatDataFontNameDataHeader;
/*
   the next two structures are only used when the nameSpecType is set to
   kATSFlattenedFontSpecifierRawNameData. They are setup to store multiple
   font name table entries for the purposes of reconstructing an ATSUFontID
   for (hopefully) the same font some time in the future.
*/
/* this is the structure in which raw font name data is actually stored. */
struct ATSFlatDataFontSpecRawNameData {

                                              /* the type of name being specified*/
  FontNameCode        fontNameType;

                                              /* the platform type of the font name, whether it be Unicode, Mac, etc.  */
                                              /* This should be specified if known. If not known, then specify*/
                                              /* kFontNoPlatform, but then all matching will be done based on the first*/
                                              /* font in the name table matching the other parameters.*/
  FontPlatformCode    fontNamePlatform;

                                              /* the script code of the font’s name based on the platform that was passed*/
                                              /* in above. If set to kFontNoScript, then the name will be matched based*/
                                              /* on the first font in the name table matching the other font name*/
                                              /* parameters.*/
  FontScriptCode      fontNameScript;

                                              /* the language of the font name. If set to kFontNoLanguage, then the name */
                                              /* will be matched based on the first font in the name table matching the*/
                                              /* other font name parameters.*/
  FontLanguageCode    fontNameLanguage;

                                              /* the length of the font name in bytes, not including any padding bytes*/
                                              /* added to maintain the four byte alignment*/
  ByteCount           fontNameLength;

                                              /* after the name length comes the actual font name data itself, plus any*/
                                              /* padding bytes needed to maintain the four byte alignment.*/

};
typedef struct ATSFlatDataFontSpecRawNameData ATSFlatDataFontSpecRawNameData;
/*
   this is a header structure that defines some things constant throughout
   the entire search for the font name, as well as the array of
   ATSFlatDataFontNameData structures. In order to gaurantee that the same font 
   will be used, more than one name specifer should be stored. The standard ATSUI
   style run flattening and parsing functions, ATSUFlattenStyleRunsToStream and
   ATSUUnflattenStyleRunsFromStream. These will store both the font's full name
   (kFontFullName) as well as the font's manufacturer name (kFontManufacturerName)
   and match fonts based on both of
   these. 
*/
struct ATSFlatDataFontSpecRawNameDataHeader {

                                              /* the number of flattened font names. There must be at least one flattened */
                                              /* font name, otherwise the structure is malformed.*/
  ItemCount           numberOfFlattenedNames;

                                              /* the first in an array of possibly many font name specifiers - depending*/
                                              /* on how specific the caller wants this. There must be one */
                                              /* ATSFlatDataFontNameData structure for each numberOfFlattenedNames*/
                                              /* above.*/
  ATSFlatDataFontSpecRawNameData  nameDataArray[1];

};
typedef struct ATSFlatDataFontSpecRawNameDataHeader ATSFlatDataFontSpecRawNameDataHeader;
/* ---------------------------------------------------------------------------- */
/* Style Flattening and Parsing Functions                                       */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUFlattenStyleRunsToStream()
 *  
 *  Summary:
 *    Converts a series of ATSUStyle objects and associated run info to
 *    a flat binary representation.
 *  
 *  Discussion:
 *    This function takes an array of ATSUStyle objects and style run
 *    information and flattens the data to the specified format. The
 *    style runs must all reference the same block of Unicode text
 *    (usually passed separately as text in the 'utxt' format). The
 *    style runs must also be in ascending order relative to the text
 *    in the text block. Typically you use the function
 *    ATSUFlattenStyleRunsFromStream by calling it twice, as follows:
 *    (1) Provide appropriate values for the iStreamFormat,
 *    iFlattenOptions, iNumberOfRunInfo, iRunInfoArray,
 *    iNumberOfStyleObjects, and iStyleArray parameters. Set
 *    iStreamBufferSize to 0, oStreamBuffer to NULL, and pass a valid
 *    reference to a ByteCount variable in the oActualStreamBufferSize
 *    parameter. Call the function ATSUFlattenStyleRunsToStream. On
 *    return, oActualStreamBufferSize points to the size needed for the
 *    buffer. (2) Allocate an appropriately-sized buffer for the
 *    oStreamBuffer parameter and then call the function
 *    ATSUFlattenStyleRunsToStream a second time.
 *  
 *  Parameters:
 *    
 *    iStreamFormat:
 *      The format of the flattened data. There is only one format
 *      supported at this time ('ustl'), so you must pass the constant
 *      kATSUDataStreamUnicodeStyledText.
 *    
 *    iFlattenOptions:
 *      The options you want to use to flatten the data. There are no
 *      options supported at this time, so you must pass the constant
 *      kATSUFlattenOptionNoOptionsMask.
 *    
 *    iNumberOfRunInfo:
 *      The number of style run information structures passed in the
 *      iRunInfoArray parameter. If you pass 0, ATSUI assumes there is
 *      only one style for the entire text block passed in the
 *      oStreamBuffer parameter. The flattened data format passed to
 *      the iStreamFormat parameter must support the use of one style.
 *    
 *    iRunInfoArray:
 *      An array of ATSUStyleRunInfo structures that describes the
 *      style runs to be flattened. This array must contain
 *      iNumberOfRunInfo entries. An ATSUStyleRunInfo structure
 *      contains an index into an array of unique ATSUStyle objects and
 *      the length of the run to which the style object applies. Each
 *      index in the ATSUStyleRunInfo structure must reference a valid
 *      ATSUStyle object passed in the iStyleArray parameter. You can
 *      pass NULL, only if iNumberOfRunInfo is set to zero.
 *    
 *    iNumberOfStyleObjects:
 *      The number of ATSUStyle objects in the array passed to the
 *      iStyleArray parameter. You must pass a value that is greater
 *      than 0.
 *    
 *    iStyleArray:
 *      An array of ATSUStyle objects to be flattened. You cannot pass
 *      NULL.
 *    
 *    iStreamBufferSize:
 *      The size of the stream buffer, pointed to by the oStreamBuffer
 *      parameter. You can pass 0only if the iStreamBufferSize
 *      parameter is set to NULL. If you are uncertain of the size of
 *      the array, see the Discussion.
 *    
 *    oStreamBuffer:
 *      On input, a pointer to the data you want to flatten. On return,
 *      points to the flattened data. If you pass NULL for this
 *      parameter, no data is flattened. Instead, the size of the
 *      buffer is calculated by ATSUI and returned in oActualStreamSize
 *      parameter. See the Discussion for more details. You are
 *      responsible for allocating the text buffer passed in the
 *      oStreamBuffer parameter.
 *    
 *    oActualStreamBufferSize:
 *      On return, the size of the data written to the oStreamBuffer
 *      parameter. You can pass NULL only if the oStreamBuffer
 *      parameter is not NULL.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUFlattenStyleRunsToStream(
  ATSUFlattenedDataStreamFormat   iStreamFormat,
  ATSUFlattenStyleRunOptions      iFlattenOptions,
  ItemCount                       iNumberOfRunInfo,
  const ATSUStyleRunInfo          iRunInfoArray[],
  ItemCount                       iNumberOfStyleObjects,
  const ATSUStyle                 iStyleArray[],
  ByteCount                       iStreamBufferSize,
  void *                          oStreamBuffer,
  ByteCount *                     oActualStreamBufferSize)    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ATSUUnflattenStyleRunsFromStream()
 *  
 *  Summary:
 *    Creates a series of ATSUStyle objects and associated run
 *    information from a flat binary representation.
 *  
 *  Discussion:
 *    This function extracts the ATSUI style run information from
 *    previously-flattened data. The style objects and style run
 *    information structures are returned in two separate arrays—the
 *    array oStyleArray and the array oRunInfoArray. These arrays are
 *    not parallel. Each ATSUStyle object in the oStyleArray is a
 *    unique ATSUStyle object. To figure out which ATSUStyle object
 *    belongs to which text run, the caller must parse the array of
 *    ATSUStyleRunInfo structures. These structures contain the style
 *    run lengths and an index into the oStyleArray. Typically you use
 *    the function ATSUUnflattenStyleRunsFromStream by calling it
 *    twice, as follows: (1) Provide appropriate values for the
 *    iStreamFormat, iUnflattenOptions, and iStreamBuffer parameters.
 *    Pass 0for the iNumberOfRunInfo and iNumberOfStyleObjects
 *    parameters, NULL for the oRunInfoArray and oStyleArray,
 *    parameters and valid ItemCount references for the
 *    oActualNumberOfRunInfo and oActualNumberOfStyleObjects
 *    parameters. On return, oActualNumberOfRunInfo and
 *    oActualNumberOfStyleObjects point to the sizes needed to allocate
 *    these arrays. (2) Allocate appropriately-sized arrays of
 *    ATSUStyleRunStructures and ATSUStyle object references. Call the
 *    function ATSUUnflattenStyleRunsFromStream a second time, passing
 *    the newly allocated arrays in the oRunInfoArray and oStyleArray
 *    parameters, with the iNumberOfRunInfo and iNumberOfStyleObjects
 *    parameters set to the values you obtained from the first call.
 *  
 *  Parameters:
 *    
 *    iStreamFormat:
 *      The format of the flattened data. There is only one format
 *      supported at this time ('ustl'), so you must pass the constant
 *      kATSUDataStreamUnicodeStyledText.
 *    
 *    iUnflattenOptions:
 *      The options you want to use to unflatten the data. There are no
 *      options supported at this time, so you must pass the constant
 *      kATSUUnflattenOptionNoOptionsMask.
 *    
 *    iStreamBufferSize:
 *      The size of the buffer pointed to by the iStreamBuffer
 *      parameter. You must pass a value greater than 0.
 *    
 *    iStreamBuffer:
 *      A pointer to the buffer that contains the flattened data. The
 *      data must be of the format specified by the iStreamFormat
 *      parameter and must be of size specified by the
 *      iStreamBufferSize parameter. You cannot pass NULL .
 *    
 *    iNumberOfRunInfo:
 *      The number of style run information structures passed in the
 *      oRunInfoArray parameter. If you are uncertain of the number of
 *      style run information structures, see the Discussion.
 *    
 *    iNumberOfStyleObjects:
 *      The number of ATSUStyle objects in the array passed into the
 *      iStyleArray parameter. If you are uncertain of the number of
 *      ATSUStyle objects, see the Discussion.
 *    
 *    oRunInfoArray:
 *      On return, points to an array of style run information
 *      structures. Each structure contains a style run length and
 *      index into the oStyleArray array. If you are uncertain of how
 *      much memory to allocate for this array, see the Discussion. You
 *      are responsible for disposing of the array when you no longer
 *      need it.
 *    
 *    oStyleArray:
 *      On return, a pointer to an array of the unique ATSUStyle
 *      objects obtained from the flattened data. The indices returned
 *      in the array oRunInfoArray are indices into this array. If you
 *      are uncertain of how much memory to allocate for this array,
 *      see the Discussion. You are responsible for disposing of the
 *      array and the ATSUI style objects in the array when you no
 *      longer need the array.
 *    
 *    oActualNumberOfRunInfo:
 *      On return, points to the actual number of ATSUStyleRunInfo
 *      structures obtained from the flattened data. The actual number
 *      of structures is the number of entries added to the array
 *      oRunInfoArray. You can pass NULL if you to not want to obtain
 *      this value.
 *    
 *    oActualNumberOfStyleObjects:
 *      On return, points to the actual number of unique ATSUStyle
 *      objects obtained from the flattened data. The actual number is
 *      the number of entries added to the oStyleArray array. You can
 *      pass NULL if you do no want to obtain this value.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUUnflattenStyleRunsFromStream(
  ATSUFlattenedDataStreamFormat   iStreamFormat,
  ATSUUnFlattenStyleRunOptions    iUnflattenOptions,
  ByteCount                       iStreamBufferSize,
  const void *                    iStreamBuffer,
  ItemCount                       iNumberOfRunInfo,
  ItemCount                       iNumberOfStyleObjects,
  ATSUStyleRunInfo                oRunInfoArray[],
  ATSUStyle                       oStyleArray[],
  ItemCount *                     oActualNumberOfRunInfo,
  ItemCount *                     oActualNumberOfStyleObjects) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Functions listed beyond this point are either deprecated or not recommended */

/*
 *  ATSUCopyToHandle()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUFlattenStyleRunsToStream instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    ATSUFlattenStyleRunsToStream instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.1
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCopyToHandle(
  ATSUStyle   iStyle,
  Handle      oStyleHandle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_1;


/*
 *  ATSUPasteFromHandle()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUUnflattenStyleRunsFromStream instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    ATSUUnflattenStyleRunsFromStream instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.1
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUPasteFromHandle(
  ATSUStyle   iStyle,
  Handle      iStyleHandle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_1;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __ATSUNICODEFLATTENING__ */

