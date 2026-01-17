//
//  CIPlugIn.h
//  
//
//  Created on Fri May 14 2004.
//  Copyright (c) 2004 Apple Computer. All rights reserved.
//

/*!
    @header CIPlugIn
	@copyright 2004 Apple Computer, Inc. All rights reserved.
	@availability Coming to a Tiger installation near you
    @abstract   The CIPlugIn class is responsible for loading ImageUnits.
    @discussion The implementation of the CIPlugIn objects is for now private. 
		But an application will call the 2 public class method to load plug-ins.
*/

#import <Foundation/Foundation.h>
#import "CIPlugInInterface.h"


/*!
    @class      CIPlugIn
    @abstract   (description)
    @discussion (description)
*/
@interface CIPlugIn : NSObject {
    void *_priv[8];
}

/*!
    @method     loadAllPlugIns
    @abstract   CIPlugIn class method to load plug-ins
    @discussion This call will Scan for plugins with the extension .plugin in 
		/Library/Graphics/Plug-Ins
		~Library/Graphics/Plug-Ins
		If called more than once, newly added plug-ins will be loaded but you cannot remove a plug-in and its filters.
*/
+(void)loadAllPlugIns;

/*!
    @method     loadNonExecutablePlugIns
    @abstract   CIPlugIn class method to load plug-ins
    @discussion Same as loadAllPlugIns but restricted only to pure CIKernel filters (see addPlugIn).
*/
+(void)loadNonExecutablePlugIns;

/*!
    @method     loadPlugIn
    @abstract   CIPlugIn class method to load a plug-in specified by its URL
    @discussion The behavior of invoking this call more than once with the same URL is not defined and therefore for now not encouraged.
    @param      url   URL of the plug-in to be loaded.
    param       allowNonExecutable  only load the CIKernel filters of the plug-in and do not execute any of the plug-ins code.
    
*/
+(void)loadPlugIn:(NSURL*)url allowNonExecutable:(BOOL)allowNonExecutable;

@end

