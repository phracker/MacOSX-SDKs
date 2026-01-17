//
//  CLKComplicationTemplate.h
//  ClockKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClockKit/CLKDefines.h>

@class CLKTextProvider;
@class CLKImageProvider;
@class UIColor;

@class CLKGaugeProvider;
@class CLKFullColorImageProvider;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplate : NSObject <NSCopying>

- (instancetype)init API_DEPRECATED("Initializing a template without parameters is deprecated in watchOS 7.0. Use an init with parameters instead.", watchos(2.0, 7.0), ios(9.0, 14.0));
+ (instancetype)new API_DEPRECATED("Creating a template without parameters is deprecated in watchOS 7.0. Use a factory method with parameters instead.", watchos(2.0, 7.0), ios(9.0, 14.0));

@property (nonatomic, copy, nullable) UIColor *tintColor;

@end


#pragma mark - Modular Small

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularSmallSimpleText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularSmallSimpleImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularSmallRingText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                        fillFraction:(float)fillFraction
                           ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                            fillFraction:(float)fillFraction
                               ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularSmallRingImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider
                         fillFraction:(float)fillFraction
                            ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider
                             fillFraction:(float)fillFraction
                                ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularSmallStackText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *line1TextProvider;
@property (nonatomic, copy) CLKTextProvider *line2TextProvider;

@property (nonatomic) BOOL highlightLine2;

- (instancetype)initWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                        line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                            line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularSmallStackImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *line1ImageProvider;
@property (nonatomic, copy) CLKTextProvider *line2TextProvider;

@property (nonatomic) BOOL highlightLine2;

- (instancetype)initWithLine1ImageProvider:(CLKImageProvider *)line1ImageProvider
                         line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1ImageProvider:(CLKImageProvider *)line1ImageProvider
                             line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularSmallColumnsText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *row1Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row1Column2TextProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column2TextProvider;

@property (nonatomic) CLKComplicationColumnAlignment column2Alignment;
@property (nonatomic) BOOL highlightColumn2;

- (instancetype)initWithRow1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                        row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                        row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                        row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithRow1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                            row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                            row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                            row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Modular Large

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularLargeStandardBody : CLKComplicationTemplate

@property (nonatomic, copy, nullable) CLKImageProvider *headerImageProvider;
@property (nonatomic, copy) CLKTextProvider *headerTextProvider;
@property (nonatomic, copy) CLKTextProvider *body1TextProvider;
@property (nonatomic, copy, nullable) CLKTextProvider *body2TextProvider; // optional. if omitted, the first line of body text will be allowed to wrap.

- (instancetype)initWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                         body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                         body1TextProvider:(CLKTextProvider *)body1TextProvider
                         body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderImageProvider:(nullable CLKImageProvider *)headerImageProvider
                         headerTextProvider:(CLKTextProvider *)headerTextProvider
                          body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderImageProvider:(nullable CLKImageProvider *)headerImageProvider
                         headerTextProvider:(CLKTextProvider *)headerTextProvider
                          body1TextProvider:(CLKTextProvider *)body1TextProvider
                          body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                             body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                             body1TextProvider:(CLKTextProvider *)body1TextProvider
                             body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderImageProvider:(nullable CLKImageProvider *)headerImageProvider
                             headerTextProvider:(CLKTextProvider *)headerTextProvider
                              body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderImageProvider:(nullable CLKImageProvider *)headerImageProvider
                             headerTextProvider:(CLKTextProvider *)headerTextProvider
                              body1TextProvider:(CLKTextProvider *)body1TextProvider
                              body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularLargeTallBody : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *headerTextProvider;
@property (nonatomic, copy) CLKTextProvider *bodyTextProvider;

- (instancetype)initWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                          bodyTextProvider:(CLKTextProvider *)bodyTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                              bodyTextProvider:(CLKTextProvider *)bodyTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularLargeTable : CLKComplicationTemplate

@property (nonatomic, copy, nullable) CLKImageProvider *headerImageProvider;
@property (nonatomic, copy) CLKTextProvider *headerTextProvider;
@property (nonatomic, copy) CLKTextProvider *row1Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row1Column2TextProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column2TextProvider;

@property (nonatomic) CLKComplicationColumnAlignment column2Alignment;

