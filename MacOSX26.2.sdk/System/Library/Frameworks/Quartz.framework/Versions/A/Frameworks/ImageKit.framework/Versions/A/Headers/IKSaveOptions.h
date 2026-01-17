/*
    IKSaveOptions.h
    ImageKit Framework
    Copyright (c) 2004-2008, Apple, Inc.
    All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ImageKit/ImageKitBase.h>

#ifndef IKSaveOptions_h
#define IKSaveOptions_h

@class IKSaveOptions;

IK_CLASS_AVAILABLE(10.6)
@interface NSObject(IKSaveOptionsDelegate)
- (BOOL)saveOptions: (IKSaveOptions *)saveOptions
   shouldShowUTType: (NSString *)utType;
@end

@class NSSavePanel, NSView;

/*! 
 @class IKSaveOptions
 @abstract The IKSaveOptions class initializes, adds, and manages user interface options for saving image data.
 */
IK_CLASS_AVAILABLE(10.5)
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
@property (assign,nonatomic) id delegate;

/*!
 @property imageProperties
 @abstract current imageProperties (respecting user UI selection).
 */
@property (nonatomic, readonly) NSDictionary * imageProperties;

/*!
 @property imageUTType
 @abstract current imageUTType (respecting user UI selection).
 */
@property (nonatomic, readonly) NSString * imageUTType;

/*!
 @property userSelection
 @abstract information about the UI settings.
 */
@property (nonatomic, readonly) NSDictionary * userSelection;


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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_11_3
/*!
 @property rememberLastSetting
 @abstract If set, the last used UI choices are preserved for the next time IKSaveOptions is used. [default is YES]
 */
@property (assign,nonatomic) BOOL rememberLastSetting;
#endif

@end
    
#endif

