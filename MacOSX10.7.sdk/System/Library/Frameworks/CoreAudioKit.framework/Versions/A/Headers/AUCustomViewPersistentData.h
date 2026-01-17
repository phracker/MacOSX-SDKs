/*
     File:      AUCustomViewPersistentData.h
 
     Contains:  Protocol definition for AU View persistent data
  
     Copyright: (c) 2004-2008 by Apple, Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

@class NSDictionary;

@protocol AUCustomViewPersistentData

/*!
	@header AUCustomViewPersistentData
	This file specifies a protocol that cocoa-based audio unit views will implement. Audio Unit hosts will call these methods to manage view data that needs to be preserved between subsequent openings of an audio unit's custom view. The view data is an opaque dictionary and can contain any information that the view needs to preserve such as user selection, and interface state such as selected tab view items, etc.

	The host should retrieve the customViewData before closing the view. This can be saved as part of a document, or used to restore view settings by calling setCustomViewData prior to opening the view.
 */

/*!
	@function	customViewPersistentData
	@abstract	Return the custom data to be preserved by the host before closing the view.
	@result		A NSDictionary
	@discussion 	The host should call this method before closing the view. This dictionary should be returned autoreleased.
*/
- (NSDictionary *)customViewPersistentData;

/*!
	@function	setCustomViewPersistentData:
	@abstract	Return the custom data to be preserved by the host between openings of the view.
	@param		A NSDictionary containing the view data to restore when the view is opened.
	@discussion 	This call should be made prior to opening the view. The au view should be written in such a way that it can store this
			dictionary and use its information when the view is opened and user interface elements are created. The view should retain
			this dictionary until it is finished with it, and should not release the dictionary. This dictionary is owned by the host.
*/
- (void) setCustomViewPersistentData:(NSDictionary *) data;

@end
