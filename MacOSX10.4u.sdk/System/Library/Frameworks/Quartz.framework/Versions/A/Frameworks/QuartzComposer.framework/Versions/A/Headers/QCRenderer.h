/*
	Copyright:	(c) 2003-2004 by Apple Computer, Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>
#import <OpenGL/OpenGL.h>

/* HIGH-LEVEL NOTES:
- QCRenderer is a simplified runtime object to load and play a QuartzComposer composition on an arbitrary GL context.
- The QCRenderer can also be used to pass and retrieve data to / from the ports of the root patch of the composition.
*/

/* Keys for optional arguments passed to the renderer */
extern NSString* const QCRendererEventKey;
extern NSString* const QCRendererMouseLocationKey;

/* Key for composition attributes */
extern NSString* const QCCompositionAttributeNameKey;
extern NSString* const QCCompositionAttributeDescriptionKey;
extern NSString* const QCCompositionAttributeCopyrightKey;

/* Keys for input / output ports attributes */
extern NSString* const QCPortAttributeTypeKey;
extern NSString* const QCPortAttributeNameKey;
extern NSString* const QCPortAttributeMinimumValueKey;
extern NSString* const QCPortAttributeMaximumValueKey;

/* Possible values for the QCPortAttributeTypeKey corresponding to the possible types of input / output ports */
extern NSString* const QCPortTypeBoolean;
extern NSString* const QCPortTypeIndex;
extern NSString* const QCPortTypeNumber;
extern NSString* const QCPortTypeString;
extern NSString* const QCPortTypeColor;
extern NSString* const QCPortTypeImage;
extern NSString* const QCPortTypeStructure;

/* Defined in AppKit */
@class NSOpenGLContext, NSOpenGLPixelFormat;

/* QuartzComposer Composition Renderer */
@interface QCRenderer : NSObject
{
@private
	__strong void*		_QCRendererPrivate;
}

/*
Create a new renderer from a NSOpenGLContext and a QuartzComposer composition file.
The NSOpenGLContext must have both a color and a depth buffer.
If any error occurs during loading of the composition file, nil will be returned.
*/
- (id) initWithOpenGLContext:(NSOpenGLContext*)context pixelFormat:(NSOpenGLPixelFormat*)format file:(NSString*)path;

/*
Renders a frame for a given timestamp ("time" must be positive or null).
This method will not swap the buffers on the OpenGL context, so that you can combine QuartzComposer with custom OpenGL code.
All OpenGL states modified by the renderer are saved / restored except:
	- States defined by GL_CURRENT_BIT
	- Texture on each unit and the environment mode
	- Matrix mode
The "arguments" parameters is used to passed optional arguments to the patches of the composition:
	- Use "QCRuntimeEventKey" to pass the current NSEvent if any
	- Use "QCRuntimeMouseLocationKey" to pass the current mouse location in normalized coordinates relatively to the OpenGL context viewport ([0,1]x[0,1] with (0,0) at the lower-left corner) as a NSPoint stored in a NSValue
*/
- (BOOL) renderAtTime:(NSTimeInterval)time arguments:(NSDictionary*)arguments;

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
	- NSNumber or any object that responds to -intValue, -floatValue or -doubleValue for Boolean, Index and Number ports
	- NSString or any object that responds to -stringValue or -description for String ports
	- NSColor for Color ports
	- NSImage, CGImageRef, CIImage or CVImageBufferRef for Image ports
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

@end
