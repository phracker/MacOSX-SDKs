//
//  MLCLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCDevice;
@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCLayer
    @abstract   The base class for all MLCompute layers
    @discussion There are as many MLCLayer subclasses as there are MLCompute neural network layer objects. Make one of those.
                This class defines an polymorphic interface for them.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCLayer : NSObject

/*! @property   layerID
    @abstract   The layer ID
    @discussion A unique number to identify each layer.  Assigned when the layer is created.
 */
@property (readonly, nonatomic) NSUInteger layerID;

/*! @property   label
    @abstract   A string to help identify this object.
 */
@property (readwrite, nonatomic, copy) NSString *label;

/*! @property   isDebuggingEnabled
    @abstract   A flag to identify if we want to debug this layer when executing a graph that includes this layer
    @discussion If this is set, we will make sure that the result tensor and gradient tensors are available for reading on CPU
                The default is NO.  If isDebuggingEnabled is set to YES,  make sure to set options to enable debugging when
                compiling the graph.  Otherwise this property may be ignored.
 */
@property (readwrite, nonatomic) BOOL isDebuggingEnabled;

/*! @abstract   Determine whether instances of this layer accept source tensors of the given data type on the given device.
    @param      dataType   A data type of a possible input tensor to the layer
    @param      device     A device
    @return     A boolean indicating whether the data type is supported
 */
+ (BOOL)supportsDataType:(MLCDataType)dataType onDevice:(MLCDevice *)device;

/* This is a virtual base class. Make MLCLayer subclass objects instead. */
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


