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

#import <WebKit/DOMNode.h>


@class DOMAbstractView;
@class DOMAttr;
@class DOMCDATASection;
@class DOMCSSRuleList;
@class DOMCSSStyleDeclaration;
@class DOMComment;
@class DOMDocumentFragment;
@class DOMDocumentType;
@class DOMElement;
@class DOMEntityReference;
@class DOMEvent;
@class DOMImplementation;
@class DOMNode;
@class DOMNodeList;
@class DOMProcessingInstruction;
@class DOMRange;
@class DOMStyleSheetList;
@class DOMText;
@class DOMXPathExpression;
@class DOMXPathResult;
@class NSString;
@protocol DOMXPathNSResolver;

@interface DOMDocument : DOMNode
@property(readonly, retain) DOMDocumentType *doctype;
@property(readonly, retain) DOMImplementation *implementation;
@property(readonly, retain) DOMElement *documentElement;
@property(readonly, retain) DOMAbstractView *defaultView;
@property(readonly, retain) DOMStyleSheetList *styleSheets;

- (DOMElement *)createElement:(NSString *)tagName;
- (DOMDocumentFragment *)createDocumentFragment;
- (DOMText *)createTextNode:(NSString *)data;
- (DOMComment *)createComment:(NSString *)data;
- (DOMCDATASection *)createCDATASection:(NSString *)data;
- (DOMProcessingInstruction *)createProcessingInstruction:(NSString *)target data:(NSString *)data;
- (DOMAttr *)createAttribute:(NSString *)name;
- (DOMEntityReference *)createEntityReference:(NSString *)name;
- (DOMNodeList *)getElementsByTagName:(NSString *)tagname;
- (DOMNode *)importNode:(DOMNode *)importedNode deep:(BOOL)deep;
- (DOMElement *)createElementNS:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName;
- (DOMAttr *)createAttributeNS:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName;
- (DOMNodeList *)getElementsByTagNameNS:(NSString *)namespaceURI localName:(NSString *)localName;
- (DOMElement *)getElementById:(NSString *)elementId;
- (DOMNode *)adoptNode:(DOMNode *)source;
- (DOMEvent *)createEvent:(NSString *)eventType;
- (DOMRange *)createRange;
- (DOMCSSStyleDeclaration *)getOverrideStyle:(DOMElement *)element pseudoElement:(NSString *)pseudoElement;
- (DOMXPathExpression *)createExpression:(NSString *)expression resolver:(id <DOMXPathNSResolver>)resolver;
- (id <DOMXPathNSResolver>)createNSResolver:(DOMNode *)nodeResolver;
- (DOMXPathResult *)evaluate:(NSString *)expression contextNode:(DOMNode *)contextNode resolver:(id <DOMXPathNSResolver>)resolver type:(unsigned short)type inResult:(DOMXPathResult *)inResult;
- (DOMCSSStyleDeclaration *)createCSSStyleDeclaration;
- (DOMCSSStyleDeclaration *)getComputedStyle:(DOMElement *)element pseudoElement:(NSString *)pseudoElement;
- (DOMCSSRuleList *)getMatchedCSSRules:(DOMElement *)element pseudoElement:(NSString *)pseudoElement;
- (DOMCSSRuleList *)getMatchedCSSRules:(DOMElement *)element pseudoElement:(NSString *)pseudoElement authorOnly:(BOOL)authorOnly;
@end

@interface DOMDocument (DOMDocumentDeprecated)
- (DOMProcessingInstruction *)createProcessingInstruction:(NSString *)target :(NSString *)data DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMNode *)importNode:(DOMNode *)importedNode :(BOOL)deep DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMElement *)createElementNS:(NSString *)namespaceURI :(NSString *)qualifiedName DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMAttr *)createAttributeNS:(NSString *)namespaceURI :(NSString *)qualifiedName DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMNodeList *)getElementsByTagNameNS:(NSString *)namespaceURI :(NSString *)localName DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMCSSStyleDeclaration *)getOverrideStyle:(DOMElement *)element :(NSString *)pseudoElement DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMXPathExpression *)createExpression:(NSString *)expression :(id <DOMXPathNSResolver>)resolver DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMXPathResult *)evaluate:(NSString *)expression :(DOMNode *)contextNode :(id <DOMXPathNSResolver>)resolver :(unsigned short)type :(DOMXPathResult *)inResult DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (DOMCSSStyleDeclaration *)getComputedStyle:(DOMElement *)element :(NSString *)pseudoElement DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
@end
