//
//  AXAudiograph.h
//  AccessibilitySharedSupport
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class AXChartDescriptor;
@class AXNumericDataAxisDescriptor;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Protocols

/// Chart or graph container elements may adopt this protocol to enable Audio Graph support.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@protocol AXChart <NSObject>

@property (nonatomic, strong, nullable) AXChartDescriptor *accessibilityChartDescriptor;

@end

#pragma mark - Descriptor Objects

/// Describes a data axis for the chart (e.g. X, Y, etc.)
/// Each AXChart requires at least two AXDataAxis objects
/// to describe, at minimum, and X and a Y axis.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@protocol AXDataAxisDescriptor <NSCopying>

/// The name or title of this axis.
@property (nonatomic, copy) NSString *title;

/// An attributed version of the title of this axis.
/// When set, this will be used instead of `title`.
@property (nonatomic, copy) NSAttributedString *attributedTitle;

@end

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
typedef NS_ENUM(NSInteger, AXNumericDataAxisDescriptorScale) {
    AXScaleTypeLinear NS_SWIFT_NAME(linear) = 0,
    AXScaleTypeLog10 NS_SWIFT_NAME(log10),
    AXScaleTypeLn NS_SWIFT_NAME(ln)
} NS_SWIFT_NAME(AXNumericDataAxisDescriptor.ScaleType);

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
__attribute__((objc_subclassing_restricted))
@interface AXNumericDataAxisDescriptor : NSObject <AXDataAxisDescriptor>

/// The scale to use for this axis. This should match the visual representation in the chart.
/// If not set explicitly, this will default to `linear`.
@property (nonatomic, assign) AXNumericDataAxisDescriptorScale scaleType;

/// The minimum displayable value for the axis.
@property (nonatomic, assign) double lowerBound NS_REFINED_FOR_SWIFT;

/// The maximum displayable value for the axis.
@property (nonatomic, assign) double upperBound NS_REFINED_FOR_SWIFT;

/// Provides a value description to be spoken for a particular data value on this axis.
/// Use this to format data values to string representations that include units, dates, times, etc.
@property (nonatomic, copy) NSString *(^valueDescriptionProvider)(double);

/// The positions of any gridlines along this axis.
@property (nonatomic, copy) NSArray<NSNumber *> *gridlinePositions NS_REFINED_FOR_SWIFT;

- (instancetype)initWithTitle:(NSString *)title lowerBound:(double)lowerbound upperBound:(double)upperBound gridlinePositions:(nullable NSArray<NSNumber *> *)gridlinePositions valueDescriptionProvider:(NSString * _Nonnull (^)(double))valueDescriptionProvider NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

- (instancetype)initWithAttributedTitle:(NSAttributedString *)attributedTitle lowerBound:(double)lowerbound upperBound:(double)upperBound gridlinePositions:(nullable NSArray<NSNumber *> *)gridlinePositions valueDescriptionProvider:(NSString * _Nonnull (^)(double))valueDescriptionProvider NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface AXCategoricalDataAxisDescriptor : NSObject <AXDataAxisDescriptor>

/// The order of the category values for this axis.
/// This list should contain every possible category value for this axis, in the order they are displayed visually in the graph or legend.
/// For example, if your categorical axis represented 'blood type', and the legend contained 'AB, A, B, O' in that order,
/// you would provide an array containing "AB", "A", "B" and "O" in the same order.
@property (nonatomic, copy) NSArray<NSString *> *categoryOrder;

- (instancetype)initWithTitle:(NSString *)title categoryOrder:(NSArray<NSString *> *)categoryOrder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithAttributedTitle:(NSAttributedString *)attributedTitle categoryOrder:(NSArray<NSString *> *)categoryOrder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Describes a single data value, either numeric or categorical. Only the `number`
/// property will be used for data points in a numeric axis, and only the `category`
/// property will be used for data points in a categorical axis.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
__attribute__((objc_subclassing_restricted))
@interface AXDataPointValue : NSObject <NSCopying>

@property (nonatomic, assign) double number NS_REFINED_FOR_SWIFT;

@property (nonatomic, copy) NSString *category NS_REFINED_FOR_SWIFT;

+ (instancetype)valueWithNumber:(double)number NS_REFINED_FOR_SWIFT;

+ (instancetype)valueWithCategory:(NSString *)category NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Provides axis values for a single data point within a series.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
__attribute__((objc_subclassing_restricted))
@interface AXDataPoint : NSObject <NSCopying>

/// The x-axis value for this data point.
/// Should be a Double for a numeric x-axis or a String for a categorical x-axis.
@property (nonatomic, copy) AXDataPointValue *xValue;

/// The y-axis value for this data point.
@property (nonatomic, copy, nullable) AXDataPointValue *yValue;

/// Any additional values for additional axes for this data point.
/// These should be provided in the same order as their corresponding
/// `AXDataAxisDescriptor` objects in `AXChartDescriptor.additionalAxes`.
@property (nonatomic, copy) NSArray<AXDataPointValue *> *additionalValues NS_REFINED_FOR_SWIFT;

/// A name or label for this data point.
@property (nonatomic, copy, nullable) NSString *label;

/// An attributed version of the name or label for this data point.
@property (nonatomic, copy, nullable) NSAttributedString *attributedLabel;

- (instancetype)initWithX:(AXDataPointValue *)xValue y:(nullable AXDataPointValue *)yValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithX:(AXDataPointValue *)xValue y:(nullable AXDataPointValue *)yValue additionalValues:(nullable NSArray<AXDataPointValue *> *)additionalValues NS_REFINED_FOR_SWIFT;
- (instancetype)initWithX:(AXDataPointValue *)xValue y:(nullable AXDataPointValue *)yValue additionalValues:(nullable NSArray<AXDataPointValue *> *)additionalValues label:(nullable NSString *)label NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Provides information about a data series. A chart may have one or many data series.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface AXDataSeriesDescriptor : NSObject <NSCopying>

