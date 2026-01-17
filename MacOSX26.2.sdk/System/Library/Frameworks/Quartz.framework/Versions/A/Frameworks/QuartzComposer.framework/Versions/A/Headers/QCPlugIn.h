/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <QuartzComposer/QuartzComposerDefines.h>

#import <Foundation/Foundation.h>
#import <ApplicationServices/ApplicationServices.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>

/* HIGH-LEVEL NOTES:
- QCPlugIn provides the base class to subclass in order to write custom patches for Quartz Composer.
- The plug-in is implemented by subclassing QCPlugIn and overriding the appropriate methods (there's no need to call super).
- All the methods related to the execution of the plug-in (called when the Quartz Composer engine is rendering) get passed an opaque object conforming to the <QCPlugInContext> protocol, which represents the execution context of the plug-in.
- Do not retain the plug-in context or use it outside of the scope of the execution method it was passed to.
- These execution methods should not assume they are called on the main thread of the process or that there is an active runloop available.
	It's the responsibility of the execution methods to ensure they can be called on any thread, and do not require a runloop to be running on the calling thread (they can however span a worker thread that would have a running runloop and handle communication with it).
- Like a standard patch in Quartz Composer, a plug-in defines a set of input and output ports through which it communicates.
- To minimize impedance issues within the Quartz Composer engine, only a restricted set of data types is supported when reading from / writing to ports:
	Boolean, Index, Number port <-> NSNumber (BOOL, NSUInteger, double)
	String port <-> NSString
	Color port <-> CGColorRef (always of type RGBA on input)
	Structure port <-> NSDictionary (and NSArray for Obj-C 2.0 property ports)
	Image port (input) -> id<QCPlugInInputImageSource>
	Image port (output) -> id<QCPlugInOutputImageProvider>
- If the plug-in class has Obj-C 2.0 properties whose names start with "input" or "output" and have a type or class corresponding to one of the supported port types, input / output ports are automatically created when a plug-in instance is created, and their values are "bound" to its properties.
	For instance, a "@property(dynamic) BOOL inputFoo" would turn into a Boolean input port with the key "inputFoo" on the plug-in, and accessing the "inputFoo" variable in the plug-in code actually gets the port value.
- Note that such property based ports are protected and cannot be deleted.
- The plug-in can also have dynamic ports which are explicitely created / deleted.
- Accessing dynamic port values is done with -valueForInputKey: and -setValue:forOutputKey:.
- Retrieving values from input ports and setting values on output ports can only be done from within -execute:atTime:withArguments:.
- Plug-ins must be packaged as Cocoa bundles with the ".plugin" extension and installed in /Library/Graphics/Quartz Composer Plug-Ins.
	The Info.plist of these bundles must have a "QCPlugInClasses" key that is an array listing the names of the QCPlugIn subclasses implemented in the bundle.
	The Resources of a plug-in may include example compositions that use the plug-in. Examples may also point to a web URL which describes the plug-in or shows samples of its usage.
- All supported pixel formats assume premultiplied alpha and those using multi-components per word (e.g. ARGB8) assume components to be in memory order (for instance, A first, then R, G, B for ARGB8)
*/

/* Keys for plug-in attributes */
#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
extern NSString* const QCPlugInAttributeNameKey QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPlugInAttributeDescriptionKey QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPlugInAttributeCopyrightKey QC_DEPRECATED_MAC(10_15);
#endif
#if defined(MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7)
extern NSString* const QCPlugInAttributeCategoriesKey QC_DEPRECATED_MAC(10_15); // Return an NSArray with category strings.
extern NSString* const QCPlugInAttributeExamplesKey QC_DEPRECATED_MAC(10_15); // Return an NSArray of examples. Examples may be NSURLs or NSString paths that are relative to the plug-in's Resources directory.
#endif

/* Keys for input / output ports attributes */
extern NSString* const QCPortAttributeTypeKey QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortAttributeNameKey QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortAttributeMinimumValueKey QC_DEPRECATED_MAC(10_15); //For Number ports only
extern NSString* const QCPortAttributeMaximumValueKey QC_DEPRECATED_MAC(10_15); //For Index and Number ports only
#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
extern NSString* const QCPortAttributeDefaultValueKey QC_DEPRECATED_MAC(10_15); //For value ports only (Boolean, Index, Number, Color and String)
extern NSString* const QCPortAttributeMenuItemsKey QC_DEPRECATED_MAC(10_15); //For Index ports only
#endif

