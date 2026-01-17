//
//  VZEFIVariableStore.h
//  Virtualization
//
//  Copyright © 2019-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Options when creating a new EFI variable store.
*/
typedef NS_OPTIONS(NSUInteger, VZEFIVariableStoreInitializationOptions) {
    VZEFIVariableStoreInitializationOptionAllowOverwrite = 1ULL << 0,
} NS_SWIFT_NAME(VZEFIVariableStore.InitializationOptions) API_AVAILABLE(macos(13.0));

/*!
 @abstract EFI variable store
 @discussion
    The EFI variable store contains NVRAM variables exposed by the EFI ROM.
 @seealso VZEFIBootLoader
 */

VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZEFIVariableStore : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize the variable store from the URL of an existing file.
 @param URL The URL of the variable store on the local file system.
 @discussion To create a new variable store, use -[VZEFIVariableStore initCreatingVariableStoreAtURL:options:error].
 */
- (instancetype)initWithURL:(NSURL *)URL;

/*!
 @abstract Write an initialized VZEFIVariableStore to a URL on a file system.
 @param URL The URL to write the variable store to on the local file system.
 @param options Initialization options.
 @param error If not nil, used to report errors if creation fails.
 @return A newly initialized VZEFIVariableStore on success. If an error was encountered returns @c nil, and @c error contains the error.
 */
- (nullable instancetype)initCreatingVariableStoreAtURL:(NSURL *)URL options:(VZEFIVariableStoreInitializationOptions)options error:(NSError **)error;

/*!
 @abstract The URL of the variable store on the local file system.
 */
@property (readonly, copy) NSURL *URL;

@end

NS_ASSUME_NONNULL_END
