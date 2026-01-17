//
//  BETextDocumentRequest.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITextInput.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSInteger, BETextDocumentRequestOptions) {
    BETextDocumentOptionNone = 0,
    BETextDocumentOptionText = 1 << 0,
    BETextDocumentOptionAttributedText = 1 << 1,
    BETextDocumentOptionTextRects = 1 << 2,
    BETextDocumentOptionMarkedTextRects = 1 << 5,
    BETextDocumentOptionAutocorrectedRanges = 1 << 7,
} NS_SWIFT_NAME(BETextDocumentRequest.Options) BROWSERENGINE_TEXTINPUT_AVAILABILITY;

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BETextDocumentRequest : NSObject

/**
 *  Represents the information that the system is requesting
 */
@property (nonatomic, assign) BETextDocumentRequestOptions options;

/**
 *  Represents the granularity units for the scope of the request
 */
@property (nonatomic, assign) UITextGranularity surroundingGranularity;

/**
 *  Represents the scope of the request as a count of granularity units specified in `surroundingGranularity`
 */
@property (nonatomic, assign) NSInteger granularityCount;

- (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // BROWSERENGINEKIT_HAS_UIVIEW
