//
//  MPSNNGraph.h
//  MPS
//
//  Created by Ian Ollmann on 10/17/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSNNGraph_h
#define MPSNNGraph_h

#include <MPSNeuralNetwork/MPSNNGraphNodes.h>
#include <MPSCore/MPSKernel.h>

/*! @abstract   A notification when computeAsyncWithSourceImages:completionHandler: has finished
 *  @param      result  If no error, the image produced by the graph operation.
 *  @param      error   If an error occurs, more information might be found here.
 */
typedef void (^MPSNNGraphCompletionHandler)( MPSImage * __nullable result,
                                             NSError * __nullable error);

/*! @class      MPSNNGraph
 *  @abstract   Optimized representation of a graph of MPSNNImageNodes and MPSNNFilterNodes
 *  @discussion Once you have prepared a graph of MPSNNImageNodes and MPSNNFilterNodes
 *              (and if needed MPSNNStateNodes), you may initialize a MPSNNGraph using 
 *              the MPSNNImageNode that you wish to appear as the result. The MPSNNGraph 
 *              object will introspect the graph representation and determine which nodes
 *              are needed for inputs, and which nodes are produced as output state (if any).
 *              Nodes which are not needed to calculate the result image node are ignored.
 *              Some nodes may be internally concatenated with other nodes for better 
 *              performance.
 *
 *              Note: the MPSNNImageNode that you choose as the result node may be interior
 *                    to a graph. This feature is provided as a means to examine intermediate
 *                    computations in the full graph for debugging purposes.
 *
 *              During MPSNNGraph construction, the graph attached to the result node will 
 *              be parsed and reduced to an optimized representation. This representation may
 *              be saved using the NSSecureCoding protocol for later recall.
 *                  
 *              When decoding a MPSNNGraph using a NSCoder, it will be created against 
 *              the system default MTLDevice. If you would like to set the MTLDevice,
 *              your NSCoder should conform to the <MPSDeviceProvider> protocol.
 *
 *              You may find it helpful to set MPSKernelOptionsVerbose on the graph when
 *              debugging.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNGraph : MPSKernel <NSCopying, NSSecureCoding>

/*! @abstract   Initialize a MPSNNGraph object on a device starting with resultImage working backward
 *  @discussion The MPSNNGraph constructor will start with the indicated result image, and look
 *              to see what MPSNNFilterNode produced it, then look to its dependencies and so
 *              forth to reveal the subsection of the graph necessary to compute the image.
 *  @param      device      The MTLDevice on which to run the graph
 *  @param      resultImage The MPSNNImageNode corresponding to the last image in the graph.
 *                          This is the image that will be returned.  Note: the imageAllocator
 *                          for this node is ignored and the MPSNNGraph.destinationImageAllocator
 *                          is used for this node instead.
 *  @result     A new MPSNNGraph.
 */
-(nullable instancetype)  initWithDevice: (nonnull id <MTLDevice>) device
                             resultImage: (MPSNNImageNode * __nonnull) resultImage NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract Use initWithDevice:resultImage: instead */
-(nonnull instancetype) initWithDevice:(__nonnull id<MTLDevice>)device NS_UNAVAILABLE;

/*! @abstract   Get a list of identifiers for source images needed to calculate the result image */
@property (readonly, nonnull, copy, nonatomic) NSArray<id <MPSHandle>> * sourceImageHandles;

/*! @abstract   Get a list of identifiers for source state objects needed to calculate the result image 
 *  @discussion Not guaranteed to be in the same order as resultStateHandles  */
@property (readonly, nullable, copy, nonatomic) NSArray<id <MPSHandle>> * sourceStateHandles;

/*! @abstract   Get a list of identifiers for intermediate images objects produced by the graph */
@property (readonly, nullable, copy, nonatomic) NSArray<id <MPSHandle>> * intermediateImageHandles;

/*! @abstract   Get a list of identifiers for result state objects produced by the graph
 *  @discussion Not guaranteed to be in the same order as sourceStateHandles  */
@property (readonly, nullable, copy, nonatomic) NSArray<id <MPSHandle>> * resultStateHandles;

/*! @abstract   Get a handle for the graph result image */
@property (readonly, nullable, nonatomic) id <MPSHandle> resultHandle;

/*! @abstract   Should MPSState objects produced by -encodeToCommandBuffer... be temporary objects.
 *  @discussion See MPSState description. Default: YES
 */
@property (readwrite, nonatomic) BOOL  outputStateIsTemporary;

/*! @abstract   Method to allocate the result image from -encodeToCommandBuffer...
 *  @discussion This property overrides the allocator for the final result image in
 *              the graph. Default: MPSImage.defaultAllocator
 */
@property (readwrite, nonatomic, retain, nonnull) id <MPSImageAllocator> destinationImageAllocator;