/* Values for QCPortAttributeTypeKey corresponding to the possible types of input / output ports */
extern NSString* const QCPortTypeBoolean QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortTypeIndex QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortTypeNumber QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortTypeString QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortTypeColor QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortTypeImage QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPortTypeStructure QC_DEPRECATED_MAC(10_15);

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/* Supported image pixel formats */
extern NSString* const QCPlugInPixelFormatARGB8 QC_DEPRECATED_MAC(10_15); //Recommended on PPC for optimal performances
extern NSString* const QCPlugInPixelFormatBGRA8 QC_DEPRECATED_MAC(10_15); //Recommended on X86 for optimal performances
extern NSString* const QCPlugInPixelFormatRGBAf QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPlugInPixelFormatI8 QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPlugInPixelFormatIf QC_DEPRECATED_MAC(10_15);

/* Optional arguments received by -execute:atTime:withArguments: */
extern NSString* const QCPlugInExecutionArgumentEventKey QC_DEPRECATED_MAC(10_15);
extern NSString* const QCPlugInExecutionArgumentMouseLocationKey QC_DEPRECATED_MAC(10_15);

/* Supported execution modes for plug-ins */
typedef enum {
	kQCPlugInExecutionModeProvider = 1,
	kQCPlugInExecutionModeProcessor,
	kQCPlugInExecutionModeConsumer
} QCPlugInExecutionMode QC_DEPRECATED_MAC(10_15);;

/* Supported time modes for plug-ins */
typedef enum {
	kQCPlugInTimeModeNone = 0,
	kQCPlugInTimeModeIdle,
	kQCPlugInTimeModeTimeBase
} QCPlugInTimeMode QC_DEPRECATED_MAC(10_15);;

/* Callbacks */
typedef void (*QCPlugInBufferReleaseCallback)(const void* address, void* context) QC_DEPRECATED_MAC(10_15);;
typedef void (*QCPlugInTextureReleaseCallback)(CGLContextObj cgl_ctx, GLuint name, void* context) QC_DEPRECATED_MAC(10_15);;

/* Protocol for plug-ins execution context (do not retain context object) */
QC_CLASS_DEPRECATED_MAC(10_15)
@protocol QCPlugInContext

/*
Returns the URL of the composition corresponding to this plug-in context (might be nil if not available and is not necessarily a file URL either).
*/
- (NSURL*) compositionURL;

/*
Writes a message to the Quartz Composer log (which writes to the standard output by default).
Use this when needed to log messages instead of NSLog() or printf().
*/
- (void) logMessage:(NSString*)format, ...;

/*
A mutable dictionary the plug-in can use to store information it wants to share among instances running on the same plug-in context.
Make sure to use unique keys like "com.myCompany.foo".
*/
- (NSMutableDictionary*) userInfo;

/*
The colorspace of the context (always RGB type).
*/
- (CGColorSpaceRef) colorSpace;

/*
Bounds of the context expressed in Quartz Composer units.
*/
- (NSRect) bounds;

/*
The OpenGL context to draw in the context.
Copy this value into a local "CGLContextObj cgl_ctx" variable and use <OpenGL/CGLMacro.h> to send commands to the OpenGL context.
The plug-in must save / restore all the OpenGL states it changes except the ones defined by GL_CURRENT_BIT.
You can retrieve the corresponding OpenGL pixel format using CGLGetPixelFormat().
*/
- (CGLContextObj) CGLContextObj QC_GL_DEPRECATED(10_5, 10_14);

