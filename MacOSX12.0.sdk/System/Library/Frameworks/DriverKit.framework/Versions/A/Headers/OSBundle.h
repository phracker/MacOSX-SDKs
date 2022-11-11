/* iig(DriverKit-191.30.2) generated from OSBundle.iig */

/* OSBundle.iig:1-34 */
/*
 * Copyright (c) 2020-2020 Apple Inc. All rights reserved.
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

#ifndef _IOKIT_OSBUNDLE_H
#define _IOKIT_OSBUNDLE_H

#include <DriverKit/OSObject.h>  /* .iig include */
#include <DriverKit/OSMappedFile.h>  /* .iig include */

/* source class OSBundle OSBundle.iig:35-76 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class OSBundle
 *
 * @abstract
 * OSBundle represents either a DriverKit bundle or a DriverKit framework bundle.
 */
class LOCALONLY OSBundle : public OSObject
{
public:

	virtual void
	free() override;

	virtual bool
	init() override;

	/*!
	 * @brief  Return the main bundle for the current running DriverKit binary.
	 * @return Allocated OSBundle object with reference count 1 to be released by the caller.
	 */
	static OSBundle *
	mainBundle();

	/*!
	 * @brief  Create an OSBundle from the specified path.
	 * @param  path      The path to the bundle.
	 * @return Allocated OSBundle object with reference count 1 to be released by the caller.
	 */
	static OSBundle *
	createFromPath(const char *path);

	/*!
	 * @brief  Get the specified resource.
	 * @param name         Name of the resource. This is interpreted as a path relative to the bundle directory.
	 * @param options      Options to use when opening the resource. This field is currently ignored and should be set to 0.
	 * @param minGuardSize The size of the guard page region surrounding this file's mapping.
	 *                     This is rounded up to the nearest page size multiple.
	 * @param outputMap    Allocated OSMappedFile object with reference count 1 to be released by the caller.
	 * @return kIOReturnSuccess on success. See IOReturn.h for error codes.
	 */
	kern_return_t
	loadResource(const char * name, uint64_t options, size_t minGuardSize, OSMappedFile **outputMap);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSBundle OSBundle.iig:35-76 */


#define OSBundle_Methods \
\
public:\
\
    static OSBundle *\
    mainBundle(\
);\
\
    static OSBundle *\
    createFromPath(\
        const char * path);\
\
    kern_return_t\
    loadResource(\
        const char * name,\
        uint64_t options,\
        size_t minGuardSize,\
        OSMappedFile ** outputMap);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSBundle_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSBundle_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    init(\
) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gOSBundleMetaClass;
extern const OSClassLoadInformation OSBundle_Class;

class OSBundleMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSBundleInterface : public OSInterface
{
public:
};

struct OSBundle_IVars;
struct OSBundle_LocalIVars;

class OSBundle : public OSObject, public OSBundleInterface
{
#if !KERNEL
    friend class OSBundleMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef OSBundle_DECLARE_IVARS
OSBundle_DECLARE_IVARS
#else /* OSBundle_DECLARE_IVARS */
    union
    {
        OSBundle_IVars * ivars;
        OSBundle_LocalIVars * lvars;
    };
#endif /* OSBundle_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gOSBundleMetaClass; };
#endif /* KERNEL */

    using super = OSObject;

#if !KERNEL
    OSBundle_Methods
    OSBundle_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* OSBundle.iig:78- */

#endif /* ! _IOKIT_OSBUNDLE_H */
