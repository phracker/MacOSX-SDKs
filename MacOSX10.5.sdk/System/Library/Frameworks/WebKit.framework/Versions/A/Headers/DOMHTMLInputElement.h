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


@class DOMHTMLFormElement;
@class NSString;
@class NSURL;

@interface DOMHTMLInputElement : DOMHTMLElement
@property(copy) NSString *defaultValue;
@property BOOL defaultChecked;
@property(readonly, retain) DOMHTMLFormElement *form;
@property(copy) NSString *accept;
@property(copy) NSString *accessKey;
@property(copy) NSString *align;
@property(copy) NSString *alt;
@property BOOL checked;
@property BOOL disabled;
@property int maxLength;
@property(copy) NSString *name;
@property BOOL readOnly;
@property(copy) NSString *size;
@property(copy) NSString *src;
@property int tabIndex;
@property(copy) NSString *type;
@property(copy) NSString *useMap;
@property(copy) NSString *value;
@property(readonly, copy) NSString *altDisplayString;
@property(readonly, copy) NSURL *absoluteImageURL;

- (void)blur;
- (void)focus;
- (void)select;
- (void)click;
@end