/*
Convenience method that returns an image provider from a single memory buffer, which must not be modified anymore until the release callback is called.
The pixel format and colorspace must be compatible, and both the base address and bytes per row must be multiple of 16.
The "shouldColorMatch" argument should be NO if the image should not be color matched (e.g. it's a mask or gradient).
The release callback must be defined and will be called and passed the base address and info arguments when the memory buffer is not needed anymore - note that the callback can be called from any thread at any time.
*/
- (id) outputImageProviderFromBufferWithPixelFormat:(NSString*)format pixelsWide:(NSUInteger)width pixelsHigh:(NSUInteger)height baseAddress:(const void*)baseAddress bytesPerRow:(NSUInteger)rowBytes releaseCallback:(QCPlugInBufferReleaseCallback)callback releaseContext:(void*)context colorSpace:(CGColorSpaceRef)colorSpace shouldColorMatch:(BOOL)colorMatch;

/*
Convenience method that returns an image provider from an OpenGL texture of type GL_TEXTURE_RECTANGLE_EXT, which must not be modified anymore until the release callback is called.
The pixel format and colorspace must be compatible, and the texture must be valid on the Quartz Composer OpenGL context.
The "shouldColorMatch" argument should be NO if the image should not be color matched (e.g. it's a mask or gradient).
The release callback must be defined and will be called and passed the texture name and info arguments when the OpenGL texture is not needed anymore - note that the callback can be called from any thread at any time.
*/
- (id) outputImageProviderFromTextureWithPixelFormat:(NSString*)format pixelsWide:(NSUInteger)width pixelsHigh:(NSUInteger)height name:(GLuint)name flipped:(BOOL)flipped releaseCallback:(QCPlugInTextureReleaseCallback)callback releaseContext:(void*)context colorSpace:(CGColorSpaceRef)colorSpace shouldColorMatch:(BOOL)colorMatch QC_GL_DEPRECATED(10_5, 10_14);

@end

/* Protocol for images received as inputs */
QC_CLASS_DEPRECATED_MAC(10_15)
@protocol QCPlugInInputImageSource

/*
Returns the actual bounds of the image source expressed in pixels and aligned to integer boundaries.
*/
- (NSRect) imageBounds;

/*
Returns the colorspace of the image source (typically RGB or Gray).
*/
- (CGColorSpaceRef) imageColorSpace;

/*
Returns NO if the image source should not be color matched (e.g. it's a mask or gradient).
*/
- (BOOL) shouldColorMatch;

/*
Creates a memory buffer representation from a subregion of the image source in a given pixel format and colorspace or returns NO on failure.
The colorspace and pixel format must be compatible.
The subregion bounds are expressed in pixels and must be aligned to integer boundaries.
The content of the buffer is read-only and must not be modified.
*/
- (BOOL) lockBufferRepresentationWithPixelFormat:(NSString*)format colorSpace:(CGColorSpaceRef)colorSpace forBounds:(NSRect)bounds;

/*
Returns the width and height of the buffer expressed in pixels (those match the actual image bounds).
*/
- (NSUInteger) bufferPixelsWide;
- (NSUInteger) bufferPixelsHigh;

/*
Returns the pixel format of the buffer.
*/
- (NSString*) bufferPixelFormat;

/*
Returns the colorspace of the buffer.
*/
- (CGColorSpaceRef) bufferColorSpace;

/*
Returns the base address and bytes per row of the buffer.
The base address is guaranteed to be 16 bytes aligned and the bytes per row a multiple of 16 as well.
*/
- (const void*) bufferBaseAddress;
- (NSUInteger) bufferBytesPerRow;

/*
Destroy the memory buffer representation of the image source.
*/
- (void) unlockBufferRepresentation;

/*
Creates an OpenGL texture representation from a subregion of the image source in a given colorspace or returns NO on failure.
The subregion bounds are expressed in pixels and must be aligned to integer boundaries.
Neither the content of the texture nor its states (e.g. wrap mode) must be modified: you can only draw with it.
The created texture is only valid in the plug-in context.
*/
- (BOOL) lockTextureRepresentationWithColorSpace:(CGColorSpaceRef)colorSpace forBounds:(NSRect)bounds QC_GL_DEPRECATED(10_5, 10_14);

/*
Returns the width and height of the texture expressed in pixels (those might not match the requested bounds if they were greater than the maximum supported texture size).
*/
- (NSUInteger) texturePixelsWide QC_GL_DEPRECATED(10_5, 10_14);
- (NSUInteger) texturePixelsHigh QC_GL_DEPRECATED(10_5, 10_14);

