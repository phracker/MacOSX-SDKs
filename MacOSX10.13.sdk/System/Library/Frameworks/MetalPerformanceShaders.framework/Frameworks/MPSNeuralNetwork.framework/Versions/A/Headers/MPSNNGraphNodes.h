/*!
 *  @header MPSNNGraphNodes.h
 *  @framework MetalPerformanceShaders
 *
 *  Created by Ian Ollmann on 10/19/16.
 *  @copyright Copyright © 2016 Apple. All rights reserved.
 *
 *  @discussion This header describes building blocks to prepare a graph
 *              of MPS images, kernels and state objects. You should prepare
 *              your graph by creating a MPSNNImageNode for each of the
 *              graph input textures. These are then used as inputs to
 *              MPSNNFilterNode subclasses. These in turn produce more 
 *              image nodes as results, which can be linked to more 
 *              MPSNNFilterNodes as inputs.  When the graph representation
 *              is complete, make a MPSNNGraph object to interpret and
 *              optimize the graph. The MPSNNGraph may be used to encode 
 *              the entire graph on a MTLCommandBuffer.
 *
 *              Objects presented here are generally light weight. They do not
 *              have a MTLDevice reference, and so can not create MTLResource
 *              objects. In the few cases when data is expected to be large
 *              (e.g. convolution weights), the nodes are designed to defer
 *              allocation of storage, preferring to leave them on disk or network
 *              or other persistent storage to hold the data until it is actually
 *              needed to initialize a MPSKernel object.  Not until the MPSNNGraph 
 *              is constructed does the heavy lifting begin. MPSNNGraphs in 
 *              contrast can be extremely heavy. A large graph may use most of 
 *              the memory available to your system!  Nearly all of this is due 
 *              to convolution weights. Construct your <MPSCNNConvolutionDataSource>
 *              to only load data when it is needed.
 */

#ifndef MPSNNGraphNodes_h
#define MPSNNGraphNodes_h

#include <MPSCore/MPSImage.h>
#include <MPSCore/MPSState.h>
#include <MPSNeuralNetwork/MPSNeuralNetworkTypes.h>
#include <MPSNeuralNetwork/MPSCNNNeuronType.h>

#pragma mark -
#pragma mark Base Classes


/*! @protocol   MPSHandle
 *  @abstract   MPS resource identification
 *  @discussion Most of the time, there is only one image and one or fewer states needed as 
 *              input to a graph, so the order of the images and states passed to
 *              [MPSNNGraph encodeToCommandBuffer:sourceImages:] or 
 *              [MPSNNGraph encodeToCommandBuffer:sourceImages:sourceStates:intermediateImages:destinationStates:] 
 *              is clear. There is only one order. However, sometimes graphs have more than one 
 *              input image or state. What order should they appear in the NSArray passed to 
 *              these methods? 
 *
 *              Each MPSNNImageNode or MPSNNStateNode can be tagged with a MPSHandle. MPSNNGraph 
 *              keeps track of these. You can request that the MPSNNGraph return them to you in 
 *              an array in the same order as needed to encode the MPSNNGraph, using 
 *              MPSNNGraph.sourceImageHandles and MPSNNGraph.sourceStateHandles.
 *
 *              Example:
 *              @code
 *              @interface MyHandle : NSObject <MPSHandle>
 *                  // Add a method for my use to get the image needed based on the handle to it.
 *                  // This isn't part of the MPSHandle protocol, but we need it for MyEncodeGraph
 *                  // below. Since it is my code calling my object, we can add whatever we want like this.
 *                  -(MPSImage*__nonnull) image;    // return the MPSImage corresponding to the handle
 *
 *                  // required by MPSHandle protocol
 *                  -(NSString * __nullable) label;
 *
 *                  // MPSHandle implies NSSecureCoding too
 *                  +(BOOL) supportsSecureCoding;
 *                  - (void)encodeWithCoder:(NSCoder * __nonnull )aCoder;
 *                  - (nullable instancetype)initWithCoder:(NSCoder * __nonnull )aDecoder; // NS_DESIGNATED_INITIALIZER
 *              @end
 *
 *              // Encode a graph to cmdBuf using handles for images
 *              // Here we assume that the MPSNNImageNodes that are graph inputs (not produced 
 *              // by the graph) are tagged with a unique instance of MyHandle that can be used 
 *              // to get the appropriate image for that node.
 *              static void MyEncodeGraph( MPSNNGraph * graph, id <MTLCommandBuffer> cmdBuf )
 *              {
 *                  @autoreleasepool{
 *                      // prepare an array of source images, using the handles
 *                      NSArray<MyHandle*> * handles = graph.sourceImageHandles;
 *                      unsigned long count = handles.count;
 *                      NSMutableArray<MPSImage*> * __nonnull images = [NSMutableArray arrayWithCapacity: count];
 *                      for( unsigned long i = 0; i < count; i++ )
 *                          images[i] = handles[i].image;
 *
 *                      // encode the graph using the array
 *                      [ graph encodeToCommandBuffer: cmdBuf
 *                                       sourceImages: images ];
 *                  }
 *              }
 *              @endcode
 */
@protocol MPSHandle <NSSecureCoding, NSObject>

