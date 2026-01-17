/*
 * NCWidgetSearchViewController.h
 * NotificationCenter.framework
 * Copyright (c) 2014-2015 Apple Inc. All rights reserved.
 */

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@protocol NCWidgetSearchViewDelegate;

API_DEPRECATED("Use WidgetKit instead. Today View extensions have been deprecated.", macos(10.10, 11.0))
@interface NCWidgetSearchViewController : NSViewController

/* The delegate is responsible for performing the search based on the
   searchTerm provided to it and setting the searchResults array accordingly. */
@property (nullable, weak) IBOutlet id<NCWidgetSearchViewDelegate> delegate;

/* A textual representation of the objects in searchResults will be displayed
   using the description property of each object. A different property may be
   specified for display using the searchResultKeyPath property. */
@property (nullable, copy) NSArray<id> *searchResults;

/* Specify localized header text for the search view. Defaults to "Search" */
@property (nullable, copy) NSString *searchDescription;

/* Specify a localized placeholder string to display in the list view when no
   results are available. */
@property (nullable, copy) NSString *searchResultsPlaceholderString;

/* Specify a key path for the string property to display for each object in
   searchResults. By default "description" will be used. */
@property (nullable, copy) NSString *searchResultKeyPath;

@end

API_DEPRECATED("Use WidgetKit instead. Today View extensions have been deprecated.", macos(10.10, 11.0))
@protocol NCWidgetSearchViewDelegate <NSObject>

/* Called as new search terms are typed.
   Set the searchResults of the NCSearchViewController in order to display the
   results. The max results argument hints at a maximum number of results that
   will be displayed. */
- (void)widgetSearch:(NCWidgetSearchViewController *)controller searchForTerm:(NSString *)searchTerm maxResults:(NSUInteger)max;

/* Called when the search term is cleared. */
- (void)widgetSearchTermCleared:(NCWidgetSearchViewController *)controller;

/* Called when the user selects an item from the list of search results.
   The search view controller will be dismissed after this method returns. */
- (void)widgetSearch:(NCWidgetSearchViewController *)controller resultSelected:(id)object;

@end
API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
