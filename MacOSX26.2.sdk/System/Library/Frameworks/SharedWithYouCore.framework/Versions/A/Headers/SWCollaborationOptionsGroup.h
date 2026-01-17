#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <SharedWithYouCore/SWDefines.h>

@class SWCollaborationOption;

NS_ASSUME_NONNULL_BEGIN

/*!
    @abstract String identifier used to initialize a UTType to represent the type of the array of SWCollaborationOptionsGroups when registering to and reading from the NSItemProvider
 */
SW_EXTERN NSString * const UTCollaborationOptionsTypeIdentifier API_AVAILABLE(ios(16.0), macos(13.0));

/*!
     @class SWCollaborationOptionsGroup
     @abstract A group of SWCollaborationOptions that should be displayed and configured together
     @discussion Use SWCollaborationOptionsGroup to represent a group of options used to configure a collaborative item. An SWCollaborationOptionsGroup with one option indicates a switch.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationOptionsGroup : NSObject <NSCopying, NSSecureCoding>

/*!
    @abstract Localized string used to title the section
 */
@property (nonatomic, copy) NSString *title;
/*!
    @abstract A unique identifier
 */
@property (nonatomic, copy, readonly) NSString *identifier;

/*!
    @abstract Localized string to describe or provide additional information about the group of options
 */
@property (nonatomic, copy) NSString *footer;

/*!
    @abstract SWCollaborationOptions to be displayed in the group
 */
@property (nonatomic, copy) NSArray<SWCollaborationOption *> *options;


/*!
     @abstract Initializes a new option group
     @param identifier unique identifier for the group
     @param options SWCollaborationOptions to display in the section
*/
- (instancetype)initWithIdentifier:(NSString *)identifier options:(NSArray<SWCollaborationOption *> *)options NS_DESIGNATED_INITIALIZER;

/*!
     @abstract Initializes a new option group
     @param identifier unique identifier for the group
     @param options SWCollaborationOptions to display in the group
*/
+ (SWCollaborationOptionsGroup *)optionsGroupWithIdentifier:(NSString *)identifier options:(NSArray<SWCollaborationOption *> *)options;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
