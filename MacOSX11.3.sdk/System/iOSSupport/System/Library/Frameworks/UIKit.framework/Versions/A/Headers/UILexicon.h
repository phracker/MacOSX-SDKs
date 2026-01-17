#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UILexicon.h>)
//
//  UILexicon.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>


NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos) @interface UILexiconEntry : NSObject <NSCopying>
// -documentText returns the intended text to be inserted into the document for a given -userInput.
// -userInput represents the expected typed string, which need not match the actual typed string.
// for example, if the -documentText were "iPhone", the corresponding -userInput could be "iphone"
// -the documentText may also be in a different text script from the -userInput
@property (nonatomic, readonly) NSString *documentText;
@property (nonatomic, readonly) NSString *userInput;
@end

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos) @interface UILexicon : NSObject <NSCopying>
@property (nonatomic, readonly) NSArray<UILexiconEntry *> *entries;
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UILexicon.h>
#endif
