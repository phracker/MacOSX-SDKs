/*
	File:  AVTextStyleRule.h

	Framework:  AVFoundation
 
	Copyright 2012-2013 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

/*!
  @class		AVTextStyleRule

  @abstract		AVTextStyleRule represents a set of text styling attributes that can be applied to some or all of the text of legible media, such as subtitles and closed captions.
*/

@class AVTextStyleRuleInternal;

NS_CLASS_AVAILABLE(10_9, 6_0)
@interface AVTextStyleRule : NSObject <NSCopying> {
@private
	AVTextStyleRuleInternal *_textStyleRule;
}

/*!
 @method		propertyListForTextStyleRules:
 @abstract		Converts an NSArray of AVTextStyleRules into a serializable property list that can be used for persistent storage.
 @param			textStyleRules
 				An array of AVTextStyleRules.
 @result		A serializable property list.
 @discussion	For serialization utilities, see NSPropertyList.h.
*/
+ (id)propertyListForTextStyleRules:(NSArray *)textStyleRules;

/*!
 @method		textStyleRulesFromPropertyList:
 @abstract		Converts a property list into an NSArray of AVTextStyleRules.
 @param			plist
 				A property list, normally obtained previously via an invocation of +propertyListForTextStyleRules:.
 @result		An NSArray of AVTextStyleRules
*/
+ (NSArray *)textStyleRulesFromPropertyList:(id)plist;

/*!
 @method		textStyleRuleWithTextMarkupAttributes:
 @abstract		Creates an instance of AVTextStyleRule with the specified text markup attributes.
 @param			textMarkupAttributes
 				An NSDictionary with keys representing text style attributes that are specifiable in text markup. Eligible keys are defined in <CoreMedia/CMTextMarkup.h>.
 @result		An instance of AVTextStyleRule
 @discussion	Equivalent to invoking +textStyleRuleWithTextMarkupAttributes:textSelector: with a value of nil for textSelector.
*/
+ (AVTextStyleRule *)textStyleRuleWithTextMarkupAttributes:(NSDictionary *)textMarkupAttributes;

/*!
 @method		textStyleRuleWithTextMarkupAttributes:textSelector:
 @abstract		Creates an instance of AVTextStyleRule with the specified text markup attributes and an identifier for the range or ranges of text to which the attributes should be applied.
 @param			textMarkupAttributes
 				An NSDictionary with keys representing text style attributes that are specifiable in text markup. Eligible keys are defined in <CoreMedia/CMTextMarkup.h>.
 @param			textSelector
				An identifier for the range or ranges of text to which the attributes should be applied. Eligible identifiers are determined by the format and content of the legible media. A value of nil indicates that the textMarkupAttributes should be applied as default styles for all text unless overridden by content markup or other applicable text selectors.
 @result		An instance of AVTextStyleRule
*/
+ (AVTextStyleRule *)textStyleRuleWithTextMarkupAttributes:(NSDictionary *)textMarkupAttributes textSelector:(NSString *)textSelector;

/*!
 @method		initWithTextMarkupAttributes:
 @abstract		Creates an instance of AVTextStyleRule with the specified text markup attributes.
 @param			textMarkupAttributes
 				An NSDictionary with keys representing text style attributes that are specifiable in text markup. Eligible keys are defined in <CoreMedia/CMTextMarkup.h>.
 @result		An instance of AVTextStyleRule
 @discussion	Equivalent to invoking -initWithTextMarkupAttributes:textSelector: with a value of nil for textSelector.
*/
- (instancetype)initWithTextMarkupAttributes:(NSDictionary *)textMarkupAttributes;

/*!
 @method		initWithTextMarkupAttributes:textSelector:
 @abstract		Creates an instance of AVTextStyleRule with the specified text markup attributes and an identifier for the range or ranges of text to which the attributes should be applied.
 @param			textMarkupAttributes
 				An NSDictionary with keys representing text style attributes that are specifiable in text markup. Eligible keys are defined in <CoreMedia/CMTextMarkup.h>.
 @param			textSelector
				An identifier for the range or ranges of text to which the attributes should be applied. Eligible identifiers are determined by the format and content of the legible media. A value of nil indicates that the textMarkupAttributes should be applied as default styles for all text unless overridden by content markup or other applicable text selectors.
 @result		An instance of AVTextStyleRule
*/
- (instancetype)initWithTextMarkupAttributes:(NSDictionary *)textMarkupAttributes textSelector:(NSString *)textSelector;

/*!
 @property		textMarkupAttributes
 @abstract		An NSDictionary with keys representing text style attributes that are specifiable in text markup. Eligible keys and the expected types of their corresponding values are defined in <CoreMedia/CMTextMarkup.h>.
*/
@property (nonatomic, readonly) NSDictionary *textMarkupAttributes;

/*!
 @property		textSelector
 @abstract		A string that identifies the range or ranges of text to which the attributes should be applied. A value of nil indicates that the textMarkupAttributes should be applied as default styles for all text unless overridden by content markup or other applicable text selectors.
 @dicussion		The syntax of text selectors is determined by the format of the legible media. Eligible selectors may be determined by the content of the legible media (e.g. CSS selectors that are valid for a specific WebVTT document).
*/
@property (nonatomic, readonly) NSString *textSelector;

@end