@required
/*! @abstract   A label to be attached to associated MTLResources for this node
 *  @return     A human readable string for debugging purposes
 */
-(NSString * __nullable) label;

/* Note: You must also implement the NSSecureCoding protocol. These objects will be
 *       serialized along with the MPSNNGraph when it is serialized. */
@end

/*! @class      MPSNNImageNode
 *  @abstract   A placeholder node denoting the position of a MPSImage in a graph
 *  @discussion MPS neural network graphs are made up of filter nodes connected by
 *              image (or state) nodes. An image node is produced by one filter but
 *              may be consumed by more than one filter.
 *
 *              Most image nodes will be created by MPS and made available through
 *              MPSNNFilterNode.resultImage. Image nodes that are not created by MPS
 *              (i.e. "the graph inputs") must be created by you.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNImageNode : NSObject

-(nonnull instancetype) initWithHandle: (NSObject <MPSHandle> * __nullable) handle NS_DESIGNATED_INITIALIZER;
+(nonnull instancetype) nodeWithHandle: (NSObject <MPSHandle> * __nullable) handle;

/*! @abstract Create a autoreleased MPSNNImageNode with exportFromGraph = YES.
 *  @discussion Note: image is still temporary. See MPSNNImageNode.imageAllocator parameter. */
+(nonnull instancetype) exportedNodeWithHandle: (NSObject <MPSHandle> * __nullable) handle;

-(nonnull instancetype) init    NS_UNAVAILABLE;

/*! @abstract   MPS resource identifier
 *  @discussion See MPSHandle protocol description.  Default: nil
 */
@property (nonatomic, nullable, readwrite, retain) id <MPSHandle>   handle;

/*! @abstract   The preferred precision for the image
 *  @discussion Default: MPSImageFeatureChannelFormatNone, meaning MPS should pick a format
 *                       Typically, this is 16-bit floating-point.
 */
@property (nonatomic, readwrite) MPSImageFeatureChannelFormat   format;

/*! @abstract   Configurability for image allocation
 *  @discussion Allows you to influence how the image is allocated
 *              Default: MPSTemporaryImage.defaultAllocator  */
@property (readwrite, nonatomic, nonnull, retain) id <MPSImageAllocator>  imageAllocator;

/*  The height, width, number of feature channels, and number of most image nodes is automatically determined from
 *  the size of the input images presented to the graph. Please use [MPSNNGraph resultDescriptorForSourceImages:]
 *  to find the size of the output image. */

/*! @abstract   Tag a image node for view later
 *  @discussion Most image nodes are private to the graph. These alias memory heavily and
 *              consequently generally have invalid state when the graph exists.  When 
 *              exportFromGraph = YES, the image is preserved and made available through
 *              the [MPSNNGraph encode... intermediateImages:... list. 
 *
 *              CAUTION: exporting an image from a graph prevents MPS from 
 *                       recycling memory. It will nearly always cause the
 *                       amount of memory used by the graph to increase by the size
 *                       of the image. There will probably be a performance
 *                       regression accordingly.  This feature should generally
 *                       be used only when the node is needed as an input for
 *                       further work and recomputing it is prohibitively costly.
 *
 *              Default: NO
 */
@property (nonatomic, readwrite) BOOL       exportFromGraph;

@end

/*! @class      MPSNNStateNode
 *  @abstract   A placeholder node denoting the position in the graph of a MPSState object
 *  @discussion Some filters need additional information about an image in order to function. For example
 *              an unpooling max filter needs to know which position the max result came from in the
 *              original pooling filter in order to select the right data for unpooling.  In other cases,
 *              state may be moved into a MPSState object in order to keep the filter itself immutable.
 *              The MPSState object typically encapsulates one or more MTLResource objects.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNStateNode : NSObject
-(nonnull instancetype) init NS_UNAVAILABLE;    // These are typically obtained using  MPSNNFilterNode.resultState
                                                // If you do need a state node, make a MPSNNStateNode subclass, instead.
/*! @abstract   MPS resource identification
 *  @discussion See MPSHandle protocol reference.  Default: nil
 */
@property (nullable, retain, nonatomic) id <MPSHandle> handle;
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNConvolutionStateNode : MPSNNStateNode
@end

/*! @class      MPSNNFilterNode
 *  @abstract   A placeholder node denoting a neural network filter stage
 *  @discussion There are as many MPSNNFilterNode subclasses as there are
 *              MPS neural network filter objects. Make one of those. 
 *              This class defines an polymorphic interface for them.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNFilterNode : NSObject

/* This is a virtual base class. Make MPSNNFilterNode subclass objects instead. */
-(nonnull instancetype) init    NS_UNAVAILABLE;


/*! @abstract   Get the node representing the image result of the filter 
 *  @discussion Except where otherwise noted, the precision used for the 
 *              result image (see format property) is copied from the precision 
 *              from the first input image node.
 */
@property (nonatomic, readonly, nonnull) MPSNNImageNode * resultImage;

/*! @abstract   convenience method for resultStates[0]
 *  @discussion  If resultStates is nil, returns nil */
@property (nonatomic, readonly, nullable) MPSNNStateNode * resultState;

