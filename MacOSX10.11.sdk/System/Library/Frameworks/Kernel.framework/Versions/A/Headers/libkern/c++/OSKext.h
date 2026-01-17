/*
 * Copyright (c) 2008-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _LIBKERN_OSKEXT_H
#define _LIBKERN_OSKEXT_H

extern "C" {
#include <kern/thread_call.h>
#include <libkern/OSKextLibPrivate.h>
#include <libkern/kernel_mach_header.h>
#include <libkern/kxld.h>
#include <mach/kmod.h>

}

#include <libkern/OSKextLib.h>
#include <libkern/OSKextLibPrivate.h>
#include <libkern/c++/OSObject.h>
#include <libkern/c++/OSContainers.h>
#include <IOKit/IOLocks.h>

/*********************************************************************
* C functions used for callbacks.
*********************************************************************/

/*********************************************************************
* C Function Prototypes for Friend Declarations.
*********************************************************************/
class OSKext;

extern "C" {

void OSKextLog(
    OSKext         * aKext,
    OSKextLogSpec    msgLogSpec,
    const char     * format, ...)
        __attribute__((format(printf, 3, 4)));

void OSKextVLog(
    OSKext         * aKext,
    OSKextLogSpec    msgLogSpec,
    const char     * format,
    va_list          srcArgList);

};

/********************************************************************/
#if PRAGMA_MARK
#pragma mark -
#endif

struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

struct OSKextGrabPgoStruct {
    bool metadata;
    uint64_t *pSize;
    char *pBuffer;
    uint64_t bufferSize;
    int err;
    struct list_head list_head;
};

#ifndef container_of
#define container_of(ptr,type,member) ((type*)(((uintptr_t)ptr) - offsetof(type, member)))
#endif
/********************************************************************/


/*
 * @class OSKext
 */
/********************************************************************/
class OSKext : public OSObject
{
    OSDeclareDefaultStructors(OSKext)

#if PRAGMA_MARK
/**************************************/
#pragma mark Friend Declarations
/**************************************/
#endif
    friend class IOCatalogue;
    friend class KLDBootstrap;
    friend class OSMetaClass;

    friend int OSKextGrabPgoData(uuid_t uuid,
                                 uint64_t *pSize,
                                 char *pBuffer,
                                 uint64_t bufferSize,
                                 int wait_for_unload,
                                 int metadata);


private:

   /*************************
    * Instance variables
    *************************/
    OSDictionary   * infoDict;

    const OSSymbol * bundleID;
    OSString       * path;               // not necessarily correct :-/
    OSString       * executableRelPath;  // relative to bundle

    OSKextVersion    version;            // parsed
    OSKextVersion    compatibleVersion;  // parsed

   /* These fields are required for tracking loaded kexts and
    * will always have values for a loaded kext.
    */
    OSKextLoadTag    loadTag;            // 'id' from old kmod_info; 
                                         // kOSKextInvalidLoadTag invalid
    kmod_info_t    * kmod_info;          // address into linkedExec./alloced for interface

    OSArray        * dependencies;       // kernel resource does not have any;
                                         // links directly to kernel

   /* Only real kexts have these; interface kexts do not.
    */
    OSData         * linkedExecutable;
    OSSet          * metaClasses;           // for C++/OSMetaClass kexts
    
   /* Only interface kexts have these; non-interface kexts can get at them
    * in the linked Executable.
    */
    OSData         * interfaceUUID;

    struct {
        unsigned int loggingEnabled:1;

        unsigned int hasAllDependencies:1;
        unsigned int hasBleedthrough:1;

        unsigned int interface:1;
        unsigned int kernelComponent:1;
        unsigned int prelinked:1;
        unsigned int loaded:1;
        unsigned int dtraceInitialized:1;
        unsigned int starting:1;
        unsigned int started:1;
        unsigned int stopping:1;
        unsigned int unloading:1;

        unsigned int autounloadEnabled:1;
        unsigned int delayAutounload:1;    // for development

        unsigned int CPPInitialized:1;
        unsigned int jettisonLinkeditSeg:1;
    } flags;

    struct list_head pendingPgoHead;
    uuid_t instance_uuid;
    OSKextAccount * account;

#if PRAGMA_MARK
/**************************************/
#pragma mark Private Functions
/**************************************/
#endif


private:
   /* Called by power management at sleep/shutdown.
    */
    static bool setLoadEnabled(bool flag);
    static bool setUnloadEnabled(bool flag);
    static bool setAutounloadsEnabled(bool flag);
    static bool setKernelRequestsEnabled(bool flag);

