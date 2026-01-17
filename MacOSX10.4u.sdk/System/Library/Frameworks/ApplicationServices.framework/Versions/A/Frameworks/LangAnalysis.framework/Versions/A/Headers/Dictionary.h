/*
     File:       LangAnalysis/Dictionary.h
 
     Contains:   Dictionary Manager Interfaces
 
     Version:    LanguageAnalysis-164.2.17~316
 
     Copyright:  © 1992-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DICTIONARY__
#define __DICTIONARY__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __AE__
#include <AE/AE.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power

/*
=============================================================================================
 Modern Dictionary Manager
=============================================================================================
*/
/*
    Dictionary information
*/
enum {
  kDictionaryFileType           = 'dict',
  kDCMDictionaryHeaderSignature = 'dict',
  kDCMDictionaryHeaderVersion   = 2
};

enum {
  kDCMAnyFieldTag               = typeWildCard,
  kDCMAnyFieldType              = typeWildCard
};

/*
    Contents of a Field Info Record (an AERecord)
*/
enum {
  keyDCMFieldTag                = 'ftag', /* typeEnumeration */
  keyDCMFieldType               = 'ftyp', /* typeEnumeration */
  keyDCMMaxRecordSize           = 'mrsz', /* typeMagnitude */
  keyDCMFieldAttributes         = 'fatr',
  keyDCMFieldDefaultData        = 'fdef',
  keyDCMFieldName               = 'fnam', /* typeChar */
  keyDCMFieldFindMethods        = 'ffnd' /* typeAEList of typeDCMFindMethod */
};

/*
    Special types for fields of a Field Info Record
*/
enum {
  typeDCMFieldAttributes        = 'fatr',
  typeDCMFindMethod             = 'fmth'
};


/*
    Field attributes
*/
enum {
  kDCMIndexedFieldMask          = 0x00000001,
  kDCMRequiredFieldMask         = 0x00000002,
  kDCMIdentifyFieldMask         = 0x00000004,
  kDCMFixedSizeFieldMask        = 0x00000008,
  kDCMHiddenFieldMask           = (long)0x80000000
};

typedef OptionBits                      DCMFieldAttributes;
/*
    Standard dictionary properties
*/
enum {
  pDCMAccessMethod              = 'amtd', /* data type: typeChar ReadOnly */
  pDCMPermission                = 'perm', /* data type: typeUInt16 */
  pDCMListing                   = 'list', /* data type: typeUInt16 */
  pDCMMaintenance               = 'mtnc', /* data type: typeUInt16 */
  pDCMLocale                    = 'locl', /* data type: typeUInt32.  Optional; default = kLocaleIdentifierWildCard */
  pDCMClass                     = pClass, /* data type: typeUInt16 */
  pDCMCopyright                 = 'info' /* data type: typeChar */
};

/*
    pDCMPermission property constants
*/
enum {
  kDCMReadOnlyDictionary        = 0,
  kDCMReadWriteDictionary       = 1
};

/*
    pDCMListing property constants
*/
enum {
  kDCMAllowListing              = 0,
  kDCMProhibitListing           = 1
};

/*
    pDCMClass property constants
*/
enum {
  kDCMUserDictionaryClass       = 0,
  kDCMSpecificDictionaryClass   = 1,
  kDCMBasicDictionaryClass      = 2
};

/*
    Standard search method
*/
enum {
  kDCMFindMethodExactMatch      = kAEEquals,
  kDCMFindMethodBeginningMatch  = kAEBeginsWith,
  kDCMFindMethodContainsMatch   = kAEContains,
  kDCMFindMethodEndingMatch     = kAEEndsWith,
  kDCMFindMethodForwardTrie     = 'ftri', /* used for morphological analysis*/
  kDCMFindMethodBackwardTrie    = 'btri' /* used for morphological analysis*/
};

