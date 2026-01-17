//
//  BETextSuggestion.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

NS_ASSUME_NONNULL_BEGIN

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BETextSuggestion : NSObject

/**
 *  Initializes a new text suggestion with the given input text.
 */
- (instancetype)initWithInputText:(NSString *)inputText;

/**
 *  Text that will be inserted into the document when the user chooses the suggestion.
 */
@property (nonatomic, copy, readonly) NSString *inputText;

- (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
