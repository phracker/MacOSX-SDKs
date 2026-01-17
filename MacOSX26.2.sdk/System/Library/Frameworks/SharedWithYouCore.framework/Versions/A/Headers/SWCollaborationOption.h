#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

NS_ASSUME_NONNULL_BEGIN
/*!
     @class SWCollaborationOption
     @abstract A user-facing option for configuring a shareable collaborative item
     @discussion SWCollaborationOptions represent the available settings (such as permissions) a user can configure on a collaborative item
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationOption : NSObject <NSCopying, NSSecureCoding>

/*!
    @abstract A localized title string to be used when displaying the option
 */
@property (nonatomic, copy) NSString *title;

/*!
    @abstract Unique identifier
 */
@property (nonatomic, copy, readonly) NSString *identifier;

/*!
    @abstract A localized subtitle string to be used when displaying the option
 */
@property (nonatomic, copy) NSString *subtitle;

/*!
    @abstract A flag that indicates whether the option is selected.
    @discussion This property should only be set directly when the option represents an individual switch. Defaults to NO
 */
@property (nonatomic, assign, getter=isSelected) BOOL selected;

/*!
    @abstract An array of option identifiers that must already be selected in order to be interacted with
 */
@property (nonatomic, copy) NSArray<NSString *> *requiredOptionsIdentifiers;

/*!
     @abstract Initializes a collaboration option object with a title and unique identifier
     @param title A localized title string to be used when displaying the option
     @param identifier The unique identifier for the option
*/
- (instancetype)initWithTitle:(NSString *)title identifier:(NSString *)identifier NS_DESIGNATED_INITIALIZER NS_SWIFT_UNAVAILABLE("Use SWCollaborationOption.init(title:identifier:subtitle:selected:requiredOptionsIdentifiers:) instead");

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
     @abstract Initializes a collaboration option with a title and unique identifier
     @param title A localized title string to be used when displaying the option
     @param identifier The unique identifier for the option
*/
+ (SWCollaborationOption *)optionWithTitle:(NSString *)title identifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