/*! @abstract   Get the node representing the state result of the filter
 @discussion If more than one, see description of subclass for ordering. */
@property (nonatomic, readonly, nullable) NSArray<MPSNNStateNode*> * resultStates;

/*! @abstract   The padding method used for the filter node
 *  @discussion The default value varies per filter.
 */
@property (nonatomic, readwrite, retain, nonnull) id <MPSNNPadding> paddingPolicy;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

@end

#pragma mark -
#pragma mark Convolution Nodes

@class MPSCNNConvolutionDescriptor;
@protocol MPSCNNConvolutionDataSource;

/*! @abstract   A MPSNNFilterNode representing a MPSCNNConvolution kernel   */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNConvolutionNode : MPSNNFilterNode
/*! @abstract   Init an autoreleased not representing a MPSCNNConvolution kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @return     A new MPSNNFilter node for a MPSCNNConvolution kernel.  */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights;

/*! @abstract   Init a node representing a MPSCNNConvolution kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @return     A new MPSNNFilter node for a MPSCNNConvolution kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights;

/*! @abstract   A node to represent a MPSCNNConvolutionState object
 *  @discussion  Use this if the convolution is mirrored by a convolution transpose node
 *               later on in the graph to make sure that the size of the image returned
 *               from the convolution transpose matches the size of the image passed in
 *               to this node. */
@property (nonatomic, readonly, nullable) MPSCNNConvolutionStateNode * convolutionState;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A MPSNNFilterNode representing a MPSCNNFullyConnected kernel   */
@interface MPSCNNFullyConnectedNode : MPSCNNConvolutionNode
/*! @abstract   Init an autoreleased not representing a MPSCNNFullyConnected kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @return     A new MPSNNFilter node for a MPSCNNConvolution kernel.  */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights;

/*! @abstract   Init a node representing a MPSCNNFullyConnected kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @return     A new MPSNNFilter node for a MPSCNNFullyConnected kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A MPSNNFilterNode representing a MPSCNNBinaryConvolution kernel   */
@interface MPSCNNBinaryConvolutionNode : MPSCNNConvolutionNode
/*! @abstract   Init an autoreleased not representing a MPSCNNBinaryConvolution kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @param      scaleValue              A floating point value used to scale the entire convolution.
 *  @param      type                    What kind of binarization strategy is to be used.
 *  @param      flags                   See documentation of MPSCNNBinaryConvolutionFlags.
 *  @return     A new MPSNNFilter node for a MPSCNNBinaryConvolution kernel.  */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights
                            scaleValue: (float) scaleValue
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;

/*! @abstract   Init a node representing a MPSCNNBinaryConvolution kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @param      scaleValue              A floating point value used to scale the entire convolution.
 *  @param      type                    What kind of binarization strategy is to be used.
 *  @param      flags                   See documentation of MPSCNNBinaryConvolutionFlags.
 *  @return     A new MPSNNFilter node for a MPSCNNBinaryConvolution kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights
                            scaleValue: (float) scaleValue
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;

/*! @abstract unavailable */
@property (nonatomic, readonly, nullable) MPSCNNConvolutionStateNode * convolutionState NS_UNAVAILABLE;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A MPSNNFilterNode representing a MPSCNNBinaryFullyConnected kernel   */
@interface MPSCNNBinaryFullyConnectedNode : MPSCNNBinaryConvolutionNode
/*! @abstract   Init an autoreleased not representing a MPSCNNBinaryFullyConnected kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @param      scaleValue              A floating point value used to scale the entire convolution.
 *  @param      type                    What kind of binarization strategy is to be used.
 *  @param      flags                   See documentation of MPSCNNBinaryConvolutionFlags.
 *  @return     A new MPSNNFilter node for a MPSCNNBinaryFullyConnected kernel.  */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights
                            scaleValue: (float) scaleValue
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;

/*! @abstract   Init a node representing a MPSCNNBinaryFullyConnected kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @param      scaleValue              A floating point value used to scale the entire convolution.
 *  @param      type                    What kind of binarization strategy is to be used.
 *  @param      flags                   See documentation of MPSCNNBinaryConvolutionFlags.
 *  @return     A new MPSNNFilter node for a MPSCNNBinaryFullyConnected kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights
                            scaleValue: (float) scaleValue
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A MPSNNFilterNode representing a MPSCNNConvolutionTranspose kernel   */
@interface MPSCNNConvolutionTransposeNode : MPSCNNConvolutionNode
/*! @abstract   Init an autoreleased not representing a MPSCNNConvolutionTransposeNode kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      convolutionState        When the convolution transpose is used to 'undo' an earlier convolution
 *                                      in the graph, it is generally desired that the output image be the same
 *                                      size as the input image to the earlier convolution. You may optionally 
 *                                      specify this size identity by passing in the MPSNNConvolutionStateNode
 *                                      created by the convolution node here.
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @return     A new MPSNNFilter node for a MPSCNNConvolutionTransposeNode kernel.  */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                      convolutionState: (MPSCNNConvolutionStateNode * __nullable) convolutionState
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights;