/*
Returns the target and name of the texture.
*/
- (GLenum) textureTarget QC_GL_DEPRECATED(10_5, 10_14);
- (GLuint) textureName QC_GL_DEPRECATED(10_5, 10_14);

/*
Returns the colorspace of the texture.
*/
- (CGColorSpaceRef) textureColorSpace QC_GL_DEPRECATED(10_5, 10_14);

/*
Returns true if the contents of the texture is flipped upside-down.
*/
- (BOOL) textureFlipped QC_GL_DEPRECATED(10_5, 10_14);

/*
Returns an optional 4x4 texture matrix to be applied to the texture coordinates or NULL if identity.
*/
- (const GLfloat*) textureMatrix QC_GL_DEPRECATED(10_5, 10_14);

/*
Convenience method that bind the texture to a given texture unit (GL_TEXTURE0...) - it also loads the optional texture matrix on the texture matrix stack.
If "flag" is YES, another texture matrix will be applied if necessary to scale coordinates (from [0, pixels] to [0,1]) and / or flip them vertically.
Make sure that each call to -bindTextureRepresentationToCGLContext is balanced with a call to -unbindTextureRepresentationFromCGLContext.
*/
- (void) bindTextureRepresentationToCGLContext:(CGLContextObj)cgl_ctx textureUnit:(GLenum)unit normalizeCoordinates:(BOOL)flag QC_GL_DEPRECATED(10_5, 10_14);
- (void) unbindTextureRepresentationFromCGLContext:(CGLContextObj)cgl_ctx textureUnit:(GLenum)unit QC_GL_DEPRECATED(10_5, 10_14);

/*
Destroy the OpenGL texture representation of the image source.
*/
- (void) unlockTextureRepresentation QC_GL_DEPRECATED(10_5, 10_14);

@end

/* Protocol for images produced as outputs */
QC_CLASS_DEPRECATED_MAC(10_15)
@protocol QCPlugInOutputImageProvider

/*
Returns the bounds of the image expressed in pixels and aligned to integer boundaries.
*/
- (NSRect) imageBounds;

/*
Returns the colorspace of the image.
*/
- (CGColorSpaceRef) imageColorSpace;

@optional

/*
Returns NO if the image should not be color matched (e.g. it's a mask or gradient) - YES by default.
*/
- (BOOL) shouldColorMatch;

/*
Returns the list of memory buffer pixel formats supported by -renderToBuffer (or nil if not supported) - nil by default.
*/
- (NSArray*) supportedBufferPixelFormats;

/*
Renders a subregion of the image into a memory buffer of a given pixel format or returns NO on failure.
The base address is guaranteed to be 16 bytes aligned and the bytes per row a multiple of 16 as well.
*/
- (BOOL) renderToBuffer:(void*)baseAddress withBytesPerRow:(NSUInteger)rowBytes pixelFormat:(NSString*)format forBounds:(NSRect)bounds;

/*
Returns the list of texture pixel formats supported by -copyRenderedTextureForCGLContext (or nil if not supported) - nil by default.
If this methods returns nil, then -canRenderWithCGLContext / -renderWithCGLContext are called.
*/
- (NSArray*) supportedRenderedTexturePixelFormats QC_GL_DEPRECATED(10_5, 10_14);

/*
Returns the name of an OpenGL texture of type GL_TEXTURE_RECTANGLE_EXT that contains a subregion of the image in a given pixel format - 0 by default.
The "flipped" parameter must be set to YES on output if the contents of the returned texture is vertically flipped.
Use <OpenGL/CGLMacro.h> to send commands to the OpenGL context.
Make sure to preserve all the OpenGL states except the ones defined by GL_CURRENT_BIT.
*/
- (GLuint) copyRenderedTextureForCGLContext:(CGLContextObj)cgl_ctx pixelFormat:(NSString*)format bounds:(NSRect)bounds isFlipped:(BOOL*)flipped QC_GL_DEPRECATED(10_5, 10_14);

/*
Called to release the previously copied texture.
Use <OpenGL/CGLMacro.h> to send commands to the OpenGL context.
Make sure to preserve all the OpenGL states except the ones defined by GL_CURRENT_BIT.
*/
- (void) releaseRenderedTexture:(GLuint)name forCGLContext:(CGLContextObj)cgl_ctx QC_GL_DEPRECATED(10_5, 10_14);

