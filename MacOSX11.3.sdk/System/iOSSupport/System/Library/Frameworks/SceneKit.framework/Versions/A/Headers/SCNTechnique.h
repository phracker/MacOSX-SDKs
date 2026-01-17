//
//  SCNTechnique.h
//  SceneKit
//
//  Copyright © 2014-2020 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNShadable.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNTechnique
 @abstract SCNTechnique represents a rendering process that may require multiple passes.
 @discussion A technique is generally initialized from a Property List file. It can be set to any object that conforms to the SCNTechniqueSupport protocol.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNTechnique : NSObject <SCNAnimatable, NSCopying, NSSecureCoding>

/*!
 @method techniqueWithDictionary:
 @abstract Creates and returns a technique instance initialized with the specified dictionary.
 @param dictionary The dictionary representation of the technique.
 @discussion The format of the dictionary is described below. Quoted strings can be any name of your choice. Tags are defined below.
 The passes are executed sequentially as specified in the "sequence" section. The definition of each pass is within the "passes" section. A pass may have inputs/outputs that reference targets or symbols defined in the "targets" and "symbols" section. The entries of the "symbols" section can be set/get and animated with SCNTechnique's APIs below.
 
 {
   sequence: ["Pass1", "Pass2", ...],
   passes: {
     "Pass1": {
        outputs: <outputs>
        inputs: <inputs>
        draw: <draw command>
        program: <program name>
        metalVertexShader: <METAL vertex shader function name>
        metalFragmentShader: <METAL fragment shader function name>
        colorStates: <color states>               //optional
        depthStates: <depth states>               //optional
        stencilStates: <stencil states>           //optional
        cullMode: <cull mode>                     //optional
        blendStates: <blend states>               //optional
        viewport: <custom viewport>               //optional
        pointOfView: <node name>                  //optional
        samples: <sample count>                   //optional
        excludeCategoryMask: <category bitMask>   //optional
        includeCategoryMask: <category bitMask>   //optional
     },
     "Pass2" : { 
         [...]
     }
   }
   symbols: {
     "symbol A": {
        <symbol description>
     }
     [...]
   }
   targets: {
      "target A": {
         <target description>
     }
     [...]
   },

   //optional

   bundle: <bundleIdentifier>,
   metalLibraryName: <metalLibraryName>,
}

<outputs>:
 The possible (and optional) keys with their possible associated values are:
 color: a string referencing a color render target. See <render target reference>.
 depth: a string referencing a depth render target. See <render target reference>.
 stencil: a string referencing a stencil render target. See <render target reference>.
 
<inputs>:
The inputs are listed in a dictionary. The keys are the uniform name as specified in the program of this pass.
The values can be a single string referencing a symbol or a semantic or a target OR a dictionary with the following structure:
 
 {
   target: <render target reference>,
 
   //optional:
   minificationFilter: linear, nearest
   magnificationFilter: linear, nearest
   mipFilter: linear, nearest, none
   wrapS: clamp, repeat, clampToBorder, mirror
   wrapT: clamp, repeat, clampToBorder, mirror
   wrapP: clamp, repeat, clampToBorder, mirror
   maxAnisotropy: a number
 }
 
 (See SCNMaterialProperty for more documentation and default values of these optional parameters.)
 
<render target reference>
 A string referencing a target (i.e an entry in the top level "targets" dictionary) or one of the special strings below:
 COLOR  The render target that represents that main color fragments that will be displayed on the screen ultimately.
 DEPTH  The render target that represents that main depth fragments.
 
<draw command>
 can be one of the following strings:
 DRAW_SCENE:    render the entire scene
 DRAW_QUAD:     render a fullscreen quad
 DRAW_NODE:     render a node and its sub-tree. The node is specified by setting its name as the value for the key "node".
 
<program name>
 Name of a program (a vertex shader + a fragment shader) located in the application bundle.
 The vertex shader must have the extension "vsh" and the fragment shader "fsh".
 
<METAL vertex shader function name>
 Name of a METAL function to use as the vertex shader.

<METAL fragment shader function name>
 Name of a METAL function to use as the fragment shader.
 
<color states>
 A dictionary with the following optional keys:
 "clear" a boolean specifying whether the color target should be cleared or not
 "clearColor" a string specifying the clear color as 4 float ("red green blue alpha"), or the string "sceneBackground" to clear with the scene background color.
 
<depth states>
 A dictionary with the following optional keys:
 "clear" a boolean specifying whether the depth target should be cleared or not
 "enableWrite" a boolean specifying whether writing to depth should be enabled or not.
 "enableRead" a boolean specifying whether reading from depth should be enabled or not.
 "func" a string specifying depth function to use. See <comparison function> for the possible values.

<stencil states>
 A dictionary with the following optional keys:
 "clear" a boolean specifying whether the stencil target should be cleared or not
 "enable" a boolean specifying whether writing to stencil should be enabled or not.
 "behavior" a dictionary describing the stencil behavior of the front face, or of both faces if no backFaceBehavior is specified. See <stencil behavior> for the format of this dictionary.
 "backFaceBehavior" a dictionary describing the behavior of the back face. See <stencil behavior> for the format of this dictionary.
 
<stencil behavior>
 A dictionary with the following optional keys:
 "depthFail" a string specifying the operation to do if the depth test fails. See <stencil operation> for the possible values.
 "fail" a string specifying the operation to do if the stencil test fails. See <Stencil operation> for the possible values.
 "pass" a string specifying the operation to do if the stencil test passes. See <stencil operation> for the possible values.
 "function" a string specifying the stencil test. See <comparison function> for the possible values.
 "readMask" a uint8_t number specifying a mask that is ANDed with both the reference value and the stored stencil value when the test is done
 "writeMask" a uint8_t number specifies a bit mask to enable and disable writing of individual bits in the stencil planes
 "referenceValue" a uint8_t number specifies the reference value for the stencil test. The initial value is 0. 
 
<stencil operation>
 A string specifying a stencil operation. It can be one of the following: keep, zero, replace, increment, decrement, invert, incrementWrap, decrementWrap
 
<comparison function>
 A string specifying a comparison function. It can be one of the following: never, always, equal, notEqual, less, lessEqual, greater, greaterEqual
 
<blend states>
 A dictionary with the following optional keys:
 "enable" a boolean number specifying if the blending should be enabled or not. defaults to true.
 "colorSrc" a string specifying a blend mode. See <blend mode>
 "colorDst" a string specifying a blend mode. See <blend mode>
 "alphaSrc" a string specifying a blend mode. See <blend mode>
 "alphaDst" a string specifying a blend mode. See <blend mode>
 "colorOp" a string specifying a blend operation. See <blend operation>
 "alphaOp" a string specifying a blend operation. See <blend operation>
 In no Blend states are specified, then the blending is turned off.
 
<blend mode>
 A string specifying a blend mode. It can be one of the following: zero, one, srcColor, oneMinusSrcColor, srcAlpha, oneMinusSrcAlpha, dstColor, oneMinusDstColor, dstAlpha, oneMinusDstAlpha, constantColor, oneMinusConstantColor, constantAlpha, oneMinusConstantAlpha, alphaSaturate.
 
<blend operation>
 A string specifying a blend operation. It can be one of the following: add, substract, reverseSubstract, min, max.

<cull mode>
 A string specifying a cull mode. It can be one of the following: front, none, back.
 
<custom viewport>
 A string specifying the viewport as 4 float.

<category bitMask>
 A integer value representing a node category mask (see SCNNode's categoryBitMask).
 if the key "excludeCategoryMask" is not specified then it defaults to 0.
 if the key "includeCategoryMask" is not specified then it defaults to all bits set.
 The DRAW_SCENE command will then render nodes that validate the following test (node.categoryBitMask & includeCategoryMask) && !(excludeCategoryMask & node.categoryBitMask).

<node name>
 The name of a node, or "self" to reference the owner of the technique if any.

<sample count>
 The number of samples (multisampling) used to render the pass.
 
<symbol description>
 A dictionary with the following optional keys and their possible associated values:
 
 semantic: vertex, normal, color, texcoord, tangent, time, modelViewProjectionTransform, modelViewTransform, modelTransform, viewTransform, projectionTransform, normalTransform, modelViewProjectionInverseTransform, modelViewInverseTransform, modelInverseTransform, viewInverseTransform, projectionInverseTransform, normalInverseTransform
 
 type: float, vec2, vec3, vec4, mat4, int, ivec2, ivec3, ivec4, mat3, sampler2D, none. Every types can also be an array of the given type by adding [N] where N is the number of elements in the array.
 
 image: name of an image located in the application bundle. (only valid when type is sampler2D)
 
 if a semantic is set, no type is required.
 Note that with Metal shaders you should not provide any semantic. Instead simply declare a struct in you shader and add the members you need named as specified in SceneKit/scn_metal.
 
 For example for a per-node semantic:
 
 struct MyStruct
 {
 float4x4 modelTransform;
 float4x4 modelViewProjectionTransform;
 };
 then in your function add an argument that must be named “scn_node” to get the members automatically filed with node semantics (see the documentation in scn_metal).
 
<target description>
 A dictionary with the following optional keys and their possible associated values:
 
 type: a string specifying the type of the render target. It can be one of the following: color, depth, stencil
 format: a string specifying the format of the render target. It can be:
 - for color targets: rgba32f, r8, r16f, rg16 or rgba. If not specified defaults to the framebuffer's pixel format.
 - for depth targets: depth24, depth24stencil8
 - for stencil targets: depth24stencil8
 scaleFactor: a float value (encapsulated in a NSNumber) that controls the size of the render target. Defaults to 1, which means 1x the size of the main viewport.
 size: a string with the format %dx%d that controls the size of the render target.
 persistent: a boolean that tells if this target should persist from one frame to the next. It permits to create temporal effects suchs as motion blur. Defaults to NO.

 <bundleIdentifier>
 An optional bundle identifier to load metal programs from

 <metalLibraryName>
 An optional metal library name to load metal programs from. The metallib file is located from the default or specified bundle using NSBundle pathForResource:ofType:.
 */
