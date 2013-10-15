/*
 * Copyright (c) 2006 Apple Computer, Inc. All rights reserved.
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
#ifndef _DYLD_IMAGES_
#define _DYLD_IMAGES_

#ifdef __cplusplus
extern "C" {
#endif


/* 
 *	Beginning in Mac OS X 10.4, this is how gdb discovers which mach-o images are loaded in a process.
 *
 *	gdb looks for the symbol "_dyld_all_image_infos" in dyld.  It contains the fields below.  
 *
 *	For a snashot of what images are currently loaded, the infoArray fields contain a pointer
 *	to an array of all images. If infoArray is NULL, it means it is being modified, come back later.
 *
 *	To be notified of changes, gdb sets a break point on the address pointed to by the notificationn
 *	field.  The function it points to is called by dyld with an array of information about what images 
 *	have been added (dyld_image_adding) or are about to be removed (dyld_image_removing). 
 *
 * The notification is called after infoArray is updated.  This means that if gdb attaches to a process
 * and infoArray is NULL, gdb can set a break point on notification and let the proccess continue to
 * run until the break point.  Then gdb can inspect the full infoArray.
 */

enum dyld_image_mode { dyld_image_adding=0, dyld_image_removing=1 };

struct dyld_image_info {
	const struct mach_header*	imageLoadAddress;	/* base address image is mapped into */
	const char*					imageFilePath;		/* path dyld used to load the image */
	uintptr_t					imageFileModDate;	/* time_t of image file */
													/* if stat().st_mtime of imageFilePath does not match imageFileModDate, */
													/* then file has been modified since dyld loaded it */
};

typedef void (*dyld_image_notifier)(enum dyld_image_mode mode, uint32_t infoCount, const struct dyld_image_info info[]);

struct dyld_all_image_infos {
	uint32_t						version;		/* == 1 in Mac OS X 10.4 */
	uint32_t						infoArrayCount;
	const struct dyld_image_info*	infoArray;
	dyld_image_notifier				notification;		
	bool							processDetachedFromSharedRegion;
};
extern struct dyld_all_image_infos  dyld_all_image_infos;




/*
 * Beginning in Mac OS X 10.5, this is how gdb discovers where the shared cache is in a process.
 * Images that are in the shared cache have their segments rearranged, so when using imageFilePath
 * to load the file from disk, you have to know to adjust addresses based on how their segment
 * was rearranged.
 *
 * gdb looks for the symbol "_dyld_shared_region_ranges" in dyld. 
 * 
 * It contains information the count of shared regions used by the process.  The count is
 * the number of start/length pairs.  
 */
struct dyld_shared_cache_ranges {
	uintptr_t					sharedRegionsCount;	/* how many ranges follow */
	struct {
		uintptr_t	start;
		uintptr_t	length;
	}							ranges[4];			/* max regions */
};
extern struct dyld_shared_cache_ranges dyld_shared_cache_ranges;



#ifdef __cplusplus
}
#endif

#endif /* _DYLD_IMAGES_ */