typedef OSType                          DCMFindMethod;
/*
    AccessMethod features
*/
enum {
  kDCMCanUseFileDictionaryMask  = 0x00000001,
  kDCMCanUseMemoryDictionaryMask = 0x00000002,
  kDCMCanStreamDictionaryMask   = 0x00000004,
  kDCMCanHaveMultipleIndexMask  = 0x00000008,
  kDCMCanModifyDictionaryMask   = 0x00000010,
  kDCMCanCreateDictionaryMask   = 0x00000020,
  kDCMCanAddDictionaryFieldMask = 0x00000040,
  kDCMCanUseTransactionMask     = 0x00000080
};

typedef OptionBits                      DCMAccessMethodFeature;
typedef UInt32                          DCMUniqueID;
typedef struct OpaqueDCMObjectID*       DCMObjectID;
typedef DCMObjectID                     DCMAccessMethodID;
typedef DCMObjectID                     DCMDictionaryID;
#define kDCMInvalidObjectID ((DCMObjectID) kInvalidID)
typedef struct OpaqueDCMObjectRef*      DCMObjectRef;
typedef DCMObjectRef                    DCMDictionaryRef;
typedef DCMObjectRef                    DCMDictionaryStreamRef;
#define kDCMInvalidObjectRef ((DCMObjectRef) kInvalidID)
typedef struct OpaqueDCMObjectIterator*  DCMObjectIterator;
typedef DCMObjectIterator               DCMAccessMethodIterator;
typedef DCMObjectIterator               DCMDictionaryIterator;
typedef struct OpaqueDCMFoundRecordIterator*  DCMFoundRecordIterator;
/*
    Field specification declarations
*/
typedef DescType                        DCMFieldTag;
typedef DescType                        DCMFieldType;
/*
    Dictionary header information
*/
struct DCMDictionaryHeader {
  FourCharCode        headerSignature;
  UInt32              headerVersion;
  ByteCount           headerSize;
  Str63               accessMethod;
};
typedef struct DCMDictionaryHeader      DCMDictionaryHeader;
/*
    Callback routines
*/
typedef CALLBACK_API( Boolean , DCMProgressFilterProcPtr )(Boolean determinateProcess, UInt16 percentageComplete, UInt32 callbackUD);
typedef STACK_UPP_TYPE(DCMProgressFilterProcPtr)                DCMProgressFilterUPP;
/*
 *  NewDCMProgressFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeDCMProgressFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeDCMProgressFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
    Library version
*/
/*
 *  DCMLibraryVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern UInt32 
DCMLibraryVersion(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Create/delete dictionary
*/
/*
 *  DCMNewDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMNewDictionary(
  DCMAccessMethodID   accessMethodID,
  const FSSpec *      newDictionaryFile,
  ScriptCode          scriptTag,
  const AEDesc *      listOfFieldInfoRecords,
  Boolean             invisible,
  ItemCount           recordCapacity,
  DCMDictionaryID *   newDictionary)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMDeriveNewDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDeriveNewDictionary(
  DCMDictionaryID    srcDictionary,
  const FSSpec *     newDictionaryFile,
  ScriptCode         scriptTag,
  Boolean            invisible,
  ItemCount          recordCapacity,
  DCMDictionaryID *  newDictionary)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMDeleteDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDeleteDictionary(DCMDictionaryID dictionaryID)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Register dictionary
*/
/*
 *  DCMRegisterDictionaryFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMRegisterDictionaryFile(
  const FSSpec *     dictionaryFile,
  DCMDictionaryID *  dictionaryID)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMUnregisterDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMUnregisterDictionary(DCMDictionaryID dictionaryID)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Open dictionary
*/
/*
 *  DCMOpenDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMOpenDictionary(
  DCMDictionaryID       dictionaryID,
  ByteCount             protectKeySize,
  ConstLogicalAddress   protectKey,
  DCMDictionaryRef *    dictionaryRef)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMCloseDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCloseDictionary(DCMDictionaryRef dictionaryRef)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Change access privilege
*/
/*
 *  DCMGetDictionaryWriteAccess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryWriteAccess(
  DCMDictionaryRef   dictionaryRef,
  Duration           timeOutDuration)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMReleaseDictionaryWriteAccess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMReleaseDictionaryWriteAccess(
  DCMDictionaryRef   dictionaryRef,
  Boolean            commitTransaction)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Find records
*/
/*
 *  DCMFindRecords()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMFindRecords(
  DCMDictionaryRef          dictionaryRef,
  DCMFieldTag               keyFieldTag,
  ByteCount                 keySize,
  ConstLogicalAddress       keyData,
  DCMFindMethod             findMethod,
  ItemCount                 preFetchedDataNum,
  DCMFieldTag               preFetchedData[],
  ItemCount                 skipCount,
  ItemCount                 maxRecordCount,
  DCMFoundRecordIterator *  recordIterator)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMCountRecordIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern ItemCount 
DCMCountRecordIterator(DCMFoundRecordIterator recordIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMIterateFoundRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMIterateFoundRecord(
  DCMFoundRecordIterator   recordIterator,
  ByteCount                maxKeySize,
  ByteCount *              actualKeySize,
  LogicalAddress           keyData,
  DCMUniqueID *            uniqueID,
  AEDesc *                 dataList)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMDisposeRecordIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDisposeRecordIterator(DCMFoundRecordIterator recordIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Dump dictionary
*/
/*
 *  DCMCountRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCountRecord(
  DCMDictionaryID   dictionaryID,
  ItemCount *       count)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetRecordSequenceNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetRecordSequenceNumber(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  DCMUniqueID           uniqueID,
  ItemCount *           sequenceNum)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetNthRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetNthRecord(
  DCMDictionaryRef   dictionaryRef,
  DCMFieldTag        keyFieldTag,
  ItemCount          serialNum,
  ByteCount          maxKeySize,
  ByteCount *        keySize,
  LogicalAddress     keyData,
  DCMUniqueID *      uniqueID)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetNextRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetNextRecord(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  DCMUniqueID           uniqueID,
  ByteCount             maxKeySize,
  ByteCount *           nextKeySize,
  LogicalAddress        nextKeyData,
  DCMUniqueID *         nextUniqueID)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetPrevRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetPrevRecord(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  DCMUniqueID           uniqueID,
  ByteCount             maxKeySize,
  ByteCount *           prevKeySize,
  LogicalAddress        prevKeyData,
  DCMUniqueID *         prevUniqueID)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Get field data
*/
/*
 *  DCMGetFieldData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldData(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  DCMUniqueID           uniqueID,
  ItemCount             numOfData,
  const DCMFieldTag     dataTag[],
  AEDesc *              dataList)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMSetFieldData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMSetFieldData(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  DCMUniqueID           uniqueID,
  const AEDesc *        dataList)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Add record
*/
/*
 *  DCMAddRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMAddRecord(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  Boolean               checkOnly,
  const AEDesc *        dataList,
  DCMUniqueID *         newUniqueID)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMDeleteRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDeleteRecord(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  DCMUniqueID           uniqueID)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Reorganize/compact dictionary
*/
/*
 *  DCMReorganizeDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMReorganizeDictionary(
  DCMDictionaryID        dictionaryID,
  ItemCount              extraCapacity,
  DCMProgressFilterUPP   progressProc,
  UInt32                 userData)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMCompactDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCompactDictionary(
  DCMDictionaryID        dictionaryID,
  DCMProgressFilterUPP   progressProc,
  UInt32                 userData)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    DictionaryID utilities
*/
/*
 *  DCMGetFileFromDictionaryID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFileFromDictionaryID(
  DCMDictionaryID   dictionaryID,
  FSSpec *          fileRef)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetDictionaryIDFromFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryIDFromFile(
  const FSSpec *     fileRef,
  DCMDictionaryID *  dictionaryID)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetDictionaryIDFromRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern DCMDictionaryID 
DCMGetDictionaryIDFromRef(DCMDictionaryRef dictionaryRef)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Field information and manipulation
*/
/*
 *  DCMGetDictionaryFieldInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryFieldInfo(
  DCMDictionaryID   dictionaryID,
  DCMFieldTag       fieldTag,
  AEDesc *          fieldInfoRecord)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Dictionary property
*/
/*
 *  DCMGetDictionaryProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryProperty(
  DCMDictionaryID   dictionaryID,
  DCMFieldTag       propertyTag,
  ByteCount         maxPropertySize,
  ByteCount *       actualSize,
  LogicalAddress    propertyValue)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMSetDictionaryProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMSetDictionaryProperty(
  DCMDictionaryID       dictionaryID,
  DCMFieldTag           propertyTag,
  ByteCount             propertySize,
  ConstLogicalAddress   propertyValue)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetDictionaryPropertyList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryPropertyList(
  DCMDictionaryID   dictionaryID,
  ItemCount         maxPropertyNum,
  ItemCount *       numProperties,
  DCMFieldTag       propertyTag[])                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Seaarch dictionary
*/
/*
 *  DCMCreateDictionaryIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCreateDictionaryIterator(DCMDictionaryIterator * dictionaryIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Search AccessMethod
*/
/*
 *  DCMCreateAccessMethodIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCreateAccessMethodIterator(DCMAccessMethodIterator * accessMethodIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Iterator Operation
*/
/*
 *  DCMCountObjectIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern ItemCount 
DCMCountObjectIterator(DCMObjectIterator iterator)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMIterateObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMIterateObject(
  DCMObjectIterator   iterator,
  DCMObjectID *       objectID)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMResetObjectIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMResetObjectIterator(DCMObjectIterator iterator)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMDisposeObjectIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDisposeObjectIterator(DCMObjectIterator iterator)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Get AccessMethod information
*/
/*
 *  DCMGetAccessMethodIDFromName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetAccessMethodIDFromName(
  ConstStr63Param      accessMethodName,
  DCMAccessMethodID *  accessMethodID)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Field Info Record routines
*/
/*
 *  DCMCreateFieldInfoRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCreateFieldInfoRecord(
  DescType             fieldTag,
  DescType             fieldType,
  ByteCount            maxRecordSize,
  DCMFieldAttributes   fieldAttributes,
  AEDesc *             fieldDefaultData,
  ItemCount            numberOfFindMethods,
  DCMFindMethod        findMethods[],
  AEDesc *             fieldInfoRecord)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetFieldTagAndType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldTagAndType(
  const AEDesc *  fieldInfoRecord,
  DCMFieldTag *   fieldTag,
  DCMFieldType *  fieldType)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetFieldMaxRecordSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldMaxRecordSize(
  const AEDesc *  fieldInfoRecord,
  ByteCount *     maxRecordSize)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetFieldAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldAttributes(
  const AEDesc *        fieldInfoRecord,
  DCMFieldAttributes *  attributes)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetFieldDefaultData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldDefaultData(
  const AEDesc *  fieldInfoRecord,
  DescType        desiredType,
  AEDesc *        fieldDefaultData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DCMGetFieldFindMethods()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldFindMethods(
  const AEDesc *  fieldInfoRecord,
  ItemCount       findMethodsArrayMaxSize,
  DCMFindMethod   findMethods[],
  ItemCount *     actualNumberOfFindMethods)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Check Dictionary Manager availability
*/
#if TARGET_RT_MAC_CFM
#ifdef __cplusplus
    inline pascal Boolean DCMDictionaryManagerAvailable() { return (DCMLibraryVersion != (void*)kUnresolvedCFragSymbolAddress); }
