//
//  MKLocalSearchCompleter.h
//  MapKit
//
//  Copyright (c) 2016, Apple Inc. All rights reserved.
//

#import <MapKit/MapKit.h>
#import <MapKit/MKLocalSearchRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class MKLocalSearchCompletion;
@class MKPointOfInterestFilter;
@protocol MKLocalSearchCompleterDelegate;

typedef NS_ENUM(NSInteger, MKSearchCompletionFilterType) {
    MKSearchCompletionFilterTypeLocationsAndQueries = 0, // Returns completions for points of interest as well as query suggestions (e.g., "coffee")
    MKSearchCompletionFilterTypeLocationsOnly, // Returns completions only for points of interest
} API_DEPRECATED("Use MKLocalSearchCompleterResultType", ios(9.3, 13.0), macos(10.11.4, 10.15), tvos(9.2, 13.0)) API_UNAVAILABLE(watchos);

typedef NS_OPTIONS(NSUInteger, MKLocalSearchCompleterResultType) {
    MKLocalSearchCompleterResultTypeAddress = 1 << 0,
    MKLocalSearchCompleterResultTypePointOfInterest = 1 << 1,
    MKLocalSearchCompleterResultTypeQuery = 1 << 2
} API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

NS_CLASS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKLocalSearchCompleter : NSObject

@property (nonatomic, copy) NSString *queryFragment;
@property (nonatomic, assign) MKCoordinateRegion region;
@property (nonatomic, assign) MKSearchCompletionFilterType filterType API_DEPRECATED("Use resultTypes", ios(9.3, 13.0), macos(10.11.4, 10.15), tvos(9.2, 13.0)) API_UNAVAILABLE(watchos); // Defaults to MKSearchCompletionFilterTypeLocationsAndQueries
@property (nonatomic, assign) MKLocalSearchCompleterResultType resultTypes API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, weak, nullable) id<MKLocalSearchCompleterDelegate> delegate;

@property (nonatomic, readonly, strong) NSArray<MKLocalSearchCompletion *> *results;

@property (nonatomic, readonly, getter=isSearching) BOOL searching;

- (void)cancel;

@end

NS_CLASS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@protocol MKLocalSearchCompleterDelegate <NSObject>
@optional

- (void)completerDidUpdateResults:(MKLocalSearchCompleter *)completer;
- (void)completer:(MKLocalSearchCompleter *)completer didFailWithError:(NSError *)error;

@end

NS_CLASS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKLocalSearchCompletion : NSObject

@property (nonatomic, readonly, strong) NSString *title;
@property (nonatomic, readonly, strong) NSArray<NSValue *> *titleHighlightRanges; // NSValue-wrapped NSRanges

@property (nonatomic, readonly, strong) NSString *subtitle;
@property (nonatomic, readonly, strong) NSArray<NSValue *> *subtitleHighlightRanges; // NSValue-wrapped NSRanges

@end

@interface MKLocalSearchRequest ()
- (instancetype)initWithCompletion:(MKLocalSearchCompletion *)completion NS_DESIGNATED_INITIALIZER NS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos);
@end

NS_ASSUME_NONNULL_END
