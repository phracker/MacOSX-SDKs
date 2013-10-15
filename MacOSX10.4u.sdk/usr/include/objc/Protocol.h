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
	Protocol.h
	Copyright 1991-1996 NeXT Software, Inc.
*/

#ifndef _OBJC_PROTOCOL_H_
#define _OBJC_PROTOCOL_H_

#import <objc/Object.h>

struct objc_method_description {
	SEL name;
	char *types;
};
struct objc_method_description_list {
        int count;
        struct objc_method_description list[1];
};

@interface Protocol : Object
{
@private
	char *protocol_name;
 	struct objc_protocol_list *protocol_list;
  	struct objc_method_description_list *instance_methods, *class_methods;
}

/* Obtaining attributes intrinsic to the protocol */

- (const char *)name;

/* Testing protocol conformance */

- (BOOL) conformsTo: (Protocol *)aProtocolObject;

/* Looking up information specific to a protocol */

- (struct objc_method_description *) descriptionForInstanceMethod:(SEL)aSel;
- (struct objc_method_description *) descriptionForClassMethod:(SEL)aSel;

@end

#endif /* _OBJC_PROTOCOL_H_ */