/*! @abstract   Init a node representing a MPSCNNConvolutionTransposeNode kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      convolutionState        When the convolution transpose is used to 'undo' an earlier convolution
 *                                      in the graph, it is generally desired that the output image be the same
 *                                      size as the input image to the earlier convolution. You may optionally
 *                                      specify this size identity by passing in the MPSCNNConvolutionState node
 *                                      here.
 *  @param      weights                 A pointer to a valid object conforming to the MPSCNNConvolutionDataSource
 *                                      protocol. This object is provided by you to encapsulate storage for
 *                                      convolution weights and biases.
 *  @return     A new MPSNNFilter node for a MPSCNNConvolutionTransposeNode kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                      convolutionState: (MPSCNNConvolutionStateNode * __nullable) convolutionState
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights;

/*! @abstract unavailable */
@property (nonatomic, readonly, nullable) MPSCNNConvolutionStateNode * convolutionState NS_UNAVAILABLE;
@end

#pragma mark -
#pragma mark Neuron Nodes

@class MPSCNNNeuronDescriptor;

/*! @abstract virtual base class for MPSCNNNeuron nodes 
 *  @discussion This is a virtual base class only. Please create a
 *              subclass using +newNeuronNodeWithSouce:descriptor or
 *              by making one of the subclasses directly. Better yet, skip
 *              the node entirely and specify the neuron function directly in
 *              your MPSCNNConvolutionDataSource.descriptor.neuronDescriptor.
 *
 *              MPSCNNNeuronNodes are provided as a representational convenience.
 *              However, you are usually better off incorporating your neuron
 *              into the MPSCNNConvolutionDataSource when possible. The MPSNNGraph
 *              will attempt to optimize away the neuron pass by fusing it with a 
 *              preceeding convolution, but it might be prevented from doing so 
 *              if the neuron pass has a custom padding method or more than one 
 *              node reads from the convolution result. The graph -debugDescription
 *              should reveal what happened.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNNeuronNode : MPSNNFilterNode

/*! @abstract filter parameter a */
@property (nonatomic, readonly)  float a;

/*! @abstract filter parameter a */
@property (nonatomic, readonly)  float b;

-(nonnull instancetype) init NS_UNAVAILABLE;

@end


MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronAbsolute kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = fabs(x)
 *  @endcode */
@interface MPSCNNNeuronAbsoluteNode : MPSCNNNeuronNode
/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronELU kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = a * exp(x) - 1, x <  0
 *             x             , x >= 0
 *  @endcode    */
@interface MPSCNNNeuronELUNode : MPSCNNNeuronNode
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a;

/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a;

@end


MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronLinear kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = a * x + b
 *  @endcode    */
@interface MPSCNNNeuronLinearNode : MPSCNNNeuronNode

+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;

/*! @abstract   Init a node representing a MPSCNNNeuronLinear kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      a                       See discussion above.
 *  @param      b                       See discussion above.
 *  @return     A new MPSNNFilter node for a MPSCNNNeuronLinear kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;


/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronReLU kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = x            if x >= 0
 *           = a * x        if x < 0
 *  @endcode        */
@interface MPSCNNNeuronReLUNode : MPSCNNNeuronNode
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a;

/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronSigmoid kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = 1 / (1 + e^-x)
 *  @endcode        */
@interface MPSCNNNeuronSigmoidNode : MPSCNNNeuronNode
/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronHardSigmoid kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = clamp((a * x) + b, 0, 1)
 *  @endcode        */
@interface MPSCNNNeuronHardSigmoidNode : MPSCNNNeuronNode
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;

/*! @abstract   Init a node representing a MPSCNNNeuronHardSigmoid kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      a                       See discussion above.
 *  @param      b                       See discussion above.
 *  @return     A new MPSNNFilter node for a MPSCNNNeuronHardSigmoid kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;


/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronSoftPlus kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = a * log(1 + e^(b * x))
 *  @endcode            */
@interface MPSCNNNeuronSoftPlusNode : MPSCNNNeuronNode
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;

/*! @abstract   Init a node representing a MPSCNNNeuronSoftPlus kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      a                       See discussion above.
 *  @param      b                       See discussion above.
 *  @return     A new MPSNNFilter node for a MPSCNNNeuronSoftPlus kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;


/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronSoftSign kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = x / (1 + abs(x))
 *  @endcode        */
@interface MPSCNNNeuronSoftSignNode : MPSCNNNeuronNode

/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;
@end



MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract   A node representing a MPSCNNNeuronTanH kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = a * tanh(b * x)
 *  @endcode                */
@interface MPSCNNNeuronTanHNode : MPSCNNNeuronNode
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;

/*! @abstract   Init a node representing a MPSCNNNeuronTanH kernel
 *  @discussion For each pixel, applies the following function:
 *  @code
 *      f(x) = a * tanh(b * x)
 *  @endcode
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      a                       See discussion above.
 *  @param      b                       See discussion above.
 *  @return     A new MPSNNFilter node for a MPSCNNNeuronTanH kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                                     a: (float) a
                                     b: (float) b;


/*! @abstract Create an autoreleased node with default values for parameters a & b */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract Init a node with default values for parameters a & b */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

@end

