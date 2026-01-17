#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextElement.h>)
//
//  NSTextElement.h
//  Text Kit
//
//  Copyright (c) 2018-2025, Apple Inc. All rights reserved.
//


#import <Foundation/NSArray.h>

@class NSTextRange;
@class NSTextContentManager;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// NSTextElement is an abstract base class for representing the smallest text layout unit typically paragraphs, tables, or attachments. A text element is associated with an NSTextContentManager.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextElement : NSObject
#pragma mark Initialization
- (instancetype)initWithTextContentManager:(nullable NSTextContentManager *)textContentManager NS_DESIGNATED_INITIALIZER;

#pragma mark Properties
// Returns the owner NSTextContentManager. A text element can migrate between text content managers.
@property (nullable, weak) NSTextContentManager *textContentManager;

// Represents the range of the element inside the document.
@property (nullable, strong) NSTextRange *elementRange;

#pragma mark Child Elements
// A concrete NSTextElement subclass can be structured in a tree. An element can have zero or more child elements. This section provides interface for supporting such a configuration.
// Returns an array of children. The array can contain zero or more elements.
@property (readonly, copy) NSArray<__kindof NSTextElement *> *childElements API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

// Returns the parent element if the receiver is a child.
@property (nullable, readonly, weak) __kindof NSTextElement *parentElement API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

// Returns YES if it is an element represented in text layout. It is enumerated by NSTextContentManager.
@property (readonly) BOOL isRepresentedElement API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

#pragma mark NSTextParagraph
// NSTextParagraph represents a single paragraph backed by NSAttributedString as the contents.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextParagraph : NSTextElement
#pragma mark Initialization
- (instancetype)initWithAttributedString:(nullable NSAttributedString *)attributedString NS_DESIGNATED_INITIALIZER;

#pragma mark Contents
@property (strong, readonly) NSAttributedString *attributedString;

// The paragraph ranges are derived from elementRange and attributedString.
@property (nullable, strong, readonly) NSTextRange *paragraphContentRange;
@property (nullable, strong, readonly) NSTextRange *paragraphSeparatorRange;
@end
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextElement.h>
#endif
