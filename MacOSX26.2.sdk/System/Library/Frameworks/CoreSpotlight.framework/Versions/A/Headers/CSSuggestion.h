//
//  CSSuggestion.h
//  CoreSpotlight
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(suggestionHighlight)
CORESPOTLIGHT_EXPORT NSAttributedStringKey const CSSuggestionHighlightAttributeName API_AVAILABLE(macos(13.0), ios(16.0)) CS_TVOS_UNAVAILABLE;

API_AVAILABLE(macos(13.0), ios(16.0)) CS_TVOS_UNAVAILABLE
typedef NS_ENUM(NSInteger, CSSuggestionKind) {
    CSSuggestionKindNone,
    CSSuggestionKindCustom,
    CSSuggestionKindDefault,
} NS_SWIFT_NAME(CSSuggestion.SuggestionKind);

API_AVAILABLE(macos(13.0), ios(16.0)) CS_TVOS_UNAVAILABLE
@interface CSSuggestion : NSObject <NSSecureCoding, NSCopying>

@property (nonnull, nonatomic, readonly) NSAttributedString *localizedAttributedSuggestion NS_REFINED_FOR_SWIFT;
@property (nonatomic, readonly) CSSuggestionKind suggestionKind;

// For suggestions that have been ranked by the query
- (NSComparisonResult)compareByRank:(CSSuggestion *)other;

- (NSComparisonResult)compare:(CSSuggestion *)other;

@end
NS_ASSUME_NONNULL_END
