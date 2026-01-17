/*
        NSPreviewRepresentingActivityItem.h
        Application Kit
        Copyright (c) 2022-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSImage, NSItemProvider;

API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
@protocol NSPreviewRepresentableActivityItem <NSObject>

@required

/// The item to be shared
@property (strong, readonly) id item;

@optional

/// A string representing the name or title of the item to be shared
@property (nullable, copy, readonly) NSString *title;

/// Provides an image appropriate to represent the item.
///
/// This image typically is a full-size representation of the content being shared.
/// For instance, if sharing a link to a webpage, this might be the hero image on that webpage.
@property (nullable, strong, readonly) NSItemProvider *imageProvider;

/// Provides an icon appropriate to represent the item.
///
/// This icon typically is a thumbnail-sized representation of the source of the content.
/// For instance, if sharing a link to a webpage, this might be an icon representing the website overall.
@property (nullable, strong, readonly) NSItemProvider *iconProvider;

@end


API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSPreviewRepresentingActivityItem : NSObject <NSPreviewRepresentableActivityItem>

/// - Parameters:
///     - item: The item to share
///     - title: A title to show in a preview
///     - image: An image to show in a preview
///     - icon: An icon to show in a preview
///
/// For more information about the parameters, see NSPreviewRepresentableActivityItem documentation

- (instancetype)initWithItem:(id)item title:(nullable NSString *)title image:(nullable NSImage *)image icon:(nullable NSImage *)icon;

/// - Parameters:
///     - item: The item to share
///     - title: A title to show in a preview
///     - imageProvider: An NSItemProvider which provides an image to show in a preview
///     - iconProvider: An NSItemProvider which provides an icon to show in a preview
///
/// For more information about the parameters, see NSPreviewRepresentableActivityItem documentation

- (instancetype)initWithItem:(id)item title:(nullable NSString *)title imageProvider:(nullable NSItemProvider *)imageProvider iconProvider:(nullable NSItemProvider *)iconProvider NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
