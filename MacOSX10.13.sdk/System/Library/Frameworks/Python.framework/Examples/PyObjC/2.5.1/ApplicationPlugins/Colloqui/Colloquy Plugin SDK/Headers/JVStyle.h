#import <Foundation/NSObject.h>

@class NSBundle;
@class NSDictionary;
@class NSArray;
@class NSSet;
@class NSString;
@class NSURL;

extern NSString *JVStylesScannedNotification;
extern NSString *JVDefaultStyleChangedNotification;
extern NSString *JVDefaultStyleVariantChangedNotification;
extern NSString *JVNewStyleVariantAddedNotification;
extern NSString *JVStyleVariantChangedNotification;

@interface JVStyle : NSObject {
	NSBundle *_bundle;
	NSDictionary *_parameters;
	NSArray *_styleOptions;
	NSArray *_variants;
	NSArray *_userVariants;
	void *_XSLStyle; /* xsltStylesheet */
	BOOL _releasing;
}
+ (void) scanForStyles;
+ (NSSet *) styles;
+ (id) styleWithIdentifier:(NSString *) identifier;
+ (id) newWithBundle:(NSBundle *) bundle;

+ (id) defaultStyle;
+ (void) setDefaultStyle:(JVStyle *) style;

- (id) initWithBundle:(NSBundle *) bundle;

- (void) unlink;
- (void) reload;
- (BOOL) isCompliant;

- (NSBundle *) bundle;
- (NSString *) identifier;

- (NSString *) transformXML:(NSString *) xml withParameters:(NSDictionary *) parameters;
- (NSString *) transformXMLDocument:(/* xmlDoc */ void *) document withParameters:(NSDictionary *) parameters;

- (NSComparisonResult) compare:(JVStyle *) style;
- (NSString *) displayName;

- (NSString *) mainVariantDisplayName;
- (NSArray *) variantStyleSheetNames;
- (NSArray *) userVariantStyleSheetNames;
- (BOOL) isUserVariantName:(NSString *) name;
- (NSString *) defaultVariantName;
- (void) setDefaultVariantName:(NSString *) name;

- (NSArray *) styleSheetOptions;

- (void) setMainParameters:(NSDictionary *) parameters;
- (NSDictionary *) mainParameters;

- (NSURL *) baseLocation;
- (NSURL *) mainStyleSheetLocation;
- (NSURL *) variantStyleSheetLocationWithName:(NSString *) name;
- (NSString *) XMLStyleSheetFilePath;
- (NSString *) previewTranscriptFilePath;
- (NSString *) headerFilePath;

- (NSString *) contentsOfMainStyleSheet;
- (NSString *) contentsOfVariantStyleSheetWithName:(NSString *) name;
- (NSString *) contentsOfHeaderFile;
@end