//
//  CIPlugIn.h
//
//
//  Created on Fri May 14 2004.
//  Copyright (c) 2004 Apple Computer. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <CoreImage/CIPlugInInterface.h>
#import <CoreImage/CoreImageDefines.h>



/**
 The CIPlugIn class is responsible for loading Image Units.
 
 The implementation of the CIPlugIn objects is private.
 An application can, however, call the 2 public class method to load plug-ins.
 */
NS_CLASS_AVAILABLE_MAC(10_4)
@interface CIPlugIn : NSObject {
    void *_priv[8];
}

/** This call will scan for plugins with the extension .plugin in
 		/Library/Graphics/Image Units
        ~Library/Graphics/Image Units
 If called more than once, newly added plug-ins will be loaded but you cannot remove a plug-in and its filters. */
+ (void)loadAllPlugIns;

/** Same as loadAllPlugIns does not load filters that contain executable code. */
+ (void)loadNonExecutablePlugIns;

/** Loads a plug-in specified by its URL. */
+ (void)loadPlugIn:(NSURL *)url allowNonExecutable:(BOOL)allowNonExecutable
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

/** Loads a plug-in specified by its URL.
 
 If allowExecutableCode is NO, filters containing executable code will not be loaded. If YES, any kind of filter will be loaded. */
+ (void)loadPlugIn:(NSURL *)url allowExecutableCode:(BOOL)allowExecutableCode NS_AVAILABLE_MAC(10_7);

@end
