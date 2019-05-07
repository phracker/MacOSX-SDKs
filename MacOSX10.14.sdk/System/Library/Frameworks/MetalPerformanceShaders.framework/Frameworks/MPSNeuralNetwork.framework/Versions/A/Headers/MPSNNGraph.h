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
 *              debugging. To turn this on during MPSKernel initialization (including
 *              MPSNNGraph initialization) set the MPS_LOG_INFO environment variable.
 *              There is a lot of information about what optimizations are done to your
 *              graph, including some information on why certain optimizations were not
 *              made.
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
 *  @param      resultIsNeeded Commonly, when training a graph, the last MPSImage out of the
 *                             graph is not used. The final gradient filter is run solely to update
 *                             some weights. If resultIsNeeded is set to NO, nil will
 *                             be returned from the left hand side of the -encode call instead,
 *                             and computation to produce the last image may be pruned away.
 *  @result     A new MPSNNGraph.
 */

-(nullable instancetype)  initWithDevice: (nonnull id <MTLDevice>) device
                             resultImage: (MPSNNImageNode * __nonnull) resultImage
                     resultImageIsNeeded: (BOOL) resultIsNeeded NS_DESIGNATED_INITIALIZER;


+(nullable instancetype) graphWithDevice: (nonnull id <MTLDevice>) device
                             resultImage: (MPSNNImageNode * __nonnull) resultImage
                     resultImageIsNeeded: (BOOL) resultIsNeeded;

/*! @abstract   Initialize a MPSNNGraph object on a device starting with resultImage working backward
 *  @discussion The MPSNNGraph constructor will start with the indicated result images, and look
 *              to see what MPSNNFilterNode produced them, then look to its dependencies and so
 *              forth to reveal the subsection of the graph necessary to compute the image. This variant
 *              is provided to support graphs and subgraphs with multiple image outputs.
 *  @param      device      The MTLDevice on which to run the graph
 *  @param      resultImages The MPSNNImageNodes corresponding to the last images in the graph.
 *                           The first image in the array will be returned from the -encode method
 *                           LHS. The rest will be included in the list of intermediate images.
 *  @param      areResultsNeeded  An array of BOOL values with count equal to resultImages.count.
 *                                If NO is passed for a given image, the image itself is marked unneeded
 *                                and might be skipped. The graph will prune this branch back to the
 *                                first requred filter. A filter is required if it generates a needed
 *                                result image, or is needed to update training parameters.
 *  @result     A new MPSNNGraph.
 */
-(nullable instancetype)  initWithDevice: (nonnull id <MTLDevice>) device
                            resultImages: (NSArray <MPSNNImageNode *> * __nonnull) resultImages
                        resultsAreNeeded: (BOOL * __nullable) areResultsNeeded NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), tvos(13.0));

+(nullable instancetype)  graphWithDevice: (nonnull id <MTLDevice>) device
                             resultImages: (NSArray <MPSNNImageNode *> * __nonnull) resultImages
                         resultsAreNeeded: (BOOL * __nullable) areResultsNeeded
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), tvos(13.0));


-(nullable instancetype)  initWithDevice: (nonnull id <MTLDevice>) device
                             resultImage: (MPSNNImageNode * __nonnull) resultImage
MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Please use -initWithDevice:resultImage:resultIsNeeded: instead. Without this information, too much or too little work may occur. Results may be undefined.",
                                      macos(10.13, 10.13.4), ios(11.0, 11.3), tvos(11.0,11.3));

+(nullable instancetype) graphWithDevice: (nonnull id <MTLDevice>) device
                             resultImage: (MPSNNImageNode * __nonnull) resultImage
MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Please use +graphWithDevice:resultImage:resultIsNeeded: instead. Without this information, too much or too little work may occur. Results may be undefined.",
                                      macos(10.13, 10.13.4), ios(11.0, 11.3), tvos(11.0,11.3));

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
 *  @discussion See MPSState description. Default: NO
 */
@property (readwrite, nonatomic) BOOL  outputStateIsTemporary;

/*! @abstract   Method to allocate the result image from -encodeToCommandBuffer...
 *  @discussion This property overrides the allocator for the final result image in
 *              the graph. Default: MPSImage.defaultAllocator
 */
@property (readwrite, nonatomic, retain, nonnull) id <MPSImageAllocator> destinationImageAllocator;


/*! @abstract   The default storage format used for graph intermediate images
 *  @discussion This doesn't affect how data is stored in buffers in states.
 *              Nor does it affect the storage format for weights
 *              such as convolution weights stored by individual filters.
 *              Default: MPSImageFeatureChannelFormatFloat16 */
@property (readwrite, nonatomic) MPSImageFeatureChannelFormat   format;

