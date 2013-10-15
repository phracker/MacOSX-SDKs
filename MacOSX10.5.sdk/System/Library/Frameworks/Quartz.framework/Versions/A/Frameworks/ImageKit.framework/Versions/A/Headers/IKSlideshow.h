/*
	IKSlideshow.h
	ImageKit Framework
	Copyright (c) 2004-2007, Apple, Inc.
	All rights reserved.
 */

#ifndef IKSLIDESHOW_H_
#define IKSLIDESHOW_H_

#import <Foundation/Foundation.h>
#import <ApplicationServices/ApplicationServices.h>

// IKSlideshow data source
//------------------------------------------------------------------
@protocol IKSlideshowDataSource 

@required

// return number of items in Slideshow. 
- (NSUInteger)numberOfSlideshowItems;

// return the item for a given index
// The item can be: 
//           - NSImage *
//           - NSString *     (path)
//           - NSURL *
//           - CGImageRef
// 		     - PDFPage *
//
- (id)slideshowItemAtIndex: (NSUInteger)index;

@optional

// display name for item at index
- (NSString*)nameOfSlideshowItemAtIndex: (NSUInteger)index;

// should the export button be enabled for a given item at index?
- (BOOL)canExportSlideshowItemAtIndex: (NSUInteger)index
                        toApplication: (NSString *)applicationBundleIdentifier;

// Slideshow will start
- (void)slideshowWillStart;

// Slideshow did stop
- (void)slideshowDidStop;

// Slideshow did change current item index
- (void)slideshowDidChangeCurrentIndex: (NSUInteger)newIndex;
@end



// IKSlideshow
//------------------------------------------------------------------
@interface IKSlideshow : NSObject
{
@private
    id _privateData;
}

@property NSTimeInterval autoPlayDelay;

// shared instance of the IKSlideshow class
+ (IKSlideshow*)sharedSlideshow;

// start the slideshow (slideshowOptions can be NULL)
- (void)runSlideshowWithDataSource: (id<IKSlideshowDataSource>)dataSource
                            inMode: (NSString*)slideshowMode
                           options: (NSDictionary*)slideshowOptions;


- (void)stopSlideshow: (id)sender;

- (void)reloadData;
- (void)reloadSlideshowItemAtIndex: (NSUInteger)index;

- (NSUInteger)indexOfCurrentSlideshowItem;

// is exporting to a given application possible (application installed?, right version?, ...)
+ (BOOL) canExportToApplication: (NSString *) applicationBundleIdentifier;

// export an item to the given application
// The item can be: 
//           - NSImage *
//           - NSString *     (path)
//           - NSURL *
//           - an NSArray of NSImage / NSString / NSURL
+ (void) exportSlideshowItem: (id)         item
               toApplication: (NSString *) applicationBundleIdentifier;
@end


// IKSlideshow modes:
//------------------------------------------------------------------
extern NSString *const IKSlideshowModeImages;       // all items are images 
extern NSString *const IKSlideshowModePDF;          // all items are PDFs
extern NSString *const IKSlideshowModeOther;        // mixed mode (images, PDF, text, HTML, ...)


// IKSlideshow option keys:
//------------------------------------------------------------------
extern NSString *const IKSlideshowWrapAround;           // boolean
extern NSString *const IKSlideshowStartPaused;          // boolean 
extern NSString *const IKSlideshowStartIndex;           // number

extern NSString *const IKSlideshowPDFDisplayBox;        // PDFDisplayBox  (see PDFKit)
extern NSString *const IKSlideshowPDFDisplayMode;       // PDFDisplayMode (see PDFKit)
extern NSString *const IKSlideshowPDFDisplaysAsBook;    // boolean


// exporting
//------------------------------------------------------------------
extern NSString *const IK_iPhotoBundleIdentifier;    // com.apple.iPhoto

#endif