/// The name or title of this data series.
@property (nonatomic, copy, nullable) NSString *name;

/// An attributed version of the name of this data series.
/// When set, this will be used instead of `name`.
@property (nonatomic, copy) NSAttributedString *attributedName;

/// Whether or not this data series should be treated as continuous.
@property (nonatomic, assign) BOOL isContinuous;

/// The data points that make up the series.
@property (nonatomic, copy) NSArray<AXDataPoint *> *dataPoints;

- (instancetype)initWithName:(NSString *)name isContinuous:(BOOL)isContinuous dataPoints:(NSArray<AXDataPoint *> *)dataPoints NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName isContinuous:(BOOL)isContinuous dataPoints:(NSArray<AXDataPoint *> *)dataPoints NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Describes the content direction of the chart (i.e. the direction in which the X axis is rendered).
/// For example, a bar chart might be leftToRight, while a pie chart might be radialClockwise.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
typedef NS_ENUM(NSInteger, AXChartDescriptorContentDirection) {
    AXChartContentDirectionLeftToRight NS_SWIFT_NAME(leftToRight) = 0,
    AXChartContentDirectionRightToLeft NS_SWIFT_NAME(rightToLeft),
    AXChartContentDirectionTopToBottom NS_SWIFT_NAME(topToBottom),
    AXChartContentDirectionBottomToTop NS_SWIFT_NAME(bottomToTop),
    AXChartContentDirectionRadialClockwise NS_SWIFT_NAME(radialClockwise),
    AXChartContentDirectionRadialCounterClockwise NS_SWIFT_NAME(radialCounterClockwise)
} NS_SWIFT_NAME(AXChartDescriptor.ContentDirection);

/// The top-level descriptor object for an accessible chart.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
__attribute__((objc_subclassing_restricted))
@interface AXChartDescriptor : NSObject <NSCopying>

/// The title of the chart.
@property (nonatomic, copy, nullable) NSString *title;

/// An attributed version of the title of the chart.
/// When set, this will be used instead of `title`.
@property (nonatomic, copy, nullable) NSAttributedString *attributedTitle;

/// A natural language summary of the key message or features of the chart.
/// e.g. "The chart shows that fuel efficiency decreases as vehicle weight increases."
@property (nonatomic, copy, nullable) NSString *summary;

/// The direction of the chart's X axis.
@property (nonatomic, assign) AXChartDescriptorContentDirection contentDirection;

/// The bounds of the view area for visually rendering data values if applicable, provided in superview coordinates.
@property (nonatomic, assign) CGRect contentFrame;

/// A set of data series descriptors describing each series in the chart.
@property (nonatomic, copy) NSArray<AXDataSeriesDescriptor *> *series;

/// The axis descriptor for the chart's X axis.
@property (nonatomic, strong) id<AXDataAxisDescriptor> xAxis NS_REFINED_FOR_SWIFT;

/// The axis descriptor for the chart's Y axis.
@property (nonatomic, strong, nullable) AXNumericDataAxisDescriptor *yAxis;

/// Descriptors for additional categorical or numerical axes beyond x and y.
/// For example, in a visual chart, these values might be represented by the size
/// or color of data points.
@property (nonatomic, copy, nullable) NSArray<id<AXDataAxisDescriptor>> *additionalAxes NS_REFINED_FOR_SWIFT;

- (instancetype)initWithTitle:(nullable NSString *)title summary:(nullable NSString *)summary xAxisDescriptor:(id<AXDataAxisDescriptor>)xAxis yAxisDescriptor:(nullable AXNumericDataAxisDescriptor *)yAxis series:(NSArray<AXDataSeriesDescriptor *> *)series NS_REFINED_FOR_SWIFT;
- (instancetype)initWithAttributedTitle:(nullable NSAttributedString *)attributedTitle summary:(nullable NSString *)summary xAxisDescriptor:(id<AXDataAxisDescriptor>)xAxis yAxisDescriptor:(AXNumericDataAxisDescriptor *)yAxis series:(NSArray<AXDataSeriesDescriptor *> *)series NS_REFINED_FOR_SWIFT;
- (instancetype)initWithTitle:(nullable NSString *)title summary:(nullable NSString *)summary xAxisDescriptor:(id<AXDataAxisDescriptor>)xAxis yAxisDescriptor:(nullable AXNumericDataAxisDescriptor *)yAxis additionalAxes:(nullable NSArray<id<AXDataAxisDescriptor>> *)additionalAxes series:(NSArray<AXDataSeriesDescriptor *> *)series NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

- (instancetype)initWithAttributedTitle:(nullable NSAttributedString *)attributedTitle summary:(nullable NSString *)summary xAxisDescriptor:(id<AXDataAxisDescriptor>)xAxis yAxisDescriptor:(nullable AXNumericDataAxisDescriptor *)yAxis additionalAxes:(nullable NSArray<id<AXDataAxisDescriptor>> *)additionalAxes series:(NSArray<AXDataSeriesDescriptor *> *)series NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - Live Audio Graphs

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface AXLiveAudioGraph : NSObject

/// Begins a live audio graph session.
+ (void)start;

/// Sets the pitch of the audio graph's tone. This should be a normalized value in the range [0.0, 1.0], where 0 represents the minimum displayable y-axis value for your series
/// and 1 represents the maximum displayable y-axis value for your series.
+ (void)updateValue:(double)value;

/// Ends the live audio graph session.
+ (void)stop;

@end

NS_ASSUME_NONNULL_END