#else
    #define DCMDictionaryManagerAvailable()     ((DCMLibraryVersion != (void*)kUnresolvedCFragSymbolAddress)
#endif
#elif TARGET_RT_MAC_MACHO
/* Dictionary Manager is always available on OS X */
#ifdef __cplusplus
    inline pascal Boolean DCMDictionaryManagerAvailable() { return true; }
#else
    #define DCMDictionaryManagerAvailable()     (true)
#endif
#endif  /*  */

/*
=============================================================================================
    Definitions for Japanese Analysis Module
=============================================================================================
*/
/*
    Default dictionary access method for Japanese analysis
*/
#define kAppleJapaneseDefaultAccessMethodName   "\pDAM:Apple Backward Trie Access Method"
/*
    Data length limitations of Apple Japanese dictionaries
*/
enum {
  kMaxYomiLengthInAppleJapaneseDictionary = 40,
  kMaxKanjiLengthInAppleJapaneseDictionary = 64
};

/*
    Defined field tags of Apple Japanese dictionary
*/
enum {
  kDCMJapaneseYomiTag           = 'yomi',
  kDCMJapaneseHyokiTag          = 'hyok',
  kDCMJapaneseHinshiTag         = 'hins',
  kDCMJapaneseWeightTag         = 'hind',
  kDCMJapanesePhoneticTag       = 'hton',
  kDCMJapaneseAccentTag         = 'acnt',
  kDCMJapaneseOnKunReadingTag   = 'OnKn',
  kDCMJapaneseFukugouInfoTag    = 'fuku'
};