/*
Performs extra checkings on the capabilities of the OpenGL context (e.g check for supported extensions) and returns YES if the image can be rendered into this context - NO by default.
Use <OpenGL/CGLMacro.h> to send commands to the OpenGL context.
If this methods returns NO, then -renderToBuffer is called.
*/
- (BOOL) canRenderWithCGLContext:(CGLContextObj)cgl_ctx QC_GL_DEPRECATED(10_5, 10_14);

/*
Renders a subregion of the image with the provided OpenGL context or returns NO on failure.
Use <OpenGL/CGLMacro.h> to send commands to the OpenGL context.
The viewport is already set to the proper dimensions and the projection and modelview matrices are identity.
The rendering must save / restore all the OpenGL states it changes except the ones defined by GL_CURRENT_BIT.
*/
- (BOOL) renderWithCGLContext:(CGLContextObj)cgl_ctx forBounds:(NSRect)bounds QC_GL_DEPRECATED(10_5, 10_14);

@end

/* The abstract plug-in class */
QC_CLASS_DEPRECATED_MAC(10_15)
@interface QCPlugIn : NSObject
{
@private
	void*			_private;
}

/*
Override this method to return a dictionary of attributes describing the plug-in.
The dictionary can contain one or more of these keys: QCPlugInAttributeNameKey, QCPlugInAttributeDescriptionKey, QCPlugInAttributeCopyrightKey.
*/
+ (NSDictionary*) attributes;

/*
Override this method to specify the optional attributes for property based ports (QCPortAttribute...).
*/
+ (NSDictionary*) attributesForPropertyPortWithKey:(NSString*)key;

/*
Override this method to specify an optional ordering for property based ports in the user interface.
*/
+ (NSArray*) sortedPropertyPortKeys;

/*
Override this method to specify the execution mode of the plug-in:
- kQCPlugInExecutionModeProvider: The plug-in executes on demand—that is, whenever data is requested of it, but at most once per frame.
- kQCPlugInExecutionModeProcessor: The plug-in executes whenever its inputs change or if the time change (assuming it's time-dependent).
- kQCPlugInExecutionModeConsumer: The plug-in always executes assuming its "Enable" input (automatically added by the system) is true.
Note that a consumer plug-in can render with OpenGL to the plug-in context, but cannot have output ports.
*/
+ (QCPlugInExecutionMode) executionMode;

/*
Override this method to specify the time dependency of the plug-in:
- kQCPlugInTimeModeNone: The plug-in does not depend on time at all (it does not use the "time" parameter of the execute -execute:atTime:withArguments: method).
- kQCPlugInTimeModeIdle: The plug-in does depend on time implicitely and needs the system to execute it periodically (it still does not use the "time" parameter of the execute -execute:atTime:withArguments: method).
- kQCPlugInTimeModeTimeBase: The plug-in does depend on time explicitely and has a timebase defined by the system (it does uses the "time" parameter of the execute -execute:atTime:withArguments: method).
*/
+ (QCPlugInTimeMode) timeMode;

/*
Override this method to return the list of KVC keys representing the internal settings of the plug-in.
This list of keys is used for automatic serialization of these internal settings.
It's also used by the QCPlugInViewController object that drives the user interface to edit the internal settings.
*/
+ (NSArray*) plugInKeys;

/*
Override this execution method if the plug-in needs to perform some setup before the Quartz Composer engine starts rendering.
Returning NO indicates a fatal error occured and prevents the Quartz Composer engine to start rendering.
*/
- (BOOL) startExecution:(id<QCPlugInContext>)context;

/*
Override this execution method if the plug-in needs to know when the Quartz Composer engine starts using it.
*/
- (void) enableExecution:(id<QCPlugInContext>)context;

/*
Override this execution method in order to describe when a time dependent plug-in should be executed next.
*/
- (NSTimeInterval) executionTimeForContext:(id<QCPlugInContext>)context atTime:(NSTimeInterval)time withArguments:(NSDictionary*)arguments;

