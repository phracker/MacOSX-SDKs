//
//  INDefaultCardTemplate.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INImage.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A template for customizing the display of relevant shortcuts.
 @seealso INRelevantShortcut
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface INDefaultCardTemplate : NSObject <NSCopying, NSSecureCoding>

/*!
 @abstract The title used when displaying the relevant shortcut.
 */
@property (copy, NS_NONATOMIC_IOSONLY) NSString *title;

/*!
 @abstract The subtitle used when displaying the relevant shortcut.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *subtitle;

/*!
 @abstract The image used when displaying the relevant shortcut.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

/*!
 @abstract Initializes a default card template with the provided title.
 */
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

/*!
 @note Must be initilaized with a title, using those initializers.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
