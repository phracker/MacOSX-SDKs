/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppRule.h
 * @discussion This file declares the NEAppRule API. The NEAppRule API is used to create rules that match network traffic by the source application of the traffic.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEAppRule
 * @discussion The NEAppRule class declares the programmatic interface for an object that contains the match conditions for a rule that is used to match network traffic originated by applications.
 *
 * NEAppRule is used in the context of a Network Extension configuration to specify what traffic should be made available to the Network Extension.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithSigningIdentifier:
 * @discussion Initializes a newly-allocated NEAppRule object.
 * @param signingIdentifier The signing identifier of the executable that matches the rule.
 */
- (instancetype)initWithSigningIdentifier:(NSString *)signingIdentifier NS_AVAILABLE(NA, 9_0);

/*!
 * @method initWithSigningIdentifier:designatedRequirement:
 * @discussion Initializes a newly-allocated NEAppRule object.
 * @param signingIdentifier The signing identifier of the executable that matches the rule.
 * @param designatedRequirement The designated requirement of the executable that matches the rule.
 */
- (instancetype)initWithSigningIdentifier:(NSString *)signingIdentifier designatedRequirement:(NSString *)designatedRequirement NS_AVAILABLE(10_11, NA);

/*!
 * @property matchSigningIdentifier
 * @discussion A string containing a signing identifier. If the code signature of the executable being evaluated has a signing identifier equal to this string and all other conditions of the rule match, then the rule matches.
 */
@property (readonly) NSString *matchSigningIdentifier NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDesignatedRequirement
 * @discussion A string containing a designated requirement. If the code signature of the exectuable being evaluated has a designated requirement equal to this string and all other conditions of the rule match, then the rule matches. This property is required on Mac OS X.
 */
@property (readonly) NSString *matchDesignatedRequirement NS_AVAILABLE(10_11, NA);

/*!
 * @property matchPath
 * @discussion A string containing a file system path. If the file system path of the executable being evaluated is equal to this string and all other conditions of the rule match, then the rule matches. This property is optional.
 */
@property (copy, nullable) NSString *matchPath NS_AVAILABLE(10_11, NA);

/*!
 * @property matchDomains
 * @discussion An array of strings. If the destination host of the network traffic being evaluated has a suffix equal to one of the strings in this array and all other conditions of the rule match, then the rule matches. This property is optional.
 */
@property (copy, nullable) NSArray *matchDomains NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
