//
//  MLCYOLOLossDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCLossDescriptor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCYOLOLossDescriptor
    @discussion The MLCYOLOLossDescriptor specifies a YOLO loss filter descriptor.
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCYOLOLossDescriptor : NSObject <NSCopying>

/*! @property   anchorBoxCount
 *  @abstract   number of anchor boxes used to detect object per grid cell
 */
@property (readonly, nonatomic) NSUInteger anchorBoxCount;

/*! @property   anchorBoxes
 *  @abstract   \p NSData containing the width and height for \p anchorBoxCount anchor boxes
 *              This \p NSData should have 2 floating-point values per anchor box which represent the width
 *              and height of the anchor box.
 */
@property (readonly, nonatomic, nonnull, copy) NSData *anchorBoxes;

/*! @property   shouldRescore
 *  @abstract   Rescore pertains to multiplying the confidence groundTruth with IOU (intersection over union)
 *              of predicted bounding box and the groundTruth boundingBox.  The default is YES
 */
@property (readwrite, nonatomic) BOOL shouldRescore;

/*! @property   scaleSpatialPositionLoss
 *  @abstract   The scale factor for spatial position loss and loss gradient.  The default is 10.0
 */
@property (readwrite, nonatomic) float scaleSpatialPositionLoss;

/*! @property   scaleSpatialSizeLoss
 *  @abstract   The scale factor for spatial size loss and loss gradient.  The default is 10.0
 */
@property (readwrite, nonatomic) float scaleSpatialSizeLoss;

/*! @property   scaleNoObject
 *  @abstract   The scale factor for no object confidence loss and loss gradient.  The default is 5.0
 */
@property (readwrite, nonatomic) float scaleNoObjectConfidenceLoss;

/*! @property   scaleObject
 *  @abstract   The scale factor for object confidence loss and loss gradient.  The default is 100.0
 */
@property (readwrite, nonatomic) float scaleObjectConfidenceLoss;

/*! @property   scaleClass
 *  @abstract   The scale factor for no object classes loss and loss gradient.  The default is 2.0
 */
@property (readwrite, nonatomic) float scaleClassLoss;

/*! @property   positive IOU
 *  @abstract   If the prediction IOU with groundTruth is higher than this
 *              value we consider it a confident object presence, The default is 0.7
 */
@property (readwrite, nonatomic) float minimumIOUForObjectPresence;

/*! @property   negative IOU
 *  @abstract   If the prediction IOU with groundTruth is lower than this
 *              value we consider it a confident object absence.  The default is 0.3
 */
@property (readwrite, nonatomic) float maximumIOUForObjectAbsence;


+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract  Create a YOLO loss descriptor object
    @param     anchorBoxes       The anchor box data
    @param     anchorBoxCount    The number of anchor boxes
    @return    A new MLCYOLOLossDescriptor object.
 */
+ (instancetype)descriptorWithAnchorBoxes:(NSData *)anchorBoxes
                           anchorBoxCount:(NSUInteger)anchorBoxCount;

@end

NS_ASSUME_NONNULL_END