#pragma mark -
#pragma mark Pooling Nodes

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract  A node for a MPSCNNPooling kernel
 *  @discussion This is an abstract base class that does not correspond with any
 *              particular MPSCNNKernel. Please make one of the MPSCNNPooling
 *              subclasses instead. */
@interface MPSCNNPoolingNode : MPSNNFilterNode
/*! @abstract Convenience initializer for MPSCNNPooling nodes with square non-overlapping kernels
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = strideInPixelsX = strideInPixelsY = size
 *  @return     A new MPSNNFilter node for a MPSCNNPooling kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size;

/*! @abstract Convenience initializer for MPSCNNPooling nodes with square non-overlapping kernels and a different stride
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = size
 *  @param      stride          strideInPixelsX = strideInPixelsY = stride
 *  @return     A new MPSNNFilter node for a MPSCNNPooling kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size
                                stride: (NSUInteger) stride;

/*! @abstract   Init a node representing a MPSCNNPooling kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      kernelWidth             The width of the max filter window
 *  @param      kernelHeight            The height of the max filter window
 *  @param      strideInPixelsX         The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY         The output stride (downsampling factor) in the y dimension.
 *  @return     A new MPSNNFilter node for a MPSCNNPooling kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY;


/*! @abstract Convenience initializer for MPSCNNPooling nodes with square kernels
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = size
 *  @param      stride          strideInPixelsX = strideInPixelsY = stride
 *  @return     A new MPSNNFilter node for a MPSCNNPooling kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size
                                stride: (NSUInteger) stride;

/*! @abstract Convenience initializer for MPSCNNPooling nodes with square non-overlapping kernels
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = strideInPixelsX = strideInPixelsY = size
 *  @return     A new MPSNNFilter node for a MPSCNNPooling kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract  A node representing a MPSCNNPoolingAverage kernel
 *  @discussion The default edge mode is MPSImageEdgeModeClamp  */
@interface MPSCNNPoolingAverageNode : MPSCNNPoolingNode
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract  A node representing a MPSCNNPoolingL2Norm kernel
 *  @discussion The default edge mode is MPSImageEdgeModeClamp  */
@interface MPSCNNPoolingL2NormNode : MPSCNNPoolingNode
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract  A node representing a MPSCNNPoolingMax kernel
 *  @discussion The default edge mode is MPSImageEdgeModeClamp  */
@interface MPSCNNPoolingMaxNode : MPSCNNPoolingNode
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract  A node for a MPSCNNDilatedPooling kernel
 *  @discussion This class corresponds to the MPSCNNDilatedPooling class. */
@interface MPSCNNDilatedPoolingMaxNode : MPSNNFilterNode

@property (nonatomic, readonly)    NSUInteger  dilationRateX;
@property (nonatomic, readonly)    NSUInteger  dilationRateY;


/*! @abstract Convenience initializer for MPSCNNDilatedPooling nodes with square non-overlapping kernels
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = strideInPixelsX = strideInPixelsY = dilationFactorX = dilationFactorY = size
 *  @return     A new MPSNNFilter node for a MPSCNNDilatedPooling kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size;

/*! @abstract Convenience initializer for MPSCNNDilatedPooling nodes with square kernels and equal dilation factors
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = size
 *  @param      stride          strideInPixelsX = strideInPixelsY = stride
 *  @param      dilationRate    dilationRateX = dilationRateY = stride
 *  @return     A new MPSNNFilter node for a MPSCNNDilatedPooling kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size
                                stride: (NSUInteger) stride
                          dilationRate: (NSUInteger) dilationRate;

/*! @abstract   Init a node representing a MPSCNNPooling kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      kernelWidth             The width of the max filter window
 *  @param      kernelHeight            The height of the max filter window
 *  @param      strideInPixelsX         The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY         The output stride (downsampling factor) in the y dimension.
 *  @param      dilationRateX           The dilation factor in the x dimension.
 *  @param      dilationRateY           The dilation factor in the y dimension.
 *  @return     A new MPSNNFilter node for a MPSCNNPooling kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY
                         dilationRateX: (NSUInteger) dilationRateX
                         dilationRateY: (NSUInteger) dilationRateY;

/*! @abstract Convenience initializer for MPSCNNDilatedPooling nodes with square kernels and equal dilation factors
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = size
 *  @param      stride          strideInPixelsX = strideInPixelsY = stride
 *  @param      dilationRate    dilationRateX = dilationRateY = stride
 *  @return     A new MPSNNFilter node for a MPSCNNDilatedPooling kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size
                                stride: (NSUInteger) stride
                          dilationRate: (NSUInteger) dilationRate;

/*! @abstract Convenience initializer for MPSCNNDilatedPooling nodes with square non-overlapping kernels
 *  @param      sourceNode      The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      size            kernelWidth = kernelHeight = strideInPixelsX = strideInPixelsY = dilationRateX = dilationRateY = size
 *  @return     A new MPSNNFilter node for a MPSCNNDilatedPooling kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            filterSize: (NSUInteger) size;

@end

#pragma mark - 
#pragma mark Normalization Nodes

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract virtual base class for CNN normalization nodes */
@interface MPSCNNNormalizationNode : MPSNNFilterNode

