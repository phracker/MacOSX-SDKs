//
//  CPSearchTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPListItem.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CPSearchTemplateDelegate;


API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPSearchTemplate : CPTemplate

@property (nullable, nonatomic, weak) id<CPSearchTemplateDelegate> delegate;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPSearchTemplateDelegate <NSObject>

/**
 The user has entered characters in the search text field.
 
 @param searchTemplate The search template in use by the user
 @param searchText The search text entered by the user
 @param completionHandler You must call the completionHandler with updated search results
 */
- (void)searchTemplate:(CPSearchTemplate *)searchTemplate updatedSearchText:(NSString *)searchText completionHandler:(void (^)(NSArray <CPListItem *> *searchResults))completionHandler;

/**
 The user has selected an item in the search result list.
 
 @param searchTemplate The search template in use by the user
 @param item The item selected by the user
 @param completionHandler You must call the completionHandler when you have handled the row selection in the search result
 */
- (void)searchTemplate:(CPSearchTemplate *)searchTemplate selectedResult:(CPListItem *)item completionHandler:(void (^)(void))completionHandler;

@optional

/**
 The user has selected the keyboard's search button. Generally, you should push a @c CPListTemplate containing the current search results.

 @param searchTemplate The search template in use by the user
 */
- (void)searchTemplateSearchButtonPressed:(CPSearchTemplate *)searchTemplate;

@end

NS_ASSUME_NONNULL_END
