/*!
 @header     MSMessageTemplateLayout
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Messages/MSMessageLayout.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MSMessageTemplateLayout
 @abstract   The MSMessageTemplateLayout encapsulates properties used in the construction of UI
 representing a message using the default message layout template.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSMessageTemplateLayout : MSMessageLayout

/*!
 @property   caption
 @abstract   Text to be used as a caption related to the message content.
 */
@property (nonatomic, copy, nullable) NSString *caption;

/*!
 @property   subcaption
 @abstract   Text to be used as a subcaption related to the message content.
 */
@property (nonatomic, copy, nullable) NSString *subcaption;

/*!
 @property   trailingCaption
 @abstract   Text to be drawn right aligned on the same line as the caption text.
 */
@property (nonatomic, copy, nullable) NSString *trailingCaption;

/*!
 @property   trailingSubcaption
 @abstract   Text to be drawn right aligned on the same line as the subcaption text.
 */
@property (nonatomic, copy, nullable) NSString *trailingSubcaption;

/*!
 @property   image
 @abstract   A UIImage object used to construct the message representation in the conversation transcript.
 @discussion When this property and the mediaURL property are both set, the mediaURL
 property will be ignored.
 */
@property (nonatomic, strong, nullable) UIImage *image;

/*!
 @property   mediaFileURL
 @abstract   The URL to a media file used to construct the message representation in the conversation transcript.
 @discussion This must be a file URL, the data contained in the file must conform to
 kUTTypeImage or kUTTypeMovie. When image property and
 this property are both set, then this property will be ignored.
 */
@property (nonatomic, copy, nullable) NSURL *mediaFileURL;

/*!
 @property   imageTitle
 @abstract   Title text associated with the image or media .
 */
@property (nonatomic, copy, nullable) NSString *imageTitle;

/*!
 @property   imageSubtitle
 @abstract   Subtitle text associated with the image or media .
 */
@property (nonatomic, copy, nullable) NSString *imageSubtitle;

@end

NS_ASSUME_NONNULL_END