@property (readwrite, nonatomic) float       alpha;
@property (readwrite, nonatomic) float       beta;
@property (readwrite, nonatomic) float       delta;

+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode NS_DESIGNATED_INITIALIZER;

@end

/*! @abstract Node representing MPSCNNSpatialNormalization 
 *  @discussion  For each feature channel, the function computes the sum of squares of X inside each rectangle, N2(i,j).
 *               It then divides each element of X as follows:
 *                  Y(i,j) = X(i,j) / (delta + alpha/(kw*kh) * N2(i,j))^beta,
 *               where kw and kh are the kernelWidth and the kernelHeight.
 *
 *      @code
 *        Defaults:
 *             alpha = 1.0f
 *             beta  = 5.0f
 *             delta = 1.0f
 *             kernelHeight = kernelWidth = kernelSize
 *      @endcode
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNSpatialNormalizationNode : MPSCNNNormalizationNode

@property (readwrite, nonatomic) NSUInteger  kernelWidth;
@property (readwrite, nonatomic) NSUInteger  kernelHeight;

+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            kernelSize: (NSUInteger) kernelSize;

-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            kernelSize: (NSUInteger) kernelSize NS_DESIGNATED_INITIALIZER;
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode NS_DESIGNATED_INITIALIZER;

@end

/*! @abstract Node representing MPSCNNLocalContrastNormalization
 *  @discussion  The result is computed for each element of X as follows:
 *
 *                  Y(i,j) = pm + ps * ( X(i,j) - p0 * M(i,j)) / pow((delta + alpha * variance(i,j)), beta),
 *
 *              where kw and kh are the kernelWidth and the kernelHeight and pm, ps and p0 are parameters that
 *              can be used to offset and scale the result in various ways. *
 *      @code
 *        Defaults:
 *             alpha = 1.0f
 *             beta  = 0.5f
 *             delta = 2^-10
 *             pm = 0
 *             ps = 1
 *             p0 = 1
 *             kernelHeight = kernelWidth = kernelSize
 *      @endcode
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNLocalContrastNormalizationNode : MPSCNNNormalizationNode

@property (readwrite, nonatomic) float       pm;
@property (readwrite, nonatomic) float       ps;
@property (readwrite, nonatomic) float       p0;
@property (readwrite, nonatomic) NSUInteger  kernelWidth;
@property (readwrite, nonatomic) NSUInteger  kernelHeight;

+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            kernelSize: (NSUInteger) kernelSize;

-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            kernelSize: (NSUInteger) kernelSize NS_DESIGNATED_INITIALIZER;
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode NS_DESIGNATED_INITIALIZER;

@end

/*! @abstract Node representing MPSCNNCrossChannelNormalization
 *  @discussion  The normalized output is given by:
 *                  Y(i,j,k) = X(i,j,k) / L(i,j,k)^beta,
 *               where the normalizing factor is:
 *                  L(i,j,k) = delta + alpha/N * (sum_{q in Q(k)} X(i,j,q)^2, where
 *               N is the kernel size. The window Q(k) itself is defined as:
 *                  Q(k) = [max(0, k-floor(N/2)), min(D-1, k+floor((N-1)/2)], where
 *
 *              k is the feature channel index (running from 0 to D-1) and
 *              D is the number of feature channels, and alpha, beta and delta are paremeters.
 *      @code
 *        Defaults:
 *             alpha = 1.0f
 *             beta  = 5.0f
 *             delta = 1.0f
 *             kernelHeight = kernelWidth = kernelSize
 *      @endcode
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNCrossChannelNormalizationNode : MPSCNNNormalizationNode

@property (readwrite, nonatomic) NSUInteger  kernelSizeInFeatureChannels;

+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            kernelSize: (NSUInteger) kernelSize;

-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            kernelSize: (NSUInteger) kernelSize NS_DESIGNATED_INITIALIZER;
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode NS_DESIGNATED_INITIALIZER;

@end

#pragma mark -
#pragma mark Image resizing
@protocol MPSImageTransformProvider  <NSSecureCoding, NSObject>
-(MPSScaleTransform) transformForSourceImage: (MPSImage * __nonnull) image
                                      handle: (__nullable id <MPSHandle>) handle;
@end

/*! @abstract Abstract Node representing a image resampling operation
 *  @discussion  Please make a MPSNNBilinearScale or MPSNNLanczosScale object instead
 */
 MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNScaleNode : MPSNNFilterNode
/*! @abstract create an autoreleased node to convert a MPSImage to the desired size
 *  @param  sourceNode    A valid MPSNNImageNode
 *  @param  size          The size of the output image {width, height, depth}    */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            outputSize: (MTLSize) size;

/*! @abstract create an autoreleased node to convert a MPSImage to the desired size for a region of interest
 *  @param  sourceNode            A valid MPSNNImageNode
 *  @param  transformProvider    If non-nil, a valid MPSImageTransformProvider that provides the region of interest
 *  @param  size              The size of the output image {width, height, depth}    */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                     transformProvider: (__nullable id <MPSImageTransformProvider>) transformProvider
                            outputSize: (MTLSize) size;