- (instancetype)initWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                   row1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                   row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                   row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                   row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderImageProvider:(nullable CLKImageProvider *)headerImageProvider
                         headerTextProvider:(CLKTextProvider *)headerTextProvider
                    row1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                    row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                    row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                    row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                       row1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                       row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                       row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                       row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderImageProvider:(nullable CLKImageProvider *)headerImageProvider
                             headerTextProvider:(CLKTextProvider *)headerTextProvider
                        row1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                        row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                        row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                        row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateModularLargeColumns : CLKComplicationTemplate

@property (nonatomic, copy, nullable) CLKImageProvider *row1ImageProvider;
@property (nonatomic, copy) CLKTextProvider *row1Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row1Column2TextProvider;
@property (nonatomic, copy, nullable) CLKImageProvider *row2ImageProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column2TextProvider;
@property (nonatomic, copy, nullable) CLKImageProvider *row3ImageProvider;
@property (nonatomic, copy) CLKTextProvider *row3Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row3Column2TextProvider;

@property (nonatomic) CLKComplicationColumnAlignment column2Alignment;

- (instancetype)initWithRow1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                        row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                        row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                        row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider
                        row3Column1TextProvider:(CLKTextProvider *)row3Column1TextProvider
                        row3Column2TextProvider:(CLKTextProvider *)row3Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithRow1ImageProvider:(nullable CLKImageProvider *)row1ImageProvider
                  row1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                  row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                        row2ImageProvider:(nullable CLKImageProvider *)row2ImageProvider
                  row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                  row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider
                        row3ImageProvider:(nullable CLKImageProvider *)row3ImageProvider
                  row3Column1TextProvider:(CLKTextProvider *)row3Column1TextProvider
                  row3Column2TextProvider:(CLKTextProvider *)row3Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithRow1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                            row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                            row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                            row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider
                            row3Column1TextProvider:(CLKTextProvider *)row3Column1TextProvider
                            row3Column2TextProvider:(CLKTextProvider *)row3Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithRow1ImageProvider:(nullable CLKImageProvider *)row1ImageProvider
                      row1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                      row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                            row2ImageProvider:(nullable CLKImageProvider *)row2ImageProvider
                      row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                      row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider
                            row3ImageProvider:(nullable CLKImageProvider *)row3ImageProvider
                      row3Column1TextProvider:(CLKTextProvider *)row3Column1TextProvider
                      row3Column2TextProvider:(CLKTextProvider *)row3Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Utilitarian Small

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateUtilitarianSmallSquare : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");


