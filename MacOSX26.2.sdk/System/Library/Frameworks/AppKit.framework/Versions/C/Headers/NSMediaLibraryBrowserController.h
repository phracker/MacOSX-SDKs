/* 
    NSMediaLibraryBrowserController.h
    Application Kit
    Copyright (c) 2012-2024, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/// @abstract This type is used to configure a media browser for individual media types.
/// @warning Though this type is declared as a set of mixable options -- and was originally intended to become that eventually -- you should treat it as an enum.
/// @warning In other words, this type should be declared with NS_ENUM rather than NS_OPTIONS, but the latter has historical inertia not worth struggling against.
typedef NS_OPTIONS(NSUInteger, NSMediaLibrary) {
    NSMediaLibraryAudio = 1UL << 0,
    NSMediaLibraryImage = 1UL << 1,
    NSMediaLibraryMovie = 1UL << 2
} API_AVAILABLE(macos(10.9));

/// @abstract This class configures and displays a media browser panel.
/// @discussion This class provides no direct access to the panel, and its meaningful contents aren't in the calling process.
API_AVAILABLE(macos(10.9))
@interface NSMediaLibraryBrowserController : NSObject

@property (class, readonly, strong) NSMediaLibraryBrowserController *sharedMediaLibraryBrowserController;

@property (getter=isVisible) BOOL visible;
@property NSRect frame;
@property NSMediaLibrary mediaLibraries;

- (IBAction)togglePanel:(nullable id)sender;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
