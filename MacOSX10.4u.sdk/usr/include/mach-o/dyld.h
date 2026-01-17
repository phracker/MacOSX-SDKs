/*
 * Copyright (c) 1999-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#ifndef _MACH_O_DYLD_H_
#define _MACH_O_DYLD_H_

#if __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <stdint.h>
#if __cplusplus
  /* C++ has bool type built in */
#else
 #include <stdbool.h>
#endif
#include <mach-o/loader.h>
#include <AvailabilityMacros.h>

#ifndef ENUM_DYLD_BOOL
#define ENUM_DYLD_BOOL
#undef FALSE
#undef TRUE
enum DYLD_BOOL {
    FALSE,
    TRUE
};
#endif /* ENUM_DYLD_BOOL */

/*
 * The high level NS... API.
 */

/* Object file image API */
typedef enum {
    NSObjectFileImageFailure, /* for this a message is printed on stderr */
    NSObjectFileImageSuccess,
    NSObjectFileImageInappropriateFile,
    NSObjectFileImageArch,
    NSObjectFileImageFormat, /* for this a message is printed on stderr */
    NSObjectFileImageAccess
} NSObjectFileImageReturnCode;

typedef struct __NSObjectFileImage*  NSObjectFileImage;

/* limited implementation, only MH_BUNDLE files can be used */
extern NSObjectFileImageReturnCode NSCreateObjectFileImageFromFile(
    const char *pathName,
    NSObjectFileImage *objectFileImage);
extern NSObjectFileImageReturnCode NSCreateCoreFileImageFromFile(
    const char *pathName,
    NSObjectFileImage *objectFileImage);
extern NSObjectFileImageReturnCode NSCreateObjectFileImageFromMemory(
    const void *address,
    size_t size, 
    NSObjectFileImage *objectFileImage);
extern bool NSDestroyObjectFileImage(
    NSObjectFileImage objectFileImage);
/*
 * API on NSObjectFileImage's for:
 *   "for Each Symbol Definition In Object File Image" (for Dynamic Bundles)
 *   and the same thing for references
 */
extern uint32_t NSSymbolDefinitionCountInObjectFileImage(
    NSObjectFileImage objectFileImage);
extern const char * NSSymbolDefinitionNameInObjectFileImage(
    NSObjectFileImage objectFileImage,
    uint32_t ordinal);
extern uint32_t NSSymbolReferenceCountInObjectFileImage(
    NSObjectFileImage objectFileImage);
extern const char * NSSymbolReferenceNameInObjectFileImage(
    NSObjectFileImage objectFileImage,
    uint32_t ordinal,
    bool *tentative_definition); /* can be NULL */
/*
 * API on NSObjectFileImage:
 *   "does Object File Image define symbol name X" (using sorted symbol table)
 *   and a way to get the named objective-C section
 */
extern bool NSIsSymbolDefinedInObjectFileImage(
    NSObjectFileImage objectFileImage,
    const char *symbolName) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern void * NSGetSectionDataInObjectFileImage(
    NSObjectFileImage objectFileImage,
    const char *segmentName,
    const char *sectionName,
    size_t *size); /* can be NULL */
/* SPI first appeared in Mac OS X 10.3 */
extern bool NSHasModInitObjectFileImage(
    NSObjectFileImage objectFileImage)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* module API */
typedef struct __NSModule* NSModule;
extern const char * NSNameOfModule(
    NSModule m); 
extern const char * NSLibraryNameForModule(
    NSModule m);

/* limited implementation, only MH_BUNDLE files can be linked */
extern NSModule NSLinkModule(
    NSObjectFileImage objectFileImage, 
    const char *moduleName,
    uint32_t options);
#define NSLINKMODULE_OPTION_NONE		0x0
#define NSLINKMODULE_OPTION_BINDNOW		0x1
#define NSLINKMODULE_OPTION_PRIVATE		0x2
#define NSLINKMODULE_OPTION_RETURN_ON_ERROR	0x4
#define NSLINKMODULE_OPTION_DONT_CALL_MOD_INIT_ROUTINES 0x8
#define NSLINKMODULE_OPTION_TRAILING_PHYS_NAME	0x10

/* limited implementation, only modules loaded with NSLinkModule() can be
   unlinked */
extern bool NSUnLinkModule(
    NSModule module, 
    uint32_t options);
#define NSUNLINKMODULE_OPTION_NONE			0x0
#define NSUNLINKMODULE_OPTION_KEEP_MEMORY_MAPPED	0x1
#define NSUNLINKMODULE_OPTION_RESET_LAZY_REFERENCES	0x2

/* not yet implemented */
extern NSModule NSReplaceModule(
    NSModule moduleToReplace,
    NSObjectFileImage newObjectFileImage, 
    uint32_t options);

/* symbol API */
typedef struct __NSSymbol* NSSymbol;
extern bool NSIsSymbolNameDefined(
    const char *symbolName) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern bool NSIsSymbolNameDefinedWithHint(
    const char *symbolName,
    const char *libraryNameHint) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern bool NSIsSymbolNameDefinedInImage(
    const struct mach_header *image,
    const char *symbolName) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern NSSymbol NSLookupAndBindSymbol(
    const char *symbolName) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern NSSymbol NSLookupAndBindSymbolWithHint(
    const char *symbolName,
    const char *libraryNameHint) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern NSSymbol NSLookupSymbolInModule(
    NSModule module,
    const char *symbolName);
extern NSSymbol NSLookupSymbolInImage(
    const struct mach_header *image,
    const char *symbolName,
    uint32_t options);