/*! @abstract init a node to convert a MPSImage to the desired size
 *  @param  sourceNode    A valid MPSNNImageNode
 *  @param  size          The size of the output image {width, height, depth}    */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                            outputSize: (MTLSize) size;

/*! @abstract init a node to convert a MPSImage to the desired size for a region of interest
 *  @param  sourceNode           A valid MPSNNImageNode
 *  @param  transformProvider    If non-nil, a valid MPSImageTransformProvider that provides the region of interest
 *  @param  size                 The size of the output image {width, height, depth}    */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                     transformProvider: (__nullable id <MPSImageTransformProvider>) transformProvider
                            outputSize: (MTLSize) size;

@end

/*!    @abstract A MPSNNScale object that uses bilinear interpolation for resampling
 *     @discussion    Caution: bilinear downscaling by more than a factor of
 *                    two in any dimension causes loss of information if a
 *                    low pass filter is not run over the image first. Details
 *                    may be omitted.    */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNBilinearScaleNode : MPSNNScaleNode
@end

/*!    @abstract A MPSNNScale object that uses the Lanczos resampling filter
 *     @discussion    This method does not require a low pass filter for downsampling
 *                    by more than a factor of two. Caution: may cause ringing, which
 *                    could prove distracting to a neural network unused to seeing it.
 *                    You should use the resampling method that was used to train the
 *                    network. */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNLanczosScaleNode : MPSNNScaleNode
@end


#pragma mark -
#pragma mark Basic Arithmetic

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract virtual base class for basic arithmetic nodes */
@interface MPSNNBinaryArithmeticNode : MPSNNFilterNode

/*! @abstract create an autoreleased arithemtic node with an array of sources
 *  @param  sourceNodes     A valid NSArray containing two sources  */
+(nonnull instancetype) nodeWithSources: (NSArray <MPSNNImageNode *> * __nonnull) sourceNodes;

/*! @abstract create an autoreleased arithemtic node with two sources
 *  @param  left    the left operand
 *  @param  right   the right operand */
+(nonnull instancetype) nodeWithLeftSource: (MPSNNImageNode * __nonnull) left
                               rightSource: (MPSNNImageNode * __nonnull) right;

/*! @abstract init an arithemtic node with an array of sources
 *  @param  sourceNodes     A valid NSArray containing two sources  */
-(nonnull instancetype) initWithSources: (NSArray <MPSNNImageNode *> * __nonnull) sourceNodes;

/*! @abstract init an arithemtic node with two sources
 *  @param  left    the left operand
 *  @param  right   the right operand */
-(nonnull instancetype) initWithLeftSource: (MPSNNImageNode * __nonnull) left
                               rightSource: (MPSNNImageNode * __nonnull) right;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract returns elementwise sum of left + right */
@interface MPSNNAdditionNode : MPSNNBinaryArithmeticNode
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract returns elementwise difference of left - right */
@interface MPSNNSubtractionNode : MPSNNBinaryArithmeticNode
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract returns elementwise product of left * right */
@interface MPSNNMultiplicationNode : MPSNNBinaryArithmeticNode
@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! @abstract returns elementwise quotient of left / right */
@interface MPSNNDivisionNode : MPSNNBinaryArithmeticNode
@end

#pragma mark -
#pragma mark Other Nodes

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! Node representing a the concatenation (in the feature channel dimension) of the results from one or more kernels */
@interface MPSNNConcatenationNode : MPSNNFilterNode
/*! @abstract   Init a autoreleased node that concatenates feature channels from multiple images
 *  @discussion In some neural network designs, it is necessary to append feature channels
 *              from one neural network filter to the results of another. If we have three
 *              image nodes with M, N and O feature channels in them, passed to -initWithSources:
 *              as @[imageM, imageN, imageO], then feature channels [0,M-1] will be drawn from
 *              image M,  feature channels [M, M+N-1] will be drawn from image N and feature channels
 *              [M+N, M+N+O-1] will be drawn from image O.
 *
 *              As all images are padded out to a multiple of four feature channels,
 *              M, N and O here are also multiples of four, even when the MPSImages
 *              are not. That is, if the image is 23 feature channels and one channel
 *              of padding, it takes up 24 feature channels worth of space in the
 *              concatenated result.
 *
 *              Performance Note:  Generally, concatenation is free as long as all
 *              of the sourceNodes are produced by filters in the same MPSNNGraph.
 *              Most MPSCNNKernels have the ability to write their results  at a
 *              feature channel offset within a target MPSImage. However, if the
 *              MPSNNImageNode source nodes come from images external to the MPSNNGraph,
 *              then we have to do a copy operation to assemble the concatenated node.
 *              As a result, when deciding where to break a large logical graph into
 *              multiple smaller MPSNNGraphs, it is better for concatenations to
 *              appear at the ends of subgraphs when possible rather than at the start,
 *              to the extent that all the images used in the concatenation are
 *              produced by that subgraph.
 *
 *  @param      sourceNodes              The MPSNNImageNode representing the source MPSImages for the filter
 *  @return     A new MPSNNFilter node that concatenates its inputs.
 */
+(nonnull instancetype) nodeWithSources: (NSArray <MPSNNImageNode *> * __nonnull) sourceNodes;

