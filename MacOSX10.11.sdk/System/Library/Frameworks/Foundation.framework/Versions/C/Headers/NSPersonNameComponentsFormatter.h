/*	NSPersonNameComponentsFormatter.h
	Copyright (c) 2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSPersonNameComponents.h>
#import <Foundation/NSFormatter.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSPersonNameComponentsFormatterStyle) {
    NSPersonNameComponentsFormatterStyleDefault = 0,

    /* Relies on user preferences and language defaults to display shortened form appropriate
      for display in space-constrained settings, e.g. C Darwin */
    NSPersonNameComponentsFormatterStyleShort,

    /* The minimally necessary features for differentiation in a casual setting , e.g. Charles Darwin */
    NSPersonNameComponentsFormatterStyleMedium,

    /* The fully-qualified name complete with all known components, e.g. Charles Robert Darwin, FRS */
    NSPersonNameComponentsFormatterStyleLong,

    /* The maximally-abbreviated form of a name suitable for monograms, e.g. CRD) */
    NSPersonNameComponentsFormatterStyleAbbreviated
} NS_ENUM_AVAILABLE(10_11, 9_0);

typedef NS_OPTIONS (NSUInteger, NSPersonNameComponentsFormatterOptions) {
    /* Indicates that the formatter should format the component object's phoneticRepresentation components instead of its own components.
     The developer must have populated these manually. e.g.: Developer creates components object with the following properties:
     <family:"Family", given:"Given", phoneticRepresentation:<family:"FamilyPhonetic", given:"GivenPhonetic">>.
     If this option is specified, we perform formatting operations on <family "FamilyPhonetic", given "GivenPhonetic"> instead. */
    NSPersonNameComponentsFormatterPhonetic = (1UL << 1)
} NS_ENUM_AVAILABLE(10_11, 9_0);


NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSPersonNameComponentsFormatter : NSFormatter {
@private
    id _private;
}

/* Specify the formatting style for the formatted string on an instance. ShortStyle will fall back to user preferences and language-specific defaults
 */
@property NSPersonNameComponentsFormatterStyle style;

/* Specify that the formatter should only format the components object's phoneticRepresentation
 */
@property (getter=isPhonetic) BOOL phonetic;

/* Shortcut for converting an NSPersonNameComponents object into a string without explicitly creating an instance.
    Create an instance for greater customizability.
 */
+ (NSString *)localizedStringFromPersonNameComponents:(NSPersonNameComponents *)components
                                                style:(NSPersonNameComponentsFormatterStyle)nameFormatStyle
                                              options:(NSPersonNameComponentsFormatterOptions)nameOptions;

/* Convenience method on stringForObjectValue:. Returns a string containing the formatted value of the provided components object.
 */
- (NSString *)stringFromPersonNameComponents:(NSPersonNameComponents *)components;

/* Returns attributed string with annotations for each component. For each range, attributes can be obtained by querying
    dictionary key NSPersonNameComponentKey , using NSPersonNameComponent constant values.
 */
- (NSAttributedString *)annotatedStringFromPersonNameComponents:(NSPersonNameComponents *)components;

/* NSPersonNameComponentsFormatter currently only implements formatting, not parsing. Until it implements parsing, this will always return NO.
 */
- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string errorDescription:(out NSString * __nullable * __nullable)error;

@end

// Attributed String identifier key string
FOUNDATION_EXPORT NSString * const NSPersonNameComponentKey NS_AVAILABLE(10_11, 9_0);

// Constants for attributed strings
FOUNDATION_EXPORT NSString * const NSPersonNameComponentGivenName NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentFamilyName NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentMiddleName NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentPrefix NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentSuffix NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentNickname NS_AVAILABLE(10_11, 9_0);

/* The delimiter is the character or characters used to separate name components.
 For CJK languages there is no delimiter.
 */
FOUNDATION_EXPORT NSString * const NSPersonNameComponentDelimiter NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
