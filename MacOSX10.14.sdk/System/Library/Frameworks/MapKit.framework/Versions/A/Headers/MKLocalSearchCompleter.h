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
@protocol MKLocalSearchCompleterDelegate;

typedef NS_ENUM(NSInteger, MKSearchCompletionFilterType) {
    MKSearchCompletionFilterTypeLocationsAndQueries = 0, // Returns completions for points of interest as well as query suggestions (e.g., "coffee")
    MKSearchCompletionFilterTypeLocationsOnly, // Returns completions only for points of interest
} NS_ENUM_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED;

NS_CLASS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKLocalSearchCompleter : NSObject

@property (nonatomic, copy) NSString *queryFragment;
@property (nonatomic, assign) MKCoordinateRegion region;
@property (nonatomic, assign) MKSearchCompletionFilterType filterType; // Defaults to MKSearchCompletionFilterTypeLocationsAndQueries

@property (nonatomic, weak, nullable) id<MKLocalSearchCompleterDelegate> delegate;

@property (nonatomic, readonly, strong) NSArray<MKLocalSearchCompletion *> *results;

@property (nonatomic, readonly, getter=isSearching) BOOL searching;

- (void)cancel;

@end

NS_CLASS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@protocol MKLocalSearchCompleterDelegate <NSObject>
@optional

- (void)completerDidUpdateResults:(MKLocalSearchCompleter *)completer;
- (void)completer:(MKLocalSearchCompleter *)completer didFailWithError:(NSError *)error;

@end

NS_CLASS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKLocalSearchCompletion : NSObject

@property (nonatomic, readonly, strong) NSString *title;
@property (nonatomic, readonly, strong) NSArray<NSValue *> *titleHighlightRanges; // NSValue-wrapped NSRanges

@property (nonatomic, readonly, strong) NSString *subtitle;
@property (nonatomic, readonly, strong) NSArray<NSValue *> *subtitleHighlightRanges; // NSValue-wrapped NSRanges

@end

@interface MKLocalSearchRequest ()
- (instancetype)initWithCompletion:(MKLocalSearchCompletion *)completion NS_AVAILABLE(10_11_4, 9_3) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED;
@end

NS_ASSUME_NONNULL_END
