//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>

#if TARGET_OS_OSX

#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYouCore/SWCollaborationMetadata.h>

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0))
@interface NSPasteboardItem (SWCollaborationMetadata)

/*!
 @abstract Sets the collaboration metadata on the pasteboard item.
 */
@property (readwrite, copy, nullable) SWCollaborationMetadata *collaborationMetadata;

@end

NS_ASSUME_NONNULL_END

SW_EXTERN NSPasteboardType const NSPasteboardTypeCollaborationMetadata;

#endif /* TARGET_OS_OSX */
