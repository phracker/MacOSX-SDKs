/*
 * Copyright (c) 2017-2020 Apple Inc. All Rights Reserved.
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

/*!
    @header SFChooseIdentityTableCellView
*/

#ifndef _SFCHOOSEIDENTITYTABLECELLVIEW_H_
#define _SFCHOOSEIDENTITYTABLECELLVIEW_H_

#import <Cocoa/Cocoa.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

#if __OBJC2__

API_AVAILABLE(macos(10.13))
@interface SFChooseIdentityTableCellView : NSTableCellView
{
    IBOutlet NSTextField *issuerTextField;
}
@property(assign) IBOutlet NSTextField *issuerTextField;

@end

#endif // __OBJC2__

API_UNAVAILABLE_END

#endif // _SFCHOOSEIDENTITYTABLECELLVIEW_H_¬
