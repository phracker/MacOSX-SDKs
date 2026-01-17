//
//  MKLocalSearchCompleter.h
//  MapKit
//
//  Copyright (c) 2016, Apple Inc. All rights reserved.
//

#import <MapKit/MapKit.h>
#import <MapKit/MKLocalSearchRequest.h>
#import <MapKit/MKAddressFilter.h>

NS_ASSUME_NONNULL_BEGIN

@class MKLocalSearchCompletion;
@class MKPointOfInterestFilter;
@protocol MKLocalSearchCompleterDelegate;

typedef NS_ENUM(NSInteger, MKSearchCompletionFilterType) {
    MKSearchCompletionFilterTypeLocationsAndQueries = 0, // Returns completions for points of interest as well as query suggestions (e.g., "coffee")
    MKSearchCompletionFilterTypeLocationsOnly, // Returns completions only for points of interest
}
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use MKLocalSearchCompleterResultType", ios(9.3, 13.0), macos(10.11.4, 10.15), tvos(9.2, 13.0)) API_UNAVAILABLE(watchos);
#endif

typedef NS_OPTIONS(NSUInteger, MKLocalSearchCompleterResultType) {
    MKLocalSearchCompleterResultTypeAddress = 1 << 0,
    MKLocalSearchCompleterResultTypePointOfInterest = 1 << 1,
    MKLocalSearchCompleterResultTypeQuery = 1 << 2,
    MKLocalSearchCompleterResultTypePhysicalFeature API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0)) = 1 << 3
} API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

API_AVAILABLE(macos(10.11.4), ios(9.3), tvos(9.2), watchos(3.0))
@interface MKLocalSearchCompleter : NSObject

@property (nonatomic, copy) NSString *queryFragment;
@property (nonatomic, assign) MKCoordinateRegion region;
@property (nonatomic, assign) MKLocalSearchRegionPriority regionPriority API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));
@property (nonatomic, assign) MKSearchCompletionFilterType filterType
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use resultTypes", ios(9.3, 13.0), macos(10.11.4, 10.15), tvos(9.2, 13.0)) API_UNAVAILABLE(watchos); // Defaults to MKSearchCompletionFilterTypeLocationsAndQueries
#endif
@property (nonatomic, assign) MKLocalSearchCompleterResultType resultTypes API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
@property (nonatomic, copy, nullable) MKAddressFilter *addressFilter API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));

@property (nonatomic, weak, nullable) id<MKLocalSearchCompleterDelegate> delegate;

@property (nonatomic, readonly, strong) NSArray<MKLocalSearchCompletion *> *results;

@property (nonatomic, readonly, getter=isSearching) BOOL searching;

- (void)cancel;

@end

API_AVAILABLE(macos(10.11.4), ios(9.3), tvos(9.2), watchos(3.0))
@protocol MKLocalSearchCompleterDelegate <NSObject>
@optional

- (void)completerDidUpdateResults:(MKLocalSearchCompleter *)completer;
- (void)completer:(MKLocalSearchCompleter *)completer didFailWithError:(NSError *)error;

@end

API_AVAILABLE(macos(10.11.4), ios(9.3), tvos(9.2), watchos(3.0))
@interface MKLocalSearchCompletion : NSObject

@property (nonatomic, readonly, strong) NSString *title;
@property (nonatomic, readonly, strong) NSArray<NSValue *> *titleHighlightRanges; // NSValue-wrapped NSRanges

@property (nonatomic, readonly, strong) NSString *subtitle;
@property (nonatomic, readonly, strong) NSArray<NSValue *> *subtitleHighlightRanges; // NSValue-wrapped NSRanges

@end

@interface MKLocalSearchRequest ()
- (instancetype)initWithCompletion:(MKLocalSearchCompletion *)completion NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.11.4), ios(9.3), tvos(9.2), watchos(3.0));
@end

NS_ASSUME_NONNULL_END