#define NSLOOKUPSYMBOLINIMAGE_OPTION_BIND            0x0
#define NSLOOKUPSYMBOLINIMAGE_OPTION_BIND_NOW        0x1
#define NSLOOKUPSYMBOLINIMAGE_OPTION_BIND_FULLY      0x2
#define NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR 0x4
extern const char * NSNameOfSymbol(
    NSSymbol symbol);
extern void * NSAddressOfSymbol(
    NSSymbol symbol);
extern NSModule NSModuleForSymbol(
    NSSymbol symbol);

/* error handling API */
typedef enum {
    NSLinkEditFileAccessError,
    NSLinkEditFileFormatError,
    NSLinkEditMachResourceError,
    NSLinkEditUnixResourceError,
    NSLinkEditOtherError,
    NSLinkEditWarningError,
    NSLinkEditMultiplyDefinedError,
    NSLinkEditUndefinedError
} NSLinkEditErrors;

/*
 * For the NSLinkEditErrors value NSLinkEditOtherError these are the values
 * passed to the link edit error handler as the errorNumber (what would be an
 * errno value for NSLinkEditUnixResourceError or a kern_return_t value for
 * NSLinkEditMachResourceError).
 */
typedef enum {
    NSOtherErrorRelocation, 
    NSOtherErrorLazyBind,
    NSOtherErrorIndrLoop,
    NSOtherErrorLazyInit,
    NSOtherErrorInvalidArgs
} NSOtherErrorNumbers;

extern void NSLinkEditError(
    NSLinkEditErrors *c,
    int *errorNumber, 
    const char **fileName,
    const char **errorString);

typedef struct {
     void     (*undefined)(const char *symbolName);
     NSModule (*multiple)(NSSymbol s, NSModule oldModule, NSModule newModule); 
     void     (*linkEdit)(NSLinkEditErrors errorClass, int errorNumber,
                          const char *fileName, const char *errorString);
} NSLinkEditErrorHandlers;

extern void NSInstallLinkEditErrorHandlers(
    const NSLinkEditErrorHandlers *handlers);

/* other API */
extern bool NSAddLibrary(
    const char *pathName) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern bool NSAddLibraryWithSearching(
    const char *pathName) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern const struct mach_header * NSAddImage(
    const char *image_name,
    uint32_t options);
#define NSADDIMAGE_OPTION_NONE                  	0x0
#define NSADDIMAGE_OPTION_RETURN_ON_ERROR       	0x1
#define NSADDIMAGE_OPTION_WITH_SEARCHING        	0x2
#define NSADDIMAGE_OPTION_RETURN_ONLY_IF_LOADED 	0x4
#define NSADDIMAGE_OPTION_MATCH_FILENAME_BY_INSTALLNAME	0x8
extern int32_t NSVersionOfRunTimeLibrary(
    const char *libraryName);
extern int32_t NSVersionOfLinkTimeLibrary(
    const char *libraryName);
extern int _NSGetExecutablePath( /* SPI first appeared in Mac OS X 10.2 */
    char *buf,
    uint32_t *bufsize);

/*
 * The low level _dyld_... API.
 * (used by the objective-C runtime primarily)
 */
extern bool _dyld_present(
    void);

extern uint32_t _dyld_image_count(
    void);
extern const struct mach_header * _dyld_get_image_header(
    uint32_t image_index);
extern intptr_t _dyld_get_image_vmaddr_slide(
    uint32_t image_index);
extern const char * _dyld_get_image_name(
    uint32_t image_index);

extern void _dyld_register_func_for_add_image(
    void (*func)(const struct mach_header *mh, intptr_t vmaddr_slide));
extern void _dyld_register_func_for_remove_image(
    void (*func)(const struct mach_header *mh, intptr_t vmaddr_slide));
extern void _dyld_register_func_for_link_module(
    void (*func)(NSModule module));
/* not yet implemented */
extern void _dyld_register_func_for_unlink_module(
    void (*func)(NSModule module));
/* not yet implemented */
extern void _dyld_register_func_for_replace_module(
    void (*func)(NSModule oldmodule, NSModule newmodule));
extern void _dyld_get_objc_module_sect_for_module(
    NSModule module,
    void **objc_module,
    size_t *size);
extern void _dyld_bind_objc_module(
    const void *objc_module);
extern bool _dyld_bind_fully_image_containing_address(
    const void *address);
extern bool _dyld_image_containing_address(
    const void* address);
/* SPI first appeared in Mac OS X 10.3 */
extern const struct mach_header * _dyld_get_image_header_containing_address(
    const void* address)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern void _dyld_moninit(
    void (*monaddition)(char *lowpc, char *highpc));
extern bool _dyld_launched_prebound(
    void);
/* SPI first appeared in Mac OS X 10.3 */
extern bool _dyld_all_twolevel_modules_prebound(
    void)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern void _dyld_lookup_and_bind(
    const char *symbol_name,
    void **address,
    NSModule* module) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern void _dyld_lookup_and_bind_with_hint(
    const char *symbol_name,
    const char *library_name_hint,
    void **address,
    NSModule* module) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
extern void _dyld_lookup_and_bind_objc(
    const char *symbol_name,
    void **address,
    NSModule* module);
extern void _dyld_lookup_and_bind_fully(
    const char *symbol_name,
    void **address,
    NSModule* module);

extern int _dyld_func_lookup(
    const char *dyld_func_name,
    void **address);

#if __cplusplus
}
#endif /* __cplusplus */

#endif /* _MACH_O_DYLD_H_ */