/*! @abstract       Encode the graph to a MTLCommandBuffer
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImages        A list of MPSImages to use as the source images for the graph.
 *                                      These should be in the same order as the list returned from MPSNNGraph.sourceImageHandles.
 *                                      The images may be image arrays. Typically, this is only one or two images
 *                                      such as a .JPG decoded into a MPSImage*.  If the sourceImages are MPSTemporaryImages,
 *                                      the graph will decrement the readCount by 1, even if the graph actually
 *                                      reads an image multiple times.
 *  @param          sourceStates        A list of MPSState objects to use as state for a graph.
 *                                      These should be in the same order as the list returned from MPSNNGraph.sourceStateHandles.
 *                                      May be nil, if there is no source state. If the sourceStates are temporary,
 *                                      the graph will decrement the readCount by 1, even if the graph actually
 *                                      reads the state multiple times.
 *  @param      intermediateImages      An optional NSMutableArray to receive any MPSImage objects exported as part of its operation.
 *                                      These are only the images that were tagged with MPSNNImageNode.exportFromGraph = YES. The 
 *                                      identity of the states is given by -resultStateHandles.  If temporary, each intermediateImage 
 *                                      will have a readCount of 1.  If the result was tagged exportFromGraph = YES, it will be here
 *                                      too, with a readCount of 2.
 *  @param      destinationStates       An optional NSMutableArray to receive any MPSState objects created as part of its operation.
 *                                      The identity of the states is given by -resultStateHandles.
 *  @result     A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *              It will be automatically released when commandBuffer completes.
 */
-(MPSImage * __nonnull)  encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                  sourceImages: (NSArray<MPSImage*> * __nonnull) sourceImages
                                  sourceStates: (NSArray<MPSState*> * __nullable) sourceStates
                            intermediateImages: (NSMutableArray <MPSImage*> * __nullable) intermediateImages
                             destinationStates: (NSMutableArray<MPSState*> * __nullable) destinationStates;

/*! @abstract       Encode the graph to a MTLCommandBuffer
 *
 *  @discussion     IMPORTANT:  Please use [MTLCommandBuffer addCompletedHandler:] to determine when this work is
 *                  done. Use CPU time that would have been spent waiting for the GPU to encode the next command
 *                  buffer and commit it too.  That way, the work for the next command buffer is ready to go the
 *                  moment the GPU is done. This will keep the GPU busy and running at top speed.
 *
 *                  Those who ignore this advice and use [MTLCommandBuffer waitUntilCompleted] instead will likely
 *                  cause their code to slow down by a factor of two or more. The CPU clock spins down while it
 *                  waits for the GPU. When the GPU completes, the CPU runs slowly for a while until it spins up.
 *                  The GPU has to wait for the CPU to  encode more work (at low clock), giving it plenty of time to
 *                  spin its own clock down. In typical CNN graph usage, neither may ever reach maximum clock
 *                  frequency, causing slow down far beyond what otherwise would be expected from simple failure
 *                  to schedule CPU and GPU work concurrently. Regrattably, it is probable that every performance
 *                  benchmark you see on the net will be based on [MTLCommandBuffer waitUntilCompleted].
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImages        A list of MPSImages to use as the source images for the graph.
 *                                      These should be in the same order as the list returned from MPSNNGraph.sourceImageHandles.
 *  @result     A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *              It will be automatically released when commandBuffer completes.
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                 sourceImages: (NSArray<MPSImage*> * __nonnull) sourceImages;


/*! @abstract Convenience method to execute a graph without having to manage many Metal details
 *  @discussion   This function will synchronously encode the graph on a private command buffer,
 *                commit it to a MPS internal command queue and return. The GPU will start working.
 *                When the GPU is done, the completion handler will be called.  You should use
 *                the intervening time to encode other work for execution on the GPU, so that
 *                the GPU stays busy and doesn't clock down.
 *
 *                The work will be performed on the MTLDevice that hosts the source images.
 *
 *                This is a convenience API.  There are a few situations it does not handle optimally.
 *                These may be better handled using [encodeToCommandBuffer:sourceImages:].
 *                Specifically:
 *                @code
 *                    o     If the graph needs to be run multiple times for different images,
 *                          it would be better to encode the graph multiple times on the same
 *                          command buffer using [encodeToCommandBuffer:sourceImages:]  This
 *                          will allow the multiple graphs to share memory for intermediate
 *                          storage, dramatically reducing memory usage.
 *
 *                    o     If preprocessing or post-processing of the MPSImage is required,
 *                          such as resizing or normalization outside of a convolution, it would
 *                          be better to encode those things on the same command buffer.
 *                          Memory may be saved here too for intermediate storage. (MPSTemporaryImage
 *                          lifetime does not span multiple command buffers.)
 *                @endcode
 *
 *
 *  @param  sourceImages    A list of MPSImages to use as the source images for the graph.
 *                          These should be in the same order as the list returned from
 *                          MPSNNGraph.sourceImageHandles. They should be allocated against
 *                          the same MTLDevice. There must be at least one source image.
 *                          Note: this array is intended to handle the case where multiple
 *                          input images are required to generate a single graph result.
 *                          That is, the graph itself has multiple inputs.  If you need to
 *                          execute the graph multiple times, then call this API multiple
 *                          times, or better yet use [encodeToCommandBuffer:sourceImages:]
 *                          multiple times. (See discussion)
 *
 *  @param  handler         A block to receive any errors generated. This block may run
 *                          on any thread and may be called before this method returns.
 *                          The image, if any, passed to this callback is the same image
 *                          as that returned from the left hand side.
 *
 *  @return    A MPSImage to receive the result. The data in the image will not be valid until
 *             the completionHandler is called.
 */
 -(MPSImage * __nonnull) executeAsyncWithSourceImages: (NSArray<MPSImage*> * __nonnull) sourceImages
                                    completionHandler: (MPSNNGraphCompletionHandler __nonnull) handler;

@end



#endif /* MPSNNGraph_h */