+ (nullable SCNTechnique *)techniqueWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

/*!
 @method techniqueBySequencingTechniques:
 @abstract Creates and returns a technique by sequencing the passes from the specified techniques.
 @param techniques The techniques to sequence.
 @discussion The passes from "techniques" are executed sequentially. The symbols and targets are merged. This allows to use the same uniform ad targets across multiple techniques.
 */
+ (nullable SCNTechnique *)techniqueBySequencingTechniques:(NSArray<SCNTechnique *> *)techniques;

/*!
 @method handleBindingOfSymbol:usingBlock:
 @abstract Sets the block to call at render time to bind the value for the specified symbol of the receiver. 
 @param symbol The name of the symbol to bind a value for.
 @param block The block to call to bind the specified symbol.
 @discussion The block will be called at every frame for every pass referencing the specified symbol.
 */
- (void)handleBindingOfSymbol:(NSString *)symbol usingBlock:(nullable SCNBindingBlock)block;

/*!
 @property dictionaryRepresentation
 @abstract Returns the dictionary representation of the technique.
 */
@property(readonly) NSDictionary<NSString *, id> *dictionaryRepresentation;

/*
 SCNTechnique is a key-value coding compliant class, which means that you can set values for arbitrary keys. Even if the key `myAmplitude` is not a declared property of the class, you can still set a value for it.
 If the Property List file declares the `myAmplitude` symbol, any change to the `myAmplitude` property of the receiver will make SceneKit bind the associated uniform with the new value.
 
 Symbols can be animated using explicit animations.
 
 The following GLSL types (and Objective-C counterparts) can be used to bind symbols:
 
 GLSL types    | Objective-C types
 --------------------------------------
 int           | NSNumber, NSInteger, int
 float         | NSNumber, CGFloat, float, double
 vec2          | CGPoint
 vec3          | SCNVector3
 vec4          | SCNVector4
 mat4, mat44   | SCNMatrix4
 
 On macOS 10.11 or later and iOS 9 or later you can also use the object subscripting syntax to set values to uniforms.
 For example:
 myTechnique[@"myAmplitude"] = aValue;
 */
- (nullable id)objectForKeyedSubscript:(id)key API_AVAILABLE(macos(10.11), ios(9.0));
- (void)setObject:(nullable id)obj forKeyedSubscript:(id <NSCopying>)key API_AVAILABLE(macos(10.11), ios(9.0));

#if SCN_ENABLE_METAL
/*!
 @property library
 @abstract The Metal library to use to load the Metal programs specified in the technique description. Defaults to nil which corresponds to the default Metal library.
 */
@property(nonatomic, strong, nullable) id <MTLLibrary> library API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0)) API_UNAVAILABLE(watchos);
#endif

@end



/*!
 @protocol SCNTechniqueSupport
 @abstract The SCNTechniqueSupport protocol describes an object that supports single or multi-pass techniques
 */
@protocol SCNTechniqueSupport <NSObject>

/*!
 @property technique
 @abstract Specifies the technique of the receiver. Defaults to nil.
 */
@property(nonatomic, copy, nullable) SCNTechnique *technique API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END
