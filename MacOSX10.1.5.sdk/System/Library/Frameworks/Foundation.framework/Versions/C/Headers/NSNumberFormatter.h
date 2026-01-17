/*	NSNumberFormatter.h
	Copyright 1996-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>

@class NSDecimalNumber, NSAttributedString, NSDictionary, NSString;
@class NSDecimalNumberHandler;

@interface NSNumberFormatter : NSFormatter {
@private
    NSString               *_negativeFormat;
    NSString               *_positiveFormat;
    NSDictionary           *_negativeAttributes;
    NSDictionary    	   *_positiveAttributes;
    NSAttributedString     *_attributedStringForZero;
    NSAttributedString     *_attributedStringForNil;
    NSAttributedString     *_attributedStringForNotANumber; 
    NSDecimalNumber        *_minimum;
    NSDecimalNumber        *_maximum;
    NSDecimalNumberHandler *_roundingBehavior;
    NSString               *_decimalSeparator;
    NSString               *_thousandSeparator;
    void                   *_private;
    struct {
	unsigned int thousandSeparators:1;
	unsigned int localizesFormat:1;
	unsigned int allowsFloats:1;
	unsigned int RESERVED:29;
    } _flags;
    
    void *_reserved;
}

- (NSString *)negativeFormat;
- (void)setNegativeFormat:(NSString *)format;
- (NSDictionary *)textAttributesForNegativeValues;
- (void)setTextAttributesForNegativeValues:(NSDictionary *)newAttributes;

- (NSString *)positiveFormat;
- (void)setPositiveFormat:(NSString *)format;
- (NSDictionary *)textAttributesForPositiveValues;
- (void)setTextAttributesForPositiveValues:(NSDictionary *)newAttributes;

- (NSAttributedString *)attributedStringForZero;
- (void)setAttributedStringForZero:(NSAttributedString *)newAttributedString;
- (NSAttributedString *)attributedStringForNil;
- (void)setAttributedStringForNil:(NSAttributedString *)newAttributedString;
- (NSAttributedString *)attributedStringForNotANumber;
- (void)setAttributedStringForNotANumber:(NSAttributedString *)newAttributedString;

- (NSString *)format;
- (void)setFormat:(NSString *)format;

- (BOOL)hasThousandSeparators;
- (void)setHasThousandSeparators:(BOOL)flag;
- (NSString *)thousandSeparator;
- (void)setThousandSeparator:(NSString *)newSeparator;

- (NSString *)decimalSeparator;
- (void)setDecimalSeparator:(NSString *)newSeparator;

- (BOOL)localizesFormat;
- (void)setLocalizesFormat:(BOOL)flag;

- (BOOL)allowsFloats;
- (void)setAllowsFloats:(BOOL)flag;

- (NSDecimalNumberHandler *)roundingBehavior;
- (void)setRoundingBehavior:(NSDecimalNumberHandler *)newRoundingBehavior;

- (NSDecimalNumber *)minimum;
- (void)setMinimum:(NSDecimalNumber *)aMinimum;
- (NSDecimalNumber *)maximum;
- (void)setMaximum:(NSDecimalNumber *)aMaximum;

@end

