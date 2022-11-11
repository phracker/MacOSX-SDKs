/*
 * Copyright (c) 2009 Apple Inc. All rights reserved.
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

#if __OBJC__
#import <Foundation/Foundation.h>
#endif /* __OBJC__ */

#include <CFOpenDirectory/CFOpenDirectory.h>

#if __OBJC__

FOUNDATION_EXPORT NSString *const ODFrameworkErrorDomain NS_AVAILABLE(10_6, NA);

#import <OpenDirectory/ODSession.h>
#import <OpenDirectory/ODRecord.h>
#import <OpenDirectory/ODNode.h>
#import <OpenDirectory/ODQuery.h>
#import <OpenDirectory/ODConfiguration.h>
#import <OpenDirectory/ODMappings.h>
#import <OpenDirectory/ODRecordMap.h>
#import <OpenDirectory/ODAttributeMap.h>
#import <OpenDirectory/ODModuleEntry.h>

#endif /* __OBJC__ */
