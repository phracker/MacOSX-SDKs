/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <QuartzComposer/QuartzComposerDefines.h>

#import <Foundation/Foundation.h>
#import <OpenGL/OpenGL.h>

#import <QuartzComposer/QCCompositionRepository.h>
#import <QuartzComposer/QCPlugIn.h>

/* HIGH-LEVEL NOTES:
- QCRenderer is a simplified runtime object to load and play a Quartz composition on an arbitrary OpenGL context.
- The QCRenderer can also be used to pass and retrieve data to / from the ports of the root patch of the composition.
- Use the methods from the <QCCompositionRenderer> protocol to communicate with the composition.
- The input and output ports of the root patch of a <QCCompositionRenderer> instance are also accessible with KVC through the "patch" property e.g. "patch.inputFoo.value",
	and you can observe for value changes using KVO. Be aware however that the values on the output ports might be changing during rendering, but also when starting or stopping.
*/

/* Keys for optional arguments passed to the renderer */
extern NSString* const QCRendererEventKey QC_DEPRECATED_MAC(10_15);
extern NSString* const QCRendererMouseLocationKey QC_DEPRECATED_MAC(10_15);

/* Defined in AppKit */
@class NSOpenGLContext, NSOpenGLPixelFormat, NSImage;

/* Protocol for Quartz Composer composition renderers */
QC_CLASS_DEPRECATED_MAC(10_15)
@protocol QCCompositionRenderer

/*
Returns a dictionary containing attributes describing the composition and the input / output ports on its root patch.
The dictionary may define the following composition attributes:
	- QCCompositionAttributeNameKey: the name of the composition as specified in the information dialog in Quartz Composer (NSString)
	- QCCompositionAttributeDescriptionKey: the description of the composition as specified in the information dialog in Quartz Composer (NSString)
	- QCCompositionAttributeCopyrightKey: the copyright of the composition as specified in the information dialog in Quartz Composer (NSString)
The dictionary also contains dictionaries corresponding to the keys identifying each input / output port of the root patch of the composition. Each of those dictionaries defines the following port attributes:
	- QCPortAttributeTypeKey: the type of the port (NSString)
	- QCPortAttributeNameKey: the name of the port if available (NSString)
	- QCPortAttributeMinimumValueKey: the minimum numerical value accepted by the port if available - smaller values will be clamped (NSNumber)
	- QCPortAttributeMaximumValueKey: the maximum numerical value accepted by the port if available - bigger values will be clamped (NSNumber)
	- QCPortAttributeMenuItemsKey: the list of menu item titles if available - index ports only (NSArray of NSStrings)
*/
- (NSDictionary*) attributes;

/*
Returns an array listing the keys identifying the input ports of the root patch of the composition.
*/
- (NSArray*) inputKeys;

/*
Returns an array listing the keys identifying the output ports of the root patch of the composition.
*/
- (NSArray*) outputKeys;

/*
Sets the value on an input port (identified by its key) of the root patch of the composition.
This method will throw an exception if "key" is invalid or return NO if it cannot set the value.
The types of values you can pass depends on the type of the input port:
	- NSNumber or any object that responds to -integerValue, -floatValue or -doubleValue for Boolean, Index and Number ports
	- NSString or any object that responds to -stringValue or -description for String ports
	- NSColor, CIColor, CGColorRef for Color ports
	- NSImage, NSBitmapImageRep, CGImageRef, CIImage, CVPixelBufferRef, CVOpenGLBufferRef, CVOpenGLTextureRef or opaque QCImage (see below) for Image ports
	- NSArray or NSDictionary for Structure ports
*/
- (BOOL) setValue:(id)value forInputKey:(NSString*)key;

/*
Returns the current value on an input port (identified by its key) of the root patch of the composition.
This method will throw an exception if "key" is invalid.
The type of value returned depends on the type of the input port:
- NSNumber for Boolean, Index and Number ports
- NSString for String ports
- NSColor for Color ports
- NSImage for Image ports
- NSDictionary for Structure ports
*/
- (id) valueForInputKey:(NSString*)key; 

/*
Returns the current value on an output port (identified by its key) of the root patch of the composition.
This method will throw an exception if "key" is invalid.
The type of value returned depends on the type of the output port:
	- NSNumber for Boolean, Index and Number ports
	- NSString for String ports
	- NSColor for Color ports
	- NSImage for Image ports
	- NSDictionary for Structure ports
*/
- (id) valueForOutputKey:(NSString*)key;

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/*
Returns the current value on an output port (identified by its key) of the root patch of the composition.
This method will throw an exception if "key" is invalid.
The type of the returned value can be specified explicitely (if the type is not supported by the port, nil is returned):
	- Boolean, Index and Number ports: NSNumber
	- String ports: NSString
	- Color ports: NSColor, CIColor, CGColor
	- Image ports: NSImage, NSBitmapImageRep, CIImage, CGImage, CVPixelBuffer, CVOpenGLBuffer or QCImage (optimized abstract image object only to be used with -setValue:forInputKey: of another <QCCompositionRenderer>)
	- Structure ports: NSDictionary, NSArray or QCStructure (optimized abstract structure object only to be used with -setValue:forInputKey: of another <QCCompositionRenderer>)
*/
- (id) valueForOutputKey:(NSString*)key ofType:(NSString*)type;

