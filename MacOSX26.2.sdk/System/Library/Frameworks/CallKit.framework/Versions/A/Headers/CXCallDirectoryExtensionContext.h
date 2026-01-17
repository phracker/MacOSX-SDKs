//
//  CXCallDirectoryExtensionContext.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <CallKit/CXBase.h>
#import <CallKit/CXCallDirectory.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCallDirectoryExtensionContext;

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, watchos, tvos)
@protocol CXCallDirectoryExtensionContextDelegate <NSObject>

- (void)requestFailedForExtensionContext:(CXCallDirectoryExtensionContext *)extensionContext withError:(NSError *)error;

@end

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, watchos, tvos)
@interface CXCallDirectoryExtensionContext : NSExtensionContext

@property (nonatomic, weak, nullable) id<CXCallDirectoryExtensionContextDelegate> delegate;

/**
 Whether the request should provide incremental data.

 If this is called at the beginning of the request (before any entries have been added or removed) and the result is YES,
 then the request must only provide an "incremental" set of entries, i.e. only add or remove entries relative to the last time data
 was loaded for the extension. Otherwise, if this method is not called OR is called and returns NO, then the request must provide
 a "complete" set of entries, adding the full list of entries from scratch (and removing none), regardless of whether data has ever been
 successfully loaded in the past.
 */
@property (nonatomic, readonly, getter=isIncremental) BOOL incremental API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE(macos, watchos);

- (void)addBlockingEntryWithNextSequentialPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber;

/**
 Remove blocking entry with the specified phone number.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove a previously-added blocking entry.

 @param phoneNumber The blocking entry phone number to remove.
 */
- (void)removeBlockingEntryWithPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE(macos, watchos);

/**
 Remove all currently-stored blocking entries.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove all previously-added blocking entries.
 */
- (void)removeAllBlockingEntries API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE(macos, watchos);

- (void)addIdentificationEntryWithNextSequentialPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber label:(NSString *)label;

/**
 Remove identification entry with the specified phone number.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove a previously-added identification entry. Removes all identification entries with the specified phone number, even if
 multiple identification entries with different labels are present for a single phone number.

 @param phoneNumber The identification entry phone number to remove.
 */
- (void)removeIdentificationEntryWithPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE(macos, watchos);

/**
 Remove all currently-stored identification entries.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove all previously-added identification entries.
 */
- (void)removeAllIdentificationEntries API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE(macos, watchos);

- (void)completeRequestWithCompletionHandler:(nullable void (^)(BOOL expired))completion;

// Use -completeRequestWithCompletionHandler: instead
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void (^__nullable)(BOOL expired))completionHandler NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