/*
Override this execution method to perform the actual processing or rendering: read from the input ports and update the output ports or render to the plug-in context.
The "arguments" dictionary can contain these optional keys:
- QCPlugInExecutionArgumentEventKey: The current NSEvent if available.
- QCPlugInExecutionArgumentMouseLocationKey: The current location of the mouse (as an NSPoint object stored in an NSValue object) in normalized coordinates relative to the OpenGL context viewport ([0,1]x[0,1] with the origin (0,0) at the lower-left corner).
Returning NO indicates the plug-in was not able to execute successfully and the Quartz Composer engine aborts rendering of the current frame.
*/
- (BOOL) execute:(id<QCPlugInContext>)context atTime:(NSTimeInterval)time withArguments:(NSDictionary*)arguments;

/*
Override this execution method if the plug-in needs to know when the Quartz Composer engine stops using it.
*/
- (void) disableExecution:(id<QCPlugInContext>)context;

/*
Override this execution method if the plug-in needs to perform some cleanup after the Quartz Composer engine stops rendering.
*/
- (void) stopExecution:(id<QCPlugInContext>)context;

/*
Override this method if the plug-in needs to handle serialization of one or more of its internal settings (typically if the result of -valueForKey: does not conform to the <NSCoding> protocol).
The returned result must be a Plist compliant object i.e. exclusively NSString, NSNumber, NSDate, NSData, NSArray, NSDictionary.
The default implementation calls -valueForKey: to retrieve the value for the key, then does nothing for NSString, NSNumber, NSDate and use <NSCoding> encoding for others.
*/
- (id) serializedValueForKey:(NSString*)key;

/*
Override this method if the plug-in overrides -serializedValueForKey: in order to perform the deserializing operation.
The default implementation calls -setValue:forKey: after decoding the serialized value if necessary.
*/
- (void) setSerializedValue:(id)serializedValue forKey:(NSString*)key;

@end

QC_CLASS_DEPRECATED_MAC(10_15)
@interface QCPlugIn (Ports)

/*
Returns YES if the value on a given input port of the plug-in has changed since the last time -execute:atTime:withArguments: was called.
This will return YES for the first execution and always NO if called outside of -execute:atTime:withArguments:.
*/
- (BOOL) didValueForInputKeyChange:(NSString*)key;

/*
Returns the current value on a given input port of the plug-in.
This will always return nil if called outside of -execute:atTime:withArguments:.
*/
- (id) valueForInputKey:(NSString*)key;

/*
Sets a new value on a given output port of the plug-in and returns YES on success.
This will always return NO if called outside of -execute:atTime:withArguments:.
*/
- (BOOL) setValue:(id)value forOutputKey:(NSString*)key;

/*
Adds an input port of a given type (QCPortType...) and key on the plug-in, and with optional attributes (QCPortAttribute...).
This method will throw an exception if called from within an execution method, or if there's already an input or output port with that key.
*/
- (void) addInputPortWithType:(NSString*)type forKey:(NSString*)key withAttributes:(NSDictionary*)attributes;

/*
Removes the input port for a given key from the plug-in.
This method will throw an exception if called from within an execution method, or if there's no input port with that key or if the port is a property based port.
*/
- (void) removeInputPortForKey:(NSString*)key;

/*
Adds an output port of a given type (QCPortType...) and key on the plug-in, and with optional attributes (QCPortAttribute...).
This method will throw an exception if called from within an execution method, or if there's already an input or output port with that key.
*/
- (void) addOutputPortWithType:(NSString*)type forKey:(NSString*)key withAttributes:(NSDictionary*)attributes;

/*
Removes the output port for a given key from the plug-in.
This method will throw an exception if called from within an execution method, or if there's no output port with that key or if the port is a property based port.
*/
- (void) removeOutputPortForKey:(NSString*)key;

@end

/* The plug-in registry */
QC_CLASS_DEPRECATED_MAC(10_15)
@interface QCPlugIn (Registry)

/*
Attempts to load a Quartz Composer plug-in from a .plugin bundle at the specified path and returns YES on success.
This method will do nothing if the plug-in was already loaded.
*/
+ (BOOL) loadPlugInAtPath:(NSString*)path;

/*
Register a plug-in class with the plug-in registry (the class must be a subclass of QCPlugIn).
This method will do nothing if the class is already registered.
*/
+ (void) registerPlugInClass:(Class)aClass;

@end

#endif