/*! @abstract   Init a node that concatenates feature channels from multiple images
 *  @discussion In some neural network designs, it is necessary to append feature channels
 *              from one neural network filter to the results of another. If we have three
 *              image nodes with M, N and O feature channels in them, passed to -initWithSources:
 *              as @[imageM, imageN, imageO], then feature channels [0,M-1] will be drawn from
 *              image M,  feature channels [M, M+N-1] will be drawn from image N and feature channels
 *              [M+N, M+N+O-1] will be drawn from image O.
 *
 *              As all images are padded out to a multiple of four feature channels,
 *              M, N and O here are also multiples of four, even when the MPSImages
 *              are not. That is, if the image is 23 feature channels and one channel
 *              of padding, it takes up 24 feature channels worth of space in the
 *              concatenated result.
 *
 *              Performance Note:  Generally, concatenation is free as long as all
 *              of the sourceNodes are produced by filters in the same MPSNNGraph.
 *              Most MPSCNNKernels have the ability to write their results  at a
 *              feature channel offset within a target MPSImage. However, if the
 *              MPSNNImageNode source nodes come from images external to the MPSNNGraph,
 *              then we have to do a copy operation to assemble the concatenated node. 
 *              As a result, when deciding where to break a large logical graph into 
 *              multiple smaller MPSNNGraphs, it is better for concatenations to 
 *              appear at the ends of subgraphs when possible rather than at the start,
 *              to the extent that all the images used in the concatenation are 
 *              produced by that subgraph.
 *
 *  @param      sourceNodes              The MPSNNImageNode representing the source MPSImages for the filter
 *  @return     A new MPSNNFilter node that concatenates its inputs.
 */
-(nonnull instancetype) initWithSources: (NSArray <MPSNNImageNode *> * __nonnull) sourceNodes;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! Node representing a MPSCNNSoftMax kernel */
@interface MPSCNNSoftMaxNode : MPSNNFilterNode
/*! @abstract   Init a node representing a autoreleased MPSCNNSoftMax kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @return     A new MPSNNFilter node for a MPSCNNSoftMax kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract   Init a node representing a MPSCNNSoftMax kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @return     A new MPSNNFilter node for a MPSCNNSoftMax kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! Node representing a MPSCNNLogSoftMax kernel */
@interface MPSCNNLogSoftMaxNode : MPSNNFilterNode
/*! @abstract   Init a node representing a autoreleased MPSCNNLogSoftMax kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @return     A new MPSNNFilter node for a MPSCNNLogSoftMax kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode;

/*! @abstract   Init a node representing a MPSCNNLogSoftMax kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @return     A new MPSNNFilter node for a MPSCNNLogSoftMax kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode;

@end


MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! Node representing a MPSCNNUpsamplingNearest kernel */
@interface MPSCNNUpsamplingNearestNode : MPSNNFilterNode
/*! @abstract Convenience initializer for an autoreleased MPSCNNUpsamplingNearest nodes
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      integerScaleFactorX     The upsampling factor for the x dimension.
 *  @param      integerScaleFactorY     The upsampling factor for the y dimension.
 *  @return     A new MPSNNFilter node for a MPSCNNUpsamplingNearest kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY;

/*! @abstract   Init a node representing a MPSCNNUpsamplingNearest kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      integerScaleFactorX     The upsampling factor for the x dimension.
 *  @param      integerScaleFactorY     The upsampling factor for the y dimension.
 *  @return     A new MPSNNFilter node for a MPSCNNUpsamplingNearest kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY;

@property (nonatomic, readonly)    double  scaleFactorX;
@property (nonatomic, readonly)    double  scaleFactorY;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
/*! Node representing a MPSCNNUpsamplingBilinear kernel */
@interface MPSCNNUpsamplingBilinearNode : MPSNNFilterNode
/*! @abstract   Init a autoreleased node representing a MPSCNNUpsamplingBilinear kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      integerScaleFactorX     The upsampling factor for the x dimension.
 *  @param      integerScaleFactorY     The upsampling factor for the y dimension.
 *  @return     A new MPSNNFilter node for a MPSCNNUpsamplingBilinear kernel.
 */
+(nonnull instancetype) nodeWithSource: (MPSNNImageNode * __nonnull) sourceNode
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY;

/*! @abstract   Init a node representing a MPSCNNUpsamplingBilinear kernel
 *  @param      sourceNode              The MPSNNImageNode representing the source MPSImage for the filter
 *  @param      integerScaleFactorX     The upsampling factor for the x dimension.
 *  @param      integerScaleFactorY     The upsampling factor for the y dimension.
 *  @return     A new MPSNNFilter node for a MPSCNNUpsamplingBilinear kernel.
 */
-(nonnull instancetype) initWithSource: (MPSNNImageNode * __nonnull) sourceNode
                   integerScaleFactorX: (NSUInteger) integerScaleFactorX
                   integerScaleFactorY: (NSUInteger) integerScaleFactorY;

@property (nonatomic, readonly)    double  scaleFactorX;
@property (nonatomic, readonly)    double  scaleFactorY;

@end



#endif /* MPSNNGraphNodes_h */