    // all getters subject to race condition, caller beware
    static bool getLoadEnabled(void);
    static bool getUnloadEnabled(void);
    static bool getAutounloadEnabled(void);
    static bool getKernelRequestsEnabled(void);

   /* Instance life cycle.
    */
    static OSKext * withBooterData(
        OSString * deviceTreeName,
        OSData   * booterData);
    virtual bool initWithBooterData(
        OSString * deviceTreeName,
        OSData   * booterData);

    static OSKext * withPrelinkedInfoDict(
        OSDictionary * infoDict);
    virtual bool initWithPrelinkedInfoDict(
        OSDictionary * infoDict);

    static OSKext * withMkext2Info(
        OSDictionary * anInfoDict,
        OSData       * mkextData);
    virtual bool initWithMkext2Info(
        OSDictionary * anInfoDict,
        OSData       * mkextData);

    virtual bool setInfoDictionaryAndPath(
        OSDictionary * aDictionary,
        OSString     * aPath);
    virtual bool setExecutable(
        OSData       * anExecutable,
        OSData       * externalData        = NULL,
        bool           externalDataIsMkext = false);
    virtual bool registerIdentifier(void);

    virtual void free(void) APPLE_KEXT_OVERRIDE;

    static OSReturn removeKext(
        OSKext * aKext,
        bool     terminateServicesAndRemovePersonalitiesFlag = false);

    virtual bool isInExcludeList(void);

   /* Mkexts.
    */
    static OSReturn readMkextArchive(
        OSData   * mkextData,
        uint32_t * checksumPtr = NULL);
    static OSReturn readMkext2Archive(
        OSData * mkextData,
        OSDictionary ** mkextPlistOut,
        uint32_t * checksumPtr = NULL);
    virtual OSData * createMkext2FileEntry(
        OSData * mkextData,
        OSNumber * offsetNum,
        const char * entryName);
    virtual OSData * extractMkext2FileData(
        UInt8      * data,
        const char * name,
        uint32_t     compressedSize,
        uint32_t     fullSize);

   /* Dependencies.
    */
    virtual bool resolveDependencies(
        OSArray * loopStack = NULL); // priv/prot
    virtual bool addBleedthroughDependencies(OSArray * anArray);
    virtual bool flushDependencies(bool forceFlag = false); // priv/prot
    virtual uint32_t  getNumDependencies(void);
    virtual OSArray * getDependencies(void);

   /* User-space requests (load/generic).
    */
    static OSReturn loadFromMkext(
        OSKextLogSpec   clientLogSpec,
        char          * mkextBuffer,
        uint32_t        mkextBufferLength,
        char         ** logInfoOut,
        uint32_t      * logInfoLengthOut);
    static OSReturn handleRequest(
        host_priv_t     hostPriv,
        OSKextLogSpec   clientLogSpec,
        char          * requestBuffer,
        uint32_t        requestLength,
        char         ** responseOut,
        uint32_t      * responseLengthOut,
        char         ** logInfoOut,
        uint32_t      * logInfoLengthOut);
    static OSReturn serializeLogInfo(
        OSArray   * logInfoArray,
        char     ** logInfoOut,
        uint32_t  * logInfoLengthOut);

   /* Loading.
    */
    virtual OSReturn load(
        OSKextExcludeLevel   startOpt         = kOSKextExcludeNone,
        OSKextExcludeLevel   startMatchingOpt = kOSKextExcludeAll,
        OSArray            * personalityNames = NULL); // priv/prot
    virtual OSReturn unload(void);
    virtual OSReturn queueKextNotification(
        const char * notificationName,
        OSString   * kextIdentifier);

    static void recordIdentifierRequest(
        OSString * kextIdentifier);

    virtual OSReturn slidePrelinkedExecutable(void);
    virtual OSReturn loadExecutable(void);
    virtual void     jettisonLinkeditSegment(void);
    virtual void     jettisonDATASegmentPadding(void);
    static  void     considerDestroyingLinkContext(void);
    virtual OSData * getExecutable(void);
    virtual void     setLinkedExecutable(OSData * anExecutable);
    
#if CONFIG_DTRACE
    friend  void OSKextRegisterKextsWithDTrace(void);
    static  void registerKextsWithDTrace(void);
    virtual void registerWithDTrace(void);
    virtual void unregisterWithDTrace(void);
#endif /* CONFIG_DTRACE */