/*! @abstract   Set at -init time.
 *  @discussion If NO, nil will be returned from -encode calls and some computation
 *              may be omitted. */
@property (readonly, nonatomic) BOOL resultImageIsNeeded;

/*! @abstract   Reinitialize all graph nodes from data sources
 *  @discussion A number of the nodes that make up a graph have a data source
 *              associated with them, for example a MPSCNNConvolutionDataSource
 *              or a MPSCNNBatchNormalizationDataSource. Generally, the data
 *              is read from these once at graph initialization time and then
 *              not looked at again, except during the weight / parameter update
 *              phase of the corresponding gradient nodes and then only if CPU
 *              updates are requested.  Otherwise, update occurs on the GPU,
 *              and the data in the data source is thereafter ignored.
 *
 *              It can happen, though, that your application has determined the
 *              graph should load a new set of weights from the data source.
 *              When this method is called, the graph will find all nodes that
 *              support reloading and direct them to reinitialize themselves
 *              based on their data source.
 *
 *              This process occurs immediately. Your application will
 *              need to make sure any GPU work being done by the graph is complete
 *              to ensure data coherency. Most nodes do not have a data source
 *              and will not be modified. Nodes that are not used by the graph
 *              will not be updated.
 */
-(void) reloadFromDataSources;

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
-(MPSImage * __nullable)  encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                   sourceImages: (NSArray<MPSImage*> * __nonnull) sourceImages
                                   sourceStates: (NSArray<MPSState*> * __nullable) sourceStates
                             intermediateImages: (NSMutableArray<MPSImage*> * __nullable) intermediateImages
                              destinationStates: (NSMutableArray<MPSState*> * __nullable) destinationStates;

/*! @abstract       Encode the graph to a MTLCommandBuffer
 *  @discussion     This interface is like the other except that it operates on a batch of images all
 *                  at once.  In addition, you may specify whether the result is needed.
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
 *  @result     A MPSImageBatch or MPSTemporaryImageBatch allocated per the destinationImageAllocator containing the output of the graph.
 *              It will be automatically released when commandBuffer completes. If resultIsNeeded == NO, then this
 *              will return nil.
 */
-(MPSImageBatch * __nullable) encodeBatchToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                                            sourceImages: (NSArray<MPSImageBatch*> * __nonnull) sourceImages
                                            sourceStates: (NSArray<MPSStateBatch*> * __nullable) sourceStates
                                      intermediateImages: (NSMutableArray <MPSImageBatch*> * __nullable) intermediateImages
                                       destinationStates: (NSMutableArray <MPSStateBatch *> * __nullable) destinationStates
                                MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3));

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
 *              It will be automatically released when commandBuffer completes.  It can be nil if resultImageIsNeeded == NO
 */
-(MPSImage * __nullable) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                 sourceImages: (NSArray<MPSImage*> * __nonnull) sourceImages;

/*! @abstract Convenience method to encode a batch of images*/
-(MPSImageBatch * __nullable) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                            sourceImages: (NSArray<MPSImageBatch*> * __nonnull) sourceImages
                                            sourceStates: (NSArray<MPSStateBatch*> * __nullable) sourceStates;


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

/*! @abstract   Find the number of times a image will be read by the graph *
 *  @discussion From the set of images (or image batches) passed in to the graph, find
 *              the number of times the graph will read an image.  This may be needed
 *              by your application to correctly set the MPSImage.readCount property.
 *  @param      index   The index of the image. The index of the image matches the index of the image in the array returned
 *              by the sourceImageHandles property.
 *  @return     The read count of the image(s) at the index will be reduced by the value returned
 *              when the graph is finished encoding. The readcount of the image(s) must be at least
 *              this value when it is passed into the -encode... method. */
-(NSUInteger) readCountForSourceImageAtIndex: (NSUInteger) index
    MPS_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), tvos(12.1));

/*! @abstract   Find the number of times a state will be read by the graph *
 *  @discussion From the set of state (or state batches) passed in to the graph, find
 *              the number of times the graph will read a state.  This may be needed
 *              by your application to correctly set the MPSState.readCount property.
 *  @param      index   The index of the state. The index of the state matches the index of the state in the array returned
 *              by the sourceStateHandles property.
 *  @return     The read count of the state(s) at the index will be reduced by the value returned
 *              when the graph is finished encoding. The read count of the state(s) must be at least
 *              this value when it is passed into the -encode... method. */
-(NSUInteger) readCountForSourceStateAtIndex: (NSUInteger) index
    MPS_AVAILABLE_STARTING( macos(10.14.1), ios(12.1), tvos(12.1));

@end



#endif /* MPSNNGraph_h */
