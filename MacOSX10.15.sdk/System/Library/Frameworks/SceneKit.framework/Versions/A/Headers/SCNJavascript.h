//
//  SCNJavascript.h
//  SceneKit
//
//  Copyright © 2014-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class JSContext;

NS_ASSUME_NONNULL_BEGIN

/*
 @function SCNExportJavaScriptModule
 @abstract Exports SceneKit's symbols (constants and class definition) into the specified JavaScript context.
 @discussion SceneKit's classes, properties and constants are exported as global object with their original name. Selectors are exported using the rules defined in JavaScriptCore's JSExport.h.
 
 For example to instanciate a node in JavaScript:
 
 var aNode = SCNNode.node();
 
 to change its opacity:
 
 aNode.opacity = 0.5;
 
 to remove from its parent node:
 
 aNode.removeFromParentNode();
 
 to animate a node opacity:
 
 SCNTransaction.begin();
 SCNTransaction.setAnimationDuration(1.0);
 aNode.opacity = 0.5;
 SCNTransaction.commit();
 
 The following special objects are also exported:
 
 class name           constructor                                                  Objective-C class
 SCNColor             SCNColor.color(r,g,b,a)                                      NSColor
 CATimingFunction     CATimingFunction.functionWithName(name)                      CATimingFunction
 CABasicAnimation     CABasicAnimation.animationWithKeyPath(aPath)                 CABasicAnimation
 CAAnimationGroup     new CAAnimationGroup()                                       CAAnimationGroup
 CAKeyframeAnimation  CAKeyframeAnimation.animationWithKeyPath(aPath)              CAKeyframeAnimation
 SCNImage             SCNImage.imageWithURL(aURL)                                  NSImage / UIImage
                      SCNImage.imageWithPath(aPath)                                  
 
 Vectors use this syntax:
 aNode.scale = {x:2, y:2, z:2};
 
 Matrices use this syntax:
 aNode.transform = {m11:1, m12:0, m13:0 ... m44:1};
 */

SCN_EXPORT void SCNExportJavaScriptModule(JSContext *context) API_AVAILABLE(macos(10.10));

NS_ASSUME_NONNULL_END
