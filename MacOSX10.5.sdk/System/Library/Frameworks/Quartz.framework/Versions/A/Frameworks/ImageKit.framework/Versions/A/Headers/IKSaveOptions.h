/*
	IKSaveOptions.h
	ImageKit Framework
	Copyright (c) 2004-2007, Apple, Inc.
	All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface IKSaveOptions : NSObject
{
@private
    void *  _privateData;
    id      _saveOptionsView;
}

- (id)initWithImageProperties: (NSDictionary*)imageProperties
                  imageUTType: (NSString*)imageUTType; 

- (void)addSaveOptionsAccessoryViewToSavePanel: (NSSavePanel*)savePanel;


// returns updated imageProperties (respecting user UI selection)
- (NSDictionary *)imageProperties;

// returns updated imageUTType (respecting user UI selection)
- (NSString *)imageUTType;

// information about the UI settings
- (NSDictionary *)userSelection;

@end
    


