/*!
 @header     MSSticker
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSSticker : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method     initWithContentsOfFileURL:localizedDescription:error:
 @abstract   Initializes a sticker with the contents of the URL and the localized description.
 @discussion Initializes a sticker with the contents of the URL and the localized description.
 The specified file must have a maximum size of 500KB and must conform to kUTTypePNG, kUTTypeGIF
 or kUTTypeJPEG. The image loaded from the file must be no smaller than 300px X 300px and must
 be no larger 618px x 618px. This localized description string is limited to 150 Unicode
 characters in length.
 @param      fileURL    The URL from which to read sticker data.
 @param      localizedDescription   A succinct localized string describing the sticker.
 @param      error  If this method could not initialize a sticker, this will contain an NSError object describing the failure.
 @return     A new sticker object or nil if the method could not initialize a sticker from the specified file and localizedDescription.
 */
- (nullable instancetype)initWithContentsOfFileURL:(NSURL *)fileURL localizedDescription:(NSString *)localizedDescription error:(NSError *_Nullable *)error NS_DESIGNATED_INITIALIZER;

/*!
 @property   imageFileURL
 @abstract   The file URL to the Sticker was initialized with.
 */
@property (nonatomic, strong, readonly) NSURL *imageFileURL;

/*!
 @property   localizedDescription
 @abstract   A succinct localized string describing the sticker.
 */
@property (nonatomic, copy, readonly) NSString *localizedDescription;

@end

NS_ASSUME_NONNULL_END
