/* 
    NSMediaLibraryBrowserController.h
    Application Kit
    Copyright (c) 2012-2015, Apple Inc.
    All rights reserved.
*/

/*  NSMediaLibraryBrowserController

    An instance of an NSMediaLibraryBrowserController configures and displays a Media Library Browser Panel. A User can drag and drop media files from the Media Library Browser into views in their application.
*/

/*
    typedef NSMediaLibrary:

    NSMediaLibrary enums are masks used to configure a Media Library Browser to display specific types of media. Combined masks are not yet supported.  In other words, only one non zero mask value is supported at a time.  If masks are combined, the lowest mask value will be used.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSMediaLibrary) {
    NSMediaLibraryAudio = 1UL << 0,
    NSMediaLibraryImage = 1UL << 1,
    NSMediaLibraryMovie = 1UL << 2
} NS_ENUM_AVAILABLE(10_9, NA);

/*
    class:

    NSMediaLibraryBrowserController configures and displays a Media Library Browser Panel.
    
    discussion:
 
    NSMediaLibraryBrowserController is not an NSPanel!  It has NSPanel like methods to remotely control the Media Library Browser.  Clients have no direct programmatic access to the panel displaying the Media Library Browser.
*/

NS_CLASS_AVAILABLE(10_9, NA)
@interface NSMediaLibraryBrowserController : NSObject
{
@private
    id _browserProxy;
}

@property (getter=isVisible) BOOL visible;
@property NSRect frame;
@property NSMediaLibrary mediaLibraries;

+ (NSMediaLibraryBrowserController*)sharedMediaLibraryBrowserController;
- (IBAction)togglePanel:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
