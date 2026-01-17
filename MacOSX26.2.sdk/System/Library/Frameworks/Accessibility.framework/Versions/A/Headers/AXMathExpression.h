//
//  AXMathExpression.h
//  Accessibility
//

#import <Foundation/Foundation.h>
#import <Accessibility/AXFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 AXMathExpression provides an interface for returning a hierarchical, formatted math expression for assistive technologies to output, using either speech or Braille.
*/

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpression : NSObject
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionNumber : AXMathExpression
- (instancetype)initWithContent:(NSString *)content;
@property(nonatomic, readonly) NSString *content;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionIdentifier : AXMathExpression
- (instancetype)initWithContent:(NSString *)content;
@property(nonatomic, readonly) NSString *content;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionOperator : AXMathExpression
- (instancetype)initWithContent:(NSString *)content;
@property(nonatomic, readonly) NSString *content;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionText : AXMathExpression
- (instancetype)initWithContent:(NSString *)content;
@property(nonatomic, readonly) NSString *content;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionFenced : AXMathExpression
- (instancetype)initWithExpressions:(NSArray<AXMathExpression *> *)expressions openString:(NSString *)openString closeString:(NSString *)closeString;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *expressions;
@property(nonatomic, readonly) NSString *openString;
@property(nonatomic, readonly) NSString *closeString;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionRow : AXMathExpression
- (instancetype)initWithExpressions:(NSArray<AXMathExpression *> *)expressions;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *expressions;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionTable : AXMathExpression
- (instancetype)initWithExpressions:(NSArray<AXMathExpression *> *)expressions;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *expressions;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionTableRow : AXMathExpression
- (instancetype)initWithExpressions:(NSArray<AXMathExpression *> *)expressions;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *expressions;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionTableCell : AXMathExpression
- (instancetype)initWithExpressions:(NSArray<AXMathExpression *> *)expressions;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *expressions;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionUnderOver : AXMathExpression
- (instancetype)initWithBaseExpression:(AXMathExpression *)baseExpression underExpression:(AXMathExpression *)underExpression overExpression:(AXMathExpression *)overExpression;
@property(nonatomic, readonly) AXMathExpression *baseExpression;
@property(nonatomic, readonly) AXMathExpression *underExpression;
@property(nonatomic, readonly) AXMathExpression *overExpression;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionSubSuperscript : AXMathExpression
- (instancetype)initWithBaseExpression:(NSArray<AXMathExpression *> *)baseExpression subscriptExpressions:(NSArray<AXMathExpression *> *)subscriptExpressions superscriptExpressions:(NSArray<AXMathExpression *> *)superscriptExpressions;
@property(nonatomic, readonly) AXMathExpression *baseExpression;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *subscriptExpressions;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *superscriptExpressions;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionFraction : AXMathExpression
- (instancetype)initWithNumeratorExpression:(AXMathExpression *)numeratorExpression denimonatorExpression:(AXMathExpression *)denimonatorExpression;
@property(nonatomic, readonly) AXMathExpression *numeratorExpression;
@property(nonatomic, readonly) AXMathExpression *denimonatorExpression;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionMultiscript : AXMathExpression
- (instancetype)initWithBaseExpression:(AXMathExpression *)baseExpression prescriptExpressions:(NSArray<AXMathExpressionSubSuperscript *> *)prescriptExpressions postscriptExpressions:(NSArray<AXMathExpressionSubSuperscript *> *)postscriptExpressions;
@property(nonatomic, readonly) AXMathExpression *baseExpression;
@property(nonatomic, readonly) NSArray<AXMathExpressionSubSuperscript *> *prescriptExpressions;
@property(nonatomic, readonly) NSArray<AXMathExpressionSubSuperscript *> *postscriptExpressions;
@end

API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2))
@interface AXMathExpressionRoot : AXMathExpression
- (instancetype)initWithRadicandExpressions:(NSArray<AXMathExpression *> *)radicandExpressions rootIndexExpression:(AXMathExpression *)rootIndexExpression;
@property(nonatomic, readonly) NSArray<AXMathExpression *> *radicandExpressions;
@property(nonatomic, readonly) AXMathExpression *rootIndexExpression;
@end

@protocol AXMathExpressionProvider <NSObject>

// Implement this method on an accessibility object for it to return a formatted math expression to be output.
- (nullable AXMathExpression *)accessibilityMathExpression API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2));

@end

NS_ASSUME_NONNULL_END
