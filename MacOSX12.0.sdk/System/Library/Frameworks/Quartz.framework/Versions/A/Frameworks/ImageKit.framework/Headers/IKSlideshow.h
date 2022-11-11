/*
	IKSlideshow.h
	ImageKit Framework
	Copyright (c) 2004-2008, Apple, Inc.
	All rights reserved.
 */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#import <Foundation/Foundation.h>
#import <ApplicationServices/ApplicationServices.h>
#import <ImageKit/ImageKitBase.h>

/*! 
 @protocol IKSlideshowDataSource
 @abstract The data source of IKSlideshow must conform to IKSlideshowDataSource protocol.
 @discussion The data source methods may be called one a non-main thread.
 */
@protocol IKSlideshowDataSource 

@required

/*! 
 @method numberOfSlideshowItems
 @abstract return number of items in Slideshow.
 */
- (NSUInteger)numberOfSlideshowItems;

/*! 
 @method slideshowItemAtIndex:
 @abstract return the item for a given index.
 @discussion The item can be either: NSImage, NSString, NSURL, CGImageRef, or PDFPage.
             Note: when using 'IKSlideshowModeOther' as slideshowMode, the item has to be a NSURL.
 */
- (id)slideshowItemAtIndex: (NSUInteger)index;

@optional

/*! 
 @method nameOfSlideshowItemAtIndex:
 @abstract Display name for item at index.
 */
- (NSString *)nameOfSlideshowItemAtIndex: (NSUInteger)index;

/*! 
 @method canExportSlideshowItemAtIndex:toApplication:
 @abstract should the export button be enabled for a given item at index?
 */
- (BOOL)canExportSlideshowItemAtIndex: (NSUInteger)index toApplication: (NSString *)applicationBundleIdentifier;

/*! 
 @method slideshowWillStart
 @abstract Slideshow will start.
 */
- (void)slideshowWillStart;

/*! 
 @method slideshowDidStop
 @abstract Slideshow did stop.
 */
- (void)slideshowDidStop;

/*! 
 @method slideshowDidChangeCurrentIndex:
 @abstract Slideshow did change current item index.
 */
- (void)slideshowDidChangeCurrentIndex: (NSUInteger)newIndex;
@end



/*! 
 @class IKSlideshow
 @abstract IKSlideshow handles a slideshow with images, PDFs & more.
 */
@interface IKSlideshow : NSObject
{
@private
    id _privateData;
}

/*!
 @property autoPlayDelay
 @abstract Array of filters reflecting the current user adjustments in the adjust or effects tab.
 */
@property NSTimeInterval autoPlayDelay;

/*!
 @method sharedSlideshow
 @abstract shared instance of the IKSlideshow.
 */
+ (IKSlideshow *)sharedSlideshow;

/*!
 @method runSlideshowWithDataSource:inMode:options:
 @abstract start the slideshow (slideshowOptions can be NULL).
 */
- (void)runSlideshowWithDataSource: (id<IKSlideshowDataSource>)dataSource inMode: (NSString *)slideshowMode options: (NSDictionary *)slideshowOptions;

/*!
 @method stopSlideshow:
 @abstract stop the slideshow.
 */
- (void)stopSlideshow: (id)sender;

/*!
 @method reloadData:
 @abstract reloadData.
 */
- (void)reloadData;

/*!
 @method reloadSlideshowItemAtIndex:
 @abstract reloadSlideshowItemAtIndex.
 */
- (void)reloadSlideshowItemAtIndex: (NSUInteger)index;

/*!
 @method indexOfCurrentSlideshowItem:
 @abstract Returns index of current slideshow item.
 */
- (NSUInteger)indexOfCurrentSlideshowItem;

/*!
 @method canExportToApplication:
 @abstract Is exporting to a given application possible (application installed?, right version?, ...).
 */
+ (BOOL) canExportToApplication: (NSString *) applicationBundleIdentifier;

/*! 
 @method exportSlideshowItem:toApplication:
 @abstract export an item to the given application.
 @discussion The item can be either: NSImage, NSString, NSURL, or a NSArray of NSImage / NSString / NSURL.
 */
+ (void) exportSlideshowItem: (id)item toApplication: (NSString *)applicationBundleIdentifier;
@end


/* IKSlideshow modes: */
extern NSString *const IKSlideshowModeImages;       /* all items are images */
extern NSString *const IKSlideshowModePDF;          /* all items are PDFs */
extern NSString *const IKSlideshowModeOther;        /* mixed mode (images, PDF, text, HTML, ...) */


/* IKSlideshow option keys: */
extern NSString *const IKSlideshowWrapAround;           /* boolean, default true */
extern NSString *const IKSlideshowStartPaused;          /* boolean, default true */
extern NSString *const IKSlideshowStartIndex;           /* number, default 0 */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
extern NSString *const IKSlideshowScreen;               /* NSScreen, default [NSScreen mainScreen] */
extern NSString *const IKSlideshowAudioFile;            /* NSURL, default none*/
#endif

extern NSString *const IKSlideshowPDFDisplayBox;        /* PDFDisplayBox  (see PDFKit) */
extern NSString *const IKSlideshowPDFDisplayMode;       /* PDFDisplayMode (see PDFKit) */
extern NSString *const IKSlideshowPDFDisplaysAsBook;    /* boolean */


/* exporting */
extern NSString *const IK_iPhotoBundleIdentifier;    /* com.apple.iPhoto */
extern NSString *const IK_ApertureBundleIdentifier;  /* com.apple.Aperture */
extern NSString *const IK_MailBundleIdentifier;      /* com.apple.mail */
extern NSString *const IK_PhotosBundleIdentifier;    /* com.apple.Photos */

#endif
