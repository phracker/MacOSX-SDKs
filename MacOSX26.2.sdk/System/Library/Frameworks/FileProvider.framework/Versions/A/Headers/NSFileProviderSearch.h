//
//  NSFileProviderSearch.h
//  FileProvider
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>
#import <FileProvider/NSFileProviderEnumerating.h>

NS_ASSUME_NONNULL_BEGIN

FILEPROVIDER_API_AVAILABILITY_SEARCH
@protocol NSFileProviderSearchResult

/// The identifier for this search result.
/// This identifier should be usable on API calls from the
/// ``NSFileProviderReplicatedExtension`` protocol.
@property (nonatomic, readonly, copy) NSFileProviderItemIdentifier itemIdentifier;

@property (nonatomic, readonly, copy) NSString *filename;

@property (nonatomic, readonly, copy, nullable) NSDate *creationDate;

@property (nonatomic, readonly, copy, nullable) NSDate *contentModificationDate;

@property (nonatomic, readonly, copy, nullable) NSDate *lastUsedDate;

@property (nonatomic, readonly, copy) UTType *contentType;

@property (nonatomic, readonly, copy, nullable) NSNumber *documentSize;

@end

FILEPROVIDER_API_AVAILABILITY_SEARCH
@protocol NSFileProviderSearchEnumerationObserver <NSObject>

- (void)didEnumerateSearchResults:(NSArray <id<NSFileProviderSearchResult>> *)searchResults;

/**
 Call this method after enumerating a full page of results.  If you set a non-nil
 nextPage, -[NSFileProviderSearchEnumerator enumerateSearchResultsToObserver:startingAtPage:]
 might be called with nextPage to enumerate more items.

 Page data is limited to 500 bytes.  Setting a larger nextPage interrupts the
 enumeration.
 */
- (void)finishEnumeratingUpToPage:(nullable NSFileProviderPage)nextPage NS_SWIFT_NAME(finishEnumerating(upTo:));

/**
  Finishing a search enumeration with an error will cause the system to stop
  requesting additional pages of results.
  The system will not retry in case of an error. It is up to the extension
  to decide whether to retry errors internally, in their implementation of `enumerateSearchResultsForObserver`,
  or to return the error to the system and end the search query.
 */
- (void)finishEnumeratingWithError:(NSError *)error;

/**
 The maximum number of results to return in a single page enumeration.

 If the extension returns more than this number of results in a single page enumeration,
 the system will crash the extension process.
 */
@property (nonatomic, readonly) NSInteger maximumNumberOfResultsPerPage;

@end

FILEPROVIDER_API_AVAILABILITY_SEARCH
@protocol NSFileProviderSearchEnumerator <NSObject>

/**
  Called when the system wants to cancel a currently running enumeration, or when the system is finished using this enumerator object.

  For instance, the user has changed their query, and the result of the currently running query will no longer
  be used by the system.

  Or, the system is finished using this enumerator object.

  The extension should cancel any outstanding requests and cleanup resources.
 */
- (void)invalidate;

/**
 Enumerate search results starting from the specified page.

 - Parameters:
  - observer: The observer object, which the extension will use to provide results.
  - page: If a previous enumeration returned a `nextPage` on
          ``-[NSFileProviderSearchEnumerationObserver finishEnumeratingUpToPage:]``,
          the system may pass that page into the next enumeration.
          The page should contain whatever information is needed to resume the enumeration.
 */
- (void)enumerateSearchResultsForObserver:(id<NSFileProviderSearchEnumerationObserver>)observer
                           startingAtPage:(NSFileProviderPage _Nullable)page NS_SWIFT_NAME(enumerateSearchResults(for:startingAt:));

@end

FILEPROVIDER_API_AVAILABILITY_SEARCH
@interface NSFileProviderStringSearchRequest: NSObject

/// A plaintext string, representing the query the user entered into the system search UI.
@property (nonatomic, readonly) NSString *query;

/// How many results the system is requesting. This is a hint to the extension, to help avoid
/// unnecessary work. The extension may return more results than this.
@property (nonatomic, readonly) NSInteger desiredNumberOfResults;

@end

FILEPROVIDER_API_AVAILABILITY_SEARCH
@protocol NSFileProviderSearching <NSObject>

/// Called by the system to retrieve search results for a user search query.
- (id<NSFileProviderSearchEnumerator>)searchEnumeratorForStringSearchRequest:(NSFileProviderStringSearchRequest *)request;

@end

NS_ASSUME_NONNULL_END
