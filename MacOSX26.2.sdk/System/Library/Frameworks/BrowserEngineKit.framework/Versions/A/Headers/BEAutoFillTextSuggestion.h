//
//  BEAutofillTextSuggestion.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <BrowserEngineKit/BETextSuggestion.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BEAutoFillTextSuggestion : BETextSuggestion

/**
 *  Mapping of UITextContentType to String for AutoFill insertion values
 */
@property (nonatomic, copy, readonly) NSDictionary<UITextContentType, NSString *> *contents;

- (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // BROWSERENGINEKIT_HAS_UIVIEW
