#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

@class SWCollaborationOptionsGroup;

NS_ASSUME_NONNULL_BEGIN

/*!
     @class SWCollaborationOptionsPickerGroup
     @abstract Represents a group of SWCollaborationOptions that should be grouped together in a picker list, with mutually exclusive options.
     @discussion SWCollaborationOptionsPickerGroup is displayed as a picker view. Only one option in the group can be selected by the user.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationOptionsPickerGroup : SWCollaborationOptionsGroup

/*!
    @abstract The identifier of the selected option in the group. Defaults to the first SWCollaborationOption's identifier.
 */
@property (nonatomic, strong, readwrite) NSString *selectedOptionIdentifier;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