    virtual OSReturn start(bool startDependenciesFlag = true);
    virtual OSReturn stop(void);
    virtual OSReturn setVMAttributes(bool protect, bool wire);
    virtual boolean_t segmentShouldBeWired(kernel_segment_command_t *seg);
    virtual OSReturn validateKextMapping(bool startFlag);
    virtual boolean_t verifySegmentMapping(kernel_segment_command_t *seg);

    static OSArray * copyAllKextPersonalities(
        bool filterSafeBootFlag = false);

    static  void  setPrelinkedPersonalities(OSArray * personalitiesArray);

    static  void  sendAllKextPersonalitiesToCatalog(
        bool startMatching = false);
    virtual OSReturn  sendPersonalitiesToCatalog(
        bool      startMatching    = false,
        OSArray * personalityNames = NULL);
    
    static bool canUnloadKextWithIdentifier(
        OSString * kextIdentifier,
        bool       checkClassesFlag = true);

    static OSReturn autounloadKext(OSKext * aKext);

   /* Sync with user space.
    */
    static OSReturn pingKextd(void);

   /* Getting info about loaded kexts (kextstat).
    */
    static  OSDictionary * copyLoadedKextInfo(
        OSArray * kextIdentifiers = NULL,
        OSArray * keys = NULL);
    virtual OSDictionary * copyInfo(OSArray * keys = NULL);

   /* Logging to user space.
    */
    static OSKextLogSpec setUserSpaceLogFilter(
        OSKextLogSpec  userLogSpec,
        bool           captureFlag = false);
    static OSArray * clearUserSpaceLogFilter(void);
    static OSKextLogSpec getUserSpaceLogFilter(void);

   /* OSMetaClasses defined by kext.
    */
    virtual OSReturn addClass(
        OSMetaClass * aClass,
        uint32_t     numClasses);
    virtual OSReturn removeClass(
        OSMetaClass * aClass);
    virtual bool    hasOSMetaClassInstances(void);
    virtual OSSet * getMetaClasses(void);
    static  void reportOSMetaClassInstances(
        const char     * kextIdentifier,
        OSKextLogSpec    msgLogSpec);
    virtual void reportOSMetaClassInstances(
        OSKextLogSpec msgLogSpec);

   /* Resource requests and other callback stuff.
    */
    static OSReturn dispatchResource(OSDictionary * requestDict);

    static OSReturn dequeueCallbackForRequestTag(
        OSKextRequestTag    requestTag,
        OSDictionary     ** callbackRecordOut);
    static OSReturn dequeueCallbackForRequestTag(
        OSNumber     *    requestTagNum,
        OSDictionary ** callbackRecordOut);
    static void invokeRequestCallback(
        OSDictionary * callbackRecord,
        OSReturn         requestResult);
    virtual void invokeOrCancelRequestCallbacks(
        OSReturn callbackResult,
        bool     invokeFlag = true);
    virtual uint32_t countRequestCallbacks(void);

   /* panic() support.
    */
    static void printKextsInBacktrace(
        vm_offset_t   * addr,
        unsigned int    cnt,
        int          (* printf_func)(const char *fmt, ...),
        bool            lockFlag,
        bool            doUnslide);
    static boolean_t summaryIsInBacktrace(
        OSKextLoadedKextSummary * summary,
        vm_offset_t             * addr,
        unsigned int              cnt);
    static void printSummary(
        OSKextLoadedKextSummary * summary,
        int                    (* printf_func)(const char *fmt, ...),
        bool                      doUnslide);

    static int saveLoadedKextPanicListTyped(
        const char * prefix,
        int          invertFlag,
        int          libsFlag,
        char       * paniclist,
        uint32_t     list_size);
    static void saveLoadedKextPanicList(void);
    void savePanicString(bool isLoading);
    static void printKextPanicLists(int (*printf_func)(const char *fmt, ...));

   /* Kext summary support.
    */
    static void updateLoadedKextSummaries(void);
    void updateLoadedKextSummary(OSKextLoadedKextSummary *summary);
    void updateActiveAccount(OSKextActiveAccount *account);

