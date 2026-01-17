#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

@class SWCollaborationOptionsGroup;

NS_ASSUME_NONNULL_BEGIN

/*!
     @class SWCollaborationShareOptions
     @abstract represents the state of the collaboration options for the document.
     @discussion SWCollaborationShareOptions contains the SWCollaborationOptionsGorups that are available for the collaboration as well as a string, provided by the client, that summarizes the state of the selected options.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationShareOptions : NSObject <NSCopying, NSSecureCoding>

/*!
    @abstract SWCollaborationOptionsGroups to customize how the collaboration will be shared
 */
@property (nonatomic, copy) NSArray<SWCollaborationOptionsGroup *> *optionsGroups;

/*!
    @abstract Localized string to summarize the selected collaboration options. If nil, "Share Options" will be displayed by default.
 */
@property (nonatomic, copy) NSString *summary;

/*!
     @abstract Initializes a shareOptions object to represent the available collaboration options for the document and a summary of the selected options
     @param optionsGroups SWCollaborationOptionsGroups to customize how the collaboration will be shared
     @param summary localized string to summarize the selected collaboration options
*/
- (instancetype)initWithOptionsGroups:(NSArray<SWCollaborationOptionsGroup *> *)optionsGroups summary:(NSString *)summary NS_DESIGNATED_INITIALIZER;

/*!
     @abstract Initializes a shareOptions object to represent the available collaboration options for the document and the default summary string "Share Options"
     @param optionsGroups SWCollaborationOptionsGroups to customize how the collaboration will be shared
*/
- (instancetype)initWithOptionsGroups:(NSArray<SWCollaborationOptionsGroup *> *)optionsGroups;

/*!
     @abstract Creates a shareOptions object to represent the available collaboration options for the document and a summary of the selected options
     @param optionsGroups SWCollaborationOptionsGroups to customize how the collaboration will be shared
     @param summary localized string to summarize the selected collaboration options
*/
+ (SWCollaborationShareOptions *)shareOptionsWithOptionsGroups:(NSArray<SWCollaborationOptionsGroup *> *)optionsGroups summary:(NSString *)summary;

/*!
     @abstract Creates a shareOptions object to represent the available collaboration options for the document and a summary of the selected options
     @param optionsGroups SWCollaborationOptionsGroups to customize how the collaboration will be shared
*/

+ (SWCollaborationShareOptions *)shareOptionsWithOptionsGroups:(NSArray<SWCollaborationOptionsGroup *> *)optionsGroups;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