/*
Returns a property list object representing the current values for all the input keys of the composition.
*/
- (id) propertyListFromInputValues;

/*
Sets the values for the input keys of the composition from a property list object previously obtained with -propertyListFromInputValues.
If the property list object does not define a value for an input key or if the value is not of the proper type, the corresponding input port is left untouched.
*/
- (void) setInputValuesWithPropertyList:(id)plist;

/*
A mutable dictionary that can be used to store arbitrary information - make sure to use unique keys like "com.myCompany.foo"
This mutable dictionary is the same as the one available on the plug-in execution context for QCPlugIn instances.
*/
- (NSMutableDictionary*) userInfo;

#endif

@end

/* Quartz Composer Composition Renderer */
QC_CLASS_DEPRECATED_MAC(10_15)
@interface QCRenderer : NSObject <QCCompositionRenderer>
{
@private
	void*		_QCRendererPrivate;
}

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)


/*
Create a new renderer with a QCComposition object and an RGB colorspace (non-device).
The composition must be a pure processing composition i.e. it does not contain any consumer patches.
The colorspace is only used for the images produced by the composition's output image ports.
Note that -snapshotImage / -createSnapshotImageOfType: will always return nil on such QCRenderer instances.
If any error occurs during loading of the composition, nil will be returned.
*/
- (id) initWithComposition:(QCComposition*)composition colorSpace:(CGColorSpaceRef)colorSpace;

/*
Create a new renderer with a low-level CGLContextObj, an RGB colorspace (non-device) and a QCComposition object.
The CGLContext must have both a color and a depth buffer.
If any error occurs during loading of the composition, nil will be returned.
*/
- (id) initWithCGLContext:(CGLContextObj)context pixelFormat:(CGLPixelFormatObj)format colorSpace:(CGColorSpaceRef)colorSpace composition:(QCComposition*)composition QC_GL_DEPRECATED(10_5, 10_14);

/*
Create a new offline renderer of a given size with an RGB colorspace (non-device), and a QCComposition object.
If any error occurs during loading of the composition, nil will be returned.
*/
- (id) initOffScreenWithSize:(NSSize)size colorSpace:(CGColorSpaceRef)colorSpace composition:(QCComposition*)composition;


#endif

/*
Create a new renderer from a NSOpenGLContext and a QuartzComposer composition file.
The NSOpenGLContext must have both a color and a depth buffer.
If any error occurs during loading of the composition file, nil will be returned.
*/
- (id) initWithOpenGLContext:(NSOpenGLContext*)context pixelFormat:(NSOpenGLPixelFormat*)format file:(NSString*)path;

/*
Renders a frame for a given timestamp ("time" must be positive or null).
This method will not swap the buffers on the OpenGL context, so that you can combine Quartz Composer with custom OpenGL code.
All OpenGL states modified by the renderer are saved / restored except:
	- States defined in GL_CURRENT_BIT
	- Texture on each unit and the environment mode
	- Matrix mode
The "arguments" parameters is used to passed optional arguments to the patches of the composition:
	- Use "QCRuntimeEventKey" to pass the current NSEvent if any
	- Use "QCRuntimeMouseLocationKey" to pass the current mouse location in normalized coordinates relatively to the OpenGL context viewport ([0,1]x[0,1] with (0,0) at the lower-left corner) as a NSPoint stored in a NSValue
*/
- (BOOL) renderAtTime:(NSTimeInterval)time arguments:(NSDictionary*)arguments;

/*
	Returns the time at which the renderer will next actually draw new content.
	Calling renderAtTime before that time will unecessarily redraw the same content.
	This needs to be reevaluated whenever port values are manually set or when the arguments change.
*/
- (NSTimeInterval) renderingTimeForTime:(NSTimeInterval)time arguments:(NSDictionary*)arguments;

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/*
Returns the QCComposition from the QCRenderer.
*/
- (QCComposition*) composition;


/*
Returns a snapshot of the current image in the QCRenderer's OpenGL context.
*/
- (NSImage*) snapshotImage;

/*
Returns a snapshot of the current image in the QCRenderer's OpenGL context as a specific image type.
The following image types are supported: NSBitmapImageRep, NSImage, CIImage, CGImage, CVOpenGLBuffer, CVPixelBuffer or QCImage (optimized abstract image object only to be used with -setValue:forInputKey: of another <QCCompositionRenderer>).
The caller is responsible for releasing the returned object.
*/
- (id) createSnapshotImageOfType:(NSString*)type NS_RETURNS_RETAINED;


#endif

@end
