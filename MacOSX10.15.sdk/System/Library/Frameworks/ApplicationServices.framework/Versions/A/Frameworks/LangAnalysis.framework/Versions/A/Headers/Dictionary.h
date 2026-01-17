/*
     File:       LangAnalysis/Dictionary.h
 
     Contains:   Dictionary Manager Interfaces
 
     Version:    LanguageAnalysis-~1
 
     Copyright:  © 1992-2008 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DICTIONARY__
#define __DICTIONARY__

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
  kDCMHiddenFieldMask           = (int)0x80000000
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
  UInt32              headerSize;
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

#if !__LP64__
/*
    Library version
*/
#if !__LP64__
/*
 *  DCMLibraryVersion()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern UInt32 
DCMLibraryVersion(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Create/delete dictionary
*/
/*
 *  DCMNewDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  DCMDictionaryID *   newDictionary)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMDeriveNewDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  DCMDictionaryID *  newDictionary)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMDeleteDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDeleteDictionary(DCMDictionaryID dictionaryID)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Register dictionary
*/
/*
 *  DCMRegisterDictionaryFile()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMRegisterDictionaryFile(
  const FSSpec *     dictionaryFile,
  DCMDictionaryID *  dictionaryID)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMUnregisterDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMUnregisterDictionary(DCMDictionaryID dictionaryID)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Open dictionary
*/
/*
 *  DCMOpenDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMOpenDictionary(
  DCMDictionaryID       dictionaryID,
  ByteCount             protectKeySize,
  ConstLogicalAddress   protectKey,
  DCMDictionaryRef *    dictionaryRef)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMCloseDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCloseDictionary(DCMDictionaryRef dictionaryRef)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Change access privilege
*/
/*
 *  DCMGetDictionaryWriteAccess()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryWriteAccess(
  DCMDictionaryRef   dictionaryRef,
  Duration           timeOutDuration)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMReleaseDictionaryWriteAccess()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMReleaseDictionaryWriteAccess(
  DCMDictionaryRef   dictionaryRef,
  Boolean            commitTransaction)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Find records
*/
/*
 *  DCMFindRecords()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  DCMFoundRecordIterator *  recordIterator)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMCountRecordIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern ItemCount 
DCMCountRecordIterator(DCMFoundRecordIterator recordIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMIterateFoundRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  AEDesc *                 dataList)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMDisposeRecordIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDisposeRecordIterator(DCMFoundRecordIterator recordIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Dump dictionary
*/
/*
 *  DCMCountRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCountRecord(
  DCMDictionaryID   dictionaryID,
  ItemCount *       count)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetRecordSequenceNumber()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  ItemCount *           sequenceNum)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetNthRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  DCMUniqueID *      uniqueID)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetNextRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  DCMUniqueID *         nextUniqueID)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetPrevRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  DCMUniqueID *         prevUniqueID)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Get field data
*/
/*
 *  DCMGetFieldData()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  AEDesc *              dataList)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMSetFieldData()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  const AEDesc *        dataList)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Add record
*/
/*
 *  DCMAddRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  DCMUniqueID *         newUniqueID)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMDeleteRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDeleteRecord(
  DCMDictionaryRef      dictionaryRef,
  DCMFieldTag           keyFieldTag,
  ByteCount             keySize,
  ConstLogicalAddress   keyData,
  DCMUniqueID           uniqueID)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Reorganize/compact dictionary
*/
/*
 *  DCMReorganizeDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMReorganizeDictionary(
  DCMDictionaryID        dictionaryID,
  ItemCount              extraCapacity,
  DCMProgressFilterUPP   progressProc,
  UInt32                 userData)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMCompactDictionary()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCompactDictionary(
  DCMDictionaryID        dictionaryID,
  DCMProgressFilterUPP   progressProc,
  UInt32                 userData)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    DictionaryID utilities
*/
/*
 *  DCMGetFileFromDictionaryID()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFileFromDictionaryID(
  DCMDictionaryID   dictionaryID,
  FSSpec *          fileRef)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetDictionaryIDFromFile()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryIDFromFile(
  const FSSpec *     fileRef,
  DCMDictionaryID *  dictionaryID)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetDictionaryIDFromRef()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern DCMDictionaryID 
DCMGetDictionaryIDFromRef(DCMDictionaryRef dictionaryRef)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Field information and manipulation
*/
/*
 *  DCMGetDictionaryFieldInfo()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryFieldInfo(
  DCMDictionaryID   dictionaryID,
  DCMFieldTag       fieldTag,
  AEDesc *          fieldInfoRecord)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Dictionary property
*/
/*
 *  DCMGetDictionaryProperty()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryProperty(
  DCMDictionaryID   dictionaryID,
  DCMFieldTag       propertyTag,
  ByteCount         maxPropertySize,
  ByteCount *       actualSize,
  LogicalAddress    propertyValue)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMSetDictionaryProperty()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMSetDictionaryProperty(
  DCMDictionaryID       dictionaryID,
  DCMFieldTag           propertyTag,
  ByteCount             propertySize,
  ConstLogicalAddress   propertyValue)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetDictionaryPropertyList()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetDictionaryPropertyList(
  DCMDictionaryID   dictionaryID,
  ItemCount         maxPropertyNum,
  ItemCount *       numProperties,
  DCMFieldTag       propertyTag[])                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Seaarch dictionary
*/
/*
 *  DCMCreateDictionaryIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCreateDictionaryIterator(DCMDictionaryIterator * dictionaryIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Search AccessMethod
*/
/*
 *  DCMCreateAccessMethodIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMCreateAccessMethodIterator(DCMAccessMethodIterator * accessMethodIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Iterator Operation
*/
/*
 *  DCMCountObjectIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern ItemCount 
DCMCountObjectIterator(DCMObjectIterator iterator)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMIterateObject()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMIterateObject(
  DCMObjectIterator   iterator,
  DCMObjectID *       objectID)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMResetObjectIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMResetObjectIterator(DCMObjectIterator iterator)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMDisposeObjectIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMDisposeObjectIterator(DCMObjectIterator iterator)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Get AccessMethod information
*/
/*
 *  DCMGetAccessMethodIDFromName()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetAccessMethodIDFromName(
  ConstStr63Param      accessMethodName,
  DCMAccessMethodID *  accessMethodID)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
    Field Info Record routines
*/
/*
 *  DCMCreateFieldInfoRecord()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  AEDesc *             fieldInfoRecord)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetFieldTagAndType()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldTagAndType(
  const AEDesc *  fieldInfoRecord,
  DCMFieldTag *   fieldTag,
  DCMFieldType *  fieldType)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetFieldMaxRecordSize()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldMaxRecordSize(
  const AEDesc *  fieldInfoRecord,
  ByteCount *     maxRecordSize)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetFieldAttributes()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldAttributes(
  const AEDesc *        fieldInfoRecord,
  DCMFieldAttributes *  attributes)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetFieldDefaultData()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldDefaultData(
  const AEDesc *  fieldInfoRecord,
  DescType        desiredType,
  AEDesc *        fieldDefaultData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  DCMGetFieldFindMethods()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Dictionary Manager is deprecated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DictionaryMgrLib 1.0 and later
 */
extern OSStatus 
DCMGetFieldFindMethods(
  const AEDesc *  fieldInfoRecord,
  ItemCount       findMethodsArrayMaxSize,
  DCMFindMethod   findMethods[],
  ItemCount *     actualNumberOfFindMethods)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


#endif  /* !__LP64__ */

#endif  /* !__LP64__ */

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
  kDCMJapaneseWeightType        = typeSInt16,
  kDCMJapanesePhoneticType      = typeUnicodeText,
  kDCMJapaneseAccentType        = 'byte',
  kDCMJapaneseOnKunReadingType  = typeUnicodeText,
  kDCMJapaneseFukugouInfoType   = 'fuku'
};



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __DICTIONARY__ */

