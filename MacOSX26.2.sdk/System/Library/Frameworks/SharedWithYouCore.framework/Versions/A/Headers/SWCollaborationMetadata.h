#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class SWCollaborationOptionsGroup;
@class SWCollaborationShareOptions;

/*!
    @abstract Represents a globally unique identifier for a single collaboration item.
*/
typedef NSString *SWCollaborationIdentifier NS_TYPED_EXTENSIBLE_ENUM;


/*!
    @abstract Represents a locally unique identifier for a collaboration item
*/
typedef NSString *SWLocalCollaborationIdentifier NS_TYPED_EXTENSIBLE_ENUM;

API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationMetadata : NSObject <NSSecureCoding, NSCopying, NSMutableCopying>

/*!
    @abstract Globally unique identifier for the item represented by this metadata.
    @discussion This identifier is unique across platforms and shares of the same item.
*/
@property (copy, readonly, nonatomic) SWCollaborationIdentifier collaborationIdentifier;

/*!
    @abstract Locally unique identifier for the item represented by this metadata.
    @discussion Use this identifier to uniquely identify this metadata before a collaborationIdentifier can be created
*/
@property (copy, readonly, nonatomic) SWLocalCollaborationIdentifier localIdentifier;

/*!
    @abstract Title of the content.
    @discussion Title of the collaboration if provided by the app which owns the collaboration item.
 */
@property (copy, readwrite, nonatomic, nullable) NSString *title;

/*!
    @abstract The collaboration options that this content supports (updated).
 */
@property (copy, readwrite, nonatomic, nullable) SWCollaborationShareOptions *defaultShareOptions;

/*!
    @abstract The collaboration options that the user selected when sending the invite (updated).
 */
@property (copy, readwrite, nonatomic, nullable) SWCollaborationShareOptions *userSelectedShareOptions;

/*!
    @abstract The handle of the person initiating the collaboration, e.g. an email address or phone number.
    @discussion Set by the initiating application to allow the user to confirm the handle being used before beginning collaboration. Value will not be transmitted to recipients, and will be nil when not initiating collaboration.
 */
@property (copy, readwrite, nonatomic, nullable) NSString *initiatorHandle;

/*!
    @abstract The name of the person initiating the collaboration.
    @discussion Set by the initiating application to allow the user to confirm the name being used before beginning collaboration. Value will not be transmitted to recipients, and will be nil when not initiating collaboration.
 */
@property (strong, readwrite, nonatomic, nullable) NSPersonNameComponents *initiatorNameComponents;

- (instancetype)initWithLocalIdentifier:(SWLocalCollaborationIdentifier)localIdentifier;
- (instancetype)initWithCollaborationIdentifier:(SWCollaborationIdentifier)collaborationIdentifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