enum {
  kDCMJapaneseYomiType          = typeUnicodeText,
  kDCMJapaneseHyokiType         = typeUnicodeText,
  kDCMJapaneseHinshiType        = 'hins',
  kDCMJapaneseWeightType        = typeShortInteger,
  kDCMJapanesePhoneticType      = typeUnicodeText,
  kDCMJapaneseAccentType        = 'byte',
  kDCMJapaneseOnKunReadingType  = typeUnicodeText,
  kDCMJapaneseFukugouInfoType   = 'fuku'
};


/*
=============================================================================================
 System 7 Dictionary Manager
=============================================================================================
*/

#pragma options align=reset
#pragma options align=mac68k

enum {
                                        /* Dictionary data insertion modes */
  kInsert                       = 0,    /* Only insert the input entry if there is nothing in the dictionary that matches the key. */
  kReplace                      = 1,    /* Only replace the entries which match the key with the input entry. */
  kInsertOrReplace              = 2     /* Insert the entry if there is nothing in the dictionary which matches the key, otherwise replaces the existing matched entries with the input entry. */
};

/* This Was InsertMode */

typedef short                           DictionaryDataInsertMode;
enum {
                                        /* Key attribute constants */
  kIsCaseSensitive              = 0x10, /* case sensitive = 16       */
  kIsNotDiacriticalSensitive    = 0x20  /* diac not sensitive = 32    */
};

enum {
                                        /* Registered attribute type constants.   */
  kNoun                         = -1,
  kVerb                         = -2,
  kAdjective                    = -3,
  kAdverb                       = -4
};

/* This Was AttributeType */
typedef SInt8                           DictionaryEntryAttribute;
/* Dictionary information record */
struct DictionaryInformation {
  FSSpec              dictionaryFSSpec;
  SInt32              numberOfRecords;
  SInt32              currentGarbageSize;
  ScriptCode          script;
  SInt16              maximumKeyLength;
  SInt8               keyAttributes;
};
typedef struct DictionaryInformation    DictionaryInformation;
struct DictionaryAttributeTable {
  UInt8               datSize;
  DictionaryEntryAttribute  datTable[1];
};
typedef struct DictionaryAttributeTable DictionaryAttributeTable;
typedef DictionaryAttributeTable *      DictionaryAttributeTablePtr;
/*
 *  InitializeDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  OpenDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CloseDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InsertRecordToDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DeleteRecordFromDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FindRecordInDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FindRecordByIndexInDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetDictionaryInformation()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CompactDictionary()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */






#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __DICTIONARY__ */