@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateUtilitarianSmallRingText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                        fillFraction:(float)fillFraction
                           ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                            fillFraction:(float)fillFraction
                               ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateUtilitarianSmallRingImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider
                         fillFraction:(float)fillFraction
                            ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider
                             fillFraction:(float)fillFraction
                                ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Utilitarian Small  &  Utilitarian Small Flat

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateUtilitarianSmallFlat : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;
@property (nonatomic, copy, nullable) CLKImageProvider *imageProvider;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                       imageProvider:(nullable CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                           imageProvider:(nullable CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Utilitarian Large

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateUtilitarianLargeFlat : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;
@property (nonatomic, copy, nullable) CLKImageProvider *imageProvider;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                       imageProvider:(nullable CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                           imageProvider:(nullable CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Circular Small

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateCircularSmallSimpleText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateCircularSmallSimpleImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateCircularSmallRingText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                        fillFraction:(float)fillFraction
                           ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                            fillFraction:(float)fillFraction
                               ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateCircularSmallRingImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider
                         fillFraction:(float)fillFraction
                            ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider
                             fillFraction:(float)fillFraction
                                ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateCircularSmallStackText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *line1TextProvider;
@property (nonatomic, copy) CLKTextProvider *line2TextProvider;

- (instancetype)initWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                        line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                            line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateCircularSmallStackImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *line1ImageProvider;
@property (nonatomic, copy) CLKTextProvider  *line2TextProvider;

- (instancetype)initWithLine1ImageProvider:(CLKImageProvider *)line1ImageProvider
                         line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1ImageProvider:(CLKImageProvider *)line1ImageProvider
                             line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Extra Large

API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateExtraLargeSimpleText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateExtraLargeSimpleImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateExtraLargeRingText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                        fillFraction:(float)fillFraction
                           ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                            fillFraction:(float)fillFraction
                               ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateExtraLargeRingImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *imageProvider;
@property (nonatomic) float fillFraction;
@property (nonatomic) CLKComplicationRingStyle ringStyle;

- (instancetype)initWithImageProvider:(CLKImageProvider *)imageProvider
                         fillFraction:(float)fillFraction
                            ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKImageProvider *)imageProvider
                             fillFraction:(float)fillFraction
                                ringStyle:(CLKComplicationRingStyle)ringStyle API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateExtraLargeStackText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *line1TextProvider;
@property (nonatomic, copy) CLKTextProvider *line2TextProvider;

@property (nonatomic) BOOL highlightLine2;

- (instancetype)initWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                        line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                            line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateExtraLargeStackImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKImageProvider *line1ImageProvider;
@property (nonatomic, copy) CLKTextProvider *line2TextProvider;

@property (nonatomic) BOOL highlightLine2;

- (instancetype)initWithLine1ImageProvider:(CLKImageProvider *)line1ImageProvider
                         line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1ImageProvider:(CLKImageProvider *)line1ImageProvider
                             line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateExtraLargeColumnsText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *row1Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row1Column2TextProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column1TextProvider;
@property (nonatomic, copy) CLKTextProvider *row2Column2TextProvider;

@property (nonatomic) CLKComplicationColumnAlignment column2Alignment;
@property (nonatomic) BOOL highlightColumn2;

- (instancetype)initWithRow1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                        row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                        row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                        row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithRow1Column1TextProvider:(CLKTextProvider *)row1Column1TextProvider
                            row1Column2TextProvider:(CLKTextProvider *)row1Column2TextProvider
                            row2Column1TextProvider:(CLKTextProvider *)row2Column1TextProvider
                            row2Column2TextProvider:(CLKTextProvider *)row2Column2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Graphic Corner

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCornerGaugeText : CLKComplicationTemplate

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy, nullable) CLKTextProvider *leadingTextProvider; // Supports multi-color text.
@property (nonatomic, copy, nullable) CLKTextProvider *trailingTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *outerTextProvider;

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                    outerTextProvider:(CLKTextProvider *)outerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                  leadingTextProvider:(nullable CLKTextProvider *)leadingTextProvider
                 trailingTextProvider:(nullable CLKTextProvider *)trailingTextProvider
                    outerTextProvider:(CLKTextProvider *)outerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_NAME(init(gaugeProvider:leadingTextProvider:trailingTextProvider:outerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                        outerTextProvider:(CLKTextProvider *)outerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                      leadingTextProvider:(nullable CLKTextProvider *)leadingTextProvider
                     trailingTextProvider:(nullable CLKTextProvider *)trailingTextProvider
                        outerTextProvider:(CLKTextProvider *)outerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCornerGaugeImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy, nullable) CLKTextProvider *leadingTextProvider; // Supports multi-color text.
@property (nonatomic, copy, nullable) CLKTextProvider *trailingTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                        imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                  leadingTextProvider:(nullable CLKTextProvider *)leadingTextProvider
                 trailingTextProvider:(nullable CLKTextProvider *)trailingTextProvider
                        imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_NAME(init(gaugeProvider:leadingTextProvider:trailingTextProvider:imageProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                            imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                      leadingTextProvider:(nullable CLKTextProvider *)leadingTextProvider
                     trailingTextProvider:(nullable CLKTextProvider *)trailingTextProvider
                            imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCornerTextImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                       imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                            imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCornerStackText : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *innerTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *outerTextProvider;

- (instancetype)initWithInnerTextProvider:(CLKTextProvider *)innerTextProvider
                        outerTextProvider:(CLKTextProvider *)outerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithInnerTextProvider:(CLKTextProvider *)innerTextProvider
                            outerTextProvider:(CLKTextProvider *)outerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCornerCircularImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Graphic Circular

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircular : CLKComplicationTemplate
@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularImage : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularOpenGaugeRangeText : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKTextProvider *leadingTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *trailingTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                  leadingTextProvider:(CLKTextProvider *)leadingTextProvider
                 trailingTextProvider:(CLKTextProvider *)trailingTextProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_NAME(init(gaugeProvider:leadingTextProvider:trailingTextProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                      leadingTextProvider:(CLKTextProvider *)leadingTextProvider
                     trailingTextProvider:(CLKTextProvider *)trailingTextProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularOpenGaugeSimpleText : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKTextProvider *bottomTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                   bottomTextProvider:(CLKTextProvider *)bottomTextProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_NAME(init(gaugeProvider:bottomTextProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                       bottomTextProvider:(CLKTextProvider *)bottomTextProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularOpenGaugeImage : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKFullColorImageProvider *bottomImageProvider;
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                  bottomImageProvider:(CLKFullColorImageProvider *)bottomImageProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_NAME(init(gaugeProvider:bottomImageProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                      bottomImageProvider:(CLKFullColorImageProvider *)bottomImageProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularClosedGaugeText : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_NAME(init(gaugeProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularClosedGaugeImage : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                        imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                            imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(6.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularStackText : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKTextProvider *line1TextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *line2TextProvider; // Supports multi-color text.

- (instancetype)initWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                        line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                            line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(6.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicCircularStackImage : CLKComplicationTemplateGraphicCircular

@property (nonatomic, copy) CLKFullColorImageProvider *line1ImageProvider;
@property (nonatomic, copy) CLKTextProvider *line2TextProvider; // Supports multi-color text.

- (instancetype)initWithLine1ImageProvider:(CLKFullColorImageProvider *)line1ImageProvider
                         line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithLine1ImageProvider:(CLKFullColorImageProvider *)line1ImageProvider
                             line2TextProvider:(CLKTextProvider *)line2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Graphic Bezel

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicBezelCircularText : CLKComplicationTemplate

@property (nonatomic, copy) CLKComplicationTemplateGraphicCircular *circularTemplate;
@property (nonatomic, copy, nullable) CLKTextProvider *textProvider;

- (instancetype)initWithCircularTemplate:(CLKComplicationTemplateGraphicCircular *)circularTemplate API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithCircularTemplate:(CLKComplicationTemplateGraphicCircular *)circularTemplate
                            textProvider:(nullable CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithCircularTemplate:(CLKComplicationTemplateGraphicCircular *)circularTemplate API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithCircularTemplate:(CLKComplicationTemplateGraphicCircular *)circularTemplate
                                textProvider:(nullable CLKTextProvider *)textProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Graphic Rectangular

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicRectangularFullImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithImageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicRectangularLargeImage : CLKComplicationTemplate

@property (nonatomic, copy) CLKTextProvider *textProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithTextProvider:(CLKTextProvider *)textProvider
                       imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithTextProvider:(CLKTextProvider *)textProvider
                            imageProvider:(CLKFullColorImageProvider *)imageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicRectangularStandardBody : CLKComplicationTemplate

@property (nonatomic, copy, nullable) CLKFullColorImageProvider *headerImageProvider;
@property (nonatomic, copy) CLKTextProvider *headerTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *body1TextProvider; // Supports multi-color text.
// Optional. if omitted, the first line of body text will be allowed to wrap.
@property (nonatomic, copy, nullable) CLKTextProvider *body2TextProvider; // Supports multi-color text.

- (instancetype)initWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                         body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                         body1TextProvider:(CLKTextProvider *)body1TextProvider
                         body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderImageProvider:(nullable CLKFullColorImageProvider *)headerImageProvider
                         headerTextProvider:(CLKTextProvider *)headerTextProvider
                          body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderImageProvider:(nullable CLKFullColorImageProvider *)headerImageProvider
                         headerTextProvider:(CLKTextProvider *)headerTextProvider
                          body1TextProvider:(CLKTextProvider *)body1TextProvider
                          body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                             body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                             body1TextProvider:(CLKTextProvider *)body1TextProvider
                             body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderImageProvider:(nullable CLKFullColorImageProvider *)headerImageProvider
                             headerTextProvider:(CLKTextProvider *)headerTextProvider
                              body1TextProvider:(CLKTextProvider *)body1TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderImageProvider:(nullable CLKFullColorImageProvider *)headerImageProvider
                             headerTextProvider:(CLKTextProvider *)headerTextProvider
                              body1TextProvider:(CLKTextProvider *)body1TextProvider
                              body2TextProvider:(nullable CLKTextProvider *)body2TextProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicRectangularTextGauge : CLKComplicationTemplate

@property (nonatomic, copy, nullable) CLKFullColorImageProvider *headerImageProvider;
@property (nonatomic, copy) CLKTextProvider *headerTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *body1TextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;

- (instancetype)initWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                         body1TextProvider:(CLKTextProvider *)body1TextProvider
                             gaugeProvider:(CLKGaugeProvider *)gaugeProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithHeaderImageProvider:(nullable CLKFullColorImageProvider *)headerImageProvider
                         headerTextProvider:(CLKTextProvider *)headerTextProvider
                          body1TextProvider:(CLKTextProvider *)body1TextProvider
                              gaugeProvider:(CLKGaugeProvider *)gaugeProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

+ (instancetype)templateWithHeaderTextProvider:(CLKTextProvider *)headerTextProvider
                             body1TextProvider:(CLKTextProvider *)body1TextProvider
                                 gaugeProvider:(CLKGaugeProvider *)gaugeProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

+ (instancetype)templateWithHeaderImageProvider:(nullable CLKFullColorImageProvider *)headerImageProvider
                             headerTextProvider:(CLKTextProvider *)headerTextProvider
                              body1TextProvider:(CLKTextProvider *)body1TextProvider
                                  gaugeProvider:(CLKGaugeProvider *)gaugeProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use initializer");

@end


#pragma mark - Graphic Extra Large Circular

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircular : CLKComplicationTemplate
@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularImage : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithImageProvider:(CLKFullColorImageProvider *)imageProvider;

+ (instancetype)templateWithImageProvider:(CLKFullColorImageProvider *)imageProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularOpenGaugeRangeText : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKTextProvider *leadingTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *trailingTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                  leadingTextProvider:(CLKTextProvider *)leadingTextProvider
                 trailingTextProvider:(CLKTextProvider *)trailingTextProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_NAME(init(gaugeProvider:leadingTextProvider:trailingTextProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                      leadingTextProvider:(CLKTextProvider *)leadingTextProvider
                     trailingTextProvider:(CLKTextProvider *)trailingTextProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularOpenGaugeSimpleText : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKTextProvider *bottomTextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                   bottomTextProvider:(CLKTextProvider *)bottomTextProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_NAME(init(gaugeProvider:bottomTextProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                       bottomTextProvider:(CLKTextProvider *)bottomTextProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularOpenGaugeImage : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKFullColorImageProvider *bottomImageProvider;
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                  bottomImageProvider:(CLKFullColorImageProvider *)bottomImageProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_NAME(init(gaugeProvider:bottomImageProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                      bottomImageProvider:(CLKFullColorImageProvider *)bottomImageProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularClosedGaugeText : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKTextProvider *centerTextProvider; // Supports multi-color text.

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                   centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_NAME(init(gaugeProvider:centerTextProvider:));

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                       centerTextProvider:(CLKTextProvider *)centerTextProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularClosedGaugeImage : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKGaugeProvider *gaugeProvider;
@property (nonatomic, copy) CLKFullColorImageProvider *imageProvider;

- (instancetype)initWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                        imageProvider:(CLKFullColorImageProvider *)imageProvider;

+ (instancetype)templateWithGaugeProvider:(CLKGaugeProvider *)gaugeProvider
                            imageProvider:(CLKFullColorImageProvider *)imageProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularStackText : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKTextProvider *line1TextProvider; // Supports multi-color text.
@property (nonatomic, copy) CLKTextProvider *line2TextProvider; // Supports multi-color text.

- (instancetype)initWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                        line2TextProvider:(CLKTextProvider *)line2TextProvider;

+ (instancetype)templateWithLine1TextProvider:(CLKTextProvider *)line1TextProvider
                            line2TextProvider:(CLKTextProvider *)line2TextProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTemplateGraphicExtraLargeCircularStackImage : CLKComplicationTemplateGraphicExtraLargeCircular

@property (nonatomic, copy) CLKFullColorImageProvider *line1ImageProvider;
@property (nonatomic, copy) CLKTextProvider *line2TextProvider; // Supports multi-color text.

- (instancetype)initWithLine1ImageProvider:(CLKFullColorImageProvider *)line1ImageProvider
                         line2TextProvider:(CLKTextProvider *)line2TextProvider;

+ (instancetype)templateWithLine1ImageProvider:(CLKFullColorImageProvider *)line1ImageProvider
                             line2TextProvider:(CLKTextProvider *)line2TextProvider NS_SWIFT_UNAVAILABLE("Use initializer");

@end

NS_ASSUME_NONNULL_END
