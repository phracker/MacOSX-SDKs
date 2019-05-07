//
//  VNRequestRevisionProviding.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
@protocol VNRequestRevisionProviding
@required

/*!
	@brief	The revision of the VNRequest subclass that was used to generate the object that implements this protocol.
 */
@property (readonly, nonatomic, assign) NSUInteger requestRevision;

@end


NS_ASSUME_NONNULL_END
