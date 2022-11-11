/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <QuartzComposer/QuartzComposerDefines.h>

#import <Foundation/Foundation.h>

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzCore/CAOpenGLLayer.h>

#import <QuartzComposer/QCRenderer.h>

/* HIGH-LEVEL NOTES:
- The QCCompositionLayer is a Core Animation layer that renders a Quartz composition within a Core Animation layer hierarchy.
- The composition tracks the Core Animation layer time and is rendered directly at the QCCompositionLayer current dimensions.
- The "asynchronous" property of the superclass CAOpenGLLayer must not be modified.
- When archived, the QCCompositionLayer will embed its composition.
- Use the methods from the <QCCompositionRenderer> protocol to communicate with the composition.
- The input and output ports of the root patch of the composition are also accessible with KVC through the "patch" property e.g. "patch.inputFoo.value".
- Note than setting composition inputs through KVC instead of using the -setValue:forInputKey: API will generate implicit animations, but only for animatable parameter types of parameters (numbers and colors)
*/

/* Quartz Composer Composition Core Animation layer */
QC_GL_CLASS_DEPRECATED(10_5, 10_14)
@interface QCCompositionLayer : CAOpenGLLayer <QCCompositionRenderer>
{
@private
	void*				_QCCompositionLayerPrivate;
}

/*
Convenience methods that returns an autoreleased QCCompositionLayer created with a Quartz composition file or QCComposition object.
*/
+ (QCCompositionLayer*) compositionLayerWithFile:(NSString*)path;
+ (QCCompositionLayer*) compositionLayerWithComposition:(QCComposition*)composition;

/*
Create a new QCCompositionLayer with a Quartz composition file or QCComposition object.
*/
- (id) initWithFile:(NSString*)path;
- (id) initWithComposition:(QCComposition*)composition;

/*
Return the QCComposition from the QCCompositionLayer.
*/
- (QCComposition*) composition;

@end

#endif
