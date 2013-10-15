/*
	IKImageEditPanel.h
	ImageKit Framework
	Copyright (c) 2006 - 2007, Apple, Inc.
	All rights reserved.
 */

#ifndef IKIMAGEEDITPANEL_H_
#define IKIMAGEEDITPANEL_H_

#import <AppKit/NSPanel.h>
#import <ApplicationServices/ApplicationServices.h>

// IKImageEditPanel data source 
//------------------------------------------------------------------
@protocol IKImageEditPanelDataSource

@required
- (CGImageRef)image;

- (void)setImage: (CGImageRef)image
 imageProperties: (NSDictionary*)metaData;

@optional

- (CGImageRef)thumbnailWithMaximumSize: (NSSize)size;

- (NSDictionary*)imageProperties;
@end



// IKImageEditPanel
//------------------------------------------------------------------
@interface IKImageEditPanel : NSPanel
{
@private
    void * _privateData;
}

+ (IKImageEditPanel*) sharedImageEditPanel;

- (void)setDataSource: (id<IKImageEditPanelDataSource>)dataSource;
- (id)dataSource;

- (void)reloadData;

@end

#endif