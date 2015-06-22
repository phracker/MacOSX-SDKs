/*
    IKSaveOptions.h
    ImageKit Framework
    Copyright (c) 2004-2008, Apple, Inc.
    All rights reserved.
 */

#import <Foundation/Foundation.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class IKSaveOptions;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
@interface NSObject(IKSaveOptionsDelegate)
- (BOOL)saveOptions: (IKSaveOptions *)saveOptions
   shouldShowUTType: (NSString *)utType;
@end
#endif


/*! 
 @class IKSaveOptions
 @abstract The IKSaveOptions class initializes, adds, and manages user interface options for saving image data.
 */
@interface IKSaveOptions : NSObject
{
@private
    void *  _privateData;
    id      _saveOptionsView;
}

/*!
 @property delegate
 @abstract Delegate of the IKSaveOptions.
 */
@property (assign) id delegate;

/*!
 @property imageProperties
 @abstract current imageProperties (respecting user UI selection).
 */
@property (readonly) NSDictionary * imageProperties;

/*!
 @property imageUTType
 @abstract current imageUTType (respecting user UI selection).
 */
@property (readonly) NSString * imageUTType;

/*!
 @property userSelection
 @abstract information about the UI settings.
 */
@property (readonly) NSDictionary * userSelection;


/*! 
 @method initWithImageProperties:imageUTType:
 @abstract Initializes IKSaveOptions with metadata and UTType.
 */
- (instancetype)initWithImageProperties: (NSDictionary *)imageProperties imageUTType: (NSString *)imageUTType; 

/*! 
 @method addSaveOptionsAccessoryViewToSavePanel:
 @abstract Adds IKSaveOptions UI to a NSSavePanel.
 */
- (void)addSaveOptionsAccessoryViewToSavePanel: (NSSavePanel *)savePanel;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/*! 
 @method addSaveOptionsToView:
 @abstract Adds IKSaveOptions UI to a NSView.
 */
- (void)addSaveOptionsToView: (NSView *)view;
#endif

@end
    
#endif

