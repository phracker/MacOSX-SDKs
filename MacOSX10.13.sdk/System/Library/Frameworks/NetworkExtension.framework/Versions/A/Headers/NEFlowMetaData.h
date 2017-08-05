/*
 * Copyright (c) 2016 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEFlowMetaData
 * @discussion The NEFlowMetaData class declares the programmatic interface for an object that contains extra information about a flow.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEFlowMetaData : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property sourceAppUniqueIdentifier
 * @discussion A byte string that uniquely identifies the binary for each build of the source application of the flow.
 */
@property (readonly) NSData *sourceAppUniqueIdentifier NS_AVAILABLE(10_11, 9_0);

/*!
 * @property sourceAppSigningIdentifier
 * @discussion A string containing the signing identifier (almost always equivalent to the bundle identifier) of the source app of the flow.
 */
@property (readonly) NSString *sourceAppSigningIdentifier NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
