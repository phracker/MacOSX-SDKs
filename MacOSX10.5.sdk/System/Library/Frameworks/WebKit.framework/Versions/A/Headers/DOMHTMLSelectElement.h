/*
 * Copyright (C) 2004, 2005, 2006, 2007 Apple Inc. All rights reserved.
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#import <WebKit/DOMHTMLElement.h>


@class DOMHTMLElement;
@class DOMHTMLFormElement;
@class DOMHTMLOptionsCollection;
@class NSString;

@interface DOMHTMLSelectElement : DOMHTMLElement
@property(readonly, copy) NSString *type;
@property int selectedIndex;
@property(copy) NSString *value;
@property(readonly) int length;
@property(readonly, retain) DOMHTMLFormElement *form;
@property(readonly, retain) DOMHTMLOptionsCollection *options;
@property BOOL disabled;
@property BOOL multiple;
@property(copy) NSString *name;
@property int size;
@property int tabIndex;

- (void)add:(DOMHTMLElement *)element before:(DOMHTMLElement *)before;
- (void)remove:(int)index;
- (void)blur;
- (void)focus;
@end

@interface DOMHTMLSelectElement (DOMHTMLSelectElementDeprecated)
- (void)add:(DOMHTMLElement *)element :(DOMHTMLElement *)before DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
@end
