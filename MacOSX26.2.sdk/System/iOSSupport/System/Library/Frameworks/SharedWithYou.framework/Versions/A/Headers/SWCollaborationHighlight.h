#import <TargetConditionals.h>
#if !TARGET_OS_TV
//
//  SWCollaborationHighlight.h
//  SWCollaborationHighlight
//
//  Copyright (c) 2021 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYou/SWHighlight.h>

#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

@class SWPersonIdentity;
@class SWPersonIdentityProof;

/*!
     @class SWCollaborationHighlight
     @abstract A SWHighlight object that represents an active collaboration
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationHighlight : SWHighlight <NSSecureCoding, NSCopying>

/*!
    @abstract Unique identifier as provided by the app hosting the collaboration
    @discussion This identifier is unique across platforms and shares
 */
@property (copy, readonly, nonatomic) NSString *collaborationIdentifier;

/*!
    @abstract Title of the collaboration highlight
    @discussion Title of the collaboration if provided by the app hosting the collaboration
 */
@property (nullable, copy, readonly, nonatomic) NSString *title;

/*!
    @abstract Date when the file was created
 */
@property (copy, readonly, nonatomic) NSDate *creationDate;

/*!
    @abstract UTI type for this collaboration highlight
 */
@property (copy, readonly, nonatomic) UTType *contentType;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