    /* C++ Initialization.
     */
    virtual void               setCPPInitialized(bool initialized=true);



#if PRAGMA_MARK
/**************************************/
#pragma mark Public Functions
/**************************************/
#endif
public:
    // caller must release
    static OSKext * lookupKextWithIdentifier(const char * kextIdentifier);
    static OSKext * lookupKextWithIdentifier(OSString * kextIdentifier);
    static OSKext * lookupKextWithLoadTag(OSKextLoadTag aTag);
    static OSKext * lookupKextWithAddress(vm_address_t address);
    static OSKext * lookupKextWithUUID(uuid_t uuid);

    kernel_section_t *lookupSection(const char *segname, const char*secname);
    
    static bool isKextWithIdentifierLoaded(const char * kextIdentifier);

    static OSReturn loadKextWithIdentifier(
        const char       * kextIdentifier,
        Boolean            allowDeferFlag      = true,
        Boolean            delayAutounloadFlag = false,
        OSKextExcludeLevel startOpt            = kOSKextExcludeNone,
        OSKextExcludeLevel startMatchingOpt    = kOSKextExcludeAll,
        OSArray          * personalityNames    = NULL);
    static OSReturn loadKextWithIdentifier(
        OSString         * kextIdentifier,
        Boolean            allowDeferFlag      = true,
        Boolean            delayAutounloadFlag = false,
        OSKextExcludeLevel startOpt            = kOSKextExcludeNone,
        OSKextExcludeLevel startMatchingOpt    = kOSKextExcludeAll,
        OSArray          * personalityNames    = NULL);
    static OSReturn removeKextWithIdentifier(
        const char * kextIdentifier,
        bool         terminateServicesAndRemovePersonalitiesFlag = false);
    static OSReturn removeKextWithLoadTag(
        OSKextLoadTag loadTag,
        bool          terminateServicesAndRemovePersonalitiesFlag = false);

    static OSReturn requestResource(
        const char                    * kextIdentifier,
        const char                    * resourceName,
        OSKextRequestResourceCallback   callback,
        void                          * context,
        OSKextRequestTag              * requestTagOut);
    static OSReturn cancelRequest(
        OSKextRequestTag    requestTag,
        void             ** contextOut); 

    static void     considerUnloads(Boolean rescheduleOnlyFlag = false);
    static void     flushNonloadedKexts(Boolean flushPrelinkedKexts);
    static void     setKextdActive(Boolean active = true);
    static void     setDeferredLoadSucceeded(Boolean succeeded = true);
    static void     considerRebuildOfPrelinkedKernel(void);
    static void     createExcludeListFromBooterData(
                                            OSDictionary * theDictionary,
                                            OSCollectionIterator * theIterator);
    static void     createExcludeListFromPrelinkInfo(OSArray * theInfoArray);

    virtual bool    setAutounloadEnabled(bool flag);

    virtual const OSSymbol   * getIdentifier(void);
    virtual const char       * getIdentifierCString(void);
    virtual OSKextVersion      getVersion(void);
    virtual OSKextVersion      getCompatibleVersion(void);
    virtual bool               isLibrary(void);
    virtual bool               isCompatibleWithVersion(OSKextVersion aVersion);
    virtual OSObject         * getPropertyForHostArch(const char * key);
        
    virtual OSKextLoadTag      getLoadTag(void);
    virtual void               getSizeInfo(uint32_t *loadSize, uint32_t *wiredSize);
    virtual OSData           * copyUUID(void);
    virtual OSArray          * copyPersonalitiesArray(void);
    
   /* This removes personalities naming the kext (by CFBundleIdentifier),
    * not all personalities defined by the kext (IOPersonalityPublisher or CFBundleIdentifier).
    */
    virtual void               removePersonalitiesFromCatalog(void);

   /* Converts common string-valued properties to OSSymbols for lower memory consumption.
    */
    static void uniquePersonalityProperties(OSDictionary * personalityDict);

    virtual bool               declaresExecutable(void);     // might be missing
    virtual bool               isInterface(void);
    virtual bool               isKernel(void);
    virtual bool               isKernelComponent(void);
    virtual bool               isExecutable(void);
    virtual bool               isLoadableInSafeBoot(void);
    virtual bool               isPrelinked(void);
    virtual bool               isLoaded(void);
    virtual bool               isStarted(void);
    virtual bool               isCPPInitialized(void);
};


#endif /* !_LIBKERN_OSKEXT_H */
