/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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
/*
 *	objc-load.h
 *	Copyright 1988-1996, NeXT Software, Inc.
 */

#ifndef _OBJC_LOAD_H_
#define _OBJC_LOAD_H_

#import <objc/objc-class.h>

#import <mach-o/loader.h>

/* dynamically loading Mach-O object files that contain Objective-C code */

OBJC_EXPORT long objc_loadModules (
	char *modlist[], 
	void *errStream,
	void (*class_callback) (Class, Category),
	/*headerType*/ struct mach_header **hdr_addr,
	char *debug_file
);
OBJC_EXPORT int objc_loadModule (
	char *	moduleName, 
	void	(*class_callback) (Class, Category),
	int *	errorCode);
OBJC_EXPORT long objc_unloadModules(
	void *errorStream,				/* input (optional) */
	void (*unloadCallback)(Class, Category)		/* input (optional) */
);

OBJC_EXPORT void objc_register_header_name(
	char *name					/* input */
);

OBJC_EXPORT void objc_register_header(
	char *name					/* input */
);


#endif /* _OBJC_LOAD_H_ */
