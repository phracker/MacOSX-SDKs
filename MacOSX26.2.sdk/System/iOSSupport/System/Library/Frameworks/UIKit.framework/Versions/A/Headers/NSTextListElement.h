#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextListElement.h>)
//
//  NSTextListElement.h
//  Text Kit
//
//  Copyright (c) 2021-2025, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/NSTextElement.h>

@class NSTextList;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// NSTextListElement is a concrete subclass of NSTextElement representing a text list node. It can contain an array of child element. A text list can be represented by a tree of NSTextListElements.
#pragma mark NSTextListElement

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextListElement : NSTextParagraph
#pragma mark Initializer
// Designated initializer. Initializes 2 types of NSTextListElement: a standard list item and nesting parent element. Either of contents, markerAttributes, or childElements must be non-nil. Clients should typically use one of 2 factory methods below for instantiating with a specific type. When markerAttributes!=nil, it will be used to format the marker; otherwise, it is derived from contents.
- (instancetype)initWithParentElement:(nullable NSTextListElement *)parent textList:(NSTextList *)textList contents:(nullable NSAttributedString *)contents markerAttributes:(nullable NSDictionary<NSAttributedStringKey, id> *)markerAttributes childElements:(nullable NSArray<NSTextListElement *> *)children NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithAttributedString:(nullable NSAttributedString *)attributedString NS_UNAVAILABLE;

// Instantiates a standard text list.
+ (instancetype)textListElementWithContents:(NSAttributedString *)contents markerAttributes:(nullable NSDictionary<NSAttributedStringKey, id> *)markerAttributes textList:(NSTextList *)textList childElements:(nullable NSArray<NSTextListElement *> *)children;

// Returns an instance with childElements without contents. Returns nil if childElements.count == 0. nestingLevel specifies the number of shifts represented by the tree elements returned. Raises an exception when nestingLevel < 0. textList specifies NSTextList used by the new instance.
+ (nullable instancetype)textListElementWithChildElements:(NSArray<NSTextListElement *> *)children textList:(NSTextList *)textList nestingLevel:(NSInteger)nestingLevel;

#pragma mark Properties
@property (readonly, strong) NSTextList *textList;

// Element contents
@property (nullable, readonly, strong) NSAttributedString *contents; // The text list element contents without markers and formatting.

@property (nullable, readonly, strong) NSDictionary<NSAttributedStringKey, id> *markerAttributes; // Attributes defining the text formatting of marker string inside attributedString.

@property (strong, readonly) NSAttributedString *attributedString; // The contents intended to be displayed. Derived from contents/textList configured with the text list element's position inside the tree. It is overriding its superclass implementation, NSTextParagraph.attributedString

#pragma mark Child Elements
// NSTextListElement has children of the same type.
@property (readonly, copy) NSArray<NSTextListElement *> *childElements;

// NSTextListElement has the parent of the same type.
@property (nullable, readonly, weak) NSTextListElement *parentElement;
@end
 
NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIFoundation/NSTextListElement.h>
#endif
