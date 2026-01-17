//
//  SHMediaLibrary.h
//  ShazamKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHMediaItem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that represents the user's Shazam library.
///
/// Use `SHMediaLibrary` to add matched songs from the Shazam catalog to the user's Shazam library.
///
/// > Note:
/// > There's no system permission necessary to write to the user's Shazam library. Consider requesting permission from the user before adding songs to the library.
SH_EXPORT API_DEPRECATED("Use SHLibrary instead", macos(12.0, 15.0), ios(15.0, 18.0), tvos(15.0, 18.0), watchos(8.0, 11.0))
@interface SHMediaLibrary : NSObject

/// An instance of the user's default Shazam library.
@property (class, NS_NONATOMIC_IOSONLY, strong, readonly) SHMediaLibrary *defaultLibrary;

/// Adds an array of songs to the user's Shazam library.
///
/// > Important:
/// > You can call this method from synchronous code using a completion handler, as shown on this page, or you can call it as an asynchronous method that has the following declaration:
/// >
/// > ```swift
/// > func add(_ mediaItems: [SHMediaItem]) async throws
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
///
/// Saving a song to the user's Shazam library also saves the following media item properties and their associated values:
///
/// - ``SHMediaItemProperty/shazamID``
/// - ``SHMediaItemProperty/title``
/// - ``SHMediaItemProperty/subtitle``, or ``SHMediaItemProperty/artist`` if the subtitle is unavailable
///
/// > Note:
/// > Saving to the user's Shazam library works only for songs with a valid ``SHMediaItemProperty/shazamID``.
///
/// - Parameters:
///   - mediaItems: An array of media items that represents the songs to add to the library.
///   - completionHandler: The system calls this completion block after adding the media items to the library.
///
///     This block takes the following parameters:
///
///     - term `error`: An error object if a problem occurs when adding any item; otherwise, `nil`.
- (void)addMediaItems:(NSArray<SHMediaItem *> *)mediaItems completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * __nullable error))completionHandler;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
